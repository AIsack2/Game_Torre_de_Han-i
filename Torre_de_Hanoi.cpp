#include <stdio.h> // Biblioteca de funções principais (printf, scanf, puts, etc)
#include <stdlib.h> // Bibliotaca para manipulação de memória
#include <locale.h> // Biblioteca para usar acentuação
#include <math.h> // Biblioteca para cálculo matemático
#include <ctype.h> // Biblioteca para usar a função topper

// Declarações de funções
void imprimirTorre(const char *nome, int tamanho, int *vetor);
void mudarDeTorre(int *vetorOrigem, int *vetorDestino, int tamanho);
void jogo(int tamanho, int jogadasMax);

int main() {
    setlocale(LC_ALL, "Portuguese");

    int option, tamanho, jogadasMax;

    printf("Defina o nível da sua Torre de Hanoi:\n");
    printf("1. Fácil - 3 pinos\n");
    printf("2. Médio - 4 pinos\n");
    printf("3. Difícil - 5 pinos\n");
    printf("4. Personalizado - escolha o número de pinos\n");
    scanf(" %d", &option);

    // Configura o tamanho da torre e as jogadas máximas
    switch (option) {
        case 1:
            tamanho = 3;
            break;
        case 2:
            tamanho = 4;
            break;
        case 3:
            tamanho = 5;
            break;
        case 4:
            printf("Digite o número de pinos desejado: ");
            scanf("%d", &tamanho);
            if (tamanho < 3) {
                printf("Número de pinos deve ser pelo menos 3!\n");
                return 1;
            }
            break;
        default:
            printf("Opção inválida!\n");
            return 1;
    }

    // Calcula o número máximo de jogadas permitidas: (2^n) - 1
    jogadasMax = (int)pow(2, tamanho) - 1;
    jogo(tamanho, jogadasMax);

    return 0;
}

// Função para imprimir o estado de uma torre
void imprimirTorre(const char *nome, int tamanho, int *vetor) {
    printf("Torre %s:\n", nome);
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] != 0)
            printf("  %d\n", vetor[i]);
        else
            printf("  -\n");
    }
}

// Função para mover um disco de uma torre para outra
void mudarDeTorre(int *vetorOrigem, int *vetorDestino, int tamanho) {
    int topoOrigem = -1, topoDestino = -1;

    // Encontrar o disco no topo da torre de origem
    for (int i = 0; i < tamanho; i++) {
        if (vetorOrigem[i] != 0) {
            topoOrigem = i;
            break;
        }
    }

    // Encontrar a posição disponível na base da torre de destino
    for (int i = tamanho - 1; i >= 0; i--) {
        if (vetorDestino[i] == 0) {
            topoDestino = i;
            break;
        }
    }

    if (topoOrigem == -1) {
        printf("Movimento inválido: Torre de origem está vazia\n");
        return;
    }

    if (topoDestino == tamanho - 1 || vetorOrigem[topoOrigem] < vetorDestino[topoDestino + 1]) {
        // Realizar o movimento
        vetorDestino[topoDestino] = vetorOrigem[topoOrigem];
        vetorOrigem[topoOrigem] = 0;
        printf("Movimento realizado: %d movido\n", vetorDestino[topoDestino]);
    } else {
        printf("Movimento inválido: Disco maior sobre disco menor\n");
    }
}

// Função principal do jogo
void jogo(int tamanho, int jogadasMax) {
    // Alocação dinâmica dos vetores que representam as torres
    int *pinoA = (int *)malloc(tamanho * sizeof(int));
    int *pinoB = (int *)calloc(tamanho, sizeof(int));
    int *pinoC = (int *)calloc(tamanho, sizeof(int));

    // Inicializa a torre A com os discos e as demais torres vazias
    for (int i = 0; i < tamanho; i++) {
        pinoA[i] = i + 1;
   
    }

    char partida, destino;
    printf("Desafio das Torres de Hanoi\n");

    // Imprime o estado inicial das torres
    imprimirTorre("A", tamanho, pinoA);
    imprimirTorre("B", tamanho, pinoB);
    imprimirTorre("C", tamanho, pinoC);

    while (jogadasMax > 0) {
        printf("Jogadas restantes: %d\n", jogadasMax);
        printf("Digite o pino de partida (A/B/C): ");
        scanf(" %c", &partida);
        printf("Digite o pino de destino (A/B/C): ");
        scanf(" %c", &destino);

        // Normaliza a entrada para letras maiúsculas
        partida = toupper(partida);
        destino = toupper(destino);

        // Realiza o movimento de acordo com a entrada do usuário
        if (partida == 'A' && destino == 'B') {
            mudarDeTorre(pinoA, pinoB, tamanho);
        } else if (partida == 'A' && destino == 'C') {
            mudarDeTorre(pinoA, pinoC, tamanho);
        } else if (partida == 'B' && destino == 'A') {
            mudarDeTorre(pinoB, pinoA, tamanho);
        } else if (partida == 'B' && destino == 'C') {
            mudarDeTorre(pinoB, pinoC, tamanho);
        } else if (partida == 'C' && destino == 'A') {
            mudarDeTorre(pinoC, pinoA, tamanho);
        } else if (partida == 'C' && destino == 'B') {
            mudarDeTorre(pinoC, pinoB, tamanho);
        } else {
            printf("Movimento inválido!\n");
            continue;
        }

        // Imprime o estado atualizado das torres
        printf("\nEstado das Torres:\n");
        imprimirTorre("A", tamanho, pinoA);
        imprimirTorre("B", tamanho, pinoB);
        imprimirTorre("C", tamanho, pinoC);

        jogadasMax--;

        // Verifica a condição de vitória: se todos os discos estão na torre B ou C
        int vitoria = 1;
        for (int i = 0; i < tamanho; i++) {
            if (pinoB[i] != i + 1 && pinoC[i] != i + 1) {
                vitoria = 0;
                break;
            }
        }

        if (vitoria) {
            printf("Parabéns! Você resolveu o desafio das Torres de Hanoi!\n");
            break;
        }

        if (jogadasMax == 0) {
            printf("Você atingiu o número máximo de jogadas!\n");
        }
    }

    // Libera a memória alocada dinamicamente
    free(pinoA);
    free(pinoB);
    free(pinoC);
}
