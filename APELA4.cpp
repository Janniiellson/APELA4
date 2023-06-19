#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FABRICANTES 5
#define MAX_PRODUTOS 50
#define UF_MAX_LENGTH 3

typedef struct {
    char marca[50];
    char site[100];
    char telefone[20];
    char UF[UF_MAX_LENGTH];
} Fabricante;

typedef struct {
    char descricao[100];
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    int fabricanteID;
} Produto;

// Funções para validar a entrada do usuário
int leValidaInteiro(int min, int max) {
    int valor;
    while (1) {
        scanf("%d", &valor);
        if (valor >= min && valor <= max)
            break;
        printf("Valor inválido. Digite novamente: ");
        getchar(); // Limpar o buffer do teclado
    }
    return valor;
}

float leValidaFloat(float min, float max) {
    float valor;
    while (1) {
        scanf("%f", &valor);
        if (valor >= min && valor <= max)
            break;
        printf("Valor inválido. Digite novamente: ");
        getchar(); // Limpar o buffer do teclado
    }
    return valor;
}

char* leValidaString(int tamanhoMax) {
    char* str = (char*)malloc(tamanhoMax * sizeof(char));
    if (str == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }
    fgets(str, tamanhoMax, stdin);
    str[strcspn(str, "\n")] = '\0';
    return str;
}

// Função para cadastrar um novo fabricante
void cadastrarFabricante(Fabricante* fabricantes, int* numFabricantes) {
    if (*numFabricantes >= MAX_FABRICANTES) {
        printf("Limite máximo de fabricantes atingido.\n");
        return;
    }

    Fabricante novoFabricante;

    printf("=== Cadastro de Fabricante ===\n");
    printf("Marca: ");
	getchar(); 
	fgets(novoFabricante.marca, sizeof(novoFabricante.marca), stdin);
	novoFabricante.marca[strcspn(novoFabricante.marca, "\n")] = '\0';
    
	printf("Site: ");
    fgets(novoFabricante.site, sizeof(novoFabricante.site), stdin);
    novoFabricante.site[strcspn(novoFabricante.site, "\n")] = '\0';

    printf("Telefone: ");
    fgets(novoFabricante.telefone, sizeof(novoFabricante.telefone), stdin);
    novoFabricante.telefone[strcspn(novoFabricante.telefone, "\n")] = '\0';

    printf("UF: ");
    fgets(novoFabricante.UF, sizeof(novoFabricante.UF), stdin);
    novoFabricante.UF[strcspn(novoFabricante.UF, "\n")] = '\0';

    fabricantes[*numFabricantes] = novoFabricante;
    (*numFabricantes)++;
    printf("Fabricante cadastrado com sucesso.\n");
}

// Função para cadastrar um novo produto
void cadastrarProduto(Produto* produtos, int* numProdutos, Fabricante* fabricantes, int numFabricantes) {
    if (*numProdutos >= MAX_PRODUTOS) {
        printf("Limite máximo de produtos atingido.\n");
        return;
    }

    Produto novoProduto;

    printf("=== Cadastro de Produto ===\n");
    printf("Descrição: ");
	getchar(); 
	fgets(novoProduto.descricao, sizeof(novoProduto.descricao), stdin);
	novoProduto.descricao[strcspn(novoProduto.descricao, "\n")] = '\0';
    
	printf("Peso: ");
    novoProduto.peso = leValidaFloat(0, 10000);

    printf("Valor de compra: ");
    novoProduto.valorCompra = leValidaFloat(0, 1000000);

    printf("Valor de venda: ");
    novoProduto.valorVenda = leValidaFloat(0, 1000000);

    printf("ID do fabricante: ");
    novoProduto.fabricanteID = leValidaInteiro(0, numFabricantes - 1);

    float lucro = novoProduto.valorVenda - novoProduto.valorCompra;
    novoProduto.valorLucro = lucro;
    novoProduto.percentualLucro = (lucro / novoProduto.valorCompra) * 100;

    produtos[*numProdutos] = novoProduto;
    (*numProdutos)++;
    printf("Produto cadastrado com sucesso.\n");
}

// Função para listar todas as marcas
void listarMarcas(Fabricante* fabricantes, int numFabricantes) {
    printf("=== Marcas Cadastradas ===\n");
    for (int i = 0; i < numFabricantes; i++) {
        printf("%s\n", fabricantes[i].marca);
    }
}

// Função para listar todos os produtos
void listarProdutos(Produto* produtos, int numProdutos, Fabricante* fabricantes, int numFabricantes) {
    printf("=== Produtos Cadastrados ===\n");
    for (int i = 0; i < numProdutos; i++) {
        Produto produto = produtos[i];
        Fabricante fabricante = fabricantes[produto.fabricanteID];
        printf("Descrição: %s\n", produto.descricao);
        printf("Peso: %.2f\n", produto.peso);
        printf("Valor de compra: %.2f\n", produto.valorCompra);
        printf("Valor de venda: %.2f\n", produto.valorVenda);
        printf("Valor do lucro: %.2f\n", produto.valorLucro);
        printf("Percentual de lucro: %.2f%%\n", produto.percentualLucro);
        printf("Fabricante: %s\n", fabricante.marca);
        printf("\n");
    }
}

