/**
* Esempio di operatori e funzioni
*/

#include <iostream>
#include <iomanip>

using namespace std;

/**
 * In matematica, un'operazione è una funzione
 *                   ==========       ========
 * che agisce su zero o più valori di input (chiamati operandi)
 *                          ===============           ========
 * e fornisce un valore di output.
 *               ================
 * Ad es. l'operazione di addizione nell'insieme degli interi
 * agisce su due operandi (gli addendi) e fornisce la loro somma.
 * L'addizione di 3 e 5 dà come risultato 8.
 * 
 * Il numero di operandi è detto arietà (adicità, tipo, rango) della funzione.
 * x-ary (Latin) 	(Greek)   Mathematics 	Computer Science
 * 0-ary Nullary    Niladic   constant      A function without arguments, True, False
 * 1-ary Unary      Monadic   opposite      Logical NOT operator, unary minus
 * 2-ary Binary     Dyadic    Addition      OR, XOR, AND
 * 3-ary Ternary    Triadic                 Conditional operator ?
 * ...
 * 
 * La maggior parte delle operazioni matematiche si rappresenta
 * usando dei simboli (chiamati operatori) opportunamente inseriti
 * tra gli operandi. Ad es.
 * Operazione   Tipo    Simbolo Esempio
 * negazione    unaria  -       -x  (simbolo prefisso all'operando)
 * fattoriale   unaria  !       n!  (simbolo postfisso all'operando)
 * addizione    binaria +       x + y   (simbolo infisso tra gli operandi)
 * sottrazione  binaria -       x - y   (simbolo infisso tra gli operandi)
 * 
 * Le operazioni possono tuttavia essere rappresentate come funzioni. Ad es.
 * Operazione   Tipo    Funzione    Esempio
 * negazione    unaria  opposto     opposto(x)       restituisce -x
 * fattoriale   unaria  fattoriale  fattoriale(n)    restituisce n!
 * addizione    binaria somma       somma(x, y)      restituisce x + y
 * sottrazione  binaria differenza  differenza(x, y) restituisce x - y
 * 
 * Il linguaggio C++ consente di definire il significato degli operatori
 * quando gli operandi non sono di tipo elementare già noto al compilatore.
 * Tipico esempio le struct da noi definite.
 * Tale possibilità è detta operator overloading.
 * 
 * Esempi di operatori che possono essere definiti per i tipi di dato:
 * unari:   -, !, =, ++, --
 * binari:  +, -, *, /, &, |, +=, -=, *=, /=, <<, >>
 * 
 * Per gli operatori binari, il caso senz'altro più frequente,
 * la sintassi per definire l'operazione da effettuarsi è:
 * <tipo risultato> operator <simbolo>(<tipo sinistro> lhs, <tipo destro> rhs) {
 *      // codice che effettua l'operazione e determina il risultato
 *      return <risultato>;
 * }
 * 
 * Questo equivale a definire una funzione del tipo:
 * <tipo risultato> <nome funzione>(<tipo sinistro> lhs, <tipo destro> rhs) {
 *      // codice che effettua l'operazione e determina il risultato
 *      return <risultato;
 * }
 * 
 * L'operator overloading andrebbe limitato ai casi in cui il tipo di dato
 * che stiamo utilizzando ha un significato naturale per le operazioni.
 * Ad es. per l'operatore + di addizione
 * struct frazione; (es. 3/4, -2/7, ...) ok! la somma di frazioni ha senso
 * struct studente; NO! la somma di due studenti NON ha senso!!
 * 
 * E' spesso definito l'operatore << con operando sinistro ostream.
 * Può essere utile a fornire una rappresentazione testuale, a video o su file,
 * del nostro tipo di dato.
 * 
 * Può essere utile definire gli operatori di confronto ma, a differenza
 * delle funzioni di confronto, essi sono meno flessibili:
 * una volta definito, non è possibile nella stessa applicazione
 * modificare la definizione.
 * 
 * Applicheremo quanto detto ad un esempio con tipo di dato:
 * struct planet
 * {
 *     char name[10 + 1]; // planet name (max 10 chars)
 *     double mass;       // mass in kg
 *     double distance;   // distance from Sun in km
 *     bool inhabited;    // inhabited (usually false)
 *     int numSatellites; // number of satellites
 * };
 * per il quale definiremo:
 * - l'operatore << per effettuare l'output
 * - l'operatore < per confrontare i pianeti in base alla distanza
 * - la funzione lessThan con significato analogo all'operatore <
 * - la funzione lessThanByMass per confrontare i pianeti in base alla massa
 * 
 * Utilizzeremo tali operatori / funzioni per l'ordinamento,
 * con le funzioni sort e sortBy.
 * Quest'ultima serve a dimostrare la flessibilità delle funzioni:
 * le funzioni sono più flessibili perchè è possibile passarle come parametro
 * ad altre funzioni, come in questo esempio: la funzione sortBy riceve
 * come parametro una funzione di confronto che utilizza per l'ordinamento:
 * - passando la funzione lessThan l'ordinamento sarà per distanza,
 * - passando la funzione lessThanByMass l'ordinamento sarà per massa.
 */

