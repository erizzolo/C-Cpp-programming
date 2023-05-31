/*
    Purpose:    Aggiornamenti (aggiorna)
    Author:     Emanuele Rizzolo
    Class:      3CIN
    Date:       2017/05/02
    Note:
*/
/*

    Aggiornamenti (aggiorna)
    È dato un file di testo (il “dizionario”) contenente le definizioni delle
    parole in lingua S. In tale lingua le parole contengono da un minimo di tre
    fino ad un massimo di dieci caratteri latini e ciascuna parola può avere
    più definizioni (fino ad un massimo	di 26), a seconda dell’ambito in cui
    viene utilizzata.
    Di conseguenza il dizionario è formato da più righe ciascuna con il seguente
    formato:
    <parola><:><n><spazio><definizione>
    dove <parola> è la parola definita, <:> è un separatore costante (:),
    <n> è una singola lettera maiuscola dell'alfabeto latino indicante l'ambito
    della definizione, <spazio> è un singolo spazio separatore e <definizione>
    è una frase (di un'unica riga) che spiega il significato della parola.
    Ad esempio, il dizionario può contenere le seguenti righe:

    ancora:A Elemento in ferro o acciaio, proprio... [omissis]
    ancora:B Elemento di ferro dolce che comandato da... [omissis]
    ancora:C Nei moderni orologi, parte dello scappamento... [omissis]

    Periodicamente vengono rilasciati degli aggiornamenti per inserire i
    neologismi, eliminare le voci obsolete o correggere le definizioni imprecise.
    Il file di testo che descrive gli aggiornamenti è formato da più righe
    (massimo 1000), ciascuna con il seguente formato:
    <operazione><parola><:><n>[<spazio><definizione>]
    dove <operazione> è un singolo carattere indicante il tipo di modifica da effettuare,
    <parola> è la parola cui la modifica deve essere applicata, <:> è un separatore
    costante (:), <n> è una singola lettera maiuscola dell'alfabeto latino indicante
    l'ambito della definizione, <spazio> è un singolo spazio separatore e <definizione>
    è una frase (di un'unica riga) che spiega il significato della parola.
    Questi ultimi due elementi sono presenti solo per alcuni tipi di modifiche.
    I caratteri indicanti le possibili modifiche sono i seguenti:
    + nuova parola o nuova definizione in un nuovo ambito (definizione presente)
    / parola obsoleta nell'ambito, voce da rimuovere (definizione assente)
    = parola già definita nell'ambito, definizione sostitutiva (definizione presente)
    Ad esempio, l'aggiornamento può contenere può contenere le seguenti righe:

    /ancora:B
    =ancora:C Nei vecchi orologi, parte dello scappamento... [omissis]
    +ancora:D Nel linguaggio HTML, elemento che... [omissis]

    in base alle quali il nuovo dizionario verrebbe ad essere:

    ancora:A Elemento in ferro o acciaio, proprio... [omissis]
    ancora:C Nei vecchi orologi, parte dello scappamento... [omissis]
    ancora:D Nel linguaggio HTML, elemento che... [omissis]Esercizi

    Scrivere un'applicazione che riceva tre parametri da riga comando, indicanti
    rispettivamente il (nome del) file di dizionario attuale, il file degli aggiornamenti ed
    il file del nuovo dizionario, produca quest'ultimo leggendo i dati dei primi due.
    Facoltativamente, considerare il dizionario attuale e l'aggiornamento ordinati per
    parola/ambito e produrre un nuovo dizionario anch'esso ordinato.
    Facoltativamente, prevedere quali anomalie si possono verificare (ad esempio
    modifica di rimozione per una voce non presente) e scrivere su un (altro) file (di log)
    dei messaggi di errore significativi per ciascuna anomalia.
*/

// directive for standard io functions
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <limits>
#include <algorithm>

using namespace std;

const bool DEBUG = true;

#define INSERT ('+')
#define DELETE ('/')
#define UPDATE ('=')
#define PROCESSED (' ')

const char VALID_OPERATIONS[]{INSERT, DELETE, UPDATE, 0}; // make it a null terminated string

