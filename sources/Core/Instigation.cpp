#include "Instigation.hpp"

namespace JuNOCpp
{
    namespace Core
    {
        /**
         * Construtor
         * 
         */
        Instigation::Instigation(Utils::CustomString name, std::function<void()> func):
        Notifiable(name),
        method{func}
        {
        }

        /**
         * Destrutor
         * 
         */
        Instigation::~Instigation()
        {
        }

        /**
         * Define o código que a Instigation executará ao ser chamada
         * 
         * @param func 
         */
        void Instigation::setMt(std::function<void()>& func)
        {
            this->method = func;
        }

        /**
         * Executa a Instigation
         * 
         * @param renotify 
         */
        void Instigation::update(const bool renotify)
        {
            #ifdef SHOW_NOP_LOGGER
                // std::cout << identation_control << "(*I) " << name << 
                //     " (" << this << ") called. Executing" << std::endl;

                // identation_control += "   ";
            #endif // SHOW_NOP_LOGGER
            this->method();

            #ifdef SHOW_NOP_LOGGER
                // identation_control.pop_back();
                // identation_control.pop_back();
                // identation_control.pop_back();
            #endif // SHOW_NOP_LOGGER
        }

        /**
         * Executa a Instigation
         * 
         * @param renotify 
         * @param status 
         */
        void Instigation::update(const bool renotify, const bool status)
        {
            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeInstigationExecuting(name , this);

                Utils::NOPLogger::Get().incrementIdentation();
            #endif // SHOW_NOP_LOGGER
            this->method();

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().decrementIdentation();
            #endif // SHOW_NOP_LOGGER
        }
    } // namespace Core
}