// il nuovo tipo di dato
struct planet
{
    char name[10 + 1]; // planet name (max 10 chars)
    double mass;       // mass in kg
    double distance;   // distance from Sun in km
    bool inhabited;    // inhabited (usually false)
    int numSatellites; // number of satellites
};

// overload dell'operatore << per output
ostream &operator<<(ostream &os, const planet &p)
{
    os << p.name << "{";
    os << "mass = " << p.mass << " kg";
    os << ", distance = " << p.distance << " km";
    os << ", " << (p.inhabited ? "" : "not ") << "inhabited";
    os << ", " << p.numSatellites << " satellite(s)";
    os << "}";
    // l'operatore restituisce l'ostream per permettere
    // l'uso concatenato di altri operatori <<
    // ad es. cout << p1 << " & " << p2 << endl;
    return os;
}

// overload dell'operatore < per confronto basato sulla distanza
bool operator<(const planet &lhs, const planet &rhs)
{
    return lhs.distance < rhs.distance;
}

// funzione analoga all'operatore < per confronto basato sulla distanza
bool lessThan(const planet &lhs, const planet &rhs)
{
    return lhs.distance < rhs.distance;
}

// funzione per confronto basato sulla massa
bool lessThanByMass(const planet &lhs, const planet &rhs)
{
    return lhs.mass < rhs.mass;
}

using type = planet;

void sort(type a[], int end, int begin = 0); // ordina in modo che a[i] >= a[j] per i >= j

// definizione del tipo di funzione di confronto:
// <tipo restituito> (<lista parametri>)
using comparisonFunction = bool(const planet &, const planet &);

void sortBy(type a[], int end, int begin = 0, comparisonFunction less = lessThan); // ordina in modo che less(a[i], a[j]) false per i >= j

int main()
{
    // dichiarazione array pianeti
    planet planets[] = {
        {"Mars", 6.4171E23, 206700000, false, 2},
        {"Jupiter", 1.8982E27, 740520000, false, 79},
        {"Mercury", 3.3011E23, 46001200, false, 0},
        {"Venus", 4.8675E24, 107477000, false, 0},
        {"Earth", 5.9726E24, 147098074, true, 1},
        {"Saturn", 5.6834E26, 1352550000, false, INT32_MAX},
        {"Uranus", 8.6810E25, 2.742E9, false, 27},
        {"Neptune", 1.02413E26, 4.5E9, false, 14}};
    const int numPlanets = sizeof(planets) / sizeof(planet);

    cout << "The planets:" << endl;
    for (int p = 0; p < numPlanets; p++)
    {
        cout << planets[p] << endl;
    }
    cout << endl;

    sort(planets, numPlanets);

    cout << "The planets sorted by operator < :" << endl;
    for (int p = 0; p < numPlanets; p++)
    {
        cout << planets[p] << endl;
    }
    cout << endl;

    sortBy(planets, numPlanets, 0, lessThanByMass);

    cout << "The planets sorted by lessThanByMass :" << endl;
    for (int p = 0; p < numPlanets; p++)
    {
        cout << planets[p] << endl;
    }
    cout << endl;

    sortBy(planets, numPlanets);

    cout << "The planets sorted by lessThan :" << endl;
    for (int p = 0; p < numPlanets; p++)
    {
        cout << planets[p] << endl;
    }
    cout << endl;

    // successful termination
    return 0;
}

// full sorting, iterative + optimization on end
// remembering last swap: the rest is ordered
void sort(type a[], int end, int begin /* = 0 */)
{
    // end - begin > 1 : at least two elements
    while (end - begin > 1)
    {
        int lastSwapped = 0;
        for (int i = begin + 1; i < end; ++i)
        {
            if (a[i] < a[i - 1])
            {
                // something's wrong here: let's fix it
                swap(a[i], a[i - 1]);
                lastSwapped = i;
            }
        }
        // here last position is maximum element,
        // but the others might still be out of order !!!
        // Let's sort the rest if needed
        // end = end - 1;
        end = lastSwapped;
    }
}

// full sorting, iterative + optimization on end
// remembering last swap: the rest is ordered
void sortBy(type a[], int end, int begin /* = 0 */, comparisonFunction less /* = lessThan */)
{
    // end - begin > 1 : at least two elements
    while (end - begin > 1)
    {
        int lastSwapped = 0;
        for (int i = begin + 1; i < end; ++i)
        {
            if (less(a[i], a[i - 1]))
            {
                // something's wrong here: let's fix it
                swap(a[i], a[i - 1]);
                lastSwapped = i;
            }
        }
        // here last position is maximum element,
        // but the others might still be out of order !!!
        // Let's sort the rest if needed
        // end = end - 1;
        end = lastSwapped;
    }
}