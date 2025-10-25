// ============================================================================
//         NÍVEL AVENTUREIRO - BATALHAS ESTRATÉGICAS
// ============================================================================
// OBJETIVOS:
// - Substituir vetor estático por alocação dinâmica com calloc
// - Criar função para simular ataques entre dois territórios
// - Utilizar números aleatórios para dados de batalha
// - Usar ponteiros e gerenciar memória
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define MAX_STRING 50

// Estrutura de Dados
typedef struct {
    char nome[MAX_STRING];
    char corExercito[MAX_STRING];
    int numeroTropas;
} Territorio;

// Protótipos das Funções
Territorio* alocarMapa(int quantidade);
void inicializarTerritorios(Territorio* territorios, int quantidade);
void liberarMemoria(Territorio* territorios);
void cadastrarTerritorios(Territorio* territorios, int quantidade);
void exibirMapa(const Territorio* territorios, int quantidade);
void faseDeAtaque(Territorio* territorios, int quantidade);
void simularAtaque(Territorio* atacante, Territorio* defensor);
void limparBuffer();
int rolarDado();

int main() {
    // Inicializar semente aleatória
    srand(time(NULL));

    // Alocar memória dinamicamente
    Territorio* territorios = alocarMapa(MAX_TERRITORIOS);
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("=================================================\n");
    printf("    BEM-VINDO AO WAR - NÍVEL AVENTUREIRO\n");
    printf("    Batalhas Estratégicas\n");
    printf("=================================================\n\n");

    // Cadastrar os territórios
    cadastrarTerritorios(territorios, MAX_TERRITORIOS);

    // Exibir o mapa inicial
    printf("\n=================================================\n");
    printf("           MAPA INICIAL DOS TERRITÓRIOS\n");
    printf("=================================================\n");
    exibirMapa(territorios, MAX_TERRITORIOS);

    // Fase de ataques
    char continuar;
    do {
        faseDeAtaque(territorios, MAX_TERRITORIOS);

        printf("\n=================================================\n");
        printf("           MAPA ATUALIZADO\n");
        printf("=================================================\n");
        exibirMapa(territorios, MAX_TERRITORIOS);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
        limparBuffer();
    } while (continuar == 's' || continuar == 'S');

    printf("\n=================================================\n");
    printf("    FIM DO JOGO - OBRIGADO POR JOGAR!\n");
    printf("=================================================\n");

    // Liberar memória
    liberarMemoria(territorios);

    return 0;
}

// Implementação das Funções

Territorio* alocarMapa(int quantidade) {
    Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
    return mapa;
}

void inicializarTerritorios(Territorio* territorios, int quantidade) {
    // Função para inicialização automática (será usada no Nível Mestre)
    const char* nomes[] = {"Brasil", "Argentina", "Peru", "Chile", "Colombia"};
    const char* cores[] = {"Verde", "Azul", "Amarelo", "Vermelho", "Preto"};

    for (int i = 0; i < quantidade; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].corExercito, cores[i]);
        territorios[i].numeroTropas = 5 + (rand() % 6); // 5 a 10 tropas
    }
}

void liberarMemoria(Territorio* territorios) {
    free(territorios);
}

void cadastrarTerritorios(Territorio* territorios, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome do território: ");
        fgets(territorios[i].nome, MAX_STRING, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do exército dominante: ");
        fgets(territorios[i].corExercito, MAX_STRING, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].numeroTropas);
        limparBuffer();
    }
}

void exibirMapa(const Territorio* territorios, int quantidade) {
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

void faseDeAtaque(Territorio* territorios, int quantidade) {
    int idAtacante, idDefensor;

    printf("\n=================================================\n");
    printf("           FASE DE ATAQUE\n");
    printf("=================================================\n");

    printf("Escolha o território ATACANTE (1-%d): ", quantidade);
    scanf("%d", &idAtacante);
    limparBuffer();

    printf("Escolha o território DEFENSOR (1-%d): ", quantidade);
    scanf("%d", &idDefensor);
    limparBuffer();

    // Validações
    if (idAtacante < 1 || idAtacante > quantidade || idDefensor < 1 || idDefensor > quantidade) {
        printf("\n[ERRO] Território inválido!\n");
        return;
    }

    if (idAtacante == idDefensor) {
        printf("\n[ERRO] Um território não pode atacar a si mesmo!\n");
        return;
    }

    if (territorios[idAtacante - 1].numeroTropas < 2) {
        printf("\n[ERRO] O território atacante precisa ter pelo menos 2 tropas!\n");
        return;
    }

    // Simular ataque
    simularAtaque(&territorios[idAtacante - 1], &territorios[idDefensor - 1]);
}

void simularAtaque(Territorio* atacante, Territorio* defensor) {
    printf("\n--- BATALHA ---\n");
    printf("Atacante: %s (%s) com %d tropas\n", atacante->nome, atacante->corExercito, atacante->numeroTropas);
    printf("Defensor: %s (%s) com %d tropas\n", defensor->nome, defensor->corExercito, defensor->numeroTropas);

    // Rolar dados
    int dadoAtaque = rolarDado();
    int dadoDefesa = rolarDado();

    printf("\nDado do Atacante: %d\n", dadoAtaque);
    printf("Dado do Defensor: %d\n", dadoDefesa);

    // Determinar resultado
    if (dadoAtaque > dadoDefesa) {
        printf("\n[RESULTADO] Atacante venceu!\n");
        defensor->numeroTropas--;

        if (defensor->numeroTropas == 0) {
            printf("[CONQUISTA] %s conquistou %s!\n", atacante->nome, defensor->nome);
            strcpy(defensor->corExercito, atacante->corExercito);
            defensor->numeroTropas = 1;
            atacante->numeroTropas--;
        }
    } else {
        printf("\n[RESULTADO] Defensor resistiu ao ataque!\n");
        printf("(Em caso de empate, o defensor vence)\n");
    }
}

int rolarDado() {
    return 1 + (rand() % 6); // Retorna um número entre 1 e 6
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
