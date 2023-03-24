/**
 * Programma di esempio che calcola la media degli argomenti forniti
 * Author:  ER
 * Date:    2023/03/23
 * Note:    Il programma calcola la media aritmetica degli argomenti numerici
 *			Provare con: average 89 67 ciccia 7
 *          Viene visualizzato: The average of 89, 67, 6 is 54
 *			Notare che la conversione dei valori non è molto sicura
 */

#include <iostream>
#include <sstream>

using namespace std;

// argc: numero di elementi di argv (>= 1)
// argv: argc elementi (stringhe) con indice da 0 ad argc - 1
int main(int argc, char *argv[])
{

    double total = 0;
    int numValues = 0;
    for (int a = 1; a < argc; a++)
    {
        // convert the argument into a (floating point) number using
        // different methods (you should choose one of them)

        // 1° method: atof function
        // simple, but we cannot say if 0.0 is a real zero or nothing (ciccia)
        double value = atof(argv[a]);
        // cout << a << ": '" << argv[a] << "' = " << value << endl;
        // 2° method: sscanf function
        // also simple and return value tells us if there was a number (1) or not (0)
        double scanValue;
        int valid = sscanf(argv[a], "%lg", &scanValue);
        // cout << a << ": '" << argv[a] << "' = " << scanValue << " (" << valid << ")" << endl;
        // 3° method: istringstream object
        // also simple and fail() value tells us if there was a number (false) or not (true)
        double strValue;
        istringstream sinput(argv[a]); // input stream reading chars from argv[a]
        sinput >> strValue;
        // cout << a << ": '" << argv[a] << "' = " << strValue << " (" << input << " - " << sinput.gcount() << ")" << endl;
        if (!sinput.fail())
        {
            if(numValues == 0) {
                cout << "The average of ";
            } else {
                cout << ", ";
            }
            cout << strValue;
            total += strValue;
            numValues++;
        }
    }

    if (numValues > 0)
    {
        cout << " is " << total / numValues << endl;
    }
    else
    {
        cerr << "Usage: " << argv[0] << " value1 value2 ... valueN" << endl;
    }
    
    // termine con codice 0 = successo
    return 0;
}
