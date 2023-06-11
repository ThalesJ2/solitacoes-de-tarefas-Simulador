struct TpFila{
	int proc;
	char nome[60];
	char tipo[60];
	int ut;
	int prior;
	TpFila*prox,*ant;
	
};

struct TpDescFila{
	int qtde;
	TpFila*inicio,*fim;
};


struct 	TpPont{
	int processador;
	int cont;
	TpPont*prox;
	TpDescFila filaDesc;
};

struct TpDesc{ 
	int qtde;
	TpPont*inicio,*fim;
};



void init(TpDesc &dec);
void initFila(TpDescFila &fila);
void InserirLista(TpPont*lista,int proc);


void init(TpDesc &desc){
	desc.qtde = 0;
	desc.inicio = NULL;
	desc.fim = NULL;
}
void initFila(TpDescFila &fila){
	fila.inicio = fila.fim = NULL;
	fila.qtde = 0;
}

TpPont*Busca (TpDesc desc , int num){
	
	TpPont*aux;
	aux = desc.inicio;
	while(aux !=NULL && aux->processador != num)
		aux = aux->prox;
		
	if(aux!=NULL)
		return aux;
	else
		return NULL;
	
}

void retirar(TpDescFila &desc)
{
	TpFila*aux = desc.inicio->prox;
	delete(desc.inicio);
	desc.inicio = aux;
}

void InserirLista(TpDesc &desc,int proc){
	TpPont*caixa = new TpPont;
	TpPont*aux,*atual;
	caixa->processador = proc;
	caixa->cont = 0;
	caixa->prox = NULL;
	if(desc.inicio == NULL)
		desc.inicio = desc.fim = caixa;
	else
		if(desc.inicio->processador > caixa->processador)
		{
			caixa->prox = desc.inicio;
			desc.inicio = caixa;
			
		}
		else
		if(caixa->processador > desc.fim->processador)
		{
			desc.fim->prox = caixa;
			desc.fim = caixa;
		}
		else
		{
			aux = desc.inicio;
			atual = desc.inicio->prox;
			while(caixa->processador > atual->processador)
			{
				aux = atual;
				atual = atual->prox;
			}
			caixa->prox = atual;
			aux->prox = caixa;
			
		}

}
TpFila*NC(TpFila fila){
	TpFila*caixa = new TpFila;
	strcpy(caixa->nome,fila.nome);
	caixa->proc = fila.proc;
	strcpy(caixa->tipo,fila.tipo);
	caixa->ut = fila.ut;
	caixa->prior = fila.prior;
	caixa->prox = caixa->ant = NULL;
	return caixa;
	
}
void Moldura(int CI, int LI, int CF, int LF, int Cor)
{
	int i;
	textcolor(Cor);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LF);
	printf("%c",188);
	
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI);
		printf("%c",205);
		//Sleep(1);
		gotoxy(i,LF);
		printf("%c",205);
	}
	
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i);
		printf("%c",186);
		//Sleep(1);
		gotoxy(CF,i);
		printf("%c",186);
	}
	
	textcolor(7);      //0..15
	textbackground(0); //0..7
}
void Ordena(TpFila fila,TpDescFila &desc){
		TpFila*atual,*aux,*caixa;
	
		if(desc.qtde > 2)
		{
			caixa = NC(fila);
			aux = desc.fim->ant->prox = NULL;
			delete(desc.fim);
			desc.fim = atual;
			atual = desc.inicio;
			
			while(atual->prox != NULL && caixa->prior > atual->prior)
				atual = atual->prox;
			
			if(atual->prox == NULL)
			{
				atual->prox = caixa;
				caixa->ant = atual;
				desc.fim = caixa;
				
			}	
			else
			{
				caixa->prox = atual;
				caixa->ant = atual->ant;
				atual->ant->prox = caixa;
				atual->ant = caixa;	
			}
		}
	
}
void InserirFila(TpDescFila &desc, TpFila fila){
	TpFila*caixa = new TpFila;
	strcpy(caixa->nome,fila.nome);
	caixa->proc = fila.proc;
	strcpy(caixa->tipo,fila.tipo);
	caixa->ut = fila.ut;
	caixa->prior = fila.prior;
	desc.qtde++;
	caixa->prox = caixa->ant = NULL;

	if(desc.inicio == NULL)
	 	desc.inicio = desc.fim = caixa;
	else
	{
		caixa->ant  = desc.fim;
		desc.fim ->prox = caixa;
		desc.fim  = caixa;	
	}
	
	
	if(desc.inicio->prior >= desc.fim->prior){
		caixa->prox = desc.inicio;
		desc.inicio->ant = caixa;
		desc.fim->ant->prox = NULL;
		desc.fim = desc.fim->ant;
		desc.inicio = caixa;
	}	
	else
		Ordena(fila,desc);
}

void Exibir(TpDesc desc){
	
	while(desc.inicio != NULL){
		printf("%d ",desc.inicio->processador);
		desc.inicio = desc.inicio->prox;
	}
}

void Relatorio(TpDesc desc){
	TpPont*aux = desc.inicio;
	TpFila*fila;
	//system("cls");
	//Sleep(1000);
	
	while(aux!=NULL)
	{
		textcolor(6);
		printf("\n  Processador %d \n\n",aux->processador);
		fila = aux->filaDesc.inicio;
			if(aux->processador == fila->proc)
			{
				printf("\n");
				printf("  %s ",aux->filaDesc.inicio->nome);
				printf("  %s ",aux->filaDesc.inicio->tipo);
				printf("  %d ",aux->filaDesc.inicio->ut);
				printf("\n");
				textcolor(10);
				printf("======================================================");
		  }
		
		aux = aux->prox;
	}
	Moldura(1,1,55,21,10);
	Sleep(2000);
	clrscr();
}
