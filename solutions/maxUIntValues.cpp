/*
 * Determinare il massimo ed il minimo valore rappresentabili con il tipo di dati unsigned int.
 * Author:  ER
 * Date:    2022/10/28
 * Note:
 */

/*
## maxUIntValues
Scrivere un programma (maxUIntValues) che determini e visualizzi il massimo ed il minimo valore rappresentabili con il tipo di dati unsigned int.

Non sono ammesse soluzioni che partono dalla conoscenza di tali valori: i valori devono essere determinati in fase di esecuzione dall’algoritmo.

Si noti che sommando 1 al massimo valore (positivo) si ottiene …
*/

#include <cstdio>

#define DEBUG 1

void showSolution(unsigned int min, unsigned int max); // show problem and solution

int main(int argc, char *args[])
{
    {
        // elaborazione
        unsigned int min = 0;
        unsigned int max = min - 1; // overflow
        // Visualizzazione risultato
        showSolution(min, max);
    }

    // successful termination
    return 0;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param min il numero minimo
/// @param max il numero massimo
void showSolution(unsigned int min, unsigned int max)
{
    printf("Range is  [%u, %u] \n", min, max);
}
