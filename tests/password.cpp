/*
 * Verifica password
 * Author:  ER
 * Date:    2023/04/01
 * Note:
 */

/*
Password (password) (valevole come recupero 1° quadrimestre)
Si realizzi una applicazione in grado di generare una password casuale che
soddisfi determinati requisiti.
I requisiti che una password valida deve soddisfare sono i seguenti:
• lunghezza compresa tra 8 e 16 caratteri;
• caratteri appartenenti solo alle seguenti categorie:
◦ lettere minuscole (‘a’ … ’z’)
◦ lettere maiuscole (‘A’ … ’Z’)
◦ cifre decimali (‘0’ … ’9’)
◦ simboli speciali (‘%’, ‘_’, ‘$’, ‘£’)
• almeno un carattere per ciascuna delle categorie precedenti.
Realizzare un’applicazione che consenta all’utente di ottenere una sequenza di
password casuali, visualizzando una alla volta le password sul flusso standard
di output (ciascuna password su una riga separata) e continuando con una
nuova e diversa password se l’utente immette da tastiera qualcosa di
differente dalla parola “basta”.
La generazione della password deve avvenire tramite una funzione specifica
che riceve come parametro (modificabile) la stringa in cui memorizzare la
password generata e restituisce la lunghezza della password generata e
memorizzata nel parametro.
È possibile ovviamente definire ed utilizzare altre funzioni che riteniate
necessarie od utili.
*/

#include <iostream>
#include <limits>
#include <cstring>
#include <ctime>

using namespace std;

const bool DEBUG = true;

const size_t MIN_LENGTH = 8;
const size_t MAX_LENGTH = 16;

const char LOWER[] = "abcdefghijklmnopqrstuvwxyz";
const char UPPER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DIGIT[] = "0123456789";
const char SPECIAL[] = "%_$£";

const size_t CATEGORIES = 4;
const char *CARATTERI[CATEGORIES]{LOWER, UPPER, DIGIT, SPECIAL};

size_t generate(char password[]);
bool verify(const char password[]);

int main(int argc, char *argv[])
{
    srand(time(nullptr));

    char password[MAX_LENGTH + 1];
    cout << "Verifica password immesse" << endl;
    do
    {
        cin.getline(password, sizeof(password));
        cout << password << (verify(password) ? " " : " non ") << "e' valida" << endl;
        if (cin.fail())
        {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.clear();
        }
    } while (strcmp(password, "fine") != 0);

    cout << "Generazione password" << endl;
    do
    {
        size_t length = generate(password);
        cout << password << (verify(password) ? " " : " non ") << "e' valida: length " << length << endl;
        cin.getline(password, sizeof(password));
        if (cin.fail())
        {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.clear();
        }
    } while (strcmp(password, "basta") != 0);

    return 0;
}

char randomChar(const char *allowed)
{
    return allowed[rand() % strlen(allowed)];
}

size_t generate(char password[])
{
    size_t result = MIN_LENGTH + rand() % (MAX_LENGTH - MIN_LENGTH + 1);
    for (size_t i = 0; i < result; i++)
    {
        password[i] = randomChar(CARATTERI[i < CATEGORIES ? i : rand() % CATEGORIES]);
    }
    password[result] = 0; // don't forget it !!!
    return result;
}

size_t categoryOf(char l)
{
    for (size_t c = 0; c < CATEGORIES; c++)
    {
        if (strchr(CARATTERI[c], l) != nullptr)
        {
            return c;
        }
    }
    return CATEGORIES;
}

bool verify(const char password[])
{
    size_t length = strlen(password);
    bool result = MIN_LENGTH <= length && length <= MAX_LENGTH;
    bool present[CATEGORIES];
    for (size_t c = 0; c < CATEGORIES; c++)
    {
        present[c] = false;
    }
    for (size_t i = 0; i < length && result; i++)
    {
        size_t which = categoryOf(password[i]);
        if (which == CATEGORIES)
        {
            result = false;
        }
        else
        {
            present[which] = true;
        }
    }
    for (size_t c = 0; c < CATEGORIES && result; c++)
    {
        result = present[c];
    }
    return result;
}
