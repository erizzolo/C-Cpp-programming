# File I/O

## Esempi di implementazioni

I nomi dei file sono strutturati così:

&lt;formato&gt;&lt;scopo&gt;&lt;linguaggio&gt;.&lt;estensione&gt;

| File                                      | Descrizione                | Note    |
| ----------------------------------------- | -------------------------- | ------- |
| [binaryCopy.c](file/binaryCopy.c)         | copia file binari          |         |
| [binaryCopy++.cpp](file/binaryCopy++.cpp) | copia file binari          |         |
| [binaryIn.c](file/binaryIn.c)             | legge da file dati binari  |         |
| [binaryIn++.cpp](file/binaryIn++.cpp)     | legge da file dati binari  |         |
| [binaryOut.c](file/binaryOut.c)           | scrive su file dati binari |         |
| [binaryOut++.cpp](file/binaryOut++.cpp)   | scrive su file dati binari |         |
| [csvIn++.cpp](file/csvIn++.cpp)           | legge da file dati csv     |         |
| [csvOut++.cpp](file/csvOut++.cpp)         | scrive su file dati csv    |         |
| [JSONIn++.cpp](file/JSONIn++.cpp)         | legge da file dati JSON    |         |
| [JSONOut++.cpp](file/JSONOut++.cpp)       | scrive su file dati JSON   |         |
| [txtCopy.c](file/txtCopy.c)               | copia file di testo        |         |
| [txtCopy.cpp](file/txtCopy.cpp)           | copia file di testo        | C-style |
| [txtCopy++.cpp](file/txtCopy++.cpp)       | copia file di testo        |         |

## Alcune note sulle implementazioni

In alcune implementazioni c'è un (minimo di) controllo errori, in altre (specialmente quelle di input in formato csv o json) tale controllo è sostanzialmente mancante.

Rispetto ai formati testuali, il formato binario, sebbene più efficiente in termini di spazio occupato (e quindi di velocità), non è così portabile come sembra: si pensi ad esempio al caso in cui piattaforma di scrittura e lettura abbiano diverse dimensioni per gli int!!

## Modalità di utilizzo

1. Ovviamente "studiare" e provare a modificare il codice.

2. Eseguire i programmi di scrittura per creare i file necessari alla lettura.

3. Adattare i programmi per utilizzare altri tipi di dato (ad es. struct game anziché planet).
