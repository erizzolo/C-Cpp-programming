/*
    Purpose:    Count Sort Top 1000 English Words
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2023/06/01
    Note:
*/
/*
    Versione "Libralesso", con piccole modifiche
*/

#include <iostream>
#include <limits>
#include <chrono>
#include <algorithm>

using namespace std;

const bool DEBUG = false;

#include "top1000ew.h"

void printWords(const word_t parole[], const size_t numWords); // print the words
// 1° method: sort on each character from last to first
void sort_1(word_t parole[], const size_t numWords);
// 2° method: sort on first character, then sort each group on second, ..., then sort each group on last character
void sort_2(word_t parole[], const size_t numWords);
// 3° method: sort on each character from last to first using pointer arithmetic
void sort_3(word_t words[], const size_t numWords);

void countSort(word_t parole[], word_t copie[], const size_t inf, const size_t sup, const size_t carattere, const size_t maxCarattere);

template <typename T>
void copyArray(const T from[], T to[], size_t count, size_t offset = 0)
{
    for (size_t i = 0; i < count; i++)
        to[i + offset] = from[i];
}

// funzione principale
int main(int argc, char *argv[])
{
    word_t *w = new word_t[NUM_WORDS]; // create working array
    {
        cout << "1° method: sort on each character from last to first" << endl;
        copyArray(words, w, NUM_WORDS);                         // copy
        auto start = std::chrono::high_resolution_clock::now(); // record start time
        sort_1(w, NUM_WORDS);                                   // do some work
        auto end = std::chrono::high_resolution_clock::now();   // record end time
        std::chrono::duration<double> diff = end - start;
        std::cout << "Time to order " << NUM_WORDS << " words : " << diff.count() << " s" << endl;
        if (DEBUG)
            printWords(w, NUM_WORDS);
    }

    {
        cout << "2° method: sort on first character, then sort each group on second, ..., then sort each group on last character" << endl;
        copyArray(words, w, NUM_WORDS);                         // copy
        auto start = std::chrono::high_resolution_clock::now(); // record start time
        sort_2(w, NUM_WORDS);                                   // do some work
        auto end = std::chrono::high_resolution_clock::now();   // record end time
        std::chrono::duration<double> diff = end - start;
        std::cout << "Time to order " << NUM_WORDS << " words : " << diff.count() << " s" << endl;
        if (DEBUG)
            printWords(w, NUM_WORDS);
    }

    {
        cout << "3° method: sort on each character from last to first using pointer arithmetic" << endl;
        copyArray(words, w, NUM_WORDS);                         // copy
        auto start = std::chrono::high_resolution_clock::now(); // record start time
        sort_3(w, NUM_WORDS);                                   // do some work
        auto end = std::chrono::high_resolution_clock::now();   // record end time
        std::chrono::duration<double> diff = end - start;
        std::cout << "Time to order " << NUM_WORDS << " words : " << diff.count() << " s" << endl;
        if (DEBUG)
            printWords(w, NUM_WORDS);
    }

    {
        cout << "4° method: std::sort using < operator" << endl;
        copyArray(words, w, NUM_WORDS);                         // copy
        auto start = std::chrono::high_resolution_clock::now(); // record start time
        sort(w, w + NUM_WORDS);                                 // do some work
        auto end = std::chrono::high_resolution_clock::now();   // record end time
        std::chrono::duration<double> diff = end - start;
        std::cout << "Time to order " << NUM_WORDS << " words : " << diff.count() << " s" << endl;
        if (DEBUG)
            printWords(w, NUM_WORDS);
    }

    delete[] w; // free memory
    return 0;
}

void printWords(const word_t parole[], const size_t numWords)
{
    for (size_t w = 0; w < numWords; w++)
        cout << parole[w] << endl;
}

// helper for each method

/// @brief returns key value for a word_t or total key value number
/// @param w the word pointer or nullptr
/// @param position the position of the character to consider
/// @return if w is a null pointer the total key value number, otherwise the key for word *w
inline size_t getKey(const word_t *w, size_t position = 0)
{
    if (w == nullptr)
    {
        return std::numeric_limits<unsigned char>::max() + 1;
    }
    return (unsigned char)(w->word[position]);
}

// helper for 1° method: sort on given character
void sort_1_on(const word_t from[], word_t to[], const size_t numWords, const size_t position)
{
    size_t keyCount = getKey(nullptr, position); // get number of key values
    size_t *counts = new size_t[keyCount]();     // create counter array
    // 1° count
    for (size_t i = 0; i < numWords; i++)
        counts[getKey(from + i, position)]++;
    // 2° cumulate
    for (size_t i = 1; i < keyCount; i++)
        counts[i] += counts[i - 1];
    // 3° place elements
    for (size_t i = numWords; i-- > 0;)
    {
        auto key = getKey(from + i, position);
        counts[key]--;
        to[counts[key]] = from[i];
    }
    delete[] counts; // free memory
}

