#include <filesystem>
#include "argument_parsers/copy_argument_parser.h"

namespace {
    constexpr int COPY_BUFFER_SIZE = 1024;
}

class Copy {
public:
    Copy(CopyArgumentParser args);

    void run_one_thread() const;

    void parallel_copy();

    void writer();

    void reader();

private:
    CopyArgumentParser args;
    std::mutex _m;
    std::streamsize actual_buffer_size = 0;
    std::shared_ptr<char[]> _buffer;
};

