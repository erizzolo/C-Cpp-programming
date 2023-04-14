/**
 * Test 2023-03-30
 * Author:  ER
 * Date:    2023/03/30
 * Note:
 */

/*
Piatti (menu)
Realizzare un’applicazione che riceva l’input da riga comando e consenta di
visualizzare i dati dei piatti offerti da un ristorante che soddisfano i criteri
specificati da riga comando.
I dati dei piatti sono quelli disponibili nel file menu.h allegato, che è possibile
copiare o includere nel sorgente dell’applicazione.
Il formato del comando per l’utilizzo dell’applicazione deve essere il seguente:
menu.exe <ricerca> <valore 1> <valore 2>
ad es. menu.exe c dessert
ad es. menu.exe p 1.00 6.50
ad es. menu.exe v false
ad es. menu.exe a
dove:
◦ <ricerca> specifica il tipo di criterio da utilizzare per la ricerca;
◦ <valore 1> e <valore 2> sono i valori da utilizzare per alcuni criteri di
ricerca (per alcuni criteri non devono essere specificati).
Sono possibili i seguenti tipi di ricerca:
◦ c = ricerca per nome: <valore 1> è il nome della categoria;
◦ p = ricerca per prezzo: <valore 1> e <valore 2> sono il valore minimo e
massimo del prezzo che deve avere un piatto per essere visualizzato;
◦ v = ricerca per piatti vegan: <valore 1> è il valore (true oppure false) che
deve avere l’attributo vegan di un piatto per essere visualizzato;
◦ a = tutti i piatti devono essere visualizzati.
Qualora l’applicazione venga eseguita senza il numero corretto di argomenti o
qualora un argomento non sia corretto, essa deve:
◦ visualizzare sul flusso standard di errore (cerr) un messaggio con il formato
corretto del comando;
◦ terminare restituendo codice di errore -1 per errato numero di argomenti e
-2 per argomento/i non corretto/i.
Nel caso “normale” l’applicazione deve visualizzare sul flusso standard di
output i dati dei piatti che soddisfano i criteri specificati.
È necessario che la selezione dei piatti da visualizzare e la visualizzazione
dei piatti selezionati siano realizzate in due funzioni separate, definite con
opportuni parametri.
Si noti che nel file allegato è stato definito l’operatore << per visualizzare, ad
esempio sul flusso standard di output, un piatto usando la sintassi:
cout << thePlateToBeShown << endl;
*/
#include "menu.h"

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const int SUCCESS = 0;
const int WRONG_NUMBER = -1;
const int WRONG_ARGUMENT = -2;

void usage(const char *executable);
size_t selectAll(piatto selected[]);
size_t selectCategory(piatto selected[], const char *category);
size_t selectPrice(piatto selected[], double min, double max);
size_t selectVegan(piatto selected[], bool vegan);
void showSelected(const piatto selected[], size_t howMany);

int main(int argc, char *argv[])
{
    int result = SUCCESS;
    piatto selected[numPiatti]; // selected elements
    size_t numSelected = 0;     // none so far
    switch (argc)
    {
    case 2:
        // only option a
        if (strcmp(argv[1], "a") == 0)
        {
            numSelected = selectAll(selected);
        }
        else
        {
            result = WRONG_ARGUMENT;
        }
        break;
    case 3:
        // option c or v
        if (strcmp(argv[1], "c") == 0)
        {
            numSelected = selectCategory(selected, argv[2]);
        }
        else if (strcmp(argv[1], "v") == 0)
        {
            numSelected = selectVegan(selected, strcmp(argv[2], "true") == 0);
        }
        else
        {
            result = WRONG_ARGUMENT;
        }
        break;
    case 4:
        // only option p
        if (strcmp(argv[1], "p") == 0)
        {
            double min, max;
            int valid = sscanf(argv[2], "%lg", &min) + sscanf(argv[3], "%lg", &max);
            if (valid == 2)
            {
                numSelected = selectPrice(selected, min, max);
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

    if (result == SUCCESS)
    {
        showSelected(selected, numSelected);
    }
    else
    {
        usage(argv[0]);
    }
    return result;
}

size_t selectAll(piatto selected[])
{
    size_t result = 0;
    for (size_t i = 0; i < numPiatti; ++i)
    {
        if (true) // sorry about that
        {
            selected[result] = menu[i];
            ++result;
        }
    }
    return result;
}
size_t selectCategory(piatto selected[], const char *category)
{
    size_t result = 0;
    for (size_t i = 0; i < numPiatti; ++i)
    {
        if (strcmp(menu[i].category, category) == 0)
        {
            selected[result] = menu[i];
            ++result;
        }
    }
    return result;
}
size_t selectPrice(piatto selected[], double min, double max)
{
    size_t result = 0;
    for (size_t i = 0; i < numPiatti; ++i)
    {
        if (min <= menu[i].price && menu[i].price <= max)
        {
            selected[result] = menu[i];
            ++result;
        }
    }
    return result;
}
size_t selectVegan(piatto selected[], bool vegan)
{
    size_t result = 0;
    for (size_t i = 0; i < numPiatti; ++i)
    {
        if (menu[i].vegan == vegan)
        {
            selected[result] = menu[i];
            ++result;
        }
    }
    return result;
}

void showSelected(const piatto selected[], size_t howMany)
{
    for (size_t i = 0; i < howMany; i++)
    {
        cout << selected[i] << endl;
    }
}

void usage(const char *executable)
{
    cerr << executable << " <ricerca> <valore 1> <valore 2>" << endl;
}
