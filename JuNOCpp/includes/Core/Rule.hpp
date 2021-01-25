#ifndef JUNOCPP_RULE_HPP
#define JUNOCPP_RULE_HPP

#include "./Condition.hpp"
#include "./Action.hpp"

namespace JuNOCpp
{
    namespace Core
    {
        class NOPManager;
        class Rule: public Notifiable, public Notifier
        {
        friend class NOPManager;
        private:
            Condition* condition;
            Action* action;
            
            int id;
            bool is_approved;

        public:
            static int counter;
            static int approved;

        public:
            Rule(Utils::CustomString name = "UnnamedRule");
            ~Rule();

            Condition& getCondition() { return *condition; }
            Action& getAction() { return *action; }

            void update(const bool renotify = false);
            void update(const bool renotify, const bool status);
        };
    } // namespace Core
} // namespace JuNOCpp


#endif // !JUNOCPP_RULE_HPP
