#include "GerenciadorTS.h"
#include "AnaSint.h"

int base_pilha = 0;
int topo_pilha = 0;
int enderecoRelativo2 = 0;
int enderecoRelativo3 = 0;

char pTipo[5][20] = {
        {""},
        {"VARIAVEL"},
        {"FUNCAO"},
        {"FUNCAO_PROTOTIPO"},
        {"PARAMETRO"}
};


char pEscopo[2][20] = {
        {"GLOBAL"},
        {"LOCAL"}
};

void adicionar_Tabela_Simbolos(char id_[], char tipoDaVariavel[] ,Escopo escopo_, TipoSimbolo tipo_) {
    strcpy(tabela_Simbolos[topo_pilha].id, id_);
    strcpy(tabela_Simbolos[topo_pilha].tipoVariavel, tipoDaVariavel);
    tabela_Simbolos[topo_pilha].escopo = escopo_;
    tabela_Simbolos[topo_pilha].tipo = tipo_;
    tabela_Simbolos[topo_pilha].zumbi = FALSE;
    topo_pilha++;
}

void addEnderecoRelativo(char id_[], Escopo escopo_, TipoSimbolo tipo_){
	int x;

	for (x = topo_pilha - 1; x >= base_pilha; x--) {
        if (!strcmp(tabela_Simbolos[x].id, id_)){

        	if(escopo_ == LOCAL && tipo_ == VARIAVEL){
				tabela_Simbolos[x].enderecoRelativo = enderecoRelativo2;
				enderecoRelativo2++;
			}

			if(escopo_ == GLOBAL && tipo_ == VARIAVEL){
				tabela_Simbolos[x].enderecoRelativo = enderecoRelativo3;
				enderecoRelativo3++;
			}

		}
    }
}


void addEnderecoRelativoParametros(char id_[], Escopo escopo_, TipoSimbolo tipo_, int qtdParam){
	int x;
	int posicao_param_func;
	int EnderecoRelativo7 = -3;
	char id[50];
	
	//LOCAL //PARAMETRO
	
	for (x = topo_pilha - 1; x >= base_pilha; x--) {
        if (!strcmp(tabela_Simbolos[x].id, id_)){	
        	for(x = topo_pilha - 1; x >= base_pilha; x--){
    			if((tabela_Simbolos[x].escopo == LOCAL) && (tabela_Simbolos[x].tipo == PARAMETRO)){	
            		for(x = topo_pilha - 1; x >= base_pilha; x--){
						if((tabela_Simbolos[x].escopo == LOCAL) && (tabela_Simbolos[x].tipo == PARAMETRO)){
							tabela_Simbolos[x].enderecoRelativo = EnderecoRelativo7;
							EnderecoRelativo7--;
						}
					}
				}	
			}
		}
	}
}

int retorna_endereco_relativo(char id_[]) {
    int x;

	for (x = topo_pilha - 1; x >= base_pilha; x--) {
        if (!strcmp(tabela_Simbolos[x].id, id_)){
			return tabela_Simbolos[x].enderecoRelativo;
		}
    }
}

int retorna_escopo(char id_[]) {
    int x;

	for (x = topo_pilha - 1; x >= base_pilha; x--) {
        if (!strcmp(tabela_Simbolos[x].id, id_)){
			return tabela_Simbolos[x].escopo;
		}
    }
}



void pesquisar_Tabela_Simbolos(char id_[], Escopo escopo_recebido, TipoSimbolo tipo_) {
    int x;

    for (x = topo_pilha - 1; x >= base_pilha; x--) {
        if (!strcmp(tabela_Simbolos[x].id, id_) && tabela_Simbolos[x].zumbi == FALSE
            && tabela_Simbolos[x].escopo == escopo_recebido && tabela_Simbolos[x].tipo != PARAMETRO) {
            if (tipo_ == FUNCAO && tabela_Simbolos[x].tipo == FUNCAO_PROTOTIPO)
                continue;

            listar_Tabela_Simbolos();

            printf("\nERRO LINHA %d %s %s REDECLARADA EM ESCOPO %s\n\n", linha, pTipo[tipo_], tabela_Simbolos[x].id, pEscopo[escopo_recebido]);
            system("PAUSE");

        }

    }

}

void declarado_na_tabela_simbolos(char id_[]) {
    int x;

    for (x = topo_pilha - 1; x >= base_pilha; x--) {
        if (!strcmp(tabela_Simbolos[x].id, id_)) {
            return;

        }

    }
    printf("\nERRO LINHA %d, %s NAO DECLARADA.\n\n", linha, id_);
    system("PAUSE");

}

