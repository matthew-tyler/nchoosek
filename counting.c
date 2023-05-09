#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>


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
