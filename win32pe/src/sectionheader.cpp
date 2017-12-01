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

#include <win32pe/sectionheader.h>

#include "sectionheader_p.h"

using namespace win32pe;

SectionHeaderPrivate::SectionHeaderPrivate()
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

bool SectionHeaderPrivate::read(std::istream &istream)
{
    if (!istream.read(reinterpret_cast<char*>(this), sizeof(*this))) {
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

    return true;
}

SectionHeader::SectionHeader()
    : d(new SectionHeaderPrivate)
{
}

SectionHeader::SectionHeader(const SectionHeader &other)
    : d(new SectionHeaderPrivate(*other.d))
{
}

SectionHeader::~SectionHeader()
{
    delete d;
}

SectionHeader &SectionHeader::operator=(const SectionHeader &other)
{
    *d = *other.d;
}

std::string SectionHeader::name() const
{
    return std::string(d->mName, sizeof(d->mName));
}
