/*
	Purpose:    Gruppi di amici (friends)
	Author:     Emanuele Rizzolo
	Class:      3XIN
	Date:       2023/05/18
	Note:		union find algorithm (recursive find)
*/
/*
	Gruppi di amici (friends)
	A scuola si sono iscritti N studenti (numerati da 1 a N in ordine di iscrizione)
	e nessuno inizialmente era amico di alcun altro studente (oltre a se stesso).
	Man mano che le prove di informatica spargevano il terrore negli studenti,
	tra questi si sono formate delle amicizie nella speranza (vana) di riuscire a superare le prove.
	La relazione di amicizia, si sa, è riflessiva (X è amico di X), simmetrica
	(se X è amico di Y, allora Y è amico di X) e transitiva (se X è amico di Y e Y è amico di Z, allora X è amico di Z).
	Date le A amicizie dirette formatesi tra gli studenti, il vostro compito è determinare,
	per ciascuna di C coppie di studenti, se gli studenti della coppia sono amici tra loro, anche indirettamente.
	Ad esempio, dati N=4 studenti e le amicizie dirette (1,2), (1,3) e (2,3) risulta che
	gli studenti 1,2,3 appartengono allo stesso gruppo di amici, mentre lo studente 4 è amico solo di se stesso.
	Assunzione: 0 < N <= 10^4, 0 < A <= 10^6, 0 < C <= 10^4.
	Formato di input: la prima linea contiene i numeri interi N, A e C separati da uno spazio.
	Le successive A righe contengono ciascuna due numeri interi separati da spazi Xi, Yi (0<=i<A, 0<Xi,Yi<=N)
	indicanti che vi è un'amicizia diretta tra gli studenti Xi ed Yi. Le successive C righe contengono ciascuna
	due numeri interi separati da spazi Xi, Yi (0<=i<C, 0<Xi,Yi<=N) indicanti una coppia di studenti dei quali
	si vuole sapere se sono o no amici, anche indirettamente.
	Formato di output: C righe, ciascuna contenente la risposta alla domanda se i due studenti della coppia
	i-esima sono o no amici, nell'ordine in cui le domande sono poste: YES se i due studenti sono amici, NO altrimenti.
	Esempi:
	Input	Output	Spiegazione
	4 2 4	YES		Vi sono 4 studenti, 2 amicizie dirette e 4 domande.
	1 2		YES		Gli studenti 1,2,3 formano un gruppo di amici, mentre 4 è isolato.
	1 3		YES		Quindi per le coppie (1,2), (1,3), (2,3) la risposta è positiva
	1 2		NO		(nell'ultimo caso l'amicizia è indiretta, tramite l'amico comune 1),
	1 3				mentre per la coppia (1,4) è negativa: 1 e 4 non sono amici, né direttamente né indirettamente
	2 3
	1 4

	7 5 3	NO		Vi sono 7 studenti, 5 amicizie dirette e 3 domande.
	1 4		NO		Gli studenti 1,4,6 formano un gruppo di amici, mentre 2,3,5,7 formano un altro gruppo, separato dal primo.
	1 6		YES		Quindi per le coppie (1,5), (1,7) la risposta è negativa: non vi sono amicizie dirette né amici comuni,
	2 3				mentre per la coppia (2,7) è positiva: 2 è amico di 3 che è amico di 5 che è amico di 7 (proprietà transitiva ripetuta).
	3 5
	5 7
	1 5
	1 7
	2 7

	Limiti: tempo 2s, memoria 32MB.
*/

#include <iostream>

using namespace std;

#define DEBUG 0

#define MAX_FRIENDS (10000)
#define MAX_FRIENDSHIPS (1000000)
#define MAX_QUERIES (10000)

int *groups; // dynamic array

int findGroup(const int student);					 // return group of student
void uniteGroups(const int first, const int second); // unites groups of two students

void iota(int a[], int value, int end, int begin = 0);

int main(int argc, char *argv[])
{
	int N, A, C;
	cin >> N >> A >> C;		 // read N, A, C
	groups = new int[N + 1]; // the groups to which each student belongs
	iota(groups, 0, N + 1);	 // init groups: self-friendship
	// process direct friendships
	for (int f = 0; f < A; f++)
	{
		int first, second;
		cin >> first >> second;
		uniteGroups(first, second);
	}
	// process queries
	for (int q = 0; q < C; q++)
	{
		int first, second;
		cin >> first >> second;
		cout << (findGroup(first) == findGroup(second) ? "YES" : "NO") << endl;
	}

	delete[] groups;
	// successful termination
	return 0;
}

int findGroup(const int student) // return group of student
{
	if (groups[student] != student) // not a leader...
		groups[student] = findGroup(groups[student]);
	return groups[student];
}

void uniteGroups(const int first, const int second) // unites groups of two students
{
	groups[findGroup(first)] = findGroup(second);
}

/// @brief Imposta gli elementi in [begin, end) con valori crescenti a partire da value
/// @param a     the array to change
/// @param value the starting value, incremented with ++value
/// @param end   fine (esclusa) della scansione: a[end] non viene elaborato
/// @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
void iota(int a[], int value, int end, int begin /* = 0 */)
{
	for (int i = begin; i < end; ++i)
	{
		a[i] = value;
		++value;
	}
}
