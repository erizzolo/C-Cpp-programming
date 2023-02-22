/**
 * Esempio di implementazione ricorsiva di prodotti
 * NOTA BENE: valgono per i numeri naturali ...
 * Inoltre, se scompongo in base B (2, 3, ...) ho bisogno di B casi base!!!
 * NOTA BENISSIMO: sembra banale, ma non abbiamo sempre a disposizione un operazione di moltiplicazione...
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define DEBUG 1

#define TESTS 3        // number of tests
#define MAX_VALUE 1000 // maximum number to try

// basic numeric type
using number = int;

/// prototipi delle funzioni
number getNumber(const char *prompt = "Input n: "); /// acquisisce da tastiera un numero, con prompt dato
number prodRecTrivial(number a, number b);
number prodRecBinary(number a, number b);
number prodRecTernary(number a, number b);

/// the main function
int main(int argc, char *args[])
{
    srand(time(nullptr));
    for (int t = 0; t < TESTS; ++t)
    {
        number a = rand() % (MAX_VALUE + 1);
        number b = rand() % (MAX_VALUE + 1);
        cout << a << " * " << b << " = " << (a * b) << endl;
        number trivial = prodRecTrivial(a, b);
        cout << "prodRecTrivial(" << a << ", " << b << ") = " << trivial << endl;
        number binary = prodRecBinary(a, b);
        cout << "prodRecBinary(" << a << ", " << b << ") = " << binary << endl;
        number ternary = prodRecTernary(a, b);
        cout << "prodRecTernary(" << a << ", " << b << ") = " << ternary << endl;
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

// banale: a x 0 = 0 oppure a x b = a + a x (b - 1)
number prodRecTrivial(number a, number b)
{
    if (DEBUG)
    {
        cout << "--> prodRecTrivial(" << a << ", " << b << ")." << endl;
    }
    return b == 0 ? 0 : a + prodRecTrivial(a, b - 1);
}

// binaria: a x 0 = 0, a x 1 = a oppure a x b = (a + a) x (b / 2) + a x (b % 2)
// i.e. poiche' b = q * 2 + r, con q = b / 2 e r = b % 2, (a + a) * q + a * r = a * ( q * 2 + r) = a * b
number prodRecBinary(number a, number b)
{
    if (DEBUG)
    {
        cout << "--> prodRecBinary(" << a << ", " << b << ")." << endl;
    }
    switch (b)
    {
    case 0:
        return 0;
    case 1:
        return a;
    default:
        // return prodRecBinary(a + a, b / 2) + prodRecBinary(a, b % 2);
        return prodRecBinary(a + a, b >> 1) + prodRecBinary(a, b & 1);
    }
}
// ternaria: a x 0 = 0, a x 1 = a, a x 2 = a + a oppure a x b = (a + a + a) x (b / 3) + a x (b % 3)
// i.e. poiche' b = q * 3 + r, con q = b / 3 e r = b % 3, (a + a + a) * q + a * r = a * ( q * 3 + r) = a * b
number prodRecTernary(number a, number b)
{
    if (DEBUG)
    {
        cout << "--> prodRecTernary(" << a << ", " << b << ")." << endl;
    }
    switch (b)
    {
    case 0:
        return 0;
    case 1:
        return a;
    case 2:
        return a + a;
    default:
        return prodRecTernary(a + a + a, b / 3) + prodRecTernary(a, b % 3);
    }
}
