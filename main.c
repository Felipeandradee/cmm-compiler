#include <stdio.h>
#include <stdlib.h>
#include "sintatico.h"

int main() {

    //Caminho de teste de Felipe
    //char nome_arquivo_in[10000] = "C:\\Users\\felip\\CodeBlocksProjects\\cmm-compiler\\cd2.txt";
    //Caminho de testes de Lucas
    char nome_arquivo_in[10000] = "C:\\Users\\Luck\\Desktop\\GItHub\\cmm-compiler\\TESTE.txt";

    printf("\nAnalisando o arquivo %s\n", nome_arquivo_in);
	fp = abrirArquivo(nome_arquivo_in);

	//Analisador lexico e sintatico
	analexico();
    prog();

}
