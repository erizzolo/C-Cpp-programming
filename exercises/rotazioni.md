## Rotazioni ( rotazioni )
### Descrizione del problema
Una rotazione a sinistra di una sequenza di n valori sposta ciascun elemento a sinistra di una posizione, tranne il primo elemento che viene spostato in ultima posizione.

Ad esempio:

dopo una rotazione a sinistra la sequenza [0,1,2,3,4] diviene [1,2,3,4,0];

dopo due rotazioni a sinistra la sequenza [0,1,2,3,4] diviene [2,3,4,0,1].

Data la lunghezza n della sequenza, il numero d di rotazioni effettuate e gli n valori della sequenza iniziale, determinare quale valore si troverà in prima posizione (posizione 0) ed in quale posizione (numerate da 0 a n-1) si troverà l'elemento originalmente in posizione iniziale.

**Assunzione**: 1 ≤ n ≤ 25, 0 ≤ d ≤ 10<sup>9</sup>.

**Formato di input**: leggere n, d e gli n valori della sequenza originale da tastiera, (con controlli di validità).

**Formato di output**: il valore che si troverà in posizione 0 (la prima) e la posizione in cui si troverà il primo valore della sequenza originale, dopo d rotazioni a sinistra della sequenza data.

**Esempi**:
| Input     | Output | Note                      |
| --------- | ------ | ------------------------- |
| 5 1       |        | n = 5, d = 1:             |
| 0 1 2 3 4 | 1 4    | sequenza finale 1 2 3 4 0 |
| 5 2       |        | n = 5, d = 2:             |
| 0 1 2 3 4 | 2 3    | sequenza finale 2 3 4 0 1 |
| 5 7       |        | n = 5, d = 7:             |
| a e i o u | i 3    | sequenza finale i o u a e |
