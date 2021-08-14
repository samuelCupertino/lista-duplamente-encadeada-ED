#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define ELEM_LINHA 10 // Número de elementos printados por linha (Ajustar de acordo com a resolucao da tela)

typedef struct elemento{ // Estrutura duplamente encadeada   
	int num;
	struct elemento *ant; 
	struct elemento *prox;
}Elem;

typedef struct elemento* Lista; // Definicao de pontreiro de inicio da lista


Lista *Criar_Lista(){
	
	Lista *Lista_Num=(Lista*)malloc(sizeof(Lista)); // Alocacao de memoria para lista
	
	if(Lista_Num != NULL) // Se Lista foi alocada com sucesso 
		*Lista_Num = NULL; // O ponteiro de inicio aponta para o 1º elemento da lista, como nao ha elemento esse inicio é nulo 
	else{ // se a alocacao deu erro
		printf("Erro de Memória!"); // Informa que ocorreu um erro de memoria
		exit(1); // Mata a execucao do programa
	}
	
	return Lista_Num; // Retorna a lista alocada com sucesso 
}

int Inserir_Inicio(Lista *Lista_Num, int num){
	
	if(Lista_Num == NULL) // Lista inesistente retorna 0
		return 0;
		
	Elem *no=(Elem*)malloc(sizeof(Elem)); // Alocacao de memoria do nó 
	
	if(no == NULL) // Memoria não alocada retorna 0 
		return 0;
	
	// Se a lista e o nó existem/estao alocados, o nó é preencido 
	no->ant = NULL; // Recebe nulo como anterior (ja que para ser o 1º menbro da lista nao pode ter anterio)
	no->num = num; // Recebe como dado o numero que será armazenado neste nó 
	no->prox = (*Lista_Num); // O novo nó tem como proximo o ate entao inicio da lista (ja que o nó sera inserido no inicio)
	
	if (*Lista_Num != NULL) // Se o inicio da lista tiver algum elemento
		(*Lista_Num)->ant = no; // O nó sera adicionado ao anterior deste elemeto (passando o nó a ser o 1° elemento)
	*Lista_Num = no; // O ponteiro de inicio aponta para o atual 1° elemeto 
	
	return 1; // Retorna 1 avisando que o elemento foi adicionado ao inicio da lista com sucesso
}

int Inserir_Final(Lista *Lista_Num, int num){
	
	if(Lista_Num == NULL) // Lista inesistente retorna 0
		return 0;
		
	Elem *no=(Elem*)malloc(sizeof(Elem)); // Alocacao de memoria do nó 
	
	if(no == NULL) // Nó inesistente retorna 0
		return 0;
	
	// Se a lista e o nó existem/estao alocados, o nó é preencido 
	no->num = num;  // Recebe como dado o numero que será armazenado neste nó 
	no->prox = NULL; // O nó proximo recebe nulo, ja que este sera o ultimo da lista, nao possuindo um proximo
	
	if((*Lista_Num) == NULL){ // Se o 1º elemeto é inexistente, ou seja o ponteiro do inicio aponta para nulo, nao ha elemento na lista
		no->ant = NULL; // O nó tem seu anterior tambem como nulo, pois sera o 1º elemento e ja tem seu proximo como nulo
		*Lista_Num = no; // O ponteiro de incio aponta para o nó recem criado 
	}
	else{ // Se o 1º elemeto é exise, ou seja o ponteiro do inicio aponta para algum elemento, a lista possui elementos
		Elem *aux = *Lista_Num; // Um auxiliar é criado para poder percorrer os elementos da lista 
		while(aux->prox != NULL){ // Se percorre a lista ate o final 
			aux=aux->prox;
		}
		aux->prox = no; // O ultimo elemento recebe o nó criado como seu proximo 
		no->ant = aux; // O nó criado recebe o 'ex ultimo elemento' como seu anterior 
	}
	
	return 1; // Retorna 1 avisando que o elemento foi adicionado ao final da lista com sucesso
}


