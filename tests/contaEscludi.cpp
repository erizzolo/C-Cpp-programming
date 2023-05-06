/*
	Purpose:    La conta ad eliminazione (contaEscludi)
	Author:     Emanuele Rizzolo
	Class:      3XIN
	Date:       2023/04/28
	Note:
*/
/*
	La conta ad eliminazione (contaEscludi)
	La conta è una modalità di sorteggio: serve ad effettuare una scelta tra diverse opzioni,
	ad esempio tra più oggetti o persone. Di solito gli elementi tra cui si deve scegliere
	si dispongono in cerchio. È usata soprattutto dai bambini per decidere chi dovrà svolgere
	un particolare ruolo all'interno di un gioco.
	La conta consiste di solito in una filastrocca cantata scandendo le sillabe.
	Uno dei giocatori decide di guidare la conta: è lui a pronunciare il testo, unendo
	ad ogni sillaba un gesto del braccio e della mano ad indicare a giro uno dei partecipanti
	alla conta e partendo dal primo dopo di lui in senso antiorario.
	In questa variante il giocatore indicato dall'ultima sillaba è eliminato dal giro e
	si prosegue ad una nuova conta con i rimanenti, guidata dal primo rimasto dopo il giocatore
	eliminato in senso antiorario, fino a che l'ultimo partecipante rimasto viene designato.
	Anche in questo case, conoscendo il numero di sillabe della conta e il giocatore da cui parte
	il giro si può dunque conoscere in anticipo chi sarà la persona scelta.
	Dato il numero N di partecipanti alla conta (numerati da 1 a N in senso antiorario)
	ed il numero S di sillabe della filastrocca, determinare chi sarà il partecipante designato
	(cioè l'unico non eliminato) al termine delle N-1 conte effettuate, se a guidare la conta
	iniziale è il partecipante indicato con 1 (che quindì comincerà a indicare il partecipante 2
	con la prima sillaba).
	Assunzione: 2 ≤ N ≤ 10^5, 1 ≤ S ≤ 10^9.
	Formato di input: l'unica linea contiene i numeri interi N ed S, separati da uno spazio.
	Formato di output: un'unica riga contenente il numero del partecipante che sarà designato dalla conta.
	Esempi:
	Input	Output	Spiegazione
	3 5		1		1a conta (guidata da 1): eliminato 3.
					2a conta (guidata da 1): eliminato 2.
	4 8		3		1a conta (guidata da 1): eliminato 1.
					2a conta (guidata da 2): eliminato 4.
					3a conta (guidata da 2): eliminato 2.

	Limiti: tempo 10s, memoria 1MB.
*/

// directive for standard io functions
#include <iostream>

using namespace std;

const bool DEBUG = true;

#define MAX_N (100000)
#define MAX_S (1000000000)

int designatoSimple(int N, int S);
int designatoSlow(int N, int S);
int designatoFast(int N, int S);
int designatoRec(int N, int S);

int main(int argc, char *argv[])
{
	// read N,S
	int N, S;
	cin >> N >> S;

	if (DEBUG)
		cout << "designatoSimple(" << N << ", " << S << ")" << endl;
	int winnerSimple = designatoSimple(N, S);
	cout << winnerSimple << endl;

	if (DEBUG)
		cout << "designatoSlow(" << N << ", " << S << ")" << endl;
	int winnerSlow = designatoSlow(N, S);
	cout << winnerSlow << endl;

	if (DEBUG)
		cout << "designatoFast(" << N << ", " << S << ")" << endl;
	int winnerFast = designatoFast(N, S);
	cout << winnerFast << endl;

	if (DEBUG)
		cout << "designatoRec(" << N << ", " << S << ")" << endl;
	int winnerRec = designatoRec(N, S);
	cout << winnerRec << endl;
	// successful termination
	return 0;
}

int designatoSimple(int N, int S)
{
	int *presents = new int[N](); // presents[i] = original number

	for (size_t i = 0; i < N; i++)
		presents[i] = i + 1; // 1 ... N

	int leader = 0; // the leader position
	while (N > 1)
	{
		int loser = leader + S % N; // the excluded position
		loser = loser % N;			// make it safe
		if (DEBUG)
			cout << "Players: " << N << ", loser: " << presents[loser];
		for (size_t i = loser; i + 1 < N; i++) // shift positions
			presents[i] = presents[i + 1];
		--N;							 // one less
		leader = loser >= N ? 0 : loser; // new leader
		if (DEBUG)
			cout << ", leader: " << presents[leader] << endl;
	}
	// now the leader is the only one remaining
	leader = presents[0];
	delete[] presents;
	return leader;
}

int designatoFast(int N, int S)
{
	// the winner, renamed 0, now is the leader
	int leader = 0;
	// let's add the losers, backwards
	for (int players = 2; players <= N; players++)
	{
		// reintegrate the loser to the left of the leader
		int loser = leader == 0 ? players - 1 : leader; // circular leader..players-1 shifted by one
		// old leader
		leader = (loser - S) % players;
		if (leader < 0)
		{
			leader += players;
		}
		if (DEBUG)
			cout << "Players: " << players << ", loser: " << loser << ", leader: " << leader << endl;
	}
	// now we have the original leader (i.e. player #1), renamed
	// and we can rename the winner to its original name
	return leader == 0 ? 1 : (N - leader + 1);
}

int designatoSlow(int N, int S)
{
	bool *out = new bool[N](); // true = excluded

	int leader = 0;	   // the leader, renamed 0
	int remaining = N; // players remaining
	while (remaining > 1)
	{
		// count ...
		int toBeCounted = S % remaining; // avoid "loops"
		int loser = leader;				 // start counting from 0 = leader
		while (toBeCounted > 0)
		{
			do // find next player not excluded
			{
				loser = (loser + 1) % N; // circular
			} while (out[loser]);
			toBeCounted--;
		}
		if (DEBUG)
			cout << "Players: " << remaining << ", loser: " << loser + 1;
		out[loser] = true;
		remaining--; // one player excluded
		leader = loser;
		do // leader = find next player not excluded
		{
			leader = (leader + 1) % N; // circular
		} while (out[leader]);
		if (DEBUG)
			cout << ", leader: " << leader + 1 << endl;
	}
	delete[] out;
	// now the leader is the only one remaining
	return leader + 1;
}

int designatoRec(int N, int S)
{
	// here player 1 is the leader
	if (N == 1) // only one player
		return 1;
	int loser = 1 + S % N; // avoid "loops"
	int winner = loser + designatoRec(N - 1, S);
	if (winner > N)
	{
		winner -= N;
	}
	if (DEBUG)
		cout << "Players: " << N << ", loser: " << loser << ", winner: " << winner << endl;
	return winner;
}
