#include <stdio.h>
#include <locale.h>

void Imprimir_torre(const char* nome, int tamanho, int vetor[]) {
    printf("Torre %s:\n", nome);
    
    for (int i = 0; i < tamanho; i++) {  
        if (vetor[i] != 0)
            printf("  %d\n", vetor[i]);
        else
            printf("  -\n");
    }
}

void Mudar_de_torre(int vetorA[], int vetorB[], int tamanho) {
    int topoA = -1, topoB = -1, vez = 1;

    // Encontrar o disco no topo da torre de partida 
    for (int i = 0; i < tamanho; i++) {
        if (vetorA[i] != 0) {
            topoA = i;  
            break;
        }
    }

    // Encontrar a posição disponível na base da torre de destino 
    for (int i = tamanho - 1; i >= 0; i--) {
        if (vetorB[i] == 0) {
            topoB = i; 
            break;
        }
    }
    
    if (topoA == -1) {
        printf("Movimento inválido: Torre de partida está vazia\n");
        return;
    }
    if (topoB == tamanho - 1 || vetorA[topoA] < vetorB[topoB + 1]) {
        // Realizar o movimento
        vetorB[topoB] = vetorA[topoA];
        vetorA[topoA] = 0;
        printf("Movimento realizado: %d movido\n", vetorB[topoB]);
    } else {
        printf("Movimento inválido: Disco maior sobre disco menor\n");
    }
   
}

void game (int tamanho){
	int pinoA[tamanho];  
    int pinoB[tamanho];
    int pinoC[tamanho];
    
    	for (int j = 0; j<tamanho; j++){
    		pinoA[j] = j+1;
    		pinoB[j] = 0;
    		pinoC[j] = 0;
    	}
    
    char partida, destino;

    printf("Desafio das Torres de Hanoi\n");
    
    Imprimir_torre("A", tamanho ,pinoA);
    Imprimir_torre("B", tamanho ,pinoB);
    Imprimir_torre("C", tamanho ,pinoC);

    int qtd_jogadas = 100; //Limitei a quantidade de jogas em 100, mas essa variável pode servir de contador, dando ao jogador uma quantidade mínima de lances.
    while (qtd_jogadas > 0) {
        printf("Digite o pino de partida (A/B/C): ");
        scanf(" %c", &partida);

        printf("Digite o pino de destino (A/B/C): ");
        scanf(" %c", &destino);

        if (partida == 'A' && destino == 'B') {
            Mudar_de_torre(pinoA, pinoB, tamanho);
        } else if (partida == 'A' && destino == 'C') {
            Mudar_de_torre(pinoA, pinoC, tamanho);
        } else if (partida == 'B' && destino == 'A') {
            Mudar_de_torre(pinoB, pinoA, tamanho);
        } else if (partida == 'B' && destino == 'C') {
            Mudar_de_torre(pinoB, pinoC, tamanho);
        } else if (partida == 'C' && destino == 'A') {
            Mudar_de_torre(pinoC, pinoA, tamanho);
        } else if (partida == 'C' && destino == 'B') {
            Mudar_de_torre(pinoC, pinoB, tamanho);
        } else {
            printf("Movimento inválido!\n");
            continue;
        }

        printf("\nEstado das Torres:\n");
        Imprimir_torre("A", tamanho ,pinoA);
        Imprimir_torre("B", tamanho ,pinoB);
        Imprimir_torre("C", tamanho ,pinoC);

        qtd_jogadas--;

        // Verificar condição de vitória
        int win = 0;
        for (int i = 0; i<tamanho; i++){
        	if (pinoC[i] == i+1 || pinoB[i] == i+1)
        		win++;
        	else{
        		win = 0;
        	}
        }
        
        if (win == tamanho){
        	printf("Parabéns! Você resolveu o desafio das Torres de Hanoi!\n");
        	break;
        }
        
    }
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int option, tamanho;

	printf("Defina o nível da sua torre de Hanoi:\n");
	printf("1. Fácil - 3 pinos\n");
	printf("2. Médio - 4 pinos\n");
	printf("3. Difícil - 5 pinos\n");
	scanf(" %d", &option);
	
	switch (option){
		case 1:{
			tamanho = 3;
			game(tamanho);
			break;
		}
		case 2:{
			tamanho = 4;
			game(tamanho);
			break;
		}
		case 3:{
			tamanho = 5;
			game(tamanho);
			break;
		}
		default:{
			puts("Opção invalida!");
		}
}
    return 0;
}
