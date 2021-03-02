#include "Sensor.hpp"

Sensor::Sensor()
{
    RULE(atIsActivated == true and atIsRead == false)
        INSTIGATE([&](){ 
            this->read(); 
            this->deactivate(); 
            ++Sensor::counter; 
        })
    END_RULE
}

Sensor::~Sensor()
{
}

void Sensor::read()
{
    atIsRead = true;
}

void Sensor::activate()
{
    atIsActivated = true;
    atIsRead = false;
}

void Sensor::deactivate()
{
    atIsActivated = false;
}