// Função para listar os produtos de um determinado estado
void listarProdutosPorEstado(Produto* produtos, int numProdutos, Fabricante* fabricantes, int numFabricantes) {
    char estado[UF_MAX_LENGTH];
    printf("Digite o estado: ");
    fgets(estado, sizeof(estado), stdin);
    estado[strcspn(estado, "\n")] = '\0';

    printf("=== Produtos do Estado %s ===\n", estado);
    for (int i = 0; i < numProdutos; i++) {
        Produto produto = produtos[i];
        Fabricante fabricante = fabricantes[produto.fabricanteID];
        if (strcmp(fabricante.UF, estado) == 0) {
            printf("Descrição: %s\n", produto.descricao);
            printf("Peso: %.2f\n", produto.peso);
            printf("Valor de compra: %.2f\n", produto.valorCompra);
            printf("Valor de venda: %.2f\n", produto.valorVenda);
            printf("Valor do lucro: %.2f\n", produto.valorLucro);
            printf("Percentual de lucro: %.2f%%\n", produto.percentualLucro);
            printf("Fabricante: %s\n", fabricante.marca);
            printf("\n");
        }
    }
}

// Função para listar os produtos de uma determinada marca
void listarProdutosPorMarca(Produto* produtos, int numProdutos, Fabricante* fabricantes, int numFabricantes) {
    char marca[50];
    printf("Digite a marca: ");
    fgets(marca, sizeof(marca), stdin);
    marca[strcspn(marca, "\n")] = '\0';

    printf("=== Produtos da Marca %s ===\n", marca);
    for (int i = 0; i < numProdutos; i++) {
        Produto produto = produtos[i];
        Fabricante fabricante = fabricantes[produto.fabricanteID];
        if (strcmp(fabricante.marca, marca) == 0) {
            printf("Descrição: %s\n", produto.descricao);
            printf("Peso: %.2f\n", produto.peso);
            printf("Valor de compra: %.2f\n", produto.valorCompra);
            printf("Valor de venda: %.2f\n", produto.valorVenda);
            printf("Valor do lucro: %.2f\n", produto.valorLucro);
            printf("Percentual de lucro: %.2f%%\n", produto.percentualLucro);
            printf("Fabricante: %s\n", fabricante.marca);
            printf("\n");
        }
    }
}

// Função para encontrar o estado onde está registrado o produto mais caro
void encontrarEstadoProdutoMaisCaro(Produto* produtos, int numProdutos, Fabricante* fabricantes, int numFabricantes) {
    float valorMaisCaro = 0;
    char estadoMaisCaro[UF_MAX_LENGTH];

    for (int i = 0; i < numProdutos; i++) {
        Produto produto = produtos[i];
        Fabricante fabricante = fabricantes[produto.fabricanteID];
        if (produto.valorVenda > valorMaisCaro) {
            valorMaisCaro = produto.valorVenda;
            strcpy(estadoMaisCaro, fabricante.UF);
        }
    }

    printf("Produto mais caro registrado no estado %s\n", estadoMaisCaro);
}

// Função para encontrar o fabricante onde está registrado o produto mais barato
void encontrarFabricanteProdutoMaisBarato(Produto* produtos, int numProdutos, Fabricante* fabricantes, int numFabricantes) {
    float valorMaisBarato = produtos[0].valorVenda;
    char fabricanteMaisBarato[50];

    for (int i = 0; i < numProdutos; i++) {
        Produto produto = produtos[i];
        Fabricante fabricante = fabricantes[produto.fabricanteID];
        if (produto.valorVenda < valorMaisBarato) {
            valorMaisBarato = produto.valorVenda;
            strcpy(fabricanteMaisBarato, fabricante.marca);
        }
    }

    printf("Produto mais barato registrado pelo fabricante %s\n", fabricanteMaisBarato);
}

// Função para comparar valores para a ordenação dos produtos
int compararProdutosPorValor(const void* p1, const void* p2) {
    Produto* produto1 = (Produto*)p1;
    Produto* produto2 = (Produto*)p2;
    return produto1->valorVenda - produto2->valorVenda;
}

// Função para comparar valores para a ordenação dos produtos por valor de lucro
int compararProdutosPorLucro(const void* p1, const void* p2) {
    Produto* produto1 = (Produto*)p1;
    Produto* produto2 = (Produto*)p2;
    return produto1->valorLucro - produto2->valorLucro;
}

// Função para comparar valores para a ordenação dos produtos por percentual de lucro
int compararProdutosPorPercentualLucro(const void* p1, const void* p2) {
    Produto* produto1 = (Produto*)p1;
    Produto* produto2 = (Produto*)p2;
    return produto1->percentualLucro - produto2->percentualLucro;
}

