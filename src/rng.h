#pragma once
#include <random>

class RandomNumberGenerator
{
public:
    static int getRandomNumber(int min, int max)
    {
        if (min > max)
        {
            int temp = min;
            min = max;
            max = temp;
        }
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        return distrib(gen);
    };

    static float getRandomDecimal(float min, float max)
    {
        if (min > max)
        {
            float temp = min;
            min = max;
            max = temp;
        }
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distrib(min, max);

        return distrib(gen);
    };
};