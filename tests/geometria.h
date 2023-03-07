/*
 * Struct per geometria
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

#ifndef GEOMETRIA_H
#define GEOMETRIA_H

// un punto nel piano cartesiano
struct punto
{
    double x; // estremo inferiore
    double y; // estremo superiore
};

#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

void print(const punto &p, ostream &out = cout);
// visualizza sullo stream out (per default cout) il punto
// p in forma testuale come “P(-5,2)” (assumendo xp=−5 e yp =2 )
punto getPunto(double x, double y);
// restituisce il punto con valori x e y specificati
punto getFromKeyboard();
// restituisce il punto con valori x e y da tastiera
double distance(const punto &a, const punto &b);
// restituisce la distanza euclidea tra i punti a e b
// ovvero √( xa − xb)^2 +( ya − yb)^2 (usare sqrt della libreria cmath)
bool coincident(const punto &a, const punto &b);
// restituisce true se a e b coincidono, false altrimenti

// visualizza sullo stream out (per default cout) il punto
// p in forma testuale come “P(-5,2)” (assumendo xp=−5 e yp =2 )
void print(const punto &p, ostream &out /* = cout */)
{
    out << "P(" << p.x << "," << p.y << ")";
}
// restituisce il punto con valori x e y specificati
punto getPunto(double x, double y)
{
    punto result{x, y};
    return result;
}

/// @brief Acquisisce un double nell'intervallo [x, y] da tastiera
/// @param prompt messaggio per l'utente
/// @param x ximo valore accettabile
/// @param y massimo valore accettabile
/// @return il valore letto da tastiera
double getDouble(const char *prompt, double x = -numeric_limits<double>::max(), double max = numeric_limits<double>::max())
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
            cin.clear();                                       // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
        }
    } while (!valid);
    return result;
}

// restituisce il punto con valori x e y da tastiera
punto getFromKeyboard()
{
    punto result;
    result.x = getDouble("x: ");
    result.y = getDouble("y: ", result.x);
    return result;
}

// restituisce la distanza euclidea tra i punti a e b
// ovvero √( xa − xb)^2 +( ya − yb)^2 (usare sqrt della libreria cmath)
double distance(const punto &a, const punto &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
// restituisce true se a e b coincidono, false altrimenti
bool coincident(const punto &a, const punto &b)
{
    return a.x == b.x && a.y == b.y;
    // return distance(a, b) == 0;
}

#endif