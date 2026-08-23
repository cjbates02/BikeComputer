#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

template <typename T>
class EventQueue {
protected: 
    std::queue<T> event_queue;
    std::mutex mtx;
    std::condition_variable cv;
public:
    void push(T event);
    T pop();
};