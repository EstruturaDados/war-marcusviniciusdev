// ============================================================================
//         NÍVEL NOVATO - CADASTRO INICIAL DOS TERRITÓRIOS
// ============================================================================
// OBJETIVOS:
// - Criar uma struct chamada Territorio
// - Usar um vetor estático de 5 elementos
// - Cadastrar: Nome, Cor do Exército, Número de Tropas
// - Exibir o estado atual do mapa
// ============================================================================

#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define MAX_STRING 50

// Estrutura de Dados
typedef struct {
    char nome[MAX_STRING];
    char corExercito[MAX_STRING];
    int numeroTropas;
} Territorio;

// Protótipos das Funções
void cadastrarTerritorios(Territorio territorios[], int quantidade);
void exibirMapa(const Territorio territorios[], int quantidade);
void limparBuffer();

int main() {
    Territorio territorios[MAX_TERRITORIOS];

    printf("=================================================\n");
    printf("    BEM-VINDO AO WAR - NÍVEL NOVATO\n");
    printf("    Cadastro de Territórios\n");
    printf("=================================================\n\n");

    // Cadastrar os territórios
    cadastrarTerritorios(territorios, MAX_TERRITORIOS);

    // Exibir o mapa
    printf("\n=================================================\n");
    printf("           MAPA ATUAL DOS TERRITÓRIOS\n");
    printf("=================================================\n");
    exibirMapa(territorios, MAX_TERRITORIOS);

    return 0;
}

// Implementação das Funções

void cadastrarTerritorios(Territorio territorios[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome do território: ");
        fgets(territorios[i].nome, MAX_STRING, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remove o \n

        printf("Cor do exército dominante: ");
        fgets(territorios[i].corExercito, MAX_STRING, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0'; // Remove o \n

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].numeroTropas);
        limparBuffer();
    }
}

void exibirMapa(const Territorio territorios[], int quantidade) {
    printf("\n%-4s | %-20s | %-20s | %-10s\n", "ID", "TERRITÓRIO", "COR DO EXÉRCITO", "TROPAS");
    printf("-----+----------------------+----------------------+------------\n");

    for (int i = 0; i < quantidade; i++) {
        printf("%-4d | %-20s | %-20s | %-10d\n",
               i + 1,
               territorios[i].nome,
               territorios[i].corExercito,
               territorios[i].numeroTropas);
    }
    printf("\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
