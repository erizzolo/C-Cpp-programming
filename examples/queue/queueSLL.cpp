/**
 * Purpose: basic queue implementation based on a singly linked list
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:    item must be defined as a valid data type (e.g. with using item = double;)
 *          CAPACITY need not be defined as a valid costant positive integer
 */

// definition of node data type
struct node
{
    item info;           // one and only one info per node
    node *next{nullptr}; // link to next node (in removal order)
};

// definition of queue data type
struct queue
{
    node *front{nullptr}; // link to front node (first to be extracted)
    node *back{nullptr};  // link to back node (last to be extracted)
    size_t size{0};       // actual size of the queue (number of elements)
};

/*  NOTA BENE
    With this definition of queue data type
    data are NOT part of the struct !!!
        size of struct:
              sizeof(front) i.e. sizeof(node *) usually 4B or 8B, independent of capacity!
            + sizeof(back) i.e. sizeof(node *) usually 4B or 8B, independent of capacity!
            + sizeof(size_t)
    If the struct is copied, the addresses of the front & back nodes are copied
    but the actual nodes/data are shared between the copies !!!!
*/

// basic operations
size_t size(const queue &q)
{
    return q.size;
}
size_t capacity(const queue &q)
{
    return q.size; // can change
}
bool insert(queue &q, const item &i)
{
    // create a new node
    node *inserted = new (nothrow) node;
    // check success
    if (inserted != nullptr)
    {
        // setup of the new node
        inserted->info = i;       // insert data
        inserted->next = nullptr; // last node of the queue
        // update old back node (if any) and queue
        if (q.back != nullptr)
        {
            q.back = q.back->next = inserted; // new next and new back
        }
        else
        {
            q.back = q.front = inserted; // new front and new back
        }
        q.size++; // one element more
        return true;
    }
    return false;
}
bool remove(queue &q, item &i)
{
    node *removed = q.front;
    // if not empty
    if (removed != nullptr)
    {
        // setup info
        i = removed->info; // extract from front node
        // update queue
        q.front = removed->next; // new front node
        if (q.back == removed)
        {
            q.back = nullptr; // new back node
        }
        q.size--; // one element less
        // no memory leakage, please
        delete removed; // free memory
        return true;
    }
    return false;
}

// for debug purposes
// almost implementation independent
void print(const queue &q, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Queue{ ";
    out << size(q) << "/" << capacity(q) << ", front :";
    node *current = q.front;
    while (current != nullptr)
    {
        // show elements from front to bottom
        out << " " << current->info; // implementation dependent
        current = current->next;
    }
    out << " : back}";
    if (newLine)
    {
        out << endl;
    }
}
