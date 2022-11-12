/*
 * Verifica di primalità per divisioni successive
 * Author:  ER
 * Date:    2022/11/05
 * Note:
 */

/*
## Verifica di primalità (primo)
Descrizione del problema
Un numero intero x > 1 è detto numero primo se ha due soli divisori: 1 e x
stesso. Come è noto, 2, 3, 5, 7, 11 e 13 sono numeri primi mentre 15 non lo è
in quanto divisibile per 3.
Determinare se un numero naturale n è oppure no un numero primo.
Assunzione: n ≤ 3∙10^16.
Formato di input: leggere il numero da tastiera (senza controlli di validità)
Formato di output: PRIME se n è un numero primo, COMPOSITE altrimenti.
Esempi:
| Input         | Output    |
| ------------- | --------- |
| 0             | COMPOSITE |
| 2             | PRIME     |
| 239           | PRIME     |
| 4222234741    | PRIME     |
| 7563374525281 | COMPOSITE |

*/

#include <cstdio>

#define DEBUG 1

long long int getLLIntInRange(const char *prompt, long long int min, long long int max); // read a long long int in the range [min, max] from the keyboard
bool isPrimeSlow(long long int number);                                                  // primality test
bool isPrimeFast(long long int number);                                                  // primality test
void showSolution(long long int number, bool result);                                    // show problem and solution

// uso variabili globali per contare le operazioni
long long int tests;

int main(int argc, char *args[])
{
    // Acquisizione dati
    long long int number = getLLIntInRange("Immetti il numero: ", 0, 30'000'000'000'000'000LL);

    {
        // 1° metodo: ovvio
        // elaborazione
        tests = 0;
        bool isPrime = isPrimeSlow(number);
        // Visualizzazione risultato
        showSolution(number, isPrime);
    }

    {
        // 2° metodo: reverse ...
        // elaborazione
        tests = 0;
        bool isPrime = isPrimeFast(number);
        // Visualizzazione risultato
        showSolution(number, isPrime);
    }

    if (DEBUG)
    {
        printf("Test cases: \n");
        tests = 0;
        // Verifica casi di test
        showSolution(0, isPrimeFast(0));
        showSolution(2, isPrimeFast(2));
        showSolution(239, isPrimeFast(239));
        showSolution(4222234741, isPrimeFast(4222234741));
        showSolution(7563374525281, isPrimeFast(7563374525281));
    }

    // successful termination
    return 0;
}

/// @brief Acquisisce un intero nell'intervallo [min, max] da tastiera
/// @param prompt messaggio per l'utente
/// @param min minimo valore accettabile
/// @param max massimo valore accettabile
/// @return il valore letto da tastiera
long long int getLLIntInRange(const char *prompt, long long int min, long long int max)
{
    long long int result = 0; // assegno un valore non valido
    bool valid;
    do
    {
        printf("%s", prompt);
        valid = (scanf("%lld", &result) == 1) && (min <= result) && (result <= max);
        if (!valid)
        {
            scanf("%*[^\n]");
            printf("Value must be a number between %lld and %lld in decimal form.\n", min, max);
        }
    } while (!valid);
    return result;
}

/// @brief Restituisce true se number è primo, false altrimenti (slow version)
/// @param number il numero di cui si verifica la primalità
/// @return true se number è primo, false altrimenti
bool isPrimeSlow(long long int number)
{
    bool prime = number > 1; // no 0 e 1
    if (prime)
    {
        long long int factor = 2;
        while (factor <= number / factor && prime)
        {
            prime = number % factor != 0;
            ++factor;
        }
    }
    return prime;
}

long long int sqrt(long long int number)
{
    long long int result = 0, step = 1LL << 31;
    while (step > 0)
    {
        long long int test = result + step;
        if (test * test <= number)
        {
            result = test;
        }
        step /= 2;
    }
    return result;
}

/// @brief Restituisce true se number è primo, false altrimenti (fast version)
/// @param number il numero di cui si verifica la primalità
/// @return true se number è primo, false altrimenti
bool isPrimeFast(long long int number)
{
    bool prime = number > 1; // no 0 e 1
    if (prime)
    {
        long long int factor = 2, limit = sqrt(number);
        while (factor <= limit && prime)
        {
            prime = number % factor != 0;
            ++factor;
        }
    }
    return prime;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param number il numero
/// @param result il risultato, cioè se number è primo o no
void showSolution(long long int number, bool isPrime)
{
    printf("%lld is a %s (%lld tests)\n", number, isPrime ? "PRIME" : "COMPOSITE", tests);
}
