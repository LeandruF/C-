#include <iostream>
#include <stdlib.h>
#include "AVL.h"

using namespace std;

int main(int argc, char** argv) {
	int op = -1;
	int chave;
	AVL *raiz = NULL;
	while (op != 0){
		system("cls");
		cout << " ------------- Entre com a opcao desejada -------------" <<endl;
		cout << "01- Inserir um no na arvore " <<endl;
		cout << "02- Buscar um no na arvore " <<endl;
		cout << "03- Remover um no na arvore " <<endl;
		cout << "04- Percorrer a arvore em ordem " <<endl;
		cout << "05- Percorrer a arvore em pre-ordem " <<endl;
		cout << "06- Percorrer a arvore em pos-ordem " <<endl;
		cout << "07- Calcular a altura da arvore" <<endl;
		cout << "08- Calcular a quantidade de nos da arvore" <<endl;
		cout << "09- CASO DE TESTE 01: Arvore (8,4,10,9,15). Insercao do no 12. Rotacao simples (esq). Arvore removida posteriormente!" <<endl;
		cout << "10- CASO DE TESTE 02: Arvore (8,4,15,17,13). Insercao do no 12. Rotacao dupla (dir-esq). Arvore removida posteriormente!" <<endl;
		cout << "11- CASO DE TESTE 03: Arvore (8,4,10,3,5). Insercao do no 2. Rotacao simples (dir). Arvore removida posteriormente!" <<endl;
		cout << "12- CASO DE TESTE 04: Arvore (8,4,10,2,6). Insercao do no 5. Rotacao dupla (esq-dir). Arvore removida posteriormente!" <<endl;
		cout << "13- Excluir a arvore" <<endl;
		cout << "0- Sair " <<endl;
		cout << "Opcao: ";
		cin>> op;
		cout<<endl<<endl;
		switch (op){
			case 0:
				cout << "Adeus! ";
				cout << endl;
				cout << endl;
			break;
			case 1:
				cout << "Digite o valor da chave do no a ser inserido: ";
				cin >> chave;
				cout<<endl;
				inserir (&raiz,chave);
				imprimir(raiz,0);
				emordem(raiz);
				cout<<endl;
				cout<<endl;
			break;
			case 2:
				cout << "Digite o valor da chave do no a ser encontrado: ";
				cin >> chave;
				cout<<endl;
				struct AVL *no;
				no = buscar(raiz,chave);
				if (no != NULL){
					cout<< "No encontrado! ";
				}
				else{
					cout<< "No NAO encontrado! ";
				}
				cout<<endl;
				cout<<endl;
			break;
			case 3:
				cout << "Digite o valor da chave do no a ser excluido: ";
				cin >> chave;
				cout<<endl;
				excluir (&raiz,chave);
				imprimir(raiz,raiz->altura);
				emordem(raiz);
				cout<<endl;
				cout<<endl;
			break;
			case 4:
				cout << "Percurso em ordem " <<endl;
				emordem(raiz);
				cout<<endl;
				cout<<endl;
			break;
			case 5:
				cout << "Percurso pre-ordem " <<endl;
				preordem(raiz);
				cout<<endl;
				cout<<endl;
			break;
			case 6:
				cout << "Percurso pos-ordem " <<endl;
				posordem(raiz);
				cout<<endl;
				cout<<endl;
			break;
			case 7:
				cout << "Altura da arvore: ";
				calcular_parametros(raiz);
				if (raiz !=NULL){
					cout <<raiz->altura;
				}
				cout<<endl;
				cout<<endl;
			break;
			case 8:
				cout << "Quantidade de nos da arvore: ";
				cout << calcular_quantidade_nos(raiz) <<endl;
				cout<<endl;
				cout<<endl;
			break;
			case 9:
				inserir (&raiz,8); inserir (&raiz,4); inserir (&raiz,10); inserir (&raiz,9); inserir (&raiz,15);
				emordem(raiz);
				cout<<endl<<endl;
				//imprimir(raiz,0);
				inserir (&raiz,12);
				//imprimir(raiz,0);
				emordem(raiz);
				cout<<endl;
				cout<<endl;
				excluir_arvore (&raiz);
			break;
			case 10:
				inserir (&raiz,8); inserir (&raiz,4); inserir (&raiz,15); inserir (&raiz,17); inserir (&raiz,13);
				emordem(raiz);
				cout<<endl<<endl;
				//imprimir(raiz,0);
				inserir (&raiz,12);
				//imprimir(raiz,0);
				emordem(raiz);
				cout<<endl;
				cout<<endl;
				excluir_arvore (&raiz);
			break;
			case 11:
				inserir (&raiz,8); inserir (&raiz,4); inserir (&raiz,10); inserir (&raiz,3); inserir (&raiz,5);
				emordem(raiz);
				cout<<endl<<endl;
				//imprimir(raiz,0);
				inserir (&raiz,2);
				//imprimir(raiz,0);
				emordem(raiz);
				cout<<endl;
				cout<<endl;
				excluir_arvore (&raiz);
			break;
			case 12:
				inserir (&raiz,8); inserir (&raiz,4); inserir (&raiz,10); inserir (&raiz,2); inserir (&raiz,6);
				emordem(raiz);
				cout<<endl<<endl;
				//imprimir(raiz,0);
				inserir (&raiz,5);
				//imprimir(raiz,0);
				emordem(raiz);
				cout<<endl;
				cout<<endl;
				excluir_arvore (&raiz);
			break;
			case 13:
				excluir_arvore (&raiz);
				cout<<"Arvore excluida com sucesso! " << endl;
				cout<<endl<<endl;
			break;
			default: cout << "Opcao invalida! " <<endl;	
		}
		if (op != 0){
			system("pause");
			cout<<endl;
			cout<<endl;
		}
	}
}
