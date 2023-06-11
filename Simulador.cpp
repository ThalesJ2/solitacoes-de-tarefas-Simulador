#include <stdio.h>
#include <conio.h>
#include <conio2.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <ctype.h>
#include "tad2.h"

int addPrior (char tipo[60]){
	if(strstr(tipo,"Interno"))
		return 1;
	else
	if(strstr(tipo,"Externo"))
		return 2;
	else
	if(strstr(tipo,"Deletar"))
		return 3;
	else
	if(strstr(tipo,"Ler"))
		return 4;
	else
	if(strstr(tipo,"Imprimir"))
		return 5;
	
}

char Menu()
{
	clrscr();
	textcolor(3);
	gotoxy(53,2);
	printf("** MENU **\n\n");
	gotoxy(47,4);
	printf("[A] Iniciar Simulacao\n");
	gotoxy(47,6);
	printf("[B] Tarefas executadas \n");
	gotoxy(47,8);
	printf("[S] Sair\n");
	Moldura(45,1,70,10,4);
	return toupper(getch());
}



void imprimir(int cont1,int cont2,int cont3,int cont4,int cont5)
{
	clrscr();
	gotoxy(33,2);
	textcolor(14);
	printf("## Total individual de cada tarefa solicitada ##\n");
	gotoxy(34,4);
	printf("Gravar Dispositivo Interno: %d\n",cont1);
	gotoxy(34,5);
	printf("Gravar Dispositivo Externo: %d\n",cont2);
	gotoxy(34,6);
	printf("Deletar: %d\n",cont3);
	gotoxy(34,7);
	printf("Ler: %d\n",cont4);
	gotoxy(34,8);
	printf("Imprimir: %d\n",cont5);
	gotoxy(34,9);
	Moldura(32,1,82,10,13);
	getch();
	
}
void Executadas(TpDesc desc)
{
	clrscr();
	TpPont*aux = desc.inicio;
	if(desc.inicio != NULL)
	{
		TpPont*aux = desc.inicio;
		while(aux->prox!=NULL)
		{
			if(aux->cont > 0)
			{
				printf("Processador %d \n",aux->processador);	
				printf("Quantidade tarefas executadas: %d\n",aux->cont);
			}
			aux = aux->prox;
			
		}
		
	}
	else
		printf("Nenhuma tarefa executada\n");

	
	getch();
	
}

void salvar(TpDesc desc)
{
	FILE*arq = fopen("salvar.txt","w");
	char aux[120];
	TpPont*lista = desc.inicio;
	TpFila*fila;
	
	while(lista !=NULL)
	{
		fila = lista->filaDesc.inicio;
		
		while(fila !=NULL)
		{
			fprintf(arq,"%d;%s;%s;%d\n",fila->proc,fila->nome,fila->tipo,fila->ut);
			fila = fila->prox;
		}
		lista = lista->prox;
	}
	
	fclose(arq);
}
void recuperar(TpDesc &desc,FILE*arq)
{
	TpFila fila;
	TpPont*atual;
	int num;
	fscanf(arq,"%d;%[^;];%[^;];%d\n",&num, &fila.nome, &fila.tipo, &fila.ut);
	while(!feof(arq))
	{
		if(Busca(desc,num)==NULL){
			fila.prior = addPrior(fila.tipo);
			fila.proc = num;
			InserirLista(desc,num);
			atual = Busca(desc,num);
			InserirFila(atual->filaDesc,fila);
	
		}
		else
		{
			fila.prior = addPrior(fila.tipo);
			fila.proc = num;
			atual = Busca(desc,num);
			InserirFila(atual->filaDesc,fila);
		
		}
		fscanf(arq,"%d;%[^;];%[^;];%d\n",&num, &fila.nome, &fila.tipo, &fila.ut);
	}
}
void simular (TpDesc &desc,int &pos){
	system("cls");
	TpDescFila descFila;
	TpFila fila;
	TpPont*atual,*aux1;
	initFila(descFila);
	int num;
	int ut=0;
	int cont1=0,cont2=0,cont3=0,cont4=0,cont5=0;
	char flag = 1,op;
	FILE*arq = fopen("trabalho.txt","r");
	FILE*rec = fopen("salvar.txt","r");
	if(rec != NULL)
		recuperar(desc,rec);
	if(pos > 0 )
		fseek(arq,pos,SEEK_SET);
		
		
	while(!feof(arq) && flag)
	{
		if(!kbhit())
		{
				if(ut%2==0)
				{
					
					fscanf(arq,"%d;%[^;];%[^;];%d\n",&num, &fila.nome, &fila.tipo, &fila.ut);
						if(Busca(desc,num)==NULL){
							fila.prior = addPrior(fila.tipo);
							fila.proc = num;
							InserirLista(desc,num);
							atual = Busca(desc,num);
							InserirFila(atual->filaDesc,fila);
					
						}
						else
						{
							fila.prior = addPrior(fila.tipo);
							fila.proc = num;
							atual = Busca(desc,num);
							InserirFila(atual->filaDesc,fila);
						
						}
						
					if(strstr(fila.tipo,"Interno"))
						cont1++;
					if(strstr(fila.tipo,"Externo"))
						cont2++;
					if(strstr(fila.tipo,"Deletar"))
						cont3++;
					if(strstr(fila.tipo,"Ler"))
						cont4++;
					if(strstr(fila.tipo,"Imprimir"))
						cont5++;
						
				}
				
				if(atual->filaDesc.inicio !=NULL)
				{	
					Relatorio(desc);
					atual->filaDesc.inicio->ut--;
					if(atual->filaDesc.inicio->ut==0)
					{
						atual->cont++;
						//retirar(atual->filaDesc);
						atual->filaDesc.inicio = atual->filaDesc.inicio->prox;
					}
						
					Sleep(1000);
					clrscr();	
				}
				ut++;
		}
		else
		{
			op = getch();
			if(op==27)
			{
				salvar(desc);
				pos = ftell(arq);
				flag =0;
			}
				
		}
	}	
	fclose(arq);
	fclose(rec);
	imprimir(cont1,cont2,cont3,cont4,cont5);
	getch();
	
}
int main (){
	char op;
	TpDesc desc;
	int pos =0;
	init(desc);
	do{
		op = Menu();
		
		switch(op){
			case 'A':simular(desc,pos);
				break;
			case 'B':Executadas(desc);
				break;
				
		}
		
	}while(op!=83);
	remove("salvar.txt");
	return 0;
}
