/**
 * @description: Programa que cont�m os algoritmos de tratamento para uma �rvore AVL (Adelson-Velskii e Landis)
 * @author: Prof. Pablo Rangel, D.Sc.
 * @date: 20-10-2017
 */
#include <iostream>
#include <stdlib.h>
#include "avl.h"
using namespace std;


/**
 * @description: esta fun��o busca por um n� da �vore com base na chave.
 * @parameter: "raiz" � o n� raiz da �rvore.
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
 * @description: esta fun��o calcula a quantidade de n�s existentes na �vore.
 * @parameter: "raiz" � o n� raiz da �rvore.
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
 * @description: Esta fun��o calcula os par�metros de altura e fator de balanceamento da �vore.
 * @parameter: "raiz" � o n� raiz da �rvore.
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
 * @description: esta fun��o realiza uma rota��o simples � esquerda. O par�metro "no" � o pai do rec�m n� inserido ou removido. 
 * @parameter: "no" � o pai do rec�m n� inserido ou removido.
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
	//O n� av� era a raiz da �rvore. O pai deve assumir essa condi��o.
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
 * @description: esta fun��o realiza uma rota��o simples � direita. O par�metro "no" � o pai do rec�m n� inserido ou removido. 
 * @parameter: "no" � o pai do rec�m n� inserido ou removido.
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
	//O n� av� era a raiz da �rvore. O pai deve assumir essa condi��o.
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
 * @description: esta fun��o realiza uma rota��o simples � esquerda e posteriormente � direita do n� av�. O par�metro "no" � o pai do rec�m n� inserido ou removido. 
 * @parameter: "no" � o pai do rec�m n� inserido ou removido.
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
 * @description: esta fun��o realiza uma rota��o simples � direita e posteriormente � esquerda do n� av�. 
 * @parameter: "no" � o pai do rec�m n� inserido ou removido. 
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
 * Esta fun��o realiza um balaceamento conforme 04 casos:
 * CASO 01: n� inserido ou removido do lado direito do n� desbalanceado (fator de balanceamento igual a -2). O filho do n� desbalanceado tem fator de balanceamento com sinal negativo.
 * SOLU��O: rotacionar � esquerda o n� "neto" do n� desbalanceado. 
 * CASO 02: n� inserido ou removido do lado direito do n� desbalanceado (fator de balanceamento igual a -2). O filho do n� desbalanceado tem fator de balanceamento com sinal positivo.
 * SOLU��O: rotacionar � esquerda o n� "neto" do n� desbalanceado. Posteriormente, rotacionar o n� filho do n� desbalanceado � direita.  
 * CASO 03: n� inserido ou removido do lado esquerdo do n� desbalanceado (fator de balanceamento igual a 2). O filho do n� desbalanceado tem fator de balanceamento com sinal positivo.
 * SOLU��O: rotacionar � direita o n� "neto" do n� desbalanceado. 
 * CASO 04: n� inserido ou removido do lado direito do n� desbalanceado (fator de balanceamento igual a -2). O filho do n� desbalanceado tem fator de balanceamento com sinal negativo.
 * SOLU��O: rotacionar � direita o n� "neto" do n� desbalanceado. Posteriormente, rotacionar o n� filho do n� desbalanceado � esquerda.  
 * @parameter: "no" � o pai do rec�m n� inserido ou removido. 
 * @parameter: "raiz" � o n� raiz da �rvore.
 */
bool balancear(AVL **raiz, AVL *no){
	//�rvore vazia?
	if(no == NULL){
		return false;	
	}
	//N� possui um pai? (N�o � um n� raiz)
	if (no->pai != NULL){
		//N� possui um av�?
		if (no->pai->pai != NULL){
			//Desbalanceamento ocorreu � direita do av�
			if (no->pai->pai->fb == -2){
				//Desbalanceamento ocorreu � direita do pai (fb <= -1). CASO 01 - Solu��o: rota��o simples � esquerda  `
				if (no->pai->fb <= -1){
					rotacao_simples_esquerda (raiz, no);
				}
				//Desbalanceamento ocorreu � esquerda do pai (fb >= 1). CASO 02 - Solu��o: rota��o dupla primeiro � direita, depois rotaciona-se � esquerda.
				else{
					rotacao_dupla_direita_esquerda (raiz, no);
				}
			}
			else{
				//Desbalanceamento ocorreu � esquerda do av�
				if (no->pai->pai->fb == 2){
					//Desbalanceamento ocorreu � esquerda do pai (fb >= 1). CASO 03 - Solu��o: rota��o simples � direita.  `
					if (no->pai->fb >= 1){
						rotacao_simples_direita (raiz, no);
					}
					//Desbalanceamento ocorreu � direita do pai (fb <= -1). CASO 04 - Solu��o: rota��o dupla primeiro � esquerda, depois rotaciona-se � direita.
					else{
						rotacao_dupla_esquerda_direita (raiz, no);
					}
				} 
			}
		}
	}
}

/**
 * @description: esta fun��o realiza uma inser��o na �rvore e balanceia caso necess�rio. 
 * @parameter: "raiz" � o n� raiz da �rvore.
 * @parameter: "chave" � a chave para cria��o do novo n� a ser inserido.
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
 * @description: esta fun��o realiza uma exclus�o na �rvore e balanceia caso necess�rio. 
 * @parameter: "raiz" � o n� raiz da �rvore.
 * @parameter: "chave" � a chave do n� a ser removido.
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
 * @description: esta fun��o exclui todos os nos da �rvore 
 * @parameter: "raiz" � o n� raiz da �rvore.
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
 * @description: imprime um n� da �rvore com a seguinte nomenclatura: (chave)[fator de balanceamento, altura] 
 * @parameter: "n�" � o n� a ser impresso.
 */
void imprimir_no (AVL *no){
	cout << "(" << no->chave << ")" << "[" << no->fb<<","<<no->altura<<"]";
}
/**
 * @description: imprime a estrutura da �rvore AVL. 
 * @parameter: "raiz" � a raiz da �rvore.
 */
void imprimir(AVL *raiz, int pos_pai){
	if(raiz != NULL){
		//N� raiz?
		if (pos_pai == 0){
			cout<< "\t\t\t Estrutura da �rvore: " <<endl<<endl;
			
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
 * @parameter: "raiz" � a raiz da �rvore.
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
 * @description: faz o percurso em pr�-ordem. 
 * @parameter: "raiz" � a raiz da �rvore.
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
 * @description: faz o percurso em p�s-ordem. 
 * @parameter: "raiz" � a raiz da �rvore.
 */
void posordem(AVL *raiz){
	if(raiz != NULL){
		posordem(raiz->esq);
		posordem (raiz->dir);
		imprimir_no(raiz);
		cout << "\t";
	}
}

