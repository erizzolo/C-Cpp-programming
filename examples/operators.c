/*
 * Esempio di operazioni e operatori
 * Author:  ER
 * Date:    2022/10/11
 * Note:    Il programma non fa assolutamente nulla tranne restituire un codice al sistema operativo
 */
#include <stdio.h>

int main(int argc, char *argv[])
{
    int a, b;
    /*
    Operazione      Operandi        Risultato   C/C++
                    1               opposto     -a
    Addizione       2               somma       a + b
    Sottrazione     2               differenza  a - b
    Moltiplicazione 2               prodotto    a * b
    Divisione       2               quoziente   a / b   b != 0
                                    resto       a % b   b != 0
    */

    printf("a: ");
    scanf("%d", &a);
    printf("b: ");
    scanf("%d", &b);

    printf("a = %d, b = %d \n", a, b);

    printf("Operazione      Operandi        Risultato   C/C++ \n");
    printf("                1        %d     opposto     -a \n", -a);
    printf("Addizione       2        %d     somma       a + b \n", a + b);
    printf("Sottrazione     2        %d     differenza  a - b \n", a - b);
    printf("Moltiplicazione 2        %d     prodotto    a * b \n", a *b);
    printf("Divisione       2        %d     quoziente   a / b   b != 0 \n", a / b);
    printf("                         %d     resto       a %% b   b != 0 \n", a % b);


    // termine con codice 0 = successo
    return 0;
}
