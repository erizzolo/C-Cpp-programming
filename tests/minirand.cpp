/*
 * Generazione di numeri "pseudo"casuali
 * Author:  ER
 * Date:    2022/10/28
 * Note:
 */

/*
1. Frazioni casuali (minirand)
La funzione int rand() restituisce un valore pseudocasuale compreso tra 0 e RAND_MAX.
Si vuole realizzare un’applicazione che necessita valori pseudocasuali in virgola mobile nell’intervallo [0, 1) (0 incluso, 1 escluso).
Si realizzi un’applicazione che, tramite una funzione con il prototipo:
    double miniRand(int nCifre);
generi una sequenza di valori casuali con parte intera uguale a 0 ed nCifre cifre decimali dopo la virgola, verificando il minimo ed il massimo valore restituito dalla funzione miniRand(), in un numero sufficiente di chiamate, nLanci.
La funzione  miniRand(), tramite la funzione rand() della libreria cstdlib, deve restituire il numero con rappresentazione decimale costituita da parte intera uguale a 0 e parte frazionaria formata da nCifre cifre, ciascuna estratta casualmente con uguale probabilità.
Ad esempio, se nCifre = 3, la funzione deve estrarre tre cifre decimali casuali (decimi d, centesimi c e millesimi m) e restituire il numero corrispondente, ovvero 0.dcm (punto decimale secondo la notazione anglosassone).

Assunzione: 1 <= nCifre <= 18, 1 <= nLanci <= 10^9.
Formato di input: leggere da tastiera (con controllo di validità) il valore di nCifre ed il numero di estrazioni casuali da effettuare.
Formato di output: due interi in formato decimale corrispondenti al valore minimo e massimo ottenuti dalle estrazioni.
Esempi:
| Input      | Output           | Note                                          |
| ---------- | ---------------- | --------------------------------------------- |
| 3 100000   | 0 0.999          | Minimo e massimo per un numero a 3 cifre      |
| 5 2        | 0.67343 0.96891  | I due valori estratti con 5 cifre frazionarie |
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

using namespace std;

const bool DEBUG = false;

double miniRand(int nCifre);
long long int getIntInRange(const char *prompt, long long int min, long long int max);

int main(int argc, char *args[])
{
    srand(time(nullptr));
    cout << "Immetti il numero di cifre ed il numero di lanci";
    int nCifre = getIntInRange("", 1, 18);
    int nLanci = getIntInRange("", 1, 1'000'000'000);
    double min = numeric_limits<double>::max();
    double max = numeric_limits<double>::min();
    for (int estrazione = 0; estrazione < nLanci; ++estrazione)
    {
        double casuale = miniRand(nCifre);
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

double miniRand(int nCifre)
{
    double result = 0;
    while (nCifre-- > 0)
    {
        result = (result + rand() % 10) / 10;
    }
    return result;
}

// versione alternativa
double miniRandBis(int nCifre)
{
    double result = 0;
    double peso = 1;
    while (nCifre > 0)
    {
        peso /= 10;
        result += (rand() % 10) * peso;
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