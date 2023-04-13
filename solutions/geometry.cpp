/*
 * Struct per geometria
 * Author:  ER
 * Date:    2023/03/11
 * Note:    Tests to be completed
 */

/*
Geometria (geometry)
In un file geometry.h, dichiarare le struct seguenti:
◦ punto, con membri di tipo double x e y, rappresentanti rispettivamente
l’ascissa e l’ordinata di un punto nel piano cartesiano;
◦ segmento, con membri di tipo punto a e b, rappresentanti i due punti
estremi del segmento;
◦ retta, con membri opportuni per memorizzare i coefficienti dell’equazione
di una retta (nella forma a x + b y + c = 0);
◦ triangolo, con membri di tipo punto a, b e c, rappresentanti i vertici del
triangolo;
◦ poligono, con membri opportuni per memorizzare il numero di lati ed i
vertici del poligono.
◦ circonferenza, con membri opportuni per memorizzare il centro ed il
raggio.
Per ciascuna delle struct precedenti, si dichiarino ed implementino le seguenti
funzioni:
◦ void print(const <struct> &, ostream& out = cout);
// visualizza sullo stream out (per default cout) la struct
// in forma testuale opportuna
◦ <struct> get<struct>(...);
// restituisce la struct inizializzata con i parametri
// specificati
◦ <struct> copy(const <struct> & original);
// restituisce la struct copia di quella specificata
◦ bool equals(const <struct> & lhs, const <struct> & rhs);
// restituisce true se lhs e rhs “coincidono”,
// false altrimenti
◦ double length(const <struct> &);
// ove la funzione abbia senso
◦ double perimeter(const <struct> &);
// ove la funzione abbia senso
◦ double area(const <struct> &);
// ove la funzione abbia senso
◦ bool contains(const <struct> &, const punto & p);
// ove la funzione abbia senso
Realizzare quindi nel file geometry.cpp un’applicazione che consenta all’utente
di verificare il funzionamento della libreria geometry.h.
*/

#include <iostream>
#include <limits>

#include "geometry.h"

using namespace std;

const bool DEBUG = true;

double getDouble(const char *prompt = "", double x = -numeric_limits<double>::max(), double max = numeric_limits<double>::max());

void testPunto();
void testSegmento();
void testRetta();

int main(int argc, char *argv[])
{
    testPunto();
    testSegmento();
    testRetta();
    circonferenza c = getCirconferenza(getPunto(0, 0), 1);
    cout << perimeter(c) << endl; 

    return 0;
}

void testPunto()
{
    cout << "Test punto" << endl;

    punto p1 = getPunto(1.5, 0.5);
    print(p1);
    cout << " <- P1" << endl;

    punto p2 = getPunto(-1.5, 0.5);
    print(p2);
    cout << " <- P2" << endl;

    punto p3 = copy(p1);
    print(p3);
    cout << " <- P3" << endl;

    print(p1);
    cout << " equals ";
    print(p3);
    cout << ": " << equals(p1, p3) << " (should be 1)" << endl;

    print(p1);
    cout << " equals ";
    print(p2);
    cout << ": " << equals(p1, p2) << " (should be 0)" << endl;

    cout << endl;
}

void testSegmento()
{
    cout << "Test segmento" << endl;

    punto a = getPunto(1.5, 0.5);
    punto b = getPunto(-1.5, 0.5);

    segmento s1 = getSegmento(a, b);
    print(s1);
    cout << " <- S1" << endl;

    segmento s2 = getSegmento(b, a);
    print(s2);
    cout << " <- S2" << endl;

    segmento s3 = copy(s1);
    print(s3);
    cout << " <- S3" << endl;

    print(s1);
    cout << " equals ";
    print(s3);
    cout << ": " << equals(s1, s3) << " (should be 1)" << endl;

    print(s1);
    cout << " equals ";
    print(s2);
    cout << ": " << equals(s1, s2) << " (should be 0)" << endl;

    cout << "lunghezza di ";
    print(s1);
    cout << ": " << length(s1) << endl;

    for (double xp = -1.5; xp < 3; xp += 0.6)
    {
        punto p = getPunto(xp, 0.5);
        print(s2);
        cout << " contiene ";
        print(p);
        cout << ": " << contains(s2, p) << " should be " << (xp <= s2.b.x) << endl;
    }

    cout << endl;
}

void testRetta()
{
    cout << "Test retta" << endl;

    punto a = getPunto(1.5, 0.5);
    punto b = getPunto(-1.5, 0.5);

    retta r1 = getRetta(a, b); // should be y - 0.5 = 0
    print(r1);
    cout << " <- R1" << endl;

    retta r2 = getRetta(1.0, 0.0, 3.14); // x + 3.14 = 0
    print(r2);
    cout << " <- R2" << endl;

    retta r3 = copy(r1);
    print(r3);
    cout << " <- R3" << endl;

    print(r1);
    cout << " equals ";
    print(r3);
    cout << ": " << equals(r1, r3) << " (should be 1)" << endl;

    print(r1);
    cout << " equals ";
    print(r2);
    cout << ": " << equals(r1, r2) << " (should be 0)" << endl;

    retta r4 = getRetta(0.0, 2.0, -1.0); // should be 2 * (y - 0.5 = 0)
    print(r4);
    cout << " <- R4" << endl;

    print(r1);
    cout << " equals ";
    print(r4);
    cout << ": " << equals(r1, r4) << " (should be 1)" << endl;

    for (double xp = -1.5; xp < 3; xp += 0.6)
    {
        punto p = getPunto(xp, 0.5);
        print(r1);
        cout << " contiene ";
        print(p);
        cout << ": " << contains(r1, p) << " should be 1" << endl;
    }

    cout << endl;
}

/// @brief Acquisisce un double nell'intervallo [x, y] da tastiera
/// @param prompt messaggio per l'utente
/// @param x ximo valore accettabile
/// @param y massimo valore accettabile
/// @return il valore letto da tastiera
double getDouble(const char *prompt /* = "" */, double x /* = -numeric_limits<double>::max() */, double max /*  = numeric_limits<double>::max() */)
{
    double result = 0; // assegno un valore non valido
    bool valid;
    do
    {
        cout << prompt;
        cin >> result;
        valid = (!cin.fail()) && (x <= result) && (result <= max);
        if (!valid)
        {
            cerr << "Enter a number in [" << x << ", " << max << "]" << endl;
            cin.clear();                                         // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
        }
    } while (!valid);
    return result;
}
