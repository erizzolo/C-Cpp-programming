/*
 * Programma di esempio di functions
 * Author:  ER
 * Date:    2022/10/22
 * Note:    Versione in C++ con uso delle funzioni di I/O del C
 *          Si noti l'include stdio.h trasformato in cstdio
 *          Ovvero #include <nome.h> diventa
 *          #include <cnome>
 */

#include <cstdio>
#define DEBUG 1

/*
 * Il prototipo di una funzione è ciò che permette al compilatore di capire
 * se la chiamata della funzione rispetta le regole di sintassi, e quindi
 * di norma e' posto all'inizio del sorgente (o in alternativa, per quelle
 * funzioni non strettamente necessarie a capira il programma, prima del loro
 * primo utilizzo), tipicamente dopo le direttive #include, #define ed altre.
 * Il prototipo è costituito da:
 * 1. <tipo>        : il tipo di dato restituito dalla funzione (void se nessuno)
 * 2. <nome>        : il nome della funzione (un identificatore valido)
 * 3. <parametri>   : la lista dei (tipi dei) parametri tra parentesi ()
 * 4. ;             : terminatore !!!
 * Note:    -   2+3 costituiscono la cosiddetta "firma" della funzione, che la identifica
 *              In un sorgente può esistere UNA SOLA funzione con una data firma!!!
 *          -   in 3 non è necessario indicare i nomi con cui ci si riferirà ai
 *              parametri (non incidono sulla firma) ma per chiarezza è di solito bene farlo!!!
 *          -   il prototipo dev'essere inserito prima dell'utilizzo della funzione
 *          -   di solito si scrivono tutti dopo le direttive al compilatore (#define, ...)
 *              Non si inserisce subito la definizione della funzione (corpo ovvero blocco
 *              di istruzioni che la funzione eseguirà quando richiamata) per non "ritardare"
 *              il lettore a cui interessa la parte fondamentale, cioè la funzione main, e non
 *              i dettagli di implementazione.
 *
 * Esempio: int somma(int, int);
 *          evidentemente una funzione che restituisce la somma di due dati di tipo int
 *          quale sia il primo addendo e quale il secondo non fa differenza (commutatività)
 *          Ma:
 *          int potenza(int, int);
 *          evidentemente una funzione che restituisce la potenza di due dati di tipo int
 *          Non commutativa: qual e' la base e quale l'esponente?
 *          meglio dare i nomi ai parametri !!!
 *          int potenza(int base, int esponente);
 */

// prototipi delle funzioni
unsigned long long int getNumber();       // acquisisce da tastiera un numero ull
void printBinary(unsigned long long int); // stampa a video il numero dato, in binario

int main(int argc, char *args[])
{

    // Acquisizione dati
    // richiamo della funzione
    // notare () comunque, anche se nessun parametro nesessario...
    unsigned long long int n = getNumber();

    // elaborazione
    n += 1; // banale, non necessaria una funzione ...

    // Visualizzazione risultato
    // stampa in binario del numero acquisito e incrementato
    printBinary(n);

    // successful termination
    return 0;
}

/*
 * L'implementazione (il corpo) delle funzioni è ovviamente obbligatoria,
 * altrimenti il linker (parte del compilatore) si lamenta e si rifiuta
 * di creare l'eseguibile!!!!
 * Ma di solito non è fondamentale per capire cosa fa il programma.
 * Per questo motivo di solito si scrive alla fine del sorgente.
 * Si possono ovviamente specificare dettagli sul come la funzione
 * raggiunge il suo scopo.
 */
/*
 * acquisisce da tastiera un numero ull, senza controlli ...
 * @return  il numero acquisito da tastiera (si spera)
 */
unsigned long long int getNumber()
{
    // è comune dichiarare una variabile per il risultato
    unsigned long long int result;
    printf("Immetti un numero intero non negativo: ");
    scanf("%llu", &result);
    // restituisce il dato acquisito
    return result;
}

/*
 * stampa a video il numero dato, in binario
 * @param   number   il numero da stampare
 */
void printBinary(unsigned long long int number)
{
    // 1a fase: estraggo le cifre binarie di number, le conto
    // e le inserisco a rovescio in un altro numero (reverse)
    unsigned long long int reverse = 0; // bit a rovescio
    int nBits = 0;                      // numero di bits da visualizzare
    // do while perche' almeno un bit verrà visualizzato
    do
    {
        // prelevo il bit meno significativo
        unsigned long long int lsb = number & 1; // copia % 2
        // traslo a destra gli altri
        number >>= 1; // copia = copia / 2;
        // faccio spazio per l'inserimento
        reverse <<= 1; // reverse = reverse * 2
        // inserisco il bit estratto
        reverse |= lsb; // reverse = reverse + lsb;
        // estratto un bit in più
        nBits++;
        if (DEBUG)
            printf("LSB = %llu, number = %llu, reverse = %llu, nBits = %d \n", lsb, number, reverse, nBits);
    } while (number != 0);
    // ora visualizzo nBits cifre di reverse
    // sempre a rovescio, quindi nell'ordine in cui erano in number!!!
    while (nBits > 0)
    {
        // prelevo il bit meno significativo
        unsigned long long int lsb = reverse & 1; /// reverse % 2
        // traslo a destra gli altri
        reverse >>= 1; /// reverse = reverse / 2;
        printf("%llu", lsb);
        // decremento numero bits da visualizzare
        nBits--;
    }
    printf("\n");
    // optional return
    // quando l'esecuzione raggiunge la fine del blocco,
    // la funzione ha termine comunque
}