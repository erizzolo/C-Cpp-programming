## Aggiornamenti (aggiorna)
È dato un file di testo (il “dizionario”) contenente le definizioni delle parole in lingua S.

In tale lingua le parole contengono da un minimo di tre fino ad un massimo di dieci caratteri latini e ciascuna parola può avere più definizioni (fino ad un massimo di 26), a seconda dell’ambito in cui viene utilizzata.

Di conseguenza il dizionario è formato da più righe ciascuna con il seguente formato:
> ``<parola><:><n><spazio><definizione>``

dove
* ``<parola>`` è la parola definita,
* ``<:>`` è un separatore costante (:),
* ``<n>`` è una singola lettera maiuscola dell'alfabeto latino indicante l'ambito della definizione,
* ``<spazio>`` è un singolo spazio separatore e
* ``<definizione>`` è una frase (di un'unica riga) che spiega il significato della parola.

Ad esempio, il dizionario può contenere le seguenti righe:

> ancora:A Elemento in ferro o acciaio, proprio... [omissis]
> 
> ancora:B Elemento di ferro dolce che comandato da... [omissis]
> 
> ancora:C Nei moderni orologi, parte dello scappamento... [omissis]

Periodicamente vengono rilasciati degli aggiornamenti per inserire i neologismi, eliminare le voci obsolete o correggere le definizioni imprecise.

Il file di testo che descrive gli aggiornamenti è formato da più righe (massimo 1000), ciascuna con il seguente formato:

> ``<operazione><parola><:><n>[<spazio><definizione>]``

dove
* ``<operazione>`` è un singolo carattere indicante il tipo di modifica da effettuare,
* ``<parola>`` è la parola cui la modifica deve essere applicata,
* ``<:>`` è un separatore costante (:),
* ``<n>`` è una singola lettera maiuscola dell'alfabeto latino indicante l'ambito della definizione,
* ``<spazio>`` è un singolo spazio separatore e
* ``<definizione>`` è una frase (di un'unica riga) che spiega il significato della parola.

Questi ultimi due elementi sono presenti solo per alcuni tipi di modifiche.

I caratteri indicanti le possibili modifiche sono i seguenti:
* ``+`` nuova parola o nuova definizione in un nuovo ambito (definizione presente)
* ``/`` parola obsoleta nell'ambito, voce da rimuovere (definizione assente)
* ``=`` parola già definita nell'ambito, definizione sostitutiva (definizione presente)

Ad esempio, l'aggiornamento può contenere può contenere le seguenti righe:

> /ancora:B
> 
> =ancora:C Nei vecchi orologi, parte dello scappamento... [omissis]
> 
> +ancora:D Nel linguaggio HTML, elemento che... [omissis]
> 

in base alle quali il nuovo dizionario verrebbe ad essere:

> ancora:A Elemento in ferro o acciaio, proprio... [omissis]
> 
> ancora:C Nei vecchi orologi, parte dello scappamento... [omissis]
> 
> ancora:D Nel linguaggio HTML, elemento che... [omissis]Esercizi

Scrivere un'applicazione che riceva tre parametri da riga comando, indicanti rispettivamente il (nome del) file di dizionario attuale, il file degli aggiornamenti ed il file del nuovo dizionario, produca quest'ultimo leggendo i dati dei primi due.

Facoltativamente, considerare il dizionario attuale e l'aggiornamento ordinati per parola/ambito e produrre un nuovo dizionario anch'esso ordinato.

Facoltativamente, prevedere quali anomalie si possono verificare (ad esempio modifica di rimozione per una voce non presente) e scrivere su un (altro) file (di log) dei messaggi di errore significativi per ciascuna anomalia.
