/**
 * Test 2023-03-30
 * Author:  ER
 * Date:    2023/03/30
 * Note:
 */

/*
Pianeti (planet)
Realizzare un’applicazione che riceva l’input da riga comando e consenta di
visualizzare i dati dei pianeti che soddisfano i criteri specificati da riga
comando.
I dati dei pianeti sono quelli disponibili nel file planet.h allegato, che è possibile
copiare o includere nel sorgente dell’applicazione.
Il formato del comando per l’utilizzo dell’applicazione deve essere il seguente:
planet.exe <ricerca> <valore 1> <valore 2>
ad es. planet.exe n Earth
ad es. planet.exe m 1E24 1E25
ad es. planet.exe s 0 0
ad es. planet.exe a
dove:
◦ <ricerca> specifica il tipo di criterio da utilizzare per la ricerca;
◦ <valore 1> e <valore 2> sono i valori da utilizzare per alcuni criteri di
ricerca (per alcuni criteri non devono essere specificati).
Sono possibili i seguenti tipi di ricerca:
◦ n = ricerca per nome: <valore 1> è il nome del pianeta;
◦ m = ricerca per massa: <valore 1> e <valore 2> sono il valore minimo e
massimo della massa che deve avere un pianeta per essere visualizzato;
◦ s = ricerca per satelliti: <valore 1> e <valore 2> sono il numero minimo e
massimo dei satelliti che deve avere un pianeta per essere visualizzato;
◦ a = tutti i pianeti devono essere visualizzati.
Qualora l’applicazione venga eseguita senza il numero corretto di argomenti o
qualora un argomento non sia corretto, essa deve:
◦ visualizzare sul flusso standard di errore (cerr) un messaggio con il formato
corretto del comando;
◦ terminare restituendo codice di errore -1 per errato numero di argomenti e
-2 per argomento/i non corretto/i.
Nel caso “normale” l’applicazione deve visualizzare sul flusso standard di
output i dati dei pianeti che soddisfano i criteri specificati.
È necessario che la selezione dei pianeti da visualizzare e la visualizzazione
dei pianeti selezionati siano realizzate in due funzioni separate, definite con
opportuni parametri.
Si noti che nel file allegato è stato definito l’operatore << per visualizzare, ad
esempio sul flusso standard di output, un pianeta usando la sintassi:
cout << thePlanetToBeShown << endl;
*/
#include "planet.h"

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const int SUCCESS = 0;
const int WRONG_NUMBER = -1;
const int WRONG_ARGUMENT = -2;

void usage(const char *executable);
void selectAll(bool selected[]);
void selectName(bool selected[], const char *name);
void selectMass(bool selected[], double min, double max);
void selectSatellites(bool selected[], int min, int max);
void showSelected(const bool selected[]);

int main(int argc, char *argv[])
{
    int result = SUCCESS;
    bool selected[numPlanets]; // selected elements
    for (size_t i = 0; i < numPlanets; i++)
    {
        selected[i] = false; // none selected
    }
    if (argc < 2)
    {
        result = WRONG_NUMBER;
    }
    else if (strlen(argv[1]) != 1)
    {
        result = WRONG_ARGUMENT;
    }
    else
    {
        switch (argv[1][0])
        {
        case 'a':
            // only option a
            if (argc == 2)
            {
                selectAll(selected);
            }
            else
            {
                result = WRONG_ARGUMENT;
            }
            break;
        case 'n':
            if (argc == 3)
            {
                selectName(selected, argv[2]);
            }
            else
            {
                result = WRONG_ARGUMENT;
            }
            break;
        case 'm':
            if (argc == 4)
            {
                double min, max;
                int valid = sscanf(argv[2], "%lg", &min) + sscanf(argv[3], "%lg", &max);
                if (valid == 2)
                {
                    selectMass(selected, min, max);
                }
                else
                {
                    result = WRONG_ARGUMENT;
                }
            }
            else
            {
                result = WRONG_ARGUMENT;
            }
            break;
        case 's':
            if (argc == 4)
            {
                int min, max;
                int valid = sscanf(argv[2], "%d", &min) + sscanf(argv[3], "%d", &max);
                if (valid == 2)
                {
                    selectSatellites(selected, min, max);
                }
                else
                {
                    result = WRONG_ARGUMENT;
                }
            }
            else
            {
                result = WRONG_ARGUMENT;
            }
            break;
        default:
            result = WRONG_NUMBER;
        }
    }
    if (result == SUCCESS)
    {
        showSelected(selected);
    }
    else
    {
        usage(argv[0]);
    }
    return result;
}

void selectAll(bool selected[])
{
    for (size_t i = 0; i < numPlanets; ++i)
    {
        selected[i] = true; // sorry about that
    }
}

void selectName(bool selected[], const char *name)
{
    for (size_t i = 0; i < numPlanets; ++i)
    {
        selected[i] = strcmp(planets[i].name, name) == 0;
    }
}
void selectMass(bool selected[], double min, double max)
{
    for (size_t i = 0; i < numPlanets; ++i)
    {
        selected[i] = min <= planets[i].mass && planets[i].mass <= max;
    }
}
void selectSatellites(bool selected[], int min, int max)
{
    for (size_t i = 0; i < numPlanets; ++i)
    {
        selected[i] = min <= planets[i].numSatellites && planets[i].numSatellites <= max;
    }
}

void showSelected(const bool selected[])
{
    for (size_t i = 0; i < numPlanets; ++i)
    {
        if (selected[i])
        {
            cout << planets[i] << endl;
        }
    }
}

void usage(const char *executable)
{
    cerr << executable << " <ricerca> <valore 1> <valore 2>" << endl;
}
