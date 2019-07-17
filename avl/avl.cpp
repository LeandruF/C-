/**
 * @description: Programa que contém os algoritmos de tratamento para uma árvore AVL (Adelson-Velskii e Landis)
 * @author: Prof. Pablo Rangel, D.Sc.
 * @date: 20-10-2017
 */
#include <iostream>
#include <stdlib.h>
#include "avl.h"
using namespace std;


/**
 * @description: esta função busca por um nó da ávore com base na chave.
 * @parameter: "raiz" é o nó raiz da árvore.
 */
AVL * buscar(AVL *raiz, int chave){
	if (raiz == NULL){
		return NULL;		
	}
	if (raiz->chave == chave){
		return raiz;
	}
	if (chave > raiz->chave){
		return buscar (raiz->dir,chave);
	}
	else{
		return buscar (raiz->esq,chave);
	}
}

/**
 * @description: esta função calcula a quantidade de nós existentes na ávore.
 * @parameter: "raiz" é o nó raiz da árvore.
 */
int calcular_quantidade_nos(AVL *raiz){
	// Arvore vazia
	if (raiz == NULL){
		return 0;
	}
	else{
		int qtd_esq = calcular_quantidade_nos (raiz->esq);
		int qtd_dir = calcular_quantidade_nos (raiz->dir);
		return 1+ qtd_esq + qtd_dir;
	}	
}

/**
 * @description: Esta função calcula os parâmetros de altura e fator de balanceamento da ávore.
 * @parameter: "raiz" é o nó raiz da árvore.
 */
void calcular_parametros(AVL *raiz){
	// Arvore vazia
	if (raiz == NULL){
		return;
	}
	// No folha
	if (raiz->esq == NULL && raiz->dir == NULL){
		raiz->fb=0;
		raiz->altura=1;
		return;
	}
	else{
		calcular_parametros (raiz->esq);
		int h_esq = 0;
		if (raiz->esq != NULL){
			h_esq = raiz->esq->altura;
		}
		calcular_parametros (raiz->dir);
		int h_dir = 0; 
		if (raiz->dir != NULL){
			h_dir = raiz->dir->altura;
		}
		
		raiz->fb = h_esq - h_dir;
		if (h_esq > h_dir){
			raiz->altura = 1 + h_esq;			
		} 
		else{
			raiz->altura = 1 + h_dir;
		}
	}	
}

/**
 * @description: esta função realiza uma rotação simples à esquerda. O parâmetro "no" é o pai do recém nó inserido ou removido. 
 * @parameter: "no" é o pai do recém nó inserido ou removido.
 */
void rotacao_simples_esquerda(AVL **raiz, AVL *no){
	cout<<"\n Rotacao simples a esquerda ... " <<endl;
	AVL *avo = no->pai->pai;
	AVL *pai = no->pai;
	
	avo->dir = pai->esq;
	if (pai->esq){
		pai->esq->pai = avo;
	}
	
	
	pai->esq = avo;
	//O nó avô era a raiz da árvore. O pai deve assumir essa condição.
	if (avo->pai == NULL){
		*raiz = pai;
		(*raiz)->pai = NULL;
	}
	else{
		avo->pai->esq = pai;
		pai->pai = avo->pai; 
	}
	avo->pai = pai;
	
}

/**
 * @description: esta função realiza uma rotação simples à direita. O parâmetro "no" é o pai do recém nó inserido ou removido. 
 * @parameter: "no" é o pai do recém nó inserido ou removido.
 */
void rotacao_simples_direita(AVL **raiz, AVL *no){
	cout<<"\n Rotacao simples a direita ... " <<endl;
	
	AVL *avo = no->pai->pai;
	AVL *pai = no->pai;
	
	avo->esq = pai->dir;
	if (pai->dir){
		pai->dir->pai = avo;
	}
	
	pai->dir = avo;
	//O nó avô era a raiz da árvore. O pai deve assumir essa condição.
	if (avo->pai == NULL){
		*raiz = pai;
		pai->pai = NULL;
	}
	else{
		avo->pai->dir = pai; 
		pai->pai = avo->pai; 
	}
	avo->pai = pai;	
}

/**
 * @description: esta função realiza uma rotação simples à esquerda e posteriormente à direita do nó avô. O parâmetro "no" é o pai do recém nó inserido ou removido. 
 * @parameter: "no" é o pai do recém nó inserido ou removido.
 */
