/*
 * Struct per frazioni
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

/*
Razionali (frazioni)
In un file frazioni.h, dopo aver dichiarato la struct di nome frazione con
membri di tipo int n e d, rappresentanti rispettivamente il numeratore ed il
denominatore (diverso da 0) della frazione n/d, si dichiarino ed implementino le
funzioni con i seguenti prototipi:
a. void print(const frazione &f, ostream& out = cout);
// visualizza sullo stream out (per default cout) la frazione
// f in forma testuale come “-5/2” (assumendo nf =−5 e d f =2 )
b. frazione getFrazione(int n, int d);
// restituisce la frazione con valori n e d specificati
c. frazione getFromKeyboard();
// restituisce la frazione con valori n e d letti da tastiera
d. double approximation(const frazione &f);
// restituisce il valore approssimato in virgola mobile di f
// ovvero n/d (calcolo con valori di tipo double)
e. bool equivalent(const frazione &a, const frazione &b);
// restituisce true se a e b sono equivalenti,false altrimenti
// a = na / da e b = nb / db sono equivalenti se e solo se na⋅db = da⋅nb
Realizzare quindi nel file frazioni.cpp un’applicazione che consenta all’utente
di verificare il funzionamento della libreria frazioni.h.
*/

#include <iostream>
#include <limits>

#include "frazioni.h"

using namespace std;

const bool DEBUG = true;
const size_t MAX_FRACTIONS = 10;
frazione theFractions[MAX_FRACTIONS];
size_t numFractions = 0;

void test(const frazione &f)
{
    cout << "Test di: ";
    print(f);
    cout << " = " << approximation(f) << endl;
    for (size_t i = 0; i < numFractions; i++)
    {
        print(f);
        cout << " and ";
        print(theFractions[i]);
        cout << " are " << (equivalent(f, theFractions[i]) ? "" : "not ") << "equivalent." << endl;
    }
    if (numFractions < MAX_FRACTIONS)
    {
        theFractions[numFractions] = f;
        numFractions++;
    }
}

int main(int argc, char *argv[])
{
    test({0, 5});
    test(getFrazione(-3, 5));
    test(getFrazione(-15, 25));
    test(getFromKeyboard());

    return 0;
}
