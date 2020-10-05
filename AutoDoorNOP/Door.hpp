#pragma once

class Door
{
public:
    bool is_open;
public:
    Door(bool value = false)
    {
        this->is_open = value;
    }

    ~Door()
    {
    }
};