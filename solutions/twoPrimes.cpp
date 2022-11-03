/*
 * Numero intero positivo prodotto di due primi distinti
 * Author:  ER
 * Date:    2022/10/28
 * Note:    Tramite conteggio dei divisori (4 se è il prodotto di due primi distinti)
 */

/*
## twoPrimes
Scrivere un programma (twoPrimes) che dice se un numero intero positivo n è il prodotto di esattamente due diversi numeri primi (con esponente 1).

Es.: n = 20, output = NO; n = 33, output = YES

*/

#include <cstdio>

#define DEBUG 1

long long int getLLIntInRange(const char *prompt, long long int min, long long int max); // read a long long int in the range [min, max] from the keyboard
bool twoPrimesSlow(long long int number);                                                // true iff number = product of two primes
bool twoPrimesFast(long long int number);                                                // true iff number = product of two primes
void showSolution(long long int number, bool result);                                    // show problem and solution

int main(int argc, char *args[])
{
    // Acquisizione dati
    long long int number = getLLIntInRange("Immetti il numero: ", 1, (1LL << 62) - 1 + (1LL << 62)); // [1, 2^63 - 1]
    {
        // 1° metodo: ovvio
        // elaborazione
        bool result = twoPrimesSlow(number);
        // Visualizzazione risultato
        showSolution(number, result);
    }

    {
        // 2° metodo: interruzione del conteggio se trovo troppi divisori
        // elaborazione
        bool result = twoPrimesFast(number);
        // Visualizzazione risultato
        showSolution(number, result);
    }

    if (DEBUG)
    {
        printf("Test cases: \n");
        // Verifica casi di test
        showSolution(20, twoPrimesSlow(20));
        showSolution(33, twoPrimesSlow(33));
        showSolution(9223372036854775807, twoPrimesFast(9223372036854775807));
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

int countDivisori(long long int number)
{
    int numDivisori;
    if (number == 1)
    {
        numDivisori = 1;
    }
    else
    {
        numDivisori = 2;
        long long int divisore = 2;
        while (divisore < number / divisore)
        {
            if (number % divisore == 0)
            {
                numDivisori += 2;
            }
            divisore++;
        }
        // perfect square?
        if (number == divisore * divisore)
        {
            numDivisori++;
        }
    }
    return numDivisori;
}

/// @brief Restituisce se il numero dato è il prodotto di due primi distinti
/// @param number il numero
/// @return true se il numero dato è il prodotto di due primi distinti
bool twoPrimesSlow(long long int number)
{
    return countDivisori(number) == 4;
}

/// @brief Restituisce se il numero dato è il prodotto di due primi distinti
/// @param number il numero
/// @return true se il numero dato è il prodotto di due primi distinti
bool twoPrimesFast(long long int number)
{
    bool result = number > 5; // 6 è il minimo prodotto di due primi distinti
    if (result)
    {
        int coppie = 0; // 1 e number non interessano
        long long int divisore = 2;
        while (divisore < number / divisore && coppie < 2)
        {
            if (number % divisore == 0)
            {
                ++coppie;
            }
            divisore++;
        }
        result = (coppie == 1) && (number != divisore * divisore);
    }
    return result;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param number il numero
/// @param result il risultato, cioè se il numero dato è il prodotto di due primi distinti
void showSolution(long long int number, bool result)
{
    if (result)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
}