// Função para ordenar e listar todos os produtos em ordem crescente de valor
void listarProdutosPorValor(Produto* produtos, int numProdutos, Fabricante* fabricantes, int numFabricantes) {
    qsort(produtos, numProdutos, sizeof(Produto), compararProdutosPorValor);

    printf("=== Produtos em Ordem Crescente de Valor ===\n");
    for (int i = 0; i < numProdutos; i++) {
        Produto produto = produtos[i];
        Fabricante fabricante = fabricantes[produto.fabricanteID];
        printf("Descrição: %s\n", produto.descricao);
        printf("Peso: %.2f\n", produto.peso);
        printf("Valor de compra: %.2f\n", produto.valorCompra);
        printf("Valor de venda: %.2f\n", produto.valorVenda);
        printf("Valor do lucro: %.2f\n", produto.valorLucro);
        printf("Percentual de lucro: %.2f%%\n", produto.percentualLucro);
        printf("Fabricante: %s\n", fabricante.marca);
        printf("\n");
    }
}

// Função para ordenar e listar todos os produtos em ordem crescente de valor de lucro
void listarProdutosPorLucro(Produto* produtos, int numProdutos, Fabricante* fabricantes, int numFabricantes) {
    qsort(produtos, numProdutos, sizeof(Produto), compararProdutosPorLucro);

    printf("=== Produtos em Ordem Crescente de Valor de Lucro ===\n");
    for (int i = 0; i < numProdutos; i++) {
        Produto produto = produtos[i];
        Fabricante fabricante = fabricantes[produto.fabricanteID];
        printf("Descrição: %s\n", produto.descricao);
        printf("Peso: %.2f\n", produto.peso);
        printf("Valor de compra: %.2f\n", produto.valorCompra);
        printf("Valor de venda: %.2f\n", produto.valorVenda);
        printf("Valor do lucro: %.2f\n", produto.valorLucro);
        printf("Percentual de lucro: %.2f%%\n", produto.percentualLucro);
        printf("Fabricante: %s\n", fabricante.marca);
        printf("\n");
    }
}

// Função para ordenar e listar todos os produtos em ordem crescente de percentual de lucro
void listarProdutosPorPercentualLucro(Produto* produtos, int numProdutos, Fabricante* fabricantes, int numFabricantes) {
    qsort(produtos, numProdutos, sizeof(Produto), compararProdutosPorPercentualLucro);

    printf("=== Produtos em Ordem Crescente de Percentual de Lucro ===\n");
    for (int i = 0; i < numProdutos; i++) {
        Produto produto = produtos[i];
        Fabricante fabricante = fabricantes[produto.fabricanteID];
        printf("Descrição: %s\n", produto.descricao);
        printf("Peso: %.2f\n", produto.peso);
        printf("Valor de compra: %.2f\n", produto.valorCompra);
        printf("Valor de venda: %.2f\n", produto.valorVenda);
        printf("Valor do lucro: %.2f\n", produto.valorLucro);
        printf("Percentual de lucro: %.2f%%\n", produto.percentualLucro);
        printf("Fabricante: %s\n", fabricante.marca);
        printf("\n");
    }
}

int main() {
    Fabricante* fabricantes = (Fabricante*)malloc(MAX_FABRICANTES * sizeof(Fabricante));
    if (fabricantes == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    Produto* produtos = (Produto*)malloc(MAX_PRODUTOS * sizeof(Produto));
    if (produtos == NULL) {
        printf("Erro de alocação de memória.\n");
        free(fabricantes);
        return 1;
    }

    int numFabricantes = 0;
    int numProdutos = 0;

    int opcao;

    do {
        printf("=== Menu ===\n");
        printf("1. Cadastrar fabricante\n");
        printf("2. Cadastrar produto\n");
        printf("3. Listar todas as marcas\n");
        printf("4. Listar todos os produtos\n");
        printf("5. Listar produtos por estado\n");
        printf("6. Listar produtos por marca\n");
        printf("7. Encontrar estado do produto mais caro\n");
        printf("8. Encontrar fabricante do produto mais barato\n");
        printf("9. Listar produtos em ordem crescente de valor\n");
        printf("10. Listar produtos em ordem crescente de valor de lucro\n");
        printf("11. Listar produtos em ordem crescente de percentual de lucro\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        opcao = leValidaInteiro(0, 11);

        switch (opcao) {
            case 1:
                cadastrarFabricante(fabricantes, &numFabricantes);
                break;
            case 2:
                cadastrarProduto(produtos, &numProdutos, fabricantes, numFabricantes);
                break;
            case 3:
                listarMarcas(fabricantes, numFabricantes);
                break;
            case 4:
                listarProdutos(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 5:
                listarProdutosPorEstado(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 6:
                listarProdutosPorMarca(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 7:
                encontrarEstadoProdutoMaisCaro(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 8:
                encontrarFabricanteProdutoMaisBarato(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 9:
                listarProdutosPorValor(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 10:
                listarProdutosPorLucro(produtos, numProdutos, fabricantes, numFabricantes);
                break;
            case 11:
                listarProdutosPorPercentualLucro(produtos, numProdutos, fabricantes, numFabricantes);
                break;
        }

        printf("\n");

    } while (opcao != 0);

    free(fabricantes);
    free(produtos);

    return 0;
}

