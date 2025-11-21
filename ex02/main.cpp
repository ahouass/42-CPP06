#include "Identify.hpp"
#include <iostream>

int main() {

    std::srand(std::time(0));
    std::cout << std::endl;
    
    for (int i = 0; i < 5; ++i) {
        std::cout << "--- Test " << (i + 1) << " ---" << std::endl;
        
        Base* obj = generate();
        
        std::cout << "Identify by pointer: ";
        identify(obj);
        
        std::cout << "Identify by reference: ";
        identify(*obj);
        
        std::cout << std::endl;
        
        delete obj;
    }
    
    std::cout << std::endl;
    
    return 0;
}