/*
 * Multipli di un numero dato in un intervallo
 * Author:  ER
 * Date:    2022/11/04
 * Note:    Il risultato, anche se min, max e n sono rappresentabili
 *          con dati di tipo int, può non esserlo, ad es.:
 *           con min = -2000000000, max = 2000000000, n = 1
 *           l'output è 4000000001 !!!
 *          Dovremmo usare per l'output dati di tipo long long
 */

/*
Multipli (multipli)
Nell’insieme dei numeri interi sono dati l’intervallo R = [min, max] ed un
numero n positivo.
Scrivere un programma che, acquisiti da tastiera gli estremi (min, max)
dell’intervallo ed il numero dato, determini quanti sono i numeri interi che
appartengono all’intervallo R e sono multipli del numero dato.
Assunzione: min <= max. I valori sono tutti rappresentabili con dati di tipo int.
Formato di input: leggere da tastiera (senza controlli di validità) gli interi min,
max ed n, separati da uno spazio.
Formato di output: un intero in formato decimale con il conteggio dei numeri
che soddisfano i criteri indicati.
Esempi:
| Input    | Output | Note           |
| -------- | ------ | -------------- |
| -5 9 3   | 5      | -3, 0, 3, 6, 9 |
| -5 -5 10 | 0      | Nessuno        |
| 0 0 13   | 1      | 0              |
*/
#include <cstdio>
#include <climits>

#define DEBUG 1

long long int getLLIntInRange(const char *prompt, long long int min, long long int max); // read a long long int in the range [min, max] from the keyboard
int multipliSlow(int min, int max, int n);
int multipliFast(int min, int max, int n);
void showSolution(int min, int max, int n, int result); // show problem and solution

int main(int argc, char *args[])
{
    // Acquisizione dati
    printf("Immetti min, max ed n, separati da uno spazio: ");
    int min = getLLIntInRange("", INT_MIN, INT_MAX); // qualunque
    int max = getLLIntInRange("", min, INT_MAX);     // garantisce min <= max !!!
    int n = getLLIntInRange("", 1, INT_MAX);         // positivo !!!

    {
        // elaborazione
        int result = multipliSlow(min, max, n);
        // Visualizzazione risultato
        showSolution(min, max, n, result);
    }
    {
        // elaborazione
        int result = multipliFast(min, max, n);
        // Visualizzazione risultato
        showSolution(min, max, n, result);
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

int multipliSlow(int min, int max, int n)
{
    int result = 0;
    while (min <= max)
    {
        if (min % n == 0)
        {
            if (DEBUG)
                printf("%d ", min);
            ++result;
        }
        ++min;
    }
    if (DEBUG)
        printf("\n");
    return result;
}

int multipliFast(int min, int max, int n)
{
    // NOTA: nella divisione, il quoziente viene arrotondato verso lo 0 !!!
    // il resto è sempre tale che dividendo = divisore * quoziente + resto
    // +10 : 7 = quoziente  1 e resto  3.  10 == 7 *  1 +  3 -> 1
    // -10 : 7 = quoziente -1 e resto -3. -10 == 7 * -1 + -3 -> 1
    int qmin = min / n, qmax = max / n;
    // ipotizzo siano compresi tutti i multipli da qmin * n a qmax * n
    int result = qmax - qmin + 1;
    // sistemo se qmin * n < min (ad esempio min 10, n 7, ma 1*7 < 10)
    if (qmin * n < min)
    {
        --result;
    }
    // sistemo se qmax * n > max (ad esempio max -10, n 7, ma -1*7 > -10)
    if (qmax * n > max)
    {
        --result;
    }
    return result;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param result il risultato, cioè base ^ esponente
void showSolution(int min, int max, int n, int result)
{
    printf("Nell'intervallo [%d, %d] vi sono %d multipli di %d. \n", min, max, result, n);
}
