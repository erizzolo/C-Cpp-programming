/*
 * Struct per periodi
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

/*
Periodo (periodo)
In un file periodo.h, dopo aver dichiarato la struct di nome periodo con
membri di tipo double inizio e fine, rappresentanti rispettivamente l’inizio e la
fine di un periodo di tempo specificato (in unità di misura arbitraria), si
dichiarino ed implementino le funzioni con i seguenti prototipi:
a. void print(const periodo &p, ostream& out = cout);
// visualizza sullo stream out (per default cout) il periodo
// p in forma testuale come “(5,25)” (con iniziop=5 e finep=25 )
b. periodo getPeriodo(double inizio, double fine);
// restituisce il periodo con valori inizio e fine specificati
c. periodo getFromKeyboard();
// restituisce il periodo con valori inizio e fine da tastiera
d. double duration(const periodo &p);
// restituisce la durata del periodo p ovvero fine p−iniziop
e. periodo intersection(const periodo &a, const periodo &b);
// restituisce l’intersezione dei periodi a e b
// ovvero il periodo di sovrapposizione di a e b
f. bool contains(const periodo &p, double x);
// restituisce true se l’istante x appartiene a p, false
altrimenti
Realizzare quindi nel file periodo.cpp un’applicazione che consenta all’utente
di verificare il funzionamento della libreria periodo.h.
*/

#include <iostream>
#include <limits>

#include "periodo.h"

using namespace std;

const bool DEBUG = true;
const size_t MAX_PERIODS = 10;
periodo thePeriods[MAX_PERIODS];
size_t numPeriods = 0;

void test(const periodo &r, double x)
{
    cout << "Test di: ";
    print(r);
    cout << endl;
    cout << "Duration: " << duration(r) << endl;
    cout << "r does " << (contains(r, x) ? "" : "not ") << "contain " << x << endl;
    for (size_t i = 0; i < numPeriods; i++)
    {
        periodo intersect = intersection(r, thePeriods[i]);
        print(r);
        cout << " intersection ";
        print(thePeriods[i]);
        cout << " = ";
        print(intersect);
        cout << endl;
    }
    if (numPeriods < MAX_PERIODS)
    {
        thePeriods[numPeriods] = r;
        numPeriods++;
    }
}

int main(int argc, char *argv[])
{
    test({-3, 5}, 0);
    test(getPeriodo(-5, 3), -10);
    test(getFromKeyboard(), 0);

    return 0;
}
