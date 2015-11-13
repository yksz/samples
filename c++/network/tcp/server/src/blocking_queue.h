#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <cstddef>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace tcp {

template<typename T>
class BlockingQueue final {
public:
    BlockingQueue() = default;
    ~BlockingQueue() = default;
    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;

    void Push(const T& element);
    void Emplace(T&& element);
    T Pop();
    void Pop(T& element);
    std::size_t Size();
    bool Empty();

private:
    std::queue<T> m_queue;
    std::condition_variable m_condition;
    std::mutex m_mutex;
};

} // namespace tcp

#include "blocking_queue_impl.h"

#endif /* BLOCKING_QUEUE_H */
