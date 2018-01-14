//
// Created by luktor99 on 09.12.17.
//

#ifndef BLINKYTUNE_FIFOQUEUE_H
#define BLINKYTUNE_FIFOQUEUE_H

#include <boost/circular_buffer.hpp>
#include <mutex>
#include <condition_variable>
#include "Settings.h"

/**
 * Represents a thread-safe FIFO queue.
 * @tparam T The queue element type.
 */
template<typename T>
class FIFOQueue {
public:
    /**
     * Timeout exception.
     */
    class TimeoutException : std::exception {
    };

    /**
     * The constructor.
     * @param capacity The capacity of the queue.
     */
    FIFOQueue(std::size_t capacity) : buffer_(capacity) {};

    /**
     * Push an element to the back of the queue.
     * Pushing element to a full queue overwrites the oldest element.
     * @param ptr An unique_ptr to the element.
     */
    void push(std::unique_ptr<T> ptr) {
        std::lock_guard<std::mutex> lock(m_);
        buffer_.push_back(ptr);
        cvEmpty_.notify_all();
    }

    /**
     * Push an element to the back of the queue.
     * Pushing element to a full queue overwrites the oldest element.
     * @param ptr A pointer to the element.
     */
    void push(T *ptr) {
        std::lock_guard<std::mutex> lock(m_);
        buffer_.push_back(std::unique_ptr<T>(ptr));
        cvEmpty_.notify_all();
    }

    /**
     * Get the element from the front and remove it from the queue.
     * Throws an exception if the queue is empty for longer than FIFO_TIMEOUT.
     * @return The element.
     */
    std::unique_ptr<T> pop() {
        std::unique_lock<std::mutex> lock(m_);
        if (!cvEmpty_.wait_for(lock, FIFO_TIMEOUT, [this] { return buffer_.size() != 0; }))
            throw TimeoutException();
        auto ptr = std::move(buffer_.front());
        buffer_.pop_front();
        return ptr;
    }

private:
    boost::circular_buffer<std::unique_ptr<T>> buffer_; /*!< A circular buffer that holds the elements. */
    std::mutex m_; /*!< A mutex allowing concurrent access to the queue. */
    std::condition_variable cvEmpty_; /*!< A conditional variable used to implement the timeout. */
};

#endif //BLINKYTUNE_FIFOQUEUE_H
