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

#ifndef WIN32PE_SECTIONHEADER_H
#define WIN32PE_SECTIONHEADER_H

#include <string>

#include <win32pe/win32pe.h>

namespace win32pe
{

class WIN32PE_EXPORT SectionHeaderPrivate;

/**
 * @brief PE section header
 */
class WIN32PE_EXPORT SectionHeader
{
public:

    SectionHeader();
    SectionHeader(const SectionHeader &other);
    virtual ~SectionHeader();

    SectionHeader &operator=(const SectionHeader &other);

    std::string name() const;

private:

    SectionHeaderPrivate *const d;
};

}

#endif // WIN32PE_SECTIONHEADER_H
