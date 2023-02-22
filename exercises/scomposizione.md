## Scomposizione (scomposizione)
Dato il tipo numerico number, opportunamente definito ad esempio con:
> ``using number = long long int;``

si definiscano le struct:
* ``couple`` con due membri di tipo ``number``, *fattore* ed *esponente*;
* ``scomposizione``, con membri un array di ``couple`` di opportune dimensioni, *coppie*,  ed uno  di tipo ``size_t``, *numCoppie*, inizializzato a zero.

Realizzare una funzione con il seguente prototipo:
> ``scomposizione scomponi(number n);``

che restituisca una struct ``scomposizione`` rappresentante la scomposizione in fattori primi del numero naturale positivo n.

Realizzare una funzione con il seguente prototipo:
> ``number ricomponi(const scomposizione &s);``

che restituisca il valore del numero corrispondente alla scomposizione in fattori primi specificata come parametro (che si suppone valida).

Realizzare due funzioni con i seguenti prototipi:
> ``void print(const couple &c, ostream &out = cout);``

> ``void print(const scomposizione &s, ostream &out = cout);``

che visualizzino un’opportuna rappresentazione testuale del parametro fornito ed un’applicazione per la verifica delle funzioni realizzate.
