/*
 * Programma di esempio
 * Author:  ER
 * Date:    2019/10/01
 * Note:    Il programma esemplifica il costrutto while
 * 			sintassi generale:
 * 			while(<condizione>) { <blocco ripetizione> }
 * 				{ } non necessarie, ma consigliate!!!, se <blocco> è una singola istruzione
 *				N.B. : numero di valutazioni della condizione uguale a:
 *					   numero di esecuzioni del blocco (risultato: condizione vera)
 *					   + 1 (l'ultima, con risultato: condizione falsa)
 *			Esempi di logica di ripetizione
 *			A.	In base alle operazioni residue
 *			B.	In base elle operazioni effettuate
 *			C.	In base al raggiungimento dell'obiettivo
 *			D.	... ovviamente i casi non si esauriscono qui
 *			La logica adattata al problema di stampare i primi n numeri dispari, n naturale
 */

#include <stdio.h>

// per (dis)attivare in modo rapido output di debug
#define DEBUG 1

int main(int argc, char *args[])
{
    {
        int n = 5;
        // A.	In base alle operazioni residue
        int residue = n;
        // 0. preparo la prima operazione
        int dispari = 1;
        // Ripetizione mentre ci sono operazioni residue
        if (DEBUG)
            printf("Before while: Operazioni residue = %d \n", residue);
        while (residue > 0)
        {
            // effettua una operazione !
            printf("Numero dispari = %d \n", dispari);
            // fatto, una in meno da effettuare
            residue--; // equivale a "residue = residue - 1;" ovvero a "residue -= 1;"
            if (DEBUG)
                printf("While: Operazioni residue = %d \n", residue);
            // preparo l'operazione successiva
            dispari += 2; // equivale a "dispari = dispari + 2;"
        }
        // fine !!!
        if (DEBUG)
            printf("After while: Operazioni residue = %d \n", residue);
        if (residue > 0)
        {
            // verifica superflua
            printf("oops!, devo aver sbagliato qualcosa !!!!!!!!!! \n");
        }
    }
    {
        int n = 5;
        // B.	In base elle operazioni effettuate
        int necessarie = n, effettuate = 0;
        // 0. preparo la prima operazione
        int dispari = 1;
        // Ripetizione mentre le operazioni effettuate sono inferiori a quelle necessarie
        if (DEBUG)
            printf("Before while: Operazioni necessarie = %d, effettuate = %d \n", necessarie, effettuate);
        while (effettuate < necessarie)
        {
            // effettua una operazione !
            printf("Numero dispari = %d \n", dispari);
            // fatto, una in più effettuata
            effettuate++; // equivale a "effettuate = effettuate + 1;" ovvero a "effettuate += 1;"
            if (DEBUG)
                printf("While: Operazioni necessarie = %d, effettuate = %d \n", necessarie, effettuate);
            // preparo l'operazione successiva
            dispari += 2; // equivale a "dispari = dispari + 2;"
        }
        // fine !!!
        if (DEBUG)
            printf("After while: Operazioni necessarie = %d, effettuate = %d \n", necessarie, effettuate);
        if (effettuate < necessarie)
        {
            // verifica superflua
            printf("oops!, devo aver sbagliato qualcosa !!!!!!!!!! \n");
        }
    }
    {
        int n = 5;
        // C.	In base al raggiungimento dell'obiettivo
        int obiettivo = 2 * n - 1, raggiunto = -1; // n-esimo numero dispari, valore raggiunto (0-esimo numero dispari)
        // 0. preparo la prima operazione
        int dispari = 1;
        // Ripetizione mentre non ho raggiunto l'obiettivo
        if (DEBUG)
            printf("Before while: raggiunto = %d, obiettivo = %d \n", raggiunto, obiettivo);
        while (raggiunto != obiettivo)
        {
            // effettua una operazione !
            printf("Numero dispari = %d \n", dispari);
            // fatto, raggiunto dispari
            raggiunto = dispari;
            if (DEBUG)
                printf("While: raggiunto = %d, obiettivo = %d \n", raggiunto, obiettivo);
            // preparo l'operazione successiva, sposto verso l'obiettivo
            dispari += 2; // equivale a "dispari = dispari + 2;"
        }
        // fine !!!
        if (DEBUG)
            printf("After While: raggiunto = %d, obiettivo = %d \n", raggiunto, obiettivo);
        if (raggiunto != obiettivo) // verifica superflua
        {
            printf("oops!, devo aver sbagliato qualcosa !!!!!!!!!! \n");
        }
    }

    // termine con codice 0 = successo
    return 0;
}
