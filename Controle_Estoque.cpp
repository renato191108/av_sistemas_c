#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_NOME_PRODUTO 50
typedef int TIPOCHAVE;

typedef struct PRODUTO {
  TIPOCHAVE chave;
  char nome[MAX_NOME_PRODUTO];
  int quantidade;
  float preco;
} PRODUTO;

typedef struct aux {
  PRODUTO prod;
  struct aux *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct {
  PONT topo;
} PILHA;

// Prot�tipos das fun��es
void criarEstq(PILHA *p);
int verificarTamanhoEstq(PILHA *p);
void exibirElemEstq(PILHA *p);
void consultarElemEstq(PILHA *p, const char *nome);
void inserirElemEstqComID(PILHA *p, TIPOCHAVE id, const char *nome, int quantidade, float preco);
void alterarElemEstq(PILHA *p, const char *nome);
void excluirElemEstq(PILHA *p);
void salvarEstq(PILHA *p);
void reinicializarEstq(PILHA *p);
void carregarEstq(PILHA *p);

// Fun��o principal
int main() {
  PILHA estoque;

  char nomeProduto[MAX_NOME_PRODUTO];
  char nomePesquisa[MAX_NOME_PRODUTO];
  char opcaoApagar;
  int IDProduto;
  int quantProduto;
  float precoProduto;

  int opcao;

  criarEstq(&estoque);

  while (1) {
    printf("\n========== Controle de Estoque Hardw&Peripherals ==========\n");
    printf("1. Inserir Produto\n");
    printf("2. Excluir Produto\n");
    printf("3. Alterar Produto\n");
    printf("4. Exibir produtos\n");
    printf("5. Consultar Produto\n");
    printf("6. Limpar Estoque\n");
    printf("7. Salvar estoque\n");
    printf("8. Carregar estoque\n");
    printf("0. Sair\n\n");
    printf("QTD PROD ESTQ:%i\n\n", verificarTamanhoEstq(&estoque));
    printf("Escolha uma op��o: ");
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        printf("ID do produto: ");
        scanf("%d", &IDProduto);
        printf("Nome do produto: ");
        scanf(" %[^\n]", nomeProduto);
        printf("Quantidade: ");
        scanf("%d", &quantProduto);
        printf("Pre�o: ");
        scanf("%f", &precoProduto);
        inserirElemEstqComID(&estoque, IDProduto, nomeProduto, quantProduto, precoProduto);
        break;
      case 2:
        if (verificarTamanhoEstq(&estoque) == 0) {
          printf("\nEstoque vazio!\n");
          break;
        } else {
          printf("Confirmar? Esta a��o ir� apagar o �ltimo elemento do estoque (s/n): ");
          scanf("%s", &opcaoApagar);
          if(strcmp(&opcaoApagar, "s") == 0) {
            excluirElemEstq(&estoque);
          }
        }
        break;
      case 3:
        if (verificarTamanhoEstq(&estoque) == 0) {
          printf("\nEstoque vazio!\n");
          break;
        } else {
          printf("\nQual produto deseja modificar?\n>> ");
          scanf("%s", nomeProduto);
          alterarElemEstq(&estoque, nomeProduto);
        }
        break;
      case 4:
        if (verificarTamanhoEstq(&estoque) == 0) {
          printf("\nEstoque vazio!\n");
          break;
        } else {
          exibirElemEstq(&estoque);
        }
        break;
      case 5:
        if (verificarTamanhoEstq(&estoque) == 0) {
          printf("\nEstoque vazio!\n");
          break;
        } else {
          printf("Nome do produto: ");
          scanf("%s", nomePesquisa);
          consultarElemEstq(&estoque, nomePesquisa);
        }
        break;
      case 6:
        if (verificarTamanhoEstq(&estoque) == 0) {
          printf("\nEstoque vazio!\n");
          break;
        } else {
          reinicializarEstq(&estoque);
        }
        break;
      case 7: 
        salvarEstq(&estoque);
        printf("\n Estoque salvo!");
        break;
      case 8: 
        carregarEstq(&estoque);
        break;
      case 0:
        printf("\nPrograma encerrado.\n");
        return 0;
      default:
        printf("Op��o inv�lida. Tente novamente.\n");
        break;
    }
  }
  return 0;
}

void criarEstq(PILHA *p) { p->topo = NULL; }

int verificarTamanhoEstq(PILHA *p) {
  PONT end = p->topo;
  int tam = 0;
  while (end != NULL) {
    tam++;
    end = end->prox;
  }
  return tam;
}

void exibirElemEstq(PILHA *p) {
  PONT end = p->topo;
  printf("\nProdutos:\n");
  while (end != NULL) {
    printf("\n>> %s <<\n", end->prod.nome);
    printf("ID: %i\n", end->prod.chave);
    printf("NOME: %s\n", end->prod.nome);
    printf("QUANT: %d\n", end->prod.quantidade);
    printf("PRE�O: R$%f\n\n", end->prod.preco);
    end = end->prox;
  }
  printf("\n\n");
}

