/**
 * Esempio di dichiarazione ed inizializzazione di array
 */

#include <iostream>
#include <iomanip>

using namespace std;

/**
 * Un array è una struttura dati che contiene una sequenza di dati omogenei
 * (dello stesso tipo) allocati in memoria in modo contiguo (uno dopo l'altro).
 * L'utilizzo degli array è quindi utile quando si vogliano memorizzare
 * più dati con il medesimo significato logico (e di conseguenza lo stesso tipo)
 * ma riferiti ad entità diverse (in genere più di una).
 * Ad esempio:
 * 1. i voti di più studenti in una medesima prova;
 * 2. i voti in diverse materie del medesimo studente;
 * 3. le masse dei diversi pianeti del sistema solare;
 * 4. i giorni dei diversi mesi di un anno.
 * 5. i coefficienti di un polinomio.
 * In questi esempi si ha:
 * Esempio  Significato logico  Entità di riferimento
 * 1        Voto                Studente
 * 2        Voto                Materia
 * 3        Massa               Pianeta
 * 4        Giorni              Mese
 * 5        Coefficiente        Termine di grado i
 * Attenzione: quando il significato logico dei dati è diverso, non è
 * opportuno usare un array solo perché il tipo di dato è lo stesso!
 * Ad esempio, se voglio rappresentare una data del 21° secolo con i dati
 * giorno, mese, anno, potrei usare lo stesso tipo (char) per i tre dati,
 * ma aggregarli in un array porterebbe solo confusione nella logica dei dati:
 * ad es. uso il formato giorno, mese, anno oppure anno, mese, giorno?
 * E se si dovesse gestire una data in secoli diversi usando per l'anno
 * il tipo int, dovrei modificare il tipo di dato anche per giorno e mese ???
 * Per questo esistono le struct (cui si rimanda).
 */

