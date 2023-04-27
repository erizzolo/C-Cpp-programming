## Somme di intervalli (sumint)
Data una sequenza di N valori numerici Vi (0 <=i < N), si deve rispondere a D domande del tipo: dati a e b, determinare la somma dei valori Vi per a <= i <= b.
Ad esempio, dati gli N = 5 valori V0 = 3, V1 = 2, V2 = -1, V3 = 10, V4 = 5:
* dati a=1 e b=3, la somma vale V1 + V2 + V3 = 2 + (-1) + 10 = 11,
* dati a = 0 e b = 0, la somma vale V0 = 3.

**Assunzione**: 0 < N, D <= 10<sup>7</sup>, |Vi| <= 10<sup>3</sup>, 0 <= a <= b < N.

**Formato di input**: la prima linea contiene il numero intero N. La seconda contiene gli N valori Vi (0 <= i < N) separati da spazi. La terza contiene il numero intero D. Le successive D contengono ciascuna due valori interi a e b separati da spazio.

**Formato di output**: D righe, ciascuna contenente la risposta ad una domanda, nell'ordine in cui le domande sono poste.
| Input         | Output | Spiegazione                      |
| ------------- | ------ | -------------------------------- |
| 5             | 11     | Esempio del testo.               |
| 3 2 -1 10 5   | 3      |                                  |
| 2             |        |                                  |
| 1 3           |        |                                  |
| 0 0           |        |                                  |
| ------------- | ------ | -------------------------------- |
| 7             | 28     | 1a:  V0+V1+V2+V3+V4+V5+V6=28     |
| 1 2 3 4 5 6 7 | 10     | 2a:  V0+V1+V2+V3=10              |
| 3             | 18     | 3a:  V4+V5+V6=18                 |
| 0 6           |        |                                  |
| 0 3           |        |                                  |
| 4 6           |        |                                  |

**Limiti**: tempo 10s, memoria 32MB.
