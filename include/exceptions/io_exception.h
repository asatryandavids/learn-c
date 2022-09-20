#include "exception_base.h"
#include <string>

class CopyFileReadException : public CopyExceptionBase {
    std::string _file_name;

    public:

    CopyFileReadException(std::string  file_name);
    virtual const char* what() const noexcept override;
};

class CopyFileWriteException : public CopyExceptionBase {
    std::string _file_name;
public:

    CopyFileWriteException(std::string  file_name);
    virtual const char* what() const noexcept override;
};