#include <stdio.h>

// Função para calcular o soatório de 1 até n, ultilizando o modo iterativo
unsigned long long somatorioIterativo(int n)
{
    unsigned long long soma = 0;

    // Loop para iterar de n até 1 e armazenar o resultado na variável soma
    for (int i = n; i > 0; i--)
    {
        soma += i;
    }
    return soma;
}

// Funçção apa calcular o soatório de 1 até n, ultilizando recursão
unsigned long long somatorioRecursivo(int n)
{
    if (n == 0) /// Definindo caso base
        return 0;
    else
    {
        return somatorioRecursivo(n - 1) + n;
    }
}

int main()
{
    int n;
    printf("\nInforme o valo de n: ");
    scanf("%d", &n);
    printf("\nO somatório iterativo de n = %d até 1 é: %llu\n", n, somatorioIterativo(n));
    printf("O somatório recursivo de n = %d até 1 é: %llu\n\n", n, somatorioRecursivo(n));
    return 0;
}