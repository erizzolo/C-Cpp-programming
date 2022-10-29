/*
 * Potenza con base ed esponenti interi
 * Author:  ER
 * Date:    2022/10/28
 * Note:    versione "ovvia" e meno ovvia
 *          dati i limiti di input, uso long long int (__int128 non è standard...)
 */

/*
## Potenza (power)
Scrivere un programma che, dato un numero naturale base ed un numero naturale esponente, produca in output il valore della potenza base<sup>esponente</sup>.

Assunzione: base < 2·10^9, esponente < 2·10^9.

Formato di input: leggere da tastiera i numeri base ed esponente separati da spazi.

Formato di output: il valore della potenza base<sup>esponente</sup> in formato decimale.
Esempi:
| Input        | Output |
| ------------ | ------ |
| 0 9999999    | 0      |
| 1 19827789   | 1      |
| 1987653424 0 | 1      |
| 2 2          | 4      |
| 3 4          | 81     |

### Parti opzionali:
* contare il numero di moltiplicazioni effettuate (si può diminuire?)
* capire se il risultato ha provocato overflow
*/
#include <cstdio>

#define DEBUG 1

long long int getLLIntInRange(const char *prompt, long long int min, long long int max); // read a long long int in the range [min, max] from the keyboard
long long int powerSlow(long long int base, long long int exponent);                     // compute base ^ exponent
long long int powerFast(long long int base, long long int exponent);                     // compute base ^ exponent
void showSolution(long long int base, long long int exponent, long long int result);     // show problem and solution

// uso variabili globali per contare le operazioni
int moltiplicazioni, divisioni, sottrazioni;

int main(int argc, char *args[])
{
    // Acquisizione dati
    long long int base = getLLIntInRange("Immetti la base: ", 0, 1999999999);
    long long int esponente = getLLIntInRange("Immetti l'esponente: ", 0, 1999999999);

    // 0 ^ 0 in realtà non è definita ...

    {
        // 1° metodo: ovvio
        // elaborazione
        moltiplicazioni = divisioni = sottrazioni = 0;
        long long int potenza = powerSlow(base, esponente);
        // Visualizzazione risultato
        showSolution(base, esponente, potenza);
    }

    {
        // 2° metodo: DIVIDE ET IMPERA / DICOTOMIA
        // elaborazione
        moltiplicazioni = divisioni = sottrazioni = 0;
        long long int potenza = powerFast(base, esponente);
        // Visualizzazione risultato
        showSolution(base, esponente, potenza);
    }

    if (DEBUG)
    {
        printf("Test cases: \n");
        // Verifica casi di test
        showSolution(0, 9999999, powerFast(0, 9999999));
        showSolution(1, 19827789, powerFast(1, 19827789));
        showSolution(1987653424, 0, powerFast(1987653424, 0));
        showSolution(2, 2, powerFast(2, 2));
        showSolution(3, 4, powerFast(3, 4));
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

/// @brief Restituisce base ^ exponent (slow version)
/// @param base la base
/// @param exponent l'esponente
/// @return il valore della potenza base ^ exponent
long long int powerSlow(long long int base, long long int exponent)
{
    long long int result = 1;
    while (exponent > 0)
    {
        result *= base;
        ++moltiplicazioni;
        --exponent;
        ++sottrazioni;
    }
    return result;
}

/// @brief Restituisce base ^ exponent (fast version)
/// @param base la base
/// @param exponent l'esponente
/// @return il valore della potenza base ^ exponent
long long int powerFast(long long int base, long long int exponent)
{
    // per i commenti uso b ed e per i valori "originali"
    long long int result = 1, b = base, e = exponent;
    // all'inizio vale la precondizione:
    // b ^ e = result * base ^ exponent = 1 * b ^ e
    while (exponent > 0)
    {
        if (DEBUG)
        {
            printf("result = %lld, b = %lld, e = %lld \n", result, base, exponent);
        }
        // b ^ e = b * (b^2)^(e/2) per e dispari    e.g. 3^15 = 3 * (3^2)^(15/2) = 3 * 9^7
        // b ^ e =     (b^2)^(e/2) per e pari       e.g. 3^16 =     (3^2)^(16/2) =     9^8
        if (exponent % 2 == 1)
        {
            result *= base;
            ++moltiplicazioni;
        }
        base *= base; // elevo base al quadrato
        ++moltiplicazioni;
        exponent /= 2; // dimezzo exponent (13 /= 2 diventa 6)
        ++divisioni;
        // anche qui vale la condizione:
        // b ^ e = result * base ^ exponent
    }
    return result;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param base la base
/// @param exponent l'esponente
/// @param result il risultato, cioè base ^ esponente
void showSolution(long long int base, long long int exponent, long long int result)
{
    printf("%lld ^ %lld = %lld (%d *, %d /2, %d -1) \n", base, exponent, result, moltiplicazioni, divisioni, sottrazioni);
}
