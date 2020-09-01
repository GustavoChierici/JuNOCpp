#pragma once
#include "./Attributes/Attribute.hpp"
#include <vector>
#include <iostream>
namespace JuNOCpp
{
    class FBE
    {
    private:
        std::vector<Attributes::Attribute*> attributes;
    public:
        FBE() {}
        ~FBE() {}

        void insertAttribute(Attributes::Attribute* attr)
        {
            attributes.push_back(attr);
        }
    };
}

