#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tipoNo {
  char nome[100];
  tipoNo *esq;
  tipoNo *dir;
  int altura;
}TNo;

TNo *raiz;

void inicializa(TNo **R);
TNo *criaNo(char *nome);
void insere(TNo **R, char *nome);
int fatorBalanceamento(TNo *R);
int altura(TNo *R);
TNo *busca(TNo *R, char *nome);
TNo *exclui(TNo *R, char *nome);
TNo *rotacaoDireita(TNo *y);
TNo *rotacaoEsquerda(TNo *x);
int max(int a, int b);
void balancear(TNo **R);
void exibir_arvore(TNo *raiz, int nivel);
TNo *menor_valor_no(TNo *raiz);
void caminhamento_Em_Ordem(TNo *R);
void caminhamento_Pre_Ordem(TNo *R);
void caminhamento_Pos_Ordem(TNo *R);

int main(){

    inicializa(&raiz);

    printf("\nINSERINDO...\n");
	
	  insere(&raiz, "Andressa");
    insere(&raiz, "Paula");
    insere(&raiz, "Rodrigo");
    insere(&raiz, "Carlos");
    insere(&raiz, "Souza");
    insere(&raiz, "Lina");
    insere(&raiz, "Sofia");
    insere(&raiz, "Joao");
    insere(&raiz, "Wanessa");

    printf("\n\n�rvore antes do balanceamento:\n");
    exibir_arvore(raiz, 0);

    // Balancear a �rvore
    balancear(&raiz);

    printf("\n\n�rvore ap�s o balanceamento:\n");
    exibir_arvore(raiz, 0);

    printf("\n=================================\n");

    //Inicio das sa�das
    printf("\n\n\tCaminhamento EM ORDEM: ");
    caminhamento_Em_Ordem(raiz);

    printf("\n\n\tCaminhamento PR� ORDEM: ");
    caminhamento_Pre_Ordem(raiz);

    printf("\n\n\tCaminhamento POS ORDEM: ");
    caminhamento_Pos_Ordem(raiz);

    printf("\n\n=================================\n");

    printf("\nBUSCA:\n");
    printf("\n\n\tBuscando NO com o nome 'Maria':\n");
    TNo *atual = busca(raiz, "Maria");
    
	if (atual != NULL) {
      printf("\n\tEncontrado: %s", atual->nome);
  }
    else{
      printf("\n\tNome NAO ENCONTRADO!!!");
  }

    printf("\n\nEXCLUSAO:\n");
    printf("\n\n\tExcluindo NO com o nome 'Maria':");
    raiz = exclui(raiz, "Maria");
    printf("\n=================================\n");

	printf("\n\n�rvore depois da exclus�o:\n");
    exibir_arvore(raiz, 0);
	
    printf("\n\n\tCaminhamento EM ORDEM apos exclusao: ");
    caminhamento_Em_Ordem(raiz);

    printf("\n\n\tCaminhamento PR� ORDEM apos exclusao: ");
    caminhamento_Pre_Ordem(raiz);

    printf("\n\n\tCaminhamento POS ORDEM pos exclusao: ");
    caminhamento_Pos_Ordem(raiz); 

  return 0;

}

//=====| FUN��ES |====================================================

void inicializa(TNo **R)
{
  *R = NULL;
}

//====================================================================

TNo *criaNo(char *nome)
{
  TNo *novo = (TNo *)malloc(sizeof(TNo));
  strcpy(novo->nome, nome);
  novo->esq = NULL;
  novo->dir = NULL;
  novo->altura = 1;
  return novo;
}

//====================================================================

int altura(TNo *R) 
{
  if (R == NULL) 
  {
    return 0;
  }

  return R->altura;

}

//====================================================================

int max(int a, int b) 
{
    if (a > b) 
  {
        return a;
    } else 
  {
        return b;
    }
}

//====================================================================

int fatorBalanceamento(TNo *R) 
{
    if (R == NULL) 
  {
        return 0;
    }

  return altura(R->esq) - altura(R->dir);
}

//====================================================================

void insere(TNo **R, char *nome) 
{
    if (*R == NULL) {
        *R = criaNo(nome);
    }

    if (strcmp(nome, (*R)->nome) < 0) 
  {
      insere(&(*R)->esq, nome);
  }
    else if (strcmp(nome, (*R)->nome) > 0) 
  {

      insere(&(*R)->dir, nome);
  }

    (*R)->altura = 1 + max(altura((*R)->esq), altura((*R)->dir));
}

