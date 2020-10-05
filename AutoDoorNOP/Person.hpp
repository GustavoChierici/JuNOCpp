#pragma once

class Person
{
public:
    bool pos_door_front;
    double velocity;

public:
    Person(bool value = false, double velocity = 0.f)
    {
        this->pos_door_front = value;
        this->velocity = velocity;
    }

    ~Person()
    {
    }
};