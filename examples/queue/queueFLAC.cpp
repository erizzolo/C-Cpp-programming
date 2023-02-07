/**
 * Purpose: basic queue implementation based on a fixed length (circular) array
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
 */

/**
 * An array of 16 elements viewed in a circular way
 * |  0 |  1 |  2 |  3 |  4 |
 * | 15 |              |  5 |
 * | 14 |              |  6 |
 * | 13 |              |  7 |
 * | 12 | 11 | 10 |  9 |  8 |
 *
 * The situation after 6 insertions (A, B, C, D, E, F)
 * and two removals (A, B)
 * |  0 |  1 |  C |  D |  E |
 * | 15 |              |  F |
 * | 14 |              |  6 |
 * | 13 |              |  7 |
 * | 12 | 11 | 10 |  9 |  8 |
 * size: 4
 * insertion: 6
 * [removal = (insertion - size) % capacity: 2]
 *
 * Example with items = letters and CAPACITY = 3
 * Logical index        0   1   2   3   4   5   6   7   8   ...
 * Physical index       0   1   2   0   1   2   0   1   2   ...
 * Oper Size Ins Rem
 *       0    0  [0]  |   |   |   |   |   |   |   |   |   | ...
 * I A   1    1   0   | A |   |   |   |   |   |   |   |   | ...
 * I B   2    2   0   | A | B |   |   |   |   |   |   |   | ...
 * I C   3   [0]  0   | A | B | C |   |   |   |   |   |   | ...
 * R A   2    0   1   |   | B | C |   |   |   |   |   |   | ...
 * I D   3   [1]  1   |   | B | C | D |   |   |   |   |   | ...
 * R B   2    1   2   |   |   | C | D |   |   |   |   |   | ...
 * R C   1    1   0   |   |   |   | D |   |   |   |   |   | ...
 * R D   0    1  [1]  |   |   |   |   |   |   |   |   |   | ...
 * [ ] means insertion/removal impossible
 */

// definition of queue data type
struct queue
{
    item data[CAPACITY]; // the actual data
    size_t size{0};      // actual number of elements
    size_t insertion{0}; // actual insertion slot
    // size_t removal{0};   // (insertion - size) % capacity
};

// basic operations
size_t size(const queue &q)
{
    return q.size;
}
size_t capacity(const queue &q)
{
    return CAPACITY;
}
bool insert(queue &q, const item &i)
{
    bool result = size(q) < capacity(q); // not full yet
    if (result)
    {
        q.data[q.insertion] = i; // insert into next empty position
        q.size++;                // one element more
        q.insertion++;           // next empty position (circular)
        if (q.insertion == capacity(q))
        {
            q.insertion = 0;
        }
    }
    return result;
}
bool remove(queue &q, item &i)
{
    bool result = size(q) > 0; // not empty
    if (result)
    {
        size_t removal; // removal position (circular)
        if (q.insertion >= q.size)
            removal = q.insertion - q.size;
        else
            removal = q.insertion + (capacity(q) - size(q));
        i = q.data[removal]; // extract from first non-empty position
        q.size--;            // one element less
    }
    return result;
}

// for debug purposes
// almost implementation independent
void print(const queue &q, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Queue{ ";
    out << size(q) << "/" << capacity(q) << ", first :";
    size_t removal; // removal position (circular)
    if (q.insertion >= q.size)
        removal = q.insertion - q.size;
    else
        removal = q.insertion + (capacity(q) - size(q));
    for (size_t i = 0; i < size(q); i++)
    {
        // show element from first to last
        out << " " << q.data[removal]; // implementation dependent
        removal++;
        if (removal == capacity(q))
        {
            removal = 0;
        }
    }
    out << " : last}";
    if (newLine)
    {
        out << endl;
    }
}
