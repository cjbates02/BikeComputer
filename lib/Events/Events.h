#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

#pragma once

template <typename T>
class EventQueue {
protected: 
    std::queue<T> event_queue;
    std::mutex mtx;
    std::condition_variable cv;
public:
    void push(T event) {
        std::unique_lock<std::mutex> lock(mtx);
        event_queue.push(event);
        cv.notify_one();
    }
    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return !event_queue.empty(); });
        T event = event_queue.front();
        event_queue.pop();
        return event;
    }
};