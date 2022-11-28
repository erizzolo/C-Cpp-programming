## Statistiche sul lancio di due dadi (cubes)

Utilizzando le funzioni di generazione di numeri pseudocasuali della libreria ``cstdlib``, realizzare un’applicazione che determini e visualizzi la frequenza con cui, in nLanci di due dadi (cubici, con facce numerate da 1 a 6 ugualmente
probabili), la somma dei valori ottenuti assume uno degli undici valori possibili (da 2 a 12). L’applicazione deve inoltre verificare se la somma delle frequenze ottenute è parti al numero di lanci effettuati.

> Si ricorda che:
> * la funzione ``int rand()`` restituisce un valore compreso tra 0 e RAND_MAX.
> * per inizializzare il generatore di numeri pseudocasuali è necessario richiamare la funzione ``void srand(unsigned seed)`` con un valore opportuno (in caso contrario, *“rand() behaves as if it was seeded with std::srand(1)”*);
> * per ottenere sequenze di numeri pseudocasuali diverse ad ogni esecuzione dell’applicazione è opportuno richiamare la funzione ``void srand(unsigned seed)`` con un valore derivato dall’istante di esecuzione dell’applicazione, ad esempio ottenuto richiamando la funzione ``time_t time(time_t* arg)`` della libreria ctime con parametro ``NULL`` (oppure ``nullptr``);
> * per ottenere un valore casuale nell’intervallo [min, max] è possibile utilizzare la seguente formula (sebbene non perfetta dal punto di vista statistico): ``min + rand() % (max - min + 1)``;
> * è richiesto di non usare più di una variabile per il conteggio delle frequenze, bensì una funzione ``int frequenza(int valore, int nLanci)`` che restituisce il conteggio delle occorrenze di un particolare valore;
> * è possibile aggiungere altre funzioni se lo si ritiene opportuno.

**Esempio di possibile output (per nLanci = 10000):**

2: 294 / 10000

3: 604 / 10000

4: 827 / 10000

5: 1116 / 10000

6: 1339 / 10000

7: 1653 / 10000

8: 1392 / 10000

9: 1069 / 10000

10: 840 / 10000

11: 510 / 10000

12: 260 / 10000

Oh! Total is 9904 instead of 10000
