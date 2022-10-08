/**
 * Esempio di dichiarazione variabili
 * Author:  ER
 * Date:    2019/10/01
 * Note:    Il programma non fa assolutamente nulla tranne restituire un codice al sistema operativo
 */

/// variabili globali, accessibili ovunque
/// una variabile di tipo int
int intVar;
/// più variabili di tipo char
char charVar1, charVar2, charVar3;
/// variabile di tipo int con valore iniziale
int anInt = 42;
/// più variabili di tipo int con valori iniziali
int anotherInt = 42, yetAnother = 45 + 5 * 10;  /// i.e. 95

/// la funzione principale le cui istruzioni saranno eseguite all'avvio del programma
int main(int argc, char * argv[]) {
    /// variabili locali, accessibili nel blocco in cui sono dichiarate:
    /// in questo caso, nella funzione main
    /// una variabile di tipo int
    int intLocal;
    /// più variabili di tipo double con valori iniziali
    double aDouble = 42.0, anotherDouble = 45 + 5.25 / 10.37;
    /// Usage of variables: assignment
    intLocal = 42;  /// value of intLocal becomes 42
    /// Expressions
    aDouble = intLocal * 3.14;  /// aDouble becomes 42 * 3.14
    aDouble = aDouble * aDouble / anotherDouble + 5.128;
    /// Parentheses to modify evaluation
    aDouble = aDouble * aDouble / ( anotherDouble + 5.128 );
    
    /// termine con codice 0 = successo
    return 0;
}
