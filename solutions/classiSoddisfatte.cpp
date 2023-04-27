/*
    Purpose:    Compagni di classe (classiSoddisfatte)
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2023/04/23
    Note:
*/
/*
    Compagni di classe (classiSoddisfatte)
    N studenti (numerati da 0 a N-1) sono stati assegnati ad M classi
    (numerate da 0 a M-1). Ciascuno di essi avrebbe desiderato essere
    nella stessa classe di un amico, ma forse non tutti sono stati esauditi.
    Dato un elenco di studenti indicante per ciascuno l'amico con il quale
    voleva stare (diverso da sé stesso) e la classe a cui è stato assegnato,
    determinare il numero di studenti il cui desiderio è stato soddisfatto
    per ciascuna classe.
    Ad esempio, se vi sono N = 3 studenti e M = 1 classe,
    ovviamente sono stati tutti e tre soddisfatti.
    Assunzione: 1 ≤ N ≤ 10^8, 1 ≤ M ≤ 10^6.
    Formato di input: la prima linea contiene i numeri interi N ed M.
    Le N successive linee, una per per ciascuno studente, contengono due numeri:
    l'amico con cui lo studente desiderava essere e la classe a cui lo studente è stato assegnato.
    Formato di output: M riga contenenti ciascuna il numero di studenti
    il cui desiderio è stato soddisfatto nella classe i-esima.
    Esempi:
    Input   Output  Spiegazione
    3 1     3       Esempio del testo.
    1 0
    2 0
    1 0

    5 2     1       Classi: 0={0,1,3},1={2,4}
    1 0     1       Desideri: {0→1},{1→2},{2→1},{3→4},{4→2}
    2 0             Studenti soddisfatti = {0,4}, uno nella prima e uno nella seconda.
    1 1
    4 0
    2 1

    Limiti: tempo 2s, memoria 1GB.
*/

#include <iostream>

using namespace std;

const bool DEBUG = false;

#define MAX_STUDENTS (100'000'000)
#define MAX_CLASSES (1'000'000)

// the student type
struct student
{
    int classe, amico;
};

int main(int argc, char *argv[])
{
    // read N,M
    int N, M;
    cin >> N >> M;
    student *students = new student[N]; // the students
    int *satisfied = new int[M]();      // number of satisfied students in classes
    // read students
    for (int s = 0; s < N; s++)
    {
        cin >> students[s].amico >> students[s].classe;
    }
    // loop through students
    for (int s = 0; s < N; s++)
    {
        if (students[s].classe == students[students[s].amico].classe)
        {
            satisfied[students[s].classe]++;
        }
    }
    // output
    // loop through classes
    for (int c = 0; c < M; c++)
    {
        cout << satisfied[c] << endl;
    }
    delete[] students;
    delete[] satisfied;

    return 0;
}
