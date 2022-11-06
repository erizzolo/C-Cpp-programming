/*
 * Resto massimo della divisione tra due numeri positivi di somma data
 * Author:  ER
 * Date:    2022/11/05
 * Note:
 */

/*
Resto massimo (residuo)
È data la somma di due numeri interi positivi a e b, con a >= b.
Si chiede di calcolare il valore massimo che può assumere il resto della
divisione tra a e b.
Assunzione: 2 <= somma <= 10^9.
Formato di input: leggere da tastiera (senza controlli di validità) la somma dei
due numeri.
Formato di output: un intero in formato decimale che rappresenta il valore
massimo del resto della divisione tra a e b.
Esempi:
| Input     | Output    | Note                                                |
| --------- | --------- | --------------------------------------------------- |
| 2         | 0         | I due numeri sono per forza 1 e 1: 1/1 dà resto 0   |
| 15        | 3         | Il resto è massimo per a = 11, b = 4 o a = 9, b = 6 |
| 20        | 6         | Il resto è massimo per a = 13, b = 7                |
| 500000000 | 166666666 | ... per a = 333333333, b = 7333333333               |
*/

#include <cstdio>
#include <climits>

#define DEBUG 0

int tests; // variabile globale per conteggio test effettuati

long long int getLLIntInRange(const char *prompt, long long int min, long long int max); // read a long long int in the range [min, max] from the keyboard
int residuoSlowest(int sum);
int residuoSlow(int sum);
int residuoFast(int sum);
void showSolution(int sum, int result); // show problem and solution

int main(int argc, char *args[])
{
    // Acquisizione dati
    int sum = getLLIntInRange("Immetti la somma: ", 2, 1999999999);

    {
        // 1° metodo: ovvio
        // elaborazione
        tests = 0;
        int result = residuoSlowest(sum);
        // Visualizzazione risultato
        showSolution(sum, result);
    }

    {
        // 2° metodo: evita tests inutili
        // elaborazione
        tests = 0;
        int result = residuoSlow(sum);
        // Visualizzazione risultato
        showSolution(sum, result);
    }

    {
        // 3° metodo: 1 solo test
        // elaborazione
        tests = 0;
        int result = residuoFast(sum);
        // Visualizzazione risultato
        showSolution(sum, result);
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
    long long int result;
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

int residuoSlowest(int sum)
{
    // forza bruta per b = 2 ... sum / 2 (dividere per 1 dà resto 0)
    int result = 0;
    int a = sum - 2, b = 2;
    while (a > b) // a == b dà resto 0
    {
        ++tests; // incremento tests effetuati
        int resto = a % b;
        // if (DEBUG && resto >= result)
        if (DEBUG)
        {
            printf("result = %d, a = %d, b = %d, quoziente = %d, resto = %d %s\n", result, a, b, a / b, resto, result <= resto ? "*" : "");
        }
        if (result < resto)
        {
            result = resto;
        }
        --a;
        ++b;
    }
    return result;
}

int residuoSlow(int sum)
{
    // forza bruta per b = sum / 2 ... 2 (dividere per 1 dà resto 0)
    // ma interrompo ricerca quando b - 1 <= result
    // (resto non può essere maggiore di result)
    int result = 0;
    int a = (sum + 2) / 2, b = (sum - 1) / 2;
    // per sum = 2k (pari): a = k + 1, b = k - 1
    // per sum = 2k + 1 (dispari): a = k + 1, b = k
    while ((b > 1) && (b - 1 > result))
    {
        ++tests; // incremento tests effetuati
        int resto = a % b;
        // if (DEBUG && resto >= result)
        if (DEBUG)
        {
            printf("result = %d, a = %d, b = %d, quoziente = %d, resto = %d %s\n", result, a, b, a / b, resto, result <= resto ? "*" : "");
        }
        if (result < resto)
        {
            result = resto;
        }
        ++a;
        --b;
    }
    return result;
}

int residuoFast(int sum)
{
    // Si cerca il resto massimo della divisione di a = (somma - b) per b
    // con a >= b, ovvero somma - b >= b, quindi b <= somma / 2.
    // Si esclude il caso di uguaglianza perché in tal caso il resto è 0
    // quindi b < somma / 2 e di conseguenza a > somma / 2.
    // Il resto della divisione per b (intero positivo) è in [0, b - 1].
    // Detto q il quoziente di (somma - b) / b,
    // si ha resto = (somma - b) - q * b = somma - (q + 1) * b.
    // Per un dato valore di q, il resto è massimo per b minimo, cioè per
    // b = minimo b tale che (somma - b) / b < q + 1
    // (altrimenti il quoziente sarebbe q + 1 e non q).
    // Allora somma - b < b * (q + 1) cioè somma < b * (q + 2)
    // quindi per b minimo = somma / (q + 2) + 1.
    // Ad es. con somma = 20, il b minimo per cui q = 1 è 7
    // infatti (20 - 6) / 6 = 14 / 6 dà q 2 (e resto 2)
    // mentre (20 - 7) / 7 = 13 / 7 dà q 1 (e resto 6)
    // Considerando il caso di q = 1 si ha che:
    // b minimo = somma / 3 + 1
    // I vari casi di somma % 3 (con k = somma / 3) sono:
    // (b minimo = k + 1, tra () il resto ottenuto)
    // somma % 3 = 0, per somma = 3k:
    // a = 2k - 1, b = k + 1: 2k - 1 =  k + 1 + (k - 2)
    // a = 2k    , b = k    : 2k     = 2k     + (0)
    // a = 2k + 1, b = k - 1: (inutile)
    // somma % 3 = 1, per somma = 3k + 1:
    // a = 2k    , b = k + 1: 2k     =  k + 1 + (k - 1)
    // a = 2k + 1, b = k    : (inutile)
    // somma % 3 = 2, per somma = 3k + 2:
    // a = 2k + 1, b = k + 1: 2k + 1 =  k + 1 + (k)
    // a = 2k + 2, b = k    : (inutile)
    // Attenzione ai casi particolari per k = 0, 1
    // somma = 2 = 0 * 3 + 2: resto max = k     =  0 (ok!)
    // somma = 3 = 1 * 3 + 0: resto max = k - 2 = -1 (NO!)
    // somma = 4 = 1 * 3 + 1: resto max = k - 1 =  0 (ok!)
    // somma = 5 = 1 * 3 + 2: resto max = k     =  1 (ok!)
    // con somma >= 2 * 3 = 6 non ci sono problemi
    int result = 0;
    ++tests; // considero questo un test...
    int sumModulo3 = sum % 3, k = sum / 3;
    if (sumModulo3 == 0)
    {
        result = (k - 2) > 0 ? k - 2 : 0;
    }
    else if (sumModulo3 == 1)
    {
        result = k - 1;
    }
    else
    {
        result = k;
    }
    return result;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param sum la somma di a e b
/// @param result il risultato, cioè il massimo residuo di a / b
void showSolution(int sum, int result)
{
    printf("Il resto massimo con somma = %d \212 %d (%d tests) \n", sum, result, tests);
}
