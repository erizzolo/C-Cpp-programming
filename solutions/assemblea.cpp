/*
    Purpose:    validità assemblea
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2023/01/12
    Note:
*/
/*
    Assemblea di condominio ( assemblea )
    Descrizione del problema
    Un'assemblea di condominio è stata convocata per l'ora X
    (numero di secondi a partire dalla mezzanotte: X=3600 indica le ore 1:00:00 del mattino).
    L'i-esimo degli N condomini arriva al luogo di convocazione all'orario Ci.
    Il regolamento di condominio prevede che l'assemblea sia valida se all'orario di inizio
    sono presenti almeno K condomini (un condomino si considera presente se il suo orario
    di arrivo è inferiore o uguale all'ora di inizio dell'assemblea).
    Data l'ora di convocazione dell'assemblea X, la soglia di validità K e l'orario di arrivo
    di ciascun condomino, determinare se l'assemblea è valida oppure no.
    Assunzione: 0 ≤ X, Ci ≤ 86400, 1 ≤ K ≤ N ≤ 10^9.
    Formato di input: la prima riga contiene X, N e K separati da spazi,
    la seconda riga contiene gli N valori Ci separati da spazio.
    Formato di output: YES, se l'assemblea è valida, NO altrimenti.
    Esempi:
    Input						Output	Spiegazione
    72000 5 3					YES		3 condomini su 5 sono presenti (1°,2° e 5°), quindi l'assemblea è valida
    70000 0 86000 80000 1000

    43200 4 3					NO		Solo il 4° condomino è presente, quindi l'assemblea non è valida
    50000 60000 45000 43200

    100 10 6					YES		Tutti i condomini sono presenti, quindi l'assemblea è valida
    1 1 1 0 0 0 1 1 1 0

    Limiti: tempo 1s, memoria 1KB.

*/

#include <iostream>

using namespace std;

#define DEBUG 0
#define INDEFINITO 0
#define VALIDA 1
#define NON_VALIDA 2

int main(int argc, char *argv[])
{
    int X, N, K;
    cerr << "Immetti l'ora di convocazione X, il numero di condomini N e la soglia di validità K (0≤X≤86400,1≤K≤N≤10^9):";
    cin >> X >> N >> K;
    cerr << "Immetti l'ora di arrivo degli " << N << " condomini (0<=Ci<=86400):";
    // condomini presenti
    int sogliaPresenti = K, sogliaAssenti = N - K + 1;
    int valida = INDEFINITO;
    for (int condomino = 0; condomino < N && valida == INDEFINITO; condomino++)
    {
        int arrivo;
        cin >> arrivo;
        if (arrivo <= X)
        {
            sogliaPresenti--;
            if (sogliaPresenti == 0)
            {
                valida = VALIDA;
            }
        }
        else
        {
            sogliaAssenti--;
            if (sogliaAssenti < 0)
            {
                valida = NON_VALIDA;
            }
        }
    }
    // output result
    if (valida == VALIDA)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    // successful termination
    return 0;
}
