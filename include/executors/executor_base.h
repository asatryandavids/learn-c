#pragma once

#include <argument_parsers/copy_argument_parser.h>

class ExecutorBase {
public:
    ExecutorBase(CopyArgumentParser args);
    virtual void run() = 0;
    virtual ~ExecutorBase();

    const CopyArgumentParser& args() const;
protected:
    const CopyArgumentParser _args;
};