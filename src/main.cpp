#include "FunctionCalculator.h"

#include <iostream>

int main()
{
    try {
        FunctionCalculator(std::cin, std::cout).run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n'; return EXIT_FAILURE;
        
    }
     catch (...) {
         std::cerr << "Unknown exception\n"; return EXIT_FAILURE;
        
    }
}
