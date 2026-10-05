/*
Author: Oscar Egan
Date: 3/10/2026
Purpose: Calculates powers of any number in any modular number system
*/

#include <stdio.h>
#include <stdlib.h>

int binary(int pow, int base, int mod);
long powerOf(long base, long exponent);
int recAlg(int arr[], int base, int exponent, int mod, int size);
long modCalc(long num, long mod);
int modCalcRec(long base, long exponent, long numInMod, long mod, long pow);
void main()
{

    int base;
    int exponent;
    int mod;

    printf("\nEnter your base ");
    scanf("%d", &base);
    printf("\nEnter your exponent ");
    scanf("%d", &exponent);
    printf("\nEnter your mod ");
    scanf("%d", &mod);

    binary(exponent, base, mod);
}
long powerOf(long base, long exponent)//function that calculates powers
{
    long i;
    long ans = 1;
    for (i = 0; i < exponent; i++)
    {
        ans *= base;
    }
    return ans;
}
int modCalcRec(long base, long exponent, long numInMod, long mod, long pow)//recursive algorith that prints each line of recursion, breaks down incomputibally large powers into more workable numbers.
{
    printf("\n%ld^%ld = %ld (mod %ld)", base, pow, numInMod, mod);
    pow *= 2;//increases power after every reccurence
    if ((pow <= exponent))//condition for reccurence
    {
        return modCalcRec(base, exponent, modCalc(numInMod * numInMod, mod), mod, pow);//calculates new power for the next run of the algorithm
    }
    else
    {
        return(numInMod);//if the pow and exponent are equal then the algorith returns the answer. Exponent is the original exponent entered by the user and pow is the new exponent for each recurrence of the algorithm.
    }
}
long modCalc(long num, long mod)
{
    int ans;
    ans = num - (num / mod) * mod;
    return ans;
}
int recAlg(int arr[], int base, int exponent, int mod, int size)
{
    int i = 0;
    int j = 0;
    // printf("\n%d^%d=", base, exponent);
    // modCalcRec(base, arr[i], mod, 1);
    long first = modCalc(base, mod);//f
    int *returnedValues = calloc(size, sizeof(int)); // for collecting values returned from the recurring algorithm
    for (i = 0; i < size; i++)
    {
        returnedValues[i] = modCalcRec(base, arr[i], first, mod, 1);//sends the base, current result of binary (calculated from each relevant power of 2), the first answer of the equation, the mod, and first exponent.
    }
    int ans = 1;
    for (i = 0; i < size; i++)
    {
        ans = modCalc(ans * returnedValues[i], mod);   // reduce after every multiply
    }
    printf("\nThe Answer is %d", modCalc(ans, mod));
}
int binary(int pow, int base, int mod)// converts decimal to binary and adds each digit to an array
{

    int i = 0;
    int count = 0;
    int temp = pow;
    int store = pow;
    int oneCounter = 0;//for counting how many digits in the binary are a 1 values
    do//finds how many digits of binary the decimal number is and thus how long the array is required to be
    {
        count++;
        temp /= 2;
    } while (temp > 0);

    // printf("\n%d\n", count);
    int *binaryDigits = calloc(count, sizeof(int)); // array to store each digit of the decimal's binary
    for (i = 0; i < count; i++)
    {
        binaryDigits[count - 1 - i] = pow % 2; // storing from end of array forwards as this method of calculating binary is reversed
        if (pow % 2 != 0)
        { // for later array size
            oneCounter++;
        }
        pow /= 2;
    }
    int *binaryResults = calloc(oneCounter, sizeof(int)); // initialize array for the relevant powers of 2
    int j = 0;

    for (i = 0; i < count; i++)
    { // calculate relevant powers of 2
        if (binaryDigits[i] == 1)
        {
            binaryResults[j] = powerOf(2, (count - i) - 1); // passes 2 and the relevant power into a function that calculates powers, enters into array for storing
            j++;
        }
    }
    recAlg(binaryResults, base, store, mod, oneCounter); // parse the new array, base, exponent, mod, and array length to next function
};