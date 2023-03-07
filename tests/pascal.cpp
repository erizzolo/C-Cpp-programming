/*
 * C-string vs Pascal string
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

/*
Linguaggi (pascal)
Nel linguaggio Pascal, a differenza del C, le stringhe di caratteri sono
memorizzate come un array di char (al massimo 256) in cui l’elemento in
posizione 0, interpretato come unsigned char, contiene la lunghezza L della
stringa (0 <= L <= 255) ed i successivi i caratteri veri e propri della stringa.
Ad esempio, la parola ‘pascal’ nel linguaggio C sarebbe memorizzata come:
‘p’ ‘a’ ‘s’ ‘c’ ‘a’ ‘l’ 0 ...
con il valore 0 come terminatore, mentre nel linguaggio Pascal sarebbe
memorizzata come:
6 ‘p’ ‘a’ ‘s’ ‘c’ ‘a’ ‘l’ ...
con il valore 6 per la lunghezza.
Realizzare le funzioni con il seguente prototipo:
void pascalToC(const char p[], char c[]);
void cToPascal(const char c[], char p[]);
che trasformino la stringa c memorizzata secondo il linguaggio C nella stringa p
memorizzata secondo il linguaggio Pascal e viceversa.
Realizzare un’applicazione che consenta all’utente di verificare la correttezza
della funzione, immettendo da tastiera delle stringhe e visualizzando il risultato
ottenuto dopo la conversione in “Pascal” e la riconversione in “C”.
Si noti che non ha senso, nel linguaggio C, cercare di visualizzare un array di
char p nel formato “Pascal” con cout << p !!!
*/

#include <iostream>
#include <limits>
#include <cstring>

using namespace std;

const bool DEBUG = true;

const size_t MAX_LENGTH = 255 + 1;

void pascalToC(const char p[], char c[]);
void cToPascal(const char c[], char p[]);

void test(const char message[])
{
    cout << "Test di: " << message << endl;
    char pascal[MAX_LENGTH];
    char copied[MAX_LENGTH];
    cToPascal(message, pascal);
    pascalToC(pascal, copied);
    cout << "C-P-C: " << copied << endl;
    if (strcmp(message, copied) != 0)
    {
        cout << "Error!!!" << endl;
    }
}

int main(int argc, char *argv[])
{
    char message[MAX_LENGTH];
    do
    {
        cout << "Enter the message ('quit' to quit): ";
        cin.getline(message, MAX_LENGTH);
        test(message);
    } while (strcmp(message, "quit") != 0);

    return 0;
}

void pascalToC(const char p[], char c[])
{
    size_t length = (unsigned char)p[0];
    for (size_t i = 0; i < length; ++i)
    {
        c[i] = p[i + 1];
    }
    c[length] = 0;
}
void cToPascal(const char c[], char p[])
{
    size_t length = 0;
    while (c[length] != 0)
    {
        p[length + 1] = c[length];
        ++length;
    }
    p[0] = length;
}
