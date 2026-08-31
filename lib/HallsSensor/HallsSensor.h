#include <Arduino.h>

class HallsSensor
{
    private:
        const int GPIO_PIN = 10;
    public:
        void poll();
        void init();
};