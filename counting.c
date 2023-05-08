#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

/*
    A version of the multiplicative formula as found on wikipedia:
    https://en.wikipedia.org/wiki/Binomial_coefficient#In_programming_languages:~:text=Implementation%20in%20the%20C%20language%3A

    Now I know it's not that creative to just find an answer on Wikipedia and use that, but hear me out: why does this work?
    I can't find much reference to it online. No citation when posted. I have found solutions that use modulous, however they rely on
    a congruence relationship and so mod by large primes.

    So why does this work?

    Starting with the factorial implmenetation, we know for sure that this will overflow, even if the final answer may fit.

                  n!
    C(n, k) = -----------
              k! (n - k)!

    If we expand the factorials and cancel common terms we get the multiplicative formula.

               n (n - 1) (n - 2) ... (n - k + 1)
    C(n, k) = ---------------------------------
                  k (k - 1) (k - 2) ... 1


    If we express the numerator of n^k̲ as a falling factorial power we get a more effecient way of computing specific coeffecients:

                 k
               =====
    C(n, k) =   | |      n + 1 - i
               | |      -----------
              n = 1          i


    We can think about this in terms of pascal's triangle:



    0:									1
    1:								1		1
    2:							1		2		1
    3:						1		3		3		1
    4:					1		4		6		4		1
    5:				1		5		10		10		5		1
    6:			1		6		15		20		15		6		1
    7:		1 		7 		21		35		35		21		7 		1
    8:	1 		8 		28		56		70		56		28		8 		1


    We can see that C(n,k) is equal to taking the n'th row and the k'th element-1 from pascal's triangle.

    This means our formula is analagous to starting at row n and "walking in" k-1 times which gives us our answer.

    This also shows us why we can take advantage of the symmetry in the triangle, so C(n,k) = C(n, n - k).

    This however is still prone to overflows, largely due to our order of operations. Because we apply the multiplication first,
    we can overflow during the multiplication even though the division by i may result in an answer that is representable.

    Ideally we should do our division first, then multiply. This ensures we keep our intermediary values as small as possible.

                 /n\
                 \k/
    C(n, k) = --------- (n - k)
                k + 1


    This introduces a problem. Although we can guarentee that our numbers are ultimately integers after the multiplication is applied,
    the division itself can result in a real number. This has a straightforward solution, just use a datatype that supports real numbers,
    such as a double. This doesn't work for our purposes as we aren't meant to use anything but a 64bit integer, and as a double can represent fewer
    ints than a long.

    The other option is to stick to integer division and account for the remainder in a seperate step:

                  /n\                    /n\
                  \k/                  ( \k/ mod (k+1) ) (n-k)
    C(n, k) = (---------) (n - k) +  ------------------------
                 k + 1                         k + 1


    Here we achieve this by first doing the lefthand side, assuming integer division we will lose the precision on any division that has a remainder,
    This is dealt with on the righthand side by taking the mod of the division, scaling it by n and dividing by our term. Because our n choose k result
    must always be an integer, the righthand side will account for the multiplication of the remainder or be 0.


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
