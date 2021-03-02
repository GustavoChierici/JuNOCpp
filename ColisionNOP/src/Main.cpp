#include "Main.h"

#ifdef _WIN32
#include <Windows.h>
#define sleep_func Sleep
#else
#include <unistd.h>
#define sleep_func(X) usleep(X*1000)
#endif

#include <chrono>


#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

Main::Main(unsigned int x, unsigned int y):
dimSalaX{x}, dimSalaY{y}, desenhador(x, y)
{
	initStartApplicationComponents();
}
Main::~Main(void) {
    if (bola) delete bola;
}
void Main::initStartApplicationComponents() {
    initFactBase();
	this->initRules();
    codeApplication();
}

void Main::initFactBase() {
    srand(time(NULL));
    int x = -dimSalaX + (5 % (2*dimSalaX + 1));
    int y = -dimSalaY + (5 % (2*dimSalaY + 1));
	bola = new Bola(x,y,1,1);
}

void Main::codeApplication() {
    long iterations = 0;

    cout << "Quantidade de Iteracoes: ";
    cin >> iterations;

    static_assert(NOPTraits::is_attribute_of_v<Core::Attribute<int>*, int>);

    auto start = std::chrono::system_clock::now();

    // bola->getAtMover()->setStatus(true);
    for (unsigned long long i = 0; i < iterations; ++i) {
        // desenhador.desenhar(bola->getX()->getCurrentStatus(), bola->getY()->getCurrentStatus());
        // sleep_func(100);
        bola->getAtMover()->setStatus(true, true);
        // bola->getAtMover()->setStatus(false);
    }
    // desenhador.desenhar(bola->getX()->getCurrentStatus(), bola->getY()->getCurrentStatus());

    auto finish = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);


    cout << "\n Tempo transcorrido: \n" << duration.count() << "ms\n";
    cout << "Aprovadas: " << Core::Rule::approved << endl;
}
void Main::initSharedEntities() {
}


void Main::initRules() {

    RULE(rlOne, *bola->getX() == -(int)dimSalaX or *bola->getX() == (int)dimSalaX);
        INSTIGATE([=](){ bola->mtInverterVX(); })
    END_RULE

    RULE(rlTwo, *bola->getY() == -(int)dimSalaY or *bola->getY() == (int)dimSalaY);
        INSTIGATE([=](){ bola->mtInverterVY(); })
    END_RULE

    RULE(rlThree, *bola->getAtMover() == true);
        INSTIGATE([=](){ bola->mtMover(); })
    END_RULE
}