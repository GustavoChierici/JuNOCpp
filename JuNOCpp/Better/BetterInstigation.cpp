#include "./BetterInstigation.hpp"

namespace JuNOCpp
{
    BetterInstigation::BetterInstigation()
    {
        this->method = nullptr;
    }

    BetterInstigation::~BetterInstigation()
    {
    }

    void BetterInstigation::setMt(std::function<void()>& func)
    {
        this->method = func;
    }

    void BetterInstigation::update(const bool renotify)
    {
        // std::cout << "INSTIGATION - " << this <<std::endl;
        this->method();
    }

    void BetterInstigation::update(const bool renotify, const bool status)
    {
        // std::cout << "INSTIGATION - " << this <<std::endl;
        this->method();
    }
}