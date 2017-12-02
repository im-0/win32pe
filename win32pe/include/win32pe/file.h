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

#ifndef WIN32PE_FILE_H
#define WIN32PE_FILE_H

#include <istream>
#include <string>
#include <vector>

#include <win32pe/win32pe.h>

namespace win32pe
{

class FileHeader;
class OptionalHeader;
class Section;

class WIN32PE_EXPORT FilePrivate;

/**
 * @brief PE file
 */
class WIN32PE_EXPORT File
{
public:

    File();
    File(const File &other);
    virtual ~File();

    File &operator=(const File &other);

    /**
     * @brief Load a PE file from a stream
     * @param stream reference to an input stream
     * @return true if the file was loaded
     */
    bool load(std::istream &istream);

    /**
     * @brief Load a PE file from disk
     * @param filename path to file
     * @return true if the file was loaded
     */
    bool load(const std::string &filename);

    /**
     * @brief Access the PE file's file header
     * @return reference to the file header
     */
    const FileHeader &fileHeader() const;

    /**
     * @brief Access the PE file's optional header
     * @return reference to the optional header
     */
    const OptionalHeader &optionalHeader() const;

    /**
     * @brief Access the PE file's sections
     * @return reference to a vector containing the sections
     */
    const std::vector<Section> &sections() const;

    /**
     * @brief Retrieve a description of the last error
     * @return description or empty string if no error has occurred
     */
    std::string errorString() const;

private:

    FilePrivate *const d;
};

}

#endif // WIN32PE_FILE_H
