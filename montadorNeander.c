#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char mnemonico[3+1];
	char nomeArquivo[30];
	unsigned int endereco;
	
	printf("\nPor favor, digite o nome do arquivo que ser%c convertido (escreva como no exemplo: 'exemplo.asm')\n", 160);
	gets(nomeArquivo);
	
	FILE *arquivoEntrada, *arquivoSaida; //Cria os ponteiros para o arquivo de entrada e para o de sa�da
	
	arquivoEntrada = fopen(nomeArquivo, "r"); //Abre o arquivo de entrada .asm no modo leitura
	
	if (arquivoEntrada == NULL) //Confere se houve erro ao tentar abrir o arquivo de entrada
	{
		printf("\nErro ao abrir o arquivo de entrada.");
		exit(1);
	}
	
	arquivoSaida = fopen("neander.mem", "wb"); //Abre o arquivo de sa�da .mem no modo de escrita em modo bin�rio
	
	if (arquivoSaida == NULL) //Confere se houve erro ao tentar abrir o arquivo de sa�da
	{
		printf("\nErro ao criar o arquivo de sa%cda.", 161);
		exit(1);
	}
	
	putc(0x03, arquivoSaida); // Grava o cabe�alho que os arquivos do Neander precisam ter
	putc(0x4E, arquivoSaida);
	putc(0x44, arquivoSaida);
	putc(0x52, arquivoSaida);
	
	while (fscanf(arquivoEntrada, "%s", mnemonico) == 1)
	{
		unsigned char opcode;
		int recebeEndereco = 1; // Flag para verificar se a instru��o precisa de endere�o
		
		//Substitui o mnemonico pelo opcode correspondente
		if (strcmp(mnemonico, "NOP") == 0)
		{
			opcode = 0x00;
			recebeEndereco = 0; //NOP n�o usa endere�o
		}
		else
		if (strcmp(mnemonico, "STA") == 0)
		opcode = 0x10;
		else
		if (strcmp(mnemonico, "LDA") == 0)
		opcode = 0x20;
		else
		if (strcmp(mnemonico, "ADD") == 0)
		opcode = 0x30;
		else
		if (strcmp(mnemonico, "OR") == 0)
		opcode = 0x40;
		else
		if (strcmp(mnemonico, "AND") == 0)
		opcode = 0x50;
		else
		if (strcmp(mnemonico, "NOT") == 0)
		{
			opcode = 0x60;
			recebeEndereco = 0; //NOT n�o usa endere�o
		}
		else
		if (strcmp(mnemonico, "JMP") == 0)
		opcode = 0x80;
		else
		if (strcmp(mnemonico, "JN") == 0)
		opcode = 0x90;
		else
		if (strcmp(mnemonico, "JZ") == 0)
		opcode = 0xA0;
		else
		if (strcmp(mnemonico, "HLT") == 0)
		{
			opcode = 0xF0;
			recebeEndereco = 0; //HLT n�o recebe endere�o
		}
		else
		{
			printf("\nMnem%cnico n%co reconhecido.", 147, 198);
			fclose(arquivoEntrada);
			fclose(arquivoSaida);
			return (1);
		}
		fputc(opcode, arquivoSaida); fputc(0x00, arquivoSaida); //Grava o opcode no arquivo .mem
		
		if (recebeEndereco) //Caso a instru��o utilize endere�os
		{
			if (fscanf(arquivoEntrada, "%x", &endereco) == 1) 
			{
				fputc(endereco, arquivoSaida);    fputc(0x00, arquivoSaida); //Grava no arquivo de sa�da o endere�o lido no arquivo de entrada
			}
			else
			{
				printf("\nEndere%co esperado ap%cs o mnem%cnico %s.", 135, 162, 147, mnemonico);
				fclose(arquivoEntrada);
				fclose(arquivoSaida);
				return (1);
			}
		}
	}
	
	fclose(arquivoEntrada);
	fclose(arquivoSaida);
	
	printf("\nArquivo convertido com sucesso!!!");
	
	getch();
	return (0);
}