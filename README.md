## win32pe

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
