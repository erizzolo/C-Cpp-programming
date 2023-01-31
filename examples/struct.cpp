/**
* Esempio di dichiarazione, inizializzazione ed uso di struct
*/

#include <iostream>
#include <iomanip>

using namespace std;

/**
 * Una struct è una struttura dati che contiene un insieme di dati diversi
 * allocati in memoria in un unico blocco.
 * N.B. - Non necessariamente nella sequenza di definizione!
 * L'utilizzo delle struct è quindi utile quando si vogliano memorizzare
 * più dati con diverso significato logico (e di conseguenza diverso tipo)
 * ma riferiti ad un'unica entità.
 * Ad esempio:
 * 1. anno, mese e giorno di una data;
 * 2. nome, cognome, data di nascita e voti di uno studente;
 * 3. nome, docente e numero ore di una materia;
 * 4. massa, periodo di rivoluzione, etc... di un pianeta;
 * 5. anno, mese, giorno, ora, minuti, secondi di un istante temporale;
 * 6. quoziente e resto di una divisione intera.
 * In questi esempi si ha:
 * Esempio  Significato logico  Entità di riferimento
 * 1        Anno, mese, giorno  Data
 * 2        Nome, cognome, ...  Studente
 * 3        Nome, docente, ...  Materia
 * 4        Massa, periodo, ... Pianeta
 * 5        Anno, mese, ...     Istante nel tempo
 * 6        Quoziente, resto    Divisione
 *
 * Nota terminologica:
 * Linguaggio   C/C++   Pascal
 * tipo dato    struct  record
 * elemento     member  field
 *
 * Accesso agli elementi di una variabile struct:
 * <nome variabile>.<nome elemento>
 * Ad es., data la variabile di nome oggi con elemento di nome giorno: oggi.giorno
 */

/// dichiarazione di struct come tipo di dato
/// Di norma, le struct definiscono un nuovo tipo di dato, utilizzabile poi
/// in tutto il codice, e quindi sono dichiarate a livello globale
/// esempio 1:
struct data
{
    char anno, mese, giorno; // anno 0 = 2000
    char sett[10] {"lunedì"};
};

// utility function to print a date
void printDataDMY(data d, ostream &os = cout);

/// esempio 2:
#define NUM_MATERIE 10
struct studente
{
    char nome[30 + 1], cognome[30 + 1]; // name and surname (max 30 chars)
    data birthdate;                     // birth date
    int voti[NUM_MATERIE];              // grades
};
/// Nota 1: le struct possono contenere array (per ora di dimensione costante)
/// Nota 2: le struct possono contenere altre struct

/// esempio 3:
struct materia
{
    char nome[30 + 1];    // subject name (max 30 chars)
    char docente[30 + 1]; // teacher's surname
    int numOre;           // classes per week
};
/// esempio 4:
struct pianeta
{
    char nome[10 + 1]; // planet name (max 10 chars)
    double massa;      // mass in kg
    double distance;   // distance from Sun in km
    bool abitato;      // inhabited (usually false)
    int numSatelliti;  // number of satellites
};

/// esempio 5:
struct tempo
{
    char anno = 0, mese = 1, giorno = 1, ore{0}, minuti{0}, secondi{0};
};
/// Nota 1: quando serve, si possono indicare valori di default
/// per default: 01/01/2000 00:00:00

/// esempio 6 (da cstdlib) già definite in std::
// struct div_t { int quot; int rem; };
// struct ldiv_t { long quot; long rem; };
// struct lldiv_t { long long quot; long long rem; };
/// Quote from https://en.cppreference.com/w/cpp/numeric/math/div
/// On many platforms, a single CPU instruction obtains both the quotient and
/// the remainder, and this function may leverage that, although compilers are
/// generally able to merge nearby / and % where suitable.

