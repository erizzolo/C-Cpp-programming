/*
 * Generazione di numeri "pseudo"casuali
 * Author:  ER
 * Date:    2022/10/28
 * Note:
 */

/*
1. Numeri casuali grandissimi (megarand)
La funzione int rand() restituisce un valore pseudocasuale compreso tra 0 e RAND_MAX.
Si vuole realizzare un’applicazione che necessita valori pseudocasuali in un intervallo [0, RAND_MEGA] possibilmente più esteso di [0, RAND_MAX].
(Ad esempio, RAND_MEGA potrebbe essere 999’999’999’999’999’999 mentre RAND_MAX nei sistemi Windows è tipicamente 32767).
Si realizzi un’applicazione che, tramite una funzione con il prototipo:
    long long int megaRand(int nCifre);
generi una sequenza di valori casuali di nCifre cifre decimali, verificando il minimo ed il massimo valore restituito dalla funzione megarand(), in un numero sufficiente di chiamate, nLanci.
Tale funzione, tramite la funzione rand() della libreria cstdlib, deve restituire il numero con rappresentazione decimale formata da nCifre cifre, ciascuna estratta casualmente con uguale probabilità.
Ad esempio, se nCifre = 3, la funzione deve estrarre tre cifre decimali casuali (unità, decine e centinaia) e restituire il numero corrispondente.

Assunzione: 1 <= nCifre <= 18, 1 <= nLanci <= 10^9.
Formato di input: leggere da tastiera (con controllo di validità) il valore di nCifre ed il numero di estrazioni casuali da effettuare.
Formato di output: due interi in formato decimale corrispondenti al valore minimo e massimo ottenuti dalle estrazioni.
Esempi:
| Input      | Output       | Note                                     |
| ---------- | ------------ | ---------------------------------------- |
| 3 100000   | 0 999        | Minimo e massimo per un numero a 3 cifre |
| 5 2        | 17823 83567  | I due valori estratti con 5 cifre        |
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

using namespace std;

const bool DEBUG = false;

long long int megaRand(int nCifre);
long long int getIntInRange(const char *prompt, long long int min, long long int max);

int main(int argc, char *args[])
{
    srand(time(nullptr));
    cout << "Immetti il numero di cifre ed il numero di lanci";
    int nCifre = getIntInRange("", 1, 18);
    int nLanci = getIntInRange("", 1, 1'000'000'000);
    long long int min = numeric_limits<long long int>::max(); // 1'000'000'000'000'000'000 is ok
    long long int max = numeric_limits<long long int>::min(); // 0 is ok
    for (int estrazione = 0; estrazione < nLanci; ++estrazione)
    {
        long long int casuale = megaRand(nCifre);
        if (min > casuale)
        {
            min = casuale;
        }
        if (max < casuale)
        {
            max = casuale;
        }
    }

    cout << min << " " << max << endl;

    // successful termination
    return 0;
}

long long int megaRand(int nCifre)
{
    long long int result = 0;
    while (nCifre-- > 0)
    {
        result = result * 10 + (rand() % 10);
    }
    return result;
}

// versione alternativa
long long int megaRandBis(int nCifre)
{
    long long int result = 0;
    long long int peso = 1;
    while (nCifre > 0)
    {
        result += (rand() % 10) * peso;
        peso *= 10;
        nCifre--;
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