//====================================================================

TNo *rotacaoDireita(TNo *y) 
{
    TNo *x = y->esq;
    TNo *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

//====================================================================

TNo *rotacaoEsquerda(TNo *x) 
{
    TNo *y = x->dir;
    TNo *T1 = y->esq;

    y->esq = x;
    x->dir = T1;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

//====================================================================

TNo *busca(TNo *R, char *nome) 
{
    if (R == NULL) {
        printf("\nNome n�o encontrado na �rvore.\n");
        return NULL;
    } else if (strcmp(nome, R->nome) == 0) {
        printf("\nNome %s encontrado na �rvore.\n", R->nome);
        return R;
    } else if (strcmp(nome, R->nome) > 0) {
        printf("\nVisitando %s e DESCENDO pela DIREITA...", R->nome);
        return busca(R->dir, nome);
    } else {
        printf("\nVisitando %s e DESCENDO pela ESQUERDA...", R->nome);
        return busca(R->esq, nome);
    }
}
//====================================================================

TNo *menor_valor_no(TNo *no) 
{
    TNo *atual = no;
    while (atual && atual->esq != NULL) {
      atual = atual->esq;
  }
    return atual;
}

//====================================================================

TNo *exclui(TNo *R, char *argumento) 
{
   if (R == NULL) {
        return R;
    }
    if (strcmp(argumento, R->nome) < 0) {
        R->esq = exclui(R->esq, argumento);
    } else if (strcmp(argumento, R->nome) > 0) {
        R->dir = exclui(R->dir, argumento);
    } else {
        if (R->esq == NULL || R->dir == NULL) {
            TNo *aux;
            if (R->esq != NULL) {
                aux = R->esq;
            } else {
                aux = R->dir;
            }
            if (aux == NULL) {
                aux = R;
                R = NULL;
            } else {
                *R = *aux;
            }
            free(aux);
        } else {
            TNo *aux = menor_valor_no(R->dir);
            strcpy(R->nome, aux->nome);
            R->dir = exclui(R->dir, aux->nome);
        }
    }

  if (R == NULL) {
        return R;
    }
    R->altura = 1 + max(altura(R->esq), altura(R->dir));
}

//==========================================================================

void exibir_arvore(TNo *no, int nivel) 
{
    if (no == NULL) {
      return ;
  }

    exibir_arvore(no->dir, nivel + 1);
    for (int i = 0; i < nivel; i++) printf("     ");
    printf("%s\n", no->nome);
    exibir_arvore(no->esq, nivel + 1);
}

//==========================================================================

void balancear(TNo **R) 
{
    if (*R == NULL) return;

    (*R)->altura = 1 + max(altura((*R)->esq), altura((*R)->dir));

    int balanceamento = fatorBalanceamento(*R);

    if (balanceamento > 1) {
        if (fatorBalanceamento((*R)->esq) >= 0) {
            *R = rotacaoDireita(*R);
        } else {
            (*R)->esq = rotacaoEsquerda((*R)->esq);
            *R = rotacaoDireita(*R);
        }
    } else if (balanceamento < -1) {
        if (fatorBalanceamento((*R)->dir) <= 0) {
            *R = rotacaoEsquerda(*R);
        } else {
            (*R)->dir = rotacaoDireita((*R)->dir);
            *R = rotacaoEsquerda(*R);
        }
    }

    balancear(&(*R)->esq);
    balancear(&(*R)->dir);
}

//==========================================================================
void caminhamento_Em_Ordem(TNo *R)
{
  if (R != NULL){
    caminhamento_Em_Ordem(R->esq);
    printf(" %s, ", R->nome);
    caminhamento_Em_Ordem(R->dir);
  }
}

//==========================================================================

void caminhamento_Pre_Ordem(TNo *R)
{
  if(R != NULL){
    printf(" %s, ", R->nome);
    caminhamento_Pre_Ordem(R->esq);
    caminhamento_Pre_Ordem(R->dir);
  }
}

//==========================================================================

void caminhamento_Pos_Ordem(TNo *R)
{
  if(R != NULL)
  {
    caminhamento_Pos_Ordem(R->esq);
    caminhamento_Pos_Ordem(R->dir);
    printf(" %s,", R->nome);
  }
}

//==================================================================