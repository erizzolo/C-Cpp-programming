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
                Come in politica, spesso anche in informatica bisogna usare l'arte del compromesso!!!
                Memorizzando i valori mi avanza della memoria, infatti 10^7 valori con |Vi| <= 10^3
                possono essere memorizzati con 10^7 valori * 2 B/valore = 20 MB < 32 MB
                Con i 12 MB restanti posso memorizzare alcune delle somme parziali!!!
                Poiché le somme parziali possono arrivare a 10^7 * 10^3 = 10^10, per ciascuna mi servono 8 B (sum_t):
                posso memorizzare fino a 12 MB / (8 B/valore) = 1,5 M valori, ad esempio una ogni 10 !!!
                Quindi: memorizzo tutti i valori, memorizzo le somme parziali dei primi 1, 11, 21, 31, 41, ... valori
                e per rispondere alle domande sommo alle differenze delle somme parziali alcuni (max 18 o volendo max 10) valori rimanenti.
                Mi sa che così soddisfo sia i limiti di tempo che quelli di memoria ;-) !!!
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
#define PARTIAL_SUM_STEP (10)

using value_t = short int;
using sum_t = long long int;

sum_t getSum_0_n(const value_t v[], const sum_t s[], size_t n);

int main(int argc, char *argv[])
{
    // read N
    size_t N;
    cin >> N;
    value_t *values = new value_t[N];
    sum_t *sums = new sum_t[N / PARTIAL_SUM_STEP + 1]; // + 1 to be on the safe side...
    // read and cumulate values
    sum_t total = 0;
    for (size_t v = 0; v < N; v++)
    {
        cin >> values[v];
        total += values[v];
        if (v % PARTIAL_SUM_STEP == 0)
        {
            sums[v / PARTIAL_SUM_STEP] = total;
        }
    }
    // read D
    size_t D;
    cin >> D;
    // read and answer the queries
    while (D-- > 0)
    {
        size_t a, b;
        cin >> a >> b;
        sum_t result = getSum_0_n(values, sums, b) + (a > 0 ? getSum_0_n(values, sums, a - 1) : 0);
        cout << result << endl;
    }
    delete[] values;
    delete[] sums;
    // successful termination
    return 0;
}

sum_t getSum_0_n(const value_t v[], const sum_t s[], size_t n)
{
    // Now Sum[k] = Somma(Vi, 0 <= i <= 10 * k)
    // Sum[0] = 0, Sum[1] = V0 + V1 + ... + V9 + V10, Sum[2] = V0 + V1+ ... + V19 + V20
    // x = 10 * dx + ux   (d = decine, u = unità)
    // Somma(Vi, 0 <= i <= x) = Somma(Vi, 0 <= i <= 10 * dx) + Somma(Vi, 10 * dx + 1  <= i <= 10 * dx + ux)
    // Somma(Vi, 0 <= i <= x) = Sum[dx] + Somma(Vi, 10 * dx + 1  <= i <= 10 * dx + ux)
    sum_t result = 0;
    size_t dn = n / PARTIAL_SUM_STEP;
    result += s[dn];
    for (size_t i = dn * PARTIAL_SUM_STEP + 1; i <= n; ++i)
    {
        result += v[i];
    }
    return result;
}
