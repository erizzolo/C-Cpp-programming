/*
 * Il postulato di Bertrand
 * Author:  ER
 * Date:    2022/11/05
 * Note:    Should be done with Eratostene's sieve
 *          but we don't know about arrays, let alone bitmaps :-(
 *          The solution is included anyway...
 */

/*
## Il postulato di Bertrand (bertrand)
Descrizione del problema
Un numero intero x > 1 è detto numero primo se ha due soli divisori: 1 e x
stesso. Come è noto, 2, 3, 5, 7, 11 e 13 sono numeri primi mentre 15 non lo è
in quanto divisibile per 3.
La versione debole del postulato di Bertrand (che in realtà è il teorema
Bertrand-Chebyshev) afferma che, per ogni intero n > 1, esiste sempre almeno
un numero primo p tale che n < p < 2n.
Questa relazione è stata ipotizzata per la prima volta da Bertrand, che la
verificò personalmente per tutti i numeri n nell'intervallo 2 <= n <= 3∙10^6. La
relazione fu poi definitivamente dimostrata da Chebyshev.
Il compito che questo problema propone è un po' più ampio: scrivere un
programma che riceve un intero n > 1 e stabilisce quanti numeri primi p sono
compresi nell'intervallo n < p < 2n.
Assunzione: 2 ≤ n ≤ 3000.
Formato di input: leggere il numero da tastiera (senza controlli di validità)
Formato di output: il risultato richiesto, che rappresenta quanti numeri primi p
sono compresi nell'intervallo n < p < 2n, in forma decimale.
Esempi:
| Input | Output |
| ----- | ------ |
| 2     | 1      |
| 239   | 39     |
Autore/i
A.S. Stankevich, ACM ICPC Team, St. Petersburg State University of Information
*/

#include <cstdio>
#include <ctime>
#include <cstdlib>

#define DEBUG 1

long long int getLLIntInRange(const char *prompt, long long int min, long long int max); // read a long long int in the range [min, max] from the keyboard
int bertrandSlow(int number);                                                            // prime count
int bertrandFast(int number);                                                            // prime count
int bertrandSieveArray(int number);                                                      // prime count
void showSolution(int number, int result, double duration);                              // show problem and solution

// uso variabili globali per contare le operazioni
long long int tests;

int main(int argc, char *args[])
{
    // Acquisizione dati
    int number = getLLIntInRange("Immetti il numero: ", 2, 300000000);

    {
        // 1° metodo: ovvio
        // elaborazione
        tests = 0;
        clock_t startTime = clock(); // read clock
        // block to be timed
        int bertrand = bertrandSlow(number);
        // end of block to be timed
        clock_t endTime = clock(); // read clock again
        double duration = 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC;
        // Visualizzazione risultato
        showSolution(number, bertrand, duration);
    }

    {
        // 2° metodo: evito ripetizioni ...
        // elaborazione
        tests = 0;
        clock_t startTime = clock(); // read clock
        // block to be timed
        int bertrand = bertrandFast(number);
        // end of block to be timed
        clock_t endTime = clock(); // read clock again
        double duration = 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC;
        // Visualizzazione risultato
        showSolution(number, bertrand, duration);
    }

    {
        // 3° metodo: sieve ...
        // elaborazione
        tests = 0;
        clock_t startTime = clock(); // read clock
        // block to be timed
        int bertrand = bertrandSieveArray(number);
        // end of block to be timed
        clock_t endTime = clock(); // read clock again
        double duration = 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC;
        // Visualizzazione risultato
        showSolution(number, bertrand, duration);
    }

    if (DEBUG)
    {
        printf("Test cases: \n");
        tests = 0;
        // Verifica casi di test
        showSolution(2, bertrandFast(2), 0);
        showSolution(239, bertrandFast(239), 0);
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

/// @brief Restituisce quanti primi sono compresi in ]n, 2n[ (slow version)
/// @param number il numero
/// @return quanti primi sono compresi in ]n, 2n[
int bertrandSlow(int number)
{
    int result = 0, test = 2 * number - 1;
    while (test > number)
    {
        bool prime = true;
        int factor = 2;
        while (factor <= test / factor && prime)
        {
            prime = test % factor != 0;
            ++factor;
        }
        if (prime)
        {
            ++result;
        }
        --test;
    }
    return result;
}

int sqrt(int number)
{
    int result = 0, step = 1 << 15;
    while (step > 0)
    {
        int test = result + step;
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
bool isPrimeFast(int number)
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

/// @brief Restituisce true se number è primo, false altrimenti (fast version)
/// @param number il numero
/// @return quanti primi sono compresi in ]n, 2n[
int bertrandFast(int number)
{
    int result = 0, test = 2 * number - 1;
    int limit = sqrt(test);    // first limit
    int until = limit * limit; // limit is valid until test >= until
    while (test > number)
    {
        bool prime = true;
        int factor = 2;
        while (factor <= limit && prime)
        {
            prime = test % factor != 0;
            ++factor;
        }
        if (prime)
        {
            ++result;
        }
        --test;
        if (test < limit)
        {
            --limit;               // next limit
            until = limit * limit; // limit is valid until test >= until
        }
    }
    return result;
}

/// @brief Restituisce quanti primi sono compresi in ]n, 2n[ (sieve version)
/// @param number il numero
/// @return quanti primi sono compresi in ]n, 2n[
int bertrandSieveArray(int number)
{
    int result = 0;
    // consider only odd numbers composite[flag] refers to possible prime = 2flag + 1
    bool *composite = (bool *)calloc(number, sizeof(bool));
    int flag = 1;                     // first prime = 3
    int limit = sqrt(2 * number) / 2; // primes up to sqrt(2*number)
    while (flag <= limit)
    {
        if (!composite[flag])
        {
            int prime = 2 * flag + 1; // 2flag + 1 is a prime
            // first (unmarked) multiple = prime^2
            int multipleFlag = prime * prime / 2;
            while (multipleFlag < number)
            {
                composite[multipleFlag] = true;
                multipleFlag += prime; // +2prime
            }
        }
        ++flag;
    }
    // first useful flag: first odd > n
    flag = (number + 1) / 2;
    // first flag past the useful ones: first odd > 2n = 2n + 1
    limit = number;
    while (flag < number)
    {
        if (!composite[flag])
        {
            ++result;
        }
        ++flag;
    }
    free(composite);
    return result;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param number il numero
/// @param result il risultato, cioè quanti primi sono compresi in ]n, 2n[
/// @param duration la durata dell'elaborazione in ms
void showSolution(int number, int result, double duration)
{
    printf("in ]%d, %d[ there are %d primes (%f ms)\n", number, 2 * number, result, duration);
}
