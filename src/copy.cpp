#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <copy.h>
#include <exceptions/io_exception.h>

Copy::Copy(CopyArgumentParser args) : _args(std::move(args)) {
}

void Copy::runOneThread(const int buffer_size) const {

    std::ifstream fin(_args.sourcePath(), std::ifstream::binary);
    if (!fin.is_open())
        throw CopyFileReadException(_args.sourcePath());

    std::ofstream fout(_args.destinationPath(), std::ifstream::binary);
    if (!fout.is_open())
        throw CopyFileWriteException(_args.destinationPath());

    std::unique_ptr<char[]> buffer(new char[buffer_size]);

    while (fin.good()) {
        fin.read(buffer.get(), buffer_size);
        std::streamsize s = fin.gcount();

        if (fout.good())
            fout.write(buffer.get(), s);
        else
            throw CopyFileWriteException(_args.sourcePath());
    }
}

void Copy::parallelCopy(const int buffer_size) {

    std::thread reader(&Copy::reader, this, buffer_size);
    std::thread writer(&Copy::writer, this);

    reader.join();
    writer.join();
}

void Copy::writer() {
//    std::cout << "start writer worker" << std::endl;
    std::ofstream fout(_args.destinationPath(), std::ifstream::binary);
    if (!fout.is_open())
        throw CopyFileWriteException(_args.destinationPath());

    std::pair<std::unique_ptr<char []>, int> buffer_obj;

    while (_done_reading != -1 || !_buffer_queue.empty()) {
        while (!_buffer_queue.empty()) {
            {
                std::unique_lock lk(_m);
//                std::cout << "Read from queue. " << _buffer_queue.size() << " message left" << std::endl;
                buffer_obj = std::move(_buffer_queue.front());
                _buffer_queue.pop();
            }

            fout.write(buffer_obj.first().get(), buffer_obj.second());
            if (!fout.good())
                throw CopyFileWriteException(_args.destinationPath());
        }
    }
}

void Copy::reader(const int buffer_size) {
//    std::cout << "start reader worker" << std::endl;
    std::ifstream fin(_args.sourcePath(), std::ifstream::binary);
    if (!fin.is_open())
        throw CopyFileReadException(_args.sourcePath());

    int local_buffer_size;

    while (fin.good()) {
        std::unique_ptr<char[]> local_buffer(new char[buffer_size]);
        fin.read(local_buffer.get(), buffer_size);
        local_buffer_size = fin.gcount();

        {
            std::unique_lock lk(_m);
            _buffer_queue.push(std::move(std::pair(std::move(local_buffer), local_buffer_size)));
//            std::cout << "Push to queue" << std::endl;
        }
    }
    _done_reading = -1;
}