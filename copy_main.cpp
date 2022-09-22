#include "argument_parsers/copy_argument_parser.h"
#include "copy.h"
#include <iostream>
#include <exceptions/exception_base.h>

int main(int argc, char* argv[]) {
    // Display each command-line argument.
    std::cout << "\nCommand-line arguments:\n";
    for( int count = 0; count < argc; count++ )
        std::cout << "  argv[" << count << "]   " << argv[count] << "\n";

    if (argc != 3) {
        std::cerr << "Please specify source and destination file path" << std::endl;
        return 1;
    }
    CopyArgumentParser args = CopyArgumentParser(argv[1], argv[2]);
    Copy c(args);
    try {
        c.parallelCopy();
    } catch (CopyExceptionBase& e) {
        std::cerr << e.what();
        return e.number();
    }
}