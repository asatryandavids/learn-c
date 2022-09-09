#include "argument_parsers/copy_argument_parser.h"
#include "copy.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        throw std::invalid_argument("Please specify source and destination file path");
    }
    CopyArgumentParser args = CopyArgumentParser(argv[1], argv[2]);
    Copy c(args);
    c.parallel_copy();
}