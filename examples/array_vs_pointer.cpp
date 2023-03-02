/*
    Purpose:    differences and analogies between arrays and pointers
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2020/01/22
    Note:
*/
// directive for standard io functions
#include <iostream>
// directive for io manipulation
#include <iomanip>
// directive for malloc
#include <cstdlib>

using namespace std;

#define DEBUG 1

// array/pointer function using array sintax
void fa(double ap[], int size)
{
    cout << "[ ";
    for (int i = 0; i < size; i++)
    {
        if (i != 0)
        {
            cout << ", ";
        }
        cout << ap[i];
    }
    cout << "]";
}

// array/pointer function using pointer sintax
void fp(double *ap, int size)
{
    // Version 1 with array-like sintax
    cout << "[";
    for (int i = 0; i < size; i++)
    {
        if (i != 0)
        {
            cout << ", ";
        }
        cout << ap[i];
    }
    cout << "]";
    // Version 2 with some pointer-like sintax
    cout << "[";
    for (int i = 0; i < size; i++)
    {
        if (i != 0)
        {
            cout << ", ";
        }
        cout << *(ap + i);
    }
    cout << "]";
    // Version 3 with full pointer-like sintax
    cout << "[";
    for (double *p = ap, *theEnd = ap + size; p != theEnd; p++)
    {
        if (p != ap)
        {
            cout << ", ";
        }
        cout << *p;
    }
    cout << "]";
}

