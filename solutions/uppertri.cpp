/*
	Purpose:    stampa sequenza in forma triangolare
	Author:     Emanuele Rizzolo
	Class:      3XIN
	Date:       2023/01/12
	Note:
*/
/*
	Matrice triangolare (superiore) (uppertri)
	Descrizione del problema
	Dato un numero naturale positivo R, produrre in output una tabella di R righe
	contenente i numeri naturali da 0 a R⋅(R+1)/2−1, i primi R nella prima riga,
	i successivi R-1 nella seconda, e così via.
	Assunzione: R≤10^6.
	Formato di input: leggere R da tastiera, (senza controlli di validità).
	Formato di output: il risultato richiesto, cioè la tabella di R righe.
	Esempi:
	Input 	Output	Spiegazione
	1		0		Un unico valore nella prima ed unica riga
	3		0 1 2	Tre valori nella prima riga, due nella seconda ed il sesto
			3 4		nella terza ( 3⋅(3+1)/2−1=5 )
			5
	4		0 1 2 3	Quattro valori nella prima riga, tre nella seconda, due
			4 5 6	nella terza e l'ultimo nella quarta ( 4⋅(4+1)/2−1=9 )
			7 8
			9
	Limiti: tempo 10s, memoria 1KB.
	Nota: che regola seguono i valori nella prima colonna?
	Il primo elemento della i-esima riga (0<=i<nRighe) è R+(R-1)+(R-2)+...+(R+1-i) = i*R-(0+1+2+...+i-1) = i*R-i*(i-1)/2

*/

#include <iostream>

using namespace std;

#define DEBUG 0

int main(int argc, char *argv[])
{
	unsigned int R;
	cerr << "Immetti il numero naturale positivo R (0<R<=10^6):";
	cin >> R;
	unsigned long long int value = 0; // valore attuale
	for (int row = 0; row < R; row++)
	{
		cout << value;
		value++;
		for (int inRow = 1; inRow < R - row; inRow++)
		{
			cout << " " << value; // con separatore
			value++;
		}
		cout << endl;
	}

	// successful termination
	return 0;
}
