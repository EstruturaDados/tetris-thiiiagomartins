#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- CONSTANTES DO SISTEMA ---
#define TAMANHO_FILA 5
#define TIPOS_PECAS "IOTL"
#define NUM_TIPOS 4
#define TAMANHO_PILHA 3

// --- ESTRUTURA DE DADOS: PEÇA ---
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;
} Peca;

// --- ESTRUTURA DE DADOS: FILA CIRCULAR ---
typedef struct {
    Peca pecas[TAMANHO_FILA];
    int inicio;
    int fim;
    int total;
    int proximo_id;
} FilaPecas;

typedef struct {
    Peca pecas[TAMANHO_PILHA];
    int topo;
} PilhaPecas;

// --- CABEÇALHOS DAS FUNÇÕES DE UTILS.C ---

// Inicialização e geração
void inicializarFila(FilaPecas *f);
void inicializarPilha(PilhaPecas *p);
Peca gerarPeca(int *proximo_id);

// Operações da fila
int enqueue(FilaPecas *f, Peca novaPeca);
int dequeue(FilaPecas *f, Peca *pecaJogada);
int filaCheia(FilaPecas *f);
int filaVazia(FilaPecas *f);

// Operações da Pilha
int push(PilhaPecas *p, Peca pecaEmpilhada);
int pop(PilhaPecas *p, Peca *pecaDesempilhada);
int pilhaCheia(PilhaPecas *p);
int pilhaVazia(PilhaPecas *p);

// Utilitários e exibição
void mostrarFila(FilaPecas *f);
void mostrarPilha(PilhaPecas *p);
void exibirResultado(FilaPecas *f, PilhaPecas *p);
void exibirMenu();

#endif