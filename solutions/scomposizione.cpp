/*
 * Scomposizione in fattori primi
 * Author:  ER
 * Date:    2023/02/16
 * Note:
 */

/*
    2. Scomposizione (scomposizione)
       Dato il tipo numerico number, opportunamente definito ad esempio con:
            using number = number;
       si definiscano le struct:
        ◦ couple con due membri di tipo number, fattore ed esponente;
        ◦ scomposizione, con membri un array di couple di opportune dimensioni, coppie,  ed uno  di tipo size_t, numCoppie, inizializzato a zero.
       Realizzare una funzione con il seguente prototipo:
            scomposizione scomponi(number n);
       che restituisca una struct scomposizione rappresentante la scomposizione in fattori primi del numero naturale positivo n.
       Realizzare una funzione con il seguente prototipo:
            number ricomponi(const scomposizione &s);
       che restituisca il valore del numero corrispondente alla scomposizione in fattori primi specificata come parametro (che si suppone valida).
       Realizzare un’applicazione per la verifica delle funzioni realizzate.
*/

#include <iostream>
#include <limits>

using namespace std;

const bool DEBUG = true;

#define MAX_COUPLES 15

using number = unsigned long long int;

struct couple
{
    number fattore, esponente;
};
struct scomposizione
{
    couple coppie[MAX_COUPLES];
    size_t numCoppie{0};
};

scomposizione scomponi(number n);
number ricomponi(const scomposizione &s);
void print(const couple &c, ostream &out = cout);
void print(const scomposizione &s, ostream &out = cout);

void test(number original)
{
    scomposizione s = scomponi(original);
    print(s);
    cout << endl;
    number n = ricomponi(s);
    cout << "original = " << original << ", n = " << n << endl;
}

int main(int argc, char *argv[])
{
    test(126738495);
    test(1);
    test(121);
    test(64);
    test(2*3*5*7*11*13*17*19);

    return 0;
}

scomposizione scomponi(number n)
{
    scomposizione result;

    number fattore = 2; // minimo numero primo
    while (fattore <= n / fattore)
    {
        number esponente = 0;
        while (n % fattore == 0)
        {
            n /= fattore;
            ++esponente;
        }
        if (esponente > 0) // found !!!
        {
            result.coppie[result.numCoppie] = {fattore, esponente};
            ++result.numCoppie;
        }
        ++fattore; // fattore successivo
    }
    // caso di ulteriore fattore primo
    if (n > 1)
    {
        result.coppie[result.numCoppie] = {n, 1};
        ++result.numCoppie;
    }
    return result;
}

number powerFast(number base, number exponent)
{
    number result = 1, b = base, e = exponent;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result *= base;
        }
        base *= base;  // elevo base al quadrato
        exponent /= 2; // dimezzo exponent (13 /= 2 diventa 6)
    }
    return result;
}

number ricomponi(const scomposizione &s)
{
    number result = 1;
    for (size_t i = 0; i < s.numCoppie; i++)
    {
        result *= powerFast(s.coppie[i].fattore, s.coppie[i].esponente);
    }
    return result;
}

void print(const couple &c, ostream &out /* = cout */)
{
    out << c.fattore << "^" << c.esponente;
}

void print(const scomposizione &s, ostream &out /* = cout */)
{
    for (size_t i = 0; i < s.numCoppie; i++)
    {
        if (i != 0)
        {
            out << " x ";
        }
        print(s.coppie[i], out);
    }
}
