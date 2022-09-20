#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "argument_parsers/copy_argument_parser.h"
#include "copy.h"
#include <filesystem>
#include "iostream"
#include "include/test_helper.h"


CopyArgumentParser prepare_files(std::string source_file_name, std::string dest_file_name){
    std::cout << std::boolalpha;

    std::ofstream file;
    file.open (source_file_name, std::ios::out);
    file << "some text to copy";
    file.close();

    return CopyArgumentParser(source_file_name, dest_file_name);
}

TEST_CASE( "copy in one thread" ) {
    CopyArgumentParser args = prepare_files("test_file.txt", "test_file_copy.txt");

    std::filesystem::path source = args.sourcePath();
    std::filesystem::path destination = args.destinationPath();
    if (std::filesystem::exists(destination))
        std::filesystem::remove(destination);
    REQUIRE(source.is_relative());
    REQUIRE_FALSE(std::filesystem::is_directory(source));
    REQUIRE(source.is_relative());
    REQUIRE(std::filesystem::exists(source));
    REQUIRE_FALSE(std::filesystem::exists(destination));

    Copy c(args);
    c.runOneThread();
    REQUIRE(std::filesystem::exists(destination));

    REQUIRE(isMD5Correct(args.sourcePath(), args.destinationPath()));
}

TEST_CASE( "copy in multi thread" ) {
    std::string gig_file = "1g.file";
    RandomTestFiles test_file(gig_file, 1024);
    REQUIRE(gig_file == "1g.file");
    REQUIRE(std::filesystem::file_size(gig_file) == 1024 * 1024 * 1024 );
    CopyArgumentParser args(gig_file, gig_file + ".copy");

    Copy c(args);
    c.parallelCopy();
    REQUIRE(std::filesystem::exists(args.destinationPath()));

    REQUIRE(isMD5Correct(args.sourcePath(), args.destinationPath()));

    if (std::filesystem::exists(gig_file + ".copy"))
        std::filesystem::remove(gig_file + ".copy");

}