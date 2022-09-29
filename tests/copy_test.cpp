#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "argument_parsers/copy_argument_parser.h"
#include "copy.h"
#include <filesystem>
#include "include/test_helper.h"
#include <executors/single_thread_executor.h>
#include <executors/multi_thread_executor.h>

TEST_CASE( "copy in one thread" ) {
    RandomTestFiles random_file("test_file.txt", false);
    random_file.create_text_file();

    REQUIRE(std::filesystem::exists(random_file.file_name));
    REQUIRE_FALSE(std::filesystem::exists(random_file.copy_file_name));

    std::unique_ptr<ExecutorBase> executor(new SingleThreadExecutor(CopyArgumentParser(random_file.file_name, random_file.copy_file_name)));
    Copy(executor.get())();
    REQUIRE(std::filesystem::exists(random_file.copy_file_name));

    REQUIRE(isMD5Correct(random_file.file_name, random_file.copy_file_name));
}

TEST_CASE( "copy binary in multi thread" ) {
    RandomTestFiles random_file("1g.file" ,false);

    random_file.create_binary_with_size(1024);
    REQUIRE(std::filesystem::file_size(random_file.file_name) == 1024 * 1024 * 1024 );

    std::unique_ptr<ExecutorBase> executor(new MultiThreadExecutor(CopyArgumentParser(random_file.file_name, random_file.copy_file_name)));
    Copy(executor.get())();

    REQUIRE(std::filesystem::exists(random_file.copy_file_name));

    REQUIRE(isMD5Correct(random_file.file_name, random_file.copy_file_name));
}

TEST_CASE( "copy text in multi thread" ) {
    RandomTestFiles random_file("test_file_multi.txt", false);
    random_file.create_text_file();

    std::unique_ptr<ExecutorBase> executor(new MultiThreadExecutor(CopyArgumentParser(random_file.file_name, random_file.copy_file_name)));
    Copy(executor.get())();

    REQUIRE(std::filesystem::exists(random_file.copy_file_name));

    REQUIRE(isMD5Correct(random_file.file_name, random_file.copy_file_name));
}

TEST_CASE("CopyArgumentParser") {
    char * in = "in.txt";
    char * out = "out.txt";
    CopyArgumentParser args(in, out);
    REQUIRE(args.sourcePath() == "in.txt");
    REQUIRE(args.destinationPath() == "out.txt");
}