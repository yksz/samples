#include "thread_pool.h"
#include <thread>
#include <vector>
#include "blocking_queue.h"

namespace tcp {

class ThreadPool::Impl {
private:
    const std::function<void()> m_poison;
    std::vector<std::thread> m_threads;
    BlockingQueue<std::function<void()>> m_queue;

public:
    explicit Impl(size_t numThreads) {
        for (size_t i = 0; i < numThreads; i++) {
            auto worker = [this]() {
                while (true) {
                    std::function<void()> task;
                    m_queue.Pop(task);
                    if (task.target_type() == m_poison.target_type()) {
                        return;
                    }
                    task();
                }
            };
            m_threads.emplace_back(worker);
        }
    }

    ~Impl() {
        for (size_t i = 0, n = m_threads.size(); i < n; i++) {
            m_queue.Push(m_poison);
        }
        for (std::thread& th : m_threads) {
            th.join();
        }
    }

    void Dispatch(std::function<void()>&& task) {
        if (task.target_type() != m_poison.target_type()) {
            m_queue.Emplace(std::move(task));
        }
    }
};

ThreadPool::ThreadPool(size_t numThreads)
        : pimpl(new ThreadPool::Impl(numThreads)) {
}

ThreadPool::~ThreadPool() {
    delete pimpl;
}

void ThreadPool::Dispatch(std::function<void()>&& task) {
    pimpl->Dispatch(std::move(task));
}

} // namespace tcp
