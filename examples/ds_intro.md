# Data structures

## Definizioni

Una *struttura dati* è un metodo di organizzare e gestire dei dati in memoria.

Alcune strutture dati hanno uno specifico modo di memorizzare *fisicamente* i dati e sono generalmente fornite in modo nativo dai linguaggi di programmazione.
Ad esempio, per il linguaggio C/C++, gli *array* e le *struct*.

In altri casi, le strutture dati hanno una specifica logica indipendente dalla memorizzazione fisica: si definiscono in questi casi strutture dati **astratte**: esse possono essere implementate in diverso modo, senza alcuna corrispondenza particolare ad una disposizione fisica dei dati in memoria.

## Caratteristiche generali

Per una data struttura, in un dato istante temporale, si definiscono:

| Termine  | Significato                    | Note                                                             |
| -------- | ------------------------------ | ---------------------------------------------------------------- |
| size     | numero di elementi presenti    | tipicamente 0 all'inizio, <= capacity nella vita della struttura |
| capacity | numero di elementi contenibili | massimo valore di *size* in un dato istante                      |

Il *size* di una struttura dati varia generalmente durante la vita della struttura, da un minimo di 0 (struttura vuota) ad un massimo di *capacity*.
Le strutture dati in cui *capacity* rimane costante dall'inzio alla fine della vita della struttura sono definite **statiche**, mentre quelle in cui *capacity* puù variare durante la vita della struttura sono definite **dinamiche**.
## Operazioni
Distinguiamo tra operazioni di tipo informativo (che non modificano la struttura) ed operativo (che modificano la struttura).
> nelle operazioni, *s* indica una struttura, *e* un elemento.
### Informative
| Termine            | Significato                                       | Note |
| ------------------ | ------------------------------------------------- | ---- |
| size(*s*)          | restituisce il numero di elementi presenti in *s* |      |
| capacity(*s*)      | restituisce la capacità massima di *s*            |      |
| contains(*s*, *e*) | verifica se *s* contiene l'elemento *e*           |      |
### Operative
| Termine          | Significato                             | Note                                       |
| ---------------- | --------------------------------------- | ------------------------------------------ |
| insert(*s*, *e*) | inserisce l'elemento *e* in *s*         |                                            |
| remove(*s*)      | rimuove un elemento da *s*              | può essere necessario specificare quale... |
| ...              | altre operazioni per logiche specifiche |                                            |

## Esempi

Particolare importanza hanno alcune semplici strutture dati quali:
* stack (pila)
* queue (coda)

Sono strutture dati lineari (possono essere rappresentate disponendo gli elementi in una linea) ed hanno una specifica logica di funzionamento per inserzione e rimozione:
* stack (pila): LIFO (Last In, First Out)
* queue (coda): FIFO (First In, First Out)

### Stack

Struttura dati lineare in cui inserimento e rimozione avvengono alla stessa estremità.

L'ordine di estrazione degli elementi è l'opposto di quello di inserimento.

Ad es. se inserisco A, B, C, D, E poi estraggo E, D, C, B, A.

Esempi di utilizzo:
* nella programmazione, per le variabili locali e le chiamate a funzione (parametri ed indirizzi di ritorno): consente un efficiente uso della memoria e la possibilità di chiamate ricorsive;
* funzioni di navigazione nei browser (back & forward tra le pagine visitate);
* undo/redo negli editor (annullamento e ripristino delle azioni effettuate);
* algoritmi di *backtracking*, in cui è necessario ritornare sui propri passi per modificare le scelte effettuate ed arrivare alla soluzione del problema (uscita da un labirinto, ...).

### Queue

Struttura dati lineare in cui inserimento e rimozione avvengono a diverse estremità.

L'ordine di estrazione degli elementi è lo stesso di quello di inserimento.

Ad es. se inserisco A, B, C, D, E poi estraggo A, B, C, D, E.

Esempi di utilizzo:
* per elaborare dati e richieste nell'ordine in cui sono stati generati;
* algoritmi di esplorazione in cui è necessario procedere dal primo elemento trovato ed ai successivi nello stesso ordine con cui gli elementi sono stati trovati (DFS, ...).

### Dequeue (deck)

Struttura dati lineare in cui inserimento e rimozione avvengono ad estremità decise dal programma.

Si tratta di un ageneralizzazione delle strutture vise in precedenza.
