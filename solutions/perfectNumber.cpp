/*
 * Numero perfetto pari alla metà della somma dei suoi divisori
 * Author:  ER
 * Date:    2022/10/28
 * Note:
 */

/*
## perfectNumber
Scrivere un programma (perfectNumber) che dice se un numero intero positivo n è un numero perfetto.

Un numero si dice perfetto se è pari alla somma dei suoi divisori (escluso sé stesso).

(Ad es. 28 è perfetto perché i divisori di 28 sono 1,2,4,7,14[,28] e 1+2+4+7+14=28)

Es.: n = 20, output = NO; n = 28, output = YES
*/

#include <cstdio>

#define DEBUG 1

long long int getLLIntInRange(const char *prompt, long long int min, long long int max); // read a long long int in the range [min, max] from the keyboard
bool isPerfect(long long int number);                                                    // true iff number is a perfect number
void showSolution(long long int number, bool result);                                    // show problem and solution

int main(int argc, char *args[])
{
    // Acquisizione dati
    long long int number = getLLIntInRange("Immetti il numero: ", 1, (1LL << 62) - 1 + (1LL << 62)); // [1, 2^63 - 1]
    {
        // 1° metodo: ovvio
        // elaborazione
        bool result = isPerfect(number);
        // Visualizzazione risultato
        showSolution(number, result);
    }

    if (DEBUG)
    {
        printf("Test cases: \n");
        // Verifica casi di test
        showSolution(20, isPerfect(20));
        showSolution(6, isPerfect(6));
        showSolution(28, isPerfect(28));
        showSolution(9223372036854775807, isPerfect(9223372036854775807));
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

/// @brief Restituisce se il numero dato è un numero perfetto
/// @param number il numero
/// @return true se il numero dato è un numero perfetto
bool isPerfect(long long int number)
{
    bool result = number > 5; // 6 è il minimo numero perfetto
    if (result)
    {
        long long int somma = 1; // 1
        long long int divisore = 2;
        while (divisore < number / divisore && somma <= number)
        {
            if (number % divisore == 0)
            {
                somma += divisore;
                somma += number / divisore;
            }
            divisore++;
        }
        if (number == divisore * divisore)
        {
            somma += divisore;
        }
        result = somma == number;
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
