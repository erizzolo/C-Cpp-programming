/*
    Purpose:    dati un punto ed una retta parallela ad uno degli assi
                (definita da due punti) trovare il punto simmetrico
                di quello dato rispetto alla retta data
    Author:     Emanuele Rizzolo
    Date:       2022/10/20
    Note:
*/

/*
    Simmetria (simmetria)
    Descrizione del problema
    Dati una retta R e un punto A nel piano cartesiano, si definisce il punto B simmetrico ad A rispetto a R
    come l'altro estremo del segmento AB perpendicolare a R, tale che la distanza di A rispetto a R è uguale a quella di B rispetto a R.
    In altre parole, AB è diviso in due parti uguali dall'intersezione con R e, quindi, A è speculare a B rispetto a R.
    Si noti che, qualora il punto A appartenga alla retta R, il punto B coincide con il punto A.
    Scrivere un programma che, presa una retta R parallela a uno degli assi cartesiani e un punto A nel piano cartesiano,
    calcola le coordinate del punto B simmetrico ad A rispetto a R.
    Assunzione: coordinate dei punti -1000000 ≤ x,y ≤ 1000000.
    Formato di input: leggere da tastiera (senza controlli di validità) quattro interi xL1, yL1, xL2 e yL2,
    separati da uno spazio, che rappresentano le coordinate di due punti L1 e L2 appartenenti alla retta R;
    leggere poi due interi xA e yA separati da uno spazio, che rappresentano le coordinate del punto A.
    Formato di output: due interi xB e yB separati da uno spazio, che rappresentano le coordinate del punto B
    simmetrico ad A rispetto a R, in forma decimale.
    Esempi:
    Input       Output
    0 0 0 1     -10 10
    10 10

    0 0 1 0     10 -10
    10 10
    Autore/i
    A.S. Stankevich, ACM ICPC Team, St. Petersburg State University of Information Technology, Mechanics and Optics
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    // le quattro coordinate xL1, yL1, xL2 e yL2
    int xL1, yL1, xL2, yL2;
    printf("Immetti le quattro coordinate xL1, yL1, xL2 e yL2, separate da spazi, dei due punti L1 e L2 appartenenti alla retta R (-1000000 <= x,y <= 1000000): ");
    scanf("%d %d %d %d", &xL1, &yL1, &xL2, &yL2);

    // le coordinate xA e yA del punto A
    int xA, yA;
    printf("Immetti le coordinate xA e yA, separate da spazi, del punto A (-1000000 <= x,y <= 1000000): ");
    scanf("%d %d", &xA, &yA);

    // check that L1 and L2 define a parallel to one of the axes
    if ((xL1 == xL2) == (yL1 == yL2))
    {
        printf("Houston! We have a problem... \n");
    }
    else
    {
        // le coordinate xB e yB del punto B, simmetrico di A rispetto ad R
        int xB, yB;
        // strategia risolutiva
        // il punto medio del segmento AB appartiene alla retta
        if (yL1 == yL2) // retta R è parallela all'asse x
        {
            xB = xA;
            // yM = yL1 = yL2 = (yA + yB) / 2
            yB = 2 * yL1 - yA;
        }
        else
        {
            // xM = xL1 = xL2 = (xA + xB) / 2
            xB = 2 * xL1 - xA;
            yB = yA;
        }
        // output coordinate
        printf("%d %d\n", xB, yB);
    }

    // successful termination
    return 0;
}