// 1° method: sort on each character from last to first
void sort_1(word_t words[], const size_t numWords)
{
    word_t *w1 = new word_t[numWords]; // create working array
    word_t *w2 = words;
    for (size_t position = MAX_WORD_LENGTH; position-- > 0;)
    {
        sort_1_on(w2, w1, numWords, position);
        swap(w1, w2);
    }
    if (MAX_WORD_LENGTH % 2 != 0)
    {
        copyArray(w2, words, numWords); // copy into words
        delete[] w2;                    // free memory
    }
    else
        delete[] w1; // free memory
}

// helper for 2° method: sort on given character
void sort_2_range_onOld(word_t from[], word_t to[], const size_t begin, const size_t end, const size_t position, const size_t maxPosition)
{
    if (end - begin > 1) // at least 2 elements...
    {
        size_t keyCount = getKey(nullptr, position) + 1; // get number of key values + 1 for total
        size_t *counts = new size_t[keyCount]();         // create counter array
        // 1° count
        for (size_t i = begin; i < end; i++)
            counts[getKey(from + i, position)]++;
        // 2° cumulate + adapt
        counts[0] = begin;
        for (size_t i = 1; i < keyCount; i++)
            counts[i] += counts[i - 1];
        // 3° place elements
        for (size_t i = end; i-- > begin;)
        {
            auto key = getKey(from + i, position);
            counts[key]--;
            to[counts[key]] = from[i];
        }
        // 4° copy back
        copyArray(to + begin, from + begin, end - begin);
        if (position < maxPosition)
            for (size_t i = 0; i < keyCount - 1; i++)
                sort_2_range_onOld(from, to, counts[i], counts[i + 1], position + 1, maxPosition);
        delete[] counts; // free memory
    }
}

// helper for 2° method: sort on given character
void sort_2_range_on(word_t from[], word_t to[], const size_t dim, const size_t position, const size_t maxPosition)
{
    if (dim > 1) // at least 2 elements...
    {
        size_t keyCount = getKey(nullptr, position) + 1; // get number of key values + 1 for total
        size_t *counts = new size_t[keyCount]();         // create counter array
        // 1° count
        for (size_t i = 0; i < dim; i++)
            counts[getKey(from + i, position)]++;
        // 2° cumulate + adapt
        for (size_t i = 1; i < keyCount; i++)
            counts[i] += counts[i - 1];
        // 3° place elements
        for (size_t i = dim; i-- > 0;)
        {
            auto key = getKey(from + i, position);
            counts[key]--;
            to[counts[key]] = from[i];
        }
        // 4° copy back
        copyArray(to, from, dim);
        if (position < maxPosition)
            for (size_t i = 0; i < keyCount - 1; i++)
            {
                size_t dim = counts[i + 1] - counts[i];
                if (dim > 1)
                    sort_2_range_on(from + counts[i], to, dim, position + 1, maxPosition);
            }
        delete[] counts; // free memory
    }
}

// 2° method: sort on first character, then sort each group on second, ..., then sort each group on last character
void sort_2(word_t words[], const size_t numWords)
{
    word_t *w1 = new word_t[numWords]; // create working array
    // sort_2_range_onOld(words, w1, 0, numWords, 0, MAX_WORD_LENGTH - 1);
    sort_2_range_on(words, w1, numWords, 0, MAX_WORD_LENGTH - 1);
    delete[] w1; // free memory
}

// helper for 3° method: sort on given character
void sort_3_on(const word_t *from, word_t *to, const size_t numWords, const size_t position)
{
    size_t keyCount = getKey(nullptr, position); // get number of key values
    size_t *counts = new size_t[keyCount]();     // create counter array
    // 1° count
    for (const word_t *w = from, *limit = from + numWords; w != limit; w++)
        counts[getKey(w, position)]++;
    // 2° cumulate
    for (size_t i = 1; i < keyCount; i++)
        counts[i] += counts[i - 1];
    // 3° place elements
    for (const word_t *limit = from, *w = from + numWords; w-- != limit;)
    {
        auto key = getKey(w, position);
        counts[key]--;
        to[counts[key]] = *w;
    }
    delete[] counts; // free memory
}

// 3° method: sort on each character from last to first using pointer arithmetic
void sort_3(word_t words[], const size_t numWords)
{
    word_t *w1 = new word_t[numWords]; // create working array
    word_t *w2 = words;
    for (size_t position = MAX_WORD_LENGTH; position-- > 0;)
    {
        sort_3_on(w2, w1, numWords, position);
        swap(w1, w2);
    }
    if (MAX_WORD_LENGTH % 2 != 0)
    {
        copyArray(w2, words, numWords); // copy into words
        delete[] w2;                    // free memory
    }
    else
        delete[] w1; // free memory
}
