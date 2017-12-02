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

#ifndef WIN32PE_IMPORTTABLE_H
#define WIN32PE_IMPORTTABLE_H

#include <cstdint>
#include <string>
#include <vector>

#include <win32pe/win32pe.h>

namespace win32pe
{

class WIN32PE_EXPORT ImportTablePrivate;

/**
 * @brief PE import table
 */
class WIN32PE_EXPORT ImportTable
{
public:

    struct Item
    {
        uint32_t characteristics;
        uint32_t timeDateStamp;
        uint32_t forwarderChain;
        uint32_t name;
        uint32_t firstThunk;
    };

    ImportTable();
    ImportTable(const ImportTable &other);
    virtual ~ImportTable();

    ImportTable &operator=(const ImportTable &other);

    /**
     * @brief Load an import table from a string
     * @param data raw data
     * @return true if the table was loaded
     */
    bool load(const std::string &data);

    /**
     * @brief Access the items in the import table
     * @return reference to a vector containing the items
     */
    const std::vector<Item> &items() const;

private:

    ImportTablePrivate *const d;
};

}

#endif // WIN32PE_IMPORTTABLE_H
