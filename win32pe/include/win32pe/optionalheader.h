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

#ifndef WIN32PE_OPTIONALHEADER_H
#define WIN32PE_OPTIONALHEADER_H

#include <cstdint>

#include <win32pe/win32pe.h>

namespace win32pe
{

class WIN32PE_EXPORT OptionalHeaderPrivate;

/**
 * @brief PE optional header
 */
class WIN32PE_EXPORT OptionalHeader
{
public:

    enum {
        Win32 = 0x010b,
        Win64 = 0x020b
    };

    enum {
        Native = 1,
        GUI    = 2,
        CUI    = 3
    };

    OptionalHeader();
    OptionalHeader(const OptionalHeader &other);
    virtual ~OptionalHeader();

    OptionalHeader &operator=(const OptionalHeader &other);

    uint16_t magic() const;
    uint16_t majorOperatingSystemVersion() const;
    uint16_t minorOperatingSystemVersion() const;
    uint16_t subsystem() const;

private:

    OptionalHeaderPrivate *const d;

    friend class FilePrivate;
};

}

#endif // WIN32PE_OPTIONALHEADER_H
