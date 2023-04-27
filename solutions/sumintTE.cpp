/*
    Purpose:    Somme di intervalli (sumint)
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2023/04/23
    Note:		Se memorizzo i valori e per rispondere alle domande calcolo le somme partendo da zero,
                non rispetto i limiti di tempo: Time Exceeded :-(
                With input file of 20K values and 1M queries and output on /dev/null:
                emanuele@owl:/$ time ./sumintTE < sumint_20K_1M.in > /dev/null
                real	0m8,504s
                user	0m8,411s
                sys	0m0,092s
*/
/*
    Somme di intervalli (sumint)
    Data una sequenza di N valori numerici Vi (0<=i<N),
    si deve rispondere a D domande del tipo: dati a e b,
    determinare la somma dei valori Vi per a<=i<=b.
    Ad esempio, dati gli N=5 valori V0=3, V1=2, V2=-1, V3=10, V4=5:
    dati a=1 e b=3, la somma vale V1+V2+V3=2+(-1)+10=11,
    dati a=0 e b=0, la somma vale V0=3.
    Assunzione: 0 < N, D <= 10^7, |Vi| <= 10^3, 0 <= a <= b < N.
    Formato di input: la prima linea contiene il numero intero N.
    La seconda contiene gli N valori Vi (0<=i<N) separati da spazi.
    La terza contiene il numero intero D.
    Le successive D contengono ciascuna due valori interi a e b separati da spazio.
    Formato di output: D righe, ciascuna contenente la risposta
    ad una domanda, nell'ordine in cui le domande sono poste.
    Esempi:
    Input           Output  Spiegazione
    5               11      Esempio del testo.
    3 2 -1 10 5     3
    2
    1 3
    0 0

    7               28      1a:  V0+V1+V2+V3+V4+V5+V6=28
    1 2 3 4 5 6 7   10      2a:  V0+V1+V2+V3=10
    3               18      3a:  V4+V5+V6=18
    0 6
    0 3
    4 6

    Limiti: tempo 10s, memoria 32MB.
*/

#include <iostream>

using namespace std;

const bool DEBUG = true;

#define MAX_VALUES (10'000'000)
#define MAX_QUERIES (10'000'000)
#define MAX_VALUE (1'000)

using value_t = short int;
using sum_t = long long int;

int main(int argc, char *argv[])
{
    // read N
    size_t N;
    cin >> N;
    value_t *values = new value_t[N];
    // read and cumulate values
    for (size_t v = 0; v < N; v++)
    {
        cin >> values[v];
    }
    // read D
    size_t D;
    cin >> D;
    // read and answer the queries
    while (D-- > 0)
    {
        size_t a, b;
        cin >> a >> b;
        sum_t sum = 0;
        for (size_t i = a; i <= b; i++)
        {
            sum += values[i];
        }
        cout << sum << endl;
    }
    delete[] values;
    // successful termination
    return 0;
}
