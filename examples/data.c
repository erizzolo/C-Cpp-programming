/*
 * Programma di esempio: lettura e controllo di una data
 * Author:  ER
 * Date:    2022/10/19
 * Note:
 */

#include <stdio.h>

// per comodità (in C non esiste il tipo bool...)
#define FALSE 0
#define TRUE 1

int main(int argc, char *args[])
{
    printf("Esempio di input di una data in formato GG/MM/AAAA\n");
    printf("con controllo di validità e opportuni messaggi di errore\n");
    int giorno, mese, anno;
    int valido = FALSE;
    do
    {
        printf("Immetti una data in formato GG/MM/AAAA: ");
        // int letti = scanf("%d/%d/%d", &giorno, &mese, &anno);
        // the following should match also GG-MM-AAAA and GG.MM.AAAA
        int letti = scanf("%d%*[-./]%d%*[-./]%d", &giorno, &mese, &anno);
        if (letti != 3) // manca qualcosa ...
        {
            printf("La data non è nel formato valido\n");
        }
        else if (mese < 1 || mese > 12)
        {
            printf("Il mese dev'essere compreso tra 1 (gennaio) e 12 (dicembre)\n");
        }
        else
        {
            int giorni;
            if (mese == 2) // febbraio
            {
                giorni = (anno % 400 == 0) || ((anno % 4 == 0) && (anno % 100 != 0)) ? 29 : 28;
            }
            else if (mese < 8) // gennaio, marzo-luglio
            {
                giorni = 30 + (mese % 2); // 31 per 1 gennaio, 3 marzo, 5 maggio, 7 luglio
            }
            else // agosto-dicembre
            {
                giorni = 31 - (mese % 2); // 30 per 9 settembre, 11 novembre
            }
            // possibile alternativa
            if (mese == 2) // febbraio
            {
                giorni = (anno % 400 == 0) || ((anno % 4 == 0) && (anno % 100 != 0)) ? 29 : 28;
            }
            else if (mese == 4 || mese == 6 || mese == 9 || mese == 11) // aprile, giugno, settembre, novembre
            {
                giorni = 30;
            }
            else // tutti gli altri
            {
                giorni = 31;
            }
            if (giorno < 1 || giorno > giorni)
            {
                printf("Il giorno dev'essere compreso tra 1 e %d \n", giorni);
            }
            else
            {
                valido = TRUE;
            }
        }
        scanf("%*[^\n]"); // discard rest of the buffer...
    } while (!valido);
    printf("La data accettata e': %02d/%02d/%04d \n", giorno, mese, anno);
    // data come numero AAAAMMGG
    // (in quest'ordine perché così posso confrontare date come numero)
    int data = ((anno * 100) + mese) * 100 + giorno;
    printf("La data numerica e': %08d \n", data);

    // termine con codice 0 = successo
    return 0;
}
