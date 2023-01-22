/**
 * Purpose: basic utilities for strings
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/01/18
 * Note:
 */

#include <iostream>

using namespace std;

const bool DEBUG = true;

int strlen(const char s[]);
// nota char* fun(...) per uniformità con libreria cstring
char *strcpy(char d[], const char s[]);
char *strcat(char d[], const char s[]);
char *strupper(char d[]);
char *strrev(char d[]);
char *strhide(char d[]);
int strcmp(const char *lhs, const char *rhs);
char *strreverse(char *dst);

// main function
int main(int argc, char *argv[])
{
    char frase[] = "La vita e' bella";
    cout << frase << endl;
    cout << "Lunghezza di frase = " << strlen(frase) << endl;
    char stringa[20];
    strcpy(stringa, frase);
    cout << stringa << endl;
    cout << "Lunghezza di stringa = " << strlen(stringa) << endl;
    cout << strcpy(stringa, frase) << endl;
    char sentence[100] = "La vita e' ";
    strcat(sentence, "fantastica!");
    cout << sentence << endl;
    cout << "Lunghezza di sentence = " << strlen(sentence) << endl;
    cout << strupper(sentence) << endl;
    cout << strcmp("uguale", "uguale") << endl;
    cout << strcmp("minore", "z") << endl;
    cout << strcmp("z", "maggiore") << endl;
    cout << strreverse(sentence) << endl;
    // NOTA: dichiarare le funzioni con char* consente cose del tipo:
    char nome[] = "Emanuele";
    char cognome[] = "Rizzolo";
    char saluto[] = "Buongiorno";
    char output[200];
    // piuttosto illeggibile, mi pare ...
    cout << strcat(strcat(strcat(strcat(strcat(saluto, " "), nome), " "), cognome), "!") << endl;
    // successful termination
    return 0;
}

/// @brief Lunghezza di una stringa
/// Si assume che sia correttamente terminata ...
/// i.e. la sentinella esiste ed è al suo posto
/// @param s  la stringa di cui si vuole la lunghezza
/// @return la lunghezza della stringa specificata
int strlen(const char s[])
{
    int len = 0;
    while (s[len] != 0)
    {
        ++len;
    }
    return len;
}

/// @brief Copia s in d
/// @param d stringa destinazione
/// @param s stringa sorgente
/// @return d
char *strcpy(char d[], const char s[])
{
    int i = 0;
    while (s[i] != 0)
    {
        d[i] = s[i];
        i++; // next char
    }
    d[i] = s[i]; // terminator
    return d;
}

/// @brief Concatena s in d
/// @param d stringa destinazione
/// @param s stringa sorgente
/// @return d
char *strcat(char d[], const char s[])
{
    int len = strlen(d);
    int i = 0;
    while (s[i] != 0)
    {
        d[len + i] = s[i];
        i++; // next char
    }
    d[len + i] = s[i]; // terminator
    return d;
}

/// @brief Converte d in maiuscolo
/// @param d stringa destinazione
/// @return d
char *strupper(char d[])
{
    int len = 0;
    while (d[len] != 0)
    {
        if (('a' <= d[len]) && (d[len] <= 'z'))
        {
            d[len] += 'A' - 'a';
        }
        ++len;
    }
    return d;
}

/// @brief Confronta lhs e rhs (lhs confronto rhs)
/// @param lhs stringa left hand side
/// @param rhs stringa right hand side
/// @return <=> 0 a seconda che lhs <=> rhs
int strcmp(const char *lhs, const char *rhs)
{
    int len = 0;
    while ((lhs[len] == rhs[len]) && (lhs[len] != 0))
    {
        ++len;
    }
    return lhs[len] - rhs[len];
}

/// @brief Rovescia
/// @param d stringa destinazione
/// @return d
char *strreverse(char *d)
{
    int l = 0, r = strlen(d) - 1;
    while (l < r)
    {
        swap(d[l], d[r]); // system swap ...
        // char temp = d[l];
        // d[l] = d[r];
        // d[r] = temp;
        ++l;
        --r;
    }
    return d;
}
