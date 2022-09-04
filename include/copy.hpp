#pragma once

#include "filesystem"
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

static int COPY_BUFFER_SIZE = 1024;

class Copy {
public:
    Copy(std::filesystem::path source, std::filesystem::path destination){
        _source = source;
        _destination = destination;
    }

    void run_one_thread(){
        std::ofstream fout(_destination, std::ifstream::binary);
        std::ifstream fin(_source, std::ifstream::binary);
        int buffer_size = 1024;
        char* buffer = new char[buffer_size];

        try {
            while(!fin.eof()) {
                fin.read(buffer, buffer_size);
                std::streamsize s=fin.gcount();
                fout.write(buffer, s);
            }
        }
        catch(...) {
            delete[] buffer;
            try {
                fout.close();
                fin.close();
            }
            catch (...){
                std::cerr << "Error while closing working files"<< std::endl;
            }
            throw ;
        }
        delete[] buffer;
        fout.close();
        fin.close();
    }

    void parallel_copy(){
        char* buffer = new char[COPY_BUFFER_SIZE];

        std::thread reader(&Copy::reader, this, buffer);
        std::thread writer(&Copy::writer, this, buffer);

        reader.join();
        writer.join();

        delete[] buffer;
    }

    void writer(char* buffer) {
        std::cout << "start writer worker"<< std::endl;
        std::ofstream fout(_destination, std::ifstream::binary);

        do {
            std::unique_lock lk(_m);

            if (actual_buffer_size > 0) {
                fout.write(buffer, actual_buffer_size);
            }
            lk.unlock();
        } while (!reading_done);

        fout.close();
    }

    void reader(char* buffer) {
        std::cout << "start reader worker"<< std::endl;
        std::ifstream fin(_source, std::ifstream::binary);

        reading_done = fin.eof();
        while(!reading_done) {
            std::unique_lock lk(_m);

            fin.read(buffer, COPY_BUFFER_SIZE);
            actual_buffer_size = fin.gcount();

            lk.unlock();
            reading_done = fin.eof();
        }
        fin.close();
    }

private:
    std::filesystem::path _source;
    std::filesystem::path _destination;
    std::mutex _m;
    std::streamsize actual_buffer_size = 0;
    bool reading_done = false;
};

