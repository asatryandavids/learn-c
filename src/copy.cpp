#include <argument_parsers/copy_argument_parser.hpp>
#include "copy.hpp"

int main(int argc, char** argv) {
    if (argc != 3) {
        throw std::invalid_argument("Please specify source and destination file path");
    }
    CopyArgumentParser args = CopyArgumentParser(argv[1], argv[2]);
    args.validate();

    Copy c(args.source_path(), args.destination_path());
    c.run_one_thread();
}
