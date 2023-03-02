/**
 * Esempio di implementazione ricorsiva di funzioni
 * I casi classici: fattoriale, fibonacci, ...
 * GOOD LUCK !!!
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define DEBUG 0

#define TESTS 3      // number of tests
#define MAX_VALUE 20 // maximum number to try

unsigned long long int calls[MAX_VALUE + 1];

// basic numeric type
using number = unsigned long long int;

/// prototipi delle funzioni
number getNumber(const char *prompt = "Input n: "); /// acquisisce da tastiera un numero, con prompt dato
number fattorialeIterativo(number n);
number fattorialeRicorsivo(number n);
number fibonacciIterativo(number n);
number fibonacciRicorsivo(number n);
number fibonacciRicorsivoMemoization(number n);
void resetCalls();

/// the main function
int main(int argc, char *args[])
{
    srand(time(nullptr));
    for (int t = 0; t < TESTS; ++t)
    {
        number n = rand() % (MAX_VALUE + 1);
        cout << "Test #" << t << ": n = " << n << endl;
        {
            clock_t startTime = clock(); // read clock
            number fattIter = fattorialeIterativo(n);
            clock_t endTime = clock(); // read clock again
            double duration = 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC;
            cout << n << "! (iterativo) = " << fattIter << " in " << duration << endl;
        }
        {
            clock_t startTime = clock(); // read clock
            number fattRec = fattorialeRicorsivo(n);
            clock_t endTime = clock(); // read clock again
            double duration = 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC;
            cout << n << "! (ricorsivo) = " << fattRec << " in " << duration << endl;
        }
        {
            clock_t startTime = clock(); // read clock
            number fibIter = fibonacciIterativo(n);
            clock_t endTime = clock(); // read clock again
            double duration = 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC;
            cout << "Fib(" << n << ") (iterativo) = " << fibIter << " in " << duration << endl;
        }
        {
            resetCalls();
            clock_t startTime = clock(); // read clock
            number fibRec = fibonacciRicorsivo(n);
            clock_t endTime = clock(); // read clock again
            double duration = 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC;
            cout << "Fib(" << n << ") (ricorsivo) = " << fibRec << " in " << duration << endl;
            for (int i = 0; i < MAX_VALUE + 1; ++i)
            {
                cout << "fibonacciRicorsivo(" << i << ") calls: " << calls[i] << endl;
            }
        }
        {
            resetCalls();
            clock_t startTime = clock(); // read clock
            number fibRec = fibonacciRicorsivoMemoization(n);
            clock_t endTime = clock(); // read clock again
            double duration = 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC;
            cout << "Fib(" << n << ") (ricorsivo con memoization) = " << fibRec << " in " << duration << endl;
            for (int i = 0; i < MAX_VALUE + 1; ++i)
            {
                cout << "fibonacciRicorsivoMemoization(" << i << ") calls: " << calls[i] << endl;
            }
        }
    }
    /// successful termination
    return 0;
}

/**
 * acquisisce da tastiera un numero, con prompt dato
 * @param   prompt  il messaggio per l'utente
 * @return  il numero acquisito da tastiera (si spera)
 */
number getNumber(const char *prompt /* = "Input n: " */)
{
    /// è comune dichiarare una variabile per il risultato
    number result;
    /// input: un numero intero non negativo
    cout << prompt;
    cin >> result;
    /// restituisce il dato acquisito
    return result;
}

number fattorialeIterativo(number n)
{
    number result = 1;
    for (number factor = 2; factor <= n; ++factor)
    {
        result *= factor;
    }
    return result;
}

number fattorialeRicorsivo(number n)
{
    if (DEBUG)
    {
        cout << "--> fattorialeRicorsivo(" << n << ")." << endl;
    }
    return n < 2 ? 1 : n * fattorialeRicorsivo(n - 1);
}

number fibonacciIterativo(number n)
{
    if (n < 2)
    {
        return n;
    }
    else
    {
        number k = 2;               // current
        number f_k_2 = 0;           // f[k-2]
        number f_k_1 = 1;           // f[k-1]
        number f_k = f_k_1 + f_k_2; // f[k]
        while (k < n)
        {
            // compute next
            k++;
            f_k_2 = f_k_1;
            f_k_1 = f_k;
            f_k = f_k_1 + f_k_2;
        }
        return f_k;
    }
}

number fibonacciRicorsivo(number n)
{
    calls[n]++;
    if (DEBUG)
    {
        cout << "--> fibonacciRicorsivo(" << n << ")." << endl;
    }
    return n < 2 ? n : fibonacciRicorsivo(n - 1) + fibonacciRicorsivo(n - 2);
}

number fibonacciRicorsivoMemoization(number n)
{
    static number soluzioni[MAX_VALUE + 1];
    calls[n]++;
    if (DEBUG)
    {
        cout << "--> fibonacciRicorsivoMemoization(" << n << ")." << endl;
    }
    if (n < 2)
        return n;
    if (soluzioni[n] == 0)
    { // not solved yet
        soluzioni[n] = fibonacciRicorsivoMemoization(n - 1) + fibonacciRicorsivoMemoization(n - 2);
    }
    return soluzioni[n];
}

void resetCalls()
{
    // reset calls
    for (int i = 0; i < MAX_VALUE + 1; ++i)
        calls[i] = 0;
}