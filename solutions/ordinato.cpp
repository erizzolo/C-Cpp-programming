/*
 * Generazione di numeri "pseudo"casuali con ordine
 * Author:  ER
 * Date:    2022/12/23
 * Note:
 */

/*
## Caos ordinato (ordinato)
Utilizzando le funzioni di generazione di numeri pseudocasuali della libreria
cstdlib, realizzare un’applicazione che memorizzi in un array di numElementi
elementi dei valori interi casuali compresi in un intervallo [min, max] scelto
dall’utente in modo tale che l’array risulti ordinato in modo crescente.

Ogni esecuzione dell’applicazione deve generare una diversa sequenza di valori,
anche a parità dei dati di input.

Se la generazione dei valori non è possibile, l’applicazione deve mostrare un
opportuno messaggio e terminare.

Assunzione: 1 ≤ numElementi ≤ 1000, min ≤ max.

Formato di input: leggere da tastiera (controllandone la validità) gli interi
 *numElementi*, *min* e *max*, separati da uno spazio.

Formato di output: visualizzare gli elementi dell’array generato.
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

using namespace std;
using type = int;

const bool DEBUG = true;

void fillRandStrictAscending(type a[], type min, type max, int end, int begin = 0);
void fillRandDichoAscending(type a[], type min, type max, int end, int begin = 0);
void fillRandAuxArrayAscending(type a[], type min, type max, int end, int begin = 0);
void fillRandAscending(type a[], type min, type max, int end, int begin = 0);
void JSON(const type a[], int end, int begin = 0, ostream &out = cout); // output su out in formato JSON

long long int getIntInRange(const char *prompt, long long int min, long long int max);

int main(int argc, char *args[])
{
    int numElementi = getIntInRange("Numero di elementi: ", 1, 1000);
    int min = getIntInRange("Valore minimo: ", numeric_limits<int>::min(), numeric_limits<int>::max());
    int max = getIntInRange("Valore massimo: ", min, numeric_limits<int>::max());

    srand(time(nullptr));
    int values[numElementi];

    // ordine strettamente crescente: verifica esistenza soluzione
    if (max - min + 1 >= numElementi)
    {
        cout << "Con accumulo verso il massimo ..." << endl;
        fillRandStrictAscending(values, min, max, numElementi);
        JSON(values, numElementi);
        cout << endl;
        cout << "Distribuzione troppo uniforme ..." << endl;
        fillRandDichoAscending(values, min, max, numElementi);
        JSON(values, numElementi);
        cout << endl;
        if (max - min < 1000)
        {
            cout << "Possibile per range limitato ..." << endl;
            fillRandAuxArrayAscending(values, min, max, numElementi);
            JSON(values, numElementi);
            cout << endl;
        }
    }
    else
    {
        cout << "Impossibile con ordinamento strettamente crescente!" << endl;
    }

    // ordine non strettamente crescente
    fillRandAscending(values, min, max, numElementi);
    JSON(values, numElementi);
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

void fillRandAscending(type a[], type min, type max, int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        a[i] = rand() % (max - min + 1) + min;
        min = a[i];
    }
}

void fillRandStrictAscending(type a[], type min, type max, int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        a[i] = rand() % (max - min + 1 - (end - 1 - i)) + min;
        min = a[i] + 1;
    }
}

void fillRandDichoAscending(type a[], type min, type max, int end, int begin /* = 0 */)
{
    if (end - begin > 1)
    { // more than one element
        // split [begin, end) = [begin, middle) U [middle, end)
        int middle = begin + (end - begin) / 2;
        // split [min, max + 1) = [min, half) U [half, max + 1)
        type half = min + (max + 1 - min) / 2;
        // fill first and second parts
        fillRandDichoAscending(a, min, half - 1, middle, begin);
        fillRandDichoAscending(a, half, max, end, middle);
    }
    else if (end - begin == 1)
    { // just one element
        a[begin] = rand() % (max - min + 1) + min;
    }
}

void fillRandAuxArrayAscending(type a[], type min, type max, int end, int begin /* = 0 */)
{
    // con array ausiliario
    bool estratti[max - min + 1];
    for (int i = 0; i < max - min + 1; i++)
    {
        estratti[i] = false;
    }
    for (int i = begin; i < end; ++i)
    {
        int estrazione;
        do {
            estrazione = rand() % (max - min + 1);
        } while(estratti[estrazione]);
        estratti[estrazione] = true;
    }
    for (int i = begin, estrazione = 0; i < end; ++i)
    {
        while(!estratti[estrazione]) {
            estrazione++;
        }
        a[i] = estrazione + min;
        ++estrazione;
    }
}
