#include "exception_base.h"
#include <string>

class CopyFileReadException : public CopyExceptionBase {
    std::string _msg;

    public:

    CopyFileReadException(std::string file_name);
};

class CopyFileWriteException : public CopyExceptionBase {
    std::string _file_name;
public:

    CopyFileWriteException(std::string file_name);
};