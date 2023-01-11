/*
 * Andamento sequenza numerica
 * Author:  ER
 * Date:    2022/10/28
 * Note:
 */

/*
2. Andamento sequenze (andamento)
Una sequenza di numeri interi si dice:
    • PIATTA, se tutti i valori sono uguali;
    • CRESCENTE, se non è PIATTA e se ciascun valore è maggiore o uguale al precedente;
    • DECRESCENTE, se non è PIATTA e se ciascun valore è minore o uguale al precedente;
    • ALTERNANTE negli altri casi.
Si vuole determinare la categoria cui appartiene una sequenza di numeri interi non nulli, terminata da un valore 0 (zero), immessa dall’utente.
Assunzione: 1 <= lunghezza sequenza <= 108, -109 <= valore <= 109.
Formato di input: leggere da tastiera la sequenza di numeri interi non nulli, terminata dal valore 0 (zero).
Formato di output: I caratteri P, C, D oppure A, a seconda che la sequenza sia PIATTA, CRESCENTE, DECRESCENTE oppure ALTERNANTE.



Esempi:
| Input                 | Output    | Note                      |
| --------------------- | --------- | ------------------------- |
| 1 2 1 5 7 3 9 4 6 0   | A         | La sequenza è ALTERNANTE  |
| 1 2 3 4 5 6 7 8 8 0   | C         | La sequenza è CRESCENTE   |
| 1 0                   | P         | La sequenza è PIATTA      |
| 2 2 1 0               | D         | La sequenza è DECRESCENTE |
*/

#include <iostream>
#include <limits>

using namespace std;

const bool DEBUG = false;

long long int getIntInRange(const char *prompt, long long int min, long long int max);

int main(int argc, char *args[])
{
    cout << "Immetti la sequenza (0 per terminare): ";
    int first = getIntInRange("", numeric_limits<int>::min(), numeric_limits<int>::max());
    if (first != 0)
    {
        // just in case assumptions are not correct
        bool ascending = true, descending = true;
        do
        {

            int second = first;
            first = getIntInRange("", numeric_limits<int>::min(), numeric_limits<int>::max());
            if (first != 0)
            {
                if(first < second)
                {
                    ascending = false;
                }
                else if(first > second)
                {
                    descending = false;
                }
            }
        }
        while (first != 0);
        if (ascending)
        {
            if(descending)
            {
                cout << "P" << endl;
            }
            else
            {
                cout << "C" << endl;
            }
        }
        else
        {

            if (descending)
            {
                cout << "D" << endl;
            }
            else
            {
                cout << "A" << endl;
            }
        }
    }
    // successful termination
    return 0;
}

/// @brief Acquisisce un intero nell'intervallo [min, max] da tastiera
/// @param prompt messaggio per l'utente
/// @param min minimo valore accettabile
/// @param max massimo valore accettabile
/// @return il valore letto da tastiera
long long int getIntInRange(const char *prompt, long long int min, long long int max)
{
    long long int result = 0; // assegno un valore non valido
    bool valid;
    do
    {
        cout << prompt;
        cin >> result;
        valid = (!cin.fail()) && (min <= result) && (result <= max);
        if (!valid)
        {
            cerr << "Enter a number in [" << min << ", " << max << "]" << endl;
            cin.clear();                                         // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
        }
    }
    while (!valid);
    return result;
}
