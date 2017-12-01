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

#include <win32pe/optionalheader.h>

#include "optionalheader_p.h"

using namespace win32pe;

OptionalHeaderPrivate::OptionalHeaderPrivate()
    : mMagic(0),
      mMajorLinkerVersion(0),
      mMinorLinkerVersion(0),
      mSizeOfCode(0),
      mSizeOfInitializedData(0),
      mSizeOfUninitializedData(0),
      mAddressOfEntryPoint(0),
      mBaseOfCode(0),
      mImageBaseLoBaseOfData(0),
      mImageBaseHi(0),
      mSectionAlignment(0),
      mFileAlignment(0),
      mMajorOperatingSystemVersion(0),
      mMinorOperatingSystemVersion(0),
      mMajorImageVersion(0),
      mMinorImageVersion(0),
      mMajorSubsystemVersion(0),
      mMinorSubsystemVersion(0),
      mWin32VersionValue(0),
      mSizeOfImage(0),
      mSizeOfHeaders(0),
      mCheckSum(0),
      mSubsystem(0),
      mDllCharacteristics(0),
      mSizeOfStackReserve(0),
      mSizeOfStackCommit(0),
      mSizeOfHeapReserve(0),
      mSizeOfHeapCommit(0),
      mLoaderFlags(0),
      mNumberOfRvaAndSizes(0),
      mDataDirectory{0}
{
}

bool OptionalHeaderPrivate::read(std::istream &istream)
{
    if (!istream.read(
            reinterpret_cast<char*>(&mMagic),
            reinterpret_cast<char*>(&mSizeOfStackReserve) - reinterpret_cast<char*>(&mMagic)
        )) {
        return false;
    }

    boost::endian::little_to_native_inplace(mMagic);
    boost::endian::little_to_native_inplace(mSizeOfCode);
    boost::endian::little_to_native_inplace(mSizeOfInitializedData);
    boost::endian::little_to_native_inplace(mSizeOfUninitializedData);
    boost::endian::little_to_native_inplace(mAddressOfEntryPoint);
    boost::endian::little_to_native_inplace(mBaseOfCode);
    boost::endian::little_to_native_inplace(mImageBaseLoBaseOfData);
    boost::endian::little_to_native_inplace(mImageBaseHi);
    boost::endian::little_to_native_inplace(mSectionAlignment);
    boost::endian::little_to_native_inplace(mFileAlignment);
    boost::endian::little_to_native_inplace(mMajorOperatingSystemVersion);
    boost::endian::little_to_native_inplace(mMinorOperatingSystemVersion);
    boost::endian::little_to_native_inplace(mMajorImageVersion);
    boost::endian::little_to_native_inplace(mMinorImageVersion);
    boost::endian::little_to_native_inplace(mMajorSubsystemVersion);
    boost::endian::little_to_native_inplace(mMinorSubsystemVersion);
    boost::endian::little_to_native_inplace(mWin32VersionValue);
    boost::endian::little_to_native_inplace(mSizeOfImage);
    boost::endian::little_to_native_inplace(mSizeOfHeaders);
    boost::endian::little_to_native_inplace(mCheckSum);
    boost::endian::little_to_native_inplace(mSubsystem);
    boost::endian::little_to_native_inplace(mDllCharacteristics);

    auto size = mMagic == OptionalHeader::Win32 ? sizeof(uint32_t) : sizeof(uint64_t);
    if (!istream.read(reinterpret_cast<char*>(&mSizeOfStackReserve), size) ||
            !istream.read(reinterpret_cast<char*>(&mSizeOfStackCommit), size) ||
            !istream.read(reinterpret_cast<char*>(&mSizeOfHeapReserve), size) ||
            !istream.read(reinterpret_cast<char*>(&mSizeOfHeapCommit), size)) {
        return false;
    }

    boost::endian::little_to_native_inplace(mSizeOfStackReserve);
    boost::endian::little_to_native_inplace(mSizeOfStackCommit);
    boost::endian::little_to_native_inplace(mSizeOfHeapReserve);
    boost::endian::little_to_native_inplace(mSizeOfHeapCommit);

    if (!istream.read(
            reinterpret_cast<char*>(&mLoaderFlags),
            reinterpret_cast<char*>(&mDataDirectory) - reinterpret_cast<char*>(&mLoaderFlags)
        )) {
        return false;
    }

    boost::endian::little_to_native_inplace(mLoaderFlags);
    boost::endian::little_to_native_inplace(mNumberOfRvaAndSizes);

    if (!istream.read(
            reinterpret_cast<char*>(mDataDirectory),
            sizeof(mDataDirectory) * sizeof(OptionalHeader::ImageDataDirectory)
        )) {
        return false;
    }

    for (int i = 0; i < DATA_DIRECTORY_COUNT; ++i) {
        boost::endian::little_to_native_inplace(mDataDirectory[i].virtualAddress);
        boost::endian::little_to_native_inplace(mDataDirectory[i].size);
    }

    return true;
}

OptionalHeader::OptionalHeader()
    : d(new OptionalHeaderPrivate)
{
}

OptionalHeader::OptionalHeader(const OptionalHeader &other)
    : d(new OptionalHeaderPrivate(*other.d))
{
}

OptionalHeader::~OptionalHeader()
{
    delete d;
}

OptionalHeader &OptionalHeader::operator=(const OptionalHeader &other)
{
    *d = *other.d;
}

uint16_t OptionalHeader::magic() const
{
    return d->mMagic;
}

uint16_t OptionalHeader::majorOperatingSystemVersion() const
{
    return d->mMajorOperatingSystemVersion;
}

uint16_t OptionalHeader::minorOperatingSystemVersion() const
{
    return d->mMinorOperatingSystemVersion;
}

uint16_t OptionalHeader::subsystem() const
{
    return d->mSubsystem;
}

uint16_t OptionalHeader::dllCharacteristics() const
{
    return d->mDllCharacteristics;
}
