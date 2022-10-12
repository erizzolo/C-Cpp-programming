/*
 * Esempio di input da stdin (usually the keyboard)
 * Author:  ER
 * Date:    2022/10/11
 * Note:    Il programma acquisisce da tastiera (stdin) alcune variabili
 */

// direttiva per usare le funzioni di standard I/O
#include <stdio.h>

int main(int argc, char *argv[])
{
    // dichiarazione ed acquisizione di alcune variabili
    char initial = '?'; // note single quotes ...
    // prompt per l'utente
    printf("What's the initial of your name? ");
    // uso della funzione scanf per acquisire un dato di tipo carattere (singolo)
    // read a common character, a letter or a digit or ...
    scanf("%c", &initial);
    int age;
    // prompt per l'utente
    printf("Hi %c! Tell me your age: ", initial);
    // uso della funzione scanf per acquisire un dato int
    scanf("%d", &age); // notare la & prima del nome della variabile !!!!
    // visualizzazione valore acquisito (per verifica)
    printf("Are you really %d years old?!!! \n", age);
    // more complicated as well
    printf("Tell me your birthdate in GG/MM/AAAA format: ");
    int day, month, year;
    // scanf returns the number of successful conversions as an int
    int letti = scanf("%d/%d/%d", &day, &month, &year);
    // hope it's correct: --/--/----
    printf("Did you say %2d/%2d/%4d? \n", day, month, year);
    // a very huge integer number (up to 8 followed by 18 zeros)
    long long int hugeNumber;
    // prompt per l'utente
    printf("Enter 123456789123456789: ");
    scanf("%lld", &hugeNumber);
    printf("Ehi %c, you entered %lld ! \n", initial, hugeNumber);
    // a double floating point number
    double pigreco;
    // prompt per l'utente
    printf("Enter the value of pi: ");
    scanf("%lg", &pigreco);
    printf("The correct value is %20.16lg \n", 3.14159265358979323846);

    /*
        NOTA BENE
        L'uso generale è:
        scanf(<stringa di formato> [, <lista variabili>])
        dove:
        - <stringa di formato> è obbligatoria è può contenere specifiche di conversione tipo %...
        - <lista variabili> è facoltativa ma deve contenere tante variabili,
            separate da , quanti sono gli specificatori contenuti in <stringa di formato>
        - le variabili devono essere precedute da '&'
        Per leggere un carattere %, usare %%, ad es. scanf("%d%%", &p)
        consente di leggere, ad es. '20%' assegnando 20 a p.
        Vedere https://en.cppreference.com/w/c/io/fscanf per ulteriori dettagli ed esempi
    */

    /// termine con codice 0 = successo
    return 0;
}