int pesquisar_Tipo(char id_[]) {
    int caracter, inteiro, real;

	int x;

    for (x = topo_pilha - 1; x >= base_pilha; x--) {
        if (!strcmp(tabela_Simbolos[x].id, id_)) {
            if(!strcmp(tabela_Simbolos[x].tipoVariavel, "inteiro")){
				inteiro = 1;
                strcpy(tipo_dado, "inteiro");
            	return inteiro;
			}

            if(!strcmp(tabela_Simbolos[x].tipoVariavel, "caracter")){
            	caracter = 2;
                strcpy(tipo_dado, "caracter");
            	return caracter;
			}

            if(!strcmp(tabela_Simbolos[x].tipoVariavel, "real")){
            	real = 3;
                strcpy(tipo_dado, "real");
            	return real;
			}

        }

    }

}

void excluir_Tabela_Simbolos() {

    while (tabela_Simbolos[topo_pilha - 1].escopo == LOCAL
           && tabela_Simbolos[topo_pilha - 1].tipo != FUNCAO) {

        if (tabela_Simbolos[topo_pilha - 1].tipo == PARAMETRO)
            tabela_Simbolos[topo_pilha - 1].zumbi = TRUE;

        topo_pilha--;

    }
}

void listar_Tabela_Simbolos() {
    int x;

    for (x = base_pilha; x <= topo_pilha; x++) {
        printf("\n");
        printf(tabela_Simbolos[x].id);
    }
}

void addParamFunc(char id2[]){
	char idAux[50];
	int x, qtd;

    for(x = topo_pilha - 1; x >= base_pilha; x--)
    {
        if(!strcmp(tabela_Simbolos[x].id, id2) && tabela_Simbolos[x].qtd_param != 0 )
     	{
     		strcpy(idAux,tabela_Simbolos[x].id);
			qtd = tabela_Simbolos[x].qtd_param;

			for(x = topo_pilha - 1; x >= base_pilha; x--){
				if(!strcmp(idAux, tabela_Simbolos[x].id) && tabela_Simbolos[x].qtd_param == 0){
					tabela_Simbolos[x].qtd_param = qtd;
				}
			}
		}
	}
}

void addParamFunc2(char id2[], int posicaoParam){
	char idAux[50], params[50];
	int x, qtd;

    for(x = topo_pilha - 1; x >= base_pilha; x--)
    {
        if(!strcmp(tabela_Simbolos[x].id, id2) && strcmp(tabela_Simbolos[x].parametros[posicaoParam], "\000"))
     	{
     		strcpy(idAux,tabela_Simbolos[x].id);
			strcpy(params,tabela_Simbolos[x].parametros[posicaoParam]);

			for(x = topo_pilha - 1; x >= base_pilha; x--){
				if(!strcmp(idAux, tabela_Simbolos[x].id) && !strcmp(tabela_Simbolos[x].parametros[posicaoParam], "\000")){
					strcpy(tabela_Simbolos[x].parametros[posicaoParam],params);
				}
			}
		}
	}
}

void adicionar_qtd_param(int qtd, char id_[]) //Guarda a quantidade de  parâmetros na tabela de símbolos
{
    int x;

     for(x = topo_pilha - 1; x >= base_pilha; x--)
     {
          if(!strcmp(tabela_Simbolos[x].id, id_))
     	  {
     	     tabela_Simbolos[x].qtd_param = qtd;
		  }
	 }

}

//Guarda os tipos dos parâmetros numa matriz na tabela de símbolos
void adicionar_Tipos_Param(int posicao_parametro , char tipo_Param[], char id_[])
{
   int x;

     for(x = topo_pilha - 1; x >= base_pilha; x--)
     {

          if(!strcmp(tabela_Simbolos[x].id, id_))
     	  {
             strcpy(tabela_Simbolos[x].parametros[posicao_parametro], tipo_Param);
              return;
	      }

	 }

}

void verificar_retorno_expr(char nome_funcao[], char tipo_retorno_expr[], char id_[]) //Verifica se o tipo de retorno da função é o mesmo da expressão
{
	int x;

	if(!strcmp(tipo_retorno_expr, "")){     //Caso o retorno seja só uma declaração de variavel.

		for(x = topo_pilha - 1; x >= base_pilha; x--)
		{
	     	if(!strcmp(tabela_Simbolos[x].id, id_))
         	{
         		strcpy(tipo_retorno_expr, tabela_Simbolos[x].tipoVariavel);
		 	}
		}
	}

    for(x = topo_pilha - 1; x >= base_pilha; x--)
	{
	     if(!strcmp(tabela_Simbolos[x].id, nome_funcao))
         {
         	if(strcmp(tabela_Simbolos[x].tipoVariavel,tipo_retorno_expr) != 0 ) modulo_erros((Erro)RETURN_EXPR_ERRO);
		 }
	}

}

