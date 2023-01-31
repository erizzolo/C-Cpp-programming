/*
    Purpose:    conteggio divisori con criterio
    Author:     Emanuele Rizzolo
    Class:      3CIN
    Date:       2016/12/
    Note:
*/
/*
    Differenza e prodotto (diffprod)
    Descrizione del problema
    Dati due numeri interi D e P, quante coppie (ordinate) di interi esistono tali che
    il valore assoluto della differenza sia pari a D ed il prodotto sia pari a P?
    Ovvero, quante coppie (a,b) di interi esistono tali che |a-b|=D e a*b=P?
    Assunzione: |D|<=10^9 e |P|<=10^9.
    Formato di input: leggere D e P da tastiera, (senza controlli di validità).
    Formato di output: il risultato richiesto, cioè il numero di coppie (a,b) di interi tali che |a-b|=D e a*b=P.
    Esempi:
    Input   Output     Spiegazione
    1 2     4           Le coppie sono (1,2),(2,1),(-1,-2),(-2,-1)
    0 4     2           Le coppie sono (2,2),(-2,-2)
    -1 1    0           Il modulo della differenza non può essere negativo.
    Limiti: tempo 1s, memoria 1KB.

    Some theory ...
    D<0	: 	impossible
    D=0	: 	a=b, P=a^2
            P=0	: 	(0,0) 1 solution
            P<0	: 	impossible (P should be a negative square)
            P>0	: 	if a=sqrt(P) integer 2 solutions (a,a) and (-a,-a) else impossible (2 real solutions)
                    e.g. P=4:(2,2), (-2,-2); P=5: impossible ( (+-sqrt(5),+-sqrt(5)) )
    D>0	: 	P=0	: 	4 solutions (0,D), (D,0), (0,-D), (-D,0)
                    e.g. D=10,P=0:(0,10), (10,0), (0,-10), (-10,0)
            P<0 : 	then D=|a|+|b|
                    let M=|a|, m=|b|=D-|a|=D-M : M*m=-P=M*(D-M) and M^2-D*M-P=0
                    let delta=D*D+4*P
                    delta<0	: no solutions
                    delta=0 : 2 solutions (D/2,-D/2), (-D/2,D/2)
                    delta>0 : if delta=d^2 with d integer then M1,M2=(D+-d)/2 are integers (M1>0,M2>0):
                                4 solutions (M1,-M2), (-M1,M2), (M2,-M1), (-M2,M1)
                              else impossible
                    e.g. D=3,P=-10: delta=9-40<0: impossible
                         D=8,P=-16: delta=64-64=0: (4,-4), (-4,4)
                         D=9,P=-10: delta=81-40=41>0 but not a perfect square: impossible
                         D=7,P=-10: delta=49-40=9>0 and a perfect square 9=3^2: M1,M2=(7+-3)/2=5,2:
                                    4 solutions (5,-2), (-5,2), (2,-5), (-2,5)
                         D=10,P=-9: delta=100-36=64>0 and a perfect square 64=8^2: M1,M2=(10+-8)/2=9,1:
                                    4 solutions (9,-1), (-9,1), (1,-9), (-1,9)
            P>0 : 	then D=|a|+|b|
                    let M=max(|a|,|b|), m=min(|a|,|b|)=M-D : M*m=P=M*(M-D) and M^2-D*M-P=0
                    let delta=D*D+4*P>0
                    delta>0 : if delta=d^2 with d integer then M1,M2=(D+-d)/2 are integers (M1>0,M2<0):
                                4 solutions (M1,-M2), (-M1,M2), (M2,-M1), (-M2,M1)
                              else impossible
                    e.g. D=5,P=10: delta=25+40=65>0 but not a perfect square: impossible
                         D=3,P=10: delta=9+40=49>0 and a perfect square 49=7^2: M1,M2=(3+-7)/2=5,-2:
                                   4 solutions (5,2), (-5,-2), (-2,-5), (2,5)
                         D=6,P=16: delta=34+64=100>0 and a perfect square 100=10^2: M1,M2=(6+-10)/2=8,-2:
                                   4 solutions (8,2), (-8,-2), (-2,-8), (2,8)

*/

// directive for standard io functions
#include <iostream>

using namespace std;

#define DEBUG 0

// returns integer square root of n
long long int isqrt(const long long int n);

