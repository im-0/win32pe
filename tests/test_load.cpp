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

#define BOOST_TEST_MODULE load

#include <boost/test/included/unit_test.hpp>

#include <sstream>
#include <string>

#include <win32pe/file.h>
#include <win32pe/fileheader.h>
#include <win32pe/optionalheader.h>
#include <win32pe/section.h>

#include "sample.h"

BOOST_AUTO_TEST_CASE(test_load)
{
    win32pe::File file;
    std::stringstream stringstream(std::string(gSample, gSampleSize));
    BOOST_TEST(file.load(stringstream));

    BOOST_TEST(file.fileHeader().machine() == win32pe::FileHeader::amd64);
    BOOST_TEST(file.fileHeader().timeDateStamp() == 1512189454);
    BOOST_TEST(file.fileHeader().characteristics() ==
        win32pe::FileHeader::RelocsStripped |
        win32pe::FileHeader::ExecutableImage |
        win32pe::FileHeader::ThirtyTwoBitMachine
    );

    BOOST_TEST(file.optionalHeader().magic() == win32pe::OptionalHeader::Win64);
    BOOST_TEST(file.optionalHeader().majorOperatingSystemVersion() == 4);
    BOOST_TEST(file.optionalHeader().minorOperatingSystemVersion() == 0);
    BOOST_TEST(file.optionalHeader().subsystem() == win32pe::OptionalHeader::CUI);
    BOOST_TEST(file.optionalHeader().dllCharacteristics() == 0);

    BOOST_TEST(file.sections().size() == 3);
    BOOST_TEST(file.sections().at(0).name() == ".text");
    BOOST_TEST(file.sections().at(0).data().size() == 512);
}
