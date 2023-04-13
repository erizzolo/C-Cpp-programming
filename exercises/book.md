## Rubrica (book)
Realizzare un’applicazione che riceva l’input da riga comando e consenta di verificare la correttezza o meno dei dati forniti, visualizzando il risultato sul flusso standard di output/error.

Il formato del comando per l’utilizzo dell’applicazione deve essere il seguente:

> book.exe *nome* *cognome* *telefono* *età*
> 
> ad es. book.exe “Gian Paolo” Rossi +3901174562 23
> 
> ad es. book.exe “Gian-Paolo” Rossi 3901178562 32
> 
> ad es. book.exe Mario ”Dei Rossi” 011785624 52

dove:
* *nome* deve essere una stringa contenente solo lettere alfabetiche (almeno una in più rispetto ai separatori) ed eventuali spazi (come nell’esempio) o trattini (-) separatori non consecutivi;
* *cognome* deve essere una stringa contenente solo lettere alfabetiche (almeno una in più rispetto ai separatori) ed eventuali spazi separatori non consecutivi;
* *telefono* deve essere una stringa contenente solo cifre numeriche decimali ed un’eventuale segno ‘+’ iniziale;
* *età* deve essere un numero intero positivo compreso tra 1 e 125 (estremi inclusi).
  
Qualora l’applicazione venga eseguita senza il numero corretto di argomenti essa deve:
* visualizzare sul flusso standard di errore (cerr) un messaggio con il formato
corretto del comando.
* terminare restituendo codice di errore -10 per errato numero di argomenti.

Qualora l’applicazione venga eseguita ma almeno un argomento non sia corretto essa deve:
* visualizzare sul flusso standard di errore (cerr) un messaggio con il formato corretto per ciascun argomento errato;
* terminare restituendo codice di errore uguale all’opposto del numero di argomenti non corretti.

Nel caso “normale” l’applicazione deve terminare con codice di ritorno 0 senza
visualizzare alcunché.