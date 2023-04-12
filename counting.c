#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

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

        // if (result / i > ULONG_MAX / n)
        // {

        //     //  result = result * (n - i + 1) / i;

        //     printf("test\n");
        //     continue;
        // }
        result = result * simplify_division(n + 1, i);
        n--;
        // result = result / i * n + result % i * n / i;
        // n--;
    }

    return result;
}

uint64_t factorising(int n, int k)
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

    uint64_t *numerator = malloc(sizeof(uint64_t) * (n - 1));
    uint64_t *denominator = malloc(sizeof(uint64_t) * (k - 1));
}

int main(int argc, char const *argv[])
{

    char inputBuffer[100];
    int n;
    int k;

    // 80 59

    while (fgets(inputBuffer, sizeof(inputBuffer), stdin))
    {
        if (sscanf(inputBuffer, "%d %d", &n, &k) == 2)
        {
            uint64_t test = ch(n, k);

            // uint64_t test = choose(n, k);
            printf("%ld\n", test);
        }
    }

    return 0;
}
