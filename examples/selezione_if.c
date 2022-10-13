/**
 * Programma di esempio
 * Author:  ER
 * Date:    2022/10/12
 * Note:    Il programma esemplifica il costrutto if - else
 * 			sintassi generale:
 * 			if(<condizione>) { <blocco se vera> } [ else { <blocco se falsa> }]
 * 				[ parte opzionale ]
 * 				{ } non necessarie, ma consigliate!!!, se <blocco> è una singola istruzione
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    // Per gli esempi, saranno utilizzati 3 interi
    // lettura tre numeri interi a, b e c
    printf("Immetti tre numeri a, b e c: ");
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    // Esempio 1: selezione senza alternativa
    {
        if (a > 0)
        {
            printf("Il valore a = %d e' positivo\n", a);
        }
    }
    // Esempio 2: selezione con alternativa
    {
        if (b < 0)
        {
            printf("Il valore b = %d e' negativo\n", b);
        }
        else
        {
            printf("Il valore b = %d e' positivo o nullo\n", b);
        }
    }
    // Esempio 3: selezione con alternativa = altra selezione
    {
        if (a < b)
        {
            printf("Il valore a = %d e' minore del valore b = %d\n", a, b);
        }
        else if (a == b)
        {
            printf("Il valore a = %d e' uguale al valore b = %d\n", a, b);
        }
        else
        {
            printf("Il valore a = %d e' maggiore del valore b = %d\n", a, b);
        }
    }
    // Esempio 4: selezione con condizione composta &&
    {
        // test appartenenza ad intervallo [min, max]
        int min = 1, max = 10;
        if ((min <= c) && (c <= max))
        {
            printf("Il valore c = %d appartiene all'intervallo [%d, %d]\n", c, min, max);
        }
    }
    // Esempio 4b: selezione con condizione composta && trasformata in doppio if
    {
        // test appartenenza ad intervallo [min, max]
        int min = 1, max = 10;
        if (min <= c)
        {
            if (c <= max)
            {
                printf("Il valore c = %d appartiene all'intervallo [%d, %d]\n", c, min, max);
            }
        }
    }
    // Esempio 5: selezione con condizione composta ||
    {
        // test non appartenenza ad intervallo [min, max]
        int min = 1, max = 10;
        if ((c < min) || (c > max))
        {
            printf("Il valore c = %d NON appartiene all'intervallo [%d, %d]\n", c, min, max);
        }
    }
    // Esempio 5b: selezione con condizione composta || trasformata in doppio if
    // Si noti la duplicazione del codice !!!
    {
        // test non appartenenza ad intervallo [min, max]
        int min = 1, max = 10;
        if (c < min)
        {
            printf("Il valore c = %d NON appartiene all'intervallo [%d, %d]\n", c, min, max);
        }
        else if (c > max)
        {
            printf("Il valore c = %d NON appartiene all'intervallo [%d, %d]\n", c, min, max);
        }
    }
    // Esempio 6: selezione piuttosto complessa
    {
        // test voto
        int min = 1, max = 10, voto;
        printf("Immetti il voto: ");
        scanf("%d", &voto);
        if (voto < min)
        {
            printf("Il voto %d NON appartiene all'intervallo [%d, %d]\n", c, min, max);
        }
        else if (voto > max)
        {
            printf("Il valore %d NON appartiene all'intervallo [%d, %d]\n", c, min, max);
        }
        else if (voto < 5)
        {
            printf("Piuttosto male..\n");
        }
        else if (voto < 6)
        {
            printf("Andrà meglio la prossima volta..\n");
        }
        else if (voto < 7)
        {
            printf("Ok ma puoi fare meglio..\n");
        }
        else if (voto < 10)
        {
            printf("Ottimo, o quasi..\n");
        }
        else // voto == 10 qui !!!!
        {
            printf("Meglio non si può..\n");
        }

        // NOTA: data la sostanziale analogia tra i vari casi si può fare meglio...
        // ma non con gli if ...
    }

    return 0;
}
