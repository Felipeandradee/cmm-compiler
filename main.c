#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"
//#include "lexico.c"

int main() {
	int opcao, valor;

	fp = abrirArquivo("TESTE.txt");
	analexico(fp);
    fclose(fp);
    printf("ENDPROGRAM\n");


    system("PAUSE");

    return 0;
}
