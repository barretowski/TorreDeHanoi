#include<conio2.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "funcoes.h"

char menu()
{
	clrscr();
	textcolor(11);printf("\n--- Arquivos binarios e texto ---\n");textcolor(15);
	printf("\n[A] Cadastro de alunos");
	printf("\n[B] Exibir alunos em tela");
	printf("\n[C] Gerar relatorio em arquivo texto");
	printf("\n[D] Gerar o arquivo binario Disciplinas.dat a partir do aqruivo binario Alunos.dat");
	printf("\n[E] Exibe disciplinas em tela");
	printf("\n[F] Gerar relatorio em Arq texto de todos os alunos e suas disciplinas");
	printf("\n[G] Exibir aqruivo texto (caracter a caracter)");
	printf("\n[H] Exibir aqruivo texto (bloco de caracter)");
	printf("\n[I] Alimentar dados a partir de um arquivo texto");//Alimentar.csv
	textcolor(12);printf("\n\n[ESC] Sair");
	textcolor(15);
	printf("\nOpcao desejada: ");
	
	return toupper(getch());
}
void executa()
{
	char op,Nome[30];
	char Arq[40];
	do
	{
		op=menu();
		switch(op)
		{
			case 'A':
				CadAlunos("Alunos.dat");
				break;
			case 'B':
				ExibeAlunos("Alunos.dat");
				break;
			case 'C':
				GerarTexto("Alunos.dat","Relatorio.txt");
				break;
			case 'D':
				GeraBinario("Alunos.dat","Disciplinas.dat");
				break;
			case 'E':
				ExibeDisc("Disciplinas.dat");
				break;
			case 'F':
				GeraTextoGeral("Alunos.dat","Disciplinas.dat");
				break;
			case 'G':
				clrscr();
				MostraTexto("Relatorio.txt");
				break;
			case 'H':
				clrscr();
				MostraTextoT("Relatorio.txt");
				break;
			case 'I':
				clrscr();
				printf("\nDigite o nome do arquivo: ");
				fflush(stdin);
				gets(Arq);
				Alimentar(Arq);
				break;
				
		}
	}while(op!=27);
}
int main()
{
	executa();
}
