## 	Gruppi di amici (friends)
A scuola si sono iscritti N studenti (numerati da 1 a N in ordine di iscrizione) e nessuno inizialmente era amico di alcun altro studente (oltre a se stesso).

Man mano che le prove di informatica spargevano il terrore negli studenti, tra questi si sono formate delle amicizie nella speranza (vana) di riuscire a superare le prove.

La relazione di amicizia, si sa, è riflessiva (X è amico di X), simmetrica (se X è amico di Y, allora Y è amico di X) e transitiva (se X è amico di Y e Y è amico di Z, allora X è amico di Z).

Date le A amicizie dirette formatesi tra gli studenti, il vostro compito è determinare, per ciascuna di C coppie di studenti, se gli studenti della coppia sono amici tra loro, anche indirettamente.

Ad esempio, dati N=4 studenti e le amicizie dirette (1,2), (1,3) e (2,3) risulta che gli studenti 1,2,3 appartengono allo stesso gruppo di amici, mentre lo studente 4 è amico solo di se stesso.


**Assunzione**: 0 < N <= 10<sup>4</sup>, 0 < A <= 10<sup>6</sup>, 0 < C <= 10<sup>4</sup>.

**Formato di input**: la prima linea contiene i numeri interi N, A e C separati da uno spazio.
Le successive A righe contengono ciascuna due numeri interi separati da spazi Xi, Yi (0 <=i < A, 0 < Xi, Yi <= N) indicanti che vi è un'amicizia diretta tra gli studenti Xi ed Yi.
Le successive C righe contengono ciascuna due numeri interi separati da spazi Xi, Yi (0 <= i < C, 0 < Xi, Yi <= N) indicanti una coppia di studenti dei quali si vuole sapere se sono o no amici, anche indirettamente.


**Formato di output**: C righe, ciascuna contenente la risposta alla domanda se i due studenti della coppia	i-esima sono o no amici, nell'ordine in cui le domande sono poste: YES se i due studenti sono amici, NO altrimenti.

**Esempi**:
| Input   | Output | Note                                                                                                          |
| ------- | ------ | ------------------------------------------------------------------------------------------------------------- |
| 4 2 4   | YES    | Vi sono 4 studenti, 2 amicizie dirette e 4 domande.                                                           |
| 1 2     | YES    | Gli studenti 1,2,3 formano un gruppo di amici, mentre 4 è isolato.                                            |
| 1 3     | YES    | Quindi per le coppie (1,2), (1,3), (2,3) la risposta è positiva                                               |
| 1 2     | NO     | (nell'ultimo caso l'amicizia è indiretta, tramite l'amico comune 1),                                          |
| 1 3     |        | mentre per la coppia (1,4) è negativa: 1 e 4 non sono amici, né direttamente né indirettamente                |
| 2 3     |        |                                                                                                               |
| 1 4     |        |                                                                                                               |
| ------- | ------ | ----------------------------------------------------------------------------------------------                |
| 7 5 3   | NO     | Vi sono 7 studenti, 5 amicizie dirette e 3 domande.                                                           |
| 1 4     | NO     | Gli studenti 1,4,6 formano un gruppo di amici, mentre 2,3,5,7 formano un altro gruppo, separato dal primo.    |
| 1 6     | YES    | Quindi per le coppie (1,5), (1,7) la risposta è negativa: non vi sono amicizie dirette né amici comuni,       |
| 2 3     |        | mentre per la coppia (2,7) è positiva: 2 è amico di 3 che è amico di 5 che è amico di 7 (proprietà transitiva |
| 3 5     |        | ripetuta).                                                                                                    |
| 5 7     |        |                                                                                                               |
| 1 5     |        |                                                                                                               |
| 1 7     |        |                                                                                                               |
| 2 7     |        |                                                                                                               |

**Limiti**: tempo 2s, memoria 32MB.
