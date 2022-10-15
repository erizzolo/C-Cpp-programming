## Numero di cifre (cifre)
Un numero naturale n si può rappresentare in diverse basi.

Ad esempio sette 7<sub>10</sub> = 111<sub>2</sub> = 21<sub>3</sub> = 13<sub>4</sub> = 12<sub>5</sub> = 11<sub>6</sub> = 10<sub>7</sub> = 7<sub>b</sub> (per b ≥ 8).

Dato un numero naturale n ed il valore della base B (2 ≤ B ≤ 16), si determini il numero di cifre (significative!) necessarie per rappresentare n in base B.

Si ricorda che lo zero si rappresenta con una cifra 0 qualunque sia la base.

(Quale altro numero si rappresenta allo stesso modo in tutte le diverse basi?)

**Assunzione**: 0 ≤ n ≤ 10<sup>9</sup>, 2 ≤ B ≤ 16.

**Formato di input**: leggere n e B da tastiera (senza controlli di validità)

**Formato di output**: il risultato richiesto, che rappresenta quante cifre si usano per rappresentare n in base B.
**Esempi**:
| Input        | Output | Note                                       |
| ------------ | ------ | ------------------------------------------ |
| 0 7          | 1      | 0<sub>10</sub> = 0<sub>7</sub> (1 cifra)   |
| 7 2          | 3      | 7<sub>10</sub> = 111<sub>2</sub> (3 cifre) |
| 189234567 10 | 9      | 189234567<sub>10</sub> (9 cifre)           |
