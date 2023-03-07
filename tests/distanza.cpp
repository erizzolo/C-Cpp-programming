/*
 * Distanza di Hamming +-
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

/*
Distanza (distanza)
Si vogliono confrontare tra loro due stringhe, usando come misura della loro
similitudine la seguente definizione di distanza di Hamming tra due stringhe
di uguale lunghezza:
il numero di posizioni nelle quali i simboli corrispondenti sono diversi.
Ad esempio, le parole “vero” e “timo” hanno distanza 3 (le lettere sottollineate
sono diverse nelle due parole).
Realizzare una funzione con il seguente prototipo:
size_t distance(const char p[], const char s[]);
che restituisca la distanza di Hamming tra le due parole contenute in s e p.
La funzione deve considerare soltanto le lettere dell’alfabeto ignorando la
differenza tra maiuscole e minuscole, e considerare come simboli diversi le
eventuali lettere mancanti se le lunghezze delle stringhe sono diverse.
Ad esempio “Ciocco Latino” e “cioccolatino” hanno distanza nulla poiché lo
spazio viene ignorato e la distanza non è sensibile alle maiuscole.
Realizzare un’applicazione che consenta all’utente di verificare la correttezza
della funzione, immettendo da tastiera delle coppie di stringhe e
visualizzandone la distanza.
*/

#include <iostream>
#include <limits>
#include <cstring>

using namespace std;

const bool DEBUG = true;
const size_t MAX_STRINGS = 10;
const size_t MAX_LENGTH = 100;
char theStrings[MAX_STRINGS][MAX_LENGTH];
size_t numStrings = 0;

size_t distance(const char p[], const char s[]);

void test(const char f[])
{
    cout << "Test di: " << f << endl;
    for (size_t i = 0; i < numStrings; i++)
    {
        cout << "distance(" << f << ", " << theStrings[i] << ") = " << distance(f, theStrings[i]) << endl;
    }
    if (numStrings < MAX_STRINGS)
    {
        strcpy(theStrings[numStrings], f);
        numStrings++;
    }
}

int main(int argc, char *argv[])
{
    test("mamma");
    test("mammola");
    test("Cioccolatino");
    test("Ciocco Latino!");
    char s[MAX_LENGTH];
    do
    {
        cin.getline(s, MAX_LENGTH);
        test(s);
    } while (strcmp(s, "quit") != 0);
    return 0;
}

char upper(char c)
{
    if ('a' <= c && c <= 'z')
        return c + 'A' - 'a';
    return c;
}

char lower(char c)
{
    if ('A' <= c && c <= 'Z')
        return c + 'a' - 'A';
    return c;
}
bool letter(char c)
{
    c = lower(c);
    return 'a' <= c && c <= 'z';
}

size_t nextLetter(const char s[], size_t start)
{
    while (s[start] != 0 && !letter(s[start]))
    {
        ++start;
    }
    return start;
}

size_t count(const char p[], size_t start)
{
    size_t result = 0;
    start = nextLetter(p, start);
    while (p[start] != 0)
    {
        ++result;
        start = nextLetter(p, ++start);
    }
    return result;
}

size_t distance(const char p[], const char s[])
{
    size_t result = 0;
    size_t ip = nextLetter(p, 0), is = nextLetter(s, 0);
    while (p[ip] != 0 && s[is] != 0)
    {
        if (lower(p[ip]) != lower(s[is]))
        {
            ++result;
        }
        ip = nextLetter(p, ++ip);
        is = nextLetter(s, ++is);
    }
    // one string finished, maybe both
    result += count(p, ip);
    result += count(s, is);
    return result;
}
