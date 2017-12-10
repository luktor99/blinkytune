//
// Created by luktor99 on 09.12.17.
//

#ifndef BLINKYTUNE_FIFOQUEUE_H
#define BLINKYTUNE_FIFOQUEUE_H

#include <boost/circular_buffer.hpp>
#include <mutex>
#include <condition_variable>

const auto timeoutDuration = std::chrono::milliseconds(100);

template<typename T>
class FIFOQueue {
public:
    class TimeoutException : std::exception {
    };

    FIFOQueue(std::size_t capacity) : buffer_(capacity) {};

    void push(std::unique_ptr<T> ptr) {
        std::lock_guard<std::mutex> lock(m_);
        buffer_.push_back(ptr);
        cvEmpty_.notify_all();
    }

    void push(T *ptr) {
        std::lock_guard<std::mutex> lock(m_);
        buffer_.push_back(std::unique_ptr<T>(ptr));
        cvEmpty_.notify_all();
    }

    std::unique_ptr<T> pop() {
        std::unique_lock<std::mutex> lock(m_);
        if (!cvEmpty_.wait_for(lock, timeoutDuration, [this] { return buffer_.size() != 0; }))
            throw TimeoutException();
        auto ptr = std::move(buffer_.front());
        buffer_.pop_front();
        return ptr;
    }

private:
    boost::circular_buffer<std::unique_ptr<T>> buffer_;
    std::mutex m_;
    std::condition_variable cvEmpty_;
};

#endif //BLINKYTUNE_FIFOQUEUE_H
