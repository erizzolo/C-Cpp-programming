/*
 * Generazione di numeri "pseudo"casuali
 * Author:  ER
 * Date:    2022/10/28
 * Note:
 */

/*
    2. Sottosequenza crescente (maxsalita)
Si vuole analizzare una sequenza di numeri interi non nulli, terminata da un valore 0 (zero), immessa dall’utente.
In particolare si vuole determinare il numero massimo di valori consecutivi immessi in ordine (strettamente) crescente.
Ad esempio, se i valori immessi sono:
    1 2 1 5 7 3 9 4 6 0 (lo zero non viene considerato parte della sequenza)
la sequenza immessa è:
    1 2 1 5 7 3 9 4 6
ed in essa sono presenti diverse sottosequenze di numeri in ordine crescente:
    ad esempio 1 2, 1 5, 1 5 7, 5 7, 3 9, 4 6
La sottosequenza più lunga è 1 5 7 per cui il numero massimo di valori consecutivi immessi in ordine (strettamente) crescente è 3.
Si chiede di calcolare il numero massimo di valori consecutivi immessi in ordine (strettamente) crescente e di visualizzare tali valori.
Nel caso vi siano più sottosequenze di lunghezza massima, è sufficiente visualizzarne una qualsiasi.
Assunzione: 2 <= lunghezza sequenza <= 10^8, -10^9 <= valore <= 10^9.
Formato di input: leggere da tastiera la sequenza di numeri interi non nulli, terminata dal valore 0 (zero).
Formato di output: un intero in formato decimale che rappresenta il numero massimo di valori consecutivi immessi in ordine (strettamente) crescente e, su un’altra riga, la lista di tali valori separati da spazio.
Esempi:
| Input                 | Output    | Note                                  |
| --------------------- | --------- | ------------------------------------- |
| 1 2 1 5 7 3 9 4 6 0   | 3         | La sottosequenza più lunga è 1 5 7    |
| 1 2 3 4 5 6 7 8 9 0   | 9         | La sequenza è tutta crescente         |
*/

#include <iostream>
#include <limits>

using namespace std;

const bool DEBUG = false;

int sequenza[100'000'000];  // not really needed

long long int getIntInRange(const char *prompt, long long int min, long long int max);

int main(int argc, char *args[])
{
    int seqLength = 0;                     // lunghezza sequenza
    bool terminated = false;               // sequenza terminata
    int maxLength = 0, maxStart = 0;       // max number of ascending values, and start index
    int actualLength = 1, actualStart = 0; // actual number of ascending values, and start index
    cout << "Immetti la sequenza (0 per terminare): ";
    int value = getIntInRange("", numeric_limits<int>::min(), numeric_limits<int>::max());
    // assume first input != 0 ...
    do
    {
        sequenza[seqLength] = value;
        ++seqLength;
        int nextValue = getIntInRange("", numeric_limits<int>::min(), numeric_limits<int>::max());
        terminated = nextValue == 0;
        if (!terminated)
        {
            if (nextValue > value)
            {
                ++actualLength; // one more in current sequence
            }
            else
            {
                if (maxLength < actualLength)
                {
                    maxLength = actualLength;
                    maxStart = actualStart;
                }
                actualLength = 1;
                actualStart = seqLength;
            }
            value = nextValue; // update last
        }
    } while (!terminated);
    if (maxLength < actualLength)
    {
        maxLength = actualLength;
        maxStart = actualStart;
    }
    cout << maxLength << endl;
    for (int i = 0; i < maxLength; ++i)
    {
        cout << sequenza[i + maxStart] << " ";
    }
    cout << endl;

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