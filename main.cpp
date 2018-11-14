/*
 
 PROBLEM: You have a number pad of 10 numbers, numbered 0-9. Write a function in
 any programming language that you’d like to find the 4-digit PIN that unlocks
 the number pad in a brute-force fashion.
 
 SOLUTION: The code below consists of two Keypad classes: one that follows the
 assumption that the keypad does not react until all 4 digits are put in, and
 another that assumes that the keypad reacts if the first digit is right, then
 the second, etc. The first method tests every 4-digit combination from 0000 to
 9999 until it finds it, where the program then breaks out. The second method,
 which is faster than the first, tests the first digit until it gets it right,
 then the second digit, and so on until every digit is matched with the
 passcode.
    The program takes in the passcode value from the user to initially set the
 passcode, and then the type for the keypad (0 being the former type, and 1
 being the latter in the above paragraph). After processing, it outputs the
 correct passcode.
 
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int NUM_DIGITS = 9;

//Keypad of type 0
class Keypad {
    
    int passcode;
    bool unlocked;
    
public:
    
    //Default constructor
    Keypad()
    : passcode(0), unlocked(false) {}
    
    //Custom constructor that takes in passcode input from user
    Keypad(string _passcode)
    : unlocked(false) {
        passcode = stoi(_passcode);
    }
    
    //REQUIRES: 'guess' made by the program
    //MODIFIES: If guess matches passcode, member variable unlocked = true
    //EFFECTS: Returns true if the guess matches passcode and unlocks keypad
    bool submit(int guess) {
        if (guess == passcode) unlocked = true;
        return guess == passcode;
    }
    
    //EFFECTS: Returns correct passcode guess
    string finalCode(int answer) {
        string output = to_string(answer);
        while (output.length() < NUM_DIGITS) output.insert(0, "0");
        return output;
    }
    
};

//Keypad of type 1
class EasyKeypad {
    
    vector<int> digits;
    vector<int> passcode;
    bool unlocked;
    
public:
    
    //Default constructor
    EasyKeypad()
    : unlocked(false) {
        passcode.reserve(NUM_DIGITS);
        digits.reserve(NUM_DIGITS);
        for (int i = 0; i < NUM_DIGITS; ++i) {
            passcode.push_back(0);
        }
    }
    
    //Custom constructor that takes in passcode input from user
    EasyKeypad(int _passcode)
    : unlocked(false) {
        passcode.reserve(NUM_DIGITS);
        digits.reserve(NUM_DIGITS);
        int divisor = pow(10, NUM_DIGITS - 1);
        for (int i = 0; i < NUM_DIGITS; ++i) {
            int temp = _passcode % divisor;
            passcode.push_back(_passcode / divisor);
            divisor /= 10;
            _passcode = temp;
        }
    }
    
    int checkDigit(int guess, int digit) {
        if (digits.size() == NUM_DIGITS - 1 && guess == passcode[digit]) {
            digits.push_back(guess);
            unlocked = true;
            return 2;
        } else if (guess == passcode[digit]) {
            digits.push_back(guess);
            return 1;
        } else {
            return 0;
        }
    }
    
    //EFFECTS: Returns correct passcode guess
    string finalCode() {
        string output = "";
        for (int i = 0; i < digits.size(); ++i) output += to_string(digits[i]);
        return output;
    }
    
};

//REQUIRES: Keypad instance
//EFFECTS: Breaks into keypad type 0 and outputs result into commandline output
void bruteForce0(Keypad &keypad) {
    for (int i = 0; i < pow(10, NUM_DIGITS); ++i)
        if (keypad.submit(i)) {
            cout << "PASSCODE IS: " << keypad.finalCode(i) << "\n";
            cout << "KEYPAD UNLOCKED. BASK IN YOUR WEALTH.\n\n";
            break;
        }
}

//REQUIRES: Keypad instance
//EFFECTS: Breaks into keypad type 1 and outputs result into commandline output
void bruteForce1(EasyKeypad &keypad) {
    for (int i = 0; i < NUM_DIGITS; ++i) {
        for (int j = 0; j < 10; ++j) {
            int tracker = keypad.checkDigit(j, i);
            if (tracker == 2) {
                cout << "PASSCODE IS: " << keypad.finalCode() << "\n";
                cout << "KEYPAD UNLOCKED. BASK IN YOUR WEALTH.\n";
                return;
            }
            if (tracker == 1) break;
        }
    }
}

int main(int argc, const char * argv[]) {
    
    string passcodeIn;
    int fastKey = 0;
    
    cout << "Please set " << NUM_DIGITS << "-digit passcode for keypad: ";
    cin >> passcodeIn;
    cout << "\n";
    
    while (passcodeIn.length() != NUM_DIGITS || stoi(passcodeIn) < 0) {
        cout << "Invalid passcode format please use another passcode.\n\n";
        cout << "Please set " << NUM_DIGITS << "-digit passcode for keypad: ";
        cin >> passcodeIn;
        cout << "\n";
    }
    
    cout << "\n\nEnter type of lock:\n1: Keypad that only checks guess upon "
    << "submitting all " << NUM_DIGITS << " digits (enter '0')\n2: Checks answer "
    << "digit by digit as it goes (enter '1')\n\nENTER TYPE: ";
    cin >> fastKey;
    
    while (fastKey < 0 || fastKey > 1) {
        cout << "Invalid type format please try again.\n\n";
        cout << "\n\nEnter type of lock:\n1: Keypad that only checks guess upon "
        << "submitting all " << NUM_DIGITS << " digits (enter '0')\n2: Checks answer "
        << "digit by digit as it goes (enter '1')\n\nENTER TYPE: ";
        cin >> fastKey;
    }
    
    cout << "\n\n";
    
    if (!fastKey) {
        Keypad keypad(passcodeIn);
        bruteForce0(keypad);
    } else {
        EasyKeypad keypad(stoi(passcodeIn));
        bruteForce1(keypad);
    }
    
    return 0;
}
