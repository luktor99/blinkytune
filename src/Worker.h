//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_WORKER_H
#define BLINKYTUNE_WORKER_H


#include <thread>

/**
 * This is an abstract class representing a worker thread.
 */
class Worker {
public:
    /**
     * The constructor.
     */
    Worker() : stop_(false) {}

    /**
     * Start the worker thread.
     */
    void run() {
        threadPtr_ = std::unique_ptr<std::thread>(new std::thread([this] { runLoop(); }));
    }

    /**
     * Join the worker thread with the current thread.
     */
    void join() {
        threadPtr_->join();
    }

    /**
     * Stop the worker thread.
     */
    void stop() {
        stop_ = true;
    }

private:
    /**
     * The main loop of the worker thread. It checks if stop has been requested.
     */
    void runLoop() {
        while (!stop_)
            mainLoop();
    }

    /**
    * The main loop of the thread.
    */
    virtual void mainLoop() = 0;

    bool stop_; /*!< A flag triggered when stop is requested. */
    std::unique_ptr<std::thread> threadPtr_; /*!< An unique_ptr to the worker thread. */
};


#endif //BLINKYTUNE_WORKER_H
