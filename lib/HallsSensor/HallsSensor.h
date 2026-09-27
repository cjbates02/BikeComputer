#include "Events.h"
#include <Arduino.h>

class HallsSensor
{
    private:
        const int GPIO_PIN = 10;
        const int wheelSize = 4; // meters
        volatile uint32_t lastRevolutionTime = 0;
        volatile uint32_t revolutionTime = 0;
        static void hallsInterrupt();
        static HallsSensor* instance;
        float getSpeed();
        EventQueue<Event, 32> &event_q;
    public:
        HallsSensor(EventQueue<Event, 32> &event_q);
        void init();
};