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

#include <boost/endian/conversion.hpp>

#include <win32pe/fileheader.h>

#include "fileheader_p.h"

using namespace win32pe;

FileHeaderPrivate::FileHeaderPrivate()
    : mMachine(FileHeader::Unknown),
      mNumberOfSections(0),
      mTimeDateStamp(0),
      mPointerToSymbolTable(0),
      mNumberOfSymbols(0),
      mSizeOfOptionalHeader(0),
      mCharacteristics(0)
{
}

bool FileHeaderPrivate::read(std::istream &istream)
{
    if (!istream.read(reinterpret_cast<char*>(this), sizeof(this))) {
        return false;
    }

    boost::endian::little_to_native(mMachine);
    boost::endian::little_to_native(mNumberOfSections);
    boost::endian::little_to_native(mTimeDateStamp);
    boost::endian::little_to_native(mPointerToSymbolTable);
    boost::endian::little_to_native(mNumberOfSymbols);
    boost::endian::little_to_native(mSizeOfOptionalHeader);
    boost::endian::little_to_native(mCharacteristics);

    return true;
}

FileHeader::FileHeader()
    : d(new FileHeaderPrivate)
{
}

FileHeader::FileHeader(const FileHeader &other)
    : d(new FileHeaderPrivate(*other.d))
{
}

FileHeader::~FileHeader()
{
    delete d;
}

FileHeader &FileHeader::operator=(const FileHeader &other)
{
    *d = *other.d;
}

uint16_t FileHeader::machine() const
{
    return d->mMachine;
}
