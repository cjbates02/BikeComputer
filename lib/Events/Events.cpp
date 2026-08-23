#include "Events.h"

template <typename T>
void EventQueue<T>::push(T event)
{
    std::unique_lock lock(mtx);
    event_queue.push(event);
    cv.notify_one();
}

template <typename T>
T EventQueue<T>::pop()
{
    std::unique_lock lock(mtx);
    cv.wait(lock, [this]() { return !event_queue.empty(); });
    T event = event_queue.front();
    event_queue.pop();
    return event;
}
