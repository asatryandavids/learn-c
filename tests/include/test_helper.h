#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>


std::string get_md5hash( const std::string& fname);
bool isMD5Correct(const std::string& one, const std::string& two);


struct RandomTestFiles {
    std::string file_name;
    std::string copy_file_name;
    bool clear;

    RandomTestFiles(std::string file_name, bool clear = true): file_name(std::move(file_name)), copy_file_name(this->file_name + ".copy"), clear(clear) {
    }

    void create_binary_with_size(int size_mb) {
        if (!clear)
            remove_related_files();

        std::cout << "Creating binary file with name " << file_name << ". It will be copied to " << copy_file_name << std::endl;
        {
            std::ofstream ofs(file_name);
        }
        std::filesystem::resize_file(file_name, size_mb * 1024 * 1024);
    }

    void create_text_file() {
        if (!clear)
            remove_related_files();

        std::ofstream file;
        file.open (file_name, std::ios::out);
        file << R""""(# Install script for directory: /Users/David_Asatrian/epam/learn/learn-c

# Set the install prefix
        if(NOT DEFINED CMAKE_INSTALL_PREFIX)
        set(CMAKE_INSTALL_PREFIX "/usr/local")
        endif()
        string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
        if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
        if(BUILD_TYPE)
            string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
        CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
        else()
        set(CMAKE_INSTALL_CONFIG_NAME "Release")
        endif()
        message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
        endif()

# Set the component getting installed.
        if(NOT CMAKE_INSTALL_COMPONENT)
            if(COMPONENT)
                message(STATUS "Install component: \"${COMPONENT}\"")
        set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
        else()
        set(CMAKE_INSTALL_COMPONENT)
        endif()
        endif()

# Is this installation the result of a crosscompile?
        if(NOT DEFINED CMAKE_CROSSCOMPILING)
        set(CMAKE_CROSSCOMPILING "FALSE")
        endif()

# Set default install directory permissions.
        if(NOT DEFINED CMAKE_OBJDUMP)
        set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
        endif()

        if(CMAKE_INSTALL_COMPONENT)
            set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
        else()
        set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
        endif()

        string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
        "${CMAKE_INSTALL_MANIFEST_FILES}")
        file(WRITE "/Users/David_Asatrian/epam/learn/learn-c/cmake-build-release/${CMAKE_INSTALL_MANIFEST}"
                   "${CMAKE_INSTALL_MANIFEST_CONTENT}"))"""";
        file.close();
    }

    ~RandomTestFiles() {
        if (clear)
            remove_related_files();
    }
private:
    void remove_related_files() const{
        if (std::filesystem::exists(file_name))
            std::filesystem::remove(file_name);
        if (std::filesystem::exists(copy_file_name))
            std::filesystem::remove(copy_file_name);
    }
};