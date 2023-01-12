## Scommettere o non scommettere? (monteCarlo)
### Descrizione del problema
Il mio amico Carlo ha lasciato il convento in cui era monaco (da cui il soprannome monteCarlo) e si è appassionato alle scommesse.

Mi ha quindi proposto una simile scommessa: si tratta di estrarre a caso due numeri interi x, y nell'intervallo [-1000,+1000] (estremi inclusi, tramite dei dadi che lui si è costruito negli anni di clausura e di cui mi fido) e verificare se la seguente espressione è vera o no: x * x + y * y <= 1000000.

Se è vera, vince Carlo ed io perdo la somma scommessa, altrimenti vinco io e guadagno il triplo della somma scommessa.

Ho deciso di accettare, ma vorrei sapere se alla lunga ci rimetterò!!!

Scrivete un'applicazione che simuli la scommessa per un numero n di volte e determini:

1. il numero di volte in cui vince Carlo ed in cui vinco io;
2. quale somma ho vinto/perso mediamente per ogni scommessa effettuata.

**Assunzione**: 1 ≤ n ≤ 10<sup>12</sup>. La somma scommessa è sempre un bitEuro (b€).

**Formato di input**: leggere n da tastiera, (senza controlli di validità).

**Formato di output**: il numero di vittorie di Carlo ed il numero di vittorie mie, separati da spazio, sulla prima riga; la vincita/perdita media sulla seconda riga.

