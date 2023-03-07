/*
 * Struct per intervalli
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

#ifndef PERIODO_H
#define PERIODO_H

// un intervallo finito e chiuso di numeri reali
struct periodo
{
    double inizio; // inizio
    double fine;   // fine
};

#include <iostream>
#include <limits>
using namespace std;

void print(const periodo &p, ostream &out = cout);
// visualizza sullo stream out (per default cout) il periodo
// p in forma testuale come “(5,25)” (con iniziop=5 e finep=25 )
periodo getPeriodo(double inizio, double fine);
// restituisce il periodo con valori inizio e fine specificati
periodo getFromKeyboard();
// restituisce il periodo con valori inizio e fine da tastiera
double duration(const periodo &p);
// restituisce la durata del periodo p ovvero fine p−iniziop
periodo intersection(const periodo &a, const periodo &b);
// restituisce l’intersezione dei periodi a e b
// ovvero il periodo di sovrapposizione di a e b
bool contains(const periodo &p, double x);
// restituisce true se l’istante x appartiene a p, false

// visualizza sullo stream out (per default cout) il periodo
// p in forma testuale come “(5,25)” (con iniziop=5 e finep=25 )
void print(const periodo &p, ostream &out /* = cout */)
{
    out << "(" << p.inizio << "," << p.fine << ")";
}
// restituisce il periodo con valori inizio e fine specificati
periodo getPeriodo(double inizio, double fine)
{
    periodo result{inizio, fine};
    return result;
}

/// @brief Acquisisce un double nell'intervallo [min, fine] da tastiera
/// @param prompt messaggio per l'utente
/// @param min minimo valore accettabile
/// @param min massimo valore accettabile
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
            cin.clear();                                          // unset failbit
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // skip bad input
        }
    } while (!valid);
    return result;
}
// restituisce il periodo con valori inizio e fine da tastiera
periodo getFromKeyboard()
{
    periodo result;
    result.inizio = getDouble("inizio: ");
    result.fine = getDouble("fine: ", result.inizio);
    return result;
}

// restituisce la durata del periodo p ovvero fine p−iniziop
double duration(const periodo &p)
{
    return p.fine - p.inizio;
}

// restituisce l’intersezione degli intervalli a e b
// ovvero il periodo di sovrapposizione di a e b
periodo intersection(const periodo &a, const periodo &b)
{
    periodo result;
    result.inizio = a.inizio > b.inizio ? a.inizio : b.inizio;
    result.fine = a.fine > b.fine ? b.fine : a.fine;
    return result;
}

// restituisce true se l’istante x appartiene a p, false
bool contains(const periodo &p, double x)
{
    return p.inizio <= x && x <= p.fine;
}

#endif
