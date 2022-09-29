
#include <executors/multi_thread_executor.h>
#include <exceptions/io_exception.h>

#include <thread>
#include <fstream>
#include <future>
#include <utility>

MultiThreadExecutor::MultiThreadExecutor(CopyArgumentParser args) : ExecutorBase(std::move(args)) {

}

void MultiThreadExecutor::run() {
    std::promise<int> promise_reader;
    std::future<int> future_reader = promise_reader.get_future();

    std::promise<int> promise_writer;
    std::future<int> future_writer = promise_writer.get_future();

    std::thread reader(&MultiThreadExecutor::reader, this, std::ref(promise_reader), _args.bufferSize());
    std::thread writer(&MultiThreadExecutor::writer, this, std::ref(promise_writer));

    try {
        future_reader.get();
    } catch(const CopyExceptionBase& e) {
        std::cout << "Exception from reader thread: " << e.what() << '\n';
    }

    try {
        future_writer.get();
    } catch(const CopyExceptionBase& e) {
        std::cout << "Exception from writer thread: " << e.what() << '\n';
    }

    reader.join();
    writer.join();
}

void MultiThreadExecutor::reader(std::promise<int>& promise, int buffer_size) {
    try {
        std::ifstream fin(_args.sourcePath());
        if (!fin.is_open())
            throw CopyFileReadException(_args.sourcePath());

        auto local_buffer_size = fin.gcount();

        while (fin.good()) {
            std::unique_ptr<char[]> local_buffer(new char[buffer_size]);
            fin.read(local_buffer.get(), buffer_size);
            local_buffer_size = fin.gcount();

            {
                std::unique_lock lk(mutex);
                buffer_queue.push(std::move(std::pair(std::move(local_buffer), local_buffer_size)));
            }
        }
    }
    catch (const CopyExceptionBase& e)
    {
        promise.set_exception(std::current_exception());
    }
    {
        std::unique_lock lk(mutex);
        done_reading = true;
    }
    promise.set_value(0);
}

void MultiThreadExecutor::writer(std::promise<int>& promise) {
    try {
        std::ofstream fout(_args.destinationPath());
        if (!fout.is_open())
            throw CopyFileWriteException(_args.destinationPath());

        bool l_done = false;
        bool buffer_empty = true;

        while (!l_done || !buffer_empty) {
            if (!buffer_empty) {
                auto buffer_obj = [&]() {
                    std::unique_lock lk(mutex);
                    auto buffer_obj = std::move(buffer_queue.front());
                    buffer_queue.pop();
                    return std::move(buffer_obj);
                }();
                fout.write(buffer_obj.first.get(), buffer_obj.second);
                if (!fout.good())
                    throw CopyFileWriteException(_args.destinationPath());
            } else {
                std::this_thread::yield();
            }
            {
                std::unique_lock lk(mutex);
                l_done = done_reading;
                buffer_empty = buffer_queue.empty();
            }
        }

    }
    catch (const CopyExceptionBase& e)
    {
        promise.set_exception(std::current_exception());
    }
    promise.set_value(0);
}
