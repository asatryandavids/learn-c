
#include <iostream>
#include <copy.h>


Copy::Copy(ExecutorBase* executor) : _executor(executor) {
    assert(_executor);
    std::cout << "Try to copy " << _executor->args().sourcePath() << " to " << _executor->args().destinationPath() << std::endl;
}

void Copy::operator()() {
    _executor->run();
}