void rotacao_dupla_esquerda_direita(AVL **raiz, AVL *no){
	cout<<"\n Rotacao dupla ... " <<endl;
	
	AVL *pai;
	AVL *filho;
	
	pai = no->pai;
	
	if (no->esq != NULL){
		filho = no->esq;	
	}
	else{
		filho = no->dir;
	}
	
	rotacao_simples_esquerda(raiz,filho);
	emordem(*raiz);	
	rotacao_simples_direita (raiz,pai);
}

/**
 * @description: esta função realiza uma rotação simples à direita e posteriormente à esquerda do nó avô. 
 * @parameter: "no" é o pai do recém nó inserido ou removido. 
 */
void rotacao_dupla_direita_esquerda(AVL **raiz, AVL *no){
	cout<<"\n Rotacao dupla ... " <<endl;
	
	AVL *pai;
	AVL *filho;
	
	pai = no->pai;
	
	if (no->esq != NULL){
		filho = no->esq;	
	}
	else{
		filho = no->dir;
	}
	
	
	rotacao_simples_direita (raiz,filho);
	emordem(*raiz);
	rotacao_simples_esquerda(raiz,pai);	
}

/**
 * Esta função realiza um balaceamento conforme 04 casos:
 * CASO 01: nó inserido ou removido do lado direito do nó desbalanceado (fator de balanceamento igual a -2). O filho do nó desbalanceado tem fator de balanceamento com sinal negativo.
 * SOLUÇÃO: rotacionar à esquerda o nó "neto" do nó desbalanceado. 
 * CASO 02: nó inserido ou removido do lado direito do nó desbalanceado (fator de balanceamento igual a -2). O filho do nó desbalanceado tem fator de balanceamento com sinal positivo.
 * SOLUÇÃO: rotacionar à esquerda o nó "neto" do nó desbalanceado. Posteriormente, rotacionar o nó filho do nó desbalanceado à direita.  
 * CASO 03: nó inserido ou removido do lado esquerdo do nó desbalanceado (fator de balanceamento igual a 2). O filho do nó desbalanceado tem fator de balanceamento com sinal positivo.
 * SOLUÇÃO: rotacionar à direita o nó "neto" do nó desbalanceado. 
 * CASO 04: nó inserido ou removido do lado direito do nó desbalanceado (fator de balanceamento igual a -2). O filho do nó desbalanceado tem fator de balanceamento com sinal negativo.
 * SOLUÇÃO: rotacionar à direita o nó "neto" do nó desbalanceado. Posteriormente, rotacionar o nó filho do nó desbalanceado à esquerda.  
 * @parameter: "no" é o pai do recém nó inserido ou removido. 
 * @parameter: "raiz" é o nó raiz da árvore.
 */
bool balancear(AVL **raiz, AVL *no){
	//Árvore vazia?
	if(no == NULL){
		return false;	
	}
	//Nó possui um pai? (Não é um nó raiz)
	if (no->pai != NULL){
		//Nó possui um avô?
		if (no->pai->pai != NULL){
			//Desbalanceamento ocorreu à direita do avô
			if (no->pai->pai->fb == -2){
				//Desbalanceamento ocorreu à direita do pai (fb <= -1). CASO 01 - Solução: rotação simples à esquerda  `
				if (no->pai->fb <= -1){
					rotacao_simples_esquerda (raiz, no);
				}
				//Desbalanceamento ocorreu à esquerda do pai (fb >= 1). CASO 02 - Solução: rotação dupla primeiro à direita, depois rotaciona-se à esquerda.
				else{
					rotacao_dupla_direita_esquerda (raiz, no);
				}
			}
			else{
				//Desbalanceamento ocorreu à esquerda do avô
				if (no->pai->pai->fb == 2){
					//Desbalanceamento ocorreu à esquerda do pai (fb >= 1). CASO 03 - Solução: rotação simples à direita.  `
					if (no->pai->fb >= 1){
						rotacao_simples_direita (raiz, no);
					}
					//Desbalanceamento ocorreu à direita do pai (fb <= -1). CASO 04 - Solução: rotação dupla primeiro à esquerda, depois rotaciona-se à direita.
					else{
						rotacao_dupla_esquerda_direita (raiz, no);
					}
				} 
			}
		}
	}
}

/**
 * @description: esta função realiza uma inserção na árvore e balanceia caso necessário. 
 * @parameter: "raiz" é o nó raiz da árvore.
 * @parameter: "chave" é a chave para criação do novo nó a ser inserido.
 */
