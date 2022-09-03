#pragma once

#include "filesystem"
#include <fstream>
#include <vector>
#include <iostream>

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

private:
    std::filesystem::path _source;
    std::filesystem::path _destination;
};