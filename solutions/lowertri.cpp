/*
	Purpose:    stampa sequenza in forma triangolare
	Author:     Emanuele Rizzolo
	Class:      3xIN
	Date:       2023/01/12
	Note:
*/
/*
	Matrice triangolare (inferiore) (lowertri)
	Descrizione del problema
	Dato un numero naturale positivo N, produrre in output una tabella contenente
	gli N numeri naturali da 0 a N-1, in cui la prima riga contiene un elemento, la
	seconda due, e così via.
	Assunzione: N≤10^9 .
	Formato di input: leggere N da tastiera, (senza controlli di validità).
	Formato di output: il risultato richiesto, cioè la tabella contenente gli N valori.
	Esempi:
	Input	Output	Spiegazione
	1 		0		Un unico valore nella prima riga
	4		0		Un valore nella prima riga, due nella seconda ed il quarto
			1 2		nella terza
			3
	10		0		Un valore nella prima riga, due nella seconda, tre nella terza
			1 2		e quattro nella quarta
			3 4 5
			6 7 8 9
	Limiti: tempo 1s, memoria 1KB.
	Nota: che regola seguono i valori nella prima colonna?
	Il primo elemento della i-esima riga (0<=i<nRighe) è i*(i+1)/2 = 1+2+...+i

*/

#include <iostream>

using namespace std;

#define DEBUG 0

int main(int argc, char *argv[])
{
	unsigned int N;
	cerr << "Immetti il numero naturale positivo N (0<N<=10^9):";
	cin >> N;
	unsigned int value = 0;	 // valore attuale
	unsigned int perRow = 1; // numero di valori della riga attuale
	unsigned int inRow = 0;	 // numero attuale di valori sulla riga

	while (value < N) // ripeti mentre ci sono valori
	{
		if (inRow == 0) // primo valore della riga
		{
			if (value > 0)
				cout << endl; // inizia una nuova riga
		}
		else
			cout << " "; // separatore
		cout << value;
		value++;
		inRow++;
		if (inRow == perRow) // finita questa riga
		{
			perRow++;
			inRow = 0;
		}
	}
	cout << endl;

	// successful termination
	return 0;
}
