/**
 * Purpose: basic queue implementation based on a dynamic length (non circular) array
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2023/02/07
 * Note:
 */

/**
 * A simple way is to insert at the lowest free position like in a stack,
 * and remove from the other end, shifting the rest of the queue.
 * |  0|  1|  2|  3|  4|  5|  6|  7|  8|  9| 10| 11| 12| 13| 14| 15|
 * The situation after 6 insertions (A, B, C, D, E, F) and two removals (A, B)
 * |  C|  D|  E|  F|  4|  5|  6|  7|  8|  9| 10| 11| 12| 13| 14| 15|
 * size: 4
 * insertion: 4
 * removal: 0  (plus shift !!!)
 *
 * Example with items = letters
 *  Insertion at this end (from the top):
 * 4        | |    | |     | |     | |     | |     | |     | |     | |     | |
 * 3        | |    | |     | |     | |     | |     | |     | |     | |     | |
 * 2        | |    | |     | |     |C|     | |     |D|     | |     | |     | |
 * 1        | |    | |     |B|     |B|     |C|     |C|     |D|     | |     | |
 * 0        | |    |A|     |A|     |A|     |B|     |B|     |C|     |D|     | |
 *  Removal (pop) at this end (from the bottom):
 * size      0      1       2       3       2       3       2       1       0
 * operation     I      I       I       R       I       R       R       R
 * item          A      B       C       A       D       B       C       D
 */

// definition of queue data type
struct queue
{
    item *data = (item *)malloc(sizeof(item) * CAPACITY); // the actual data
    // item data[CAPACITY];
    size_t size{0}; // actual number of elements === insertion index
    size_t capacity{CAPACITY};
};

// basic operations
size_t size(const queue &q)
{
    return q.size;
}
size_t capacity(const queue &q)
{
    return q.capacity;
}
bool insert(queue &q, const item &i)
{
    bool result = size(q) < capacity(q); // not full yet
    if (!result)
    {
        size_t newCapacity = capacity(q) * 2;
        item *newData = (item *)realloc(q.data, sizeof(item) * newCapacity);
        if (newData != nullptr)
        {
            q.data = newData;
            q.capacity = newCapacity;
            result = true;
        }
    }
    if (result)
    {
        q.data[size(q)] = i; // insert into next empty position
        q.size++;            // one element more
    }
    return result;
}
bool remove(queue &q, item &i)
{
    bool result = size(q) > 0; // not empty
    if (result)
    {
        i = q.data[0]; // extract from first non-empty position
        q.size--;      // one element less
        // shift the rest
        for (size_t i = 0; i < size(q); ++i)
        {
            q.data[i] = q.data[i + 1];
        }
    }
    return result;
}

// for debug purposes
// almost implementation independent
void print(const queue &q, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Queue{ ";
    out << size(q) << "/" << capacity(q) << ", first :";
    for (size_t i = 0; i < size(q); i++)
    {
        // show element from first to last
        out << " " << q.data[i]; // implementation dependent
    }
    out << " : last}";
    if (newLine)
    {
        out << endl;
    }
}
