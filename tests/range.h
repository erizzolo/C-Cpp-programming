/*
 * Struct per intervalli
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

#ifndef RANGE_H
#define RANGE_H

// un intervallo finito e chiuso di numeri reali
struct range
{
    double min; // estremo inferiore
    double max; // estremo superiore
};

#include <iostream>
#include <limits>
using namespace std;

void print(const range &r, ostream &out = cout);
// visualizza sullo stream out (per default cout) l’intervallo
// r in forma testuale come “[-5,2]” (con minr =−5 e max r=2 )
range getRange(double min, double max);
// restituisce l’intervallo con valori min e max specificati
range getFromKeyboard();
// restituisce l’intervallo con valori min e max da tastiera
double length(const range &r);
// restituisce la lunghezza dell’intervallo r
// ovvero maxr −minr
range intersection(const range &a, const range &b);
// restituisce l’intersezione degli intervalli a e b
// ovvero l’intervallo dei valori appartenenti ad entrambi
bool contains(const range &r, double x);
// restituisce true se x appartiene a r, false altrimenti

// visualizza sullo stream out (per default cout) l’intervallo
// r in forma testuale come “[-5,2]” (con minr =−5 e max r=2 )
void print(const range &r, ostream &out /* = cout */)
{
    out << "[" << r.min << "," << r.max << "]";
}
// restituisce l’intervallo con valori min e max specificati
range getRange(double min, double max)
{
    range result{min, max};
    return result;
}

/// @brief Acquisisce un double nell'intervallo [min, max] da tastiera
/// @param prompt messaggio per l'utente
/// @param min minimo valore accettabile
/// @param max massimo valore accettabile
/// @return il valore letto da tastiera
double getDouble(const char *prompt, double min = -numeric_limits<double>::max(), double max = numeric_limits<double>::max())
{
    double result = 0; // assegno un valore non valido
    bool valid;
    do
    {
        cout << prompt;
        cin >> result;
        valid = (!cin.fail()) && (min <= result) && (result <= max);
        if (!valid)
        {
            cerr << "Enter a number in [" << min << ", " << max << "]" << endl;
            cin.clear();                                         // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
        }
    } while (!valid);
    return result;
}
// restituisce l’intervallo con valori min e max da tastiera
range getFromKeyboard()
{
    range result;
    result.min = getDouble("min: ");
    result.max = getDouble("max: ", result.min);
    return result;
}
// restituisce la lunghezza dell’intervallo r ovvero maxr −minr
double length(const range &r)
{
    return r.max - r.min;
}
// restituisce l’intersezione degli intervalli a e b
// ovvero l’intervallo dei valori appartenenti ad entrambi
range intersection(const range &a, const range &b)
{
    range result;
    result.min = a.min > b.min ? a.min : b.min;
    result.max = a.max > b.max ? b.max : a.max;
    return result;
}

// restituisce true se x appartiene a r, false altrimenti
bool contains(const range &r, double x)
{
    return r.min <= x && x <= r.max;
}

#endif