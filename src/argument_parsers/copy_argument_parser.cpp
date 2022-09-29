
#include <filesystem>
#include <string>
#include <argument_parsers/copy_argument_parser.h>
#include <sstream>

CopyArgumentParser::CopyArgumentParser(const std::string& source, const std::string& destination, const std::string& string_buffer_size):
_source(std::filesystem::path{ source }), _destination(std::filesystem::path{ destination }), _buffer_size(1024){
    std::istringstream ss(string_buffer_size);
    int size;
    if ((ss >> size) && ss.eof())
    {
        _buffer_size = size;
    }
}

const std::filesystem::path & CopyArgumentParser::sourcePath() const {
    return _source;
}

const std::filesystem::path & CopyArgumentParser::destinationPath() const {
    return _destination;
}

int CopyArgumentParser::bufferSize() const {
    return _buffer_size;
}