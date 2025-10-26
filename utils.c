#include "tetris.h"

// Escolhe aleatoriamente o tipo da peça.
static char escolherTipoPeca() {
    int indice_aleatorio = rand() % NUM_TIPOS;
    return TIPOS_PECAS[indice_aleatorio];
}

// Cria uma peça nova
Peca gerarPeca(int *proximo_id) {
    Peca nova;
    nova.nome = escolherTipoPeca();
    nova.id = (*proximo_id);
    return nova;
}

// Inicia uma fila com as peças
void inicializarFila(FilaPecas *f) {
    // Inicializa os índices e o total
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
    f->proximo_id = 0;

    // Preenche a fila até o TAMANHO_FILA
    printf("--- Criando Fila com %d pecas ---\n", TAMANHO_FILA);
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca p = gerarPeca(&(f->proximo_id));
        if (enqueue(f, p)) {
            f->proximo_id++;
        }
    }
    printf("[SUCESSO] Fila inicializada.\n");
}

// Adiciona uma nova peça na lista
int enqueue(FilaPecas *f, Peca novaPeca) {
    if (filaCheia(f)) {
        return 0;
    }

    f->pecas[f->fim] = novaPeca;
    f->fim = (f->fim + 1) % TAMANHO_FILA;
    f->total++;
    printf("[SUCESSO] Peca %c com ID %d enfileirada.\n", novaPeca.nome, novaPeca.id);
    return 1;
}

// Joga uma peça
int dequeue(FilaPecas *f, Peca *pecaJogada) {
    if (filaVazia(f)) {
        return 0;
    }

    // Copia a peça da inicio antes de removê-la logicamente
    *pecaJogada = f->pecas[f->inicio];

    // Avança o índice 'inicio' de forma circular
    f->inicio = (f->inicio + 1) % TAMANHO_FILA;
    f->total--;

    printf("[SUCESSO] Peça %c com ID %d jogada.\n", pecaJogada->nome, pecaJogada->id);
    return 1;
}

// Exibe a fila atual de peças
void mostrarFila(FilaPecas *f) {
    if (filaVazia(f)) {
        return;
    }

    // Retorna a fila de peças
    printf("Fila de peças [");
    int i = f->inicio;
    int elementos_exibidos = 0;
    while (elementos_exibidos < f->total) {
        printf("%c %d]", f->pecas[i].nome, f->pecas[i].id);

        // Se ainda não for o último, adiciona um espaço
        if (elementos_exibidos < f->total - 1) {
            printf(" [");
        }

        // Avança o índice de forma circular
        i = (i + 1) % TAMANHO_FILA;
        elementos_exibidos++;
    }
    printf("\n");
    printf("Total de pecas na fila: %d de %d\n", f->total, TAMANHO_FILA);
        printf("------------------------------------------\n");
}

// Exibe o menu de opções para o jogador.
void exibirMenu() {
    printf("\n#### TETRIS STACK ####\n");
    printf("---------- MENU ----------\n");
    printf("1. Jogar peça\n");
    printf("2. Inserir nova peça\n");
    printf("3. Sair\n");
    printf("Escolha uma opcao: ");
}

int filaCheia(FilaPecas *f) {
    if (f->total == TAMANHO_FILA) {
        printf("[ERRO] Fila de peças cheia. Não foi possível inserir uma nova peça!\n");
        return 1;
    }
    return 0;
}

int filaVazia(FilaPecas *f) {
    if (f->total == 0) {
        printf("[ERRO] Fila de peças vazia. Não foi possível jogar uma peça!\n");
        return 1;
    }
    return 0;
}