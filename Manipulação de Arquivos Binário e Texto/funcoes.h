struct TpAlu
{
	char NomeAlu[100], NomeDisc[100];
	float Notas[4];
	char situcao; //[A] Aprovado [R] Reprovado	
};

struct TpDisc
{
	char NomeDisc[30];
	float MediaDisc;
	int QtdAlu,QtdAprovado;
};

void CadAlunos(char NArq[70])
{
	FILE*ptr=fopen(NArq,"ab+");
	TpAlu RA;
	TpDisc D;
	clrscr();
	printf("\nDigite o Nome do aluno: ");
	fflush(stdin);
	gets(RA.NomeAlu);
	while(strcmp(RA.NomeAlu,"\0")!=0)
	{
		int i=0;
		float media=0,MediaDisc;
		printf("\nDisciplina: ");
		fflush(stdin);
		gets(RA.NomeDisc);
		for(i;i<4;i++)
		{
			printf("\nDigite a nota [%d]: ",i+1);
			scanf("%f",&RA.Notas[i]);	
			media+=RA.Notas[i];
		}
		strcpy(D.NomeDisc,RA.NomeDisc);
		MediaDisc=media/i;
		//QtdAlu++;
		if(MediaDisc>=6)//fazer media
			{
				RA.situcao='A';
			}
		else
			RA.situcao='R';
		
			fwrite(&RA,sizeof(TpAlu),1,ptr);
	//		fwrite(&D,sizeof(TpDisc),1,ptr);
			clrscr();
			
			printf("\nDigite o nome do aluno: ");
			fflush(stdin);
			gets(RA.NomeAlu);		
	}
	fclose(ptr);
}

