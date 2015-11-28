#ifndef TCP_THREAD_POOL_H
#define TCP_THREAD_POOL_H

#include <cstddef>
#include <functional>

namespace tcp {

class ThreadPool final {
public:
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool();
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    void Dispatch(std::function<void()>&& task);

private:
    class Impl;
    Impl* pimpl;
};

} // namespace tcp

#endif /* TCP_THREAD_POOL_H */
