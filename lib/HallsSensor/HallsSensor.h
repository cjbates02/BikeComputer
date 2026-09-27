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
        void pollInterrupts();
    public:
        void init();
};