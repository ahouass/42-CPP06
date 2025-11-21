#include "Data.hpp"

Data::Data() : id(0), name("default"), value(0.0) {
    std::cout << "Data default constructor called" << std::endl;
}

Data::Data(int id, const std::string& name, double value) 
    : id(id), name(name), value(value) {
    std::cout << "Data parameterized constructor called" << std::endl;
}

Data::Data(const Data& copy) 
    : id(copy.id), name(copy.name), value(copy.value) {
    std::cout << "Data copy constructor called" << std::endl;
}

Data& Data::operator=(const Data& other) {
    std::cout << "Data assignment operator called" << std::endl;
    if (this != &other) {
        id = other.id;
        name = other.name;
        value = other.value;
    }
    return *this;
}

Data::~Data() {
    std::cout << "Data destructor called" << std::endl;
}

void Data::display() const {
    std::cout << "Data { id: " << id 
              << ", name: \"" << name 
              << "\", value: " << value 
              << " }" << std::endl;
}