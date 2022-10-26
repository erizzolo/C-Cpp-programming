/*
 * Numero di cifre per rappresentare un numero naturale
 * Author:  ER
 * Date:    2022/10/15
 * Note:
 */

/*
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
*/

#include <stdio.h>

#define DEBUG 1

int main(int argc, char *argv[])
{

    int numero, base;
    printf("Numero: ");
    scanf("%d", &numero);
    printf("Base: ");
    scanf("%d", &base);

    // visualizzazione valori acquisiti per verifica
    printf("Numero: %d \n", numero);
    printf("Base: %d \n", base);

    // elaborazione
    {
        // idea 1: "converto" e conto le cifre, senza memorizzarle
        int cifre = 0;  // numero di cifre necessario
        int n = numero; // dato temporaneo
        do
        {
            n /= base; // get rid of the units
            cifre++;   // one digit more
            if (DEBUG)
                printf("\tn = %d, cifre = %d \n", n, cifre);
        } while (n > 0);
        printf("1: numero di cifre: %d \n", cifre);
    }
    {
        // idea 2: esponente tale che (base^esponente > numero)
        int cifre = 1;      // esponente
        int potenza = base; // base^1 = base
        while (potenza <= numero)
        {
            potenza *= base; // next power
            cifre++;         // next esponente
            if (DEBUG)
                printf("\tpotenza = %d, cifre = %d \n", potenza, cifre);
        }
        printf("2: numero di cifre: %d \n", cifre);
    }
    // NOTA:
    // quale delle due soluzioni esegue meno operazioni?
    // quale delle due soluzioni può dare overflow?
    // Provare ad esempio con 1500000001 in base 10
    {
        // idea 3: come 2 ma evita overflow
        int cifre = 1;   // esponente
        int potenza = 1; // base^0 = 1
        while (numero / potenza >= base)
        {
            potenza *= base; // next power
            cifre++;         // next esponente
            if (DEBUG)
                printf("\tpotenza = %d, cifre = %d \n", potenza, cifre);
        }
        printf("3: numero di cifre: %d \n", cifre);
    }

    return 0;
}
