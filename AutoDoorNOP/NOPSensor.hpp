#pragma once

#include "../JuNOCpp/JuNOC++.hpp"

class NOPSensor
{
public:
    NOP::Attribute<bool> at_person_detected;

public:
    NOPSensor(bool value = false) : at_person_detected {value} {}

    ~NOPSensor()
    {
    }
};