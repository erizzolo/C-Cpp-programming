/**
 * Purpose: basic stack implementation based on a dynamic length array
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/02/07
 * Note:    item must be defined as a valid data type (e.g. with using item = size_t;)
 *          CAPACITY need not be defined as a valid costant positive integer
 */

/**
 * Example with items = letters
 * Insertion (push) and Removal (pop) at this end (from the top):
 * 4        | |    | |     | |     | |     | |     | |     | |     | |     | |
 * 3        | |    | |     | |     | |     | |     | |     | |     | |     | |
 * 2        | |    | |     | |     |C|     | |     |D|     | |     | |     | |
 * 1        | |    | |     |B|     |B|     |B|     |B|     |B|     | |     | |
 * 0        | |    |A|     |A|     |A|     |A|     |A|     |A|     |A|     | |
 * size      0      1       2       3       2       3       2       1       0
 * operation     I      I       I       R       I       R       R       R
 * item          A      B       C       C       D       D       B       A
 */

// needed for realloc
#include <cstdlib>

// definition of stack data type
struct stack
{
    // the fixed length array is not used anymore
    // item data[CAPACITY]; // the actual data
    // we use a pointer instead to (the first element of) a dynamic array
    item *data{nullptr}; // address of the actual data (nothing so far)
    size_t capacity{0};  // actual capacity of the stack (max number of elements)
    size_t size{0};      // actual size of the stack (number of elements)
};

/*  NOTA BENE
    With the old definition of stack data type
        struct stack
        {
            item data[CAPACITY]; // the actual data
            size_t size{0};      // actual size of the stack (number of elements)
        };
    data are part of the struct !!!
        size of struct:
            sizeof(data) i.e. CAPACITY * sizeof(item)
            + sizeof(size_t)
    With the new definition of stack data type
        struct stack
        {
            item *data{nullptr}; // address of the actual data (nothing so far)
            size_t capacity{0};  // actual capacity of the stack (max number of elements)
            size_t size{0};      // actual size of the stack (number of elements)
        };
    data are NOT part of the struct !!!
        size of struct:
            sizeof(data) i.e. sizeof(item *) usually 4B or 8B, independent of capacity!
            + 2 * sizeof(size_t)
    If the struct is copied, the address of the data is copied
    but the actual data are shared between the copies !!!!
*/

// will be used by push, and possibly to extend/reduce/free allocated memory
bool setCapacity(stack &s, size_t newCapacity);

// basic operations
size_t size(const stack &s)
{
    return s.size;
}
size_t capacity(const stack &s)
{
    return s.capacity; // can change
}
bool push(stack &s, const item &i)
{
    bool result = size(s) < capacity(s); // not full yet
    if (result)
    {
        s.data[size(s)] = i; // insert into bottom empty position
        s.size++;            // one element more
    }
    else
    {
        // we need more space: extend the array to newCapacity
        size_t newCapacity = s.capacity == 0 ? 2 : s.capacity * 2;
        if (setCapacity(s, newCapacity))
        {
            return push(s, i); // safe insert now
        }
    }
    return result;
}
bool pop(stack &s, item &i)
{
    bool result = size(s) > 0; // not empty
    if (result)
    {
        s.size--;            // one element less
        i = s.data[size(s)]; // extract from top non-empty position
    }
    return result;
}
bool setCapacity(stack &s, size_t newCapacity)
{
    if (newCapacity == 0)
    {
        // free dynamic memory ...
        free(s.data);
        s.data = nullptr; // just to be on the safe side
        s.capacity = 0;
        // and empty the stack
        s.size = 0;
        return true;
    }
    else
    {
        // resize the stack to newCapacity
        item *p = (item *)realloc(s.data, newCapacity * sizeof(s.data[0]));
        if (p != nullptr)
        {
            // successfully extended (or reduced???) !!!
            s.capacity = newCapacity;
            s.data = p; // might have changed !!!
            if (s.size > s.capacity)
            {
                s.size = s.capacity; // full stack
            }
        }
        return p != nullptr;
    }
}
// for debug purposes
// almost implementation independent
void print(const stack &s, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Stack{ ";
    out << size(s) << "/" << capacity(s) << ", bottom :";
    for (size_t i = 0; i < size(s); i++)
    {
        // show elements from bottom to top
        cout << " " << s.data[i]; // implementation dependent
    }
    out << " : top}";
    if (newLine)
    {
        out << endl;
    }
}
