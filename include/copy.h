#include <filesystem>
#include "argument_parsers/copy_argument_parser.h"
#include <queue>
#include <buffer_object.h>

namespace {
    constexpr int COPY_BUFFER_SIZE = 4 * 1024;
}

class Copy {
public:
    Copy(CopyArgumentParser args);

    void runOneThread(int buffer_size = COPY_BUFFER_SIZE) const;

    void parallelCopy(int buffer_size = COPY_BUFFER_SIZE);

    void writer();

    void reader(int buffer_size);

private:
    CopyArgumentParser _args;
    std::mutex _m;
    std::queue<BufferObj> _buffer_queue;
    std::streamsize _done_reading = 0;
};

