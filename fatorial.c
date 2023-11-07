#include <stdio.h>

unsigned long long int fatorialIterativo(int n)
{
    unsigned long long result = 1;
    for (int i = n; i > 0; i--)
    {
        result *= i;
    }
    return result;
}

unsigned long long int fatorialRecursivo(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return fatorialRecursivo(n - 1) * n;
    }
}

int main()
{
    int n;
    printf("\nInforme o valor de n: ");
    scanf("%d", &n);
    printf("\nFatorial recursivo de n = %d: %llu\n", n, fatorialRecursivo(n));
    printf("Fatorial iterativo de n = %d: %llu\n\n", n, fatorialIterativo(n));
}