// funzione principale
int main(int argc, char *argv[])
{
    {
        cout << "ARRAY VARIABLES" << endl;
        cout << "Declaring an array variable means:" << endl;
        cout << "1. reserving enough contiguous memory space for each element" << endl;
        cout << "2. assigning to the variable name the (initial) address of the space" << endl;
        cout << "   N.B. - the address cannot be changed during variable's lifetime!!!" << endl;
        double v[4]; /// example of an array of 4 doubles named v
        cout << "Example with an array of 4 doubles named v:" << endl;
        cout << "double v[4];	/// declaration" << endl;
        cout << "reserves 4 * " << sizeof(v[0]) << " = " << sizeof(v) << " B of memory like this:" << endl;
        cout << "                      0   1   2   3   4   5   6   7" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << "v: " << setw(15) << v << "  |   |   |   |   |   |   |   |   | first double" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << setw(18) << &v[1] << "  |   |   |   |   |   |   |   |   | second double" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << setw(18) << &v[2] << "  |   |   |   |   |   |   |   |   | third double" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << setw(18) << &v[3] << "  |   |   |   |   |   |   |   |   | fourth double" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << setw(18) << &v[4] << "  | ..... HIC SUNT LEONES .....   | no double here" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << endl;

        cout << "Expression        Value           Note" << endl;
        cout << "======================================================================================" << endl;
        cout << "sizeof(v)         " << setiosflags(ios_base::left) << setw(16) << sizeof(v) << "size of the whole array" << endl;
        cout << "sizeof(v[0])      " << setiosflags(ios_base::left) << setw(16) << sizeof(v[0]) << "size of a single element" << endl;
        cout << "v                 " << setiosflags(ios_base::left) << setw(16) << v << "means v is considered an address" << endl;
        cout << "v[0] = 1.0;       " << setiosflags(ios_base::left) << setw(16) << (v[0] = 1.0) << "value of assignment is the assigned value" << endl;
        cout << "v[1] = 2.0;       " << (v[1] = 2.0) << endl;
        cout << "v[2] = 3.0;       " << (v[2] = 3.0) << endl;
        cout << "v[3] = 4.0;       " << (v[3] = 4.0) << endl;
        cout << "*v                " << setiosflags(ios_base::left) << setw(16) << (*v) << "use of v as a pointer (double *): same as v[0]" << endl;
        cout << "*v = 1.5;         " << setiosflags(ios_base::left) << setw(16) << (*v = 1.5) << "use of v as a pointer (double *): same as v[0] = 1.5" << endl;
        cout << "v[0]              " << setiosflags(ios_base::left) << setw(16) << (v[0]) << "check previous assignment" << endl;
        cout << "v++;              " << setiosflags(ios_base::left) << setw(16) << "N/A"
             << "error: lvalue required as increment operand" << endl;
        cout << "                  " << setiosflags(ios_base::left) << setw(16) << " "
             << "i.e. the address cannot be changed!!!" << endl;
        cout << "POINTER VARIABLES" << endl;
        cout << "Declaring a pointer variable means:" << endl;
        cout << "1. reserving enough memory space for an address" << endl;
        cout << "   N.B. - the address can (and should) be changed during variable's lifetime!!!" << endl;
        double *p; /// example of a pointer to double(s) named p
        cout << "Example with a pointer to double(s) named p:" << endl;
        cout << "double *p;	/// declaration" << endl;
        cout << "reserves " << sizeof(p) << " B of memory like this:" << endl;
        cout << "                      0   1   2   3   4   5   6   7" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << "&p: " << setw(15) << &p << " |   |   |   |   |   |   |   |   | p" << endl;
        cout << "                    +---+---+---+---+---+---+---+---+" << endl;
        cout << endl;
        cout << "Expression        Value           Note" << endl;
        cout << "======================================================================================" << endl;
        cout << "sizeof(p)         " << setiosflags(ios_base::left) << setw(16) << sizeof(p) << "size of an address" << endl;
        cout << "sizeof(*p)        " << setiosflags(ios_base::left) << setw(16) << sizeof(*p) << "size of an element pointed by p (a double)" << endl;
        cout << "p                 " << setiosflags(ios_base::left) << setw(16) << p << "value of address (not initialised yet)" << endl;
        cout << "*p                " << setiosflags(ios_base::left) << setw(16) << "<NONSENSE!!!>"
             << "value of the double pointed by p (random?)" << endl;
        // next line commented because of possible memory error !!!!
        // cout << "*p                " << setiosflags(ios_base::left) << setw(16) << *p << "value of the double pointed by p (random?)" << endl;
        cout << "p = &v[2];        " << setiosflags(ios_base::left) << setw(16) << (p = &v[2]) << "assignment of the address of v[2]" << endl;
        cout << "*p                " << setiosflags(ios_base::left) << setw(16) << *p << "value of the double pointed by p (i.e. v[2])" << endl;
        cout << "*p = 2.5;         " << setiosflags(ios_base::left) << setw(16) << (*p = 2.5) << "assignment through p (i.e. v[2] = 2.5)" << endl;
        cout << "v[2]              " << setiosflags(ios_base::left) << setw(16) << (v[2]) << "check previous assignment" << endl;
        cout << "p = v;            " << setiosflags(ios_base::left) << setw(16) << (p = v) << "assignment of the address of the array (i.e. &v[0])" << endl;
        cout << "p[1]              " << setiosflags(ios_base::left) << setw(16) << p[1] << "use of p as an array (of doubles): same as v[1]" << endl;
        cout << "p++;              " << setiosflags(ios_base::left) << setw(16) << p++ << "postincrement to next double (i.e. v[1]" << endl;
        cout << "p                 " << setiosflags(ios_base::left) << setw(16) << p << "now the address has changed to &v[1]" << endl;
        cout << "*p                " << setiosflags(ios_base::left) << setw(16) << *p << "value of the double pointed by p (i.e. v[1])" << endl;
        cout << "p = v;            " << setiosflags(ios_base::left) << setw(16) << (p = v) << "assignment of the address of the array (i.e. &v[0])" << endl;
        cout << endl;
        cout << "Function call   Value             Note" << endl;
        cout << "==================================================================================" << endl;
        cout << "fa(v, 4);       ";
        fa(v, 4);
        cout << "  array param (actually an array) treated as array" << endl;
        cout << "fp(v, 4);       ";
        fp(v, 4);
        cout << "  pointer param (actually an array) treated as pointer" << endl;
        cout << "fa(p, 4);       ";
        fa(p, 4);
        cout << "  array param (actually a pointer) treated as array" << endl;
        cout << "fp(p, 4);       ";
        fp(p, 4);
        cout << "  pointer param (actually a pointer) treated as pointer" << endl;
    }
    //    {
    //        /// example from cppreference
    //        cout << endl
    //             << "example from cppreference" << endl;
    //        cout << "int* p1 = (int*) calloc(4, sizeof(int));    /// allocate and zero out an array of 4 int" << endl;
    //        int *p1 = (int *)calloc(4, sizeof(int)); /// allocate and zero out an array of 4 int
    //        cout << "if(p1) {    /// check allocation success" << endl;
    //        if (p1)
    //        { /// check allocation success
    //            cout << "/// print the array" << endl;
    //            /// print the array
    //            for (int n = 0; n < 4; ++n)
    //            {
    //                cout << "p1[" << n << "] = " << p1[n] << endl;
    //            }
    //            cout << "free(p1); /// free memory" << endl;
    //            free(p1); /// free memory
    //        }
    //        cout << "int *p2 = (int *)calloc(1, sizeof(int[4])); /// same, naming the array type directly" << endl;
    //        int *p2 = (int *)calloc(1, sizeof(int[4])); /// same, naming the array type directly
    //        cout << "if(p2) {    /// check allocation success" << endl;
    //        if (p2)
    //        { /// check allocation success
    //            cout << "/// print the array" << endl;
    //            /// print the array
    //            for (int n = 0; n < 4; ++n)
    //            {
    //                cout << "p2[" << n << "] = " << p2[n] << endl;
    //            }
    //            cout << "free(p2); /// free memory" << endl;
    //            free(p2); /// free memory
    //        }
    //        cout << "int *p3 = (int *)calloc(4, sizeof *p3); /// same, without repeating the type name" << endl;
    //        int *p3 = (int *)calloc(4, sizeof *p3); /// same, without repeating the type name
    //        cout << "if(p3) {    /// check allocation success" << endl;
    //        if (p3)
    //        { /// check allocation success
    //            cout << "/// print the array" << endl;
    //            /// print the array
    //            for (int n = 0; n < 4; ++n)
    //            {
    //                cout << "p3[" << n << "] = " << p3[n] << endl;
    //            }
    //            cout << "free(p3); /// free memory" << endl;
    //            free(p3); /// free memory
    //        }
    //    }
    // successful termination
    return 0;
}
