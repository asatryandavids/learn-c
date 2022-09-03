#pragma once

#include <filesystem>
#include <string>

class CopyArgumentParser {
public:
    std::filesystem::path source_path() {
        return std::filesystem::path{ _source };
    }
    std::filesystem::path destination_path() {
        return std::filesystem::path{ _destination };
    }
    bool validate(){
        return true;
    }
    CopyArgumentParser(std::string source, std::string destination){
        _source = source;
        _destination = destination;
    }

private:

    std::string _source;
    std::string _destination;
};