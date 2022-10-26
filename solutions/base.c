/*
 * Base minima per rappresentare un numero naturale con un massimo numero di cifre
 * Author:  ER
 * Date:    2022/10/20
 * Note:
 */

/*
## Base minima (cifre)
Un numero naturale n si può rappresentare in diverse basi.
Ad esempio sette 7<sub>10</sub> = 111<sub>2</sub> = 21<sub>3</sub> = 13<sub>4</sub> = 12<sub>5</sub> = 11<sub>6</sub> = 10<sub>7</sub> = 7<sub>b</sub> (per b ≥ 8).
Dato un numero naturale n ed il numero di cifre c a disposizione (1 ≤ c ≤ 31), si determini il valore minimo della cifre b (b ≥ 2) per poter rappresentare n con non più di c cifre.
Si ricorda che con una sola cifra in cifre b si possono rappresentare i numeri da 0 a b − 1 e che il numero con rappresentazione di z + 1 cifre: cifra 1 seguita da z zeri corrisponde, in cifre b, a b<sup>z</sup>, ad 1000<sub>10</sub> = 10<sup>3</sup>.
**Assunzione**: 0 ≤ n ≤ 10<sup>9</sup>, 1 ≤ c ≤ 31.
**Formato di input:** leggere n e c da tastiera (senza controlli di validità)
**Formato di output**: il risultato richiesto, che rappresenta la cifre minima b (b ≥ 2) per poter rappresentare n con non più di c cifre.
**Esempi**:
| Input        | Output | Note                                                                                            |
| ------------ | ------ | ----------------------------------------------------------------------------------------------- |
| 0 7          | 2      | 0<sub>10</sub> = 0<sub>2</sub>  (1 cifra, b ≥ 2)                                                |
| 7 2          | 3      | 7<sub>10</sub> = 21<sub>3</sub> (111<sub>2</sub> quindi almeno 3 cifre)                         |
| 189234567 10 | 7      | 189234567<sub>10</sub> = 30435541543<sub>6</sub> (11 cifre) = 4455316164<sub>7</sub> (10 cifre) |
*/

#include <stdio.h>

#define DEBUG 1

int main(int argc, char *argv[])
{

    int numero, cifre;
    printf("Numero: ");
    scanf("%d", &numero);
    printf("Cifre: ");
    scanf("%d", &cifre);

    // visualizzazione valori acquisiti per verifica
    printf("Numero: %d \n", numero);
    printf("Cifre: %d \n", cifre);

    // elaborazione
    {
        // idea 1: forza bruta, calcolando il numero di cifre
        int base = 1;   // base minima necessaria
        int necessarie; // cifre necessarie con la data base
        do
        {
            base++;         // base successiva
            int n = numero; // dato temporaneo
            // sottoalgoritmo usato in "cifre"
            necessarie = 0;
            do
            {
                n /= base;    // get rid of the units
                necessarie++; // one digit more
            } while (n > 0);
            // fine sottoalgoritmo usato in "cifre"
            if (DEBUG)
                printf("\tbase = %d, cifre necessarie = %d \n", base, necessarie);
        } while (necessarie > cifre);
        printf("base minima: %d \n", base);
        printf("cifre utilizzate: %d \n", necessarie);
    }
    {
        // idea 2: vedo quante cifre sono necessarie in base 2: c2
        // se ne ho a sufficienza, ho finito, altrimenti:
        // so che cerco b tale b^cifre > numero > 2^(c2-1)
        // allora prendendo la radice (elevo a 1/cifre):
        // b > numero^(1/cifre) > 2^((c2-1)/cifre)
        // quindi la base successiva da cercare è b = 2^((c2-1)/cifre) + 1
        // Uso la potenza di 2 con esponente intero ...
        // e calcolo la potenza in modo banale
        int base = 2;       // base minima necessario
        int necessarie = 0; // cifre necessarie con la data base
        int n = numero;     // dato temporaneo
        do
        {
            n /= base;    // get rid of the units
            necessarie++; // one digit more
        } while (n > 0);
        if (DEBUG)
            printf("\tbase 2 = %d, cifre necessarie = %d \n", base, necessarie);
        if (necessarie > cifre) // base 2 non basta
        {
            int esponente = (necessarie - 1) / cifre;
            base = 1;
            while (esponente > 0)
            {
                base *= 2;
                esponente--;
            }
            do
            {
                base++;         // base successiva
                int n = numero; // dato temporaneo
                necessarie = 0;
                do
                {
                    n /= base;    // get rid of the units
                    necessarie++; // one digit more
                } while (n > 0);
                if (DEBUG)
                    printf("\tbase = %d, cifre necessarie = %d \n", base, necessarie);
            } while (necessarie > cifre);
        }
        printf("base minima: %d \n", base);
        printf("cifre utilizzate: %d \n", necessarie);
    }
    {
        // idea 3: come 2 ma ricerca "dicotomica"
        // to be done ...
    }

    return 0;
}