void Printagem_Dinamica(int margem, int num){ // Funcao responsavel por adaptar a largura da box aos numeros informados
	int aux_num=num;
	
	int q_char=1;
	while(aux_num > 0){ // Contagem da quantidade de casas decimais que possui o numero informado  
		q_char++;
		aux_num/=10;
	}
	
	char *t=(char*)malloc(q_char*sizeof(char)); // Alocacao de uma string contendo a quantidade exata de posicoes a sem usadas  
	
	int i=0;
	while(i < q_char-1){ // Preenchimento das posicoes da string com o caractere que sofre manipulacao (aumentando ou diminunido a largura da box)
		t[i]='-';
		i++;
	}
	t[q_char-1]='\0'; // Fechamento da string com indicardo de final '\0'
	
	if(margem == 1)
		printf(" ,_.--%s--.  ", t); // Printar margin-top adaptado ao tamanho do numero armazenado na box
	if(margem == 2)
		printf("   `--%s--´  ", t); // Printar margin-bottom adaptado ao tamanho do numero armazenado na box
}

void Printar_Elemento(Lista *Lista_Num){
	int br[3];
	Lista aux1, aux2, aux3;
	aux1 = aux2 = aux3 = (*Lista_Num);
	
	printf("NULL\n"); // Printar 'NULL' que o 1º elemento aponta com seu ponteiro ant (anterior do 1º elem é Nulo)
	do{
		br[0]=0;
		while(aux1 != NULL){
			Printagem_Dinamica(1, aux1->num); // Chama a funcao responsavel por printar a 'margin-top' da box 
	        aux1 = aux1->prox;
	        
			br[0]++;
			if(br[0] % ELEM_LINHA == 0) // 1/3 - Limitador de quantas box vao aparecer por linha (Evitar embaralhamento dos caracteres)
				break;
		}
		printf("\n");
		
		br[1]=0;
		while(aux2 != NULL){
	        printf(" ` || %d ||->", aux2->num); // Chama a funcao responsavel por printar o 'margin-left, margin-right e o Conteudo' da box 
	        aux2 = aux2->prox;
	        
			br[1]++;
			if(br[1] % ELEM_LINHA == 0) // 2/3
				break;
	    }
	    
		br[2]=0;
		printf("\n");
		while(aux3 != NULL){
			Printagem_Dinamica(2, aux3->num); // Chama a funcao responsavel por printar o 'margin-bottom' da box 
	        aux3 = aux3->prox;
	        
			br[2]++;
	        if(br[2] % ELEM_LINHA == 0) // 3/3
				break;
		}
		
		if(br[0] < ELEM_LINHA) // Enquanto a linha nao for quebrada o 'NULL' segura na mesma linha 
			printf("NULL"); // Printar 'NULL' que o ultimo elemento aponta com seu ponteiro prox (proximo do ultimo elem é Nulo)
		printf("\n\n");
		
	}while(aux3 != NULL); // Retomar printagem enquanto a lista nao foi printada por completa
}

int main(void){
	setlocale(LC_ALL, "portuguese");
	int x, num=NULL, cont=0;
	Lista *Lista_Num=Criar_Lista();
	
	do{
		if(num%2 == 1){ // Se o numero é IMPAR sera inserido no inicio da lista 
			system("CLS");
			if(num != NULL) // A liata so sera printada quando for infirmado algum elemento
			if(x=Inserir_Inicio(Lista_Num, num)){ // Se alcacao bem sucedida E o a variavel 'num' possui um valor sera este enserido a lista
				Printar_Elemento(Lista_Num); // Os elemento da Lista seram printados e sempre que adcionado um novo a printagem sera atualizada
				cont++; // Contador para a quebra de linha da palavra 'NULL'
				if(cont == ELEM_LINHA){ // se esta na hora da linha ser quebrada
					cont=0; // O contador é reiniciado
					printf("NULL\n"); // A palavra 'NULL' aparece na nova linha
				}
			} else if(x == 0 && num != NULL){ // Se não foi possivel a alocacao para a lista ou para algum elemento, exibe a mensagem 
				printf("Erro de Memória!");
			}
		}
		else{ // Se o numero é PAR sera inserido no final da lista (Mesmo processo do codigo acima, so muda a insercao que sera no final)
			system("CLS");
			if(num != NULL)
			if(x=Inserir_Final(Lista_Num, num)){
				Printar_Elemento(Lista_Num);
				cont++;
				if(cont == ELEM_LINHA){
					cont=0;
					printf("NULL\n");
				}
			} else if(x == 0 && num != NULL){
				printf("Erro de Memória!");
			}
		}
		printf("INFORME UM NUMERO INTEIRO: ");
		scanf("%d", &num);
	}while(1); // Laço infinito para execucao do program em loop (Possibilitando a atualizacao da printagem em tempo de adcao do dado 'num')
}
