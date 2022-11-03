/*
 * Determinare il massimo ed il minimo valore rappresentabili con il tipo di dati int.
 * Author:  ER
 * Date:    2022/10/28
 * Note:
 */

/*
## maxIntValues
Scrivere un programma (maxIntValues) che determini e visualizzi il massimo ed il minimo valore rappresentabili con il tipo di dati int.

Non sono ammesse soluzioni che partono dalla conoscenza di tali valori: i valori devono essere determinati in fase di esecuzione dall’algoritmo.

Si noti che sommando 1 al massimo valore (positivo) si ottiene il minimo valore (negativo).

Per verifica, ma non utilizzabili dall’algoritmo, i valori massimo e minimo sono 2147483647 e -2147483648; sommando 1 a  2147483647 si ha overflow ed il risultato vale -2147483648.
*/

#include <cstdio>

#define DEBUG 1

int getMaxValue();                   // compute max value
void showSolution(int min, int max); // show problem and solution

int main(int argc, char *args[])
{
    {
        // elaborazione
        int max = getMaxValue();
        int min = max + 1; // overflow
        // Visualizzazione risultato
        showSolution(min, max);
    }

    // successful termination
    return 0;
}

/// @brief Restituisce il massimo valore
/// @return il massimo valore rappresentabile con un int
int getMaxValue()
{
    // 1° metodo:
    // parto da 1 (almeno un valore positivo ci deve essere),
    // aumento di 1 fino ad arrivare all'overflow.
    int result = 1;
    while (result > 0)
    {
        ++result;
    }
    return result - 1; // one step back
}

/// @brief Mostra i dati del problema e la soluzione
/// @param min il numero minimo
/// @param max il numero massimo
void showSolution(int min, int max)
{
    printf("Range is  [%d, %d] \n", min, max);
}
