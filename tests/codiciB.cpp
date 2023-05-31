/**
 *  Purpose:    test 2023/05/19
 *  Author:     Emanuele Rizzolo
 *  Class:      3BIN
 *  Date:       2023/05/19
 *  Note:
 */

/*
Codici (codiciB)
Il Ministero dell’Inferno ha deciso di modificare il formato dei file di testo con
cui si pubblicano i dati dei comuni italiani.
Si crei un’applicazione che consenta di leggere secondo il formato “vecchio” i
dati contenuti in un file di input e scrivere gli stessi dati in un file di output
secondo il formato “nuovo”.
Il formato “vecchio” memorizza i dati di ciascun comune in una riga nel formato
(CSV comma separated value) seguente:
<ordine>,<sigla>,<comune>,<note>,<belfiore>,<istat>,<elettorale>
ad esempio: 3,LC,”abbadia lariana”,,A005,097.001,1.3.98..1.
dove:
◦ <ordine> è il numero (naturale) d’ordine del comune (3);
◦ <sigla> è la sigla della provincia cui appartiene il comune (“LC”);
◦ <comune> è la denominazione del comune, delimitata dal carattere
doppio apice “ (‘“abbadia lariana”’);
◦ <note> è normalmente una stringa vuota ma può contenere un numero
naturale se vi sono casi particolari(“”);
◦ <belfiore> è il codice Belfiore del comune, costituito da una lettera
maiuscola e tre cifre decimali (A005).
◦ <istat> è il codice ISTAT del comune, con un punto tra le prime tre e le
ultime tre cifre (097.001);
◦ <elettorale> è il codice elettorale del comune con la cifra 0 sostituita da
un carattere punto (1.3.98..1.).
Il formato “nuovo” memorizza i dati di ciascun comune in una riga nel formato
(CSV comma separated value) seguente:
<ordine>,<comune>,<sigla>,<elettorale1>,<istat1>,<belfiore1>
ad esempio: 3,ABBADIA LARIANA,LC,1030980010,097001,A005
dove:
◦ <ordine> è il numero (naturale) d’ordine del comune (3);
◦ <comune> è la denominazione del comune, priva di delimitatori e
convertita in maiuscolo (“ABBADIA LARIANA”);
◦ <sigla> è la sigla della provincia cui appartiene il comune (“LC”);
◦ <elettorale1> è il codice elettorale del comune, costituito da sole cifre
decimali con la cifra 0 al posto del carattere punto (1030980010);
◦ <istat1> è il codice ISTAT del comune, costituito da sei cifre decimali
senza il punto separatore (097001);
◦ <belfiore1> è il codice Belfiore del comune, se corretto, oppure la stringa
‘****’ (quattro asterischi) (A005).
Scrivere un'applicazione che riceva da riga comando un parametro opzionale
indicante la provincia dei comuni i cui dati devono essere inseriti nel file di
output (se non fornita si intende tutte le province), legga dal file “codiciB.txt”
(vecchio formato) e produca il file “codicinew.txt” (nuovo formato).
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

const bool DEBUG = true;

#define MAX_NAME 60
#define MAX_SIGLA 2
#define MAX_ELETTORALE 15
#define MAX_ISTAT 7
#define MAX_BELFIORE 4
#define BUFFER_SIZE 1000

struct comune_t
{
    int ordine;                          // order number
    char name[MAX_NAME + 1];             // name
    char sigla[MAX_SIGLA + 1];           // sigla provincia
    char elettorale[MAX_ELETTORALE + 1]; // codice elettorale
    char istat[MAX_ISTAT + 1];           // codice ISTAT
    char belfiore[MAX_BELFIORE + 1];     // codice belfiore
};

bool decode(char *line, comune_t &c);
void write(ostream &out, const comune_t &c);

// main function
int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        const char empty[] = "";
        const char *provincia = argc == 2 ? argv[1] : empty;
        ifstream infile("codiciB.txt"); // automatic open with default open mode in
        if (infile.is_open())
        {
            ofstream outfile("codicinew.txt"); // automatic open with default open mode out
            if (outfile)
            {
                char letti[BUFFER_SIZE];
                comune_t c;
                while (infile.getline(letti, BUFFER_SIZE))
                {
                    if (DEBUG)
                        cout << letti << endl;
                    if (decode(letti, c)) // ignore wrong lines
                    {
                        if (DEBUG)
                            write(cout, c);
                        if (provincia == empty || strcmp(provincia, c.sigla) == 0) // filter on provincia
                        {
                            write(outfile, c);
                        }
                    }
                    cout << letti << endl;
                }
                outfile.close(); // close file
            }
            else
            {
                cerr << "failed to open output file" << endl;
            }
            infile.close(); // close file
        }
        else
        {
            cerr << "failed to open input file" << endl;
        }
    }
    else
    {
        cerr << "Usage " << argv[0] << " [<sigla>]" << endl;
    }
    // successful termination
    return 0;
}

bool decode(char *line, comune_t &c)
{
    char *next = line, *comma = strchr(line, ',');
    if (comma == nullptr) // no comma ???
        return false;
    if (sscanf(next, "%d", &c.ordine) == 0) // not an integer ???
        return false;

    comma = strchr(next = comma + 1, ',');
    if (comma == nullptr) // no comma ???
        return false;
    *comma = 0; // terminate sigla
    if (strlen(next) != 2)
        return false;
    strcpy(c.sigla, next);

    comma = strchr(next = comma + 1, ',');
    if (comma == nullptr) // no comma ???
        return false;
    --comma; // should be quotes
    if (*next != '"' || *comma != '"')
        return false;
    *comma = 0; // terminate comune
    strcpy(c.name, next + 1);

    comma = strchr(next = comma + 2, ','); // ",...
    if (comma == nullptr)                  // no comma ???
        return false;
    *comma = 0; // terminate note

    comma = strchr(next = comma + 1, ',');
    if (comma == nullptr) // no comma ???
        return false;
    *comma = 0; // terminate belfiore
    if (strlen(next) != 4)
        return false;
    strcpy(c.belfiore, next);

    comma = strchr(next = comma + 1, ',');
    if (comma == nullptr) // no comma ???
        return false;
    *comma = 0; // terminate istat
    if (strlen(next) != 7)
        return false;
    strcpy(c.istat, next);

    next = comma + 1; // first of elettorale
    strcpy(c.elettorale, next);

    return true; // decode completed ...
}

void writeWithoutSeparator(ostream &out, const char *s, char separator = '.')
{
    while (*s != 0)
    {
        if ((*s) != separator)
            out << *s;
        ++s;
    }
}

void outUpper(ostream &out, const char *s)
{
    while (*s != 0)
    {
        char c = *s;
        if ('a' <= c && c <= 'z')
            out << (char)(c + 'A' - 'a');
        else
            out << c;
        ++s;
    }
}

void outDotsZero(ostream &out, const char *s)
{
    while (*s != 0)
    {
        if ('.' == *s)
            out << '0';
        else
            out << *s;
        ++s;
    }
}

void write(ostream &out, const comune_t &c)
{
    out << c.ordine;
    out << ",";
    outUpper(out, c.name);
    out << "," << c.sigla;
    out << ",";
    outDotsZero(out, c.elettorale);
    out << ",";
    writeWithoutSeparator(out, c.istat);
    out << "," << c.belfiore;
    out << endl;
}