#define MAX_WORD_LENGTH (30)
#define MAX_DEFINITION_LENGTH (1000)

#define MAX_ENTRY_LENGTH (MAX_WORD_LENGTH + 3 + MAX_DEFINITION_LENGTH)
#define BUFFER_SIZE (1 + MAX_ENTRY_LENGTH)

struct entry_t // a dictionary entry
{
    char word[MAX_WORD_LENGTH + 1];
    char scope;
    char definition[MAX_DEFINITION_LENGTH + 1];
};

struct update_t // an update entry
{
    char operation;
    entry_t entry;
};

#define MAX_UPDATES (1000)
// update_t updates[MAX_UPDATES]; global ?

bool decodeEntry(char *line, entry_t &entry);                                   // decodes an entry from a string
bool writeEntry(ostream &file, const entry_t &entry, bool newLine = true);      // writes an entry to file
bool decodeUpdate(char *line, update_t &update);                                // decodes an update from a string
int compareEntries(const entry_t &first, const entry_t &second);                // compare entries
size_t readUpdates(istream &file, update_t updates[]);                          // read all updates from file
void sortUpdates(update_t updates[], size_t numUpdates);                        // sort all updates
size_t searchUpdate(update_t updates[], size_t nUpdates, const entry_t &entry); // search for a matching update
bool lessByEntry(const update_t &lhs, const update_t &rhs);                     // comparison function

void log(const char *msg, const char *details = "");   // simple text
void log(const entry_t &e, const char *details = "");  // an entry
void log(const update_t &u, const char *details = ""); // an update

// global log file, used by all log functions
ofstream logFile("dizionario.log", ios::app); // explicit open append mode

int main(int argc, char *argv[])
{
    // check parameters
    if (argc != 4)
        log("Wrong number of parameters.");
    else
    {
        ifstream dictFile(argv[1]); // open dictionary file
        if (!dictFile)
            log("Could not open dictionary file ", argv[1]);
        else
        {
            ifstream updFile(argv[2]); // open update file
            if (!updFile)
                log("Could not open update file ", argv[2]);
            else
            {
                ofstream outFile(argv[3]); // open output file
                if (!outFile)
                    log("Could not open output file ", argv[3]);
                else
                {
                    update_t *updates = new update_t[MAX_UPDATES]; // allocate space for updates
                    if (updates == nullptr)
                        log("Cannot allocate memory for updates");
                    else
                    {
                        size_t nUpdates = readUpdates(updFile, updates); // read all updates
                        sortUpdates(updates, nUpdates);                  // sort them to apply binary search
                        if (DEBUG)
                            for (size_t i = 0; i < nUpdates; i++)
                            {
                                cout << i;
                                cout << updates[i].operation;
                                writeEntry(cout, updates[i].entry);
                                cout << endl;
                            }

                        char line[BUFFER_SIZE]; // buffer for a line
                        while (!dictFile.eof())
                        {
                            entry_t entry;                                                       // an entry
                            if (dictFile.getline(line, BUFFER_SIZE) && decodeEntry(line, entry)) // try to read a line and decode an entry
                            {
                                if (DEBUG)
                                {
                                    cout << "searching for ";
                                    writeEntry(cout, entry);
                                }
                                size_t where = searchUpdate(updates, nUpdates, entry);
                                if (DEBUG)
                                {
                                    cout << " found at " << where << "/" << nUpdates << endl;
                                }
                                if (where < nUpdates) // found
                                {
                                    switch (updates[where].operation)
                                    {
                                    case DELETE:
                                        if (DEBUG)
                                        {
                                            cout << "deleting entry ";
                                            writeEntry(cout, entry);
                                        }
                                        break;
                                    case INSERT:
                                        log(updates[where], " Entry already exist:");
                                        log(entry, " will be modified with new definition");
                                    case UPDATE:
                                        strcpy(entry.definition, updates[where].entry.definition);
                                        writeEntry(outFile, entry);
                                    }
                                    updates[where].operation = PROCESSED; // processed
                                }
                                else
                                    writeEntry(outFile, entry);
                            }
                        }
                        for (size_t u = 0; u < nUpdates; u++)
                        {
                            if (updates[u].operation != PROCESSED)
                            {
                                if (updates[u].operation == INSERT)
                                    writeEntry(outFile, updates[u].entry);
                                else
                                {
                                    log(updates[u], " No match found");
                                }
                            }
                        }
                        delete[] updates; // deallocate memory
                    }
                    outFile.close();
                }
                updFile.close();
            }
            dictFile.close();
        }
    }
    logFile.close(); // just in case

    return 0;
}

