## Teams forever (teamsord)
### Descrizione del problema
Ad una competizione sportiva partecipano N atleti, appartenenti ad M squadre numerate da 0 a M-1 (ciascun atleta appartiene ad un'unica squadra).
Ciascun atleta ottiene un punteggio individuale P, e ciascuna squadra ottiene un punteggio complessivo S pari alla somma dei punteggi individuali ottenuti dagli atleti appartenenti ad essa.
Dati i punteggi individuali degli atleti, stabilire il punteggio ottenuto dalle squadre e l'ordine delle squadre in classifica (a parità di punteggio la squadra con numero inferiore precede in classifica quella con numero superiore).

**Assunzione**: 1 ≤ M ≤ N ≤ 10<sup>6</sup>, 0 ≤ P ≤ 1000.

**Formato di input**: la prima riga contiene N (numero di atleti) ed M (numero di squadre) separati da uno spazio; ciascuna delle successive N righe contiene la squadra di appartenenza ed il punteggio individuale P del singolo atleta, separati da uno spazio.

**Formato di output**: M righe contenenti ciascuna il numero della squadra ed il corrispondente punteggio complessivo separati da uno spazio, in ordine di classifica.

**Esempi**:
| Input | Output | Spiegazione                                                                                |
| ----- | ------ | ------------------------------------------------------------------------------------------ |
| 4 2   | 1 10   | Vi sono 4 atleti, il primo ed il terzo appartenenti alla squadra 0,                        |
| 0 5   | 0 7    | il secondo ed il quarto alla squadra 1.                                                    |
| 1 3   |        | La squadra 0 ottiene un punteggio complessivo di 7 (5 del primo atleta e 2 del terzo),     |
| 0 2   |        | la squadra 1 ottiene un punteggio complessivo di 10 (3 del secondo atleta e 7 del quarto). |
| 1 7   |        | La squadra 1 è al primo posto in classifica.                                               |

**Limiti**: tempo 20s, memoria 512MB.
