#include <exceptions/io_exception.h>

#include <utility>

CopyFileReadException::CopyFileReadException(std::string  file_name):
        CopyExceptionBase("Error while reading file (" + file_name + ")", 10) {
}

CopyFileWriteException::CopyFileWriteException(std::string  file_name):
        CopyExceptionBase("Error while writing to file (" + file_name + ")", 11) {
}