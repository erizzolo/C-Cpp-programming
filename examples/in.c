/**
 * Esempio di input da stdin
 * Author:  ER
 * Date:    2019/10/01
 * Note:    Il programma acquisisce da tastiera (stdin) alcune variabili
 */

/// direttiva per usare le funzioni di standard I/O
#include <stdio.h>

int main(int argc, char * argv[]) {
    /// dichiarazione di alcune variabili
    int n, m;
    char c;
    long long int number;
    /// prompt per l'utente
    printf("n = : ");
    /// uso della funzione scanf per acquisire un dato int
    scanf("%d", &n);    /// notare la & prima del nome della variabile !!!!
    /// visualizzazione valore acquisito
    printf("inserito n = %d\n", n);
    /// prompt per l'utente
    printf("m = : ");
    /// scanf returns the number of successful conversions as an int
    int correct = scanf("%d", &m);
    printf("correct = %d, m = %d \n", correct, m);
    /// prompt per l'utente
    printf("c = : ");
    /// uso della funzione scanf per acquisire un dato char
    scanf("%c", &c);    /// notare la & prima del nome della variabile !!!!
    printf("acquisito c = %c\n", c);

    /// prompt per l'utente
    printf("a very long long number = : ");
    /// uso della funzione scanf per acquisire un dato long long int
    scanf("%lld", &number);    /// notare la & prima del nome della variabile !!!!
    printf("acquisito numero = %lld\n", number);

    /// termine con codice 0 = successo
    return 0;
}
