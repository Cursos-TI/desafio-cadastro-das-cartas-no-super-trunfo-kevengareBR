#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo o número de estados (de A até H) e o número de cidades por estado (4 cidades)
#define NUM_ESTADOS 8  // Estados de A até H
#define CIDADES_POR_ESTADO 4  // Cada estado tem 4 cidades

// Estrutura que define os dados de uma cidade
typedef struct {
    char codigo[4];  // Exemplo: "A01", "B03" (Código único para cada cidade)
    char nome[100];  // Nome da cidade
    int populacao;   // População da cidade
    float area;      // Área da cidade em km²
    float pib;       // PIB da cidade em bilhões de reais
    int pontos_turisticos; // Número de pontos turísticos da cidade
    float densidade_populacional;  // Densidade populacional (habitantes por km²)
    float pib_per_capita;  // PIB per capita (em reais)
} Cidade;

// Estrutura que define os dados de um estado
typedef struct {
    char letra;  // Letra do estado (A, B, C, ..., H)
    Cidade cidades[CIDADES_POR_ESTADO];  // Vetor de cidades no estado
} Estado;

// Função para inicializar os estados e suas cidades
void inicializarEstados(Estado estados[]) {
    for (int i = 0; i < NUM_ESTADOS; i++) {
        estados[i].letra = 'A' + i;  // Atribui letras de A a H aos estados
        for (int j = 0; j < CIDADES_POR_ESTADO; j++) {
            estados[i].cidades[j].populacao = 0; // Inicializa as cidades com população zero (não cadastradas)
        }
    }
}

// Função para cadastrar uma nova cidade dentro de um estado
void cadastrarCidade(Estado *estado, int num_cidade) {
    if (num_cidade < 1 || num_cidade > CIDADES_POR_ESTADO) {
        printf("Número da cidade inválido!\n");
        return;  // Verifica se o número da cidade é válido
    }

    Cidade *cidade = &estado->cidades[num_cidade - 1]; // Acessa a cidade no vetor de cidades

    // Realiza o cadastro de dados para a cidade
    printf("\n--- Cadastro da Cidade %c%02d ---\n", estado->letra, num_cidade);
    sprintf(cidade->codigo, "%c%02d", estado->letra, num_cidade);  // Cria um código único para a cidade

    // Coleta os dados da cidade
    printf("Nome da cidade: ");
    scanf(" %[^\n]", cidade->nome);  // Recebe o nome da cidade

    printf("População: ");
    scanf("%", &cidade->populacao);  // Recebe a população da cidade

    printf("Área (km²): ");
    scanf("%f", &cidade->area);  // Recebe a área da cidade

    printf("PIB (em bilhões de reais): ");
    scanf("%f", &cidade->pib);  // Recebe o PIB da cidade

    printf("Número de pontos turísticos: ");
    scanf("%d", &cidade->pontos_turisticos);  // Recebe o número de pontos turísticos da cidade

    // Calcula novas propriedades da cidade com base nos dados cadastrados
    cidade->densidade_populacional = cidade->populacao / cidade->area;  // Calcula a densidade populacional
    cidade->pib_per_capita = cidade->pib * 1000000000 / cidade->populacao;  // Calcula o PIB per capita (em reais)

    printf("Cidade cadastrada com sucesso!\n");
}

// Função para exibir todas as cidades cadastradas
void exibirCidades(Estado estados[]) {
    printf("\n=== Lista de Cidades ===\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {  // Percorre todos os estados
        printf("\n>>> Estado %c\n", estados[i].letra);  // Exibe o estado
        for (int j = 0; j < CIDADES_POR_ESTADO; j++) {  // Percorre todas as cidades de um estado
            Cidade *cidade = &estados[i].cidades[j];
            if (cidade->populacao > 0) {  // Só exibe a cidade se ela tiver sido cadastrada (população > 0)
                // Exibe os dados da cidade
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

// Função para comparar duas cidades com base em uma propriedade específica (como densidade populacional, PIB, etc.)
void compararCidades(Cidade *cidade1, Cidade *cidade2, char *propriedade) {
    printf("\n--- Comparação de %s ---\n", propriedade);  // Exibe o tipo de propriedade que será comparada
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

// Função principal que interage com o usuário
int main() {
    Estado estados[NUM_ESTADOS];  // Array de estados
    inicializarEstados(estados);  // Inicializa os estados

    char opcao;
    while (1) {  // Loop principal do programa
        // Menu de opções
        printf("\n=== Super Trunfo - Países ===\n");
        printf("1 - Cadastrar Cidade\n");
        printf("2 - Exibir Cidades\n");
        printf("3 - Comparar Cidades\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);  // Lê a opção do usuário

        switch (opcao) {
            case '1': {  // Cadastrar cidade
                char estado_letra;
                int cidade_num;

                printf("\nEscolha um estado (A-H): ");
                scanf(" %c", &estado_letra);

                // Converte a letra do estado para maiúsculo se necessário
                if (estado_letra >= 'a' && estado_letra <= 'h') {
                    estado_letra -= 32;
                }

                // Verifica se o estado é válido
                if (estado_letra < 'A' || estado_letra > 'H') {
                    printf("Estado inválido!\n");
                    break;
                }

                printf("Escolha uma cidade (1-4): ");
                scanf("%d", &cidade_num);  // Escolhe a cidade a ser cadastrada

                // Chama a função para cadastrar a cidade
                cadastrarCidade(&estados[estado_letra - 'A'], cidade_num);
                break;
            }

            case '2':  // Exibir cidades cadastradas
                exibirCidades(estados);
                break;

            case '3': {  // Comparar cidades
                char estado1, estado2;
                int cidade1_num, cidade2_num;

                printf("\nEscolha o primeiro estado (A-H): ");
                scanf(" %c", &estado1);
                printf("Escolha a primeira cidade (1-4): ");
                scanf("%d", &cidade1_num);

                // Converte para maiúsculo
                if (estado1 >= 'a' && estado1 <= 'h') {
                    estado1 -= 32;
                }

                printf("\nEscolha o segundo estado (A-H): ");
                scanf(" %c", &estado2);
                printf("Escolha a segunda cidade (1-4): ");
                scanf("%d", &cidade2_num);

                // Converte para maiúsculo
                if (estado2 >= 'a' && estado2 <= 'h') {
                    estado2 -= 32;
                }

                // Compara cidades com base em várias propriedades
                compararCidades(&estados[estado1 - 'A'].cidades[cidade1_num - 1],
                                &estados[estado2 - 'A'].cidades[cidade2_num - 1], "densidade_populacional");
                break;
            }

            case '4':  // Sair do programa
                printf("Saindo...\n");
                exit(0);

            default:  // Opção inválida
                printf("Opção inválida!\n");
        }
    }

    return 0;
}
