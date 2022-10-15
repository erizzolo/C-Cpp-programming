/*
 * Numero (di ponti) tra coppie (di isole)
 * Author:  ER
 * Date:    2022/10/07
 * Note:
 */

/*
## 1. Numero di ponti minimo
    Un arcipelago di N isole (attualmente prive di ponti) vuole collegare
    le varie isole con dei ponti. Determinare il numero minimo di ponti
    da costruire per permettere lo spostamento via terra da ciascuna isola
    a qualunque altra.

## 2. Numero di ponti massimo
    Un arcipelago di N isole (attualmente prive di ponti) vuole collegare
    le varie isole con dei ponti. Determinare il numero massimo di ponti
    che si possono costruire con al massimo un ponte tra ciascuna coppia
    di isole.
*/

// direttiva per usare le funzioni di standard I/O
#include <stdio.h>

int main(int argc, char *argv[])
{

    // dichiarazione dati di input
    int isole; // numero di isole
    // acquisizione dati di input
    // prompt per l'utente
    printf("Numero di isole: ");
    // acquisizione dato int in formato decimale
    scanf("%d", &isole); // notare la & prima del nome della variabile !!!!

    // visualizzazione valore acquisito per verifica
    printf("Numero di isole: %d \n", isole);

    // dichiarazione dati di output
    int minponti; // numero minimo di ponti
    int maxponti; // numero massimo di ponti

    // elaborazione
    // 1 isola: 0 ponti, per ogni isola successiva
    // un ponte per unirla al resto dell'arcipelago
    minponti = isole - 1;
    // per ciascuna isola (isole - 1) ponti verso le altre
    // diviso 2 perché così lo stesso ponte è contato 2 volte
    maxponti = isole * (isole - 1) / 2;
    // in alternativa
    // 1 isola: 0 ponti, per ciascuna i-esima isola successiva
    // (i = 2, 3, ..., I) un ponte verso le (i - 1) isole già collegate
    // i        1   2   3   4   5   ... I-1 I
    // ponti    0   1   2   3   4   ... I-2 I-1     +   = MAX
    //          I-1 I-2 I-3 I-4 I-5 ... 1   0       +   = MAX
    // somma    ---------------------------------------------------
    //          I-1 I-1 I-1 I-1 I-1 --- I-1 I-1     +   = 2 MAX
    //          ........... I termini ..........
    //                  (I-1) * I                   +   = 2 MAX
    //
    // MAX = I + (I - 1) / 2
    // visualizzazione risultati
    printf("numero minimo di ponti: %d \n", minponti);
    printf("numero massimo di ponti: %d \n", maxponti);

    // termine con codice 0 = successo
    return 0;
}
