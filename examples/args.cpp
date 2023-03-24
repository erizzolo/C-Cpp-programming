/**
 * Programma di esempio
 * Author:  ER
 * Date:    2023/03/22
 * Note:    Il programma visualizza i parametri della riga comando
 *			Provare con: args 89ab 67, "42.78 ciccia" 7.4
 *          Per eseguire da riga comando può essere necessario
 *          compilare con l'opzione -static
 */

#include <iostream>

using namespace std;

// argc: numero di elementi di argv (>= 1)
// argv: array di argc elementi significativi (char * ovvero stringhe)
int main(int argc, char *argv[])
{
    cout << "argc = " << argc << endl;
    for (int a = 0; a < argc; a++)
    {
        cout << "argv[" << a << "]: '" << argv[a] << "' @" << (void *)argv[a] << endl;
    }

    // termine con codice 0 = successo
    return 0;
}
