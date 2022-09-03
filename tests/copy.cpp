#include <catch2/catch_test_macros.hpp>
#include "argument_parsers/copy_argument_parser.hpp"
#include "copy.hpp"
#include <filesystem>
#include "iostream"
#include <fstream>

void create_file(std::string file_name){
    std::ofstream file;
    file.open (file_name, std::ios::out);
    file << "some text to copy";
    file.close();
}

TEST_CASE( "copy in one thread" ) {
    std::cout << std::boolalpha;
    auto source_name = "test_file.txt";
    create_file(source_name);
    CopyArgumentParser args = CopyArgumentParser(source_name, "test_file_copy.txt");
    std::filesystem::path source = args.source_path();
    std::filesystem::path destination = args.destination_path();
    if (std::filesystem::exists(destination))
        std::filesystem::remove(destination);
    REQUIRE(source.is_relative());
    REQUIRE_FALSE(std::filesystem::is_directory(source));
    REQUIRE(source.is_relative());
    REQUIRE(std::filesystem::exists(source));
    REQUIRE_FALSE(std::filesystem::exists(destination));

    Copy c(source, destination);
    c.run_one_thread();
    REQUIRE(std::filesystem::exists(destination));
}