#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"
//#include "lexico.c"

int main() {

    char nome_arquivo_in[100];
    char nome_arquivo_out[100];

    printf("digite o nome do arquivo para a analise léxica:\n");
    scanf("%s", nome_arquivo_in);

    printf("\ndigite o nome do arquivo para salvar os tokens:\n");
    scanf("%s", nome_arquivo_out);

    printf("\nAnalisando o arquivo %s\n", nome_arquivo_in);
	fp = abrirArquivo(nome_arquivo_in);
	f_out = salvarArquivo(nome_arquivo_out);
	analexico(fp, f_out);
    fclose(fp);
    fclose(f_out);
    printf("ENDPROGRAM\n");
    printf("\nToken salvos em %s\n", nome_arquivo_out);
    system("PAUSE");

    return 0;
}
