//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_WORKER_H
#define BLINKYTUNE_WORKER_H

#include <thread>

class Worker {
public:
    Worker() : stop_(false) {}

    void run() {
        threadPtr_ = std::unique_ptr<std::thread>(new std::thread([this] { runLoop(); }));
    }

    void join() {
        threadPtr_->join();
    }

    void stop() {
        stop_ = true;
    }

private:
    void runLoop() {
        while (!stop_)
            mainLoop();
    }

    virtual void mainLoop() = 0;

    bool stop_;
    std::unique_ptr<std::thread> threadPtr_;
};

#endif //BLINKYTUNE_WORKER_H
