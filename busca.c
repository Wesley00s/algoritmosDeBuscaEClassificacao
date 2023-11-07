#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para verificar se um número já existe no array
int numeroRepetido(int array[], int sizeArray, int numero)
{
    for (int i = 0; i < sizeArray; i++)
    {
        if (array[i] == numero)
            return 1; // Retorna 1 se o número já existe no array
    }
    return 0; // Retorna 0 se o número não existe no array
}

// Função para gerar números aleatórios únicos e armazená-los no array
int gerarNumAleatorios(int *array, int sizeArray)
{
    for (int i = 0; i < sizeArray; i++)
    {
        int num = 0;

        // Loop do-while garante que o número gerado seja único no array
        do
        {
            // Gera um número aleatório no intervalo [0, sizeArray * 2]
            num = abs(rand() % (sizeArray * 2 + 1));

        } while (numeroRepetido(array, sizeArray, num)); // Verifica se o número já existe no array

        array[i] = num; // Armazena o número no array
    }
}
// Busca linear no array para encontrar a posição do número desejado
int buscaLinear(int *array, int sizeArray, int numero)
{
    // Loop para percorrer o array
    for (int i = 0; i < sizeArray; i++)
    {
        if (array[i] == numero)
        {
            return i; // Retorna o índice se o número for encontrado
        }
    }
    return -1; // Retorna -1 se o número não for encontrado
}

// Busca sentinela otimizada no array para encontrar a posição do número desejado
int buscaSentinela(int *array, int sizeArray, int numero)
{
    // Salva o último elemento do array e substitui-o pelo número desejado
    int ultimoElemento = array[sizeArray - 1];
    array[sizeArray - 1] = numero;

    int i = 0;
    // Percorre o array até encontrar o número desejado
    while (array[i] != numero)
    {
        i++;
    }

    // Verifica se o número foi encontrado no array
    if ((i < sizeArray - 1) || (ultimoElemento == numero))
    {
        return i; // Retorna o índice se o número for encontrado
    }
    return -1; // Retorna -1 se o número não for encontrado
}

// Função para ordenar o array usando o algoritmo de ordenação de inserção
void ordenar(int *array, int sizeArray)
{
    // Percorre o array a partir do segundo elemento
    for (int i = 1; i < sizeArray; i++)
    {
        int chave = array[i]; // Armazena o valor atual a ser comparado
        int j = i - 1;        // Inicializa o índice anterior ao valor atual

        // Move os elementos maiores que a chave para a direita
        // até encontrar a posição correta para inserir a chave
        while (j >= 0 && array[j] > chave)
        {
            array[j + 1] = array[j]; // Desloca o elemento para a direita
            j = j - 1;               // Atualiza o índice para verificar o próximo elemento
        }

        array[j + 1] = chave; // Insere a chave na posição correta
    }
}

// Busca binária em um array ordenado para encontrar a posição do número desejado
int buscaBinaria(int *array, int sizeArray, int numero)
{
    int inicio = 0;          // Índice inicial do array
    int fim = sizeArray - 1; // Índice final do array

    // Loop enquanto o intervalo de busca não estiver vazio
    while (inicio <= fim)
    {
        // Calcula o índice do elemento do meio do intervalo
        int meio = inicio + (fim - inicio) / 2;

        // Verifica se o número desejado está no meio do intervalo
        if (array[meio] == numero)
        {
            return meio; // Retorna o índice se o número for encontrado
        }

        // Se o número desejado for maior, restringe a busca para a metade direita do intervalo
        if (array[meio] < numero)
        {
            inicio = meio + 1;
        }
        // Se o número desejado for menor, restringe a busca para a metade esquerda do intervalo
        else
        {
            fim = meio - 1;
        }
    }

    // Retorna -1 se o número não for encontrado no array
    return -1;
}

int main(void)
{
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com o tempo atual

    int qntNumeros = 0;

    printf("\nDigite quantos números deseja gerar: ");
    scanf("%d", &qntNumeros);

    int *array = (int *)malloc(qntNumeros * sizeof(int)); // Aloca dinamicamente espaço para o array

    gerarNumAleatorios(array, qntNumeros); // Gera números aleatórios únicos
    ordenar(array, qntNumeros);            // Ordena o array em ordem crescente

    // Imprime os números gerados e ordenados
    printf("\nNúmeros gerados e ordenados: ");
    for (int i = 0; i < qntNumeros; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Abre o arquivo para escrita
    FILE *outputFile = fopen("resultadosBuscas.txt", "w");

    if (outputFile == NULL)
    {
        perror("Erro ao abrir o arquivo resultadosBuscas.txt");
        return 1;
    }

    clock_t inicio, fim;

    // Solicita o número que deseja buscar
    printf("\nNúmero que deseja buscar: ");
    int numBusca;
    scanf("%d", &numBusca);

    // Busca Linear
    inicio = clock();
    int resultadoLinear = buscaLinear(array, qntNumeros, numBusca);
    fim = clock();
    fprintf(outputFile, "Tempo de Busca Linear: %lu ticks de clock - Tempo tomado: %f\n", (long)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    // Busca Sentinela
    inicio = clock();
    int resultadoSentinela = buscaSentinela(array, qntNumeros, numBusca);
    fim = clock();
    fprintf(outputFile, "Tempo de Busca Sentinela: %lu ticks de clock - Tempo tomado: %f\n", (long)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    // Busca Binária
    inicio = clock();
    int resultadoBinario = buscaBinaria(array, qntNumeros, numBusca);
    fim = clock();
    fprintf(outputFile, "Tempo de Busca Binária: %lu ticks de clock - Tempo tomado: %f\n", (long)(fim - inicio), (double)((fim - inicio) / CLOCKS_PER_SEC));

    // Escreve os resultados no arquivo
    fprintf(outputFile, "\nIndex do número digitado (Busca Linear): %d\n", resultadoLinear);
    fprintf(outputFile, "Index do número digitado (Busca Linear Sentinela): %d\n", resultadoSentinela);
    fprintf(outputFile, "Index do número digitado (Busca Binária): %d\n\n", resultadoBinario);

    fclose(outputFile); // Fecha o arquivo após o uso
    free(array);        // Libera a memória alocada dinamicamente

    return 0;
}