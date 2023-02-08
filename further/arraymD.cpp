/**
 * Purpose: Multidimensional arrays
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2019/12/12
 * Note:
*/

#include <iostream>
#include <cstdlib>

using namespace std;

#define DEBUG 1

/// main function
int main(int argc, char *argv[]) {
    int numStudenti = 10, numMaterie = 7, numTrimestre = 3;
    // i voti, per ciascuno studente, materia, periodo:
    // un indice per ciascun soggetto/entità cui i dati si riferiscono
    // con un ordine che rispecchia quello logico, se possibile
    // e che va mantenuto in tutto il codice successivo.
    // Questa privilegia il punto di vista del docente di una data materia
    int voti[numMaterie][numStudenti][numTrimestre];
    // alternativa:
    // questa privilegia il punto di vista del singolo studente
    // int voti[numStudenti][numMaterie][numTrimestre];
    // alternativa:
    // questa privilegia il punto di vista della pagella ...
    // int voti[numTrimestre][numStudenti][numMaterie];
    cout << sizeof(voti) << endl;
    // elaborazione dei voti (assegnazione casuale)
    // l'ordine di elaborazione pu� variare a seconda delle esigenze
    // in questo caso, studente, materia, periodo
    for(int s = 0; s < numStudenti; s++) {
        for(int m = 0; m < numMaterie; m++) {
            for(int t = 0; t < numTrimestre; t++) {
                voti[m][s][t] = 2 + rand() % 9;
                cout << "Studente " << s << ", materia " << m \
                     << ", trimestre " << t << ": voto " \
                     << voti[m][s][t] << endl;
            }
        }
    }
    // POSSO SCAMBIARE L'ORDINE DEI CICLI FOR A SECONDA DI CIO' CHE MI INTERESSA
    // media nell'ultimo trimestre per ciascuno studente
    for(int s = 0; s < numStudenti; s++) {
        double sommaVoti = 0;
        for(int m = 0; m < numMaterie; m++) {
            sommaVoti += voti[m][s][numTrimestre - 1];
            // sommaVoti += voti[s][m][numTrimestre - 1]; NON SCAMBIARE L'ORDINE LOGICO DEGLI INDICI !!!
        }
        cout << "Studente " << s << ": media " << sommaVoti / numMaterie << endl;
    }
    // POSSO SCAMBIARE L'ORDINE DEI CICLI FOR A SECONDA DI CIO' CHE MI INTERESSA
    // media nell'ultimo trimestre per ciascuna materia
    for(int m = 0; m < numMaterie; m++) {
        double sommaVoti = 0;
        for(int s = 0; s < numStudenti; s++) {
            sommaVoti += voti[m][s][numTrimestre - 1];
            // sommaVoti += voti[s][m][numTrimestre - 1]; NON SCAMBIARE L'ORDINE LOGICO DEGLI INDICI !!!
        }
        cout << "Materia " << m << ": media " << sommaVoti / numStudenti << endl;
    }
    // verifica indirizzi di allocazione
    // con il ciclo for più esterno per il primo indice (variazione più lenta)
    // ed il ciclo for più interno per l'ultimo indice (variazione più rapida)
    // l'elaborazione avviene con contiguità degli indirizzi !!!
    for(int m = 0; m < numMaterie; m++) {
        for(int s = 0; s < numStudenti; s++) {
            for(int t = 0; t < numTrimestre; t++) {
                voti[m][s][t] = 2 + rand() % 9;
                cout << "Materia " << m \
                     << ", studente " << s \
                     << ", trimestre " << t << ": voto " \
                     << & voti[m][s][t]<< endl;
            }
        }
    }
    /// successful termination
    return 0;
}