void consultarElemEstq(PILHA *p, const char *nome) {
  PONT end = p->topo;

  while (end != NULL) {
    if(strcmp(end->prod.nome, nome) == 0) {
      printf("\nProduto:\n");
      printf("\n>> %s <<\n", end->prod.nome);
      printf("ID: %i\n", end->prod.chave);
      printf("NOME: %s\n", end->prod.nome);
      printf("QUANT: %d\n", end->prod.quantidade);
      printf("PRE�O: R$%f\n\n", end->prod.preco);
      return;
    }
    end = end->prox;
  }
  printf("\nProduto n�o encontrado\n");
}

void inserirElemEstqComID(PILHA *p, TIPOCHAVE id, const char *nome, int quantidade, float preco) {
  PONT novoProd = (PONT)malloc(sizeof(ELEMENTO));
  novoProd->prod.chave = id;
  strcpy(novoProd->prod.nome, nome);
  novoProd->prod.quantidade = quantidade;
  novoProd->prod.preco = preco;
  novoProd->prox = p->topo;
  p->topo = novoProd;
}

void alterarElemEstq(PILHA *p, const char *nome) {
  PONT end = p->topo;
  int opcaoMudar;
  char novoNome[MAX_NOME_PRODUTO];
  int novaQuant;
  float novoPreco;

  while (end != NULL) {
    if(strcmp(end->prod.nome, nome) == 0) {
      while (opcaoMudar != 4) {
        printf("\n\nOque deseja alterar?\n");
        printf("1. Nome\n");
        printf("2. Quantidade\n");
        printf("3. Pre�o\n");
        printf("4. sair\n");
        printf(">> ");
        scanf("%i", &opcaoMudar);
        switch (opcaoMudar) {
          case 1:
            printf("\nNovo nome: ");
            scanf("%s", novoNome);
            strcpy(end->prod.nome, novoNome);
            break;
          case 2:
            printf("\nNova quantidade: ");
            scanf("%d", &novaQuant);
            end->prod.quantidade = novaQuant;
            break;
          case 3:
            printf("\nNovo pre�o: ");
            scanf("%f", &novoPreco);
            end->prod.preco = novoPreco;
            break;  
          case 4:
            printf("\n");
            return;
          default:
            printf("\nOp��o inv�lida. Tente novamente.\n");
            break;
        }
      }
      break;
    }
    end = end->prox;
  }
  printf("\nProduto n�o encontrado\n");
}

void excluirElemEstq(PILHA *p) {
  PONT end = p->topo;
  end->prod = p->topo->prod;
  PONT apagar = p->topo;
  p->topo = p->topo->prox;
  free(apagar);  
}

void salvarEstq(PILHA *p) { 
  char nomeArquivo[100];
  printf("Insira o nome do arquivo: ");
  scanf("%99s", nomeArquivo);
  getchar();

  nomeArquivo[strcspn(nomeArquivo, "\n")] = 0; 

  
  strcat(nomeArquivo, ".txt");

  FILE *file = fopen(nomeArquivo, "w"); 
  if (file == NULL) { 
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  PONT end = p->topo;
  while (end != NULL) {
    fprintf(file, "Produto: %s, Quantidade: %d, Pre�o: %f\n", end->prod.nome, end->prod.quantidade, end->prod.preco);
    end = end->prox;
  }
  fclose(file);
  reinicializarEstq(p);
}

void reinicializarEstq(PILHA *p) {
  PONT apagar;
  PONT posicao = p->topo;
  while (posicao != NULL) {
    apagar = posicao;
    posicao = posicao->prox;
    free(apagar);
  }
  p->topo = NULL;
}
  void carregarEstq(PILHA *p) {
    char nomeArquivo[100];
    printf("Insira o nome do arquivo a ser carregado (incluindo a extens�o .txt): ");
    scanf("%99s", nomeArquivo);
    getchar();

    FILE *file = fopen(nomeArquivo, "r"); 
    if (file == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return;
    }

    reinicializarEstq(p);

    PRODUTO prod;
    TIPOCHAVE id = 0;

    while (fscanf(file, "Produto: %49[^,], Quantidade: %d, Pre�o: %f\n", prod.nome, &prod.quantidade, &prod.preco) == 3) {
      PONT novoProd = (PONT)malloc(sizeof(ELEMENTO));
      novoProd->prod.chave = id++;
      strcpy(novoProd->prod.nome, prod.nome);
      novoProd->prod.quantidade = prod.quantidade;
      novoProd->prod.preco = prod.preco;

      novoProd->prox = p->topo;
      p->topo = novoProd;
    }

    fclose(file);
    printf("Estoque carregado com sucesso!\n");
  }
