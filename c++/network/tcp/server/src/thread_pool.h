#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <cstddef>
#include <functional>

namespace tcp {

class ThreadPool final {
public:
    explicit ThreadPool(std::size_t numThreads);
    ~ThreadPool();
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    void Dispatch(std::function<void()>&& task);

private:
    class Impl;
    Impl* pimpl;
};

} // namespace tcp

#endif /* THREAD_POOL_H */
