/*
 * Scomposizione di un numero naturale > 1
 * Author:  ER
 * Date:    2022/10/23
 * Note:
 */

/*
## Scomposizione in fattori primi (scomponi)
Il teorema fondamentale dell'aritmetica afferma che ogni numero naturale
maggiore di 1 o è un numero primo o si può esprimere come prodotto di numeri
primi in modo unico se si prescinde dall'ordine in cui compaiono i fattori.
Scrivere un programma che, dato un numero naturale n > 1, produca in output
l’elenco delle coppie (fattore, esponente) della sua scomposizione in fattori
primi.
Assunzione: 1 < n < 2·10^9.
Formato di input: leggere da tastiera il numero n.
Formato di output: l’elenco separato da spazi delle coppie (fattore, esponente)
della scomposizione.
Esempi:
| Input         | Output                |
|---------------|-----------------------|
| 13            |(13, 1)                |
| 81            |(3, 4)                 |
| 1987653424    |(2, 4) (124228339 1)   |
Parti opzionali:
• usare in output una notazione leggermente più “matematica”, ad
esempio: “1987653424 = 2^4 * 124228339”
• usare in output codice HTML, ad esempio “1987653424 =
2<sup>4</sup> &coppie; 124228339” → 1987653424 = ...
*/

#include <stdio.h>

#define DEBUG 0

#define STANDARD 0
#define MATH 1
#define HTML 2
#define OUTPUT HTML

int main(int argc, char *argv[])
{

    int numero;
    printf("Numero: ");
    scanf("%d", &numero);

    // visualizzazione valori acquisiti per verifica
    printf("Numero: %d \n", numero);

    // elaborazione
    {
        int coppie = 0; // per output
        // algoritmo visto in classe (forza bruta con eliminazione)
        int fattore = 2; // minimo numero primo
        while (fattore <= numero / fattore)
        {
            int esponente = 0;
            while (numero % fattore == 0)
            {
                numero /= fattore;
                ++esponente;
            }
            if (DEBUG)
                printf("\tfattore = %d, esponente = %d \n", fattore, esponente);
            if (esponente > 0) // found !!!
            {
                if (OUTPUT == STANDARD)
                    printf("(%d, %d) ", fattore, esponente);
                if (OUTPUT == MATH)
                {
                    if (coppie != 0)
                        printf(" * ");
                    printf("%d", fattore);
                    if (esponente > 1)
                        printf("^%d ", esponente);
                    else
                        printf(" ");
                }
                if (OUTPUT == HTML)
                {
                    if (coppie != 0)
                        printf(" &times; ");
                    printf("%d", fattore);
                    if (esponente > 1)
                        printf("<sup>%d</sup> ", esponente);
                    else
                        printf(" ");
                }
                ++coppie;
            }
            ++fattore; // fattore successivo
        }
        // caso di ulteriore fattore primo
        if (numero > 1)
        {
            fattore = numero;
            if (OUTPUT == STANDARD)
                printf("(%d, 1) ", fattore);
            if (OUTPUT == MATH)
            {
                if (coppie != 0)
                    printf(" * ");
                printf("%d ", fattore);
            }
            if (OUTPUT == HTML)
            {
                if (coppie != 0)
                    printf(" &times; ");
                printf("%d", fattore);
            }
            ++coppie;
        }
        printf("\n");
    }

    return 0;
}
