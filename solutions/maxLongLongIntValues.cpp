/*
 * Determinare il massimo ed il minimo valore rappresentabili con il tipo di dati long long int.
 * Author:  ER
 * Date:    2022/10/28
 * Note:
 */

/*
## maxLongLongIntValues
Scrivere un programma (maxLongLongIntValues) che determini e visualizzi il massimo ed il minimo valore rappresentabili con il tipo di dati long long int.

Non sono ammesse soluzioni che partono dalla conoscenza di tali valori: i valori devono essere determinati in fase di esecuzione dall’algoritmo.

Si noti che sommando 1 al massimo valore (positivo) si ottiene il minimo valore (negativo).

Per verifica, ma non utilizzabili dall’algoritmo, i valori massimo e minimo sono 2<sup>63</sup>-1  e -2<sup>63</sup>.
*/

#include <cstdio>

#define DEBUG 1

long long int getMaxValue();                             // compute max value
void showSolution(long long int min, long long int max); // show problem and solution

int main(int argc, char *args[])
{
    {
        // elaborazione
        long long int max = getMaxValue();
        long long int min = max + 1; // overflow
        // Visualizzazione risultato
        showSolution(min, max);
    }

    // successful termination
    return 0;
}

/// @brief Restituisce il massimo valore
/// @return il massimo valore rappresentabile con un int
long long int getMaxValueSlow()
{
    // 1° metodo:
    // parto da 1 (almeno un valore positivo ci deve essere),
    // aumento di 1 fino ad arrivare all'overflow.
    // Troppo tempo: se per int bastava 1 secondo, qui ci vogliono 136 anni !!!!
    long long int result = 1;
    while (result > 0)
    {
        ++result;
    }
    return result - 1; // one step back
}

/// @brief Restituisce il massimo valore
/// @return il massimo valore rappresentabile con un int
long long int getMaxValue()
{
    // 2° metodo:
    // adotto uno step variabile per arrivare all'overflow:
    // parto da max = 0 (qualunque valore dovrebbe essere ok) e step = 1,
    // se max + step > max, aggiorno e raddoppio step (se possibile)
    // altrimento dimezzo step
    long long int max = 0, step = 1;
    while (step != 0)
    {
        long long int newMax = max + step;
        if (newMax > max)
        {
            max = newMax;
            long long int newStep = step + step;
            if (newStep > step)
            {
                step = newStep;
            }
        }
        else
        {
            step /= 2;
        }
        if (DEBUG)
            printf("max = %lld, step = %lld \n", max, step);
    }
    return max;
}

/// @brief Mostra i dati del problema e la soluzione
/// @param min il numero minimo
/// @param max il numero massimo
void showSolution(long long int min, long long int max)
{
    printf("Range is  [%lld, %lld] \n", min, max);
}
