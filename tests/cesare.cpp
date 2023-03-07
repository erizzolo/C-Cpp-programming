/*
 * Cifrario di Cesare
 * Author:  ER
 * Date:    2023/02/22
 * Note:
 */

/*
Cifrario (cesare)
Si racconta che Giulio Cesare utilizzasse un codice segreto per comunicare
basato su uno schema di sostituzione in cui ogni lettera del messaggio in chiaro
è sostituita, nel messaggio cifrato, dalla lettera che si trova un certo numero di
posizioni dopo nell'alfabeto (ricominciando dalla ‘a’ dopo la ‘z’).
Ad esempio, se il numero di posizioni fosse 3, la ‘a’ sarebbe sostituita dalla ‘d’,
la ‘b’ dalla ‘e’, la ‘z’ dalla ‘c’; la parola ‘attaccare’ del messaggio in chiaro
sarebbe trasformata in ‘dwwdffduh’ nel messaggio cifrato (si considera
l’alfabeto latino esteso di 26 caratteri).
Realizzare una funzione con il seguente prototipo:
void cifra(char m[], int p);
che trasforma la stringa m (messaggio in chiaro) decifrandola usando un
numero di posizioni p.
Realizzare una funzione con il seguente prototipo:
void decifra(char c[], int p);
che trasforma la stringa c (messaggio cifrato) decifrandola usando un numero
di posizioni p.
Le funzioni devono considerare soltanto le lettere minuscole dell’alfabeto,
lasciando inalterati eventuali maiuscole ed altri caratteri.
Realizzare un’applicazione che consenta all’utente di verificare la correttezza
della funzione, immettendo da tastiera delle stringhe e visualizzando il risultato
della cifratura e la verifica della decifratura.
*/

#include <iostream>
#include <limits>
#include <cstring>

using namespace std;

const bool DEBUG = true;

const size_t MAX_LENGTH = 100 + 1;

void cifra(char m[], int p);
void decifra(char c[], int p);

void test(const char message[], int p)
{
    cout << "Test di: " << message << endl;
    char copied[MAX_LENGTH];
    strcpy(copied, message);
    cifra(copied, p);
    cout << "Encrypted: " << copied << endl;
    decifra(copied, p);
    cout << "Decrypted: " << copied << endl;
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
        test(message, 5);
    } while (strcmp(message, "quit") != 0);

    return 0;
}

void cifra(char m[], int p)
{
    size_t i = 0;
    while (m[i] != 0)
    {
        if ('a' <= m[i] && m[i] <= 'z')
        {
            int coded = m[i] + p;
            while (coded > 'z')
                coded -= ('z' - 'a' + 1);
            while (coded < 'a')
                coded += ('z' - 'a' + 1);
            m[i] = coded;
        }
        ++i;
    }
}

void decifra(char c[], int p)
{
    cifra(c, -p);
}
