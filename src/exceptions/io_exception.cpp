#include <exceptions/io_exception.h>

#include <utility>

CopyFileReadException::CopyFileReadException(std::string  file_name): CopyExceptionBase("Error while reading file", 10), _file_name(std::move(file_name)) {

}

const char *CopyFileReadException::what() const noexcept {
    return (std::string(CopyExceptionBase::what()) + " (" + _file_name + ")").c_str();
}

CopyFileWriteException::CopyFileWriteException(std::string  file_name): CopyExceptionBase("Error while writing to file", 11), _file_name(std::move(file_name)) {

}

const char *CopyFileWriteException::what() const noexcept {
    return (std::string(CopyExceptionBase::what()) + " (" + _file_name + ")").c_str();
}
