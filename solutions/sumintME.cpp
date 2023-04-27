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
                Idea:
                    Somma(Vi, a <= i <= b) = Somma(Vi, 0 <= i <= b) - Somma(Vi, 0 <= i <= a - 1)
                E' sufficiente memorizzare le somme cumulative parziali
                    Sum[k] = Somma(Vi, 0 <= i <= k) per 0 <= k < N
                    Sum[0] = V0, Sum[1] = V0 + V1, Sum[2] = V0 + V1 + V2 ...
                da cui Somma(Vi, a <= i <= b) = Sum[b] - (a > 0 ? Sum[a - 1] : 0)
                Poiché le somme parziali possono arrivare a 10^7 * 10^3 = 10^10, per ciascuna mi servono 8 B (sum_t):
                I tempi saranno rispettati, ma non i limiti di memoria: Memory Exceeded :-)
                Infatti per memorizzare le somme servono 10^7 * 8B = 80MB
                With input file of 20K values and 1M queries and output on /dev/null:
                emanuele@owl:/$ time ./sumintME < sumint_20K_1M.in > /dev/null
                real	0m0,510s
                user	0m0,429s
                sys	0m0,080s
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
    sum_t *sums = new sum_t[N];
    // read and cumulate values
    sum_t total = 0;
    for (size_t v = 0; v < N; v++)
    {
        value_t value;
        cin >> value;
        total += value;
        sums[v] = total;
    }
    // read D
    size_t D;
    cin >> D;
    // read and answer the queries
    while (D-- > 0)
    {
        size_t a, b;
        cin >> a >> b;
        cout << sums[b] - (a > 0 ? sums[a - 1] : 0) << endl;
    }
    delete[] sums;
    // successful termination
    return 0;
}