void pesquisar_assinatura(char tipo_recebido[],char id_recebido[],char parametros[][8],int sinal, int num_parametros){
    //Sinal: 1 para indicar função, 0 para indicar procedimento (ou é o contrário)
    int posicao_assinaturas, posicao_param_func, achou_id=0, x;
    char idAux1[50];

    if(sinal){

        for(x = topo_pilha - 1; x >= base_pilha; x--) {

            //Verifica se possui o mesmo id da assinatura
            if(!strcmp(tabela_Simbolos[x].id, id_recebido) && tabela_Simbolos[x].tipo == FUNCAO_PROTOTIPO){ //verificar esta validação com Felipe
                achou_id=1;

                //Tipo recebido não pode ser int (Lucas)
                if(!strcmp(tabela_Simbolos[x].tipoVariavel, tipo_recebido)){  //Verifia se possui mesmo tipo de retorno da assinatura

					strcpy(idAux1,id_recebido);
					if(tabela_Simbolos[x].tipo != FUNCAO_PROTOTIPO)  //Para colocar mesma quantidade de parametros na funão da assinatura
			 			addParamFunc(idAux1);

                    //Verifica a quantidade de argumentos da assinatura em relação a func
                    if(tabela_Simbolos[x].qtd_param == num_parametros){


                        if(strcmp(parametros[0],"semparam") != 0){

                            //Verifica se os tipos dos argumentos da função são os mesmos da assinatura (Concertar aqui !!)
                            for(posicao_param_func=0; posicao_param_func < num_parametros; posicao_param_func++)
                            {
                            	addParamFunc2(idAux1, posicao_param_func);

                                if(strcmp(tabela_Simbolos[x].parametros[posicao_param_func],parametros[posicao_param_func]) != 0)
                                    modulo_erros((Erro)ARGUMENTO_INVALIDO_ERROR);
                            }

                        }


                    }else modulo_erros((Erro)QUANTIDADE_ARGUMENTOS_ERROR);

                }
                else modulo_erros((Erro)ASSINATURA_RETORNO_ERROR);
            }

        }

    }
    else if(sinal == 0){

        for(x = topo_pilha - 1; x >= base_pilha; x--) {

            //Verifica se possui o mesmo id da assinatura
            if(!strcmp(tabela_Simbolos[x].id, id_recebido) && tabela_Simbolos[x].tipo == FUNCAO_PROTOTIPO){
                achou_id=1;

                //Verifica a quantidade de argumentos de proc em relação a assinatura
                if(tabela_Simbolos[x].qtd_param == num_parametros){

                    if(strcmp(parametros[0],"semparam") != 0){
                        //Verifica se os tipos dos argumentos de proc são os mesmos da assinatura
                        for(posicao_param_func=0; posicao_param_func < num_parametros; posicao_param_func++){
                            if(strcmp(tabela_Simbolos[x].parametros[posicao_param_func],parametros[posicao_param_func]) != 0)
                                modulo_erros((Erro)ARGUMENTO_INVALIDO_ERROR);
                        }

                    }

                } else modulo_erros((Erro)QUANTIDADE_ARGUMENTOS_ERROR);
            }
        }

//        if(!achou_id) modulo_erros((Erro)ID_NAO_ENCONTRADO_ERROR);

    }

}

void verificar_param_func(char nome_funcao[], int num_parametros, char parametros[][8]){
    int x, posicao_param_func;

        for(x = topo_pilha - 1; x >= base_pilha; x--)
        {
            if(!strcmp(tabela_Simbolos[x].id, nome_funcao))
            {
                if(tabela_Simbolos[x].qtd_param != num_parametros)
                    modulo_erros((Erro)QUANTIDADE_ARGUMENTOS_ERROR);
                else {

                    for(posicao_param_func=0; posicao_param_func < num_parametros; posicao_param_func++)
                    {
                        if(strcmp(tabela_Simbolos[x].parametros[posicao_param_func],parametros[posicao_param_func]) != 0)
                            modulo_erros((Erro)ARGUMENTO_INVALIDO_ERROR);
                    }

                }
            }
        }
}



//Geração de codigo.

void adicionar_label_Tabela(char id_[], char novo_label[])
{
    int x;

    for(x = topo_pilha - 1; x >= base_pilha; x--)
	{
	    if(!strcmp(tabela_Simbolos[x].id, id_))
			strcpy(tabela_Simbolos[x].label, novo_label);
    }

}

//GERA CÓDIGO PARA CHAMADA DE FUNÇÃO
void pesquisar_nome_func(char id_[])
{
    int x;

    for(x = topo_pilha - 1; x >= base_pilha; x--)
	{
		if(!strcmp(tabela_Simbolos[x].id, id_))
		{
		   //GERA CÓDIGO
		   //fprintf(arquivo_gerador,"LDA %d,%d\n", tabela_Simbolos[x].escopo,tabela_Simbolos[x].deslocamento);
		   fprintf(arquivo_gerador,"CALL %s\n", tabela_Simbolos[x].label);
		}

	}

}

Boolean tem_principal(){

    int x;

    for(x = topo_pilha - 1; x >= base_pilha; x--)
    {
        if(!strcmp(tabela_Simbolos[x].id, "principal"))
        {
            return TRUE;
        }

    }
    return FALSE;

}
