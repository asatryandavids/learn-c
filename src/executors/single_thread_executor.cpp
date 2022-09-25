#include <executors/single_thread_executor.h>
#include <exceptions/io_exception.h>
#include <fstream>
#include <utility>

SingleThreadExecutor::SingleThreadExecutor(CopyArgumentParser args) : ExecutorBase(std::move(args)) {

}

void SingleThreadExecutor::run() {
    std::ifstream fin(_args.sourcePath(), std::ifstream::binary);
    if (!fin.is_open())
        throw CopyFileReadException(_args.sourcePath());

    std::ofstream fout(_args.destinationPath(), std::ifstream::binary);
    if (!fout.is_open())
        throw CopyFileWriteException(_args.destinationPath());

    std::unique_ptr<char[]> buffer(new char[_args.bufferSize()]);

    while (fin.good()) {
        fin.read(buffer.get(), _args.bufferSize());
        std::streamsize s = fin.gcount();

        if (fout.good())
            fout.write(buffer.get(), s);
        else
            throw CopyFileWriteException(_args.sourcePath());
    }
}

