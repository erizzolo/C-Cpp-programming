/*
 * Struct per frazioni
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

#ifndef FRAZIONI_H
#define FRAZIONI_H

// una frazione
struct frazione
{
    int n; // numeratore
    int d; // denominatore
};

#include <iostream>
#include <limits>

using namespace std;

void print(const frazione &f, ostream &out = cout);
// visualizza sullo stream out (per default cout) la frazione
// f in forma testuale come “-5/2” (assumendo nf=−5 e df=2 )
frazione getFrazione(int n, int d);
// restituisce la frazione con valori n e d specificati
frazione getFromKeyboard();
// restituisce la frazione con valori n e d da tastiera
double approximation(const frazione &a);
// restituisce il valore approssimato in virgola mobile di f
// ovvero n/d (calcolo con valori di tipo double)
bool equivalent(const frazione &a, const frazione &b);
// restituisce true se a e b sono equivalenti,false altrimenti
// a = na / da e b = nb / db sono equivalenti se e solo se na⋅db = da⋅nb

// visualizza sullo stream out (per default cout) la frazione
// f in forma testuale come “-5/2” (assumendo nf=−5 e df=2 )
void print(const frazione &p, ostream &out /* = cout */)
{
    out << p.n << "/" << p.d;
}

// restituisce la frazione con valori n e d specificati
frazione getFrazione(int n, int d)
{
    frazione result{n, d};
    return result;
}

/// @brief Acquisisce un int nell'intervallo [min, max] da tastiera
/// @param prompt messaggio per l'utente
/// @param min minimo valore accettabile
/// @param max massimo valore accettabile
/// @return il valore letto da tastiera
int getInt(const char *prompt, int min = numeric_limits<int>::min(), int max = numeric_limits<int>::max())
{
    int result = 0; // assegno un valore non valido
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

// restituisce la frazione con valori n e d da tastiera
frazione getFromKeyboard()
{
    frazione result;
    result.n = getInt("n: ");
    do
    {
        result.d = getInt("d: ");
    } while (result.d == 0);
    return result;
}

double approximation(const frazione &a);
// restituisce il valore approssimato in virgola mobile di f
// ovvero n/d (calcolo con valori di tipo double)
double approximation(const frazione &a)
{
    double d = a.d, n = a.n;
    return n / d;
}

// restituisce true se a e b sono equivalenti,false altrimenti
// a = na / da e b = nb / db sono equivalenti se e solo se na⋅db = da⋅nb
bool equivalent(const frazione &a, const frazione &b)
{
    // to avoid overflow, we should divide by Greatest Common Divisor...
    return a.n * b.d == a.d * b.n;
}

#endif