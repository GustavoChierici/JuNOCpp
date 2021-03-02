#pragma once
#include "JuNOC++.hpp"

struct Sensor
{
public:
    inline static unsigned long counter{0};

    NOP::Attribute<bool> atIsRead{false};
    NOP::Attribute<bool> atIsActivated{false};

    Sensor();
    ~Sensor();

    void read();
    void activate();
    void deactivate();
};