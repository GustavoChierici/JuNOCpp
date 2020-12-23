#ifndef BASE_PREMISE_HPP
#define BASE_PREMISE_HPP

#include "Notifier.hpp"

namespace JuNOCpp
{
    class BasePremise: public Notifier, public Notifiable
    {
    public:
        bool impertinent;
    public:
        BasePremise(): impertinent(false) {}
        ~BasePremise() {}

        virtual void activate() = 0;
        virtual void deactivate() = 0;
    };
}
#endif // !BASE_PREMISE_HPP