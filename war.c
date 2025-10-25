// ============================================================================
//         NÍVEL MESTRE - MISSÕES E MODULARIZAÇÃO TOTAL
// ============================================================================
// OBJETIVOS:
// - Dividir o código em funções bem definidas
// - Implementar sistema de missões
// - Verificar cumprimento da missão
// - Aplicar boas práticas (uso de const, modularização)
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define MAX_STRING 50
#define MISSAO_DESTRUIR_VERDE 1
#define MISSAO_CONQUISTAR_3_TERRITORIOS 2

// Estrutura de Dados
typedef struct {
    char nome[MAX_STRING];
    char corExercito[MAX_STRING];
    int numeroTropas;
} Territorio;

// Protótipos das Funções

// Funções de setup e gerenciamento de memória
Territorio* alocarMapa(int quantidade);
void inicializarTerritorios(Territorio* territorios, int quantidade);
void liberarMemoria(Territorio* territorios);

// Funções de interface com o usuário
void exibirMenuPrincipal();
void exibirMapa(const Territorio* territorios, int quantidade);
void exibirMissao(int missaoId);

// Funções de lógica principal do jogo
void faseDeAtaque(Territorio* territorios, int quantidade);
void simularAtaque(Territorio* atacante, Territorio* defensor);
int sortearMissao();
int verificarVitoria(const Territorio* territorios, int quantidade, int missaoId, const char* corJogador);

// Função utilitária
void limparBuffer();
int rolarDado();

int main() {
    // 1. Configuração Inicial (Setup)
    srand(time(NULL));

    Territorio* territorios = alocarMapa(MAX_TERRITORIOS);
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Inicializar territórios automaticamente
    inicializarTerritorios(territorios, MAX_TERRITORIOS);

    // Definir cor do jogador
    char corJogador[MAX_STRING] = "Azul";

    // Sortear missão
    int missaoId = sortearMissao();

    printf("=================================================\n");
    printf("    BEM-VINDO AO WAR - NÍVEL MESTRE\n");
    printf("    Missões e Estratégia Total\n");
    printf("=================================================\n\n");

    printf("Você é o jogador com o exército %s!\n", corJogador);
    printf("\n--- SUA MISSÃO ---\n");
    exibirMissao(missaoId);

    // 2. Laço Principal do Jogo (Game Loop)
    int opcao;
    int jogoAtivo = 1;

    do {
        printf("\n=================================================\n");
        printf("           MAPA ATUAL DOS TERRITÓRIOS\n");
        printf("=================================================\n");
        exibirMapa(territorios, MAX_TERRITORIOS);

        exibirMenuPrincipal();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                // Atacar
                faseDeAtaque(territorios, MAX_TERRITORIOS);
                break;

            case 2:
                // Verificar Missão
                if (verificarVitoria(territorios, MAX_TERRITORIOS, missaoId, corJogador)) {
                    printf("\n=================================================\n");
                    printf("    PARABÉNS! VOCÊ COMPLETOU A MISSÃO!\n");
                    printf("    VITÓRIA CONQUISTADA!\n");
                    printf("=================================================\n");
                    jogoAtivo = 0;
                } else {
                    printf("\n[INFO] Missão ainda não concluída. Continue lutando!\n");
                    exibirMissao(missaoId);
                }
                break;

            case 0:
                // Sair
                printf("\n=================================================\n");
                printf("    SAINDO DO JOGO - ATÉ A PRÓXIMA!\n");
                printf("=================================================\n");
                jogoAtivo = 0;
                break;

            default:
                printf("\n[ERRO] Opção inválida!\n");
                break;
        }

        if (jogoAtivo && opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (jogoAtivo);

    // 3. Limpeza
    liberarMemoria(territorios);

    return 0;
}

// --- Implementação das Funções ---

Territorio* alocarMapa(int quantidade) {
    Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
    return mapa;
}

void inicializarTerritorios(Territorio* territorios, int quantidade) {
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

void exibirMenuPrincipal() {
    printf("\n=================================================\n");
    printf("           MENU PRINCIPAL\n");
    printf("=================================================\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");
    printf("=================================================\n");
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

void exibirMissao(int missaoId) {
    printf("\n=================================================\n");
    if (missaoId == MISSAO_DESTRUIR_VERDE) {
        printf("MISSÃO: Destruir o exército VERDE\n");
        printf("Conquiste todos os territórios verdes!\n");
    } else if (missaoId == MISSAO_CONQUISTAR_3_TERRITORIOS) {
        printf("MISSÃO: Conquistar 3 territórios\n");
        printf("Domine pelo menos 3 territórios com sua cor!\n");
    }
    printf("=================================================\n");
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

    if (strcmp(territorios[idAtacante - 1].corExercito, territorios[idDefensor - 1].corExercito) == 0) {
        printf("\n[ERRO] Não pode atacar território da mesma cor!\n");
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

int sortearMissao() {
    return (rand() % 2) + 1; // Retorna 1 ou 2
}

int verificarVitoria(const Territorio* territorios, int quantidade, int missaoId, const char* corJogador) {
    if (missaoId == MISSAO_DESTRUIR_VERDE) {
        // Verificar se não existe mais território Verde
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(territorios[i].corExercito, "Verde") == 0) {
                return 0; // Ainda existe exército Verde
            }
        }
        return 1; // Exército Verde foi destruído
    }
    else if (missaoId == MISSAO_CONQUISTAR_3_TERRITORIOS) {
        // Contar quantos territórios pertencem ao jogador
        int territoriosConquistados = 0;
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(territorios[i].corExercito, corJogador) == 0) {
                territoriosConquistados++;
            }
        }
        return territoriosConquistados >= 3;
    }

    return 0;
}

int rolarDado() {
    return 1 + (rand() % 6); // Retorna um número entre 1 e 6
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
