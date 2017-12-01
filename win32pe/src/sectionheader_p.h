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

#ifndef WIN32PE_SECTIONHEADER_P_H
#define WIN32PE_SECTIONHEADER_P_H

#include <cstdint>
#include <istream>

namespace win32pe
{

class SectionHeaderPrivate
{
public:

    SectionHeaderPrivate();

    bool read(std::istream &istream);

    char mName[8];

    uint32_t mPhysicalAddressVirtualSize;
    uint32_t mVirtualAddress;
    uint32_t mSizeOfRawData;
    uint32_t mPointerToRawData;
    uint32_t mPointerToRelocations;
    uint32_t mPointerToLinenumbers;
    uint16_t mNumberOfRelocations;
    uint16_t mNumberOfLinenumbers;
    uint32_t mCharacteristics;
};

}

#endif // WIN32PE_SECTIONHEADER_P_H
