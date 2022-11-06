/*
 * Prodotto massimo di due interi positivi con somma data
 * Area massima del rettangolo a lati interi con semiperimetro dato
 * Author:  ER
 * Date:    2022/11/04
 * Note:
 */

/*
Prodotto massimo (prodotto)
È data la somma di due numeri interi positivi a e b.
Si chiede di calcolare il valore massimo che può assumere il loro prodotto.
Assunzione: 2 <= somma <= 10^9.
Formato di input: leggere da tastiera (senza controlli di validità) la somma dei
due numeri.
Formato di output: un intero in formato decimale che rappresenta il valore
massimo del prodotto di a e b.
Esempi:
| Input     | Output            | Note                                             |
| --------- | ----------------- | ------------------------------------------------ |
| 2         | 1                 | I due numeri sono per forza 1 e 1                |
| 15        | 56                | Il prodotto è massimo se i numeri valgono 7 e 8  |
| 20        | 100               | Il prodotto è massimo se i due numeri valgono 10 |
| 500000000 | 62500000000000000 |                                                  |
*/

#include <cstdio>
#include <climits>

#define DEBUG 1

long long int getLLIntInRange(const char *prompt, long long int min, long long int max); // read a long long int in the range [min, max] from the keyboard
long long int prodottoSlow(int somma);
long long int prodottoFast(int somma);
void showSolution(int somma, long long int result); // show problem and solution

int main(int argc, char *args[])
{
    // Acquisizione dati
    int somma = getLLIntInRange("Immetti la somma di a e b: ", 2, 1000000000); // 2 <= somma <= 10^9

    {
        // elaborazione
        long long int result = prodottoSlow(somma);
        // Visualizzazione risultato
        showSolution(somma, result);
    }
    {
        // elaborazione
        long long int result = prodottoFast(somma);
        // Visualizzazione risultato
        showSolution(somma, result);
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

long long int prodottoSlow(int somma)
{
    long long int result = 0;
    long long int minore = 1;
    while (minore < somma)
    {
        long long int prodotto = minore * (somma - minore);
        if (result < prodotto)
        {
            result = prodotto;
        }
        ++minore;
    }
    return result;
}

long long int prodottoFast(int somma)
{
    // NOTA: non immediato da dimostrare, ma
    // il massimo si ha per a = b = somma / 2
    // se somma non è pari, devo prendere i due interi più vicini
    long long int result = 0, sum = somma;
    if (sum % 2 == 0)
    {
        result = sum * sum / 4;
    }
    else
    {
        result = (sum / 2) * (sum / 2 + 1);
    }
    return result;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param result il risultato, cioè base ^ esponente
void showSolution(int somma, long long int result)
{
    printf("Il massimo prodotto di due interi positivi con somma %d e' %lld. \n", somma, result);
}
