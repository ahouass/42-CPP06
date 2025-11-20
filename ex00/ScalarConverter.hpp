#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter& operator=(const ScalarConverter& other);
		~ScalarConverter();

		static void convertFromChar(const std::string& literal);
		static void convertFromInt(const std::string& literal);
		static void convertFromFloat(const std::string& literal);
		static void convertFromDouble(const std::string& literal);
		static void handleSpecialCases(const std::string& literal);

	public:
		static void convert(const std::string& literal);
};

#endif