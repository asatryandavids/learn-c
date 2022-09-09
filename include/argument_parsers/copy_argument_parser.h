#pragma once

#include <filesystem>
#include <string>

class CopyArgumentParser {
public:
    const std::filesystem::path& source_path() const;
    const std::filesystem::path& destination_path() const;
    CopyArgumentParser(const std::string& source, const std::string& destination);

    bool validate() const;
private:

    std::filesystem::path _source;
    std::filesystem::path _destination;
};
