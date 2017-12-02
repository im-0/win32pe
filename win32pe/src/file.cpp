/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <fstream>

#include <boost/endian/conversion.hpp>

#include <win32pe/file.h>
#include <win32pe/section.h>

#include "file_p.h"
#include "fileheader_p.h"
#include "optionalheader_p.h"
#include "section_p.h"

using namespace win32pe;

const int DOSHeaderSize = 0x40;
const int PEOffsetOffset = 0x3c;
const int PESignature = 0x4550;

FilePrivate::FilePrivate(File *file)
    : q(file)
{
}

FilePrivate &FilePrivate::operator=(const FilePrivate &other)
{
    // TODO: it would be nice if this was automated

    mErrorString = other.mErrorString;
    mDOSHeader = other.mDOSHeader;
    mFileHeader = other.mFileHeader;
    mOptionalHeader = other.mOptionalHeader;
    mSections = other.mSections;
    mImportTable = other.mImportTable;

    return *this;
}

bool FilePrivate::readDOSHeader(std::istream &istream)
{
    // The DOS header is 64 bytes and contains the signature and offset to the
    // PE headers; keep all of the data in the DOS header up to the offset so
    // that it can be written back to the file later if necessary

    // Read the header
    mDOSHeader.resize(DOSHeaderSize);
    if (!istream.read(&mDOSHeader[0], DOSHeaderSize)) {
        mErrorString = "unable to read DOS header";
        return false;
    }

    // Confirm the signature
    if (mDOSHeader[0] != 'M' || mDOSHeader[1] != 'Z') {
        mErrorString = "file is missing MZ signature";
        return false;
    }

    // Determine the offset
    uint32_t peOffset = *reinterpret_cast<uint32_t*>(&mDOSHeader[0] + PEOffsetOffset);
    boost::endian::little_to_native_inplace(peOffset);

    // Read the rest of the data up to the PE headers
    mDOSHeader.resize(peOffset);
    if (!istream.read(&mDOSHeader[DOSHeaderSize], peOffset - DOSHeaderSize)) {
        mErrorString = "unable to read to PE headers";
        return false;
    }

    return true;
}

bool FilePrivate::readPEHeaders(std::istream &istream)
{
    // The PE headers consist of a signature, the file header, and the optional
    // header; the optional header has different sizes depending on the machine
    // type

    // Read the signature
    uint32_t peSignature;
    if (!istream.read(reinterpret_cast<char*>(&peSignature), sizeof(peSignature))) {
        mErrorString = "unable to read PE signature";
        return false;
    }

    // Verify the signature
    boost::endian::little_to_native_inplace(peSignature);
    if (peSignature != PESignature) {
        mErrorString = "file is missing PE signature";
        return false;
    }

    // Read the file header
    if (!mFileHeader.d->read(istream)) {
        mErrorString = "unable to read file header";
        return false;
    }

    // Read the optional header
    if (!mOptionalHeader.d->read(istream)) {
        mErrorString = "unable to read optional header";
        return false;
    }

    return true;
}

bool FilePrivate::readSections(std::istream &istream)
{
    // Read the sections
    mSections.resize(mFileHeader.d->mNumberOfSections);
    for (auto it = mSections.begin(); it != mSections.end(); ++it) {
        if (!(*it).d->read(istream)) {
            mErrorString = "unable to read sections";
            return false;
        }
    }

    // Read the import table if present
    const Section *section = q->rvaToSection(
        mOptionalHeader.dataDirectory()[OptionalHeader::ImportTable].virtualAddress
    );
    if (section && !mImportTable.load(section->data())) {
        mErrorString = "unable to read import table";
        return false;
    }

    return true;
}

File::File()
    : d(new FilePrivate(this))
{
}

File::File(const File &other)
    : d(new FilePrivate(this))
{
    *this = other;
}

File::~File()
{
    delete d;
}

File &File::operator=(const File &other)
{
    *d = *other.d;
    return *this;
}

bool File::load(std::istream &istream)
{
    return d->readDOSHeader(istream) &&
           d->readPEHeaders(istream) &&
           d->readSections(istream);
}

bool File::load(const std::string &filename)
{
    std::ifstream ifstream(filename, std::ios::binary);
    if (ifstream.bad()) {
        d->mErrorString = "unable to open file";
        return false;
    }

    return load(ifstream);
}

const FileHeader &File::fileHeader() const
{
    return d->mFileHeader;
}

const OptionalHeader &File::optionalHeader() const
{
    return d->mOptionalHeader;
}

const std::vector<Section> &File::sections() const
{
    return d->mSections;
}

const Section *File::rvaToSection(uint32_t rva) const
{
    for (auto it = d->mSections.begin(); it != d->mSections.end(); ++it) {
        if ((*it).containsRVA(rva)) {
            return &(*it);
        }
    }

    return nullptr;
}

std::string File::string(uint32_t rva) const
{
    const Section *section = rvaToSection(rva);
    std::string value;

    if (section) {
        for (uint32_t i = section->rvaToOffset(rva); i < section->data().size(); ++i) {
            value.append(1, section->data()[i]);
        }
    }

    return value;
}

std::string File::errorString() const
{
    return d->mErrorString;
}
