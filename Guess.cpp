#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>

using std::string;
using std::stoi;

// constant error message
string ERR_VALID_NUMBER = "Please enter a valid number.";
string ERR_VALID_ATTEMPTS = "Please enter a valid number for the amount of attempts you want to try.";

void printHigherLower(string highLow, int numGuessed) {
        std::cout << "The number is "<< highLow <<" than " << numGuessed << std::endl << std::endl;
}

void printConclusion(bool isCorrect, int numToGuess) {
    
    if (isCorrect)
    {
        std::cout << "You have guessed the number correctly!";
    }
    else
    {
        std::cout << "You have run out of attempts. The number was " << numToGuess;

    }
}

int userNumber(string errorMsg)
{
    // num validation
    bool isNotANumber = true;
    int numberInput = -1;
    while (isNotANumber)
    {
        std::string input;
        std::cin >> input;
        try
        {
            if (!input.empty())
            {
				// try to convert to int, exit out of loop if successful
				numberInput = stoi(input);
                isNotANumber = false;
            }
	
        }
        catch (const std::invalid_argument&)
        {
            // show arg error message 
			std::cout << errorMsg << std::endl;

        }

    }
    return numberInput;
}

int numberOfAttempts()
{
    std::cout << "How many attempts would you like to have?";
    return userNumber(ERR_VALID_ATTEMPTS);

}

bool guessLoop(int numAttempts, int numToGuess) {

    // intial vars
    int attempts = 0;
    bool isCorrect = false;

    // cycle will last the amount of attempts
    while (attempts < numAttempts)
    {
        std::cout<<"Enter your guess: ";
        int numGuessed = userNumber(ERR_VALID_NUMBER);
        std::cout<<"Checking to see if it is a valid "<<std::endl;

        if (numGuessed == numToGuess)
        {
			//exit the cycle if it is correct, set return value to true
            isCorrect = true;
            break;
        }
        else
        {
			// let the user know if the number is higher or lower
		    printHigherLower(numGuessed > numToGuess ? "lower" : "higher", numGuessed);
        }

        // increase attempts 
        attempts++;
    }
	return isCorrect;
}


// Main function
int notmain() {


    // number gen
    std::srand(std::time(0));
    int numToGuess = rand() % 101;

    // game start
    std::cout << "I'm thinking of a number between 1 and 100. Can you guess it?" << std::endl << std::endl;

    // user input 
    int numAttempts = numberOfAttempts();
    std::cout << "Starting game with " << numAttempts << " attempts" << std::endl;

	// returns if the user has guessed the number and prints result
    printConclusion(guessLoop(numAttempts, numToGuess), numToGuess);

    std::cout << std::endl << std::endl << "Press ENTER to exit";
    std::cin.ignore();
    std::cin.get();

    return 0;

}