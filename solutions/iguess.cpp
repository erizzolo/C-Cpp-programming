/**
 * Gioco che consiste nell'indovinare un numero pensato dall'utente
 * Author:  ER
 * Date:    2022/11/21
 * Note:
 */

#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

const bool DEBUG = false;

// prototypes
int randInRange(int min, int max);             // valore casuale tra min e max
void showInstructions(int max, int tentativi); // istruzioni per l'utente
void showStatus(int max, int tentativi);       // mostra situazione all'utente
int getTentativo(int max);                     // acquisisce tentativo
bool getResult(int guess);                     // acquisisce l'esito dall'utente
char getYN(const char *prompt);                // acquisisce y/n

int main(int argc, char *args[])
{
    // inizializzazione gioco
    srand(time(nullptr));
    int max = randInRange(10, 20); // impostazione range [0, max] con 10 <= max <= 20
    int tentativi = max / 2;       // numero tentativi ammessi

    showInstructions(max, tentativi); // istruzioni per l'utente

    bool indovinato = false; // non ho (ancora) indovinato

    do
    {
        showStatus(max, tentativi);    // mostra situazione all'utente
        int guess = getTentativo(max); // acquisisce tentativo (casuale)
        --tentativi;                   // un tentativo in meno
        indovinato = getResult(guess); // acquisisce l'esito
        // ripeto se ho tentativi e non ho indovinato
    } while ((tentativi > 0) && (!indovinato));

    // stato finale
    if (indovinato)
    {
        // congrats
        cout << endl;
        cout << "Congratulazioni! Ho indovinato." << endl;
    }
    else
    {
        // sorry
        cout << endl;
        cout << "Mi dispiace! Non ho indovinato: chissa' qual era il numero ?" << endl;
    }

    // successful termination
    return 0;
}

/// @brief restituisce un valore casuale tra min e max
/// @param min estremo inferiore dell'intervallo
/// @param max estremo superiore dell'intervallo
/// @return un valore casuale nell'intervallo [min, max]
int randInRange(int min, int max)
{
    return min + rand() % (max - min + 1);
}

/// @brief mostra a video istruzioni per l'utente
/// @param max il valore massimo possibile
/// @param tentativi numero tentativi residui
void showInstructions(int max, int tentativi)
{
    cout << "Pensa a un numero compreso tra 0 e " << max << " inclusi, ";
    cout << "ed io cerchero' di indovinarlo in " << tentativi << " tentativi" << endl;
}

/// @brief mostra situazione all'utente
/// @param max
/// @param tentativi tentativi residui
void showStatus(int max, int tentativi)
{
    cout << "Ho ancora " << tentativi << " tentativi. ";
}

/// @brief acquisisce tentativo da utente
/// @return il tentativo effettuato
int getTentativo(int max)
{
    return randInRange(0, max);
}

/// @brief acquisisce l'esito dall'utente
/// @param guess il tentativo effettuato
/// @return l'esito segnalato dall'utente
bool getResult(int guess)
{
    cout << "Il mio tentativo e' " << guess << endl;
    cout << "Ho indovinato ? (y/n)";
    char answer = getYN("");
    return answer == 'y';
}

/// @brief Acquisisce y/n  da tastiera
/// @param prompt messaggio per l'utente
/// @return il valore letto da tastiera
char getYN(const char *prompt)
{
    char result = '?';
    bool valid;
    do
    {
        cout << prompt;
        cin >> result;
        valid = (!cin.fail()) && ((result == 'y') || (result == 'n'));
        if (!valid)
        {
            cerr << "Enter y (yes) or n (no)" << endl;
            cin.clear();                                         // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
        }
    } while (!valid);
    return result;
}
