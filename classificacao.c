#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void troca(int vet[], int i, int j)
{
    int aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

int particiona(int vet[], int inicio, int fim)
{
    int pivo = vet[fim];
    int pivoIndice = inicio;

    for (int i = inicio; i < fim; i++)
    {
        if (vet[i] <= pivo)
        {
            troca(vet, i, pivoIndice);
            pivoIndice++;
        }
    }

    troca(vet, pivoIndice, fim);
    return pivoIndice;
}

int particionaRandom(int vet[], int inicio, int fim)
{
    int pivoIndice = (rand() % (fim - inicio + 1)) + inicio;
    troca(vet, pivoIndice, fim);
    return particiona(vet, inicio, fim);
}

void quickSort(int vet[], int inicio, int fim)
{
    if (inicio < fim)
    {
        int pivoIndice = particionaRandom(vet, inicio, fim);
        quickSort(vet, inicio, pivoIndice - 1);
        quickSort(vet, pivoIndice + 1, fim);
    }
}

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        troca(arr, i, minIndex);
    }
}

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                troca(arr, j, j + 1);
            }
        }
    }
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void imprimirResultado(char *nomeAlgoritmo, int n, clock_t inicio, clock_t fim)
{
    FILE *arquivo = fopen("resultadoClassificacao.txt", "a");

    if (arquivo == NULL)
    {
        // Exibe uma mensagem de erro e encerra o programa
        printf("\nErro ao abrir o arquivo!\n");
        exit(1);
    }

    fprintf(arquivo, "%s para n = %d: %ld ticks de clock - Tempo tomado: %f\n\n", nomeAlgoritmo, n, (long)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));
    printf("%s para n = %d: %ld ticks de clock - Tempo tomado: %f\n", nomeAlgoritmo, n, (long)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    fclose(arquivo);
}

void executarAlgoritmo(char *nomeAlgoritmo, void (*algoritmo)(int[], int), int n)
{
    int *vetor = (int *)malloc(n * sizeof(int));

    for (int j = 0; j < n; j++)
    {
        vetor[j] = rand();
    }

    clock_t inicio = clock();
    algoritmo(vetor, n);
    clock_t fim = clock();

    imprimirResultado(nomeAlgoritmo, n, inicio, fim);

    free(vetor);
}

// Função específica para o Quick Sort
void executarQuickSort(char *nomeAlgoritmo, void (*algoritmo)(int[], int, int), int n)
{
    int *vetor = (int *)malloc(n * sizeof(int));

    for (int j = 0; j < n; j++)
    {
        vetor[j] = rand();
    }

    clock_t inicio = clock();
    algoritmo(vetor, 0, n - 1);
    clock_t fim = clock();

    imprimirResultado(nomeAlgoritmo, n, inicio, fim);

    free(vetor);
}

int main()
{
    int tamanhos[] = {10000, 30000, 50000, 70000, 100000};

    printf("-----------------------------------------------------\n");
    printf("       Comparação algoritmos de classificação\n");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < sizeof(tamanhos) / sizeof(tamanhos[0]); i++)
    {
        int n = tamanhos[i];

        executarAlgoritmo("Selection Sort", selectionSort, n);
        executarAlgoritmo("Bubble Sort", bubbleSort, n);
        executarAlgoritmo("Insertion Sort", insertionSort, n);
        executarQuickSort("Quick Sort", quickSort, n);

        printf("-----------------------------------------------------\n\n");
    }

    return 0;
}
