/*
 * Programma di esempio di functions
 * Author:  ER
 * Date:    2022/10/22
 * Note:    Versione in C. Per quanto riguarda le funzioni C e C++ presentano
 *          notevoli differenze. Nei commenti sono riportate le principali
 *          con DIFF!!!
 */

#include <stdio.h>

#define DEBUG 1

int getPositiveInt(const char *nome); // read a positive int from the keyboard

int MCD(int a, int b); // compute MCD (GCD) of two int
// DIFF !!!
// la seguente dichiarazione è consentita solo in C++
// int MCD(int a, int b, int c); // Ok in C++: diversa lista parametri
// C NON consente funzioni con lo stesso nome e diversa lista parametri (overload):
// error: conflicting types for ‘MCD’; have ‘int(int,  int,  int)’
// mentre per C++ non è un problema
// DIFF !!!
// la seguente dichiarazione è consentita solo in C++
// double MCD(double a, double b);  // Ok in C++: diversa lista parametri
// C NON consente funzioni con lo stesso nome e diversa lista parametri (overload):
// error: conflicting types for ‘MCD’; have ‘double(double,  double)’
// mentre per C++ non è un problema
// DIFF !!!
// la seguente dichiarazione NON è consentita né in C né in C++
// double MCD(int a, int b);  // Ambigua in C++: uguale lista parametri
// Il messaggio di errore di C è sostanzailmente lo stesso di prima

void showSolution(int mcd, int a, int b, int c); // show problem and solution

int potenza(int base, int esponente);             // not used
int numeroGiorni(int giorno, int mese, int anno); // not used

int main(int argc, char *args[])
{
    // Acquisizione dati
    int a = getPositiveInt("a");
    int b = getPositiveInt("b");
    int c = getPositiveInt("c");

    // elaborazione
    int m = MCD(a, b);
    m = MCD(m, c);
    // int m = MCD(MCD(a, b), c); // alternativa

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
