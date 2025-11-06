#include <stdio.h>
#include <stdlib.h> // Necessario para malloc e free
#include <string.h> // Necessario para strcpy

// Struct 

// Struct Sala: Representa um no da arvore binaria (um comodo da mansao) [cite: 520]
typedef struct Sala {
    char nome[50];          // Nome da sala (a string que identifica o comodo) [cite: 507]
    struct Sala *esquerda;  // Ponteiro para o comodo a esquerda (filho esquerdo) [cite: 64]
    struct Sala *direita;   // Ponteiro para o comodo a direita (filho direito) [cite: 64]
} Sala;

// Funcoes de Utilitario

// Funcao auxiliar para limpar o buffer de entrada apos a leitura de caracteres (usado no explorarSalas)
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// Funcao de Criacao do No 

// criarSala(): Cria, de forma dinamica, uma nova sala (no) e retorna seu ponteiro.
Sala* criarSala(const char *nome_sala) {
    // Aloca memoria para a nova struct Sala [cite: 521]
    Sala *nova_sala = (Sala*)malloc(sizeof(Sala));

    if (nova_sala == NULL) {
        printf("ERRO FATAL - Falha na alocacao de memoria.\n");
        exit(1);
    }
    
    // Inicializa os campos
    strcpy(nova_sala->nome, nome_sala);
    nova_sala->esquerda = NULL; // Novo no comeca sem filhos
    nova_sala->direita = NULL;  // Novo no comeca sem filhos
    
    return nova_sala;
}

//  Funcao de Exploracao

// explorarSalas(): Permite a navegacao interativa do jogador pela arvore binaria.
void explorarSalas(Sala *sala_atual) {
    char escolha;

    // Loop de exploracao continua
    while (sala_atual != NULL) {
        
        printf("\nVoce esta no comodo: %s\n", sala_atual->nome); // Exibe a sala atual [cite: 505]
        
        // Verifica se a sala atual e um no-folha (nao possui caminhos) [cite: 504]
        if (sala_atual->esquerda == NULL && sala_atual->direita == NULL) {
            printf("FIM DE JORNADA - Voce chegou a um comodo sem saidas (no-folha).\n");
            break; // Encerra a exploracao 
        }

        printf("Escolha o proximo caminho: (e) Esquerda | (d) Direita | (s) Sair: ");
        
        // Leitura da escolha do usuario
        if (scanf(" %c", &escolha) != 1) {
            limpar_buffer();
            continue;
        }
        limpar_buffer(); // Limpa o buffer após a leitura

        if (escolha == 's' || escolha == 'S') {
            printf("SAIDA - Exploracao encerrada pelo jogador.\n");
            break;
        } 
        
        // Controle das decisoes do jogador
        else if (escolha == 'e' || escolha == 'E') {
            if (sala_atual->esquerda != NULL) {
                sala_atual = sala_atual->esquerda;
            } else {
                printf("ALERTA - Caminho 'Esquerda' inexistente. Escolha outra opcao.\n");
            }
        } 
        
        else if (escolha == 'd' || escolha == 'D') {
            if (sala_atual->direita != NULL) {
                sala_atual = sala_atual->direita;
            } else {
                printf("ALERTA - Caminho 'Direita' inexistente. Escolha outra opcao.\n");
            }
        } 
        
        else {
            printf("ALERTA - Opcao invalida. Digite 'e', 'd' ou 's'.\n");
        }
    }
}

// Funcaode liberacao de Memoria 

// Funcao recursiva para desalocar todos os nos (evita memory leak)
void liberarMapa(Sala *raiz) {
    if (raiz != NULL) {
        liberarMapa(raiz->esquerda);
        liberarMapa(raiz->direita);
        free(raiz);
    }
}
int main() {
    
    
    // Nivel 0: Raiz 
    Sala *hall_entrada = criarSala("Hall de Entrada");
    
    // Nivel 1: Filhos do Hall
    hall_entrada->esquerda = criarSala("Sala de Estar");
    hall_entrada->direita  = criarSala("Biblioteca");
    
    // Nivel 2: Filhos da Sala de Estar e Biblioteca
    Sala *sala_estar = hall_entrada->esquerda;
    Sala *biblioteca = hall_entrada->direita;
    
    sala_estar->esquerda = criarSala("Quarto Principal");
    sala_estar->direita  = criarSala("Cozinha");
    
    // Nivel 3: Filhos do Quarto Principal
    sala_estar->esquerda->esquerda = criarSala("Banheiro");
    
    // Nivel 4: Folha
    sala_estar->esquerda->esquerda->direita = criarSala("Closet Escondido"); // NO FOLHA FINAL
    
    printf(">>> DETECTIVE QUEST: Exploracao da Mansao <<<\n");
    printf("MAPA CARREGADO - O detetive comeca no Hall de Entrada.\n");
    
    // Inicia a exploracao a partir da raiz
    explorarSalas(hall_entrada);
    
    // Limpeza: Libera a memoria alocada dinamicamente
    liberarMapa(hall_entrada);
    
    return 0;
}