size_t readUpdates(istream &file, update_t updates[])
{
    size_t result = 0;
    char line[BUFFER_SIZE]; // buffer for a line
    while (!file.eof())
    {
        file.getline(line, BUFFER_SIZE);
        if (decodeUpdate(line, updates[result])) // try to read a line and decode an update
            ++result;
    }
    return result;
}

bool lessByEntry(const update_t &lhs, const update_t &rhs) // comparison function
{
    int cmp = strcmp(lhs.entry.word, rhs.entry.word);
    return cmp < 0 || (cmp == 0 && (lhs.entry.scope < rhs.entry.scope));
}

void sortUpdates(update_t updates[], size_t numUpdates) // sort all updates
{
    sort(updates, updates + numUpdates, lessByEntry);
}

char *decodeWordAndScope(char *line, entry_t &entry) // decodes an entry from a string
{
    char *colon = strchr(line, ':');
    if (colon == nullptr) // not a correct entry
        return nullptr;
    *colon = 0;                                 // word terminator
    strcpy(entry.word, line);                   // copy word to entry
    entry.scope = colon[1];                     // copy scope to entry
    if ('A' > entry.scope || entry.scope > 'Z') // invalid scope
        return nullptr;
    return colon + 2;
}

bool decodeEntry(char *line, entry_t &entry) // decodes an entry from a string
{
    char *next = decodeWordAndScope(line, entry);
    if (next == nullptr || *next != ' ') // no space
        return false;
    strcpy(entry.definition, next + 1); // copy definition to entry
    return true;
}

bool decodeUpdate(char *line, update_t &update) // decodes an update from a string
{
    if (strchr(VALID_OPERATIONS, line[0]) == nullptr) // invalid operation
        return false;
    update.operation = line[0]; // store operation to update
    return (update.operation == DELETE && decodeWordAndScope(line + 1, update.entry)) ||
           decodeEntry(line + 1, update.entry); // process rest of line
}

int cmpScope(const char lhs, const char rhs)
{
    if (lhs < rhs)
        return -1;
    if (lhs > rhs)
        return 1;
    return 0;
}

int cmpWithEntry(const update_t &lhs, const entry_t &rhs) // comparison function
{
    int cmp = strcmp(lhs.entry.word, rhs.word);                   // compare words first
    return cmp == 0 ? cmpScope(lhs.entry.scope, rhs.scope) : cmp; // then scopes
}

size_t searchUpdate(update_t updates[], size_t nUpdates, const entry_t &entry) // search for a matching update
{
    size_t result = nUpdates, end = nUpdates, count = nUpdates, begin = 0;
    while (count > 0)
    {
        size_t middle = begin + count / 2;
        int cmp = cmpWithEntry(updates[middle], entry);
        if (cmp < 0)
            begin = middle + 1;
        else
        {
            end = middle;
            if (cmp == 0)
                result = middle;
        }
        count = end - begin;
    }
    return result;
}
bool writeEntry(ostream &file, const entry_t &entry, bool newLine /* = true */)
{
    file << entry.word << ":" << entry.scope << " " << entry.definition;
    if (newLine)
        file << endl;
    return file.fail();
}

void log(const char *msg, const char *details /* = "" */) // simple text
{
    logFile << msg << details << endl;
}

void log(const entry_t &e, const char *details /* = "" */) // an entry
{
    writeEntry(logFile, e, false);
    logFile << details << endl;
}

void log(const update_t &u, const char *details /* = "" */) // an update
{
    logFile << u.operation;
    writeEntry(logFile, u.entry, false);
    logFile << details << endl;
}
