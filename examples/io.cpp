/**
 * Esempio di I/O C++ style
 * Author:  ER
 * Date:    2022/112/11
 * Note:    
 */

// C++ style I/O
#include <iostream>
// for secure input
#include <limits>

// default namespace, to avoid std:: before, cin, cout, and so on
using namespace std;

const bool DEBUG = false; // true to enable DEBUG output

int main(int argc, char *args[])
{
    // constant message output to stdout (endl means newline)
    cout << "Welcome to C++ style I/O demo" << endl;
    // variable output to stdout
    int anInt = 42;
    const double PI = 3.1415926; // e così via...
    cout << "anInt = " << anInt << ", pi = " << PI << endl;
    // simple input from stdin
    cout << "Give me a number: ";
    cin >> anInt;
    cout << "You gave me " << anInt << endl;
    // combined input from stdin
    cout << "Give me two numbers: ";
    cin >> anInt >> anInt;
    cout << "You gave me " << anInt << " and another number that I forgot :-(" << endl;
    int anotherInt;
    cout << "Let's try again: give me two numbers: ";
    cin >> anInt >> anotherInt;
    cout << "You gave me " << anInt << " and " << anotherInt << endl;
    // secure input ...
    bool valid = false;
    cout << "Give me a number, but please try to deceive me ... " << endl;
    cout << "For example press Ctrl-D to get an infinite loop ... " << endl;
    do
    {
        cout << "Give me a number: ";
        cin >> anInt;
        if (cin.eof() || cin.bad())
        { // not really useful for keyboard input ...
            cout << "end of input or device error" << std::endl;
            break;
        }
        else if (cin.fail())
        {
            cout << "What? That is not a number!!!" << endl;
            cin.clear();                                         // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
        }
        else
        {
            valid = true; // here I can check if anInt is positive/negative/belongs to an interval...
        }
    } while (!valid);
    if (valid)
    {
        cout << "You gave me " << anInt << endl;
    }
    else
    {
        cout << "You gave me nothing... probably pressed Ctrl-D :-(" << endl;
    }

    // successful termination
    return 0;
}
