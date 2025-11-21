#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
    
    std::cout << std::endl;

    Data original(42, "Test Data", 3.14159);
    std::cout << "Original data: " << std::endl;
    original.display();
    
    std::cout << "Original pointer address: " << &original << std::endl;
    
    uintptr_t serialized = Serializer::serialize(&original);
    std::cout << "Serialized value (uintptr_t): " << serialized << std::endl;
    
    Data* deserialized = Serializer::deserialize(serialized);
    std::cout << "Deserialized pointer address: " << deserialized << std::endl;

    if (deserialized == &original) {
        std::cout << "✓ SUCCESS: Original and deserialized pointers are equal!" << std::endl;
    } else {
        std::cout << "✗ FAILURE: Pointers don't match!" << std::endl;
        return 1;
    }
    
    deserialized->display();

    return 0;
}