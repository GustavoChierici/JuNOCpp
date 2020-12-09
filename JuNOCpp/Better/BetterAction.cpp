#include "./BetterAction.hpp"

namespace JuNOCpp
{   
    BetterAction::BetterAction()
    {
        this->rule = nullptr;
    }

    BetterAction::~BetterAction()
    {
    }

    void BetterAction::setBetterRule(BetterRule* b_rule)
    {
        this->rule = b_rule;
    }

    void BetterAction::update(const bool renotify)
    {
        notify();
    }
} // namespace JuNOCpp
