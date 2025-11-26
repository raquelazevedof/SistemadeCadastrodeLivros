#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct que representa um territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// -----------------------------
// Funcao para exibir territorios
// -----------------------------
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== ESTADO ATUAL DOS TERRITORIOS ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// ------------------------------------------
// Funcao que simula um ataque entre territorios
// ------------------------------------------
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nRolagem do atacante: %d", dadoAtacante);
    printf("\nRolagem do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");

        // Se vence, assume o territorio
        strcpy(defensor->cor, atacante->cor);

        // Metade das tropas do atacante vao para o defensor
        defensor->tropas = atacante->tropas / 2;

        printf("O territorio %s agora pertence ao exercito %s.\n",
               defensor->nome, defensor->cor);
    } else {
        printf("\nO defensor venceu a batalha!\n");

        // Atacante perde 1 tropa (mas nunca fica com menos de 1)
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }

        printf("O territorio atacante perdeu uma tropa e agora possui %d tropas.\n",
               atacante->tropas);
    }
}

// ------------------------------------------
// Funcao para liberar memoria
// ------------------------------------------
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// ------------------------------------------
// Programa principal
// ------------------------------------------
int main() {
    srand(time(NULL));

    int n;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &n);
    getchar();

    // Alocacao dinamica
    Territorio* mapa = (Territorio*) malloc(n * sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Cadastro dos territorios
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do territorio %d\n", i);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }

    int opcao = 1;
    while (opcao == 1) {
        exibirTerritorios(mapa, n);

        int a, d;

        printf("\nEscolha o indice do territorio atacante: ");
        scanf("%d", &a);
        getchar();

        printf("Escolha o indice do territorio defensor: ");
        scanf("%d", &d);
        getchar();

        // Validacoes
        if (a == d) {
            printf("\nErro: um territorio nao pode atacar ele mesmo.\n");
            continue;
        }

        if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
            printf("\nErro: nao pode atacar um territorio da mesma cor.\n");
            continue;
        }

        if (mapa[a].tropas < 2) {
            printf("\nO atacante precisa ter pelo menos 2 tropas para atacar.\n");
            continue;
        }

        // Realiza o ataque
        atacar(&mapa[a], &mapa[d]);

        // Exibe estado final
        exibirTerritorios(mapa, n);

        printf("\nDeseja realizar outro ataque? (1 = sim / 0 = nao): ");
        scanf("%d", &opcao);
        getchar();
    }

    liberarMemoria(mapa);
    printf("\nMemoria liberada. Programa finalizado.\n");

    return 0;
}
