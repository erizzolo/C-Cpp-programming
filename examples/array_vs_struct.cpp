/*
    Purpose:    differences and analogies between arrays and structs
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2020/01/18
    Note:
*/
// directive for standard io functions
#include <iostream>

using namespace std;

#define DEBUG 1

struct s
{
    int day, month, year;
};

void fun_a(int[]);
void fun_s(s);

// int [3] a_fun(); // error: decomposition declaration cannot be declared with type ‘int’
// int [] a_fun(); // error: decomposition declaration cannot be declared with type ‘int’
s s_fun();

// funzione principale
int main(int argc, char *argv[])
{
    {
        cout << "\n\
Caratteristica           Array                    Struct                    \n\
==============================================================================\n\
significato logico dati  medesimo                  diverso    \n\
tipo fisico dati         medesimo                  (possibilmente) diverso    \n\
dati riferiti a          diversi soggetti          medesimo soggetto   \n\
elementi organizzati in  sequenza                  insieme     \n\
numero di elementi       variabile                 fisso   \n\
accesso ad elemento      [<posizione>]             .<nome> \n\
    tramite              espressione runtime       identificatore compile time\n\
    esempio:             a[i+5]                    s.year  \n\
uso con cin >>           NO                        NO  \n\
    error                          no match for ‘operator>>’ ...   \n\
uso con cout <<          SI                        NO  \n\
    nota/error           come &a[0]                no match for ‘operator<<’ ...\n\
assegnazione (copia)     NO                        SI  \n\
    error/nota           invalid array assignment  ok    \n\
parametro funzione(a/s)  SI                        SI  \n\
    nota                 come &v[0] by address     ok by value   \n\
tipo funzione()          NO                        SI  \n\
    error/nota           decomposition ...         ok   \n\
nidificazione            SI                        SI   \n\
    esempio              array di struct           struct di array  \n\
                         array di array            struct di struct \n\
confronti ==, <, >, ...  SI                        NO   \n\
    nota/error           confronto indirizzi       no match for ‘operator...’   \n\
        " << endl;
    }
    /// esempi per array
    int a[3];
    // cin >> a;
    cout << "cout << a: " << a << endl; // means cout << &a[0] << endl;
    int a_copy[3];
    // a_copy = a;  error: invalid array assignment
    fun_a(a);
    int aa[5][3]; // array di array
    s as[10];     // array di struct
    for (int i = 0; i < 3; i++)
        a[i] = a_copy[i] = 0;
    cout << (a_copy == a ? "arrays are equals." : "arrays are different.") << endl;
    cout << (a_copy < a ? "a_copy is less than a." : "a_copy is greater than or equal to a.") << endl;
    cout << (a_copy > a ? "a_copy is greater than a." : "a_copy is less than or equal to a.") << endl;
    /// esempi per struct
    s d;
    // cin >> d;
    // cout << d;
    s d_copy;
    d_copy = d;
    fun_s(d);
    d = s_fun();
    struct sa
    {
        int a[3];
    };
    struct ss
    {
        s d;
    };
    // cout << (d_copy == d ? "structs are equals." : "structs are different.") << endl;
    // successful termination
    return 0;
}

void fun_a(int p[])
{
    cout << "In fun_a: p = " << p << endl;
}
void fun_s(s p)
{
    cout << "In fun_s: &p = " << &p << endl;
}

s s_fun()
{
    s result;
    cout << "Returning result of size " << sizeof(result) << endl;
    return result;
}
