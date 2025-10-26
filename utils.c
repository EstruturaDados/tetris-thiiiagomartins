#include "tetris.h"

void mostrarFila();
void mostrarPilha();

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

// Exibe o menu de opções para o jogador.
void exibirMenu() {
    printf("\n#### TETRIS STACK ####\n");
    printf("---------- MENU ----------\n");
    printf("1. Jogar peça\n");
    // printf("2. Inserir nova peça\n"); # removida para o nível aventureiro
    printf("2. Enviar peça da fila para a reserva\n");
    printf("3. Usar peça da reserva\n");
    printf("4. Trocar peça da frente com topo da pilha\n");
    printf("5. Trocar 3 primeiros da fila com os 3 da pilha\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

// Agrupa a exibição do estado
void exibirResultado(FilaPecas *f, PilhaPecas *p) {
    printf("\n#### ESTADO ATUAL ####\n");
    mostrarFila(f);
    mostrarPilha(p);
    printf("------------------------------------------\n");
}

// função que faz a troca de uma das peças em uma temporária
static void trocarPeca(Peca *a, Peca *b) {
    Peca temp = *a;
    *a = *b;
    *b = temp;
}

// Funções de FILA
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
    printf("Fila de peças: [");
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
    printf("Total de peças na fila: %d de %d\n", f->total, TAMANHO_FILA);
    printf("------------------------------------------\n");
}

// Verifica se a Fila está cheia
int filaCheia(FilaPecas *f) {
    if (f->total == TAMANHO_FILA) {
        printf("------------------------------------------\n");
        printf("[ERRO] Fila de peças cheia. Não foi possível inserir uma nova peça!\n");
        printf("------------------------------------------\n");
        return 1;
    }
    return 0;
}

// Verifica se a Fila está vazia
int filaVazia(FilaPecas *f) {
    if (f->total == 0) {
        printf("------------------------------------------\n");
        printf("[ERRO] Fila de peças vazia. Não foi possível jogar uma peça!\n");
        printf("------------------------------------------\n");
        return 1;
    }
    return 0;
}

// Funções de PILHA
// Inicia uma pilha com as peças
void inicializarPilha(PilhaPecas *p) {
    p->topo = 0;
    printf("--- Criando Pilha com capacidade para %d pecas ---\n", TAMANHO_PILHA);
    printf("[SUCESSO] Pilha de Reserva inicializada.\n");
}

// Adiciona uma nova peça na pilha
int push(PilhaPecas *p, Peca pecaEmpilhada) {
    if (pilhaCheia(p)) {
        return 0;
    }

    p->pecas[p->topo] = pecaEmpilhada;
    p->topo++;
    printf("[SUCESSO] Peca %c ID %d reservada.\n", pecaEmpilhada.nome, pecaEmpilhada.id);
    return 1;
}

// Joga uma peça
int pop(PilhaPecas *p, Peca *pecaDesempilhada) {
    if (pilhaVazia(p)) {
        return 0;
    }

    p->topo--;
    *pecaDesempilhada = p->pecas[p->topo];
    printf("[SUCESSO] Peca %c ID %d usada.\n", pecaDesempilhada->nome, pecaDesempilhada->id);
    return 1;
}

// Exibe a pilha atual de peças
void mostrarPilha(PilhaPecas *p) {
    if (pilhaVazia(p)) {
        return;
    }

    printf("Pilha de Reserva (Topo -> Base): ");
    for (int i = p->topo - 1; i >= 0; i--) {
        printf("[%c %d]", p->pecas[i].nome, p->pecas[i].id);
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\n");
    printf("Total na Pilha: %d/%d\n", p->topo, TAMANHO_PILHA);
    printf("------------------------------------------\n");
}

// Verifica se a pilha está cheia
int pilhaCheia(PilhaPecas *p) {
    if (p->topo == TAMANHO_PILHA) {
        printf("------------------------------------------\n");
        printf("[ERRO] Pilha de Reserva cheia. Não foi possível reservar uma nova peca!\n");
        printf("------------------------------------------\n");
        return 1;
    }
    return 0;
}

// Verifica se a pilha está vazia
int pilhaVazia(PilhaPecas *p) {
    if (p->topo == 0) {
        printf("------------------------------------------\n");
        printf("[ALERTA] Pilha de Reserva vazia!\n");
        printf("------------------------------------------\n");
        return 1;
    }
    return 0;
}

// Funções de TROCA
// Troca apenas a primeira peça da fila com a pilha
int trocarPecaAtual(FilaPecas *f, PilhaPecas *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        return 0;
    }

    // Localiza os índices da fila e da pilha
    int idx_fila = f->inicio;
    int idx_pilha = p->topo - 1;
    // Cria uma peça temporária para a troca
    trocarPeca(&(f->pecas[idx_fila]), &(p->pecas[idx_pilha]));
    printf("[SUCESSO] Troca realizada: [%c %d] da Fila <-> [%c %d] da Pilha.\n",
       f->pecas[idx_fila].nome,
       f->pecas[idx_fila].id,
       p->pecas[idx_pilha].nome,
       p->pecas[idx_pilha].id
    );
    return 1;
}

// Troca os 3 primeiros elementos da fila com todos os elementos da pilha
int trocarBloco(FilaPecas *f, PilhaPecas *p) {
    // Pilha deve estar cheia
    if (!pilhaCheia(p)) {
        printf("[ERRO] Pilha de freserva deve ter %d peças (Contagem: %d).\n",
            TAMANHO_PILHA,
            p->topo
        );
        return 0;
    }

    // Fila deve ter pelo menos 3 peças
    if (f->total < TAMANHO_PILHA) {
        printf("[ERRO] Fila deve ter pelo menos %d peças (Contagem: %d).\n",
            TAMANHO_PILHA,
            f->total
        );
        return 0;
    }

    printf("[INFO] Iniciando Troca em Bloco dos 3 primeiros elementos.\n");

    // Faz as trocas dos 3 primeiros elementos
    for (int i = 0; i < 3; i++) {
        int idx_fila_circular = (f->inicio + i) % TAMANHO_FILA;
        int idx_pilha = i;

        // Realiza a troca
        trocarPeca(&(f->pecas[idx_fila_circular]), &(p->pecas[idx_pilha]));
    }

    printf("[SUCESSO] Troca em Bloco realizada entre as 3 pecas da Fila e as 3 pecas da Pilha.\n");
    return 1;
}