int main()
{
    // dichiarazione di array non inizializzati
    /**
     * Per dichiarare una variabile di tipo array, senza inizializzarne gli
     * elementi, è sufficiente ma obbligatorio aggiungere, dopo il nome della
     * variabile, il numero di elementi che si desidera tra parentesi quadre.
     * Ovviamente, il numero di elementi dev'essere un'espressione intera
     * non negativa.
     */
    {
        // esempio 1:
        const int numero_studenti = 10; // numero di studenti presenti alla prova
        int voti[numero_studenti];      // array di int non inizializzati
    }
    {
        // esempio 2:
        const int numero_materie = 6; // numero di materie
        int voti[numero_materie];     // array di int non inizializzati
    }
    {
        // esempio 3:
        const int numero_pianeti = 8; // numero di pianeti
        double masse[numero_pianeti]; // array di double non inizializzati
    }
    {
        // esempio 4:
        const int numero_mesi = 12; // numero di mesi dell'anno
        int giorni[numero_mesi];    // array di int non inizializzati
    }
    {
        // esempio 5:
        const int grado = 4;            // grado del polinomio
        double coefficienti[grado + 1]; // array di double non inizializzati
    }
    {
        // esempio 6: numero di elementi espressione variabile (noto solo a runtime)
        int latoScacchiera; // lato di una scacchiera quadrata
        cout << "Lato della scacchiera quadrata: ";
        cin >> latoScacchiera;
        int celle[latoScacchiera * latoScacchiera];                              // array di int di dimensione variabile
        cout << "Dimensione array: " << sizeof(celle) << endl;                   // dimensione totale in bytes
        cout << "Dimensione di un elemento: " << sizeof(celle[0]) << endl;       // dimensione di un elemento
        cout << "Numero di celle: " << sizeof(celle) / sizeof(celle[0]) << endl; // numero di celle
    }
    // esempio di errore: non è possibile determinare il numero di elementi
    // e quindi lo spazio da riservare in memoria...
    // error: storage size of 'verita' isn't known
    // bool verita[];

    // dichiarazione di array e contestuale inizializzazione
    /**
     * E' possibile inizializzare un array specificando una sequenza di valori
     * (anche tramite espressioni) del tipo opportuno.
     * La sequenza non deve necessariamente essere completa, ma non può contenere
     * più elementi del necessario.
     * Se non si specifica il numero di elementi, il compilatore assume che
     * la sequenza di valori sia completa (numero elementi = numero valori).
     * Nota: il segno di uguaglianza si può omettere (universal initializer !?).
     */
    {
        // esempio 1:
        const int numero_studenti = 10; // numero di studenti presenti alla prova
        // int voti[numero_studenti] = {6, 7, 4, 3}; // altri elementi non inizializzati
        int voti[numero_studenti]{6, 7, 4, 3}; // altri elementi non inizializzati
    }
    {
        // esempio 2:
        const int numero_materie = 6; // numero di materie
        // error: too many initializers for ‘int [6]’
        // int voti[numero_materie] = {6, 5, 7, 3, 8, 4, 3}; // troppi valori
        // int voti[numero_materie]{6, 5, 7, 3, 8, 4, 3}; // troppi valori
    }
    {
        // esempio 3:
        // enum pianeta { Mercurio, Venere, Terra, Marte, Giove, Saturno, Urano, Nettuno };
        // double masse[] = {3.33E23, 4.8690E24, 5.97219E24, 6.4191E23, 1.8987E27, 5.6851E26, 8.6849E25, 1.0244E26}; // array di 8 double
        double masse[]{3.33E23, 4.8690E24, 5.97219E24, 6.4191E23, 1.8987E27, 5.6851E26, 8.6849E25, 1.0244E26}; // array di 8 double
        const int numero_pianeti = sizeof(masse) / sizeof(masse[0]);                                           // numero di pianeti
    }
    {
        // esempio 4:
        // enum mese { Gennaio, Febbraio, Marzo, Aprile, Maggio, Giugno, Luglio, Agosto, Settembre, Ottobre, Novembre, Dicembre };
        const int numero_mesi = 12;                                                 // numero di mesi dell'anno
        int giorni[numero_mesi] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // array di int inizializzati
    }
    {
        // esempio 5:
        const int grado = 4;                                       // grado del polinomio
        double coefficienti[grado + 1]{1.0, -2.5, 3.4, 0.0, -1.5}; // -1.5 x^4 +3.4 x^2 - 2.5 x + 1.0
    }
    /**
     * L'accesso ai dati avviene elemento per elemento: non è possibile operare
     * sull'intero array (se non nascondendo l'accesso ai singoli elementi,
     * ad es. in una funzione).
     * I singoli dati sono individuati da <nome array>[<indice>], dove
     * <indice> è un'espressione intera (nota a runtime) con valori
     * nel range [0, numero elementi - 1] = [0, numero elementi).
     * Si noti che il compilatore non fa alcun controllo sul valore dell'indice
     * (per questioni di efficienza: si evita di "rallentare" l'accesso) !!!
     * L'uso di indici al di fuori del range è "undefined behaviour":
     * in genere si ha errore logico e spesso crash dell'applicazione!!!
     */
    {
        const int numero_studenti = 10;           // numero di studenti presenti alla prova
        int voti[numero_studenti] = {6, 7, 4, 3}; // altri elementi non inizializzati
        // esempi di accesso valido = con indice compreso tra 0 e numero_studenti - 1
        cout << "Lo studente 2 ha preso " << voti[2] << endl;
        cout << "Lo studente 2 e' simpatico, aumentiamogli il voto!" << endl;
        voti[2]++;
        cout << "Lo studente 2 ha preso " << voti[2] << endl;
        // esempio di accesso non valido (probabilmente senza crash)
        cout << "Lo studente (inesistente) " << numero_studenti << " ha preso " << voti[numero_studenti] << endl;
        // esempio di (tentativo di) accesso a tutti gli elementi
        cout << "Gli studenti hanno preso " << voti << endl;
        // si noti che usare il nome dell'array senza indici equivale all'indirizzo del primo elemento !!!
    }
    {
        // dimostrazione dell'allocazione contigua degli elementi
        double masse[] = {3.33E23, 4.8690E24, 5.97219E24, 6.4191E23, 1.8987E27, 5.6851E26, 8.6849E25, 1.0244E26}; // array di 8 double
        const int numero_pianeti = sizeof(masse) / sizeof(masse[0]);                                              // numero di pianeti
        cout << "Dato un array di " << numero_pianeti << " double (le masse dei pianeti):" << endl;
        cout << "Indice  Elemento" << setw(16) << "Indirizzo" << setw(16) << "Valore" << endl;
        for (int i = 0; i < numero_pianeti; ++i)
        {
            cout << i << "\tmasse[" << i << "]" << setw(16) << &masse[i] << setw(16) << masse[i] << endl;
        }
        cout << "array\tmasse   " << setw(16) << masse << endl;
        // si noti che usare il nome dell'array senza indici equivale all'indirizzo del primo elemento !!!
    }

    return 0;
}
