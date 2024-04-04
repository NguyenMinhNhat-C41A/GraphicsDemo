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
};