#include <iostream>
#include <string>
#include <vector>

// for rand
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

string GetNumberString();
string Precheck(string);

int main() {
    srand(time(NULL));

    string choice;
    string input;

    cout << "Luhn Algorithm" << endl;

    do {
        cout <<
            "[1] Finish Card" << endl <<
            "[2] Generate Random Card" << endl <<
            "[3] Verify Existing Card" << endl <<
            "[0] Exit" << endl;
        getline(cin, choice);
    } while (choice != "1" && choice != "2" && choice != "3" && choice != "0");

    if (choice == "0")
        return 0; // Manual Exit
    else if (choice == "1") {
        input = GetNumberString();

        cout << endl <<
            "Finished Input:" << endl <<
            Precheck(input) << endl;
    }
    else if (choice == "2") {
        for (int i = 0; i < (rand() % 20) + 1; i++)
            input += to_string(rand() % 10);

        cout << endl <<
            "Random Input:" << endl <<
            input << endl << endl <<
            "Finished Input:" << endl <<
            Precheck(input) << endl;
    }
    else {
        input = GetNumberString();
        string check = input.substr(0, input.size() - 1);
        check = Precheck(check);

        if (input != check) {
            cout << endl <<
                "The card number is invalid" << endl;
        }
        else {
            cout << endl <<
                "The card number is valid" << endl;
        }
    }

    return 1; // Completed Exit
}

string Precheck(string input) {
    vector<int> digits;
    for (int i = 0; i < input.size(); i++)
        digits.push_back(input[i] - 48); // convert characters from ASCII to numbers by subtracting 48

    int check = 0;
    for (int i = digits.size() - 1; i >= 0; i--) // start from the end of the vector and move backwards
    {
        // this is true whenever the difference between the current index and the first is even, which is the same as every other digit
        if ((digits.size() - 1 - i) % 2 == 0) {
            digits[i] *= 2;
            if (digits[i] > 9)
                digits[i] -= 9;
            // subtracting 9 does the same thing as adding the digits for all two digit numbers
        }
        check += digits[i];
    }
    check = (check * 9) % 10; // apply the modifications to the sum to get the check digit

    string output = input + to_string(check); // append the check digit to the end of the input string
    return output;
}

string GetNumberString() {
    string input;
    bool valid;
    do {
        valid = true;
        cout << endl << "Enter a string of numbers: ";
        getline(cin, input);

        if (input.length() < 1) {
            cout << "Invalid input. Try again." << endl;
            valid = false;
            continue;
        }

        for (int i = 0; i < input.length() && valid; i++) {
            if (input[i] < 48 || input[i] > 57) {
                cout << "Invalid input. Try again." << endl;
                valid = false;
            }
        }
    } while (!valid); // if it makes it to the end, just exit the loop
    return input;
}
