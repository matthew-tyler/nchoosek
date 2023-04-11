#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
A version of the factorial formula from here:
https://en.wikipedia.org/wiki/Binomial_coefficient#Factorial_formula
*/
int64_t factorial(int n, int k)
{
}

/*
A version of the multiplicitave formula as shown on the wikipedia:
https://en.wikipedia.org/wiki/Binomial_coefficient#Multiplicative_formula
 */
int64_t multiplicative(int n, int k)
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
    int64_t result = 1;

    for (int i = 1; i <= k; i++)
    {
        result = result * (n - i + 1) / i;
    }

    return result;
}

int main(int argc, char const *argv[])
{

    int64_t test = multiplicative(10, 7);

    printf("%ld\n", test);

    return 0;
}
