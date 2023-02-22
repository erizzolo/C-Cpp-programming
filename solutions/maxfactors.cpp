/*
 * Massimo numero di fattori primi
 * Author:  ER
 * Date:    2022/02/16
 * Note:
 */

/*
## Scomposizione con massimo numero di fattori (maxFactors)
Si tratta di determinare, per un dato tipo numerico intero, qual è il massimo numero di coppie (fattore primo, esponente) che si ottiene dalla scomposizione di un numero naturale positivo esprimibile con il tipo considerato.

Ad esempio, se il tipo considerato avesse 1000 come valore massimo (ottenibile con numeric_limits<tipo>::max()), la scomposizione di un numero non potrebbe avere più di 4 fattori primi: infatti 2 x 3 x 5 x 7 = 210 e se vi fosse un altro fattore primo (o altri fattori primi necessariamente maggiori) il numero in questione non sarebbe esprimibile con il tipo dato.

Si crei quindi una funzione che verifica quanti numeri primi si possono moltiplicare prima di superare il limite del tipo numerico scelto con il seguente prototipo (il tipo restituito int è indipendente dal tipo numerico scelto):

``int maxPrimeFactors();``

La funzione deve:
* inizializzare una variabile prodotto (del tipo numerico scelto) al valore 1;
* generare ripetutamente i numeri primi in ordine crescente e moltiplicare prodotto per i primi trovati, terminando non appena il prodotto supererebbe il valore massimo del tipo numerico scelto (per evitare overflow, verificare con numeric_limits<tipo>::max() / prodotto > fattore_primo);
* restituire il numero di primi moltiplicati.

Verificare il risultato per diversi tipi numerici.
*/

#include <iostream>
#include <limits>

using namespace std;

const bool DEBUG = true;

using number = unsigned long long int;

int maxPrimeFactors();

int main(int argc, char *argv[])
{
    number min = numeric_limits<number>::min();
    number max = numeric_limits<number>::max();

    cout << "For type with min = " << min << " and max = " << max << ":" << endl;
    cout << "Maximum number of prime factors = " << maxPrimeFactors() << endl;

    return 0;
}

number sqrt(number n)
{
    number result = 0, step = 1LL << (sizeof(number) * 4 - 1);
    while (step > 0)
    {
        number test = result + step;
        if (test * test <= n)
        {
            result = test;
        }
        step /= 2;
    }
    return result;
}

/// @brief Restituisce true se number è primo, false altrimenti (fast version)
/// @param n il numero di cui si verifica la primalità
/// @return true se n è primo, false altrimenti
bool isPrimeFast(number n)
{
    bool prime = n > 1; // no 0 e 1
    if (prime)
    {
        number factor = 2, limit = sqrt(n);
        while (factor <= limit && prime)
        {
            prime = n % factor != 0;
            ++factor;
        }
    }
    return prime;
}

int maxPrimeFactors()
{
    int result = 0;
    number product = 1;
    number prime = 2;
    number max = numeric_limits<number>::max();
    while (prime <= max / product)
    {
        product *= prime;
        ++result;
        if (DEBUG)
        {
            cout << "product * " << prime << " = " << product << endl;
        }
        do
        {
            prime++;
        } while (!isPrimeFast(prime));
    }
    return result;
}
