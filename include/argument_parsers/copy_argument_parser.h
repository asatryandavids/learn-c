#pragma once

#include <filesystem>
#include <string>

class CopyArgumentParser {
public:
    const std::filesystem::path& sourcePath() const;
    const std::filesystem::path& destinationPath() const;
    CopyArgumentParser(const std::string& source, const std::string& destination);

private:

    std::filesystem::path _source;
    std::filesystem::path _destination;
};
