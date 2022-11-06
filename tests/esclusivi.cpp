/*
 * Differenza di intervalli
 * Author:  ER
 * Date:    2022/11/04
 * Note:    Il risultato, anche se min, max sono rappresentabili
 *          con dati di tipo int, può non esserlo, ad es.:
 *           con R1 = [-2000000000, 2000000000], R2 = [0,0]
 *           l'output è 4000000000 !!!
 *          Dovremmo usare per l'output dati di tipo long long
 */

/*
Numeri esclusivi (esclusivi)
Nell’insieme dei numeri interi sono dati due intervalli R1 = [min1, max1] ed
R2 = [min2, max2].
Scrivere un programma che, acquisiti da tastiera gli estremi (min, max) dei due
intervalli, determini quanti numeri interi appartengono al primo intervallo ma
non al secondo.
Assunzione: min1 <= max1 e min2 <= max2. I valori sono tutti rappresentabili
con dati di tipo int.
Formato di input: leggere da tastiera (senza controlli di validità) quattro interi
min1, max1, min2 e max2, separati da uno spazio, che rappresentano gli estremi
dei due intervalli.
Formato di output: un intero in formato decimale con il conteggio dei numeri
che soddisfano i criteri indicati.
Esempi:
| Input        | Output | Note                                                    |
| ------------ | ------ | ------------------------------------------------------- |
| -5 8 0 4     | 9      | I numeri cercati sono 9: -5, -4, -3, -2, -1, 5, 6, 7, 8 |
| -5 -5 -10 10 | 0      | Nessuno                                                 |
| 0 6 -5 3     | 3      | I numeri cercati sono 3: 4, 5, 6                        |
*/
#include <cstdio>
#include <climits>

#define DEBUG 0

long long int getLLIntInRange(const char *prompt, long long int min, long long int max); // read a long long int in the range [min, max] from the keyboard
int esclusiviSlow(int min1, int max1, int min2, int max2);
int esclusiviFast(int min1, int max1, int min2, int max2);
void showSolution(int min1, int max1, int min2, int max2, int result); // show problem and solution

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
        int result = esclusiviSlow(min1, max1, min2, max2);
        // Visualizzazione risultato
        showSolution(min1, max1, min2, max2, result);
    }
    {
        // elaborazione
        int result = esclusiviFast(min1, max1, min2, max2);
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

int esclusiviSlow(int min1, int max1, int min2, int max2)
{
    int result = 0, number = min1;
    while (number <= max1) // scansione primo intervallo
    {
        // test non appartenenza ad intervallo [min2, max2]
        if ((number < min2) || (number > max2))
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

int esclusiviFast(int min1, int max1, int min2, int max2)
{
    int result = max1 - min1 + 1; // tutto intervallo 1
    // valori da escludere: intervallo [minEsclusi, maxEsclusi]
    // minEsclusi è il maggiore dei minimi
    int minEsclusi = min1 > min2 ? min1 : min2;
    // maxEsclusi è il minore dei massimi
    int maxEsclusi = max1 < max2 ? max1 : max2;
    // se l'intervallo non è vuoto sottraggo i suoi elementi
    if (minEsclusi <= maxEsclusi)
    {
        int esclusi = maxEsclusi - minEsclusi + 1; // tutto intervallo Esclusi
        result -= esclusi;
    }
    return result;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param result il risultato, cioè base ^ esponente
void showSolution(int min1, int max1, int min2, int max2, int result)
{
    printf("I numeri in [%d, %d] ma non in [%d, %d] sono %d. \n", min1, max1, min2, max2, result);
}
