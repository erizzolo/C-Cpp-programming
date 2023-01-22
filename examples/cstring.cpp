/**
 * Purpose: C strings
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/01/17
 * Note:
 */

#include <iostream>
using namespace std;

/**
 * Come già detto, gli array si elaborano elemento per elemento.
 * Fanno eccezione, in alcuni casi, gli array di char che in C/C++
 * rappresentano le stringhe, ovvero sequenze di caratteri come parole,
 * frasi o testo in genere.
 * La particolarità è dovuta all'uso frequente ed al fatto che la
 * lunghezza della stringa (numero di caratteri che sono utilizzati),
 * non corrisponde al numero di elementi dell'array ma dipende dalla
 * posizione di un particolare valore (il valore numerico o codice ASCII 0),
 * che serve da terminatore della sequenza.
 * Gli array di char usati come stringhe possono essere inizializzati,
 * scritti in output o letti in input "interamente" e non elemento per elemento,
 * come avviene per gli array di altro tipo.
 */

#define DEBUG 1

int lunghezza(const char stringa[]);

// main function
int main(int argc, char *argv[])
{
    // una semplice stringa, racchiusa tra doppi apici
    char stringa[] = "Hello, world!";               /// 13 characters !!!
    int dim = sizeof(stringa) / sizeof(stringa[0]); /// gives 14 !!!
    cout << "L'array " << stringa << " e' lungo " << dim << endl;
    // Si noti l'elemento aggiunto, cioè il terminatore !!!
    cout << stringa << endl;
    for (int i = 0; i < dim; i++)
    {
        // stringa[i] è un singolo char, stringa[i] + 0 è convertito ad int
        // e quindi visualizzato come numero decimale (il codice ASCII del char)
        cout << stringa[i] << " ascii " << stringa[i] + 0 << endl;
    }
    // inserendo un char di valore 0 (NON la cifra '0') la stringa sarà troncata
    stringa[6] = 0; /// terminatore in posizione 6
    cout << stringa << endl;
    // caratteri speciali ...
    char doublequotes[] = "'string with \" quotes'";
    cout << doublequotes << endl;
    char backslash[] = "'string with \\ backslash'";
    cout << backslash << endl;
    char newline[] = "'string with \n newline'";
    cout << newline << endl;
    // how many characters for a newline?
    int dimnewline = sizeof(newline) / sizeof(newline[0]);
    for (int i = 0; i < dimnewline; i++)
    {
        cout << newline[i] << " ascii " << newline[i] + 0 << endl;
    }
    /// char parola[5] = "pippo";   error: need a terminator !!!
    char cognome[8] = "Rizzolo"; // fine ... 7 + 1 = 8
    char nome[15] = "pippo";     // fine ... more elements than initializers
    char greeting[] = "Ciao ";   // fine ... compiler knows better
    char prompt[] = "Immetti il tuo nome (max 14 caratteri): ";
    cout << prompt;
    // input of a "whole" array (+ terminator) in one single instruction !!!!
    //    cin >> nome; // NON sicuro
    cin.getline(nome, sizeof(nome)); // much better, exceeding chars are removed...
                                     //    char rimanenza[100];
                                     //    cin >> rimanenza;
                                     //    cout << "rimanenza = " << rimanenza << endl;
    cout << greeting << nome << " " << cognome << "!" << endl;
    // lunghezza di una stringa
    cout << "Your name is " << lunghezza(nome) << " characters!!" << endl;
    // only cin >> and cout << work with the whole array !!!
    // char soprannome[15] = nome; // error: array must be initialized with a brace-enclosed initializer
    char soprannome[15];
    // soprannome = nome; // error: invalid array assignment
    // nome = cognome; // error: incompatible types in assignment of ‘char [8]’ to ‘char [15]’
    // to get the address, we need a cast ...
    cout << "cognome @ " << (void *)cognome << endl;
    cout << "nome @ " << (void *)&nome[0] << endl;
    cout << "greeting @ " << (void *)greeting << endl;
    cout << "prompt @ " << (void *)&prompt[0] << endl;
    // non sempre ci servono stringhe !!!
    // not a string but a "real" char array (i.e. without terminator!!!)
    // char vocali[] = {'a', 'e', 'i', 'o', 'u'};
    char vocali[] = {'a', 101, 'i', 'o', 'u'};
    // probabilmente errato ...
    cout << vocali << "?" << endl;
    // table of ASCII chars (16 each row)
    for (int i = 0; i < 256; ++i)
    {
        if (i % 16 == 0)
            cout << endl;
        cout << (char)i << " ";
    }
    // successful termination
    return 0;
}
/**
 * Lunghezza di una stringa
 * Si assume che sia correttamente terminata ...
 * i.e. la sentinella esiste ed è al suo posto
 * @param   stringa  la stringa di cui si vuole la lunghezza
 * @return  la lunghezza della stringa specificata
 */
int lunghezza(const char stringa[])
{
    int i = 0;
    while (stringa[i] != 0)
    {
        i++; // skip valid chars
    }
    return i;
}
