/**
 * Purpose: basic stack implementation based on a fixed length array
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:    item must be defined as a valid data type (e.g. with using item = double; or struct item {...})
 *          CAPACITY must be defined as a valid costant positive integer
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

// definition of stack data type
struct stack
{
    item data[CAPACITY]; // the actual data
    size_t size{0};      // actual size of the stack (number of elements)
};

// basic operations
size_t size(const stack &s)
{
    return s.size;
}
size_t capacity(const stack &s)
{
    return CAPACITY;
}
bool push(stack &s, const item &i)
{
    bool result = size(s) < capacity(s); // not full yet
    if (result)
    {
        s.data[size(s)] = i; // insert size_to bottom empty position
        s.size++;            // one element more
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
