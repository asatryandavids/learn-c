#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <copy.h>

Copy::Copy(CopyArgumentParser args) : args(std::move(args)), _buffer(new char[COPY_BUFFER_SIZE]) {
}

void Copy::run_one_thread() const {
    if (!args.validate()) {
        std::cerr << "Invalid argument" << std::endl;
        return;
    }

    std::ifstream fin(args.source_path(), std::ifstream::binary);
    if (fin.rdstate() != 0) {
        std::cerr << "Can't open source file" << std::endl;
        return;
    }

    std::ofstream fout(args.destination_path(), std::ifstream::binary);
    if (fout.rdstate() != 0) {
        std::cerr << "Can't open destination file" << std::endl;
        fin.close();
        return;
    }

    std::unique_ptr<char[]> buffer(new char[COPY_BUFFER_SIZE]);

    try {
        while (!fin.eof()) {
            fin.read(buffer.get(), COPY_BUFFER_SIZE);
            std::streamsize s = fin.gcount();
            fout.write(buffer.get(), s);
        }
    }
    catch (const std::ifstream::failure &e) {
        std::cerr << "Error while reading source file" << std::endl << e.what() << std::endl;
    }
    catch (const std::ofstream::failure &e) {
        std::cerr << "Error while writing to destination file" << std::endl << e.what() << std::endl;
    }

    fout.close();
    fin.close();
}

void Copy::parallel_copy() {
    if (!args.validate()) {
        std::cerr << "Invalid argument" << std::endl;
        return;
    }

    std::thread reader(&Copy::reader, this);
    std::thread writer(&Copy::writer, this);

    reader.join();
    writer.join();
}

void Copy::writer() {
    std::cout << "start writer worker" << std::endl;
    std::ofstream fout(args.destination_path(), std::ifstream::binary);
    if (fout.rdstate() != 0) {
        std::cerr << "Can't open destination file" << std::endl;
        return;
    }

    while (actual_buffer_size != -1) {
        if (actual_buffer_size > 0) {
            fout.write(_buffer.get(), actual_buffer_size);
            actual_buffer_size = 0;
        }
    }

    fout.close();
}

void Copy::reader() {
    std::cout << "start reader worker" << std::endl;
    std::ifstream fin(args.source_path(), std::ifstream::binary);
    if (fin.rdstate() != 0) {
        std::cerr << "Can't open source file" << std::endl;
        return;
    }

    std::shared_ptr<char[]> local_buffer(new char[COPY_BUFFER_SIZE]);
    int local_buffer_size;

    while (!fin.eof()) {
        try {
            fin.read(local_buffer.get(), COPY_BUFFER_SIZE);
            local_buffer_size = fin.gcount();
        }
        catch (const std::ifstream::failure &e) {
            std::cerr << "Error while reading source file" << std::endl << e.what() << std::endl;
            break;
        }

        {
            std::unique_lock lk(_m);
            actual_buffer_size = local_buffer_size;
            std::copy(local_buffer.get(), local_buffer.get() + local_buffer_size, _buffer.get());
        }
    }
    actual_buffer_size = -1;
    fin.close();
}
