//
// Created by David Asatrian on 25.09.22.
//

#include <executors/executor_base.h>

ExecutorBase::ExecutorBase(CopyArgumentParser args): _args(std::move(args)) {

}

ExecutorBase::~ExecutorBase() {

}

const CopyArgumentParser& ExecutorBase::args() const {
    return _args;
}

