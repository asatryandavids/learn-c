#pragma once

#include <executors/executor_base.h>
#include <queue>
#include <future>

typedef std::queue<std::pair<std::unique_ptr<char []>, int>> BufferQueue;

class MultiThreadExecutor: public ExecutorBase {
public:
    MultiThreadExecutor(CopyArgumentParser args);
    void run() final;
private:
    void writer(std::promise<int>& promise);

    void reader(std::promise<int>& promise, int buffer_size);

    std::mutex mutex;
    BufferQueue buffer_queue;
    bool done_reading = false;
};