#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct que representa um livro
typedef struct {
    char nome[50];
    char autor[30];
    char editora[30];
    int edicao;
} Livro;

// Struct que representa um emprestimo
typedef struct {
    char usuario[30];
    int idLivro; // indice do livro emprestado
} Emprestimo;

int main() {
    int qtdLivros;
    int qtdEmprestimos;
    
    printf("Quantos livros deseja cadastrar? ");
    scanf("%d", &qtdLivros);
    getchar(); // limpar buffer

    // Alocacao dinamica do vetor de livros usando malloc
    Livro *livros = (Livro*) malloc(qtdLivros * sizeof(Livro));

    if (livros == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Cadastro dos livros
    for (int i = 0; i < qtdLivros; i++) {
        printf("\nCadastro do livro %d\n", i + 1);
        
        printf("Nome do livro: ");
        fgets(livros[i].nome, sizeof(livros[i].nome), stdin);
        livros[i].nome[strcspn(livros[i].nome, "\n")] = '\0';

        printf("Autor: ");
        fgets(livros[i].autor, sizeof(livros[i].autor), stdin);
        livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';

        printf("Editora: ");
        fgets(livros[i].editora, sizeof(livros[i].editora), stdin);
        livros[i].editora[strcspn(livros[i].editora, "\n")] = '\0';

        printf("Edicao (numero): ");
        scanf("%d", &livros[i].edicao);
        getchar(); // limpar buffer
    }

    // Cadastro de emprestimos
    printf("\nQuantos emprestimos deseja registrar? ");
    scanf("%d", &qtdEmprestimos);
    getchar(); 

    // Alocacao dinamica usando calloc (inicia tudo com zero)
    Emprestimo *emprestimos = (Emprestimo*) calloc(qtdEmprestimos, sizeof(Emprestimo));

    if (emprestimos == NULL) {
        printf("Erro ao alocar memoria.\n");
        free(livros);
        return 1;
    }

    for (int i = 0; i < qtdEmprestimos; i++) {
        printf("\nCadastro do emprestimo %d\n", i + 1);
        
        printf("Nome do usuario: ");
        fgets(emprestimos[i].usuario, sizeof(emprestimos[i].usuario), stdin);
        emprestimos[i].usuario[strcspn(emprestimos[i].usuario, "\n")] = '\0';

        printf("Digite o indice do livro emprestado (0 a %d): ", qtdLivros - 1);
        scanf("%d", &emprestimos[i].idLivro);
        getchar();
    }

    // Exibicao dos livros cadastrados
    printf("\n=== LISTA DE LIVROS ===\n");
    for (int i = 0; i < qtdLivros; i++) {
        printf("\nLivro %d\n", i);
        printf("Nome: %s\n", livros[i].nome);
        printf("Autor: %s\n", livros[i].autor);
        printf("Editora: %s\n", livros[i].editora);
        printf("Edicao: %d\n", livros[i].edicao);
    }

    // Exibicao dos emprestimos
    printf("\n=== EMPRESTIMOS REGISTRADOS ===\n");
    for (int i = 0; i < qtdEmprestimos; i++) {
        printf("\nEmprestimo %d\n", i + 1);
        printf("Usuario: %s\n", emprestimos[i].usuario);
        printf("Livro emprestado: %s\n", livros[emprestimos[i].idLivro].nome);
    }

    // Liberar memoria
    free(livros);
    free(emprestimos);

    printf("\nMemoria liberada. Sistema finalizado.\n");

    return 0;
}
