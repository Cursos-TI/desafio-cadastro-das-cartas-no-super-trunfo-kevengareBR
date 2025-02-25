#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ESTADOS 8  // Definindo o número de estados (A até H)
#define CIDADES_POR_ESTADO 4  // Cada estado tem 4 cidades

// Estrutura para armazenar os dados de uma cidade
typedef struct {
    char codigo[4];  // Exemplo de código da cidade: "A01", "B03"
    char nome[100];  // Nome da cidade
    int populacao;   // População da cidade
    float area;      // Área da cidade (em km²)
    float pib;       // PIB da cidade (em bilhões de reais)
    int pontos_turisticos;  // Número de pontos turísticos da cidade
    float densidade_populacional;  // Densidade populacional calculada (população/área)
    float pib_per_capita;  // PIB per capita calculado (PIB/população)
} Cidade;

// Estrutura para armazenar os estados
typedef struct {
    char letra;  // Letra do estado (A até H)
    Cidade cidades[CIDADES_POR_ESTADO];  // Vetor de cidades para cada estado
} Estado;

// Inicializa os estados com suas respectivas letras (A até H) e define as cidades com população 0 (não cadastrada)
void inicializarEstados(Estado estados[]) {
    for (int i = 0; i < NUM_ESTADOS; i++) {
        estados[i].letra = 'A' + i;  // Atribui as letras A até H aos estados
        for (int j = 0; j < CIDADES_POR_ESTADO; j++) {
            estados[i].cidades[j].populacao = 0;  // Inicializa as cidades com população 0 (não cadastradas)
        }
    }
}

// Função para cadastrar uma nova cidade dentro de um estado
void cadastrarCidade(Estado *estado, int num_cidade) {
    // Valida se o número da cidade está correto (1 a 4)
    if (num_cidade < 1 || num_cidade > CIDADES_POR_ESTADO) {
        printf("Número da cidade inválido!\n");
        return;
    }

    Cidade *cidade = &estado->cidades[num_cidade - 1];  // Aponta para a cidade selecionada no estado

    printf("\n--- Cadastro da Cidade %c%02d ---\n", estado->letra, num_cidade);
    // Gera o código da cidade, como "A01", "B03", etc.
    sprintf(cidade->codigo, "%c%02d", estado->letra, num_cidade);

    // Coleta informações da cidade
    printf("Nome da cidade: ");
    scanf(" %d[^\n]", cidade->nome);  // Leitura do nome da cidade (permitindo espaços)

    printf("População: ");
    scanf("%d", &cidade->populacao);

    printf("Área (km²): ");
    scanf("%f", &cidade->area);

    printf("PIB (em bilhões de reais): ");
    scanf("%f", &cidade->pib);

    printf("Número de pontos turísticos: ");
    scanf("%d", &cidade->pontos_turisticos);

    // Calcula a densidade populacional (população/área)
    cidade->densidade_populacional = cidade->populacao / cidade->area;
    // Calcula o PIB per capita (PIB/população), convertendo o PIB para reais
    cidade->pib_per_capita = cidade->pib * 1000000000 / cidade->populacao; 

    printf("Cidade cadastrada com sucesso!\n");
}

// Função para exibir todas as cidades cadastradas
void exibirCidades(Estado estados[]) {
    printf("\n=== Lista de Cidades ===\n");
    // Loop pelos estados (A até H)
    for (int i = 0; i < NUM_ESTADOS; i++) {
        printf("\n>>> Estado %c\n", estados[i].letra);
        // Loop pelas cidades de cada estado
        for (int j = 0; j < CIDADES_POR_ESTADO; j++) {
            Cidade *cidade = &estados[i].cidades[j];
            if (cidade->populacao > 0) {  // Só exibe cidades que têm população cadastrada
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

// Função principal que gerencia o jogo
int main() {
    Estado estados[NUM_ESTADOS];  // Array para armazenar os estados
    inicializarEstados(estados);  // Inicializa os estados com as letras A a H

    char opcao;  // Variável para armazenar a opção escolhida pelo usuário
    while (1) {
        printf("\n=== Super Trunfo - Países ===\n");
        printf("1 - Cadastrar Cidade\n");
        printf("2 - Exibir Cidades\n");
        printf("3 - Sair\n");
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);  // Leitura da opção escolhida

        // Menu de opções
        switch (opcao) {
            case '1': {
                char estado_letra;
                int cidade_num;

                // Solicita o estado (A a H)
                printf("\nEscolha um estado (A-H): ");
                scanf(" %c", &estado_letra);

                // Converte a letra do estado para maiúscula
                if (estado_letra >= 'a' && estado_letra <= 'h') {
                    estado_letra -= 32;
                }

                // Verifica se o estado é válido
                if (estado_letra < 'A' || estado_letra > 'H') {
                    printf("Estado inválido!\n");
                    break;
                }

                // Solicita o número da cidade (1 a 4)
                printf("Escolha uma cidade (1-4): ");
                scanf("%d", &cidade_num);

                // Cadastra a cidade
                cadastrarCidade(&estados[estado_letra - 'A'], cidade_num);
                break;
            }

            case '2':
                // Exibe todas as cidades cadastradas
                exibirCidades(estados);
                break;

            case '3':
                printf("\nSaindo...\n");
                return 0;  // Encerra o programa

            default:
                printf("\nOpção inválida!\n");
        }
    }

    return 0;  // Encerra a função main
}
