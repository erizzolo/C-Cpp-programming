/*
    Purpose:    conteggio ricavo totale
    Author:     Emanuele Rizzolo
    Class:      3CIN
    Date:       2016/12/12
    Note:
*/
/*
    Trasporti urbani ( actv )
    Descrizione del problema
    Una linea di trasporti urbani effettua un percorso con N fermate,
    F1, F2, …, FN, dove F1 ed FN sono i due capolinea.
    Ciascuno degli N-1 tratti del percorso (il tratto Ti è quello tra
    la fermata Fi e la successiva Fi+1) ha un costo pari a Ci, per ciascun passeggero.
    Ad ogni fermata Fi (per i da 1 a N-1) salgono nel mezzo di trasporto Ei passeggeri
    e ne scendono Ui. Al capolinea FN scendono tutti i passeggeri (eventualmente)
    presenti sul mezzo di trasporto, ma nessuno sale.
    Ogni passeggero paga regolarmente il biglietto per il percorso effettuato ed il mezzo di trasporto ha capacità infinita.
    Quanto ricava complessivamente l'azienda di trasporti dalla corsa del mezzo di trasporto tra un capolinea e l'altro?
    Assunzione: 2 ≤ N ≤ 10^6, 0 ≤ Ei, Ui ≤ 100, 1 ≤ Ci ≤ 10.
    È garantito che il numero di passeggeri presenti nel mezzo di trasporto non sia mai negativo.
    Formato di input: la prima riga contiene N, la seconda riga contiene gli N-1 valori Ci separati da spazio,
    la terza riga contiene gli N-1 valori Ei separati da spazio, la quarta riga contiene gli N-1 valori Ui separati da spazio.
    Formato di output: il risultato richiesto, cioè il totale pagato dai passeggeri del mezzo di trasporto.
    Esempi:
    Input		Output	Spiegazione
    2			15		5 passeggeri effettuano il tratto tra i due capolinea, che ha un costo di 3 ciascuno, quindi 5x3=15
    3
    5
    0

    3			10		Tratto	Passeggeri	Costo unitario	Totale tratto
    1 2					1-2		4			1				4
    4 2					2-3		3			2				6
    0 3

    Limiti: tempo 1s, memoria 32MB.

*/

// directive for standard io functions
#include <iostream>

using namespace std;

#define DEBUG 0

// funzione principale
int main(int argc, char *argv[])
{
    // prompt utente
    int N;
    cerr << "Immetti il numero di fermate N (2<=N<=10^6):";
    cin >> N;
    int C[N - 1];
    cerr << "Immetti il costo unitario degli " << (N - 1) << " tratti (1<=Ci<=10):";
    for (int tratto = 0; tratto < N - 1; tratto++)
    {
        cin >> C[tratto];
    }
    int E[N - 1];
    cerr << "Immetti il numero di passeggeri che salgono alle prime " << (N - 1) << " fermate (0<=Ei<=100):";
    for (int fermata = 0; fermata < N - 1; fermata++)
    {
        cin >> E[fermata];
    }
    cerr << "Immetti il numero di passeggeri che scendono alle prime " << (N - 1) << " fermate (0<=Ui<=100):";
    for (int fermata = 0; fermata < N - 1; fermata++)
    {
        int uscenti;
        cin >> uscenti;
        E[fermata] -= uscenti;
    }
    // computing
    // worst case: N=1e6, Ci=10,Ei=100,Ui=0 per i=0..N-2
    // ricavo totale=10*(100+200+300+...+(N-1)*100)=1000*(1+2+3+...+(N-1))=1000*(N-1)*N/2=1e9*(999999)/2 circa 5e14: serve long long
    long long int ricavoTotale = 0, passeggeri = 0;
    for (int fermata = 0; fermata < N - 1; fermata++)
    {
        passeggeri += E[fermata];
        ricavoTotale += passeggeri * C[fermata];
    }
    // output result
    cout << ricavoTotale << endl;
    // successful termination
    return 0;
}
