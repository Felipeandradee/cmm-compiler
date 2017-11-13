#include <stdio.h>
#include <stdlib.h>
#include "sintatico.h"

int main() {

    char nome_arquivo_in[10000] = "C:\\Users\\felip\\CodeBlocksProjects\\cmm-compiler\\TESTE.txt";
//    char nome_arquivo_out[100] = "SAIDA.txt";

//    printf("digite o nome do arquivo para a analise l�xica:\n");
//    scanf("%s", nome_arquivo_in);
//
//    printf("\ndigite o nome do arquivo para salvar os tokens:\n");
//    scanf("%s", nome_arquivo_out);

    printf("\nAnalisando o arquivo %s\n", nome_arquivo_in);
	fp = abrirArquivo(nome_arquivo_in);
//    analexico();
//	f_out = salvarArquivo(nome_arquivo_out);
	analexico();
    while(1){
        prog();
    }

}
