## 	Configurazione (config)
È dato un file di testo contenente le opzioni di configurazione di un'applicazione.

Tale file è costituito da sezioni il cui inizio è indicato da una riga contenente il nome della sezione (privo di spazi) racchiuso tra parentesi quadre.

Le righe precedenti la prima sezione esplicita appartengono alla sezione GLOBAL.

Ciascuna opzione ha un nome (privo di spazi) ed un valore (possibilmente con spazi) ed è specificata nel file con il formato:

> &lt;nome&gt;=&lt;valore&gt;

Ad esempio:

> DSHELL=/bin/bash

Si noti che possono esservi opzioni con lo stesso nome in sezioni diverse e, a causa di errori, la stessa opzione può essere specificata più volte all'interno
della stessa sezione; in quest'ultimo caso, vale soltanto l'ultima specifica.

Naturalmente, è possibile che il file contenga righe di commento, che iniziano con il carattere #, ad esempio il seguente è un commento
> \# The DSHELL variable specifies the default login shell on your

Scrivere un'applicazione che riceva due(tre) parametri da riga comando, indicanti rispettivamente il nome del file di configurazione, il nome dell'opzione da ricercare e, opzionalmente, il nome della sezione in cui effettuare la ricerca, produca in output il valore dell'opzione, se presente.

Nel caso in cui il parametro indicante la sezione non sia presente, deve essere visualizzato, per ciascuna delle sezioni in cui l'opzione è specificata, il nome della sezione ed il valore dell'opzione.

Facoltativamente, prevedere l'aggiunta dell'opzione specificata nella sezione specificata oppure nella sezione GLOBAL, qualora l'opzione non sia presente.

