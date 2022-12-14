#include <filesystem>
#include "argument_parsers/copy_argument_parser.h"
#include <queue>

namespace {
    constexpr int COPY_BUFFER_SIZE = 1024;
}

class Copy {
public:
    Copy(CopyArgumentParser args);

    void runOneThread(int buffer_size = COPY_BUFFER_SIZE) const;

    void parallelCopy(int buffer_size = COPY_BUFFER_SIZE);

    void writer();

    void reader(int buffer_size);

    static std::exception_ptr exceptionPtr;

private:
    CopyArgumentParser _args;
    std::mutex _m;
    std::queue<std::pair<std::unique_ptr<char []>, int>> _buffer_queue;
    bool _done_reading;
};

