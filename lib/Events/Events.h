#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

enum class EventIds {
    WheelRevolution,
    ButtonPressed,
    ButtonReleased,
    None
};

enum class ButtonIds
{
    Select,
    Next,
    Previous
};

struct Event {
    EventIds id;
    union {
        struct {
            uint32_t revolutionTime;
        } wheel;
        struct {
            ButtonIds btnId;
        } button;
    };
};

template <typename T, size_t SIZE>
class EventQueue {
private:
    QueueHandle_t queue;

public:
    EventQueue()
    {
        queue = xQueueCreate(SIZE, sizeof(T));
    }

    bool push(T event)
    {
        return xQueueSend(queue, &event, 0) == pdTRUE;
    }

    bool pushFromISR(T event)
    {
        BaseType_t higherPriorityTaskWoken = pdFALSE;

        bool success =
            xQueueSendFromISR(
                queue,
                &event,
                &higherPriorityTaskWoken
            ) == pdTRUE;

        if (higherPriorityTaskWoken) {
            portYIELD_FROM_ISR();
        }

        return success;
    }

    bool pop(T& event)
    {
        return xQueueReceive(queue, &event, 0) == pdTRUE;
    }
};