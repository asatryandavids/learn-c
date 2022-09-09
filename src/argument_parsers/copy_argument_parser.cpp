
#include <filesystem>
#include <string>
#include <argument_parsers/copy_argument_parser.h>
#include <iostream>

CopyArgumentParser::CopyArgumentParser(const std::string& source, const std::string& destination){
    _source = std::filesystem::path{ source };
    _destination = std::filesystem::path{ destination };
}

const std::filesystem::path & CopyArgumentParser::source_path() const {
    return _source;
}

const std::filesystem::path & CopyArgumentParser::destination_path() const {
    return _destination;
}

bool CopyArgumentParser::validate() const {
    if (!std::filesystem::exists(_source)){
        std::cerr << "Source file does not exist. " << _source << std::endl;
        return false;
    }
    return true;
}