// funzione principale
int main(int argc, char *argv[])
{
    // prompt utente
    long long int D, P;
    cerr << "Immetti D e P (|D|<=10^9 e |P|<=10^9):";
    cin >> D >> P;
    // number of solutions
    int nSolutions = 0; // dealt with impossible cases
    // check the different cases
    if (D == 0)
    {
        //	D=0	: 	a=b, P=a^2
        if (P == 0)
        {
            // 	P=0	: 	(0,0) 1 solution
            nSolutions = 1;
        }
        else if (P > 0)
        {
            //	P>0	: 	if a=sqrt(P) integer 2 solutions (a,a) and (-a,-a) else impossible (2 real solutions)
            long long int a = isqrt(P);
            if (a * a == P)
            {
                nSolutions = 2;
            }
        }
    }
    else if (D > 0)
    {
        if (P == 0)
        {
            //	D>0	: 	P=0	: 	4 solutions (0,D), (D,0), (0,-D), (-D,0)
            nSolutions = 4;
        }
        else if (P < 0)
        {
            //	P<0 : 	then D=|a|+|b|
            //			let M=|a|, m=|b|=D-|a|=D-M : M*m=-P=M*(D-M) and M^2-D*M-P=0
            //			let delta=D*D+4*P
            unsigned long long int delta = D * D + 4 * P;
            if (delta == 0)
            {
                //	delta=0 : 2 solutions (D/2,-D/2), (-D/2,D/2)
                nSolutions = 2;
            }
            else if (delta > 0)
            {
                //	delta>0 : if delta=d^2 with d integer then M1,M2=(D+-d)/2 are integers (M1>0,M2>0):
                //				4 solutions (M1,-M2), (-M1,M2), (M2,-M1), (-M2,M1)
                long long int d = isqrt(delta);
                if (d * d == delta)
                {
                    nSolutions = 4;
                }
            }
        }
        else if (P > 0)
        {
            //	P>0 : 	then D=|a|+|b|
            //			let M=max(|a|,|b|), m=min(|a|,|b|)=M-D : M*m=P=M*(M-D) and M^2-D*M-P=0
            //			let delta=D*D+4*P>0
            unsigned long long int delta = D * D + 4 * P;
            //	delta>0 : if delta=d^2 with d integer then M1,M2=(D+-d)/2 are integers (M1>0,M2<0):
            //				4 solutions (M1,-M2), (-M1,M2), (M2,-M1), (-M2,M1)
            long long int d = isqrt(delta);
            if (d * d == delta)
            {
                nSolutions = 4;
            }
        }
    }
    // output result
    cout << nSolutions << endl;
    {
        // brute force solution
        int solutions = 0;
        // find divisors (and their quotients) of |P| and check their difference
        // all integers divide 0 :-(
        if (P == 0)
        {
            if (D == 0)
            {
                solutions = 1; // only (0,0) 1 solution
            }
            else if (D > 0)
            {
                solutions = 4; // 4 solutions (0,D), (D,0), (0,-D), (-D,0)
            }
        }
        else
        {
            long long int absP = P >= 0 ? P : -P;
            for (int divisor = 1, limit = isqrt(absP); divisor <= limit; divisor++)
            {
                if ((absP % divisor) == 0)
                {
                    // find the quotient (here quotient>=divisor>0)
                    int quotient = absP / divisor;
                    if (DEBUG)
                        cout << "Found divisor " << divisor << " with quotient " << quotient << endl;
                    // check the absolute difference
                    if (P < 0)
                    {
                        // change one sign
                        if (divisor + quotient == D)
                        {
                            if (DEBUG)
                                cout << "Found (" << divisor << "," << -quotient << ")" << endl;
                            // bingo!!!
                            if (divisor == quotient)
                            {
                                // (d,-d), (-d,d)
                                solutions = 2;
                            }
                            else
                            {
                                // (d,-q), (-d,q), (q,-d), (-q,d)
                                solutions = 4;
                            }
                        }
                    }
                    else
                    {
                        // same sign
                        if (quotient - divisor == D)
                        {
                            if (DEBUG)
                                cout << "Found (" << divisor << "," << quotient << ")" << endl;
                            // bingo!!!
                            if (divisor == quotient)
                            {
                                // (d,d), (-d,-d)
                                solutions = 2;
                            }
                            else
                            {
                                // (d,q), (-d,-q), (q,d), (-q,-d)
                                solutions = 4;
                            }
                        }
                    }
                }
            }
        }
        if (solutions != nSolutions)
        {
            cout << "You stupid!!!" << endl;
        }
    }
    // successful termination
    return 0;
}

// returns integer square root of n
long long int isqrt(const long long int n)
{
    // square root and maximum bit weigth
    long long int root = 0, bit = 1LL << 31;
    // while more bits
    while (bit > 0)
    {
        // try to set bit: i.e. try the middle of remaining interval
        root |= bit;
        // check if too big...
        if (root * root > n)
        {
            root ^= bit; // reset it: i.e. exclude the wrong half
        }
        // next bit
        bit >>= 1;
    }
    return root;
}
