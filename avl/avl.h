/**
 * @description: Programa que contém os cabeçalhos das funções e a estrutura de dados do algoritmo da árvore AVL (Adelson-Velskii e Landis)
 * @author: Prof. Pablo Rangel, D.Sc.
 * @date: 20-10-2017
 */

#define POS_REL_RAIZ 	-1
#define POS_REL_ESQ 	 0
#define POS_REL_DIR 	 1

struct AVL{
 	int chave; //chave identificadora do nó
 	struct AVL *esq; //nó a esquerda (exceto folha)
 	struct AVL *dir; //nó a direita (exceto folha)
 	struct AVL *pai; //nó pai (exceto raiz)
 	int fb; // Fator de Balanceamento (altura da subarvore da esquerda - altura da subarvore da direita) 
 	int altura; //Altura
} typedef AVL;

AVL * buscar(AVL *, int);
int calcular_quantidade_nos(AVL *);
void calcular_parametros(AVL *);
void rotacao_simples_esquerda(AVL **, AVL *);
void rotacao_simples_direita(AVL **, AVL *);
void rotacao_dupla_esquerda_direita(AVL **, AVL *);
void rotacao_dupla_direita_esquerda(AVL **, AVL *);
bool balancear(AVL **, AVL *);
void inserir (AVL **, int);
void excluir (AVL **, int);
void excluir_arvore (AVL **);
void imprimir_no (AVL *);
void imprimir(AVL *, int);
void emordem(AVL *);
void preordem(AVL *);
void posordem(AVL *);



