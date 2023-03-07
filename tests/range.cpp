/*
 * Struct per intervalli
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

/*
Intervallo (range)
In un file range.h, dopo aver dichiarato la struct di nome range con membri di
tipo double min e max, rappresentanti rispettivamente l’estremo inferiore e
quello superiore di un intervallo finito e chiuso di numeri reali, si dichiarino ed
implementino le funzioni con i seguenti prototipi:
a. void print(const range &r, ostream& out = cout);
// visualizza sullo stream out (per default cout) l’intervallo
// r in forma testuale come “[-5,2]” (con minr =−5 e max r=2 )
b. range getRange(double min, double max);
// restituisce l’intervallo con valori min e max specificati
c. range getFromKeyboard();
// restituisce l’intervallo con valori min e max da tastiera
d. double length(const range &r);
// restituisce la lunghezza dell’intervallo r
// ovvero maxr −minr
e. range intersection(const range &a, const range &b);
// restituisce l’intersezione degli intervalli a e b
// ovvero l’intervallo dei valori appartenenti ad entrambi
f. bool contains(const range &r, double x);
// restituisce true se x appartiene a r, false altrimenti
Realizzare quindi nel file range.cpp un’applicazione che consenta all’utente di
verificare il funzionamento della libreria range.h.
*/

#include <iostream>
#include <limits>

#include "range.h"

using namespace std;

const bool DEBUG = true;
const size_t MAX_RANGES = 10;
range theRanges[MAX_RANGES];
size_t numRanges = 0;

void test(const range &r, double x)
{
    cout << "Test di: ";
    print(r);
    cout << endl;
    cout << "Length: " << length(r) << endl;
    cout << "r does " << (contains(r, x) ? "" : "not ") << "contain " << x << endl;
    for (size_t i = 0; i < numRanges; i++)
    {
        range intersect = intersection(r, theRanges[i]);
        print(r);
        cout << " intersection ";
        print(theRanges[i]);
        cout << " = ";
        print(intersect);
        cout << endl;
    }
    if (numRanges < MAX_RANGES)
    {
        theRanges[numRanges] = r;
        numRanges++;
    }
}

int main(int argc, char *argv[])
{
    test({-3, 5}, 0);
    test(getRange(-5, 3), -10);
    test(getFromKeyboard(), 0);

    return 0;
}
