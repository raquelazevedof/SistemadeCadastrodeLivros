#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================
   ESTRUTURA BASICA DO JOGO WAR (SEM ACENTOS E SEM CEDILHA)
   Inclui:
   - Cadastro de territorios (struct)
   - Ataque entre territorios (ponteiros + alocacao dinamica)
   - Missoes simples
   - Exibicao organizada
   ================================================================ */


/* ---------------------------
   DEFINICAO DA STRUCT TERRITORIO
   --------------------------- */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


/* ---------------------------
   FUNCAO: cadastrar territorios
   --------------------------- */
void cadastrarTerritorios(Territorio *vet) {
    int i;

    printf("=== Cadastro de 5 territorios ===\n\n");

    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", vet[i].nome);

        printf("Digite a cor do exercito: ");
        scanf(" %9s", vet[i].cor);

        printf("Digite o numero de tropas: ");
        scanf("%d", &vet[i].tropas);

        printf("\n");
    }
}


/* ---------------------------
   FUNCAO: exibir territorios
   --------------------------- */
void exibirTerritorios(Territorio *vet) {
    int i;

    printf("\n=== Territorios cadastrados ===\n");

    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", vet[i].nome);
        printf("  Cor: %s\n", vet[i].cor);
        printf("  Tropas: %d\n", vet[i].tropas);
        printf("----------------------------------\n");
    }
}


/* ---------------------------
   FUNCAO DE ATAQUE
   Usa ponteiros e alocacao dinamica
   --------------------------- */
void atacar(Territorio *origem, Territorio *alvo) {

    printf("\n=== Sistema de ataque ===\n");
    printf("%s (tropas: %d) vai atacar %s (tropas: %d)\n",
           origem->nome, origem->tropas, alvo->nome, alvo->tropas);

    /* Alocacao dinamica para simular dados de ataque */
    int *resultado = malloc(sizeof(int));

    if (resultado == NULL) {
        printf("Erro de memoria.\n");
        return;
    }

    /* Regra simples:
       Se origem > alvo, ataque vence e alvo perde tropas
       Caso contrario, ataque falha e origem perde tropas */
    if (origem->tropas > alvo->tropas) {
        *resultado = 1;
        alvo->tropas -= 1;
        printf("Ataque bem sucedido! %s perdeu 1 tropa.\n", alvo->nome);
    } else {
        *resultado = 0;
        origem->tropas -= 1;
        printf("Ataque falhou. %s perdeu 1 tropa.\n", origem->nome);
    }

    free(resultado);
}


/* ---------------------------
   MISSAO SIMPLES
   --------------------------- */
void verificarMissao(Territorio *vet) {
    int i;
    int totalTropas = 0;

    for (i = 0; i < 5; i++) {
        totalTropas += vet[i].tropas;
    }

    printf("\n=== Sistema de missoes ===\n");
    printf("Missao: possuir pelo menos 20 tropas no total.\n");

    if (totalTropas >= 20) {
        printf("Missao concluida! Voce venceu!\n");
    } else {
        printf("Missao nao concluida. Tropas atuais: %d\n", totalTropas);
    }
}


/* ---------------------------
   FUNCAO PRINCIPAL
   --------------------------- */
int main() {

    /* Alocacao dinamica para armazenar os 5 territorios */
    Territorio *mapa = malloc(5 * sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa);
    exibirTerritorios(mapa);

    /* Simulacao de ataque:
       territorio 0 ataca territorio 1 */
    atacar(&mapa[0], &mapa[1]);

    /* Exibir novamente depois do ataque */
    exibirTerritorios(mapa);

    /* Verificar missao */
    verificarMissao(mapa);

    free(mapa);

    return 0;
}