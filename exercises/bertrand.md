## Il postulato di Bertrand (bertrand)
Descrizione del problema
Un numero intero x > 1 è detto numero primo se ha due soli divisori: 1 e x
stesso. Come è noto, 2, 3, 5, 7, 11 e 13 sono numeri primi mentre 15 non lo è
in quanto divisibile per 3.
La versione debole del postulato di Bertrand (che in realtà è il teorema
Bertrand-Chebyshev) afferma che, per ogni intero n > 1, esiste sempre almeno
un numero primo p tale che n < p < 2n.
Questa relazione è stata ipotizzata per la prima volta da Bertrand, che la
verificò personalmente per tutti i numeri n nell'intervallo 2 <= n <= 3∙10^6. La
relazione fu poi definitivamente dimostrata da Chebyshev.
Il compito che questo problema propone è un po' più ampio: scrivere un
programma che riceve un intero n > 1 e stabilisce quanti numeri primi p sono
compresi nell'intervallo n < p < 2n.
Assunzione: 2 ≤ n ≤ 3000.
Formato di input: leggere il numero da tastiera (senza controlli di validità)
Formato di output: il risultato richiesto, che rappresenta quanti numeri primi p
sono compresi nell'intervallo n < p < 2n, in forma decimale.
Esempi:
| Input | Output |
| ----- | ------ |
| 2     | 1      |
| 239   | 39     |
Autore/i
A.S. Stankevich, ACM ICPC Team, St. Petersburg State University of Information
