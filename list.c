/*Algoritmo em C para ordenar listas duplamente encadeada e vetores com : Insertion Sort, Selection Sort, Merge Sorte, Quick Sort.
---
Instituição : Universidade Federal da Fronteira Sul
Curso : Ciência da Computação
Data : 18 de junho de 2012
escrito por : Silvana Trindade
e-mail :syletri@gmail.com
---
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define LISTA 1
#define VETOR 2
#define INSERT 3
#define SELECTION 4
#define QUICK 5
#define MERGE 6

typedef struct _dado
{
	char nome[40];
	char fone[20];

}TpContato;

typedef struct _nodo
{
	int indice;				//para facilitar ordenação na merge sort
	TpContato pInfo;		//estruturas de contatos
	struct _nodo *prox;		//ponteiro para o proximo nodo
	struct _nodo *anterior;	//ponteiro para o nodo anterior

}TpNodo;

typedef struct _lista
{
	int nNodos;				//numero de elementos inseridos na lista
	TpNodo *first;			//ponteiro da cabeça da lista
	TpNodo *last;			//ponteiro da cauda da lista

}TpLista;

int Menu_Principal() { //menu principal de acesso do usuario

	int option;

	printf("\n1) Criar Lista\n\n");
	printf("2) Criar Vetor\n\n");
	printf("3) Insertion Sort\n\n");
	printf("4) Selection Sort\n\n");
	printf("5) Quick Sort\n\n");
	printf("6) Merge Sort\n\n");
	printf("7) Sair:");
	scanf("%d",&option);

	return option;
}

int Sub_Menu() { //menu para escolha de ordenação para lista e vetor//NNÃO PRECISO

	int option;

	printf("Digite:\n1) Vetor\n");
	printf("2) Lista\n:");
	scanf("%d",&option);

	return option;

}
void Imprime_Vetor(TpContato vet[],int tamanho) { 

	int i;

	printf("------------------\n\n");

	for(i = 0;i < tamanho; i++)					 
	{
		printf("Nome:%s\n\nFone: %s\n\n",vet[i].nome, vet[i].fone);
		printf("------------------\n\n");
	}
}

void Imprime_Lista(TpLista *lista) {			

	TpNodo *p;									

	printf("------------------\n\n");

	for(p = lista->first; p != NULL; p = p->prox) 
	{

		printf("Nome: %s\n\n",p->pInfo.nome);
		printf("Fone: %s\n\n",p->pInfo.fone);
		printf("------------------\n\n");
	}
}

char* int_Para_String(int numero) {

  char* string;
  string = (char *) malloc(sizeof(char) * 200);
  sprintf(string, "%d", numero);

  string = realloc(string, sizeof(char) * strlen(string));

  return string;
}

void buffer () 														
{
    char garbage ='\0';

    while((garbage = getchar()) && garbage !='\n' && garbage!=EOF ) {	
        return;
    }
}

int getrand(int min,int max) {

	return(rand()%(max-min) + min);
}

TpLista *Inicializa() 										
{
	TpLista *lista = (TpLista*) malloc (sizeof(TpLista));	

	if(!lista)
	{														

		return NULL;										
	}

	lista->first = NULL;									
	lista->last = NULL;										
	lista->nNodos = 0;										

	return lista;										
}

TpLista *Inserir_para_Lista(TpLista *lista,char *telefone,char *name) {

	TpNodo* novoNodo = (TpNodo*) malloc (sizeof(TpNodo));

	if(!novoNodo)
	{
		printf("erro\n");
		return NULL;
	}
	
	novoNodo->indice = lista->nNodos + 1;
	strcpy(novoNodo->pInfo.fone,telefone);					
	strcpy(novoNodo->pInfo.nome,name);
	novoNodo->prox = NULL;
	novoNodo->anterior = NULL;

	if(lista == NULL)
	{
		return NULL;
	}
	else {

		if(lista->first == NULL)
		{//insere no inicio

			lista->first = novoNodo;
			lista->last = novoNodo;
			lista->nNodos++;
			
			
		}
		else
		{//insere no final
			novoNodo->anterior = lista->last;
			lista->last->prox = novoNodo;
			lista->last = novoNodo;
			lista->nNodos++;
			
		}
	}
	return lista;
}

void Divide_Lista(TpLista *lista, TpLista *l1, TpLista *l2) {

    int i,ini = lista->first->indice,fim = lista->last->indice,meio;
    TpNodo *p = lista->first;
    
   meio =((fim - ini)/2) + 1;

    for(i = 0;i <= (meio-1);i++){
 
        p = p->prox; 
    } 
    
    l1->first = lista->first; 
    l1->nNodos = meio; 
    l1->last = p->anterior; 
    
    
    l2->first = p; 
    l2->nNodos = (fim-ini)-(meio-1); 
    l2->last = lista->last;
     
    
} 
void Free_Lista(TpLista *lista) {		

	TpNodo *p;							 
	TpNodo *q;							

	q = lista->first;					

	while(q != NULL)					
	{
		p = q->prox;					
		free(q);						
		q = p;							
	}
	free(lista);						
}

void Free_Vetor(TpContato *vet,int tam) {

	int i,indice = 0;

	for (i = 0; i < tam; i++){

		vet[indice] = vet[indice + 1];
		tam -= 1;
	}
	
}
void Copia_Vetor(TpContato vet[],TpContato VetCopia[],int limite) {

	int i;

	for(i = 0; i < limite; i++) {

       VetCopia[i] = vet[i]; 
 
	}
	return;
}

void Copia_Lista(TpLista *Lista, TpLista *Lnew)	{
 
    int i; 										
    TpNodo *p = Lista->first; 					
    TpNodo *aux;							
    
    for(i = 0; i < Lista->nNodos; i++)			 
	{
 
        Inserir_para_Lista(Lnew,p->pInfo.fone,p->pInfo.nome); 		
        p = p->prox;												
    } 
    
    aux = Lnew->first; 							
    p = Lista->first; 							
    
    for(i = 0; i < Lista->nNodos; i++)			
	{
        aux->indice = p->indice; 				
        p = p->prox; 							
        aux = aux->prox;						
    } 

    
} 

int Eh_Validos(TpNodo *esq,TpNodo *dir) {

    if(esq == NULL || dir == NULL || esq == dir)
    {

        return 0;
    }
    while(esq->prox != NULL) {
        esq = esq->prox;
        if(esq == dir)
        {
            return 1;
        }
    }
    return 0;
}

TpNodo* Pega_Elemento_Por_Indice(TpLista *lista, int i) {
    TpNodo *temp = lista->first;						
    int j = 0;											

    if (i > lista->nNodos)								
	{
        return NULL;									
	}

    while (temp != NULL)								
	{

		if (j == i)																		
		{
			return temp;								
		}
		temp = temp->prox;								
		j++;											
	}
	
	printf("erro\n");
	return NULL;										
}
void swap(TpNodo *nodo1,TpNodo *nodo2) {
		
	TpNodo temp;

	temp.anterior = nodo1->anterior;
	temp.prox = nodo1->prox;

	nodo1->anterior = nodo2->anterior;
	nodo1->prox = nodo2->prox;

	nodo2->anterior = temp.anterior;
	nodo2->prox = temp.prox;
}

void troca(TpNodo *n1, TpNodo *n2) {
    TpNodo aux;

    aux.pInfo = n1->pInfo;
    n1->pInfo = n2->pInfo;
    n2->pInfo = aux.pInfo;

	return;

	
}
	
//Insertion Sort para Listas e vetores

void Insertion_Sort_Vetor(TpContato V[], int limite) {               
        int i, j;												
		TpContato aux;											
 
        for(i = 1; i < limite; i++)								
		{
 
                j = i;											
 
                while((strcmp(V[j].nome,V[j - 1].nome)) < 0) {
 
                        aux = V[j];								 
                        V[j] = V[j - 1];						
                        V[j - 1] = aux;							
                        j--;    								
 
                        if(j == 0)break;						
                }               
        }

		return;
}

void Insertion_Sort_Lista(TpLista *lista) {

	TpContato chave;														
	TpNodo *pNodo,*i,*j;													

	for (pNodo = lista->first->prox; pNodo != NULL; pNodo = pNodo->prox)	
	{



	
		j = pNodo;															
		chave = j->pInfo;													
		i = j->anterior;

		while((i != NULL) && (strcmp(i->pInfo.nome,chave.nome) > 0))		
		{
			i = i->anterior;												
			
		}

		j->anterior->prox = j->prox;
																			
		if (j->anterior->prox == NULL)										
		{
			lista->last = j->anterior;										
		}
		if(j->prox != NULL)												
		{
			j->prox->anterior = j->anterior;
		}
																		
		if (i == NULL)													
		{
			j->prox = lista->first;										
			lista->first->anterior = j;								
			lista->first = j;											
			j->anterior = NULL;											
			
		}
		else {															

			if (i->prox != NULL)										
			{
				i->prox->anterior = j;									
			}
			j->prox = i->prox;											
			i->prox = j;												
			j->anterior = i;											
		}
	
	}
	
}

void Selection_Sort_Vetor(TpContato v[],int limite) {

	TpContato swap;											
	int i,j,menor;											
	
	for(i = 0; i < (limite-1); i++)							
	{

		menor = i;											

		for(j =(i+1); j < limite; j++)						
		{

			if(strcmp(v[j].nome,v[menor].nome) < 0)			
			{

				menor = j;									
			}
		}
		if(i != menor)									
		{

			swap = v[i];								
			v[i] = v[menor];
			v[menor] = swap;
		}
	}
}

void Selection_Sort_Lista(TpLista *lista) {

    int i, j, menor;
   	TpNodo *pNodo, *pNew;

	for (i = 0; i < (lista->nNodos - 1); i++) {

      menor = i;

		for (j = i + 1; j < lista->nNodos; j++) {

       	pNodo = Pega_Elemento_Por_Indice(lista, j);
    	pNew = Pega_Elemento_Por_Indice(lista,menor);
				
		    if (strcmp(pNodo->pInfo.nome,pNew->pInfo.nome) < 0) {
		    	menor = j;
			}
		}
		troca(Pega_Elemento_Por_Indice(lista, menor), Pega_Elemento_Por_Indice(lista, i));
    }
	Imprime_Lista(lista);
}

void Merge_Vetor(TpContato vet[],int tam)
{
	int i,j,k = 0,meio;
	TpContato *temporario;

	temporario = (TpContato*) malloc (sizeof(TpContato)*tam);
	
	if(temporario == NULL) {

		exit(1);
	}
	meio = tam/2;

	i = 0;
	k = 0;
	j = meio;

	while(i < meio && j < tam) {
		if(strcmp(vet[i].nome,vet[j].nome) < 0) {

			temporario[k] = vet[i];
			i++;
		}
		else {
			temporario[k] = vet[j];
			j++;
		}
		k++;
	}
	if(i == meio) {
		while(j < tam) {
		
			temporario[k] = vet[j];
			j++;
			k++;
		}
	}
	else {
		while(i < meio) {

			temporario[k] = vet[i];
			i++;
			k++;
		}
	}
	
	for( i = 0; i < tam; i++) {

		vet[i] = temporario[i];
	}

	free(temporario);
}

void Merge_Sort_Vetor(TpContato vet[],int tam) {
	
	int meio;
	
	if(tam > 1) {
		meio = tam /2;
		Merge_Sort_Vetor(vet,meio);
		Merge_Sort_Vetor(vet + meio,tam - meio);
		Merge_Vetor(vet,tam);
	}
}

void Merge_Lista(TpLista *l,TpLista *l1, TpLista *l2){ 

	int i; 
    TpNodo *esq;
    TpNodo *dir;
    TpNodo *p = l->first;
    TpLista *lesq = Inicializa();
    TpLista *ldir = Inicializa(); 
   

    Copia_Lista(l1,lesq); 
    Copia_Lista(l2,ldir);

    esq = lesq->first; 
    dir = ldir->first; 

    Inserir_para_Lista(lesq,"zzzzzz","zzzzzz");
   	Inserir_para_Lista(ldir,"zzzzzz","zzzzzzz");
	

    for(i = 0; i < l->nNodos; i++){
		
        if(strcmp(esq->pInfo.nome,dir->pInfo.nome) < 0){ 

            p->pInfo = esq->pInfo; 
            esq = esq->prox; 
			
        } 
        else{ 
            p->pInfo = dir->pInfo;
            dir = dir->prox;
        } 
        p = p->prox;
    } 
    
} 

void Merge_Sort_Lista(TpLista *lista, int inicio, int fim) {
 
    TpLista *l1 = Inicializa(); 
    TpLista *l2 = Inicializa();

    if((fim-inicio) > 0 )
	{
        Divide_Lista(lista,l1,l2);
        Merge_Sort_Lista(l1,l1->first->indice,l1->last->indice); 
        Merge_Sort_Lista(l2,l2->first->indice,l2->last->indice);
        Merge_Lista(lista,l1,l2);
        
    } 
  
} 
void Troca_Vetor(TpContato *p1,TpContato *p2) {

	TpContato aux;

	aux = *p1;
	*p1 = *p2;
	*p2 = aux;
}

int partition(TpContato vet[],int esq,int dir) {

	int i,j;

	i = esq;

	for(j = (esq + 1); j <= dir; j++) {

		if(strcmp(vet[j].nome,vet[esq].nome) < 0) 
		{
			i++;
			Troca_Vetor(&vet[i],&vet[j]);
		}
	}
	Troca_Vetor(&vet[esq],&vet[i]);

	return i;
}
	
void Quick_Sort_Vetor(TpContato vet[],int esq,int dir) {

	int r;

	if(dir > esq) 
	{
		r = partition(vet,esq,dir);
		Quick_Sort_Vetor(vet,esq,r - 1);
		Quick_Sort_Vetor(vet,r+1,dir);
	}
}

int partition_lista(TpLista *lista,int esq,int dir)	{
	
	int i,j;
	TpNodo *pNodo,*pNew;
	i = esq;

	for(j = (esq + 1); j <= dir; j++) {

		pNodo = Pega_Elemento_Por_Indice(lista,j);
		pNew = Pega_Elemento_Por_Indice(lista,esq);

		if(strcmp(pNodo->pInfo.nome,pNew->pInfo.nome) < 0) 
		{
			i++;
			troca(Pega_Elemento_Por_Indice(lista,i),Pega_Elemento_Por_Indice(lista,j));
			
		}
	}
	troca(Pega_Elemento_Por_Indice(lista,esq),Pega_Elemento_Por_Indice(lista,i));

	return i;
}
void Quick_Sort_Lista(TpLista *lista,int esq,int dir) {
	
	int r;

	if( dir > esq ) 
	{
		r = partition_lista(lista,esq,dir);
		Quick_Sort_Lista(lista,esq,r - 1);
		Quick_Sort_Lista(lista,r + 1,dir);
	}
}
int main()
{
	srand(time(NULL));
	double tempo;
	clock_t t_fim,t_ini;
	t_ini = clock();//inicia contagem...
	int option,cont,limite_l,limite_v;
	TpLista *lista = Inicializa();
	TpContato *vet;
	char* numero = (char *) malloc (sizeof(char) * 6);
	strcpy(numero, "49332");
	char* constante = (char *) malloc (sizeof(char) * 9);
	strcpy(constante, "Fulano ");

	do {	
		
		option = Menu_Principal();
		printf("\n\n");

		switch (option) {
	

			case LISTA:{

				char *aux1 = (char*) malloc (sizeof(char)*6);
				char *aux2 = (char*) malloc (sizeof(char)*9);				
				
				if(!lista)
				{
					break;
				}
				
				printf("Digite o tamanho da lista:");
				scanf("%d",&limite_l);

				for(cont = 0 ; cont < limite_l; cont++) {

						strcpy(aux1,numero);
						strcpy(aux2,constante);
						lista = Inserir_para_Lista(lista,strcat(aux1,int_Para_String(getrand(1111,5999))),strcat(aux2,int_Para_String(getrand(400,499))));
				
				}

				Imprime_Lista(lista);

				break;
			}
			case VETOR:{

				char *aux1 = (char*) malloc (sizeof(char)*6);
				char *aux2 = (char*) malloc (sizeof(char)*9);				

				printf("Digite o tamanho do vetor:");
				scanf("%d",&limite_v);

				vet = (TpContato*) malloc (sizeof(TpContato)*limite_v);

				for(cont = 0; cont < limite_v; cont++) {
					
					strcpy(aux1,numero);
					strcpy(aux2,constante);

					strcat(aux1,(int_Para_String(getrand(1111,4999))));
					strcpy(vet[cont].fone, aux1);
					
					strcat(aux2,(int_Para_String(getrand(1111,4999))));
					strcpy(vet[cont].nome, aux2);
				}
				Imprime_Vetor(vet,limite_v);

				break;
			}
			case INSERT:{

				int op;
				TpContato *vetcopy = (TpContato*) malloc (sizeof(TpContato) * limite_v);
				TpLista *lcopy = Inicializa();
				op = Sub_Menu();
				srand(time(NULL));

				if(op == 1)
				{
					Copia_Vetor(vet,vetcopy,limite_v);
					Insertion_Sort_Vetor(vetcopy,limite_v);	
					Imprime_Vetor(vetcopy,limite_v);
				}
				if(op == 2) 
				{
					if(!lista) 
					{
						printf("Lista Vazia\n\n");
					}
					Copia_Lista(lista,lcopy);
					Insertion_Sort_Lista(lcopy);
					Imprime_Lista(lcopy);
				}

				t_fim = clock();//marca a diferença  de tempo...
				tempo = ((double)(t_fim-t_ini))/CLOCKS_PER_SEC;
				printf("\n\nTempo de %lf seg. da Insertion\n\n",tempo);
				break;
			}
			case SELECTION:{

				int op;
				TpContato *vetcopy = (TpContato*) malloc (sizeof(TpContato) * limite_v);
				TpLista *lcopy = Inicializa();
				op = Sub_Menu();
				srand(time(NULL));

				if(op == 1)
				{
					Copia_Vetor(vet,vetcopy,limite_v);
					Selection_Sort_Vetor(vetcopy,limite_v);
					Imprime_Vetor(vetcopy,limite_v);
				}
				if(op == 2) 
				{
					if(!lista) 
					{
						printf("Lista Vazia\n\n");
					}
					Copia_Lista(lista,lcopy);
					Selection_Sort_Lista(lcopy);
					Imprime_Lista(lcopy);
				}
				
				t_fim = clock();//marca a diferença  de tempo...
				tempo = ((double)(t_fim-t_ini))/CLOCKS_PER_SEC;
				printf("\n\nTempo de %lf seg. da Selection\n\n",tempo);
				break;
			}
			case QUICK:{

				int op;
				TpContato *vetcopy = (TpContato*) malloc (sizeof(TpContato) * limite_v);
				TpLista *lcopy = Inicializa();
				op = Sub_Menu();
				srand(time(NULL));
	
				if(op == 1)
				{
					Copia_Vetor(vet,vetcopy,limite_v);
					Quick_Sort_Vetor(vetcopy,0,limite_v-1);
					Imprime_Vetor(vetcopy,limite_v);
				}
				if(op == 2) 
				{
					if(!lista) 
					{
						printf("Lista Vazia\n\n");
					}
					Copia_Lista(lista,lcopy);
					Quick_Sort_Lista(lcopy,0,limite_l-1);
					Imprime_Lista(lcopy);
				}
				
				t_fim = clock();//marca a diferença  de tempo...
				tempo = ((double)(t_fim-t_ini))/CLOCKS_PER_SEC;
				printf("\n\nTempo de %lf seg. da Quick\n\n",tempo);
				break;
			}
			case MERGE:{

				int op;
				TpContato *vetcopy = (TpContato*) malloc (sizeof(TpContato) * limite_v);
				TpLista *lcopy = Inicializa();
				op = Sub_Menu();
				srand(time(NULL));

				if(op == 1)
				{
					Copia_Vetor(vet,vetcopy,limite_v);
					Merge_Sort_Vetor(vetcopy,limite_v);
					Imprime_Vetor(vetcopy,limite_v);
				}
				if(op == 2) 
				{
					if(!lista) 
					{
						printf("Lista Vazia\n\n");
					}
					Copia_Lista(lista,lcopy);
					Merge_Sort_Lista(lcopy,0,lcopy->last->indice);
					Imprime_Lista(lcopy);
				}
				
				t_fim = clock();//marca a diferença  de tempo...
				tempo = (()(t_fim-t_ini))/CLOCKS_PER_SEC;
				printf("\n\nTempo de %lf seg. da Merge\n\n",tempo);
				break;
			}
			default:

				break;
		}
	}
	while(option != 7 );

	Free_Lista(lista);
	Free_Vetor(vet,limite_v);

	return 0;			
}
