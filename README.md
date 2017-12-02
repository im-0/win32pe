## win32pe

[![Build Status](https://travis-ci.org/nathan-osman/win32pe.svg?branch=master)](https://travis-ci.org/nathan-osman/win32pe)
[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](http://opensource.org/licenses/MIT)

This library simplifies the task of working with PE files.

### Example

This snippet demonstrates how to retrieve the machine type of an executable on disk.

    #include <win32pe/file.h>
    #include <win32pe/fileheader.h>

    win32pe::File file;
    if (!file.load("test.exe")) {
        // error handling
    }
    switch (file.fileHeader().machine()) {
    case win32pe::FileHeader::i386:
        std::cout << "i386 file\n";
        break;
    case win32pe::FileHeader::amd64:
        std::cout << "amd64 file\n";
        break;
    default:
        std::cout << "unknown file\n";
        break;
    }
