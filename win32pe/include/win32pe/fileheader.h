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

#ifndef WIN32PE_FILEHEADER_H
#define WIN32PE_FILEHEADER_H

#include <cstdint>

#include <win32pe/win32pe.h>

namespace win32pe
{

class WIN32PE_EXPORT FileHeaderPrivate;

/**
 * @brief PE file header
 */
class WIN32PE_EXPORT FileHeader
{
public:

    enum {
        i386  = 0x014c,
        amd64 = 0x8664
    };

    enum {
        RelocsStripped       = 0x0001,
        ExecutableImage      = 0x0002,
        LineNumsStripped     = 0x0004,
        LocalSymsStripped    = 0x0008,
        LargeAddressAware    = 0x0020,
        ThirtyTwoBitMachine  = 0x0100,
        DebugStripped        = 0x0200,
        RemovableRunFromSwap = 0x0400,
        NetRunFromSwap       = 0x0800,
        System               = 0x1000,
        DLL                  = 0x2000,
        UPSystemOnly         = 0x4000
    };

    FileHeader();
    FileHeader(const FileHeader &other);
    virtual ~FileHeader();

    FileHeader &operator=(const FileHeader &other);

    uint16_t machine() const;
    uint32_t timeDateStamp() const;
    uint16_t characteristics() const;

private:

    FileHeaderPrivate *const d;

    friend class FilePrivate;
};

}

#endif // WIN32PE_FILEHEADER_H
