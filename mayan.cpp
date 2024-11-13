//
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

const char* ch = "\u2580";
const int SPACING = 4;
const int BASE = 20;
const int MAX_POWER_NUMBER = 7;
const int POSSIBLE_ANSWERS = 3;
const int MIN_POSSIBLE_GUESS = 10;

void printLineForSpace() {
    cout << "------" << endl;
}

void printMayanNumber(int num) {
    // print '00' if user number is 0
    if (num == 0) {
        cout << setw(SPACING) << "00" << endl;
        return;
    }
        // calculate amount of blocks and dots needed
        int blocks = num / 5;
        int dots = num % 5;

        // print 'o' for 1's
        for (int i = 0; i < dots; i++) {
            cout << "o";
        }

        cout << endl;

        // print block for 5's
        for (int i = 0; i < blocks; i++) {
            cout << ch << ch << ch << ch << endl;
        }
}

void printMayanValue(int num) {
    vector<int> mayanValues;
    bool NonZeroFound = false;

    // sort the Mayan values in base 20, going down to 20^0
    for (int i = MAX_POWER_NUMBER; i >= 0; i--) {
        int powerValue = static_cast<int>(pow(BASE,i));
        int mayanDigit = num / powerValue;

        // used A.I. to help stop my code to print extra '00' 
        if (mayanDigit != 0 || NonZeroFound) {
            mayanValues.push_back(mayanDigit);
            NonZeroFound = true;
        }
        num %= powerValue;
    }
    // used A.I. to help fix the issue if number is zero
    if (mayanValues.empty()) {
        mayanValues.push_back(0);
    }

    // print each mayan number from top to bottom
    for (unsigned int i = 0; i < mayanValues.size(); i++) {
        printMayanNumber(mayanValues.at(i));
        if (i < mayanValues.size() - 1) {
            // line for seperation between place values
            printLineForSpace();
        }
    }
}

void printStartingGameMessage() {
    // print headline
    cout << "MAYAN NUMBER GAME" << endl;
    cout << "=================" << endl;

    // print starting message
    cout << "You'll first enter a number between (>= 10) to be " << endl;
    cout << "the maximum number to guess. You'll then " << endl; 
    cout << "match a decimal number to it's mayan equivalent." << endl;

}

int enterGuess() 
{
    // ask user for max guess
    int userGuess = 0;
    cout << "Enter maximum to guess from (< 10 exits): " << endl;
    cin >> userGuess;

    // exit program if guess < 10
    if (userGuess < MIN_POSSIBLE_GUESS) {
        exit(EXIT_FAILURE);
    }
    return userGuess;
}

int randomNumberGenerator(int userGuess) {
    // get random number up to userGuess
    return rand() % userGuess + 1;
}

int randomInRange(int min, int max) {
    // return random number between 0.5 to 1.5 times the correctAnswer
    return rand() % (max - min + 1) + min;
}

void printCorrectOrIncorrectMessage(char userAnswer, int correctAnswer, int correctAnswerPosition) {
    // go through each possible answer (a,b,c) from user and print out correct/incorrect and the mayan value for the number
    if (userAnswer == 'a' && correctAnswerPosition == 0) {
        cout << "CORRECT! The mayan representation of " << correctAnswer << " is " << endl; 
        printMayanValue(correctAnswer);
    } else if (userAnswer == 'b' && correctAnswerPosition == 1) {
        cout << "CORRECT! The mayan representation of " << correctAnswer << " is " << endl; 
        printMayanValue(correctAnswer);
    } else if (userAnswer == 'c' && correctAnswerPosition == 2) {
        cout << "CORRECT! The mayan representation of " << correctAnswer << " is " << endl;  
        printMayanValue(correctAnswer);
    } else {
        cout << "INCORRECT! The mayan representation of " << correctAnswer << " is " << endl; 
        printMayanValue(correctAnswer);
    }
}
 
int main() 
{
    srand(time(0));
    printStartingGameMessage();

    // printMayanValue(12280);

    // loop mayan game, ends when userGuess < 10.
    for (;;) {
        int userGuess = enterGuess();

        // generate correct answer
        int correctAnswer = randomNumberGenerator(userGuess);

        // generate 2 wrong answers between boundaries
        int incorrectMin = static_cast<int>(correctAnswer * 0.5);
        int incorrectMax = static_cast<int>(correctAnswer * 1.5);

        // generate two random wrong answers
        int incorrectAnswer1 = randomInRange(incorrectMin, incorrectMax);
        int incorrectAnswer2 = randomInRange(incorrectMin, incorrectMax);

        // possible options a,b,c
        int a, b, c;

        // randomize correct postion 
        int correctAnswerPosition = rand() % POSSIBLE_ANSWERS;
        
        // randomly choose the possible orders for the correct answer
        if ( correctAnswerPosition == 0) {
            a = correctAnswer;
            b = incorrectAnswer1;
            c = incorrectAnswer2;
        } else if (correctAnswerPosition == 1) {
            a = incorrectAnswer2;
            b = correctAnswer;
            c = incorrectAnswer1;
        } else {
            a = incorrectAnswer1;
            b = incorrectAnswer2;
            c = correctAnswer;
        }

        // check if incorrectAnswer1 and 2 are not equal to c0rrect answer
        if (incorrectAnswer1 == correctAnswer) {
            // randomize again
            incorrectAnswer1 = randomInRange(incorrectMin, incorrectMax);
            // run loop again to make sure its not equal
            continue;
        }
        if (incorrectAnswer2 == correctAnswer) {
            incorrectAnswer2 = randomInRange(incorrectMin, incorrectMax);
            continue;
        }
        
        

        // ask user which is the answer
        cout << "Which of these mayan numbers is equal to " << correctAnswer << "?" << endl;

        // print possible answers
        cout << "a." << endl;
        printMayanValue(a);
        cout << "b." << endl;
        printMayanValue(b); 
        cout << "c." << endl;
        printMayanValue(c);

        // ask user to enter a,b,c
        cout << "Enter a, b, or c: ";
        char userAnswer;
        cin >> userAnswer;

        printCorrectOrIncorrectMessage(userAnswer, correctAnswer, correctAnswerPosition);

    }
    return 0;
}