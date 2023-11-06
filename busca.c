#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numeroRepetido(int array[], int sizeArray, int numero)
{
    for (int i = 0; i < sizeArray; i++)
    {
        if (array[i] == numero)
            return 1;
    }
    return 0;
}

int gerarNumAleatorios(int *array, int sizeArray)
{
    for (int i = 0; i < sizeArray; i++)
    {
        int num = 0;
        do
        {
            num = abs(rand() % (sizeArray * 2 + 1));

        } while (numeroRepetido(array, sizeArray, num));

        array[i] = num;
    }
}

int buscaLinear(int *array, int sizeArray, int numero)
{
    for (int i = 0; i < sizeArray; i++)
    {
        if (array[i] == numero)
        {
            return i;
        }
    }
    return -1;
}

int buscaSentinela(int *array, int sizeArray, int numero)
{
    int ultimoElemento = array[sizeArray - 1];
    array[sizeArray - 1] = numero;

    int i = 0;
    while (array[i] != numero)
    {
        i++;
    }

    if ((i < sizeArray - 1) || (ultimoElemento == numero))
    {
        return i;
    }
    return -1;
}

void ordenar(int *array, int sizeArray)
{
    for (int i = 1; i < sizeArray; i++)
    {
        int chave = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > chave)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = chave;
    }
}

int buscaBinaria(int *array, int sizeArray, int numero)
{
    int inicio = 0;
    int fim = sizeArray - 1;

    while (inicio <= fim)
    {
        int meio = inicio + (fim - inicio) / 2;

        if (array[meio] == numero)
        {
            return meio;
        }
        if (array[meio] < numero)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }
    return -1;
}
int main(void)
{
    srand(time(NULL));
    int qntNumeros = 0;

    printf("\nDigite quantos números deseja gerar: ");
    scanf("%d", &qntNumeros);


    int *array = (int *)malloc(qntNumeros * sizeof(int));

    gerarNumAleatorios(array, qntNumeros);
    ordenar(array, qntNumeros);
    for (int i = 0; i < qntNumeros; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    FILE *outputFile = fopen("resultadosBuscas.txt", "w"); // Abre o arquivo para escrita

    if (outputFile == NULL)
    {
        perror("Erro ao abrir o arquivo resultados.txt");
        return 1;
    }

    clock_t inicio, fim;

    printf("\nNúmero que deseja buscar: ");
    int numBusca;
    scanf("%d", &numBusca);

    inicio = clock();
    int resultadoLinear = buscaLinear(array, qntNumeros, numBusca);
    fim = clock();
    fprintf(outputFile, "Tempo de Busca Linear: %lu ticks de clock - Tempo tomado: %f\n", (long)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    int resultadoSentinela = buscaSentinela(array, qntNumeros, numBusca);
    fim = clock();
    fprintf(outputFile, "Tempo de Busca Sentinela: %lu ticks de clock - Tempo tomado: %f\n", (long)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    inicio = clock();
    int resultadoBinario = buscaBinaria(array, qntNumeros, numBusca);
    fim = clock();
    fprintf(outputFile, "Tempo de Busca Binária: %lu ticks de clock - Tempo tomado: %f\n", (long)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    fprintf(outputFile, "\nIndex do número digitado (Busca Linear): %d\n", resultadoLinear);
    fprintf(outputFile, "Index do número digitado (Busca Linear Sentinela): %d\n", resultadoSentinela);
    fprintf(outputFile, "Index do número digitado (Busca Binária): %d\n\n", resultadoBinario);

    fclose(outputFile); // Fecha o arquivo após o uso
    free(array);
    return 0;
}