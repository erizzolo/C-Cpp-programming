/**
 * Purpose: rotazioni sequenza
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2022/12/22
 * Note:
 */

/*
## Rotazioni ( rotazioni )
### Descrizione del problema
Una rotazione a sinistra di una sequenza di n valori sposta ciascun elemento a sinistra di una posizione, tranne il primo elemento che viene spostato in ultima posizione.

Ad esempio:

dopo una rotazione a sinistra la sequenza [0,1,2,3,4] diviene [1,2,3,4,0];

dopo due rotazioni a sinistra la sequenza [0,1,2,3,4] diviene [2,3,4,0,1].

Data la lunghezza n della sequenza, il numero d di rotazioni effettuate e gli n valori della sequenza iniziale, determinare quale valore si troverà in prima posizione (posizione 0) ed in quale posizione (numerate da 0 a n-1) si troverà l'elemento originalmente in posizione iniziale.

**Assunzione**: 1 ≤ n ≤ 25, 0 ≤ d ≤ 10<sup>9</sup>.

**Formato di input**: leggere n, d e gli n valori della sequenza originale da tastiera, (con controlli di validità).

**Formato di output**: il valore che si troverà in posizione 0 (la prima) e la posizione in cui si troverà il primo valore della sequenza originale, dopo d rotazioni a sinistra della sequenza data.

**Esempi**:
| Input     | Output | Note                      |
| --------- | ------ | ------------------------- |
| 5 1       |        | n = 5, d = 1:             |
| 0 1 2 3 4 | 1 4    | sequenza finale 1 2 3 4 0 |
| 5 2       |        | n = 5, d = 2:             |
| 0 1 2 3 4 | 2 3    | sequenza finale 2 3 4 0 1 |
| 5 7       |        | n = 5, d = 7:             |
| a e i o u | i 3    | sequenza finale i o u a e |

*/

#include <iostream>
#include <limits>
using namespace std;

const bool DEBUG = true;

// uso come valori della sequenza dei caratteri
using type = char;

long long int getIntInRange(const char *prompt, long long int min, long long int max);
// char getCharInRange(const char *prompt, char min, char max);
type getTypeInRange(const char *prompt, type min, type max);

void JSON(const type a[], int end, int begin = 0, ostream &out = cout); // output su out in formato JSON
void fillFromKeyboard(type a[], type min, type max, int end, int begin = 0);
void rotateArray(type a[], int end, int begin = 0);

// main function
int main(int argc, char *argv[])
{
    int n = getIntInRange("Lunghezza sequenza: ", 1, 25);
    int d = getIntInRange("Numero rotazioni: ", 0, 1'000'000'000);
    int deff = d % n; // elimino rotazioni che riportano la sequenza a quella iniziale
    if (DEBUG)
    {
        cout << "n = " << n << ", d = " << d << ", deff = " << deff << endl;
    }

    type sequenza[n]; // non necessario

    cout << "Immetti i valori della sequenza" << endl;
    fillFromKeyboard(sequenza, 'a', 'z', n); // use suitable min and max

    cout << "Elemento che si troverà all'inizio: " << sequenza[deff] << endl;
    int posfinale = deff == 0 ? 0 : n - deff;
    cout << "Posizione dell'elemento iniziale: " << posfinale << endl;

    cout << "Sequenza originale:" << endl;
    JSON(sequenza, n);
    cout << endl;
    for (int rot = 0; rot < d; ++rot)
    {
        rotateArray(sequenza, n);
        if (DEBUG)
        {
            cout << "Rotazione " << rot << ": ";
            JSON(sequenza, n);
            cout << endl;
        }
    }
    cout << "Sequenza finale:" << endl;
    JSON(sequenza, n);
    cout << endl;

    // successful termination
    return 0;
}

/// @brief Basic left rotation
/// @param a     the array to rotate
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void rotateArray(type a[], int end, int begin /* = 0 */)
{
    if (end - begin > 1) // at least two elements ...
    {
        type temp = a[begin];
        for (int i = begin; i < end - 1; ++i)
        {
            a[i] = a[i + 1];
        }
        a[end - 1] = temp;
    }
}

/// @brief Output su out in formato JSON da begin a end escluso: [begin, end)
/// @param a     the array to output
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @param out   the output stream to be used
void JSON(const type a[], int end, int begin /* = 0 */, ostream &out /* = cout */)
{
    out << "[ ";
    for (int i = begin; i < end; ++i)
    {
        if (i != begin)
            out << ", ";
        out << a[i];
    }
    out << " ]";
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

/// @brief Acquisisce un type nell'intervallo [min, max] da tastiera
/// @param prompt messaggio per l'utente
/// @param min minimo valore accettabile
/// @param max massimo valore accettabile
/// @return il valore letto da tastiera
type getTypeInRange(const char *prompt, type min, type max)
{
    type result;
    bool valid;
    do
    {
        cout << prompt;
        cin >> result;
        valid = (!cin.fail()) && (min <= result) && (result <= max);
        if (!valid)
        {
            cerr << "Enter a type in [" << min << ", " << max << "]" << endl;
            cin.clear();                                         // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
        }
    } while (!valid);
    return result;
}

void fillFromKeyboard(type a[], type min, type max, int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        a[i] = getTypeInRange("", min, max);
    }
}
