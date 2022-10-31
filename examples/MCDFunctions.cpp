/*
 * Programma di esempio di functions
 * Author:  ER
 * Date:    2022/10/22
 * Note:    Versione in C++. Per quanto riguarda le funzioni C e C++ presentano
 *          notevoli differenze. Nei commenti sono riportate le principali
 *          con DIFF!!!
 */

#include <cstdio>

#define DEBUG 1
int getPositiveInt(const char *nome); // read a positive int from the keyboard

int MCD(int a, int b); // compute MCD (GCD) of two int
// DIFF !!!
// la seguente dichiarazione è consentita solo in C++
int MCD(int a, int b, int c); // Ok in C++: diversa lista parametri
// DIFF !!!
// la seguente dichiarazione è consentita solo in C++
double MCD(double a, double b); // Ok in C++: diversa lista parametri
// DIFF !!!
// la seguente dichiarazione NON è consentita né in C né in C++
// error: ambiguating new declaration of ‘double MCD(int, int)’
// double MCD(int a, int b); // Ambigua in C++: uguale nome e lista parametri (cioè uguale firma)

void showSolution(int mcd, int a, int b, int c); // show problem and solution

int potenza(int base, int esponente);             // not used
int numeroGiorni(int giorno, int mese, int anno); // not used

int main(int argc, char *args[])
{
    // Acquisizione dati
    int a = getPositiveInt("a");
    int b = getPositiveInt("b");
    int c = getPositiveInt("c");

    // nota: il compilatore capisce quale versione di MCD richiamare in base alla lista dei parametri
    printf("MCD(19, 57) = %d \n", MCD(19, 57));         // ok: MCD(int, int)
    printf("MCD(3.19, 1.57) = %f \n", MCD(3.19, 1.57)); // ok: MCD(double, double)
    // ma se ci sono ambiguità si rifiuta:
    // printf("MCD(3, 1.57) = %f \n", MCD(3, 1.57)); // NO: MCD(int, double) non c'è ???!!!
    // error: call of overloaded ‘MCD(int, double)’ is ambiguous

    // elaborazione
    //    int m = MCD(a, b);
    //    m = MCD(m, c);
    int m = MCD(a, b, c);

    // Visualizzazione risultato
    showSolution(m, a, b, c);

    // successful termination
    return 0;
}

int getPositiveInt(const char *nome)
{
    int result = 0; // assegno un valore non valido
    do
    {
        printf("Immetti il valore di %s: ", nome);
        if (scanf("%d", &result) == 0)
        {
            // dato non acquisito
            // elimina tutto fino al newline (necessario x evitare loop)
            scanf("%*[^\n]");
            printf("Impossibile acquisire il dato\n");
        }
        else if (result < 0)
        {
            printf("Dato errato: %s dev'essere > 0\n", nome);
            scanf("%*[^\n]"); // elimina tutto fino al newline comunque?
        }
        // scanf("%*[^\n]"); // elimina tutto fino al newline comunque?
    } while (result <= 0); // while(non valido)
    if (DEBUG)
        printf("Il valore di %s accettato e': %d \n", nome, result);
    return result;
    // int d1 = 26102022;
    // int d2 = 20221026;
    // int data = ((anno * 100) + mese) * 100 + giorno);
}

int MCD(int a, int b)
{
    int resto;
    do
    {
        resto = a % b;
        a = b;
        b = resto;
    } while (resto != 0);
    return a;
}

void showSolution(int mcd, int a, int b, int c)
{
    printf("MCD(%d, %d, %d) = %d \n", a, b, c, mcd);
}

double MCD(double a, double b)
{
    return 3.1415926; // ovviamente senza senso
}

int MCD(int a, int b, int c)
{
    return MCD(MCD(a, b), c);
}
