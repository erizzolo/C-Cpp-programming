## Scomposizione con massimo numero di fattori (maxFactors)
Si tratta di determinare, per un dato tipo numerico intero, qual è il massimo numero di coppie (fattore primo, esponente) che si ottiene dalla scomposizione di un numero naturale positivo esprimibile con il tipo considerato.

Ad esempio, se il tipo considerato avesse 1000 come valore massimo (ottenibile con numeric_limits<tipo>::max()), la scomposizione di un numero non potrebbe avere più di 4 fattori primi: infatti 2 x 3 x 5 x 7 = 210 e se vi fosse un altro fattore primo (o altri fattori primi necessariamente maggiori) il numero in questione non sarebbe esprimibile con il tipo dato.

Si crei quindi una funzione che verifica quanti numeri primi si possono moltiplicare prima di superare il limite del tipo numerico scelto con il seguente prototipo (il tipo restituito int è indipendente dal tipo numerico scelto):

``int maxPrimeFactors();``

La funzione deve:
* inizializzare una variabile prodotto (del tipo numerico scelto) al valore 1;
* generare ripetutamente i numeri primi in ordine crescente e moltiplicare prodotto per i primi trovati, terminando non appena il prodotto supererebbe il valore massimo del tipo numerico scelto (per evitare overflow, verificare con numeric_limits<tipo>::max() / prodotto > fattore_primo);
* restituire il numero di primi moltiplicati.

Verificare il risultato per diversi tipi numerici.
