/**
 * Programma per controllo valori rubrica
 * Author:  ER
 * Date:    2023/03/31
 * Note:    rispetto al testo, i criteri di validita' sono
 *          leggermente modificati
 */

/*
## Rubrica (book)
Realizzare un’applicazione che riceva l’input da riga comando e consenta di verificare la correttezza o meno dei dati forniti, visualizzando il risultato sul flusso standard di output/error.

Il formato del comando per l’utilizzo dell’applicazione deve essere il seguente:

> book.exe *nome* *cognome* *telefono* *età*
>
> ad es. book.exe “Gian Paolo” Rossi +3901174562 23
>
> ad es. book.exe “Gian-Paolo” Rossi 3901178562 32
>
> ad es. book.exe Mario ”Dei Rossi” 011785624 52

dove:
* *nome* deve essere una stringa contenente solo lettere alfabetiche (almeno una in più rispetto ai separatori) ed eventuali spazi (come nell’esempio) o trattini (-) separatori non consecutivi;
* *cognome* deve essere una stringa contenente solo lettere alfabetiche (almeno una in più rispetto ai separatori) ed eventuali spazi separatori non consecutivi;
* *telefono* deve essere una stringa contenente solo cifre numeriche decimali ed un’eventuale segno ‘+’ iniziale;
* *età* deve essere un numero intero positivo compreso tra 1 e 125 (estremi inclusi).

Qualora l’applicazione venga eseguita senza il numero corretto di argomenti essa deve:
* visualizzare sul flusso standard di errore (cerr) un messaggio con il formato
corretto del comando.
* terminare restituendo codice di errore -10 per errato numero di argomenti.

Qualora l’applicazione venga eseguita ma almeno un argomento non sia corretto essa deve:
* visualizzare sul flusso standard di errore (cerr) un messaggio con il formato corretto per ciascun argomento errato;
* terminare restituendo codice di errore uguale all’opposto del numero di argomenti non corretti.

Nel caso “normale” l’applicazione deve terminare con codice di ritorno 0 senza
visualizzare alcunché.
*/

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

bool checkString(const char *stringa, const char *separatori);
bool checkPhone(const char *number);

int main(int argc, char *argv[])
{
    int result = 0;
    if (argc == 5)
    {
        if (!checkString(argv[1], " -"))
        {
            cerr << "Nome non valido" << endl;
            result--;
        }
        if (!checkString(argv[2], " '"))
        {
            cerr << "Cognome non valido" << endl;
            result--;
        }
        if (!checkPhone(argv[3]))
        {
            cerr << "Telefono non valido" << endl;
            result--;
        }
        int age;
        int valid = sscanf(argv[4], "%d", &age);
        if (valid == 0 || 1 > age || age > 125)
        {
            cerr << "Eta' non valida" << endl;
            result--;
        }
    }
    else
    {
        cerr << argv[0] << " <nome> <cognome> <telefono> <età>" << endl;
        result = -10;
    }

    return result;
}

bool my_isalpha(char ch)
{
    return std::isalpha(static_cast<unsigned char>(ch));
}

bool checkString(const char *stringa, const char *separatori)
{
    bool result = true;
    bool separatore = false;
    for (int i = 0; stringa[i] != 0 && result; i++)
    {
        if (strchr(separatori, stringa[i]) == nullptr)
        {
            separatore = false;
            result = my_isalpha(stringa[i]);
        }
        else
        {
            if (i == 0 || separatore)
            {
                result = false;
            }
            separatore = true;
        }
    }
    if (separatore)
    {
        result = false;
    }
    return result;
}

bool my_isdigit(char ch)
{
    return std::isdigit(static_cast<unsigned char>(ch));
}

bool checkPhone(const char *number)
{
    bool result = true;
    for (int i = 0; number[i] != 0 && result; i++)
    {
        if (!my_isdigit(number[i]))
        {
            result = (i == 0) && (number[i] == '+');
        }
    }
    return result;
}
