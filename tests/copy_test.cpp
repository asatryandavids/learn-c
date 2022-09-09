#include <catch2/catch_test_macros.hpp>
#include "argument_parsers/copy_argument_parser.h"
#include "copy.h"
#include <filesystem>
#include "iostream"
#include <fstream>

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

    std::filesystem::path source = args.source_path();
    std::filesystem::path destination = args.destination_path();
    if (std::filesystem::exists(destination))
        std::filesystem::remove(destination);
    REQUIRE(source.is_relative());
    REQUIRE_FALSE(std::filesystem::is_directory(source));
    REQUIRE(source.is_relative());
    REQUIRE(std::filesystem::exists(source));
    REQUIRE_FALSE(std::filesystem::exists(destination));

    Copy c(args);
    c.run_one_thread();
    REQUIRE(std::filesystem::exists(destination));
}

TEST_CASE( "copy in multi thread" ) {
    CopyArgumentParser args = prepare_files("test_file.txt", "test_file_copy.txt");

    Copy c(args);
    c.parallel_copy();
    REQUIRE(std::filesystem::exists(args.destination_path()));
}

TEST_CASE( "fail open source_file" ) {
    CopyArgumentParser args = CopyArgumentParser("not_exists.txt", "test_file_copy.txt");
    REQUIRE_FALSE(args.validate());
}