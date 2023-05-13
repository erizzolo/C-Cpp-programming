/*
    Purpose:    Campionato (championship)
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2023/05/06
    Note:
*/
/*
    Campionato (championship)
    È dato un file di testo contenente i nomi delle squadre di una serie
    del campionato di calcio, una per riga ed in numero pari.
    È noto che in tali campionati, date S squadre, vi sono due gironi
    (Andata e Ritorno) ciascuno di G=S-1 giornate in ciascuna delle quali
    si disputano S/2 partite. Ogni squadra incontra ciascuna delle altre
    S-1 squadre due volte, una nel girone di andata ed una in quello di ritorno.
    Generare un file che descriva le possibili giornate del girone di andata.
    Tale file è costituito da G sezioni il cui inizio è indicato da una riga
    contenente il numero della giornata cui si riferisce racchiuso tra parentesi quadre.
    Ciascuna sezione contiene poi S/2 righe contenenti i nomi, separati da un segno -,
    delle due squadre che si incontreranno in quella giornata
    Scrivere un'applicazione che riceva due parametri da riga comando,
    indicanti rispettivamente il nome del file delle squadre ed il nome
    del file che descrive il girone, prodotto in output dall'applicazione.
*/

/*
    Soluzione 0:
    E' sufficiente avere una funzione che, date due squadre (diverse!)
    ci dica in quale giornata giocano: dati gli "indici" delle squadre
    a, b con a e b nell'intervallo [0, S-1] deve restituire un valore
    nell'intervallo [0, G-1] e soddisfare i seguenti vincoli:
    - "simmetria"   :   f(a, b) = f(b, a)
        date le due squadre, il giorno del match è lo stesso!
    - "diversita'"  :   f(a, b) != f(a, c) se a != c
        data una squadra, il giorno deve essere diverso per ogni avversario!
    Esempio: se f(a, b) = (a + b) % G
        la prima condizione è soddisfatta, ma poiché G =  S - 1:
            f(a, 0) = a = f(a, S-1) = a     OOPS!
            nel giorno a, la squadra a deve giocare due partite !!!
        Per sistemare le cose, visto che f(a, a) non ha senso,
        poniamo f(a, S-1) = f(S-1, a) = f(a,a) = 2a % G != a
    Bisogna anche stabilire una regola "casuale" per dire
    chi gioca in casa e chi fuori.

    Soluzione 1:
    dette s1, s2 (0 <= s < S) le squadre di una partita e g (0 <= s < G)
    la giornata in cui si incontrano, si "forma" la tabella simmetrica
        giornata[s1][s2] = giornata[s2][s1] = g
    con S - 1 righe ed S - 1 colonne, in questo modo
        giornata[s1][s2] = giornata[s2][s1] = (s1 + s2) % G
    considerando giornata[s][s] il giorno in cui la squadra s incontra la S - 1
    E.g. per S = 6 (riga/colonna S ripetono i valori della diagonale)
    colonna     0   1   2   3   4   (5)
    riga      |---|---|---|---|---|-----|
           0  | 0 | 1 | 2 | 3 | 4 | (0) |
           1  | 1 | 2 | 3 | 4 | 0 | (2) |
           2  | 2 | 3 | 4 | 0 | 1 | (4) |
           3  | 3 | 4 | 0 | 1 | 2 | (1) |
           4  | 4 | 0 | 1 | 2 | 3 | (3) |
          (5) | 0 | 2 | 4 | 1 | 3 | (-) |
    Come si vede, in ciascuna riga/colonna, sono presenti tutte le giornate
    senza ripetizioni. Bisogna però stabilire una regola "casuale" per dire
    chi gioca in casa e chi fuori.
    Non è necessario memorizzare la tabella esplicitamente:
    equivale alle funzioni dayOfMatch, opponentOfDay, isAtHome.

    Soluzione 2:
    dagli scacchi...
    tabella con G righe e S colonne
    in ciascuna giornata si incontrano le squadre in colonne adiacenti
    (indicando con s = S/2)
    colonna     :   0   1   2   3   ...     S-2 S-1
    prima riga  :   0  S-1  1  S-2  ...     s-1  s
    nelle righe successive la squadra S-1 alterna la colonna 0 e 1
    incontrando il giocatore in colonna S-1 della riga precedente
    eccetera eccetera
    vedere https://dna.ffechecs.fr/wp-content/uploads/sites/2/2022/09/Livre-Arbitre-octobre2022.pdf
    non implementata ....

    Soluzione 3:
    backtracking
    dette s1, s2 (0 <= s < S) le squadre di una partita e g (0 <= s < G)
    la giornata in cui si incontrano, si "forma" la tabella simmetrica
        giornata[s1][s2] = giornata[s2][s1] = g
    con S righe ed S colonne, impostando nelle varie celle,
    tranne quelle della diagonale, i valori da 0 a G-1,
    tornando alla cella precedente e modificandola se vi sono conflitti
    (due valori uguali nella stessa riga/colonna)

*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>

using namespace std;

const bool DEBUG = true;

#define MAX_TEAM_LENGTH (30)
using name_t = char[MAX_TEAM_LENGTH];

#define TEAM_SEPARATOR ('-')

int dayOfMatch(int home, int guest, int nDays);
int opponentOfDay(int team, int day, int nDays);
int atHome(int team, int other, int nDays);

bool playsAtHome(int team, int other, int **days);

bool isAllowed(int **days, int row, int column, int value);

void showDays(int **days, int nTeams)
{
    for (int i = 0; i < nTeams; i++)
    {
        for (int j = 0; j < nTeams; j++)
        {
            // if (i == j)
            //     cout << "- ";
            // else
            cout << days[i][j] << " ";
        }
        cout << endl;
    }
}

using type = name_t;
void shuffleAll(type a[], int toBeShuffled);

int main(int argc, char *argv[])
{
    // check parameters
    if (argc != 3)
    {
        cerr << "Wrong number of parameters." << endl;
    }
    else
    {
        ifstream teamsFile(argv[1]); // open teams file
        if (teamsFile)               // if failed, nothing to do
        {
            ofstream outFile(argv[2]); // open output file
            if (outFile)               // if failed, use cout ???
            {
                // read teams, just to know their number
                size_t nTeams = 0;
                name_t tmpname;
                while (teamsFile.getline(tmpname, MAX_TEAM_LENGTH, '\n'))
                {
                    if (strlen(tmpname) > 0)
                        nTeams++;
                    cout << tmpname << endl;
                }
                nTeams += nTeams % 2;               // make nTeams non smaller even
                name_t *teams = new name_t[nTeams]; // now allocate space for names
                teamsFile.clear();                  // resets failbit if necessary
                teamsFile.seekg(0);                 // restart from the beginning
                size_t iTeams = 0;
                while (!teamsFile.eof())
                {
                    do
                    {
                        teamsFile.getline(teams[iTeams], MAX_TEAM_LENGTH, '\n');
                    } while (strlen(teams[iTeams]) == 0);
                    ++iTeams;
                }
                if (iTeams < nTeams) // odd number of teams
                    strcpy(teams[iTeams], "riposo");
                teamsFile.close(); // finally over
                if (DEBUG)
                {
                    cout << "Read " << nTeams << " teams." << endl;
                    for (size_t t = 0; t < nTeams; t++)
                        cout << t << ": " << teams[t] << endl;
                }

                shuffleAll(teams, nTeams); // shuffle teams ...

                int nDays = nTeams - 1;
                {
                    // Solution n° 0
                    outFile << "Solution n° 0" << endl;
                    auto start = std::chrono::high_resolution_clock::now(); // record start time
                    for (int day = 0; day < nDays; day++)
                    {
                        outFile << "[" << (day + 1) << "]" << endl;
                        for (int team = 0; team < nTeams; team++)
                        {
                            int opponent = opponentOfDay(team, day, nDays);
                            if (atHome(team, opponent, nDays) == team)
                                outFile << teams[team] << TEAM_SEPARATOR << teams[opponent] << endl;
                        }
                    }
                    auto end = std::chrono::high_resolution_clock::now(); // record end time
                    std::chrono::duration<double> diff = end - start;
                    outFile << "Time to solve " << diff.count() << " s" << endl;
                }
                {
                    // Solution n° 1 without functions
                    outFile << "Solution n° 1 without functions" << endl;
                    auto start = std::chrono::high_resolution_clock::now(); // record start time
                    int **days = new int *[nTeams];                         // allocate memory
                    for (int team = 0; team < nTeams; team++)
                    {
                        days[team] = new int[nTeams];
                    }

                    for (int team = 0; team < nTeams - 1; team++) // setup
                    {
                        for (int other = team + 1; other < nTeams - 1; other++)
                        {
                            days[team][other] = days[other][team] = (team + other) % nDays;
                        }
                        days[team][nDays] = days[nDays][team] = (team + team) % nDays; // special match
                    }

                    for (int day = 0; day < nTeams - 1; day++)
                    {
                        outFile << "[" << (day + 1) << "]" << endl;
                        for (int team = 0; team < nTeams; team++)
                            for (int other = team + 1; other < nTeams; other++)
                                if (days[team][other] == day)
                                    if (atHome(team, other, nDays) == team)
                                        outFile << teams[team] << TEAM_SEPARATOR << teams[other] << endl;
                                    else
                                        outFile << teams[other] << TEAM_SEPARATOR << teams[team] << endl;
                    }

                    for (int team = 0; team < nTeams; team++) // deallocate memory
                        delete[] days[team];
                    delete[] days;
                    auto end = std::chrono::high_resolution_clock::now(); // record end time
                    std::chrono::duration<double> diff = end - start;
                    outFile << "Time to solve " << diff.count() << " s" << endl;
                }
                {
                    // Solution n° 3
                    // here day = 1...nDays
                    outFile << "Solution n° 3" << endl;
                    auto start = std::chrono::high_resolution_clock::now(); // record start time
                    int **days = new int *[nTeams];                         // allocate memory
                    for (int team = 0; team < nTeams; team++)
                        days[team] = new int[nTeams](); // zero (i.e. invalid)
                    int team = 0, other = 1;
                    while (team < nTeams - 1) // process teams
                    {
                        int day = days[team][other]; // next allowed day
                        do
                        {
                            ++day;
                        } while (day <= nDays && !isAllowed(days, team, other, day));
                        if (day > nDays) // no day is allowed
                        {
                            days[team][other] = days[other][team] = 0; // reset
                            --other;                                   // backtrack
                            if (other <= team)
                            {
                                --team;
                                other = nTeams - 1;
                            }
                            // if (DEBUG)
                            //     showDays(days, nTeams);
                        }
                        else
                        {
                            days[team][other] = days[other][team] = day;
                            ++other; // proceed further
                            if (other == nTeams)
                            {
                                ++team;
                                other = team + 1;
                            }
                        }
                    }
                    // found a solution...
                    if (DEBUG)
                        showDays(days, nTeams);
                    for (int day = 1; day < nTeams; day++)
                    {
                        outFile << "[" << day << "]" << endl;
                        for (int team = 0; team < nTeams; team++)
                            for (int other = team + 1; other < nTeams; other++)
                                if (days[team][other] == day)
                                    if (playsAtHome(team, other, days))
                                        outFile << teams[team] << TEAM_SEPARATOR << teams[other] << endl;
                                    else
                                        outFile << teams[other] << TEAM_SEPARATOR << teams[team] << endl;
                    }

                    for (int team = 0; team < nTeams; team++) // deallocate memory
                        delete[] days[team];
                    delete[] days;
                    auto end = std::chrono::high_resolution_clock::now(); // record end time
                    std::chrono::duration<double> diff = end - start;
                    outFile << "Time to solve " << diff.count() << " s" << endl;
                }
                outFile.close();
            }
        }
    }
    // successful termination
    return 0;
}

int dayOfMatch(int home, int guest, int nDays)
{
    if (home == nDays) // special match!
        return dayOfMatch(guest, guest, nDays);
    if (guest == nDays) // special match!
        return dayOfMatch(home, home, nDays);
    return (home + guest) % nDays;
}

int opponentOfDay(int team, int day, int nDays)
{
    for (int opponent = 0; opponent <= nDays; opponent++)
        if (opponent != team && dayOfMatch(team, opponent, nDays) == day)
            return opponent;
    return team; // nonsense
}

int atHome(int team, int other, int nDays)
{
    // even days: home < guest, odd days: home > guest
    return dayOfMatch(team, other, nDays) % 2 == 0
               ? min(team, other)
               : max(team, other);
}

bool playsAtHome(int team, int other, int **days)
{
    // even days: home < guest, odd days: home > guest
    return days[team][other] % 2 == 0
               ? min(team, other)
               : max(team, other);
}

bool isAllowed(int **days, int row, int column, int value)
{
    for (int c = column; c-- > 0;)
        if (days[row][c] == value)
            return false;
    for (int r = row; r-- > 0;)
        if (days[column][r] == value)
            return false;
    return true;
}

/// @brief Mescolamento degli elementi da 0 a end escluso: [0, end)
/// @param a     l'array con i valori da mescolare
/// @param toBeShuffled   fine (esclusa) della scansione: a[toBeShuffled] non viene elaborato
void shuffleAll(type a[], int toBeShuffled)
{
    while (toBeShuffled > 1) // at least two elements
    {
        int random = rand() % toBeShuffled; // pick a random element
        --toBeShuffled;                     // one less
        swap(a[random], a[toBeShuffled]);   // swap
    }
}
