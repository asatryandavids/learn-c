
#include <filesystem>
#include <string>
#include <argument_parsers/copy_argument_parser.h>
#include <iostream>

CopyArgumentParser::CopyArgumentParser(const std::string& source, const std::string& destination){
    _source = std::filesystem::path{ source };
    _destination = std::filesystem::path{ destination };
}

const std::filesystem::path & CopyArgumentParser::sourcePath() const {
    return _source;
}

const std::filesystem::path & CopyArgumentParser::destinationPath() const {
    return _destination;
}