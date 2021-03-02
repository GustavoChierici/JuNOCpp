#include "Main.h"

#include <iostream>
using namespace std;

int main()
{
    unsigned int dimSalaX, dimSalaY;
    cout << "dimensao da sala no eixo x:" << endl;
    cin >> dimSalaX;
    cout << "dimensao da sala no eixo y:" << endl;
    cin >> dimSalaY;
	Main main(dimSalaX, dimSalaY);
}