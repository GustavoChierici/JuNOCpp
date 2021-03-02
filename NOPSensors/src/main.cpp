#include "Sensor.hpp"
#include <iostream>
#include <chrono>
#include <vector>

int main()
{
    auto start = std::chrono::system_clock::now();
    std::vector<Sensor*> sensors;

    for(int i = 0; i < 10000; i++)
    {
        sensors.push_back(new Sensor());
    }

    auto middle = std::chrono::system_clock::now();
    auto construction = std::chrono::duration_cast<std::chrono::milliseconds>(middle - start);

    std::cout << "O tempo de construção do JuNOC++ foi: " << construction.count() << "ms" << std::endl;

    for(int j = 0; j < 10000; j++)
    {
        for(int i = 0; i < 1000; i++)
        {
            sensors[i]->activate();
        }
        if(Sensor::counter != 1000) exit(1);
        Sensor::counter = 0;
    }

    auto finish = std::chrono::system_clock::now();
    auto execution = std::chrono::duration_cast<std::chrono::milliseconds>(finish - middle);
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    std::cout << "O tempo de execução do JuNOC++ foi: " << execution.count() << "ms" << std::endl;
    std::cout << "O tempo total do JuNOC++ foi: " << duration.count() << "ms" << std::endl;

    return 0;
}