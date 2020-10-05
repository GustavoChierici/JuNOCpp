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

        //Init Rules
        Rule* rlFireApple = new Rule("CONJUNCTION", Rule::COMPLETE);
        rlFireApple->addPremise(apple_tmp->atAppleStatus, true);
        rlFireApple->addPremise(archer_tmp->atArcherStatus, true);
        rlFireApple->addPremise(apple_tmp->atAppleColor, 'R');
        //rlFireApple->referenceAttr(apple_tmp->atAppleColor, 'G');
        rlFireApple->addInstigation(apple_tmp->atAppleColor, 'G');

        archer_tmp->atArcherStatus->setStatus(true);
        apple_tmp->atAppleStatus->setStatus(true);
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
            apple_list.at(j)->atAppleColor->setStatus('R');
        }
    }
    finish = clock();

    std::cout << "O tempo total do JuNOC++ foi de: " << finish - start << " ms - Regras aprovadas: " << Rule::counter << std::endl;

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
        applePI_tmp->color = 'G';
        applePI_list.push_back(applePI_tmp);
    }

    long int counter = 0;
    start = clock();
    for(long i = 0; i < iterations; i++)
    {
        for(int j = 0; j < percentage; j++)
        {
            applePI_list.at(j)->color = 'R';
        }

        for(int k = 0; k < 100; k++)
        {
            if((archerPI_list.at(k)->status) &&
               (applePI_list.at(k)->status) &&
               (applePI_list.at(k)->color == 'R'))
            {
                applePI_list.at(k)->color = 'G';
                counter++;
                //std::cout << "AP" << std::endl;
            }
        }
    }
    finish = clock();

    std::cout << "O tempo total do PI foi de: " << finish - start << " ms - Regras aprovadas: " << counter << std::endl;


    return 0;
}
