#ifndef JUNOCPP_ACTION_HPP
#define JUNOCPP_ACTION_HPP

#include "Instigation.hpp"
#include "NOPManager.hpp"
#include "Notifier.hpp"
#include "Condition.hpp"

namespace JuNOCpp
{
    namespace Core
    {
        class Rule;
        class Action: public Notifier, public Notifiable
        {
        public:
            Rule* rule;
            Utils::forward_list<Condition*> dependant_rules;

        public:
            Action(Utils::CustomString name = "UnnamedAction");
            ~Action();
            
            void setRule(Rule* b_rule);

            void update(const bool renotify = false);
            void update(const bool renotify, const bool status) {}
            void notify(const bool renotify = false);
        };
    } // namespace Core

}
#endif // !JUNOCPP_ACTION_HPP