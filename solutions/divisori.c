/*
 * Conteggio divisori di un numero naturale positivo
 * Author:  ER
 * Date:    2022/10/23
 * Note:
 */

/*
## Scrivere un programma che, dato un numero naturale n > 0, produca in output
il numero dei suoi divisori (compreso sé stesso e l’unità).
Assunzione: 1 < n < 2·10^9.
Formato di input: leggere da tastiera il numero n.
Formato di output: il numero dei divisori di n, in formato decimale.
Esempi:
| Input         | Output                |
|---------------|-----------------------|
| 13            |2                      |
| 81            |5                      |
| 1987653424    |10                     |
*/

#include <stdio.h>

#define DEBUG 1

int main(int argc, char *argv[])
{

    int numero;
    printf("Numero: ");
    scanf("%d", &numero);

    // visualizzazione valori acquisiti per verifica
    printf("Numero: %d \n", numero);

    // elaborazione
    {

        int numDivisori;
        if (numero == 1)
        {
            if (DEBUG)
                printf("Caso particolare\n");
            numDivisori = 1;
        }
        else
        {
            numDivisori = 2;
            int divisore = 2;
            while (divisore < numero / divisore)
            {
                if (DEBUG)
                    printf("Test divisore %d \n", divisore);
                if (numero % divisore == 0)
                {
                    if (DEBUG)
                        printf("Found %d and %d\n", divisore, numero / divisore);
                    numDivisori += 2;
                }
                divisore++;
            }
            // perfect square?
            if (numero == divisore * divisore)
            {
                numDivisori++;
            }
        }
        printf("%d ha %d divisori \n", numero, numDivisori);
    }

    return 0;
}
