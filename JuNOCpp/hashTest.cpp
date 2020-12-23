#include "./Table.hpp"
#include "./CustomString.hpp"
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>

int main()
{
  JuNOCpp::IntTable<std::string> test{10};

  srand(time(NULL));

  for (int i = 0; i < 100; ++i)
  {
    char c = 'a' + (rand() % 26);
    std::string *str = new std::string{c};
    test.insertValue(i, str);
    std::cout << c;
  }
  std::cout << "\n\n\n";
  for (int i = 0; i < 100; ++i)
  {
    std::cout << *test[i];
  }

  std::cout << test[102] << std::endl;
  
  std::cout.flush();
  return 0;
}