void ExibeAlunos(char NArq[70])
{
	FILE*ptr=fopen(NArq,"rb+");
	clrscr();
	if(ptr==NULL)
		printf("\nO Arquivo esta vazio!");
		else
		{
			TpAlu A;int i;
			clrscr();
			printf("\n*** ALUNOS ***");
			fread(&A,sizeof(TpAlu),1,ptr);	
			while(!feof(ptr))
			{
				printf("\n--------------------------------------------");
				printf("\n%s\n%s\n%.2f - %.2f - %.2f - %.2f\n%c",A.NomeAlu,A.NomeDisc,A.Notas[0],A.Notas[1],A.Notas[2],A.Notas[3],A.situcao);
				fread(&A,sizeof(TpAlu),1,ptr);	
			}	
		}
	getch();
	fclose(ptr);
}
void GerarTexto(char Nome[50], char Texto[50])
{
	FILE*ptr=fopen(Nome,"rb+");
	FILE*ptr2=fopen(Texto,"w+");
	TpAlu A;
	fread(&A,sizeof(TpAlu),1,ptr);
	while(!feof(ptr))
	{
		fprintf(ptr2,"Nome: %s",A.NomeAlu);
		fputc('\n',ptr2);
		fprintf(ptr2,"Disciplina: %s",A.NomeDisc);
		fputc('\n',ptr2);
		fprintf(ptr2,"Notas: |%.2f |%.2f |%.2f |%.2f|",A.Notas[0],A.Notas[1],A.Notas[2],A.Notas[3]);
		fputc('\n',ptr2);
		fprintf(ptr2,"Situacao: %c",A.situcao);
		fread(&A,sizeof(TpAlu),1,ptr);	
		
		fputs("\n-----------------------------------------------------------\n",ptr2);
		
	}
	fclose(ptr);
	fclose(ptr2);
}
void InsereVet(TpAlu D, char Vet[100][100], int &TL)
{
	//TpDisc A;
	int i=0;
	FILE*ptr=fopen("Alunos.dat","rb");
	rewind(ptr);
	fread(&D,sizeof(TpAlu),1,ptr);
	while(!feof(ptr))
	{		
		if(TL==0)
			strcpy(Vet[TL++],D.NomeDisc);
		else
		{
			i=0;
			for(int j=0;j<TL;j++)
			{
				if(stricmp(Vet[j],D.NomeDisc)==0)
						i++;
							
			}
			if(i==0)
				strcpy(Vet[TL++],D.NomeDisc);	
			
		}
		fread(&D,sizeof(TpAlu),1,ptr);		
	}
	fclose(ptr);
}
void GeraBinario(char Nome[50], char Bin[50])
{
	int i=0,k=0, TL=0;
	TpAlu A;
	TpDisc D;
	char Vet[100][100];
	FILE*ptr;
	FILE*ptr2=fopen(Bin,"wb+");
	fclose(ptr2);
	ptr2=fopen(Bin,"rb+");
	//fread(&D,sizeof(TpDisc),1,ptr2);
//	fread(&A,sizeof(TpAlu),1,ptr);
	InsereVet(A,Vet,TL);
	for(int i=0;i<TL;i++)
	{
		int cont=0,contA=0;
		float media=0,MediaD=0;
		ptr=fopen(Nome,"rb+");
		fread(&A,sizeof(TpAlu),1,ptr);
		while(!feof(ptr))
		{
			if(stricmp(A.NomeDisc,Vet[i])==0)
			{
				media=(A.Notas[0]+A.Notas[1]+A.Notas[2]+A.Notas[3])/4;
				if(media>=6)
					contA++;
				MediaD+=media;
				cont++;
			}
			fread(&A,sizeof(TpAlu),1,ptr);
		}
		strcpy(D.NomeDisc,Vet[i]);
		D.MediaDisc=MediaD/cont;
		D.QtdAprovado=contA;
		D.QtdAlu=cont;
		fwrite(&D,sizeof(TpDisc),1,ptr2);
		fclose(ptr);
	}
	//fclose(ptr);
	fclose(ptr2);
}
void ExibeDisc(char Nome[30])
{
	clrscr();
	TpDisc D;
	FILE*ptr=fopen(Nome,"rb+");
	fread(&D,sizeof(TpDisc),1,ptr);
	while(!feof(ptr))
	{
		printf("\n-----------------------------------------------------------------------------");
		printf("\nDisciplina: %s\nMedia: %.2f\nAlunos: %d\nAlunos Aprovados: %d",D.NomeDisc,D.MediaDisc,D.QtdAlu,D.QtdAprovado);
		printf("\n-----------------------------------------------------------------------------");
		fread(&D,sizeof(TpDisc),1,ptr);	
	}
	getch();
}
void MostraTexto(char Nome[30])
{
	char lido;
	FILE*ptr=fopen(Nome,"rb+");
	if(ptr==NULL)
	printf("\nErro!");
	else
	{
		lido=fgetc(ptr);
		while(!feof(ptr))
		{
			printf("%c",lido);
			lido=fgetc(ptr);
		}
	}
	getch();
}
void MostraTextoT(char Nome[30])
{
	char Linha[100];
	FILE*ptr=fopen(Nome,"rb");
	if(ptr==NULL)
	printf("\nErro!");
	else
	{
		fgets(Linha, 100, ptr);	
		printf("%s",Linha);
			while(!feof(ptr))
			{
				fgets(Linha, 100, ptr);	
			   	  printf("%s",Linha);
			}
	}
	getch();
}
void InsereVet2(char Vet2[100][100],int &TL)
{
	TpAlu A;
	FILE*ptr=fopen("Alunos.dat","rb");
	int i;
	fread(&A,sizeof(TpAlu),1,ptr);
	while(!feof(ptr))
	{
		if(TL==0)
			strcpy(Vet2[TL++],A.NomeAlu);
		else
		{
			i=0;
			for(int j=0;j<TL;j++)
			{
				if(stricmp(Vet2[j],A.NomeAlu)==0)
						i++;
							
			}
			if(i==0)
				strcpy(Vet2[TL++],A.NomeAlu);	
			
		}
		fread(&A,sizeof(TpAlu),1,ptr);
	}
}
void GeraTextoGeral(char NomeA[70], char NomeD[70])
{
	TpAlu A;
	TpDisc D;
	FILE*ptr;
	FILE*ptr2=fopen("Relatorio Geral.txt","w+");
	fclose(ptr2);
	ptr2=fopen("Relatorio Geral.txt","r+");
	int TL=0;
	char Vet2[100][100];
	InsereVet2(Vet2,TL);
	for(int i=0;i<TL;i++)
	{
		ptr=fopen(NomeA,"rb+");
		fputs("\n------------------------------------------------------------------",ptr2);
		
		fread(&A,sizeof(TpAlu),1,ptr);
		fprintf(ptr2,"\nAluno: %s",Vet2[i]);
		fputs("\nDisciplinas:",ptr2);
		while(!feof(ptr))
		{
			if(stricmp(A.NomeAlu,Vet2[i])==0)
			{
				fprintf(ptr2,"\n%s | Notas: [%.2f][%.2f][%.2f][%.2f] | Situacao: %c",A.NomeDisc,A.Notas[0],A.Notas[1],A.Notas[2],A.Notas[3],A.situcao);
			}
			fread(&A,sizeof(TpAlu),1,ptr);
		}
		fclose(ptr);
	}
	fputs("\n------------------------------------------------------------------",ptr2);
	fclose(ptr2);
}
void Alimentar(char Nome[50])
{

	TpAlu A;
	float Media=0;
	//fscanf(ptr,%[^;];%[^;];%f;%f;%f;%f);
	FILE*ptr=fopen(Nome,"r");
	FILE*ptr2=fopen("Alunos.dat","ab+");

	
		fscanf(ptr,"%[^;];%[^;];%f;%f;%f;%f",&A.NomeAlu,&A.NomeDisc,&A.Notas[0],&A.Notas[1],&A.Notas[2],&A.Notas[3]);
		printf("\n%s - %s - %f %f %f %f",A.NomeAlu,A.NomeDisc,A.Notas[0],A.Notas[1],A.Notas[2],A.Notas[3]);
		Media=(A.Notas[0],A.Notas[1],A.Notas[2],A.Notas[3])/4;
			
			if(Media>=6)
				A.situcao='A';
			else
				A.situcao='R';
				
				fwrite(&A,sizeof(TpAlu),1,ptr2);
		while(!feof(ptr))
		{
			fscanf(ptr,"%[^;];%[^;];%f;%f;%f;%f",&A.NomeAlu,&A.NomeDisc,&A.Notas[0],&A.Notas[1],&A.Notas[2],&A.Notas[3]);
			printf("\n%s - %s - %f %f %f %f",A.NomeAlu,A.NomeDisc,A.Notas[0],A.Notas[1],A.Notas[2],A.Notas[3]);
			Media=(A.Notas[0],A.Notas[1],A.Notas[2],A.Notas[3])/4;
			
			if(Media>=6)
				A.situcao='A';
			else
				A.situcao='R';
				
				fwrite(&A,sizeof(TpAlu),1,ptr2);
		//	fread(&A,sizeof(TpAlu),1,ptr);
		}
		
	
	fclose(ptr);fclose(ptr2);
	getch();
}