void inserir (AVL **raiz, int chave){
	
	AVL *no = (AVL *) malloc (sizeof(AVL)) ;
	no->chave=chave;
	no->dir=NULL;
	no->esq=NULL;	
	no->pai=NULL;
	no->fb = 0;
	if (*raiz == NULL){
		*raiz = no;
	}
	else{
		struct AVL *pai, *atual;
		atual = *raiz;
		while ( atual != NULL){
			pai = atual;
			if (chave > atual->chave){
				atual = atual->dir;
			}
			else{
				atual = atual->esq;
			}
		}
		no->pai=pai;
		if (chave > pai->chave){
			pai->dir = no;
		}
		else{
			pai->esq=no;
		}
		calcular_parametros (*raiz);
		balancear (raiz, pai);
		calcular_parametros (*raiz);
	}
}
/**
 * @description: esta função realiza uma exclusão na árvore e balanceia caso necessário. 
 * @parameter: "raiz" é o nó raiz da árvore.
 * @parameter: "chave" é a chave do nó a ser removido.
 */
void excluir (AVL **raiz, int chave){
	AVL *no = buscar (*raiz,chave); 
	if (no != NULL){
		if (no->esq)
		cout<<"No encontrado. Removendo..."<<endl;
		cout<<endl;
		if ((no)->pai !=NULL){
			if (chave > no->pai->chave){
				no->pai->dir = no->dir;
			}
			else{
				no->pai->esq = no->esq;
			}	
		}
		else{
			*raiz=NULL;
		}
		cout<<"Removido."<<endl;
		cout<<endl;
		free(no);
	}
}
/**
 * @description: esta função exclui todos os nos da árvore 
 * @parameter: "raiz" é o nó raiz da árvore.
 */
void excluir_arvore (AVL **raiz){
	if (*raiz != NULL){
		excluir_arvore(&((*raiz)->esq));
		excluir_arvore(&((*raiz)->dir));
		free(*raiz);
		*raiz= NULL;
	}
}
/**
 * @description: imprime um nó da árvore com a seguinte nomenclatura: (chave)[fator de balanceamento, altura] 
 * @parameter: "nó" é o nó a ser impresso.
 */
void imprimir_no (AVL *no){
	cout << "(" << no->chave << ")" << "[" << no->fb<<","<<no->altura<<"]";
}
/**
 * @description: imprime a estrutura da árvore AVL. 
 * @parameter: "raiz" é a raiz da árvore.
 */
void imprimir(AVL *raiz, int pos_pai){
	if(raiz != NULL){
		//Nó raiz?
		if (pos_pai == 0){
			cout<< "\t\t\t Estrutura da árvore: " <<endl<<endl;
			
			for (int i=0; i< 5; i++){
				cout<<"\t";
			}
			imprimir_no(raiz);
			cout<<endl;
			pos_pai = 5;
		}
		if (raiz->esq != NULL){
			for (int i=0; i< pos_pai -2; i++){
				cout<<"\t";
			}
			imprimir_no(raiz->esq);
		}
		if (raiz->dir != NULL){
			for (int i=0; i< (pos_pai) - (pos_pai -2); i++){
				cout<<"\t";
			}
			imprimir_no(raiz->dir);
		}
		cout<<endl;
		imprimir (raiz->esq, pos_pai-2);
		imprimir (raiz->dir, (pos_pai) - (pos_pai -2));
	}
}
/**
 * @description: faz o percurso em ordem. 
 * @parameter: "raiz" é a raiz da árvore.
 */
void emordem(AVL *raiz){
	if(raiz != NULL){
		emordem(raiz->esq);
		imprimir_no(raiz);
		cout << "\t";
		emordem (raiz->dir);
	}
}
/**
 * @description: faz o percurso em pré-ordem. 
 * @parameter: "raiz" é a raiz da árvore.
 */
void preordem(AVL *raiz){
	if(raiz != NULL){
		imprimir_no(raiz);
		cout << "\t";
		preordem(raiz->esq);
		preordem (raiz->dir);
	}
}
/**
 * @description: faz o percurso em pós-ordem. 
 * @parameter: "raiz" é a raiz da árvore.
 */
void posordem(AVL *raiz){
	if(raiz != NULL){
		posordem(raiz->esq);
		posordem (raiz->dir);
		imprimir_no(raiz);
		cout << "\t";
	}
}

