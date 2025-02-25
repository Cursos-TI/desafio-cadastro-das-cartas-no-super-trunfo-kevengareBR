#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ESTADOS 8  // Estados de A até H
#define CIDADES_POR_ESTADO 4  // Cada estado tem 4 cidades

// Estrutura para armazenar os dados de uma cidade
typedef struct {
    char codigo[4];  // Exemplo: "A01", "B03"
    char nome[100];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
} Cidade;

// Estrutura para armazenar os estados
typedef struct {
    char letra;
    Cidade cidades[CIDADES_POR_ESTADO];
} Estado;

// Inicializa os estados com suas respectivas letras (A até H)
void inicializarEstados(Estado estados[]) {
    for (int i = 0; i < NUM_ESTADOS; i++) {
        estados[i].letra = 'A' + i;  // A, B, C, ..., H
        for (int j = 0; j < CIDADES_POR_ESTADO; j++) {
            estados[i].cidades[j].populacao = 0; // Define cidades como não cadastradas
        }
    }
}

// Cadastra uma nova cidade dentro de um estado
void cadastrarCidade(Estado *estado, int num_cidade) {
    if (num_cidade < 1 || num_cidade > CIDADES_POR_ESTADO) {
        printf("Número da cidade inválido!\n");
        return;
    }

    Cidade *cidade = &estado->cidades[num_cidade - 1];

    printf("\n--- Cadastro da Cidade %c%02d ---\n", estado->letra, num_cidade);
    sprintf(cidade->codigo, "%c%02d", estado->letra, num_cidade);

    printf("Nome da cidade: ");
    scanf(" %[^\n]", cidade->nome);

    printf("População: ");
    scanf("%d", &cidade->populacao);

    printf("Área (km²): ");
    scanf("%f", &cidade->area);

    printf("PIB (em bilhões de reais): ");
    scanf("%f", &cidade->pib);

    printf("Número de pontos turísticos: ");
    scanf("%d", &cidade->pontos_turisticos);

    // Cálculo das novas propriedades
    cidade->densidade_populacional = cidade->populacao / cidade->area;
    cidade->pib_per_capita = cidade->pib * 1000000000 / cidade->populacao; // PIB em reais

    printf("Cidade cadastrada com sucesso!\n");
}

// Exibe todas as cidades cadastradas
void exibirCidades(Estado estados[]) {
    printf("\n=== Lista de Cidades ===\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        printf("\n>>> Estado %c\n", estados[i].letra);
        for (int j = 0; j < CIDADES_POR_ESTADO; j++) {
            Cidade *cidade = &estados[i].cidades[j];
            if (cidade->populacao > 0) { // Só exibe se cadastrada
                printf("\n   --- Cidade %s ---\n", cidade->codigo);
                printf("   Nome: %s\n", cidade->nome);
                printf("   População: %d habitantes\n", cidade->populacao);
                printf("   Área: %.2f km²\n", cidade->area);
                printf("   PIB: R$ %.2f bilhões\n", cidade->pib);
                printf("   Pontos Turísticos: %d\n", cidade->pontos_turisticos);
                printf("   Densidade Populacional: %.2f hab/km²\n", cidade->densidade_populacional);
                printf("   PIB per capita: R$ %.2f\n", cidade->pib_per_capita);
            }
        }
    }
}

