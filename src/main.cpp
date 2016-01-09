#include <iostream>
#include "config.h"

int main()
{
  std::cout
    << "yml v"
    << YML_VERSION_MAJOR << "." 
    << YML_VERSION_MINOR << "."
    << YML_VERSION_PATCH
    << std::endl;
}

