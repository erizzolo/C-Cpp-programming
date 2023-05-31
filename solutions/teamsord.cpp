/*
	Purpose:    Somme parziali con indici
	Author:     Emanuele Rizzolo
	Class:      3XIN
	Date:       2023/04/21
	Note:		There is probably no way to keep within time limits
				with an O(n*n) algorithm like bubble sort...
				Much better with library sort(...)
*/
/*
	Teams forever (teamsord)
	Descrizione del problema
	Ad una competizione sportiva partecipano N atleti, appartenenti ad M squadre
	numerate da 0 a M-1 (ciascun atleta appartiene ad un'unica squadra).
	Ciascun atleta ottiene un punteggio individuale P, e ciascuna squadra
	ottiene un punteggio complessivo S pari alla somma dei punteggi individuali
	ottenuti dagli atleti appartenenti ad essa.
	Dati i punteggi individuali degli atleti, stabilire il punteggio ottenuto dalle squadre
	e l'ordine delle squadre in classifica (a parità di punteggio la squadra con numero
	inferiore precede in classifica quella con numero superiore).
	Assunzione: 1 ≤ M ≤ N ≤ 10^6, 0 ≤ P ≤ 1000.
	Formato di input: la prima riga contiene N (numero di atleti) ed M (numero di squadre)
	separati da uno spazio; ciascuna delle successive N righe contiene la squadra
	di appartenenza ed il punteggio individuale P del singolo atleta, separati da uno spazio.
	Formato di output: M righe contenenti ciascuna il numero della squadra ed il corrispondente
	punteggio complessivo separati da uno spazio, in ordine di classifica.
	Esempi:
	Input	Output	Spiegazione
	4 2		1 10	Vi sono 4 atleti, il primo ed il terzo della squadra 0, il secondo ed il quarto della squadra 1.
	0 5		0 7		La squadra 0 ottiene un punteggio complessivo di 7 (5 del primo atleta e 2 del terzo),
	1 3				la squadra 1 di 10 (3 del secondo atleta e 7 del quarto). La squadra 1 è al primo posto in classifica.
	0 2
	1 7
	Limiti: tempo 20s, memoria 512MB.
*/

// directive for standard io functions
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_ATLETI 1'000'000
#define MAX_SQUADRE 1'000'000
#define MAX_PUNTI_INDIVIDUALI 1000
#define MAX_PUNTI_COMPLESSIVI (MAX_ATLETI * MAX_PUNTI_INDIVIDUALI)

struct posizione
{
	int squadra;		// numero
	unsigned int punti; // punteggio
};

// global because it's too big to fit in the stack
// posizione classifica[MAX_SQUADRE]; // la classifica

// ordinamento
void bubbleSort(posizione a[], int end, int begin = 0);
bool lessThan(const posizione &lhs, const posizione &rhs)
{
	return lhs.punti > rhs.punti ||
		   (lhs.punti == rhs.punti && lhs.squadra < rhs.squadra);
}

int main(int argc, char *argv[])
{
	// read number of athletes and teams
	int nAtleti, nSquadre;
	cin >> nAtleti >> nSquadre;
	// dynamic because it's too big to fit in the stack
	posizione *classifica = new posizione[nSquadre]; // la classifica
	// setup team numbers
	for (int squadra = 0; squadra < nSquadre; squadra++)
	{
		classifica[squadra].squadra = squadra;
		classifica[squadra].punti = 0;
	}
	// read team and points for each athlete
	for (int atleta = 0; atleta < nAtleti; atleta++)
	{
		int squadra, punti;
		cin >> squadra >> punti;
		// update athlete's team points
		classifica[squadra].punti += punti;
	}
	// order teams by points
	// bubbleSort(classifica, nSquadre, 0);	// time exceeded ,,,
	sort(classifica, classifica + nSquadre, lessThan);
	// write team and points
	for (int squadra = 0; squadra < nSquadre; squadra++)
	{
		cout << classifica[squadra].squadra << " " << classifica[squadra].punti << endl;
	}
	// successful termination
	return 0;
}

// ordinamento
void bubbleSort(posizione a[], int end, int begin /* = 0 */)
{
	int limit = begin;		// remember array start limit
	while (end - begin > 1) // at least two element
	{
		int lastSwap = 0, firstChanged = end;
		for (int i = begin + 1; i < end; ++i)
		{
			if (a[i].punti > a[i - 1].punti)
			{
				swap(a[i], a[i - 1]); // something's wrong here: let's fix it
				lastSwap = i;		  // remember last swap
				if (firstChanged > i)
				{
					firstChanged = i - 1; // remember first element changed
				}
			}
		}
		end = lastSwap;													   // Let's start again with end decreased
		begin = firstChanged == limit ? firstChanged : (firstChanged - 1); // starting with the first possibly changed test
	}
}
