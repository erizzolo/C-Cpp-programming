/*
    Purpose:    Configurazione (config)
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2023/05/06
    Note:
*/
/*
Configurazione (config)
È dato un file di testo contenente le opzioni di configurazione di un'applicazione.
Tale file è costituito da sezioni il cui inizio è indicato da una riga contenente il
nome della sezione (privo di spazi) racchiuso tra parentesi quadre. Le righe
precedenti la prima sezione esplicita appartengono alla sezione GLOBAL.
Ciascuna opzione ha un nome (privo di spazi) ed un valore (possibilmente con
spazi) ed è specificata nel file con il formato:
<nome>=<valore>
Ad esempio:
DSHELL=/bin/bash
Si noti che possono esservi opzioni con lo stesso nome in sezioni diverse e, a
causa di errori, la stessa opzione può essere specificata più volte all'interno
della stessa sezione; in quest'ultimo caso, vale soltanto l'ultima specifica.
Naturalmente, è possibile che il file contenga righe di commento, che iniziano
con il carattere #, ad esempio il seguente è un commento
# The DSHELL variable specifies the default login shell on your
Scrivere un'applicazione che riceva due(tre) parametri da riga comando,
indicanti rispettivamente il nome del file di configurazione, il nome dell'opzione
da ricercare e, opzionalmente, il nome della sezione in cui effettuare la ricerca,
produca in output il valore dell'opzione, se presente. Nel caso in cui il
parametro indicante la sezione non sia presente, deve essere visualizzato, per
ciascuna delle sezioni in cui l'opzione è specificata, il nome della sezione ed il
valore dell'opzione.
Facoltativamente, prevedere l'aggiunta dell'opzione specificata nella sezione
specificata oppure nella sezione GLOBAL, qualora l'opzione non sia presente.
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const bool DEBUG = true;

#define MAX_LINE_LENGTH (1024)
#define SECTION_START ('[')
#define SECTION_END (']')
#define COMMENT ('#')
#define SEPARATOR ('=')

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4) // check parameters
        cerr << "Wrong number of parameters." << endl;
    else
    {
        ifstream config(argv[1]); // open configuration file
        if (!config)              // if failed, nothing to do
            cerr << "Cannot open " << argv[1] << endl;
        else
        {
            char *option = argv[2];                                             // just a better name
            char *section = argc == 4 ? argv[3] : nullptr;                      // just a better name (optional)
            char line[MAX_LINE_LENGTH + 1];                                     // the line
            char current[MAX_LINE_LENGTH + 1] = "GLOBAL";                       // current section
            bool process = section == nullptr || strcmp(section, current) == 0; // needs processing
            char *where;                                                        // used for searches inside switch
            while (config.getline(line, MAX_LINE_LENGTH, '\n'))
            {
                switch (line[0])
                {
                case SECTION_START: // new section
                    where = strchr(line, SECTION_END);
                    if (where != nullptr) // correct section
                    {
                        *where = 0; // exclude section end
                        strcpy(current, line + 1);
                        process = section == nullptr || strcmp(section, current) == 0; // update needed
                    }
                    break;
                case 0:       // empty line
                case COMMENT: // comment line
                    break;    // nothing to do
                default:      // valid line
                    if (process)
                    {
                        where = strchr(line, SEPARATOR);
                        if (where != nullptr) // not found
                        {
                            *where = 0;                    // terminate to compare
                            if (strcmp(option, line) == 0) // found
                            {
                                *where = SEPARATOR;     // restore separator
                                if (section == nullptr) // show section
                                    cout << "[" << current << "]" << endl;
                                cout << line << endl;
                            }
                        }
                    }
                }
            }
            config.close(); // finally over
        }
    }
    // successful termination
    return 0;
}
