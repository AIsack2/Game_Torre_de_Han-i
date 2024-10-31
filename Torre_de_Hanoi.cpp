#include <stdio.h>
#include <locale.h>

void Imprimir_torre(const char* nome, int vetor[3]) {
    printf("Torre %s:\n", nome);
    for (int i = 2; i >= 0; i--) {  
        if (vetor[i] != 0)
            printf("  %d\n", vetor[i]);
        else
            printf("  -\n");
    }
}

void Mudar_de_torre(int vetorA[3], int vetorB[3]) {
    int topoA = -1, topoB = -1;

    // Encontrar o disco no topo da torre de partida 
    for (int i = 2; i >= 0; i--) {
        if (vetorA[i] != 0) {
            topoA = i;  
            break;
        }
    }

    // Encontrar a posição disponível na base da torre de destino 
    for (int i = 0; i < 3; i++) {
        if (vetorB[i] == 0) {
            topoB = i;  
            break;
        }
    }
    
    // Verificar o disco no topo da torre de destino
    int anterior = 0;  
    if (topoB > -1) {  
        anterior = vetorB[topoB - 1];  
    }

    // Verifica se o movimento é válido antes de realizá-lo
    if (topoA != -1 && (anterior == 0 || vetorA[topoA] < anterior)) {
        vetorB[topoB] = vetorA[topoA];
        vetorA[topoA] = 0;
    } else {
        printf("Movimento inválido!\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int pinoA[3] = {3, 2, 1};  
    int pinoB[3] = {0, 0, 0};
    int pinoC[3] = {0, 0, 0};
    char partida, destino;

    printf("Desafio das Torres de Hanoi\n");
    
    Imprimir_torre("A", pinoA);
    Imprimir_torre("B", pinoB);
    Imprimir_torre("C", pinoC);

    int qtd_jogadas = 100; //Limitei a quantidade de jogas em 100, mas essa variável pode servir de contador, dando ao jogador uma quantidade mínima de lances.
    while (qtd_jogadas > 0) {
        printf("Digite o pino de partida (A/B/C): ");
        scanf(" %c", &partida);

        printf("Digite o pino de destino (A/B/C): ");
        scanf(" %c", &destino);

        if (partida == 'A' && destino == 'B') {
            Mudar_de_torre(pinoA, pinoB);
        } else if (partida == 'A' && destino == 'C') {
            Mudar_de_torre(pinoA, pinoC);
        } else if (partida == 'B' && destino == 'A') {
            Mudar_de_torre(pinoB, pinoA);
        } else if (partida == 'B' && destino == 'C') {
            Mudar_de_torre(pinoB, pinoC);
        } else if (partida == 'C' && destino == 'A') {
            Mudar_de_torre(pinoC, pinoA);
        } else if (partida == 'C' && destino == 'B') {
            Mudar_de_torre(pinoC, pinoB);
        } else {
            printf("Movimento inválido!\n");
            continue;
        }

        printf("\nEstado das Torres:\n");
        Imprimir_torre("A", pinoA);
        Imprimir_torre("B", pinoB);
        Imprimir_torre("C", pinoC);

        qtd_jogadas--;

        // Verificar condição de vitória
        if (((pinoC[0] == 3) && (pinoC[1] == 2) && (pinoC[2] == 1)) || ((pinoB[0] == 3) && (pinoB[1] == 2) && (pinoB[2] == 1))) {
            printf("Parabéns! Você resolveu o desafio das Torres de Hanoi!\n");
            break;
        }
    }

    return 0;
}

