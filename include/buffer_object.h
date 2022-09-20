#include <memory>

struct BufferObj{
    std::unique_ptr<char []> buffer;
    int buffer_size;
};