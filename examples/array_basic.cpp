/**
 * Purpose: basic algorithms for arrays
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2022/11/23
 * Note:
 */

#include <iostream>
using namespace std;

/**
 * Come già detto, gli array si elaborano elemento per elemento.
 * Vi sono degli schemi di base che si raccomandano per i compiti più tipici.
 * In questo esempio si mostrano alcuni di tali schemi.
 * La base di tutto sono le scansioni degli elementi (o di parte di essi),
 * che possono avvenire in ordine di indice crescente o decrescente.
 * Durante la scansione, si accede al singolo elemento e lo si elabora
 * secondo le necessità.
 * La scansione può eventualmente essere interrotta se si raggiunge l'obiettivo.
 * Le varianti sono ovviamente infinite.
 * Gli esempi qui illustrati valgono per array di dati di tipo generico type.
 * E' possibile sostituire a type qualunque tipo fisico (compatibile con le
 * operazioni effettuate) modificando l'istruzione using seguente.
 */

// modificabile per usare altri tipi di dato (compatibili con i valori usati!!!)
// definisco type come "sinonimo" di double
using type = double;

// basic scan prototypes
void forwardScanAll(type a[], int end);  // scansione crescente da 0 a end escluso: [0, end)
void backwardScanAll(type a[], int end); // scansione decrescente da end escluso a 0: [0, end)
// basic scan prototypes with default parameter begin
void forwardScan(type a[], int end, int begin = 0);  // scansione crescente da begin a end escluso: [begin, end)
void backwardScan(type a[], int end, int begin = 0); // scansione decrescente da end escluso a begin: [begin, end)
// applicazione delle precedenti scansioni per la visualizzazione di un array
void JSON(const type a[], int end, int begin = 0, ostream &out = cout); // output su out in formato JSON

#define DEBUG 1

// main function
int main(int argc, char *argv[])
{
    // error: narrowing conversion of '375' from 'int' to 'type' {aka 'char'} inside { } [-Wnarrowing]|
    // type v[]{1, 5, 9, 2, 375};
    type v[]{1, 5, 9, 2, 75};
    constexpr int dim = sizeof(v) / sizeof(v[0]);

    cout << "Forward scan of all elements" << endl;
    forwardScanAll(v, dim);
    cout << "backward scan of all elements" << endl;
    backwardScanAll(v, dim);

    cout << "Forward scan of first three elements" << endl;
    forwardScanAll(v, 3);
    cout << "backward scan of first three elements" << endl;
    backwardScanAll(v, 3);

    cout << "Forward scan of all elements but the first 2" << endl;
    forwardScan(v, dim, 2);
    cout << "backward scan of all elements but the first 2" << endl;
    backwardScan(v, dim, 2);

    cout << "Forward scan of all elements" << endl;
    forwardScan(v, dim);
    cout << "backward scan of all elements" << endl;
    backwardScan(v, dim);

    cout << "Output in JSON format of all elements" << endl;
    JSON(v, dim);
    cout << endl;
    cout << "Output in JSON format of all elements but the first 2" << endl;
    JSON(v, dim, 2);
    cout << endl;
    cout << "Output in JSON format of all elements in [2,2)" << endl;
    JSON(v, 2, 2, cerr);
    // successful termination
    return 0;
}
/**
 * Basic forward scan
 * scansione crescente da 0 a end escluso: [0, end)
 * @param a     the array to scan
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 */
void forwardScanAll(type a[], int end)
{
    for (int i = 0; i < end; ++i)
    {
        // process a[i]
        cout << "processing a[" << i << "]" << endl;
    }
}
/**
 * Basic backward scan (with default limits)
 * scansione decrescente da end escluso a 0: [0, end)
 * @param a     the array to scan
 * @param end   inizio (escluso) della scansione: a[end] non viene elaborato
 */
void backwardScanAll(type a[], int end)
{
    for (int i = end; i-- > 0;)
    {
        // process a[i]
        cout << "processing a[" << i << "]" << endl;
    }
}

/**
 * Basic forward scan (with default limits)
 * scansione crescente da begin a end escluso: [begin, end)
 * @param a     the array to scan
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 */
void forwardScan(type a[], int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        // process a[i]
        cout << "processing a[" << i << "]" << endl;
    }
}
/**
 * Basic backward scan (with default limits)
 * scansione decrescente da end escluso a begin: [begin, end)
 * @param a     the array to scan
 * @param end   inizio (escluso) della scansione: a[end] non viene elaborato
 * @param begin fine (inclusa) della scansione: a[begin] e' l'ultimo elemento elaborato
 */
void backwardScan(type a[], int end, int begin /* = 0 */)
{
    for (int i = end; i-- > begin;)
    {
        // process a[i]
        cout << "processing a[" << i << "]" << endl;
    }
}
/**
 * Output su out in formato JSON da begin a end escluso: [begin, end)
 * @param a     the array to output
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @param out   the output stream to be used
 */
void JSON(const type a[], int end, int begin /* = 0 */, ostream &out /* = cout */)
{
    out << "[ ";
    for (int i = begin; i < end; ++i)
    {
        if (i != begin)
            out << ", ";
        out << a[i];
    }
    out << " ]";
}
