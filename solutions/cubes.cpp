/*
 * Generazione di numeri "pseudo"casuali
 * Author:  ER
 * Date:    2022/10/28
 * Note:
 */

/*
## Statistiche sul lancio di due dadi (cubes)

Utilizzando le funzioni di generazione di numeri pseudocasuali della libreria ``cstdlib``, realizzare un’applicazione che determini e visualizzi la frequenza con cui, in nLanci di due dadi (cubici, con facce numerate da 1 a 6 ugualmente
probabili), la somma dei valori ottenuti assume uno degli undici valori possibili (da 2 a 12). L’applicazione deve inoltre verificare se la somma delle frequenze ottenute è parti al numero di lanci effettuati.

> Si ricorda che:
> * la funzione ``int rand()`` restituisce un valore compreso tra 0 e RAND_MAX.
> * per inizializzare il generatore di numeri pseudocasuali è necessario richiamare la funzione ``void srand(unsigned seed)`` con un valore opportuno (in caso contrario, *“rand() behaves as if it was seeded with std::srand(1)”*);
> * per ottenere sequenze di numeri pseudocasuali diverse ad ogni esecuzione dell’applicazione è opportuno richiamare la funzione ``void srand(unsigned seed)`` con un valore derivato dall’istante di esecuzione dell’applicazione, ad esempio ottenuto richiamando la funzione ``time_t time(time_t* arg)`` della libreria ctime con parametro ``NULL`` (oppure ``nullptr``);
> * per ottenere un valore casuale nell’intervallo [min, max] è possibile utilizzare la seguente formula (sebbene non perfetta dal punto di vista statistico): ``min + rand() % (max - min + 1)``;
> * è richiesto di non usare più di una variabile per il conteggio delle frequenze, bensì una funzione ``int frequenza(int valore, int nLanci)`` che restituisce il conteggio delle occorrenze di un particolare valore;
> * è possibile aggiungere altre funzioni se lo si ritiene opportuno.

**Esempio di possibile output (per nLanci = 10000):**
2: 294 / 10000
3: 604 / 10000
4: 827 / 10000
5: 1116 / 10000
6: 1339 / 10000
7: 1653 / 10000
8: 1392 / 10000
9: 1069 / 10000
10: 840 / 10000
11: 510 / 10000
12: 260 / 10000
Oh! Total is 9904 instead of 10000
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

using namespace std;

const bool DEBUG = false;

int frequenza(int valore, int nLanci);
long long int getIntInRange(const char *prompt, long long int min, long long int max);

int main(int argc, char *args[])
{
    // per ottenere la stessa sequenza, memorizzo time(nullptr) ...
    time_t seed = time(nullptr); // will be used to seed random generator
    // srand(seed);                 // if you want the sequences to be different
    int nLanci = getIntInRange("Immetti il numero di lanci: ", 1, numeric_limits<int>::max());
    int sumFrequencies = 0;
    for (int valore = 2; valore < 13; ++valore)
    {
        srand(seed); // if you want the sequences to be equals
        int freq = frequenza(valore, nLanci);
        cout << valore << ": " << freq << " / " << nLanci << endl;
        sumFrequencies += freq;
    }

    if (sumFrequencies != nLanci)
    {
        cout << "Oh! Total is " << sumFrequencies << " instead of " << nLanci << endl;
    }

    // successful termination
    return 0;
}

int dado()
{
    return 1 + rand() % 6;
}

int lancio()
{
    return dado() + dado();
}

int frequenza(int valore, int nLanci)
{
    int result = 0;
    while (nLanci-- > 0)
    {
        int esito = lancio();
        if (DEBUG)
            cout << "Esito: " << esito << endl;
        if (esito == valore)
        {
            ++result;
        }
    }
    return result;
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