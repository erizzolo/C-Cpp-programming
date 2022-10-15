## Base minima (base)
Un numero naturale n si può rappresentare in diverse basi.

Ad esempio sette 7<sub>10</sub> = 111<sub>2</sub> = 21<sub>3</sub> = 13<sub>4</sub> = 12<sub>5</sub> = 11<sub>6</sub> = 10<sub>7</sub> = 7<sub>b</sub> (per b ≥ 8).

Dato un numero naturale n ed il numero di cifre c a disposizione (1 ≤ c ≤ 31), si determini il valore minimo della base b (b ≥ 2) per poter rappresentare n con non più di c cifre.

Si ricorda che con una sola cifra in base b si possono rappresentare i numeri da 0 a b − 1 e che il numero con rappresentazione di z + 1 cifre: cifra 1 seguita da z zeri corrisponde, in base b, a b<sup>z</sup>, ad 1000<sub>10</sub> = 10<sup>3</sup>.

**Assunzione**: 0 ≤ n ≤ 10<sup>9</sup>, 1 ≤ c ≤ 31.

**Formato di input:** leggere n e c da tastiera (senza controlli di validità)

**Formato di output**: il risultato richiesto, che rappresenta la base minima b (b ≥ 2) per poter rappresentare n con non più di c cifre.

**Esempi**:
| Input        | Output | Note                                                                                            |
| ------------ | ------ | ----------------------------------------------------------------------------------------------- |
| 0 7          | 2      | 0<sub>10</sub> = 0<sub>2</sub>  (1 cifra, b ≥ 2)                                                |
| 7 2          | 3      | 7<sub>10</sub> = 21<sub>3</sub> (111<sub>2</sub> quindi almeno 3 cifre)                         |
| 189234567 10 | 7      | 189234567<sub>10</sub> = 30435541543<sub>6</sub> (11 cifre) = 4455316164<sub>7</sub> (10 cifre) |
