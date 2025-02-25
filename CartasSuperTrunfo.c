#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura para armazenar informações sobre uma cidade
typedef struct {
    char codigo[4];  // Código da cidade, por exemplo: "A01", "B03"
    char nome[100];  // Nome da cidade
    int populacao;   // População da cidade
    float area;      // Área da cidade (em km²)
    float pib;       // PIB da cidade (em bilhões de reais)
    int pontos_turisticos;  // Número de pontos turísticos na cidade
} Cidade;

// Função para cadastrar uma nova cidade
void cadastrarCidade(Cidade *cidade) {
    // Solicitando e armazenando o nome da cidade
    printf("Nome da cidade: ");
    scanf(" %d[^\n]", cidade->nome); // %[^\n] permite ler uma string com espaços

    // Solicitando e armazenando a população da cidade
    printf("População: ");
    scanf("%d", &cidade->populacao);

    // Solicitando e armazenando a área da cidade
    printf("Área (km²): ");
    scanf("%f", &cidade->area);

    // Solicitando e armazenando o PIB da cidade
    printf("PIB (em bilhões de reais): ");
    scanf("%f", &cidade->pib);

    // Solicitando e armazenando o número de pontos turísticos da cidade
    printf("Número de pontos turísticos: ");
    scanf("%d", &cidade->pontos_turisticos);

    // Gerando o código da cidade (ex: "C01", "C02", ...)
    // O código é gerado com base no índice da cidade no vetor, por exemplo, "C01" para a primeira cidade
    sprintf(cidade->codigo, "C%02d", (int)(cidade - cidade) + 1); 
}

// Função para exibir os dados de uma cidade
void exibirCidade(const Cidade *cidade) {
    // Exibindo as informações da cidade
    printf("Nome: %s\n", cidade->nome);
    printf("População: %d habitantes\n", cidade->populacao);
    printf("Área: %.2f km²\n", cidade->area);
    printf("PIB: R$ %.2f bilhões\n", cidade->pib);
    printf("Pontos Turísticos: %d\n", cidade->pontos_turisticos);
}

#define NUM_CIDADES 4  // Definindo o número de cidades a serem cadastradas

// Função principal
int main() {
    // Criando um vetor de cidades
    Cidade cidades[NUM_CIDADES];

    // Loop para cadastrar todas as cidades
    for (int i = 0; i < NUM_CIDADES; i++) {
        printf("\nCadastro da Cidade %d:\n", i + 1);  // Exibe qual cidade está sendo cadastrada
        cadastrarCidade(&cidades[i]);  // Chama a função para cadastrar a cidade
    }

    // Exibindo a lista de cidades cadastradas
    printf("\n=== Lista de Cidades ===\n");
    for (int i = 0; i < NUM_CIDADES; i++) {
        printf("\n--- Cidade %d ---\n", i + 1);  // Exibe qual cidade está sendo exibida
        exibirCidade(&cidades[i]);  // Chama a função para exibir as informações da cidade
    }

    return 0;  // Finaliza o programa
}