// Compara duas cidades com base em uma propriedade específica e retorna a carta vencedora
void compararCidades(Cidade *cidade1, Cidade *cidade2, char *propriedade) {
    printf("\n--- Comparação de %s ---\n", propriedade);
    if (strcmp(propriedade, "densidade_populacional") == 0) {
        if (cidade1->densidade_populacional < cidade2->densidade_populacional) {
            printf("Cidade %s vence!\n", cidade1->nome);
        } else if (cidade1->densidade_populacional > cidade2->densidade_populacional) {
            printf("Cidade %s vence!\n", cidade2->nome);
        } else {
            printf("Empate em densidade populacional!\n");
        }
    } else if (strcmp(propriedade, "pib_per_capita") == 0) {
        if (cidade1->pib_per_capita > cidade2->pib_per_capita) {
            printf("Cidade %s vence!\n", cidade1->nome);
        } else if (cidade1->pib_per_capita < cidade2->pib_per_capita) {
            printf("Cidade %s vence!\n", cidade2->nome);
        } else {
            printf("Empate em PIB per capita!\n");
        }
    } else if (strcmp(propriedade, "populacao") == 0) {
        if (cidade1->populacao > cidade2->populacao) {
            printf("Cidade %s vence!\n", cidade1->nome);
        } else if (cidade1->populacao < cidade2->populacao) {
            printf("Cidade %s vence!\n", cidade2->nome);
        } else {
            printf("Empate em população!\n");
        }
    } else if (strcmp(propriedade, "area") == 0) {
        if (cidade1->area < cidade2->area) {
            printf("Cidade %s vence!\n", cidade1->nome);
        } else if (cidade1->area > cidade2->area) {
            printf("Cidade %s vence!\n", cidade2->nome);
        } else {
            printf("Empate em área!\n");
        }
    } else if (strcmp(propriedade, "pib") == 0) {
        if (cidade1->pib > cidade2->pib) {
            printf("Cidade %s vence!\n", cidade1->nome);
        } else if (cidade1->pib < cidade2->pib) {
            printf("Cidade %s vence!\n", cidade2->nome);
        } else {
            printf("Empate em PIB!\n");
        }
    } else if (strcmp(propriedade, "pontos_turisticos") == 0) {
        if (cidade1->pontos_turisticos > cidade2->pontos_turisticos) {
            printf("Cidade %s vence!\n", cidade1->nome);
        } else if (cidade1->pontos_turisticos < cidade2->pontos_turisticos) {
            printf("Cidade %s vence!\n", cidade2->nome);
        } else {
            printf("Empate em pontos turísticos!\n");
        }
    }
}

// Função principal do jogo
int main() {
    Estado estados[NUM_ESTADOS];
    inicializarEstados(estados);

    char opcao;
    while (1) {
        printf("\n=== Super Trunfo - Países ===\n");
        printf("1 - Cadastrar Cidade\n");
        printf("2 - Exibir Cidades\n");
        printf("3 - Comparar Cidades\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1': {
                char estado_letra;
                int cidade_num;

                printf("\nEscolha um estado (A-H): ");
                scanf(" %c", &estado_letra);

                // Converter para maiúsculo
                if (estado_letra >= 'a' && estado_letra <= 'h') {
                    estado_letra -= 32;
                }

                // Verifica se o estado é válido
                if (estado_letra < 'A' || estado_letra > 'H') {
                    printf("Estado inválido!\n");
                    break;
                }

                printf("Escolha uma cidade (1-4): ");
                scanf("%d", &cidade_num);

                cadastrarCidade(&estados[estado_letra - 'A'], cidade_num);
                break;
            }

            case '2':
                exibirCidades(estados);
                break;

            case '3': {
                char estado1, estado2;
                int cidade1_num, cidade2_num;

                printf("\nEscolha o primeiro estado (A-H): ");
                scanf(" %c", &estado1);
                printf("Escolha a primeira cidade (1-4): ");
                scanf("%d", &cidade1_num);

                // Converter para maiúsculo
                if (estado1 >= 'a' && estado1 <= 'h') {
                    estado1 -= 32;
                }

                printf("\nEscolha o segundo estado (A-H): ");
                scanf(" %c", &estado2);
                printf("Escolha a segunda cidade (1-4): ");
                scanf("%d", &cidade2_num);

                // Converter para maiúsculo
                if (estado2 >= 'a' && estado2 <= 'h') {
                    estado2 -= 32;
                }

                compararCidades(&estados[estado1 - 'A'].cidades[cidade1_num - 1], &estados[estado2 - 'A'].cidades[cidade2_num - 1], "populacao");
                compararCidades(&estados[estado1 - 'A'].cidades[cidade1_num - 1], &estados[estado2 - 'A'].cidades[cidade2_num - 1], "area");
                compararCidades(&estados[estado1 - 'A'].cidades[cidade1_num - 1], &estados[estado2 - 'A'].cidades[cidade2_num - 1], "pib");
                compararCidades(&estados[estado1 - 'A'].cidades[cidade1_num - 1], &estados[estado2 - 'A'].cidades[cidade2_num - 1], "pontos_turisticos");
                compararCidades(&estados[estado1 - 'A'].cidades[cidade1_num - 1], &estados[estado2 - 'A'].cidades[cidade2_num - 1], "densidade_populacional");
                compararCidades(&estados[estado1 - 'A'].cidades[cidade1_num - 1], &estados[estado2 - 'A'].cidades[cidade2_num - 1], "pib_per_capita");
                break;
            }

            case '4':
                printf("\nSaindo...\n");
                return 0;

            default:
                printf("\nOpção inválida!\n");
        }
    }

    return 0;
}
