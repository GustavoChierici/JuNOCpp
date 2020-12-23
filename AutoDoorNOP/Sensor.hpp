#pragma once

class Sensor
{
public:
    bool person_detected;

public:
    Sensor(bool value = false) : person_detected{value} {}

    ~Sensor()
    {
    }
};