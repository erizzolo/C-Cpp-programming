/*
    Purpose:    contare il numero di punti di coordinate intere nella zona
                "differenza" di due rettangoli.
    Author:     Emanuele Rizzolo
    Date:       2022/10/20
    Note:
*/

/*
    Conteggio di punti e rettangoli (conta)
    Descrizione del problema
    è dato un rettangolo con un vertice nell'origine del piano cartesiano e il vertice opposto situato nel punto (W,H).
    è dato un secondo rettangolo, situato completamente all'interno del precedente, i cui vertici hanno coordinate costituite da numeri interi.
    Definiamo w e h la larghezza e l'altezza di questo secondo rettangolo.
    Si chiede di calcolare il numero di punti aventi coordinate costituite da numeri interi che siano situati
    completamente all'interno del primo rettangolo e all'esterno del secondo (escludendo cio� i punti situati sui lati).
    Assunzione: 3<=W,H<=10^9,1<=w<=W-2, 1<=h<=H-2.
    Formato di input: leggere da tastiera (senza controlli di validità) quattro interi W, H, w e h.
    Formato di output: un intero, che rappresenta il numero di punti richiesto, in forma decimale.
    Esempi:
    Input       Output
    3 3 1 1     0
    4 3 1 1     2
    Autore/i
    A.S. Stankevich, ACM ICPC Team, St. Petersburg State University of Information Technology, Mechanics and Optics
*/

#include <stdio.h>

int main(int argc, char *argv[])
{

    printf("Immetti W, H, w e h, separati da spazi (3<=W,H<=10^9,1<=w<=W-2,1<=h<=H-2): ");
    // per comodità uso direttamente long long, anche se serve solo per il numero di punti
    long long int W, H, w, h; // W, H, w e h
    scanf("%lld %lld %lld %lld", &W, &H, &w, &h);
    // number of points
    long long int numPoints;
    // strategia risolutiva
    // punti interni al rettangolo esterno: (x,y) con 0 < x < W e 0 < y < H
    numPoints = (W - 1) * (H - 1);
    // sottraggo punti del rettangolo interno: (x,y) con x0 <= x <= x0+w e y0 <= y <= y0+h
    numPoints -= (w + 1) * (h + 1);
    // output risultato
    printf("%lld\n", numPoints);
    // successful termination
    return 0;
}
