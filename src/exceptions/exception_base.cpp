//
// Created by David Asatrian on 14.09.22.
//

#include <exceptions/exception_base.h>

#include <utility>

CopyExceptionBase::CopyExceptionBase(std::string msg, const int number): _msg(std::move(msg)), _number(number)
{}

const char *CopyExceptionBase::what() const noexcept {
    return _msg.c_str();
}

int CopyExceptionBase::number() const {
    return _number;
}
