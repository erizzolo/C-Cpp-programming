## Teams again (teamsavg)
### Descrizione del problema

Ad una competizione sportiva partecipano N atleti, appartenenti ad M squadre numerate da 0 a M-1 (ciascun atleta appartiene ad un'unica squadra).
Ciascun atleta ottiene un punteggio individuale P, e ciascuna squadra ottiene un punteggio complessivo S pari alla media (arrotondata ad intero per difetto) dei punteggi individuali ottenuti dagli atleti appartenenti ad essa.
Dati i punteggi individuali degli atleti, stabilire il punteggio ottenuto dalle squadre.

**Assunzione**: 1 ≤ M ≤ N ≤ 10<sup>7</sup>, 0 ≤ P ≤ 1000.

**Formato di input**: la prima riga contiene N (numero di atleti) ed M (numero di squadre) separati da uno spazio; ciascuna delle successive N righe contiene la squadra di appartenenza ed il punteggio individuale P del singolo atleta, separati da uno spazio.

**Formato di output**: M righe contenenti ciascuna il punteggio complessivo della corrispondente squadra.

**Esempi**:
| Input | Output | Spiegazione                                                                                                       |
| ----- | ------ | ----------------------------------------------------------------------------------------------------------------- |
| 4 2   | 3      | Vi sono 4 atleti, il primo ed il terzo appartenenti alla squadra 0,                                               |
| 0 5   | 5      | il secondo ed il quarto alla squadra 1.                                                                           |
| 1 3   |        | La squadra 0 ottiene un punteggio complessivo di 3 (5 del primo atleta e 2 del terzo, media 3.5 arrotondata a 3), |
| 0 2   |        | la squadra 1 ottiene un punteggio complessivo di 5 (3 del secondo atleta e 7 del quarto, media 5).                |
| 1 7   |        |                                                                                                                   |

**Limiti**: tempo 8s, memoria 256MB.
