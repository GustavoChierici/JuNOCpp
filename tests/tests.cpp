#include "JuNOC++.hpp"
#include "catch.hpp"
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <string>

TEST_CASE("Attribute can be of type int", "[Attribute]")
{
    NOP::Attribute<int> at1{123456};

    REQUIRE(at1.getValue() == 123456);
}

TEST_CASE("Attribute can be of type bool", "[Attribute]")
{
    NOP::Attribute<bool> at1{true};

    REQUIRE(at1.getValue() == true);
}

TEST_CASE("Attribute can be of a custom type", "[Attribute]")
{
    class Rectangle {
        int width, height;
    public:
        Rectangle(int w, int h) : width{ w }, height{ h } {};;
        inline bool operator== (Rectangle i) const
        {
            return (width == i.width) && (height == i.height);
        }
        inline bool operator!= (Rectangle i) const
        {
            return (width != i.width) || (height != i.height);
        }
    };

    const Rectangle val1{1, 2};
    NOP::Attribute<Rectangle> at1{val1};
    REQUIRE(at1.getValue() == val1);

    const Rectangle val2{3, 4};
    NOP::Attribute<Rectangle> at2{val2};
    REQUIRE_FALSE(at1.getValue() == at2.getValue());

    at2.setValue(val1);
    REQUIRE(at1.getValue() == at2.getValue());
}

TEST_CASE("Attribute can be of type string", "[Attribute]")
{
    const std::string val{"test"};
    NOP::Attribute<std::string> at1{val};

    REQUIRE(at1.getValue() == val);
}

SCENARIO("Premises can be a comparison between an Attribute and a const value", "[Premise]")
{

    GIVEN("An Attribute and a constant value")
    {
        const int val{1234};
        NOP::Attribute<int> at{val};

        WHEN("The Premise is a equality between this Attribute and the same constant value")
        {
            auto& pr = at == 1234;

            THEN("The Premise should be approved")
                REQUIRE(pr.getCurrentStatus() == true);
        }

        WHEN("The Premise is a equality between this Attribute and another constant value")
        {
            auto& pr = at == 1245;

            THEN("The Premise should not be approved")
                REQUIRE(pr.getCurrentStatus() == false);

            AND_WHEN("The Attribute change its value to the Premise's rhs value")
            {
                at = 1245;

                THEN("The Attribute should notify the Premise and the Premise should now be approved")
                    REQUIRE(pr.getCurrentStatus() == true);
            }
        }
    }
}

SCENARIO("Premises can be a comparison between Attributes", "[Premise]")
{
    GIVEN("Two Attributes that holds different values")
    {
        const int val1{1234}, val2{1245};
        NOP::Attribute<int> at1{val1};
        NOP::Attribute<int> at2{val2};

        WHEN("The Premise is a equalitiy between these two Attributes")
        {
           auto& pr = at1 == at2;

            THEN("The Premise should not be approved")
                REQUIRE(pr.getCurrentStatus() == false);
            
            AND_WHEN("The second Attribute change its value to a third value")
            {
                at2 = 5;

                THEN("The second Attribute should notify the Premise, but the Premise should not be approved")
                    REQUIRE(pr.getCurrentStatus() == false);
            }

            AND_WHEN("The second Attribute change its value to the value of the first Attribute")
            {
                at2 = val1;

                THEN("The second Attribute should notify the Premise and the Premise should now be approved")
                    REQUIRE(pr.getCurrentStatus() == true);
            }
        }
    }
}

SCENARIO("Premises can be a comparison between an Attribute and an expression", "[Premise]")
{
    GIVEN("Two Attributes that holds different values and an expression compound by the second Attribute")
    {
        const int val1{3}, val2{5};
        NOP::Attribute<int> at1{val1};
        NOP::Attribute<int> at2{val2};
        auto expr = ((at2 * 3) + 2);

        WHEN("The Premise is a equality beetwen the first Attribute and the expression")
        {
           auto& pr = at1 == expr;

            THEN("The Premise should not be approved")
                REQUIRE(pr.getCurrentStatus() == false);

            AND_WHEN("The first Attribute change its value to the current result of the expression")
            {
                at1 = Utils::NOPTraits::eval(expr.tup);

                THEN("The first Attribute should notify the Premise and the Premise should now be approved")
                    REQUIRE(pr.getCurrentStatus() == true);
            }
        }
    }
}

