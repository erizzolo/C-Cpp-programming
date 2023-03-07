/*
 * Verifica anagramma
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

/*
Anagrammi (anagramma)
Si realizzi una funzione che determini se due stringhe sono oppure no
anagrammi.
Si ricorda che una parola è un anagramma di una seconda parola quando le sue
lettere possono essere disposte in modo da formare la seconda parola.
Ad esempio, ridisponendo le lettere di MORA si può formare la parola ROMA.
Realizzare una funzione con il seguente prototipo:
bool anagramma(const char p[], const char s[]);
che restituisca true se le due parole contenute in s e p sono anagrammi, false
altrimenti.
La funzione deve considerare soltanto le lettere dell’alfabeto ignorando la
differenza tra maiuscole e minuscole.
Ad esempio “Bibliotecario” e “BEATO coi libri” devono essere considerati
anagrammi.
Realizzare un’applicazione che consenta all’utente di verificare la correttezza
della funzione, immettendo da tastiera delle coppie di stringhe e visualizzando
se esse sono anagrammi.
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

bool anagramma(const char p[], const char s[]);

void test(const char f[])
{
    cout << "Test di: " << f << endl;
    for (size_t i = 0; i < numStrings; i++)
    {
        cout << f << " and " << theStrings[i];
        cout << " are " << (anagramma(f, theStrings[i]) ? "" : "not ") << "anagrammi." << endl;
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
    test("bibliotecario");
    test("Beato coi Libri!");
    char s[MAX_LENGTH];
    do
    {
        cin.getline(s, MAX_LENGTH);
        test(s);
    } while (strcmp(s, "") != 0);
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
size_t count(const char s[], char c, bool ignorecase = true)
{
    size_t result = 0, i = 0;
    while (s[i] != 0)
    {
        if (s[i] == c || ignorecase && lower(s[i]) == lower(c))
        {
            ++result;
        }
        ++i;
    }
    return result;
}

bool anagramma(const char p[], const char s[])
{
    size_t i = 0;
    while (p[i] != 0)
    {
        if (letter(p[i]))
        {
            if (count(p, p[i]) != count(s, p[i]))
            {
                return false;
            }
        }
        ++i;
    }
    i = 0;
    while (s[i] != 0)
    {
        if (letter(s[i]))
        {
            if (count(p, s[i]) != count(s, s[i]))
            {
                return false;
            }
        }
        ++i;
    }
    return true;
}

bool anagrammaAlternativo(const char p[], const char s[])
{
    for (char lettera = 'a'; lettera <= 'z'; ++lettera)
    {
        if (count(p, lettera) != count(s, lettera))
        {
            return false;
        }
    }
    return true;
}
