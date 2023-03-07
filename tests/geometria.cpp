/*
 * Struct per geometria
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

/*
Geometria (geometria)
In un file geometria.h, dopo aver dichiarato la struct di nome punto con
membri di tipo double x e y, rappresentanti rispettivamente l’ascissa e
l’ordinata di un punto nel piano cartesiano, si dichiarino ed implementino le
funzioni con i seguenti prototipi:
a. void print(const punto &p, ostream& out = cout);
// visualizza sullo stream out (per default cout) il punto
// p in forma testuale come “P(-5,2)” (assumendo xp=−5 e yp =2 )
b. punto getPunto(double x, double y);
// restituisce il punto con valori x e y specificati
c. punto getFromKeyboard();
// restituisce il punto con valori x e y letti da tastiera
d. double distance(const punto &a, const punto &b);
// restituisce la distanza euclidea tra i punti a e b
// ovvero √( xa − xb)^2 +( ya − yb)^2 (usare sqrt della libreria cmath)
e. bool coincident(const punto &a, const punto &b);
// restituisce true se a e b coincidono, false altrimenti
Realizzare quindi nel file geometria.cpp un’applicazione che consenta
all’utente di verificare il funzionamento della libreria geometria.h.
*/

#include <iostream>
#include <limits>

#include "geometria.h"

using namespace std;

const bool DEBUG = true;
const size_t MAX_POINTS = 10;
punto thePoints[MAX_POINTS];
size_t numPoints = 0;

void test(const punto &p)
{
    cout << "Test di: ";
    print(p);
    cout << endl;
    for (size_t i = 0; i < numPoints; i++)
    {
        cout << "distance(";
        print(p);
        cout << ", ";
        print(thePoints[i]);
        cout << ") = " << distance(p, thePoints[i]) << endl;
        print(p);
        cout << " and ";
        print(thePoints[i]);
        cout << " are " << (coincident(p, thePoints[i]) ? "" : "not ") << "coincident." << endl;
    }
    if (numPoints < MAX_POINTS)
    {
        thePoints[numPoints] = p;
        numPoints++;
    }
}

int main(int argc, char *argv[])
{
    test({0, 0});
    test(getPunto(-3, 5));
    test(getPunto(-5, 3));
    test(getFromKeyboard());

    return 0;
}
