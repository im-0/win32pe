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

#include <cstring>

#include <boost/endian/conversion.hpp>

#include <win32pe/section.h>

#include "section_p.h"

using namespace win32pe;

SectionPrivate::SectionPrivate()
    : mName{0},
      mPhysicalAddressVirtualSize(0),
      mVirtualAddress(0),
      mSizeOfRawData(0),
      mPointerToRawData(0),
      mPointerToRelocations(0),
      mPointerToLinenumbers(0),
      mNumberOfRelocations(0),
      mNumberOfLinenumbers(0),
      mCharacteristics(0)
{
}

bool SectionPrivate::read(std::istream &istream)
{
    if (!istream.read(
            mName,
            reinterpret_cast<char*>(&mData) - mName
        )) {
        return false;
    }

    boost::endian::little_to_native_inplace(mPhysicalAddressVirtualSize);
    boost::endian::little_to_native_inplace(mVirtualAddress);
    boost::endian::little_to_native_inplace(mSizeOfRawData);
    boost::endian::little_to_native_inplace(mPointerToRawData);
    boost::endian::little_to_native_inplace(mPointerToRelocations);
    boost::endian::little_to_native_inplace(mPointerToLinenumbers);
    boost::endian::little_to_native_inplace(mNumberOfRelocations);
    boost::endian::little_to_native_inplace(mNumberOfLinenumbers);
    boost::endian::little_to_native_inplace(mCharacteristics);

    // Quit early if the data is uninitialized
    if (!mSizeOfRawData) {
        return true;
    }

    // Go to the location in the file containing the section's data
    auto pos = istream.tellg();
    if (!istream.seekg(mPointerToRawData)) {
        return false;
    }

    // Read the data for the section
    mData.resize(mSizeOfRawData);
    if (!istream.read(&mData[0], mSizeOfRawData)) {
        return false;
    }

    // Seek back to the original location in the file
    return static_cast<bool>(istream.seekg(pos));
}

Section::Section()
    : d(new SectionPrivate)
{
}

Section::Section(const Section &other)
    : d(new SectionPrivate(*other.d))
{
}

Section::~Section()
{
    delete d;
}

Section &Section::operator=(const Section &other)
{
    *d = *other.d;
    return *this;
}

std::string Section::name() const
{
    // If the final character is NULL, then strlen can be used to determine the
    // length; otherwise, assume that the string comprises the entire array

    return std::string(
        d->mName,
        d->mName[SECTION_NAME_SIZE - 1] ? SECTION_NAME_SIZE : strlen(d->mName)
    );
}

const std::string &Section::data() const
{
    return d->mData;
}

bool Section::containsRVA(uint32_t rva) const
{
    return d->mVirtualAddress <= rva &&
        rva < d->mVirtualAddress + d->mPhysicalAddressVirtualSize;
}

uint32_t Section::rvaToOffset(uint32_t rva) const
{
    return rva - d->mVirtualAddress;
}
