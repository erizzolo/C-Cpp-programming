/*
    Purpose:    determinazione di pi greco con metodo Montecarlo
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2022/12/22
    Note:
*/
/*
    Scommettere o non scommettere? (monteCarlo)
    Descrizione del problema
    Il mio amico Carlo ha lasciato il convento in cui era monaco (da cui il soprannome monteCarlo) e si è appassionato alle scommesse.
    Mi ha quindi proposto una simile scommessa: si tratta di estrarre a caso due numeri interi x, y nell'intervallo [-1000,+1000]
    (estremi inclusi, tramite dei dadi che lui si è costruito negli anni di clausura e di cui mi fido)
    e verificare se la seguente espressione è vera o no: x*x+y*y<=1000000.
    Se è vera, vince Carlo ed io perdo la somma scommessa, altrimenti vinco io e guadagno il triplo della somma scommessa.
    Ho deciso di accettare, ma vorrei sapere se alla lunga ci rimetterò!!!
    Scrivete un'applicazione che simuli la scommessa per un numero n di volte e determini:
    a. il numero di volte in cui vince Carlo ed in cui vinco io;
    b. quale somma ho vinto/perso mediamente per ogni scommessa effettuata.
    Assunzione: 1 ≤ n ≤ 1e12. La somma scommessa è sempre un bitEuro (b€).
    Formato di input: leggere n da tastiera, (senza controlli di validità)
    Formato di output: il numero di vittorie di Carlo ed il numero di vittorie mie, separati da spazio, sulla prima riga; la vincita/perdita media sulla seconda riga.
*/

#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

const bool DEBUG = false;

long long int getIntInRange(const char *prompt, long long int min, long long int max);

#define RADIUS 1000
#define MAX_VALUE RADIUS
#define MIN_VALUE -RADIUS
#define NUM_VALUES (MAX_VALUE - MIN_VALUE + 1)
#define LIMIT_VALUE (RADIUS * RADIUS)

int main(int argc, char *argv[])
{
    long long int nScommesse = getIntInRange("Numero di scommesse da simulare: ", 1, 1'000'000'000'000);

    // start simulation
    long long int carloWins = 0, carloLoses = 0, totalGainOrLoss = 0;
    // init random number generator's seed
    srand(time(nullptr));
    for (long long int scommessa = 0; scommessa < nScommesse; scommessa++)
    {
        int x = MIN_VALUE + rand() % NUM_VALUES;
        int y = MIN_VALUE + rand() % NUM_VALUES;
        if (x * x + y * y <= LIMIT_VALUE)
        {
            // Carlo wins
            carloWins++;
            // totalGainOrLoss--;
        }
        else
        {
            // Carlo loses
            // carloLoses++;
            // totalGainOrLoss += 3;
        }
    }
    // compute average gain/loss
    carloLoses = nScommesse - carloWins;
    totalGainOrLoss = 3 * carloLoses - carloWins;
    double averageGainOrLoss = ((double)totalGainOrLoss) / nScommesse;
    cout << "Carlo wins: " << carloWins << ", loses: " << carloLoses << endl;
    cout << "Average gain or loss: " << averageGainOrLoss << endl;

    double side = MAX_VALUE - MIN_VALUE;
    double square = side * side;
    cout << "Area of square of side " << side << ": " << square << endl;
    double radius = RADIUS;
    double circle = radius * radius * M_PI;
    cout << "Area of circle of radius " << radius << ": " << circle << endl;
    cout << "Ratio = probability that Carlo wins: " << circle / square << endl;
    cout << "Expected Carlo wins: " << circle / square * nScommesse << endl;
    cout << "Estimated value of pi: " << 4.0 * carloWins / nScommesse << endl;

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
