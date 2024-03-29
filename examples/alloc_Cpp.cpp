/**
 * Purpose: massima dimensione per allocazione dinamica della memoria
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:    tecnica "dicotomica" in [0..SIZE_MAX)
 */

#include <cstdio>
#include <cstdint>
// malloc
#include <cstdlib>

#define DEBUG 1
// char x[30'333'206'527LL];

void debug(const char *format, size_t data)
{
    if (DEBUG)
    {
        printf(format, data);
    }
}
// try to allocate and use size bytes of uninitialized memory
// returns number of usage failures, -1 on allocation failure
size_t test(size_t size)
{
    // char *a = (char *)malloc(size); // try uninitialized allocation
    // char *a = (char *)calloc(size, sizeof(char)); // try initialized allocation
    char *a = (char *)realloc(nullptr, size); // try initialized allocation
    if (a != nullptr)                         // check success / failure
    {
        debug("Successfully allocated %zu bytes. Testing ...", size);
        size_t nErrors = 0; // numer of errors so far
                            // check usability setting / getting some bytes
        for (size_t index = size - 1; index > 0; index >>= 1)
        {
            a[index] = 42;
            if (a[index] != 42)
            {
                if (nErrors++ == 0)
                {
                    debug("Error for a[%zu]", index);
                }
            }
        }
        debug(nErrors == 0 ? "success\n" : " failure [%zu errors]\n", nErrors);
        free(a); // free allocated memory
        return nErrors;
    }
    else
    {
        debug("Unable to allocate %zu bytes.\n", size);
        return -1;
    }
}

int main(int argc, char *argv[])
{
    // x[0] = 'a';
    // printf("%c\n", x[0]);
    debug("SIZE_MAX = %zu\n", SIZE_MAX); // maximum value of a size_t
    // find minimum size we can NOT allocate
    // search in [0..SIZE_MAX)
    size_t begin = 0, end = SIZE_MAX;
    size_t count = end - begin;
    while (count > 0)
    {
        size_t step = count / 2;
        size_t middle = begin + step;
        if (test(middle) == 0) // success
        {
            begin = middle + 1; // search in [middle + 1..end)
            count -= step + 1;
        }
        else
        {
            count = step; // search in [begin..middle)
        }
    }
    printf("Maximum size successfully allocated: %zu bytes.\n", begin - 1);
    double *p = (double *)malloc(begin - 1);
    // while(true);
    free(p);
    // successful termination
    return 0;
}
