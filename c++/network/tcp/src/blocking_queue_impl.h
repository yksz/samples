#include "blocking_queue.h"

namespace tcp {

template<typename T>
void BlockingQueue<T>::Push(const T& element) {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(element);
    }
    m_condition.notify_one();
}

template<typename T>
void BlockingQueue<T>::Emplace(T&& element) {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.emplace(std::move(element));
    }
    m_condition.notify_one();
}

template<typename T>
T BlockingQueue<T>::Pop() {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_queue.empty()) {
        m_condition.wait(lock);
    }
    T element = m_queue.front();
    m_queue.pop();
    return element;
}

template<typename T>
void BlockingQueue<T>::Pop(T& element) {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_queue.empty()) {
        m_condition.wait(lock);
    }
    element = std::move(m_queue.front());
    m_queue.pop();
}

template<typename T>
size_t BlockingQueue<T>::Size() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.size();
}

template<typename T>
bool BlockingQueue<T>::Empty() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.empty();
}

} // namespace tcp
