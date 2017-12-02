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

#ifndef WIN32PE_OPTIONALHEADER_P_H
#define WIN32PE_OPTIONALHEADER_P_H

#include <cstdint>
#include <istream>

#include <win32pe/optionalheader.h>

namespace win32pe
{

class OptionalHeaderPrivate
{
public:

    OptionalHeaderPrivate();

    bool read(std::istream &istream);

    // Both 32 and 64-bit executables share the first few fields - the
    // exception being ImageBase, which has a different size and BaseOfData
    // which does not exist in the 64-bit struct - because BaseOfData occupies
    // the same amount of space as the extra bytes for ImageBase, a 32-bit
    // integer can serve a dual-purpose - it provides storage for either
    // BaseOfData or the low bytes of ImageBase

    uint16_t mMagic;
    uint8_t  mMajorLinkerVersion;
    uint8_t  mMinorLinkerVersion;
    uint32_t mSizeOfCode;
    uint32_t mSizeOfInitializedData;
    uint32_t mSizeOfUninitializedData;
    uint32_t mAddressOfEntryPoint;
    uint32_t mBaseOfCode;
    uint32_t mImageBaseLoBaseOfData;
    uint32_t mImageBaseHi;
    uint32_t mSectionAlignment;
    uint32_t mFileAlignment;
    uint16_t mMajorOperatingSystemVersion;
    uint16_t mMinorOperatingSystemVersion;
    uint16_t mMajorImageVersion;
    uint16_t mMinorImageVersion;
    uint16_t mMajorSubsystemVersion;
    uint16_t mMinorSubsystemVersion;
    uint32_t mWin32VersionValue;
    uint32_t mSizeOfImage;
    uint32_t mSizeOfHeaders;
    uint32_t mCheckSum;
    uint16_t mSubsystem;
    uint16_t mDllCharacteristics;

    // These fields are identical in purpose but differ in size - therefore
    // they are 64-bit fields and are truncated as necessary for 32-bit
    // executables

    uint64_t mSizeOfStackReserve;
    uint64_t mSizeOfStackCommit;
    uint64_t mSizeOfHeapReserve;
    uint64_t mSizeOfHeapCommit;

    // These fields are identical in 32 and 64-bit executables

    uint32_t mLoaderFlags;
    uint32_t mNumberOfRvaAndSizes;

    OptionalHeader::DataDirectoryItem mDataDirectory[OptionalHeader::DataDirectoryCount];
};

}

#endif // WIN32PE_OPTIONALHEADER_P_H
