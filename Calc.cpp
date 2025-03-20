#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>

using std::string;
using std::stoi;

string ERR_VALID_NUMBER_CALC = "Please enter a valid number.";
string ERR_VALID_NUMBER_OPTION_CALC = "Please enter a valid number option.";

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
                numberInput = stod(input);
                break;
            }
        }
        catch (const std::invalid_argument&)
        {
            std::cout << errorMsg << std::endl;

        }

    }
    return numberInput;
}

int calcMenu() {
    std::cout << "Please select an operation:"<< std::endl;
    std::cout << "1. Addition" << std::endl;
    std::cout << "2. Subtraction" << std::endl;
    std::cout << "3. Multiplication" << std::endl;
    std::cout << "4. Division" << std::endl;

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

// Main function
int main() {

    while (true) {
        int option = calcMenu();

        double num1, num2, result = 0;
        std::cout << "Enter first number: ";
        num1 = userNumber(ERR_VALID_NUMBER_CALC);
        std::cout << "Enter second number: ";
        num2 = userNumber(ERR_VALID_NUMBER_CALC);


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