SCENARIO("Conditions can be a logical expression between Premises", "[Condition]")
{
    GIVEN("Two Attributes, two constant values and two Premises comparing the Attributes with the values")
    {
        const int val1{3}, val2{5};
        NOP::Attribute<int> at1{val1};
        NOP::Attribute<int> at2{val2};
        auto& pr1 = at1 == 5;
        auto& pr2 = at2 >= 10;

        WHEN("The Condition is a conjunction between these two Premises")
        {
            auto& cd = pr1 and pr2;

            AND_WHEN("None of the Premises is approved")
                THEN("Condition is not approved")
                    REQUIRE_FALSE(cd.getCurrentStatus() == true);

            AND_WHEN("One of the Premises is not approved")
            {
                at1 = 5;
                THEN("Condition is not approved")
                    REQUIRE_FALSE(cd.getCurrentStatus() == true);
            }

            AND_WHEN("Both Premises is approved")
            {
                at1 = 5;
                at2 = 15;
                THEN("Condition is approved")
                    REQUIRE(cd.getCurrentStatus() == true);
            }
        }

        WHEN("The Condition is a disjunction between these two Premises")
        {
            auto& cd = pr1 or pr2;

            AND_WHEN("None of the Premises is approved")
                THEN("Condition is not approved")
                    REQUIRE_FALSE(cd.getCurrentStatus() == true);

            AND_WHEN("One of the Premises is not approved")
            {
                at1 = 5;
                THEN("Condition is approved")
                    REQUIRE(cd.getCurrentStatus() == true);
            }

            AND_WHEN("Both Premises is approved")
            {
                at1 = 5;
                at2 = 15;
                THEN("Condition is approved")
                    REQUIRE(cd.getCurrentStatus() == true);
            }
        }      
    }
}


SCENARIO("Conditions can be a logical expression between Premise and Conds", "[Condition]")
{
    GIVEN("One Premises and one Condition")
    {
        const int val1{3};
        NOP::Attribute<int> at1{val1};
        NOP::Attribute<bool> at2{false};
        NOP::Attribute<bool> at3{true};
        auto& pr1 = at1 == 5;

        auto& cd1 = at2 == true or at3 == false;

        WHEN("The Condition is a conjunction between the Premises and the Condition")
        {
            auto& cd2 = pr1 and cd1;

            AND_WHEN("Neither the Premises or the first Condition is approved")
                THEN("Condition is not approved")
                    REQUIRE_FALSE(cd2.getCurrentStatus() == true);

            AND_WHEN("The first Condition is not approved")
            {
                at1 = 5;
                THEN("Condition is not approved")
                    REQUIRE_FALSE(cd2.getCurrentStatus() == true);
            }

            AND_WHEN("The Premise is not approved")
            {
                at2 = true;
                THEN("Condition is not approved")
                    REQUIRE_FALSE(cd2.getCurrentStatus() == true);
            }

            AND_WHEN("The Premise and the first Condition is approved")
            {
                at1 = 5;
                at2 = true;
                THEN("Condition is approved")
                    REQUIRE(cd2.getCurrentStatus() == true);
            }
        }

        WHEN("The Condition is a disjunction between the Premise and the first Condition")
        {
            auto& cd2 = pr1 or cd1;

            AND_WHEN("Neither the Premises or the first Condition is approved")
                THEN("Condition is not approved")
                    REQUIRE_FALSE(cd2.getCurrentStatus() == true);

            AND_WHEN("The first Condition is not approved")
            {
                at1 = 5;
                THEN("Condition is approved")
                    REQUIRE(cd2.getCurrentStatus() == true);
            }

            AND_WHEN("The Premise is not approved")
            {
                at2 = true;
                THEN("Condition is approved")
                    REQUIRE(cd2.getCurrentStatus() == true);
            }

            AND_WHEN("The Premise and the first Condition is approved")
            {
                at1 = 5;
                at2 = true;
                THEN("Condition is approved")
                    REQUIRE(cd2.getCurrentStatus() == true);

                AND_WHEN("The Premise disapproves")
                {
                    at1 = 3;
                    THEN("Condition should remain approved")
                        REQUIRE(cd2.getCurrentStatus() == true);

                    AND_WHEN("The first Condition also disapproves")
                    {
                        at2 = false;
                        THEN("Condition now should be disapproved")
                            REQUIRE_FALSE(cd2.getCurrentStatus() == true);
                    }
                }
            }
        }      
    }
}

SCENARIO("Premises can be impertinents", "[Premise][Impertinent]")
{
    GIVEN("Two unapproved Premises, one common and one impertinent")
    {
        NOP::Attribute<int> at1{3};
        NOP::Attribute<bool> at2{false};
        auto& pr1 = at1 == 5;
        auto& prImp = IMPERTINENT((at2 == true));

        WHEN("A Condition is a conjunction between the two premises")
        {
            auto& cd = pr1 and prImp;
            
            AND_WHEN("The Attribute of the impertinent Premise changes")
            {
                at2 = true;
                THEN("The impertinent Premise remains unapproved")
                    REQUIRE_FALSE(prImp.getCurrentStatus() == true);

                AND_WHEN("The common Premise approves")
                {
                    at1 = 5;

                    THEN("The impertinent Premise and the Condition should now be approved")
                    {
                        REQUIRE(prImp.getCurrentStatus() == true);
                        REQUIRE(cd.getCurrentStatus() == true);

                        AND_WHEN("The common Premise disapproves")
                        {
                            at1 = 7;

                            THEN("The Condition and the impertinent Premise should be disapproved")
                            {
                                //REQUIRE_FALSE(prImp.getCurrentStatus() == true);
                                REQUIRE_FALSE(cd.getCurrentStatus() == true);
                            }
                        }
                    }
                }
            }
            
        }
    }
}

SCENARIO("Rules can be constructed with previous declared NOP expressions", "[Rule]")
{
    GIVEN("A unapproved condition")
    {
        NOP::Attribute<int> at1{5};
        NOP::Attribute<bool> at2{false};
        auto& cd = (at1 > 7 and at2 == true);

        WHEN("An anonymous Rule is constructed with the condition")
        {
            RULE(cd)
            END_RULE

            THEN("The Rule should not be approved")
                REQUIRE(NOP::Rule::approved == 0);

            AND_WHEN("The condition is approved")
            {
                at1 = 8;
                at2 = true;

                THEN("The Rule should be approved")
                {
                    REQUIRE(NOP::Rule::approved == 1);
                    NOP::Rule::approved = 0;
                }
            }
        }

        WHEN("A declared Rule is constructed with the condition")
        {
            NOP::Rule rlDecl{"rlDecl"};
            RULE(rlDecl, cd)
            END_RULE

            THEN("The Rule should not be approved")
                REQUIRE_FALSE(rlDecl.is_approved);

            AND_WHEN("The condition is approved")
            {
                at1 = 8;
                at2 = true;

                THEN("The Rule should be approved")
                {
                    REQUIRE(rlDecl.is_approved);
                    NOP::Rule::approved = 0;

                    AND_WHEN("The condition is disapproved")
                    {
                        at1 = 0;

                        THEN("The Rule should be disapproved")
                            REQUIRE_FALSE(rlDecl.is_approved);
                    }
                }
            }
        }
    }
}

