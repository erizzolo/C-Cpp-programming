/**
 * Esempio di overload / signature / default parameters di una funzione
 *
 * Il C++ consente l'overload delle funzioni (e di altro...).
 * Ciò significa che vi possono essere più funzioni con lo stesso nome,
 * anche nello stesso namespace.
 * Naturalmente tali funzioni devono essere distinguibili in base a qualcosa
 * di diverso dal nome, ovvero la lista dei parametri.
 * Quindi se due funzioni nello stesso namespace hanno lo stesso nome,
 * il numero e/o il tipo dei parametri dovrà essere diverso!
 * Il namespace, il nome e la lista dei tipi dei parametri costituiscono la
 * firma della funzione (signature).
 * Non possono esistere più funzioni con la stessa firma !!!
 * N.B. - Per le funzioni il tipo restituito NON fa parte della firma!!!
 * Attenzione: il C++ consente anche di specificare parametri opzionali
 * con valori di default, che non è necessario specificare alla chiamata
 * se non si desidera.
 * Questo metodo è addirittura consigliato rispetto all'overload, se si può!
 * F.51: Where there is a choice, prefer default arguments over overloading
 * https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-default-args
 * Open question: Che effetto hanno i parametri opzionali sulla firma ???
 */

#include <iostream>

using namespace std;

#define DEBUG 1

// prototipi delle funzioni
// due overload leciti
long long int getNumber();                   // acquisisce da tastiera un numero ll
long long int getNumber(const char *prompt); // acquisisce da tastiera un numero ll, con prompt dato
// un overload non lecito (cambia solo il tipo restituito)
// int getNumber();                          // error: ambiguating new declaration of ‘int getNumber()’
// due overload leciti
void printBinary(long long int);               // stampa a video il numero dato, in binario
void printBinary(long long int, bool newLine); // stampa a video il numero dato, in binario con eventuale newline
// un overload non lecito (cambia solo il tipo restituito)
// int printBinary(long long int); // error: ambiguating new declaration of ‘int printBinary(long long int)’

// i due overload precedenti potrebbero essere sostituiti da un'unica funzione con parametro opzionale
void printBin(long long int, bool newLine = false); // stampa a video il numero dato, in binario con eventuale newline (default senza)

// the main function
int main(int argc, char *args[])
{
    // input: un numero intero
    long long int n = getNumber();
    // verifica
    cout << "n = " << n << endl;
    // stampa in binario del numero acquisito
    printBinary(n);
    // just in case ...
    cout << endl;
    // con gli overload
    // input: un numero intero non negativo
    char prompt[] = "Dammi il numero: ";
    long long int m = getNumber(prompt);
    // verifica
    cout << "m = " << m << endl;
    // stampa in binario del numero acquisito
    printBinary(m, true);
    // use of default parameters
    printBin(n); // same as printBin(n, false);
    cout << " + ";
    printBin(m); // same as printBin(m, false);
    cout << " = ";
    printBin(n + m, true);
    // successful termination
    return 0;
}

/**
 * acquisisce da tastiera un numero ll
 * @return  il numero acquisito da tastiera (si spera)
 */
long long int getNumber()
{
    // è comune dichiarare una variabile per il risultato
    long long int result;
    // input: un numero intero non negativo
    cout << "Immetti un numero intero: ";
    cin >> result;
    // restituisce il dato acquisito
    return result;
}

/**
 * acquisisce da tastiera un numero ll, con prompt dato
 * @param   prompt  il messaggio per l'utente
 * @return  il numero acquisito da tastiera (si spera)
 */
long long int getNumber(const char *prompt)
{
    // è comune dichiarare una variabile per il risultato
    long long int result;
    // input: un numero intero non negativo
    cout << prompt;
    cin >> result;
    // restituisce il dato acquisito
    return result;
}

/**
 * stampa a video il numero dato, in binario
 * @param   number   il numero da stampare
 */
void printBinary(long long int number)
{
    unsigned long long int mask = 1ULL << (sizeof(mask) * 8 - 1); // MSbit
    bool significant = false; // 0 non significant
    while (mask > 0)
    {
        if ((number & mask) == 0)
        {
            if (significant)
                cout << "0";
        }
        else
        {
            cout << "1";
            significant = true;
        }
        mask >>= 1; // next less significant bit
    }
}

/**
 * stampa a video il numero dato, in binario con eventuale newline
 * @param   number  il numero da stampare
 * @param   newLine va a capo se true
 */
void printBinary(long long int number, bool newLine)
{
    printBinary(number);
    if (newLine)
    {
        cout << endl;
    }
}

/**
 * stampa a video il numero dato, in binario con eventuale newline
 * @param   number  il numero da stampare
 * @param   newLine va a capo se true (default false)
 */
void printBin(long long int number, bool newLine /* = false */)
{
    unsigned long long int mask = 1ULL << (sizeof(mask) * 8 - 1); // MSbit
    bool significant = false; // 0 non significant
    while (mask > 0)
    {
        if ((number & mask) == 0)
        {
            if (significant)
                cout << "0";
        }
        else
        {
            cout << "1";
            significant = true;
        }
        mask >>= 1; // next less significant bit
    }
    if (newLine)
    {
        cout << endl;
    }
}
