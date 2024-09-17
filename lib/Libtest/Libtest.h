#ifndef Libtest_h
#define Libtest_h
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

class Libtest{

public:
    Libtest();
    ~Libtest();

    int testMethod1();

};

#endif