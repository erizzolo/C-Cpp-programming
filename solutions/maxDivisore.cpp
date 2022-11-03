/*
 * Massimo divisore di un numero intero positivo
 * Author:  ER
 * Date:    2022/10/28
 * Note:
 */

/*
## maxDivisore
Scrivere un programma (maxDivisore) che visualizzi il massimo divisore di un numero intero positivo n, diverso dal numero stesso.

Ad es.: n = 525, output: 175

> (Quante divisioni esegue il vostro algoritmo?)

*/

#include <cstdio>

#define DEBUG 1

long long int getLLIntInRange(const char *prompt, long long int min, long long int max); // read a long long int in the range [min, max] from the keyboard
long long int twoPrimesSlow(long long int number);                                          // compute max divisor
long long int maxDivFast(long long int number);                                          // compute max divisor
void showSolution(long long int number, long long int result);                           // show problem and solution

// uso variabili globali per contare le operazioni
long long int tests;

int main(int argc, char *args[])
{
    // Acquisizione dati
    long long int number = getLLIntInRange("Immetti il numero: ", 1, (1LL << 62) - 1 + (1LL << 62)); // [1, 2^63 - 1]
    {
        // 1° metodo: ovvio
        // elaborazione
        tests = 0;
        long long int divisore = twoPrimesSlow(number);
        // Visualizzazione risultato
        showSolution(number, divisore);
    }

    {
        // 2° metodo: reverse ...
        // elaborazione
        tests = 0;
        long long int divisore = maxDivFast(number);
        // Visualizzazione risultato
        showSolution(number, divisore);
    }

    if (DEBUG)
    {
        printf("Test cases: \n");
        tests = 0;
        // Verifica casi di test
        showSolution(525, maxDivFast(525));
        showSolution(9223372036854775807, maxDivFast(9223372036854775807));
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

/// @brief Restituisce il massimo divisore di number diverso da number (slow version)
/// @param number il numero di cui si cerca il divisore
/// @return il massimo divisore di number diverso da number
long long int twoPrimesSlow(long long int number)
{
    // di sicuro nessun divisore in ]number /2, number[
    long long int divisor = number / 2;
    ++tests; // first evaluation
    while (number % divisor != 0)
    {
        --divisor;
        ++tests;
    }
    return divisor;
}

/// @brief Restituisce il massimo divisore di number diverso da number (fast version)
/// @param number il numero di cui si cerca il divisore
/// @return il massimo divisore di number diverso da number
long long int maxDivFast(long long int number)
{
    // il massimo divisore è il quoziente della divisione per il minimo divisore...
    long long int divisor = 2;
    ++tests; // first evaluation
    while (number % divisor != 0 && divisor <= number / divisor)
    {
        ++divisor;
        ++tests;
    }
    // gestisco il caso in cui number è primo !
    return number % divisor == 0 ? number / divisor : 1;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param number il numero
/// @param result il risultato, cioè il massimo divisore di number
void showSolution(long long int number, long long int result)
{
    printf("Il massimo divisore di %lld \212 %lld (effettuati %lld tests)\n", number, result, tests);
}
