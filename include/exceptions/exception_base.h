#pragma once

#include <exception>
#include <iostream>
#include <string>

class CopyExceptionBase : public std::exception
{
    std::string _msg;
    int _number;
public:
    CopyExceptionBase(std::string msg, int number);
    const char* what() const noexcept override;

    int number() const;
};