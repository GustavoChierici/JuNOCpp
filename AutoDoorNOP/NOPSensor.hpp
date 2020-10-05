#pragma once

#include "JuNOCpp/JuNOC++.hpp"

class NOPSensor: public FBE
{
public:
    Boolean* at_person_detected;

public:
    NOPSensor(bool value = false)
    {
        this->at_person_detected = new Boolean(value);
    }

    ~NOPSensor()
    {
        delete this->at_person_detected;
    }
};