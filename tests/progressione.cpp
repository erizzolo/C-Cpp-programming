/*
 * Verifica sequenza in progressione aritmetica
 * Author:  ER
 * Date:    2022/10/28
 * Note:
 */

/*
2. Sequenza aritmetica (progressione)
Si vuole analizzare una sequenza di numeri interi non nulli, terminata da un valore 0 (zero), immessa dall’utente.
In particolare si vuole determinare se la sequenza costituisce una progressione aritmetica ed in tal caso conoscerne il numero di termini e la ragione.
Si ricorda che una progressione aritmetica “è una successione di numeri tali che la differenza tra ciascun termine (o elemento) della successione e il suo precedente sia una costante. Tale costante viene detta ragione della progressione.”
Ad esempio, se i valori immessi sono:
    1 3 5 7 9 11 0 (lo zero non viene considerato parte della sequenza)
la sequenza immessa è:
    1 3 5 7 9 11
ed in essa la differenza tra due termini consecutivi è sempre pari a 2, quindi essa costituisce (una parte di) una progressione aritmetica di ragione 2.
Si chiede di determinare se la sequenza immessa può essere parte di una progressione aritmetica ed in caso positivo la ragione della progressione.
Assunzione: 2 <= lunghezza sequenza <= 108, -109 <= valore <= 109.
Formato di input: leggere da tastiera la sequenza di numeri interi non nulli, terminata dal valore 0 (zero).
Formato di output: I caratteri Y oppure N, a seconda che la sequenza sia o meno in progressione aritmetica e, in caso positivo, un intero in formato decimale che rappresenta la ragione della progressione.

Esempi:
| Input                 | Output    | Note                                          |
| --------------------- | --------- | --------------------------------------------- |
| 1 2 1 5 7 3 9 4 6 0   | N         | La sequenza non è in progressione aritmetica  |
| 1 2 3 4 5 6 7 8 9 0   | Y 1       | La sequenza è una progressione con ragione 1  |
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
    { // just in case assumptions are not correct
        int second = getIntInRange("", numeric_limits<int>::min(), numeric_limits<int>::max());
        if (second != 0)
        {                                 // again, ... just in case assumptions are not correct
            int ragione = second - first; // differenza costante?
            bool isProgressione = true;   // any couple is an arithmetic progression...
            do
            {
                int nextValue = getIntInRange("", numeric_limits<int>::min(), numeric_limits<int>::max());
                if (nextValue != 0)
                {
                    isProgressione = isProgressione && ((nextValue - second) == ragione);
                }
                second = nextValue;
            } while (second != 0);
            if (isProgressione)
            {
                cout << "Y " << ragione << endl;
            }
            else
            {
                cout << "N" << endl;
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
    } while (!valid);
    return result;
}