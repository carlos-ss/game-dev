#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>

using std::string;
using std::stoi;

// constant error message
const string ERR_VALID_NUMBER_CALC = "Please enter a valid number.";
const string ERR_VALID_NUMBER_OPTION_CALC = "Please enter a valid number option.";

double userNumber(string errorMsg)
{
    // num validation
    bool isNotANumber = true;
    double numberInput = -1;
    while (isNotANumber)
    {
        std::string input;
        std::cin >> input;
        try
        {
            if (!input.empty())
            {
                // convert from string to double
                numberInput = stod(input);
                isNotANumber = false;
            }
        }
        catch (const std::invalid_argument&)
        {
            // handle error mesage 
            std::cout << errorMsg << std::endl;

        }

    }
    return numberInput;
}

int calcMenu() {
    // menu options 
    std::cout << "Please select an operation:"<< std::endl;
    std::cout << "1. Addition" << std::endl;
    std::cout << "2. Subtraction" << std::endl;
    std::cout << "3. Multiplication" << std::endl;
    std::cout << "4. Division" << std::endl;

    // will return the number selected by the user
	return userNumber(ERR_VALID_NUMBER_OPTION_CALC);
}

double add(double num1, double num2) {
	return num1 + num2;
}

double subtract(double num1, double num2) {
    return num1 - num2;
}

double multiply(double num1, double num2) {
	return num1 * num2;
}

double divide(double num1, double num2) {
	return num1 / num2;
}

void optionHandler(int option, double num1, double num2) {

    // should not return a value just print the result
	double result = 0;

    switch (option) {
        case 1:
            result = add(num1, num2);
            break;
        case 2:
            result = subtract(num1, num2);
            break;
        case 3:
            result = multiply(num1, num2);
            break;
        case 4:
            result = divide(num1, num2);
            break;
        default:
            break;

    }
    std::cout << "Result: " << result << std::endl;
}

// Main function
int notmainCalc() {

    while (true) {
        int option = calcMenu();

        double num1, num2;
        std::cout << "Enter first number: ";
        num1 = userNumber(ERR_VALID_NUMBER_CALC);
        std::cout << "Enter second number: ";
        num2 = userNumber(ERR_VALID_NUMBER_CALC);

		optionHandler(option, num1, num2);

		std::cout << "Do you want to continue? (y/n): ";
		std::string input;
		std::cin >> input;

        if (input != "y") {
            break;
        }
        else {
           std::cout << "\033[2J\033[1;1H";
        }
    }
  

    std::cout << std::endl << std::endl << "Press ENTER to exit";
    std::cin.ignore();
    std::cin.get();

    return 0;

}