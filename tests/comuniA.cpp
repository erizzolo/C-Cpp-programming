/**
 *  Purpose:    test 2023/05/19
 *  Author:     Emanuele Rizzolo
 *  Class:      3BIN
 *  Date:       2023/05/19
 *  Note:
 */

/*
Comuni (comuniA)
Il Ministero dell’Inferno ha deciso di modificare il formato dei file di testo con
cui si pubblicano i dati dei comuni italiani.
Si crei un’applicazione che consenta di leggere secondo il formato “vecchio” i
dati contenuti in un file di input e scrivere gli stessi dati in un file di output
secondo il formato “nuovo”.
Il formato “vecchio” memorizza i dati di ciascun comune in una riga nel formato
(CSV comma separated value) seguente:
<ordine>,<comune>,<sigla>,<note>,<uomini>,<donne>,<totale>
ad esempio: 3,ABBADIA LARIANA,LC,,1.565,1.637,3.202
dove:
• <ordine> è il numero (naturale) d’ordine del comune (3);
• <comune> è la denominazione del comune (“ABBADIA LARIANA”);
• <sigla> è la sigla della provincia cui appartiene il comune (“LC”);
• <note> è normalmente una stringa vuota ma può contenere un numero
naturale se vi sono casi particolari(“”);
• <uomini> è un numero naturale, con il carattere ‘.’ come separatore delle
migliaia, corrispondente alla popolazione “maschile” censita (1.565);
• <donne> è un numero naturale, con il carattere ‘.’ come separatore delle
migliaia, corrispondente alla popolazione “femminile” censita (1.637);
• <totale> è un numero naturale, con il carattere ‘.’ come separatore delle
migliaia, corrispondente alla popolazione “totale” censita (3.202).
Il formato “nuovo” memorizza i dati di ciascun comune in una riga nel formato
(CSV comma separated value) seguente:
<ordine>,<sigla>,<comune>,<totale>,<%uomini>,<%donne>
ad esempio: 3,LC,”ABBADIA LARIANA”,3202,49%,51%
dove:
◦ <ordine> è il numero (naturale) d’ordine del comune (3);
◦ <sigla> è la sigla della provincia cui appartiene il comune (“LC”);
◦ <comune> è la denominazione del comune, delimitata dal carattere
doppio apice “ (‘“ABBADIA LARIANA”’);
◦ <totale> è un numero naturale, privo di separatore delle migliaia,
corrispondente alla popolazione “totale” censita (3202).
◦ <%uomini> è un numero naturale seguito dal carattere ‘%’ corrispondente
alla percentuale della popolazione “maschile” censita rispetto al totale
arrotondata (49%) [1565/3202 = 0,4887 → arrotondato a 49];
◦ <%donne> è un numero naturale seguito dal carattere ‘%’ corrispondente
alla percentuale della popolazione “femminile” censita rispetto al totale
arrotondata (51%) [1637/3202 = 0,5112 → arrotondato a 51].
Scrivere un'applicazione che riceva da riga comando un parametro opzionale
indicante la provincia dei comuni i cui dati devono essere inseriti nel file di
output (se non fornita si intende tutte le province), legga dal file “comuniA.txt”
(vecchio formato) e produca il file “comuninew.txt” (nuovo formato).
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

#define BUFFER_SIZE 1000

const bool DEBUG = true;

struct comune_t
{
    int ordine;     // order number
    char name[100]; // name
    char sigla[3];  // sigla provincia
    int total;      // total population
    int men;        // men %
    int women;      // women %
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
        ifstream infile("comuniA.txt"); // automatic open with default open mode in
        if (infile.is_open())
        {
            ofstream outfile("comuninew.txt"); // automatic open with default open mode out
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

int mysscanf(const char *input, const char *, int *variable)
{
    // format is interpreted as %d, '.' in input are ignored
    int result = 0, value = 0, index = 0;
    bool exit = false;
    do
    {
        if (input[index] == '.')
        { // ignore it
        }
        else if ('0' <= input[index] && input[index] <= '9')
        { // valid digit
            result = 1;
            value = value * 10 + (input[index] - '0');
        }
        else
            exit = true;
        ++index;
    } while (!exit);
    if (result > 0) // assign if valid
        *variable = value;
    return result;
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
    *comma = 0; // terminate comune
    strcpy(c.name, next);
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
    *comma = 0; // terminate note
    comma = strchr(next = comma + 1, ',');
    if (comma == nullptr) // no comma ???
        return false;
    *comma = 0;                            // terminate men
    if (mysscanf(next, "%d", &c.men) == 0) // not an integer ???
        return false;
    comma = strchr(next = comma + 1, ',');
    if (comma == nullptr) // no comma ???
        return false;
    *comma = 0;                              // terminate women
    if (mysscanf(next, "%d", &c.women) == 0) // not an integer ???
        return false;
    if (mysscanf(comma + 1, "%d", &c.total) == 0) // not an integer ???
        return false;
    return true; // decode completed ...
}

void write(ostream &out, const comune_t &c)
{
    out << c.ordine;
    out << "," << c.sigla;
    out << ",\"" << c.name << "\"";
    out << "," << c.total;
    int menpc = lround(100.0 * c.men / c.total);
    out << "," << menpc << "%";
    int womenpc = lround(100.0 * c.women / c.total);
    out << "," << womenpc << "%";
    out << endl;
}
