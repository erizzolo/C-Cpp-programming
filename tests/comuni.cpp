/*
 * Intersezione di intervalli
 * Author:  ER
 * Date:    2022/11/04
 * Note:    Il risultato, anche se min, max sono rappresentabili
 *          con dati di tipo int, può non esserlo, ad es.:
 *           con R1 = R2 = [-2000000000, 2000000000]
 *           l'output è 4000000001 !!!
 *          Usiamo per l'output dati di tipo long long
 */

/*
Numeri comuni (comuni)
Nell’insieme dei numeri interi sono dati due intervalli R1 = [min1, max1] ed
R2 = [min2, max2].
Scrivere un programma che, acquisiti da tastiera gli estremi (min, max) dei due
intervalli, determini quanti numeri interi appartengono ad entrambi gli
intervalli.
Assunzione: min1 <= max1 e min2 <= max2. I valori sono tutti rappresentabili
con dati di tipo int.
Formato di input: leggere da tastiera (senza controlli di validità) quattro interi
min1, max1, min2 e max2, separati da uno spazio, che rappresentano gli estremi
dei due intervalli.
Formato di output: un intero in formato decimale con il conteggio dei numeri
che soddisfano i criteri indicati.
Esempi:
| Input      | Output | Note                                   |
| ---------- | ------ | -------------------------------------- |
| -5 8 0 4   | 5      | I numeri cercati sono 5: 0, 1, 2, 3, 4 |
| -5 -5 0 10 | 0      | Nessuno                                |
| 0 6 -5 3   | 4      | I numeri cercati sono 4: 0, 1, 2, 3    |
*/
#include <cstdio>
#include <climits>

#define DEBUG 0

long long int getLLIntInRange(const char *prompt, long long int min, long long int max); // read a long long int in the range [min, max] from the keyboard
long long int comuniSlow(int min1, int max1, int min2, int max2);
long long int comuniFast(int min1, int max1, int min2, int max2);
void showSolution(int min1, int max1, int min2, int max2, long long int result); // show problem and solution

int main(int argc, char *args[])
{
    // Acquisizione dati
    printf("Immetti min1, max1, min2 e max2, separati da uno spazio: ");
    int min1 = getLLIntInRange("", INT_MIN, INT_MAX); // qualunque
    int max1 = getLLIntInRange("", min1, INT_MAX);    // garantisce min <= max !!!
    int min2 = getLLIntInRange("", INT_MIN, INT_MAX); // qualunque
    int max2 = getLLIntInRange("", min2, INT_MAX);    // garantisce min <= max !!!

    {
        // elaborazione
        long long int result = comuniSlow(min1, max1, min2, max2);
        // Visualizzazione risultato
        showSolution(min1, max1, min2, max2, result);
    }
    {
        // elaborazione
        long long int result = comuniFast(min1, max1, min2, max2);
        // Visualizzazione risultato
        showSolution(min1, max1, min2, max2, result);
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

long long int comuniSlow(int min1, int max1, int min2, int max2)
{
    long long int result = 0;
    int number = min1;
    while (number <= max1) // scansione primo intervallo
    {
        // test appartenenza ad intervallo [min2, max2]
        if ((min2 <= number) && (number <= max2))
        {
            if (DEBUG)
            {
                printf("%d ", number);
            }
            ++result;
        }
        ++number;
    }
    if (DEBUG)
    {
        printf("\n");
    }
    return result;
}

long long int comuniFast(int min1, int max1, int min2, int max2)
{
    long long int result = 0;
    // valori da comuni: intervallo [minComuni, maxComuni]
    // minComuni è il maggiore dei minimi
    int minComuni = min1 > min2 ? min1 : min2;
    // maxComuni è il minore dei massimi
    int maxComuni = max1 < max2 ? max1 : max2;
    // se l'intervallo non è vuoto conto i suoi elementi
    if (minComuni <= maxComuni)
    {
        // con cast a long long int del 1° termine ...
        long long int comuni = ((long long int)maxComuni) - minComuni + 1; // tutto intervallo Comuni
        result += comuni;
    }
    return result;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param result il risultato, cioè base ^ esponente
void showSolution(int min1, int max1, int min2, int max2, long long int result)
{
    printf("I numeri comuni a [%d, %d] e [%d, %d] sono %lld. \n", min1, max1, min2, max2, result);
}