// utility to get the difference in B between addresses
int offset(void *base, void *address)
{
    return (long)address - (long)base;
}
int main()
{
    /// dichiarazione di variabili di tipo struct
    /**
     * Per dichiarare una variabile di tipo struct, senza inizializzarne gli
     * elementi, è sufficiente usare come tipo il nome della struct.
     */
    {
        /// esempio 1:
        data oggi; // variabile di nome <oggi> e di tipo <data>
        /// 14 marzo 1879
        oggi.anno = -121; // 0 = 2000
        oggi.mese = 3;
        oggi.giorno = 14;

        /// esempio 2: con inizializzazione dei componenti (nell'ordine di dichiarazione!!!)
        studente genius{"Albert", "Einstein", oggi, {10, 10, 10, 10, 10, 10}};
    }
    {
        /// esempio 3: con inizializzazione dei componenti (nell'ordine di dichiarazione!!!)
        materia info{"Informatica", "Rizzolo/Gobbo", 6};
        cout << info.nome << ": docente/i " << info.docente << " (" << info.numOre << "h/sett)" << endl;
    }
    {
        /// esempio 4: con inizializzazione dei componenti (nell'ordine di dichiarazione!!!)
        pianeta terra{"Earth", 5.9726E24, 147098074, true, 1}; // la distanza è quella minima ...
    }
    {
        /// esempio 5:
        tempo riferimento;
    }
    {
        /// esempio 6:
        int num = 17, den = 3;
        div_t result = div(num, den);
        cout << num << " = " << result.quot << " * " << den << " + " << result.rem << endl;
    }
    {
        /// qualche operazione di base sulle variabili di tipo struct
        data twin_towers{1, 9, 11}; // 01/09/11 = 1 settembre 2011 o 11 settembre 2001 o ...
        /// Cannot cout a variable of type struct: there is no "standard" way ...
        // error: no match for ‘operator<<’ (operand types are ‘std::ostream {aka std::basic_ostream<char>}’ and ‘data’)
        // cout << twin_towers << endl;
        /// Ok: can assign (copy) a struct variable to another one
        data strike = twin_towers;
        /// Ok: can pass a struct variable (by value i.e. a copy) to a function
        printDataDMY(strike);
    }
    {
        cout << "Dimostrazione dell'allocazione (non contigua) degli elementi" << endl;
        pianeta marte{"Mars", 6.4185E23, 206644545, false, 2}; // la distanza è quella minima ...
        cout << "Data una variabile marte di una struct così definita:\n\
        struct pianeta\n\
        {\n\
            char nome[10 + 1]; // planet name (max 10 chars)\n\
            double massa;      // mass in kg\n\
            double distance;   // distance from Sun in km\n\
            bool abitato;      // inhabited (usually false)\n\
            int numSatelliti;  // number of satellites\n\
        };" << endl;
        cout << "l'allocazione e' la seguente:" << endl;
        cout << setw(16) << "Elemento" << setw(16) << "Indirizzo" << setw(16) << "Valore" << setw(10) << "Size [B]" << setw(10) << "Offset" << endl;
        cout << setw(16) << "marte" << setw(16) << &marte << setw(16) << "N/A" << setw(10) << sizeof(marte) << setw(10) << &marte - &marte << endl;
        cout << setw(16) << "nome" << setw(16) << &marte.nome << setw(16) << marte.nome << setw(10) << sizeof(marte.nome) << setw(10) << offset(&marte, &marte.nome) << endl;
        cout << setw(16) << "massa" << setw(16) << &marte.massa << setw(16) << marte.massa << setw(10) << sizeof(marte.massa) << setw(10) << offset(&marte, &marte.massa) << endl;
        cout << setw(16) << "distance" << setw(16) << &marte.distance << setw(16) << marte.distance << setw(10) << sizeof(marte.distance) << setw(10) << offset(&marte, &marte.distance) << endl;
        cout << setw(16) << "abitato" << setw(16) << &marte.abitato << setw(16) << marte.abitato << setw(10) << sizeof(marte.abitato) << setw(10) << offset(&marte, &marte.abitato) << endl;
        cout << setw(16) << "numSatelliti" << setw(16) << &marte.numSatelliti << setw(16) << marte.numSatelliti << setw(10) << sizeof(marte.numSatelliti) << setw(10) << offset(&marte, &marte.numSatelliti) << endl;
        cout << endl;
        cout << "Si noti che il compilatore lascia spazi vuoti (padding) per allineare i dati" << endl;
        cout << "attenendosi all'ordine con cui sono stati dichiarati nella struct." << endl;
    }

    return 0;
}

void printDataDMY(data d, ostream &os /* = cout */)
{
    os << d.giorno + 0 << "/" << d.mese + 0 << "/" << d.anno + 2000 << " (" << d.sett << ")" << endl;
}
