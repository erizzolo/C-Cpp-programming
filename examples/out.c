/**
 * Esempio di output a stdout
 * Author:  ER
 * Date:    2019/10/01
 * Note:    Il programma visualizza a video (stdout) alcune variabili
 */

/// direttiva per usare le funzioni di standard I/O
#include <stdio.h>

int main(int argc, char * argv[]) {
    /// uso della funzione printf per visualizzare un messaggio
    printf("Hello, world! \n"); /// \n means new line
    /// printf returns the number of characters produced as an int
    int chars = printf(""); /// nothing: should return 0
    /// we can show variables and values in various formats
    printf("%d\n", 42); /// the number 42 in decimal format
    printf("%x\n", 42); /// the number 42 in hex format
    printf("%d\n", chars);  /// the (value of the) variable chars in decimal format
    /// other options as needed ... see documentation
    printf("%5.2f\n", 3.1415926);
    /// termine con codice 0 = successo
    return 0;
}
