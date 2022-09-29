#pragma once

#include <executors/executor_base.h>

class SingleThreadExecutor: public ExecutorBase {
public:
    SingleThreadExecutor(CopyArgumentParser args);
    void run() final;
};