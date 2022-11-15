/**
 * Programma di esempio
 * Author:  ER
 * Date:    2022/1/15
 * Note:    Il programma esemplifica il costrutto switch
 * 			sintassi generale:
 * 			switch(<espressione intera>) {
 *				case <valore 1>:
 *					<blocco per caso 1>
 *					break;
 *				case <valore 2>:
 *					<blocco per caso 2>
 *					break;
 *					... e così via
 *				case <valore n>:
 *					<blocco per caso n>
 *					break;
 *				default:
 *					<blocco per casi rimanenti>
 *			}
 * 			N.B. : 	l'espressione dev'essere un risultato intero
 * 					il caso default è opzionale
 *					questo è l'unico caso in cui è ammissibile usare break!!!
 *					senza break l'esecuzione continua col blocco per il caso successivo
 *					( a volte è utile: vedere esempio mesi )
 *
 *          Note personali...
 *              Sostituisce molti if else-if else-if ... else (default)
 *              Raramente è una scelta ottimale...
 *              Se i case sono pochi, non ha senso ...
 *              Se i case sono tanti, cercare una regola... (esempio dei mesi!)
 *              Se una regola non c'è, memorizzare i vari casi (con array...)
 *              Negli esempi seguenti, l'unico veramente sensato è il menu di scelta
 *                  e in qualche caso, ad esempio se ogni blocco è un printf,
 *                  gestibile in modo più efficiente in altro modo.
 *              COMUNQUE LO DOVETE CONOSCERE E CAPIRE !!!!
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    // Assegnazione numero di giorni in base al mese
    // 1 = gennaio, ..., 12 = dicembre
    for (int mese = 0; mese <= 12; mese++)
    {
        int giorni;
        switch (mese)
        {
        case 1:  // fall-through
        case 3:  // fall-through
        case 5:  // fall-through
        case 7:  // fall-through
        case 8:  // fall-through
        case 10: // fall-through
        case 12: // fall-through
            giorni = 31;
            break;
        case 2:
            giorni = 28; // anno non bisestile
            break;
        case 4:  // fall-through
        case 6:  // fall-through
        case 9:  // fall-through
        case 11: // fall-through
            giorni = 30;
            break;
        default:
            giorni = 0;
        }
        printf("Il mese %d ha %d giorni\n", mese, giorni);
    }
    // menu' di scelta con opzione di termine
    int scelta = -1;
    do
    {
        printf("1. Greetings \n");
        printf("2. Quote \n");
        printf("0. Uscita \n");
        printf("Immetti la scelta: ");
        if (scanf("%d", &scelta) == 0)
        {
            // dato non acquisito
            scanf("%*[^\n]"); // elimina tutto fino al newline
            printf("scelta non valida\n");
        }
        else
        {
            switch (scelta)
            {
            case 1:
                printf("Ciao, mondo!\n");
                break;
            case 2:
                printf("I have a dream! (M.L.King)\n");
                break;
            case 0:
                // nothing to do here !!!
                break;
            default:
                printf("scelta non valida\n");
            }
        }
    } while (scelta != 0); // termine richieste
    printf("Arriverderci!\n");

    {
#define EXIT_CHAR ('X')
        // menu' di scelta con opzione di termine
        // come prima ma con opzione di tipo char
        char scelta = '?';
        do
        {
            printf("G. Greetings \n");
            printf("Q. Quote \n");
            printf("%c. Uscita \n", EXIT_CHAR);
            printf("Immetti la scelta: ");
            if (scanf(" %c", &scelta) == 0) // notare lo spazio prima %c, serve a scartare spazi, tabulazioni, newline ....
            {
                // dato non acquisito
                scanf("%*[^\n]"); // elimina tutto fino al newline
                printf("scelta non valida\n");
            }
            else
            {
                switch (scelta)
                {
                case 'G':
                    printf("Ciao, mondo!\n");
                    break;
                case 'Q':
                    printf("I have a dream! (M.L.King)\n");
                    break;
                case EXIT_CHAR:
                    // nothing to do here !!!
                    break;
                default:
                    printf("scelta non valida\n");
                }
            }
        } while (scelta != EXIT_CHAR); // termine richieste
        printf(" e buonanotte :-)\n");
    }

    // termine con codice 0 = successo
    return 0;
}
