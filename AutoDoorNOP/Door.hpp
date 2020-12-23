#pragma once

class Door
{
public:
    bool is_open;
public:
    Door(bool value = false) : is_open{value} {}

    ~Door()
    {
    }
};