/*
 * Esempio di output a stdout (standard output, usually the console)
 * Author:  ER
 * Date:    2022/10/11
 * Note:    Il programma visualizza a video (stdout) alcune variabili
 */

// direttiva per usare le funzioni di standard I/O
#include <stdio.h>

int main(int argc, char *argv[])
{
    // uso della funzione printf per visualizzare un messaggio
    printf("Hello, world! \n");             // \n means new line
    printf("\tHello, world! \n");           // \t means tabulation
    printf("\tThis is a backslash: \\ \n"); // \\ means a literal backslash
    // printf returns the number of characters produced as an int
    int chars = printf("");            // nothing written: should return 0
    chars = printf("Hello, world!\n"); // should return 13+
    // we can show variables and values in various formats
    printf("chars written: %d\n", chars); // the number of chars written in decimal format
    printf("chars written: %x\n", chars); // the number of chars written in hex format
    printf("A complex expression: %d\n", chars * chars / 42 + 12);
    // other options as needed ... see documentation
    printf("pi = (approximately) %5.2f\n", 3.1415926);
    /*
        NOTA BENE
        L'uso generale è:
        printf(<stringa di formato> [, <lista espressioni>])
        dove:
        - <stringa di formato> è obbligatoria è può contenere specifiche di conversione tipo %...
        - <lista espressioni> è facoltativa ma deve contenere tante espressioni,
            separate da , quanti sono gli specificatori contenuti in <stringa di formato>
        - le espressioni possono essere:
            - costanti: 3.14, 0, ...
            - singole variabili: chars, ...
            - espressione vere e proprie ...
        Per visualizzare %, usare %%, ad es. printf("%%") visualizza '%'
        Vedere https://en.cppreference.com/w/c/io/fprintf per ulteriori dettagli ed esempi
    */

    return 0;
}
