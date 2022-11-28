/**
 * Gioco che consiste nel far indovinare all'utente un numero
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
int randInRange(int min, int max);                                                     // valore casuale tra min e max
void showInstructions(int max, int tentativi);                                         // istruzioni per l'utente
void showStatus(int max, int tentativi);                                               // mostra situazione all'utente
int getTentativo(int max);                                                             // acquisisce tentativo da utente
void getResult(int guess, bool indovinato);                                            // mostra l'esito all'utente
long long int getIntInRange(const char *prompt, long long int min, long long int max); // acquisisce n in [min, max]

int main(int argc, char *args[])
{
    // inizializzazione gioco
    srand(time(nullptr));
    int max = randInRange(10, 20);    // impostazione range [0, max] con 10 <= max <= 20
    int tentativi = max / 2;          // numero tentativi ammessi
    int valore = randInRange(0, max); // valore casuale tra 0 e max

    showInstructions(max, tentativi); // istruzioni per l'utente

    bool indovinato = false; // l'utente non ha (ancora) indovinato

    do
    {
        showStatus(max, tentativi);    // mostra situazione all'utente
        int guess = getTentativo(max); // acquisisce tentativo da utente
        --tentativi;                   // un tentativo in meno
        indovinato = guess == valore;  // ha indovinato ?
        getResult(guess, indovinato);  // mostra l'esito
        // ripeto se l'utente ha tentativi e non ha indovinato
    } while ((tentativi > 0) && (!indovinato));

    // stato finale
    if (indovinato)
    {
        // congrats
        cout << endl;
        cout << "Congratulazioni! Hai indovinato." << endl;
    }
    else
    {
        // sorry
        cout << endl;
        cout << "Mi dispiace! Non hai indovinato: il numero era " << valore << endl;
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
    cout << "Devi indovinare un numero compreso tra 0 e " << max << " inclusi, ";
    cout << "in " << tentativi << " tentativi";
}

/// @brief mostra situazione all'utente
/// @param max
/// @param tentativi tentativi residui
void showStatus(int max, int tentativi)
{
    cout << "; hai ancora " << tentativi << " tentativi." << endl;
}

/// @brief acquisisce tentativo da utente
/// @return il tentativo effettuato
int getTentativo(int max)
{
    cout << "Fai un tentativo: ";
    return getIntInRange("", 0, max);
}

/// @brief mostra l'esito all'utente
/// @param guess il tentativo effettuato
/// @param result l'esito
void getResult(int guess, bool result)
{
    cout << guess << (result ? " e'" : " non e'") << " il numero giusto";
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
