// inclui o arquivo de cabeçalho com as definições e protótipos
#include "tetris.h"

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
int main() {
    srand(time(NULL));

    FilaPecas fila;
    PilhaPecas pilha;
    int opcao = -1;
    Peca pecaAuxiliar;

    // Inicializa e preenche a fila com 5 peças
    printf("\n#### TETRIS STACK - CONFIGURAÇÃO INICIAL ####\n");
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    exibirResultado(&fila, &pilha);

    // 2. Loop principal do programa
    while (opcao != 0) {
        exibirMenu();

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
            printf("[AVISO] Opção inválida. Por favor, digite um número entre 0 - 3.\n");
            continue;
        }

        switch (opcao) {
            case 1: // Jogar peça
                printf("------------------------------------------\n");
                if (dequeue(&fila, &pecaAuxiliar)) {
                    // Cria uma nova peça e insere na fila automaticamente
                    Peca nova = gerarPeca(&(fila.proximo_id));
                    if (enqueue(&fila, nova)) {
                        fila.proximo_id++;
                    }
                }
                break;
            /* Removido do nível aventureiro
            case 2: // Inserir nova peça
                printf("------------------------------------------\n");
                Peca nova = gerarPeca(&(fila.proximo_id));
                if (enqueue(&fila, nova)) {
                    fila.proximo_id++;
                }
                mostrarFila(&fila);
                break;
            */
            case 2: // Reservar peça
                // verifica se a pilha está cheia
                if (pilhaCheia(&pilha)) {
                    break;
                }
                // verifica se a fila está vazia
                if (filaVazia(&fila)) {
                    break;
                }
                // Remove a peça da fila para inserir na pilha
                if (dequeue(&fila, &pecaAuxiliar)) {
                    // Insere a peça removida na Pilha
                    if (push(&pilha, pecaAuxiliar)) {
                        // Insere uma nova peça na fila para repor a que foi removida
                        Peca nova = gerarPeca(&(fila.proximo_id));
                        if (enqueue(&fila, nova)) {
                            fila.proximo_id++;
                        }
                    }
                }
                break;
            case 3: // Usar peça reservada
                // verifica se a pilha está vazia
                if (pilhaVazia(&pilha)) {
                    break;
                }
                // Utiliza a peça reservada
                if (pop(&pilha, &pecaAuxiliar)) {
                    printf("[INFO] Peca %c ID %d da Reserva foi usada e descartada.\n", pecaAuxiliar.nome, pecaAuxiliar.id);
                }
                break;
            case 0: // Sair
                printf("Encerrando o simulador Tetris Stack. Ate a proxima!\n");
                break;

            default:
                printf("[AVISO] Opcao %d invalida. Tente novamente.\n", opcao);
                mostrarFila(&fila);
                break;
        }
        // Exibe o resultado da fila e da pilha
        if (opcao != 0) {
            exibirResultado(&fila, &pilha);
        }
    }

    return 0;
}

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