SCENARIO("Rules can be constructed directly with the NOP expression itself", "[Rule]")
{
    GIVEN("Some Attributes and Premises")
    {
        NOP::Attribute<int> at1{5};
        NOP::Attribute<int> at2{7};
        NOP::Attribute<bool> at3{true};
        NOP::Attribute<double> at4{-5.2};
        auto& pr = at4 >= -3.113;

        WHEN("An anonymous Rule is constructed with an unapproved NOP expression made by these NOP entities")
        {
            RULE(at1 == at2 and at3 == true or pr)
            END_RULE
            
            THEN("The Rule should not be approved")
                REQUIRE(NOP::Rule::approved == 0);

            AND_WHEN("The NOP expression (Rule's condition) is approved")
            {
                at4 = 11.18;

                THEN("The Rule should be approved")
                {
                    REQUIRE(NOP::Rule::approved == 1);
                    NOP::Rule::approved = 0;
                }
            }
        }

        WHEN("A declared Rule is constructed with an unapproved NOP expression made by these NOP entities")
        {
            NOP::Rule rlDecl{"rlDecl"};
            RULE(rlDecl, (at1 == at2 and at3 == true or pr))
            END_RULE

            THEN("The Rule should not be approved")
                REQUIRE_FALSE(rlDecl.is_approved);

            AND_WHEN("The condition is approved")
            {
                at4 = 11.18;

                THEN("The Rule should be approved")
                {
                    REQUIRE(rlDecl.is_approved);
                    NOP::Rule::approved = 0;

                    AND_WHEN("The condition is disapproved")
                    {
                        at4 = -9.0003;

                        THEN("The Rule should be disapproved")
                            REQUIRE_FALSE(rlDecl.is_approved);
                    }
                }
            }
        }
    }
}

TEST_CASE("Loop Rule", "[Complete]")
{
    NOP::Attribute<int> at_counter{0};

    RULE(at_counter < 10)
        INSTIGATE([&](){
            ++at_counter;
        })
    END_RULE

    REQUIRE(at_counter.getValue() == 10);
}

long long int factorial(long long int n)
{
    return n == 0 ? 1 : n * factorial(n - 1);
}

long long int iterative_fact(long long int n)
{
    for(long long int i = n - 1; i > 0; --i)
        n *= i;

    return n;
}

TEST_CASE("Factorial Rule", "[Complete]")
{
    BENCHMARK("NOP Factorial")
    {
        NOP::Attribute<long long int> at_entry{-1};
        NOP::Attribute<long long int> at_result{1};

        RULE(at_entry > 0)
            INSTIGATE([&]{
                at_result.setValue<NOP::NoNotify>(at_result.getValue() * (at_entry.getValue()));
                --at_entry;
            })
        END_RULE

        at_entry = 1000;

        // REQUIRE(at_result.getValue() == factorial(1000));
    };

    BENCHMARK("Interative Factorial")
    {
        return iterative_fact(1000);
    };

    BENCHMARK("Recursive Factorial")
    {
        return factorial(1000);
    };
}

template<typename T>
struct NOPList
{
    NOP::Attribute<T> hd;
    NOP::Attribute<NOPList<T>*> tl;
    NOP::Attribute<T*> to_push;

    NOPList():
    tl{nullptr},
    to_push{nullptr}
    {
        RULE(this->to_push != nullptr and this->tl == nullptr)
        INSTIGATE([this](){
            this->hd = *this->to_push.getValue();
            delete this->to_push.getValue();
            this->to_push = nullptr;
            this->tl = new NOPList<T>();
        })
        END_RULE

        RULE(this->to_push != nullptr and this->tl != nullptr)
        INSTIGATE([this](){
            this->tl.getValue()->push(*this->to_push.getValue());
            delete this->to_push.getValue();
            this->to_push = nullptr;
        })
        END_RULE

    }

    void push(T element)
    {
        this->to_push = new int(element);
    }
};

TEST_CASE("NOPList", "[DataStructures]")
{
    auto list = new NOPList<int>;

    list->push(5);
    list->push(6);
    list->push(52);
    list->push(-47);

    // auto aux = list;

    // NOP::Attribute<NOPList<int>*> aux{list};

    // while(aux != nullptr)
    // {
    //     std::cout << aux->hd.getValue() << "-" << aux << std::endl;
    //     aux = aux->tl.getValue();
    // }

    // RULE(aux != nullptr)
    //     INSTIGATE([&](){
    //         std::cout << aux.getValue()->hd.getValue() << std::endl;
    //         aux.setValue<NOP::ReNotify>(aux.getValue()->tl.getValue());
    //     })
    // END_RULE

    REQUIRE(list->hd.getValue() == 5);
    REQUIRE(list->tl.getValue()->tl.getValue()->hd.getValue() == 52);

}