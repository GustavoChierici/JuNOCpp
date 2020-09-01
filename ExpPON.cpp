#include "./JuNOCpp/JuNOC++.hpp"
#include "Apple.hpp"
#include "Archer.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include "ArcherPI.hpp"
#include "ApplePI.hpp"

int main()
{
    std::vector<Apple*> apple_list;

    for(int i = 0; i < 100; i++)
    {
        //Init Facts
        Archer* archer_tmp = new Archer();

        Apple* apple_tmp = new Apple();
        apple_list.push_back(apple_tmp);

        archer_tmp->atArcherStatus->setStatus(1);
        apple_tmp->atAppleStatus->setStatus(1);

        //Init Rules
        Rule* rlFireApple = new Rule(0);
        rlFireApple->addPremise(apple_tmp->atAppleColor, 1);
        rlFireApple->addPremise(apple_tmp->atAppleStatus, 1);
        rlFireApple->addPremise(archer_tmp->atArcherStatus, 1);
        rlFireApple->referenceAttr(apple_tmp->atAppleColor);

        archer_tmp->atArcherStatus->setStatus(1);
        apple_tmp->atAppleStatus->setStatus(1);
    }

    long iterations = 0;
    double start, finish;
    int percentage = 0;

    std::cout << "Quantidade de iteracoes: ";
    std::cin >> iterations;
    std::cout << "Porcentagem de macas vermelhas: ";
    std::cin >> percentage;

    start = clock();
    for(long i = 0; i < iterations; i++)
    {
        for(int j = 0; j < percentage; j++)
        {
            apple_list.at(j)->atAppleColor->setStatus(1);
        }
    }
    finish = clock();

    std::cout << "O tempo total do JuNOC++ foi de: " << finish - start << " ms"<< std::endl;

    apple_list.clear();

    std::vector<ArcherPI*> archerPI_list;
    std::vector<ApplePI*> applePI_list;
    for(int i = 0; i < 100; i++)
    {
        ArcherPI* archerPI_tmp = new ArcherPI();
        archerPI_tmp->status = true;
        archerPI_list.push_back(archerPI_tmp);

        ApplePI* applePI_tmp = new ApplePI();
        applePI_tmp->status = true;
        applePI_tmp->color = false;
        applePI_list.push_back(applePI_tmp);
    }

    start = clock();
    for(long i = 0; i < iterations; i++)
    {
        for(int j = 0; j < percentage; j++)
        {
            applePI_list.at(j)->color = true;
        }

        for(int k = 0; k < 100; k++)
        {
            if((archerPI_list.at(k)->status) &&
               (applePI_list.at(k)->status) &&
               (applePI_list.at(k)->color))
            {
                applePI_list.at(k)->color = false;
            }
        }
    }
    finish = clock();

    std::cout << "O tempo total do PI foi de: " << finish - start << " ms"<< std::endl;


    return 0;
}
