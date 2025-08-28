#pragma once


#define LIMITATION(var, value, min, max)    var = (value); if(var < (min)) { var = (min); } else if(var > (max)) { var = (max); };


namespace Math
{
    uint CalculateCRC(const void *buffer, int size);

    template<class T>
    void CircleIncrease(T *value, T min, T max);

    template<class T>
    void CircleDecrease(T *value, T min, T max);
}
