/*
 * Scomposizione in fattori primi
 * Author:  ER
 * Date:    2023/02/16
 * Note:
 */

/*
Numero di divisori (divisori)
Con le stesse definizioni dell’esercizio precedente, realizzare le funzioni con il
seguente prototipo:
size_t divisori(number n);
size_t divisori(const scomposizione &s);
che restituiscano il numero di divisori rispettivamente del numero naturale
positivo n, e del numero naturale positivo la cui scomposizione in fattori primi è
specificata come parametro (che si suppone valida).
Realizzare un’applicazione per la verifica delle funzioni realizzate.
*/

#include <iostream>
#include <limits>

using namespace std;

const bool DEBUG = true;

#define MAX_COUPLES 15
#define MAX_DIVISORI 5000

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

number divisors[MAX_DIVISORI];

scomposizione scomponi(number n);
number ricomponi(const scomposizione &s);
void print(const couple &c, ostream &out = cout);
void print(const scomposizione &s, ostream &out = cout);
size_t divisori(number n);
size_t divisori(const scomposizione &s);
void getDivisori(number n, number d[], size_t &num);

/// @brief Output su out in formato JSON da begin a end escluso: [begin, end)
/// @param a     the array to output
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
/// @param out   the output stream to be used
void JSON(const number a[], int end, int begin = 0, ostream &out = cout)
{
    out << "[ ";
    for (int i = begin; i < end; ++i)
    {
        if (i != begin)
            out << ", ";
        out << a[i];
    }
    out << " ]";
}

void test(number original)
{
    scomposizione s = scomponi(original);
    print(s);
    cout << endl;
    number n = ricomponi(s);
    cout << "original = " << original << ", n = " << n << endl;
    cout << "Divisori di " << original << ": " << divisori(original) << endl;
    size_t divs = 0;
    getDivisori(original, divisors, divs);
    JSON(divisors, divs);
    cout << endl;
}

int main(int argc, char *argv[])
{
    test(126738495);
    test(1);
    test(121);
    test(64);
    test(2 * 3 * 5 * 7 * 11 * 13 * 17 * 19);

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
size_t divisori(number n)
{
    return divisori(scomponi(n));
}

size_t divisori(const scomposizione &s)
{
    size_t result = 1;
    for (size_t i = 0; i < s.numCoppie; i++)
    {
        result *= s.coppie[i].esponente + 1;
    }
    return result;
}

void getDivisoriHelp(const scomposizione &s, size_t fattoriRestanti, number divisors[], size_t &num, number product)
{
    if (fattoriRestanti == 0)
    {
        divisors[num] = product; // no more factors, product is a divisor
        num++;
    }
    else
    {
        --fattoriRestanti; // last factor
        for (number e = 0; e <= s.coppie[fattoriRestanti].esponente; e++)
        {
            getDivisoriHelp(s, fattoriRestanti, divisors, num, product); // recursion to other factos
            product *= s.coppie[fattoriRestanti].fattore;                // add factor to product
        }
    }
}

void getDivisori(number n, number d[], size_t &num)
{
    scomposizione s = scomponi(n);
    getDivisoriHelp(s, s.numCoppie, d, num, 1);
}
