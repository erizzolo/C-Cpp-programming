/**
 * Esempio di passaggio parametri a una funzione
 *
 * Il C++ consente il passaggio di parametri in 3 modi diversi:
 * 1.   per valore        (<tipo> <nome>)
 * 2.   per riferimento   (<tipo> &<nome>)
 * 3.   per indirizzo     (<tipo> *<nome>)
 * A parte la sintassi, 2 e 3 praticamente si equivalgono.
 * 1.   Viene fornita alla funzione una copia del dato
 *      (variabile o espressione) specificato come argomento nella chiamata.
 * 2.   Viene fornita alla funzione un alias (nome alternativo) del dato
 *      (variabile) specificato come argomento nella chiamata.
 * 3.   Viene fornita alla funzione l'indirizzo di memoria del dato
 *      (variabile) specificato come argomento nella chiamata.
 * Ciò significa, in pratica, che:
 * 1.   la funzione agisce su una copia del dato e le eventuali modifiche
 *      non si riflettono all'esterno della funzione.
 * 2.   la funzione agisce sul dato originale e le eventuali modifiche
 *      si riflettono all'esterno della funzione.
 * 3.   la funzione agisce sull'area di memoria contenente il dato originale
 *      e le eventuali modifiche si riflettono all'esterno della funzione.
 * Nel caso in cui il passaggio del parametro avvenga nei modi 2 o 3 e
 * non si desideri che la funzione possa modificare il dato originale,
 * è sufficiente premettere la keyword const alla definizione del parametro:
 * In questo modo, il compilatore controlla che il dato non sia modificato
 * nel codice della funzione.
 *
 * Quale metodo scegliere?
 * F.15: Prefer simple and conventional ways of passing information
 * https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-conventional
 */

// directive for standard io functions
#include <cstdio>

// function prototype
void f(int parmByValue, int &parmByReference, int *parmByAddress);

// funzione principale
int main(int argc, char *argv[])
{
    // local variables used as arguments to the function
    int intByValue = 0, intByReference = 1, intByAddress = 2;
    // visualizza, per ciascuna variable:
    // il nome (usato per riferirsi alla variabile)
    // l'indirizzo di memoria in cui il dato e' memorizzato (in hex) ottenuto con &nome ( cioe' <indirizzo di> nome)
    // l'indirizzo di memoria in cui il dato e' memorizzato (in decimale) ottenuto con &nome ( cioe' <indirizzo di> nome)
    // la dimensione (in bytes) dell'area di memoria riservata alla variabile ottenuta con sizeof(nome)
    // il valore della variabile
    printf("LOCAL VARIABLES, in main function before call\n");
    printf("name             | 0xaddress           | address             |size |value(s)\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("intByValue       |%20p |%20llu |%4lu |%5d\n", &intByValue, (long long int)&intByValue, sizeof(intByValue), intByValue);
    printf("intByReference   |%20p |%20llu |%4lu |%5d\n", &intByReference, (long long int)&intByReference, sizeof(intByReference), intByReference);
    printf("intByAddress     |%20p |%20llu |%4lu |%5d\n", &intByAddress, (long long int)&intByAddress, sizeof(intByAddress), intByAddress);
    printf("\nCalling function f(intByValue,intByReference,&intByAddress):\n");
    f(intByValue, intByReference, &intByAddress);
    // visualizza, per ciascuna variable ... come prima
    printf("\nLOCAL VARIABLES, in main function after call\n");
    printf("name             | 0xaddress           |address              |size |value(s)\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("intByValue       |%20p |%20llu |%4lu |%5d\n", &intByValue, (long long int)&intByValue, sizeof(intByValue), intByValue);
    printf("intByReference   |%20p |%20llu |%4lu |%5d\n", &intByReference, (long long int)&intByReference, sizeof(intByReference), intByReference);
    printf("intByAddress     |%20p |%20llu |%4lu |%5d\n", &intByAddress, (long long int)&intByAddress, sizeof(intByAddress), intByAddress);

    printf("NOTA BENE: un'espressione può essere passata solo per valore!!!\n");
    // Nota bene
    // can pass an expression by Value: the result is copied ...
    f(4 * 3 + intByValue, intByReference, &intByAddress);

    // cannot pass an expression by Reference
    // f(intByValue, 4 * 3 + intByReference, &intByAddress);
    // error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’

    // cannot pass an expression by Address
    // f(intByValue, intByReference, &(4 * 3 + intByAddress));
    // error: lvalue required as unary ‘&’ operand

    // successful termination
    return 0;
}

// function definition
void f(int parmByValue, int &parmByReference, int *parmByAddress)
{
    // visualizza, per ciascun parametro:
    // il nome (usato per riferirsi al parametro)
    // l'indirizzo di memoria in cui il dato e' memorizzato (in hex) ottenuto con &nome ( cioe' <indirizzo di> nome)
    // l'indirizzo di memoria in cui il dato e' memorizzato (in decimale) ottenuto con &nome ( cioe' <indirizzo di> nome)
    // la dimensione (in bytes) dell'area di memoria riservata al parametro ottenuta con sizeof(nome)
    // il valore del parametro (ottenuto con *parmByAddress nel caso di indirizzo!)
    printf("\nin function f(int parmByValue,int &parmByReference,int *parmByAddress) before change\n");
    printf("name             | 0xaddress           | address             |size |value(s)\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("parmByValue      |%20p |%20llu |%4lu |%5d\n", &parmByValue, (long long int)&parmByValue, sizeof(parmByValue), parmByValue);
    printf("parmByReference  |%20p |%20llu |%4lu |%5d\n", &parmByReference, (long long int)&parmByReference, sizeof(parmByReference), parmByReference);
    printf("parmByAddress    |%20p |%20llu |%4lu |%5d\n", &parmByAddress, (long long int)&parmByAddress, sizeof(parmByAddress), *parmByAddress);
    printf("\nin function f(int parmByValue,int &parmByReference,int *parmByAddress) changing variables\n");
    // modifica i tre parametri
    printf("Executing: parmByValue=40;\n");
    parmByValue = 40;
    printf("Executing: parmByReference=41;\n");
    parmByReference = 41;
    printf("Executing: *parmByAddress=42;\n");
    *parmByAddress = 42; // si noti l'* prima del nome per indicare il dato memorizzato all'indirizzo parmByAddress
    // visualizza, per ciascun parametro ... come prima
    printf("\nin function f(int parmByValue,int &parmByReference,int *parmByAddress) after change\n");
    printf("name             | 0xaddress           | address             |size |value(s)\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("parmByValue      |%20p |%20llu |%4lu |%5d\n", &parmByValue, (long long int)&parmByValue, sizeof(parmByValue), parmByValue);
    printf("parmByReference  |%20p |%20llu |%4lu |%5d\n", &parmByReference, (long long int)&parmByReference, sizeof(parmByReference), parmByReference);
    printf("parmByAddress    |%20p |%20llu |%4lu |%5d\n", &parmByAddress, (long long int)&parmByAddress, sizeof(parmByAddress), *parmByAddress);
}
