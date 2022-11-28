## Gioco “Indovina il numero”

Il gioco si svolge tra due giocatori e consiste nel permettere ad un giocatore (detto cercatore) di effettuare un certo numero di tentativi per indovinare il numero (compreso in un intervallo [min, max]) scelto dall’altro giocatore (detto custode).

Per ogni tentativo comunicato dal cercatore al custode, questi deve rispondere Y (yes) oppure N (no) a seconda che il tentativo corrisponda o meno al numero scelto.

Il gioco termina con vittoria del cercatore se questi indovina in un numero di tentativi non superiore al massimo, con vittoria del custode altrimenti.
### 1. You guess (youguess)
L’applicazione consente di svolgere all’utente il ruolo di cercatore mentre il computer svolge il ruolo di custode.
### 2. I guess (iguess)
L’applicazione consente di svolgere all’utente il ruolo di custode mentre il computer svolge il ruolo di cercatore.

***Esempio di output del caso 1 (in grassetto ciò che immette l’utente):***

Devi indovinare un numero compreso tra 0 e 14 inclusi, in 7 tentativi; hai ancora 7 tentativi.
Fai un tentativo: **5**

5 non e' il numero giusto; hai ancora 6 tentativi.

Fai un tentativo: **12**

12 non e' il numero giusto; hai ancora 5 tentativi.

Fai un tentativo: **9**

9 non e' il numero giusto; hai ancora 4 tentativi.

Fai un tentativo: **3**

3 non e' il numero giusto; hai ancora 3 tentativi.

Fai un tentativo: **1**

1 non e' il numero giusto; hai ancora 2 tentativi.

Fai un tentativo: **2**

2 non e' il numero giusto; hai ancora 1 tentativi.

Fai un tentativo: **7**

7 e' il numero giusto

Congratulazioni! Hai indovinato.
