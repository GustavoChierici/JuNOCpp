#include "./BetterInstigation.hpp"

namespace JuNOCpp
{
    /**
     * Construtor
     * 
     */
    BetterInstigation::BetterInstigation() : method{nullptr}
    {
    }

    /**
     * Destrutor
     * 
     */
    BetterInstigation::~BetterInstigation()
    {
    }

    /**
     * Define o código que a Instigation executará ao ser chamada
     * 
     * @param func 
     */
    void BetterInstigation::setMt(std::function<void()>& func)
    {
        this->method = func;
    }

    /**
     * Executa a Instigation
     * 
     * @param renotify 
     */
    void BetterInstigation::update(const bool renotify)
    {
        // std::cout << "INSTIGATION - " << this <<std::endl;
        this->method();
    }

    /**
     * Executa a Instigation
     * 
     * @param renotify 
     * @param status 
     */
    void BetterInstigation::update(const bool renotify, const bool status)
    {
        // std::cout << "INSTIGATION - " << this <<std::endl;
        this->method();
    }
}