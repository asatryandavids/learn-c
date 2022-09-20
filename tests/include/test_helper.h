#include <string>
#include <filesystem>
#include <fstream>


std::string get_md5hash( const std::string& fname);
bool isMD5Correct(const std::string& one, const std::string& two);


class RandomTestFiles {
    std::string _file_name;
public:
    RandomTestFiles(std::string file_name, const int size_mb): _file_name(std::move(file_name)) {
        {
            std::ofstream ofs(_file_name);
        }
        std::filesystem::resize_file(_file_name, size_mb * 1024*1024);
    }

    ~RandomTestFiles() {
        if (std::filesystem::exists(_file_name))
            std::filesystem::remove(_file_name);
        if (std::filesystem::exists(_file_name + ".copy"))
            std::filesystem::remove(_file_name + ".copy");
    }
};