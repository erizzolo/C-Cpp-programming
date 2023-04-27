## Compagni di classe (classi)
N studenti (numerati da 0 a N-1) sono stati assegnati ad M classi (numerate da 0 a M-1).
Ciascuno di essi avrebbe desiderato essere nella stessa classe di un amico, ma forse non tutti sono stati esauditi.

Dato un elenco di studenti indicante per ciascuno l'amico con il quale voleva stare (diverso da sé stesso) e la classe a cui è stato assegnato, determinare il numero di studenti il cui desiderio è stato soddisfatto.

Ad esempio, se vi sono N = 3 studenti e M = 1 classe, ovviamente sono stati tutti e tre soddisfatti.

**Assunzione**: 1 ≤ N ≤ 10<sup>8</sup>, 1 ≤ M ≤ 10<sup>6</sup>.

**Formato di input**: la prima linea contiene i numeri interi N ed M. Le N successive linee, una per per ciascuno studente, contengono due numeri: l'amico con cui lo studente desiderava essere e la classe a cui lo studente è stato assegnato.

**Formato di output**: una riga contenente il numero di studenti il cui desiderio è stato soddisfatto.

**Esempi**:
| Input | Output | Spiegazione                             |
| ----- | ------ | --------------------------------------- |
| 3 1   | 3      | Esempio del testo.                      |
| 1 0   |        |                                         |
| 2 0   |        |                                         |
| 1 0   |        |                                         |
| ----- | ------ | --------------------------------        |
| 5 2   | 2      | Classi: 0={0,1,3},1={2,4}               |
| 1 0   |        | Desideri: {0→1},{1→2},{2→1},{3→4},{4→2} |
| 2 0   |        | Studenti soddisfatti = {0,4}.           |
| 1 1   |        |                                         |
| 4 0   |        |                                         |
| 2 1   |        |                                         |

**Limiti**: tempo 2s, memoria 1GB.
