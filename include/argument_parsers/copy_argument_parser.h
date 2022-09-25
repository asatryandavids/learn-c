#pragma once

#include <filesystem>
#include <string>

class CopyArgumentParser {
public:
    const std::filesystem::path& sourcePath() const;
    const std::filesystem::path& destinationPath() const;
    int bufferSize() const;
    CopyArgumentParser(const std::string& source, const std::string& destination, const std::string& string_buffer_size = "");

private:

    std::filesystem::path _source;
    std::filesystem::path _destination;
    int _buffer_size;
};
