#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <cctype>
#include <cerrno>

void ScalarConverter::convert(const std::string& literal) {
    if (literal.empty()) {
        std::cout << "Error: Empty string" << std::endl;
        return;
    }

    if (literal == "nan" || literal == "nanf" || 
        literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff" ||
        literal == "-inf" || literal == "-inff") {
        handleSpecialCases(literal);
        return;
    }

    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'') {
        convertFromChar(literal);
        return;
    }

    if (!literal.empty() && (literal[literal.length() - 1] == 'f' || literal[literal.length() - 1] == 'F')) {
        convertFromFloat(literal);
        return;
    }

    // Check for double
    if (literal.find('.') != std::string::npos) {
        convertFromDouble(literal);
        return;
    }

    convertFromInt(literal);
}

void ScalarConverter::handleSpecialCases(const std::string& literal) {
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    
    if (literal == "nan" || literal == "nanf") {
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
    } else if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff") {
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    } else if (literal == "-inf" || literal == "-inff") {
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
}

void ScalarConverter::convertFromChar(const std::string& literal) {
    char c = literal[1];
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void ScalarConverter::convertFromInt(const std::string& literal) {
    errno = 0;
    char* end;
    long longValue = std::strtol(literal.c_str(), &end, 10);
    
    if (*end != '\0' || errno == ERANGE || 
        longValue < std::numeric_limits<int>::min() || 
        longValue > std::numeric_limits<int>::max()) {
        std::cout << "Error: Invalid int literal" << std::endl;
        return;
    }
    
    int intValue = static_cast<int>(longValue);
    
    std::cout << "char: ";
    if (intValue < 0 || intValue > 127) {
        std::cout << "impossible";
    } else if (intValue >= 32 && intValue <= 126) {
        std::cout << "'" << static_cast<char>(intValue) << "'";
    } else {
        std::cout << "Non displayable";
    }
    std::cout << std::endl;
    
    std::cout << "int: " << intValue << std::endl;
    
    std::cout << "float: " << static_cast<float>(intValue) << ".0f" << std::endl;
    
    std::cout << "double: " << static_cast<double>(intValue) << ".0" << std::endl;
}

void ScalarConverter::convertFromFloat(const std::string& literal) {
    std::string cleanLiteral = literal;
    cleanLiteral = cleanLiteral.substr(0, cleanLiteral.length() - 1);
    
    errno = 0;
    char* end;
    float floatValue = std::strtof(cleanLiteral.c_str(), &end);
    
    if (*end != '\0' || (errno == ERANGE && !std::isinf(floatValue))) { //(errno == ERANGE && !std::isinf(floatValue) TEST : 1e-100f
        std::cout << "Error: Invalid float literal" << std::endl;
        return;
    }

    std::cout << "char: ";
    int intVal = static_cast<int>(floatValue);
    if (intVal < 0 || intVal > 127 || floatValue != static_cast<float>(intVal)) {
        std::cout << "impossible";
    } else if (intVal >= 32 && intVal <= 126) {
        std::cout << "'" << static_cast<char>(intVal) << "'";
    } else {
        std::cout << "Non displayable";
    }
    std::cout << std::endl;
    
    std::cout << "int: ";
    if (std::isnan(floatValue) || std::isinf(floatValue) || 
        floatValue < std::numeric_limits<int>::min() || 
        floatValue > std::numeric_limits<int>::max()) {
        std::cout << "impossible";
    } else {
        std::cout << static_cast<int>(floatValue);
    }
    std::cout << std::endl;
    
    std::cout << "float: ";
    if (std::isnan(floatValue)) {
        std::cout << "nanf";
    } else if (std::isinf(floatValue)) {
        std::cout << (floatValue > 0 ? "+inff" : "-inff");
    } else {
        std::cout << floatValue;
        if (std::floor(floatValue) == floatValue) {
            std::cout << ".0";
        }
        std::cout << "f";
    }
    std::cout << std::endl;
    
    std::cout << "double: ";
    double doubleValue = static_cast<double>(floatValue);
    if (std::isnan(doubleValue)) {
        std::cout << "nan";
    } else if (std::isinf(doubleValue)) {
        std::cout << (doubleValue > 0 ? "+inf" : "-inf");
    } else {
        std::cout << doubleValue;
        if (std::floor(doubleValue) == doubleValue) {
            std::cout << ".0";
        }
    }
    std::cout << std::endl;
}

void ScalarConverter::convertFromDouble(const std::string& literal) {
    errno = 0;
    char* end;
    double doubleValue = std::strtod(literal.c_str(), &end);
    
    if (*end != '\0' || (errno == ERANGE && !std::isinf(doubleValue))) {
        std::cout << "Error: Invalid double literal" << std::endl;
        return;
    }
    
    std::cout << "char: ";
    int intVal = static_cast<int>(doubleValue);
    if (intVal < 0 || intVal > 127 || doubleValue != static_cast<double>(intVal)) {
        std::cout << "impossible";
    } else if (intVal >= 32 && intVal <= 126) {
        std::cout << "'" << static_cast<char>(intVal) << "'";
    } else {
        std::cout << "Non displayable";
    }
    std::cout << std::endl;
    
    std::cout << "int: ";
    if (std::isnan(doubleValue) || std::isinf(doubleValue) || 
        doubleValue < std::numeric_limits<int>::min() || 
        doubleValue > std::numeric_limits<int>::max()) {
        std::cout << "impossible";
    } else {
        std::cout << static_cast<int>(doubleValue);
    }
    std::cout << std::endl;
    
    std::cout << "float: ";
    float floatValue = static_cast<float>(doubleValue);
    if (std::isnan(floatValue)) {
        std::cout << "nanf";
    } else if (std::isinf(floatValue)) {
        std::cout << (floatValue > 0 ? "+inff" : "-inff");
    } else {
        std::cout << floatValue;
        if (std::floor(floatValue) == floatValue) {
            std::cout << ".0";
        }
        std::cout << "f";
    }
    std::cout << std::endl;
    
    std::cout << "double: ";
    if (std::isnan(doubleValue)) {
        std::cout << "nan";
    } else if (std::isinf(doubleValue)) {
        std::cout << (doubleValue > 0 ? "+inf" : "-inf");
    } else {
        std::cout << doubleValue;
        if (std::floor(doubleValue) == doubleValue) {
            std::cout << ".0";
        }
    }
    std::cout << std::endl;
}