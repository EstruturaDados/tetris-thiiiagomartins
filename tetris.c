// inclui o arquivo de cabeçalho com as definições e protótipos
#include "tetris.h"

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
int main() {
    srand(time(NULL));

    FilaPecas fila;
    int opcao = -1;
    Peca pecaAuxiliar;

    // Inicializa e preenche a fila com 5 peças
    printf("\n#### TETRIS STACK - CONFIGURAÇÃO INICIAL ####\n");
    inicializarFila(&fila);
    mostrarFila(&fila);

    // 2. Loop principal do programa
    while (opcao != 0) {
        exibirMenu();

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
            printf("[AVISO] Opção inválida. Por favor, digite um número entre 1 - 3.\n");
            continue;
        }

        switch (opcao) {
            case 1: // Jogar peça
                printf("------------------------------------------\n");
                dequeue(&fila, &pecaAuxiliar);
                mostrarFila(&fila);
                break;

            case 2: // Inserir nova peça
                printf("------------------------------------------\n");
                Peca nova = gerarPeca(&(fila.proximo_id));
                if (enqueue(&fila, nova)) {
                    fila.proximo_id++;
                }
                mostrarFila(&fila);
                break;

            case 0: // Sair
                printf("Encerrando o simulador Tetris Stack. Ate a proxima!\n");
                break;

            default:
                printf("[AVISO] Opcao %d invalida. Tente novamente.\n", opcao);
                mostrarFila(&fila);
                break;
        }
    }

    return 0;
}



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha