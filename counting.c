#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

/*
A version of the multiplicitave formula as shown on the wikipedia:
https://en.wikipedia.org/wiki/Binomial_coefficient#Multiplicative_formula
 */
uint64_t multiplicative(uint64_t n, uint64_t k)
{

    if (k < 0 || n == 0 || k > n)
    {
        return 0;
    }

    if (k == 0 || k == n)
    {
        return 1;
    }

    if ((n - k) < k)
    {
        k = (n - k);
    }
    uint64_t result = 1;

    for (uint64_t i = 1; i <= k; i++)
    {

        // n^k / k! = n(n-1)(n-2)...(n-(k-1)) / k(k-1)(k-2)...1
        // is equal to: for i to k product of  n + 1 - i / i
        //
        // Division can be applied before the multilication, however
        // that might produce a real number result. As the final number
        // is always an integer, we can account for the same oppration
        // on the remainder if there is one.
        result = ((result / i) * n) + (((result % i) * n) / i);
        n--;
    }

    return result;
}

int main(int argc, char const *argv[])
{

    char inputBuffer[1024];
    uint64_t n;
    uint64_t k;

    while (fgets(inputBuffer, sizeof(inputBuffer), stdin))
    {
        if (sscanf(inputBuffer, "%" SCNu64 "%" SCNu64, &n, &k) == 2)
        {
            uint64_t test = multiplicative(n, k);
            printf("%" PRIu64 "\n", test);
        }
    }

    return 0;
}
