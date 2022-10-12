/*
 * Esempio di dichiarazione variabili
 * Author:  ER
 * Date:    2022/10/11
 * Note:    Il programma non fa assolutamente nulla tranne restituire un codice al sistema operativo
 */

// variabili globali, accessibili ovunque

/*
    NOTA BENE
    Vi sconsiglio di usare variabili globali, perché:
    - sono modificabili ovunque e quindi rintracciare le modifiche è difficile;
    - vi possono essere conflitti di nomi con variabili locali;
    - ...
    Si usano solo in casi particolari, poiché lo spazio di memoria utilizzato
    dalle variabili globali è maggiore di quello delle variabili locali.
*/

// una variabile di tipo int
int primo;
/// più variabili di tipo char
char lettera, vocale, consonante;
// variabile di tipo int con valore iniziale
int minPrimo = 42;
// più variabili di tipo int con valori iniziali
int answer = 42, another = 45 + 5 * 10; // i.e. 95

int main(int argc, char *argv[])
{
    // variabili locali, accessibili nel blocco in cui sono dichiarate:
    // in questo caso, nella funzione main
    // una variabile di tipo int
    int factor;
    // una variabile di tipo double
    double position;
    // più variabili di tipo double con valori iniziali
    double speed = 42.0, force = 30.3, mass = 12.5, deltaTime = 0.01;
    double acceleration = force / mass;
    // Usage of variables: assignment
    position = 0.0;
    factor = 42; // value of factor becomes 42
    // Expressions
    double newPosition = position + speed * 0.1; // new position after 0.1 seconds
    // Use parentheses to modify/clarify evaluation
    double averageSpeed = (newPosition - position) / deltaTime;

    /*
        NOTA BENE
        Dichiarare le variabili quando servono, ovvero:
        - quando so come inizializzarle, oppure
        - all'inizio del blocco MINIMO in cui servono.
        Usare nomi significativi !!!
        - evitare come la peste a, b, c, ..., v1, v2, v3, ...
        - ciò consente di risparmiare commenti e fatica ...
        Se possibile, usare una riga di dichiarazione per ciascuna variabile
        - semplifica le eventuali modifiche;
        - semplifica la lettura.
    */

    // termine con codice 0 = successo
    return 0;
}
