## Calcolatrice (calc)
Realizzare un’applicazione che riceva l’input da riga comando e consenta di eseguire un’operazione aritmetica tra due operandi numerici in virgola mobile, visualizzando il risultato sul flusso standard di output.

Il formato del comando per l’utilizzo dell’applicazione deve essere il seguente:
> calc.exe <operando 1> <operazione> <operando 2>
> 
> ad es. calc.exe 5.5 + 7.23
> 
> ad es. calc.exe 5.5 ^ 3
> 
> ad es. calc.exe -7.5E2 * 3.1415926

dove:
* <operando 1> ed <operando 2> sono rispettivamente il primo ed il secondo operando, specificati in formato decimale (eventualmente esponenziale come 1.5E-3);
* <operazione> è l’operazione richiesta, specificata con uno tra i seguenti simboli: + (addizione), - (sottrazione), x (moltiplicazione), / (divisione), e (elevamento a potenza).

Qualora l’applicazione venga eseguita senza il numero corretto di argomenti o qualora un argomento non sia corretto, essa deve:
* visualizzare sul flusso standard di errore (cerr) un messaggio con il formato corretto del comando;
* terminare restituendo codice di errore -1 per errato numero di argomenti e -2 per argomento/i non corretto/i.

Nel caso “normale” l’applicazione deve eseguire l’operazione indicata e
visualizzare sul flusso standard di output il risultato.