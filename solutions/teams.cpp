/*
    Purpose:    Somme parziali con indici
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2023/04/21
    Note:
*/
/*
    Teams (teams)
    Descrizione del problema
    Ad una competizione sportiva partecipano N atleti, appartenenti ad M squadre
    numerate da 0 a M-1 (ciascun atleta appartiene ad un'unica squadra).
    Ciascun atleta ottiene un punteggio individuale P, e ciascuna squadra
    ottiene un punteggio complessivo S pari alla somma dei punteggi individuali
    ottenuti dagli atleti appartenenti ad essa.
    Dati i punteggi individuali degli atleti, stabilire il punteggio ottenuto dalle squadre.
    Assunzione: 1 ≤ M ≤ N ≤ 10^7, 0 ≤ P ≤ 1000.
    Formato di input: la prima riga contiene N (numero di atleti) ed M (numero di squadre)
    separati da uno spazio; ciascuna delle successive N righe contiene la squadra
    di appartenenza ed il punteggio individuale P del singolo atleta, separati da uno spazio.
    Formato di output: M righe contenenti ciascuna il punteggio complessivo della corrispondente squadra.
    Esempi:
    Input   Output  Spiegazione
    4 2     7       Vi sono 4 atleti, il primo ed il terzo appartenenti alla squadra 0, il secondo ed il quarto alla squadra 1.
    0 5     10      La squadra 0 ottiene un punteggio complessivo di 7 (5 del primo atleta e 2 del terzo), la squadra 1 ottiene
    1 3             un punteggio complessivo di 10 (3 del secondo atleta e 7 del quarto).
    0 2
    1 7

    Limiti: tempo 5s, memoria 128MB.
*/

#include <iostream>

using namespace std;

#define MAX_ATLETI 10000000
#define MAX_SQUADRE 10000000
#define MAX_PUNTI_INDIVIDUALI 1000
#define MAX_PUNTI_COMPLESSIVI (MAX_ATLETI * MAX_PUNTI_INDIVIDUALI)

// global because it's too big to fit in the stack
// unsigned long long int puntiSquadre[MAX_SQUADRE]; // i punti delle varie squadre

int main(int argc, char *argv[])
{
    // read number of athletes and teams
    int nAtleti, nSquadre;
    cin >> nAtleti >> nSquadre;
    // dynamic because it's too big to fit in the stack
    unsigned long long int *puntiSquadre = new unsigned long long int[nSquadre](); // i punti delle varie squadre

    // read team and points for each athlete
    for (int atleta = 0; atleta < nAtleti; atleta++)
    {
        int squadra, punti;
        cin >> squadra >> punti;
        // update athlete's team points
        puntiSquadre[squadra] += punti;
    }
    // write team points
    for (int squadra = 0; squadra < nSquadre; squadra++)
    {
        cout << puntiSquadre[squadra] << endl;
    }
    // free memory
    delete[] puntiSquadre;

    // successful termination
    return 0;
}
