## Date (date)
Data una definizione di un tipo di dati “date” come la seguente:

```
struct date {
    char giorno, mese, anno;
};
```
in cui l'anno è memorizzato facendo corrispondere il valore 0 all'anno 2000, scrivere i prototipi delle funzioni seguenti:

| spiegazione del dato “restituito” dalla funzione         | nome           |
| -------------------------------------------------------- | -------------- |
| differenza in giorni tra due ”date”                      | dateDifference |
| “date” successiva ad una “date” specificata              | nextDate       |
| “date” corrispondente ad un dato giorno, mese, anno      | dateDMY        |
| giorno (Lun=0,…,Dom=6) di una “date” specificata         | dayOfWeek      |
| confronto ( -1 <, 0 =, +1 > ) tra due “date” specificate | dateCompare    |
| rappresentazione in caratteri della “date” specificata   | dateString     |
| “date” corrispondente ad un array di char specificato    | dateDMYString  |

Implementare le funzioni e scrivere un programma di test.

> Per le ultime due funzioni, usare il formato GG/MM/AAAA.

> Nota: è importante distinguere il passaggio degli eventuali parametri in modo che le funzioni non abbiano effetti indesiderati, indipendentemente da chi ne scriverà l'implementazione e le utilizzerà.
