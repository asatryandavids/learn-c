#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include "argument_parsers/copy_argument_parser.h"
#include "copy.h"
#include "include/test_helper.h"

TEST_CASE("buffer size benchmark multi") {
    std::string gig_file = "1g.file";
    CopyArgumentParser args(gig_file, gig_file + ".copy");
    Copy c(args);

    {
        RandomTestFiles test_file(gig_file, 100);
        BENCHMARK("buffer size 1Kb") {
                                         return c.parallelCopy(1024);
                                     };
    }

    {
        RandomTestFiles test_file(gig_file, 100);
        BENCHMARK("buffer size 4Kb") {
                                         return c.parallelCopy(4 * 1024);
                                     };
    }

    {
        RandomTestFiles test_file(gig_file, 100);
        BENCHMARK("buffer size 16Kb") {
                                          return c.parallelCopy(16 * 1024);
                                      };
    }

    {
        RandomTestFiles test_file(gig_file, 100);
        BENCHMARK("buffer size 128Mb") {
                                           return c.parallelCopy(128 * 1024 * 1024);
                                       };
    }
}

TEST_CASE("buffer size benchmark single") {
    std::string gig_file = "1g.file";
    CopyArgumentParser args(gig_file, gig_file + ".copy");
    Copy c(args);

    {
        RandomTestFiles test_file(gig_file, 100);
        BENCHMARK("buffer size 1Kb") {
                                         return c.runOneThread(1024);
                                     };
    }

    {
        RandomTestFiles test_file(gig_file, 100);
        BENCHMARK("buffer size 4Kb") {
                                         return c.runOneThread(4 * 1024);
                                     };
    }

    {
        RandomTestFiles test_file(gig_file, 100);
        BENCHMARK("buffer size 16Kb") {
                                         return c.runOneThread(16 * 1024);
                                     };
    }

    {
        RandomTestFiles test_file(gig_file, 100);
        BENCHMARK("buffer size 128Mb") {
                                         return c.runOneThread(128 * 1024 * 1024);
                                     };
    }
}