#include <cstdio>
#include <cstring>

#define SIZE 2000000
#define SHIFT 1000


unsigned incr(char number[], unsigned offset)
{
    bool ret = false;

    do
    {
        ret = false;
        if (number[offset] == '9')
        {
            ret = true;
            number[offset--] = '0';
        }
        else
            ++number[offset];
    } while (ret);

    return offset;
}

unsigned nextPalindrome(char notShifted[], char number[], unsigned shift)
{
    unsigned len = strlen(number) - 1;
    unsigned i = 0, overflow = 0;

    // printf("step : (shift == %u, ptr == %p) %s\n", shift, number, number);

    // Add one to the number because we want a palindrom
    // bigger than initial number
    if (shift == SHIFT)
    {
       // printf("incr\n");
        overflow += (incr(notShifted, len + shift) < shift ? 1 : 0);
        if (overflow)
            return overflow;
    }

    // printf("len : %u\n", len);
    while (i < len)
    {
         //printf("i : %u\n", i);
        if (number[len - i] > number[i])
        {
            overflow += (incr(notShifted, len - i - 1 + shift) < shift ? 1 : 0);
            if (overflow)
                return overflow;
        }
        number[len - i] = number[i];
        ++i;
    }

    return overflow;
}

int main()
{
    char number[SIZE + SHIFT + 1];
    unsigned t, overflow, shift;

    scanf("%u", &t);
    while (t--)
    {
        shift = SHIFT;
        overflow = 0;
        memset(number, '0', SIZE + SHIFT + 1);
        scanf("%s", number + shift);

        // Eliminate leading zeros
        while (number[shift] == '0')
            ++shift;

        // Solution
        while ((overflow = nextPalindrome(number, number + shift, shift)))
            --shift;

        // print solution
        printf("%s\n", number + shift);
    }
}
