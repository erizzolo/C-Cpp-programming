## Geometria (geometry)
In un file geometry.h, dichiarare le struct seguenti:

* punto, con membri di tipo double x e y, rappresentanti rispettivamente l’ascissa e l’ordinata di un punto nel piano cartesiano;
* segmento, con membri di tipo punto a e b, rappresentanti i due punti estremi del segmento;
* retta, con membri opportuni per memorizzare i coefficienti dell’equazione di una retta (nella forma a x + b y + c = 0);
* triangolo, con membri di tipo punto a, b e c, rappresentanti i vertici del triangolo;
* poligono, con membri opportuni per memorizzare il numero di lati ed i vertici del poligono.
* circonferenza, con membri opportuni per memorizzare il centro ed il raggio.

Per ciascuna delle struct precedenti, si dichiarino ed implementino le seguenti funzioni:
* void print(const <struct> &, ostream& out = cout);<br>
// visualizza sullo stream out (per default cout) la struct <br>
// in forma testuale opportuna
* <struct> get<struct>(...);
// restituisce la struct inizializzata con i parametri
// specificati
* <struct> copy(const <struct> & original);<br>
// restituisce la struct copia di quella specificata
* bool equals(const <struct> & lhs, const <struct> & rhs);<br>
// restituisce true se lhs e rhs “coincidono” false altrimenti
* double length(const <struct> &);<br>
// ove la funzione abbia senso
* double perimeter(const <struct> &);<br>
// ove la funzione abbia senso
* double area(const <struct> &);<br>
// ove la funzione abbia senso
* bool contains(const <struct> &, const punto & p);<br>
// ove la funzione abbia senso

Realizzare quindi nel file geometry.cpp un’applicazione che consenta all’utente di verificare il funzionamento della libreria geometry.h.
