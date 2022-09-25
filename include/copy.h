#pragma once

#include <filesystem>
#include <argument_parsers/copy_argument_parser.h>
#include <executors/executor_base.h>

class Copy {
public:
    Copy(ExecutorBase* executor);

    void operator() ();

private:
    ExecutorBase* _executor = nullptr;
};

