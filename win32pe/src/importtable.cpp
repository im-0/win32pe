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

#include <win32pe/importtable.h>

#include "importtable_p.h"

using namespace win32pe;

ImportTablePrivate::ImportTablePrivate()
{
}

ImportTable::ImportTable()
    : d(new ImportTablePrivate)
{
}

ImportTable::ImportTable(const ImportTable &other)
    : d(new ImportTablePrivate(*other.d))
{
}

ImportTable::~ImportTable()
{
    delete d;
}

ImportTable &ImportTable::operator=(const ImportTable &other)
{
    *d = *other.d;
    return *this;
}

bool ImportTable::load(const std::string &data)
{
    // Read Items until either one is found with all zeroes or the end of the
    // data is reached (which is an error)

    for (size_t i = 0; i + sizeof(Item) <= data.size(); i += sizeof(Item)) {
        Item item;
        memcpy(&item, &data[0] + i, sizeof(Item));
        if (!item.characteristics &&
                !item.timeDateStamp &&
                !item.forwarderChain &&
                !item.name &&
                !item.firstThunk) {
            return true;
        }
        d->mItems.push_back(item);
    }

    return false;
}

const std::vector<ImportTable::Item> &ImportTable::items() const
{
    return d->mItems;
}
