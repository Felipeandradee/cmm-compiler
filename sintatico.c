#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"



//TODO: revisar Lista de variaveis
//int linha = 0; //proc_ = 0, func_ = 0;
int enquanto_for_comando = 1;
int veioExpressao = 0;
int veioFator = 0;
int veioAtribuicao = 0;
int posicao_fixa = 0;
int posicao_atual = 0;
int tipoRelacional; //Define qual � o operacional utilizado, facilita para fazer compara��es posteriormente
int posicaoParametros; //posi��o dos parametros
int contagemParametros; //contagem dos parametros
int eparam; //� Parametro (variavel que verifica se � um parametro)

//Token como global
//TOKEN Token; //No de Felipinho � lookAhead
//Encerramento da lista de variaveis.

//TODO: Ver como vai ficar em questao do ultimo token
void proximo_Token(){
    Token = TNext;
    if(Token.cat != END)
        analexico();

}

//TODO: revisar o modulo_erros
void modulo_erros(Erro tipo_erro)
{
    switch(tipo_erro)
    {
        case ID_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, ESPERADO IDENTIFICADOR!\n\n", linha);
            system("PAUSE");
            break;

        case ENDVAR_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, ENDVAR ESPERADO!\n\n", linha);
            system("PAUSE");
            break;

        case TIPO_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, TIPO ESPERADO!\n\n", linha);
            system("PAUSE");
            break;

        case ABERTURA_PARENTESE_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, ABERTURA DE PARENTESE ESPERADO!\n\n", linha);
            system("PAUSE");
            break;

        case FECHAMENTO_PARENTESE_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, FECHAMENTO DE PARENTESE ESPERADO!\n\n", linha);
            system("PAUSE");
            break;

        case ABERTURA_CHAVES_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, ABERTURA DE CHAVES ESPERADO!\n\n", linha);
            system("PAUSE");
            break;

        case FECHAMENTO_CHAVES_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, FECHAMENTO DE CHAVES ESPERADO!\n\n", linha);
            system("PAUSE");
            break;

        case NOPARAM_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, TIPO OU NOPARAM ESPERADOS!\n\n", linha);
            system("PAUSE");
            break;

        case EXPRESSAO_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, EXPRESSAO ESPERADA!\n\n", linha);
            system("PAUSE");
            break;

        case FATOR_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, FATOR ESPERADO!\n\n", linha);
            system("PAUSE");
            break;

        case TERMO_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, FATOR ESPERADO!\n\n", linha);
            system("PAUSE");
            break;

        case EXPR_SIMP_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, EXPR_SIMP INVALIDA!\n\n", linha);
            system("PAUSE");
            break;

        case EXPR_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, EXPR INVALIDA!\n\n", linha);
            system("PAUSE");
            break;

        case COMANDO_VAZIO_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, COMANDO VAZIO ERRO!\n\n", linha);
            system("PAUSE");
            break;

        case FECHAMENTO_COMANDO_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, NAO FECHOU O COMANDO ERRO!\n\n", linha);
            system("PAUSE");
            break;

        case ATRIBUICAO_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, FALTOU SINAL IGUAL NA ATRIBUICAO!\n\n", linha);
            system("PAUSE");
            break;

        case VIRGULA_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, FALTOU A VIRGULA!\n\n", linha);
            system("PAUSE");
            break;

        case PONTO_VIRGULA_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, FALTOU O PONTO E VIRGULA!\n\n", linha);
            system("PAUSE");
            break;

        case ASSINATURA_RETORNO_ERROR:
            printf("\n\nERRO SEMANTICO NA LINHA %d, TIPO DO RETORNO DA ASSINATURA DIFERENTE DO TIPO EM FUNC!\n\n",linha);
            system("PAUSE");
            break;

        case QUANTIDADE_ARGUMENTOS_ERROR:
            printf("\n\nERRO SEMANTICO NA LINHA %d, QUANTIDADE DE ARGUMENTOS EM FUNC OU PROC DIFERENTE DA ASSINATURA!\n\n", linha);
            system("PAUSE");
            break;

        case ARGUMENTO_INVALIDO_ERROR:
            printf("\n\nERRO SEMANTICO NA LINHA %d, TIPO DE ARGUMENTO DIFERENTE DA ASSINATURA!\n\n", linha);
            system("PAUSE");
            break;

        case ID_NAO_ENCONTRADO_ERROR:
            printf("\n\nERRO SEMANTICO NA LINHA %d, NAO POSSUI ASSINATURA!\n\n", linha);
            system("PAUSE");
            break;

        case VAR_NAO_DECLARADA_ERROR:
            printf("\n\nERRO SEMANTICO NA LINHA %d, VARIAVEL NAO FOI DECLARADA!\n\n", linha);
            system("PAUSE");
            break;

        case TIPO_INCOMPATIVEL_ERRO:
            printf("\n\nERRO SEMANTICO NA LINHA %d, TIPOS INCOMPATIVEIS!\n\n", linha);
            system("PAUSE");
            break;

        case RETURN_PROC_ERRO:
            printf("\n\nERRO SEMANTICO NA LINHA %d, RETURN EM PROC NAO PODE TER (EXPR)!\n\n", linha);
            system("PAUSE");
            break;

        case RETURN_FUNC_ERRO:
            printf("\n\nERRO SEMANTICO NA LINHA %d, FUNC NAO PODE TER RETURN PURO!\n\n", linha);
            system("PAUSE");
            break;

        case RETURN_EXPR_ERRO:
            printf("\n\nERRO SEMANTICO NA LINHA %d, TIPO EM RETURN DIFERENTE DO TIPO EM FUNC!\n\n", linha);
            system("PAUSE");
            break;
    }
}

//tipo, ok!
Boolean tipo(){

    if((Token.cat == PR && Token.tipo.codigo == CARACTER)){
        strcpy(tipo_id, "caracter");
        return TRUE;
    }
    if(Token.cat == PR && Token.tipo.codigo ==  INTEIRO){
        strcpy(tipo_id, "inteiro");
        return TRUE;
    }
    if(Token.cat == PR && Token.tipo.codigo ==  REAL){
        strcpy(tipo_id, "real");
        return TRUE;
    }
    if(Token.cat == PR && Token.tipo.codigo == BOOLEANO){
        strcpy(tipo_id, "booleano");
        return TRUE;
    }

    return FALSE;
}

//atrib, ok!
void atrib(){
    if(Token.cat == ID){
        proximo_Token();

        if(Token.cat == SN && Token.tipo.codigo == ATRIBUICAO){
            proximo_Token();

            if(!expr())
                modulo_erros((Erro)EXPR_ERRO);

            veioAtribuicao = 1;

        } else modulo_erros((Erro)ATRIBUICAO_ERRO);
    }
}

void tipos_param(){
Boolean  enquanto_for_virgula = TRUE;

    if(Token.cat == PR && Token.tipo.codigo ==  SEMPARAM){
        proximo_Token();
    }
    else{
        if(tipo()){
            proximo_Token();

            if(Token.cat == ID){
                pesquisar_Tabela_Simbolos(Token.tipo.lexema, 1);                     //MODIFICA��O
                adicionar_Tabela_Simbolos(Token.tipo.lexema, 1, tipo_id, "param");     //MODIFICA��O //revisar se esse param existe na linguagem cmm

                /* tirar duvidas com Felipe em rela��o ao o que � esses deslocamentos .-. */

                proximo_Token();

                while(enquanto_for_virgula){
                    if(Token.cat == SN && Token.tipo.codigo ==  VIRGULA){
                        proximo_Token();

                        if(tipo()){

                            proximo_Token();

                            if(Token.cat == ID){
                                pesquisar_Tabela_Simbolos(Token.tipo.lexema, 1);                     //MODIFICA��O
                                adicionar_Tabela_Simbolos(Token.tipo.lexema, 1, tipo_id, "param");     //MODIFICA��O

                                proximo_Token();
                                enquanto_for_virgula = TRUE;
                            } else
                                modulo_erros((Erro)ID_ERRO);
                        } else
                            modulo_erros((Erro)TIPO_ERRO);
                    }
                    else
                        enquanto_for_virgula = FALSE;
                }
            }
            else{
                modulo_erros((Erro)ID_ERRO);
            }
        }
        else{
            modulo_erros((Erro)TIPO_ERRO);
        }
    }
}

void tipos_p_opc(){
    Boolean  enquanto_for_virgula = TRUE;

    if(Token.cat == PR && Token.tipo.codigo == SEMPARAM){
        proximo_Token();
    }
    else{
        if(tipo()){
            proximo_Token();

            if(Token.cat == ID) {
                proximo_Token();
            }
                pesquisar_Tabela_Simbolos(Token.tipo.lexema, 1);                     //MODIFICA��O
                adicionar_Tabela_Simbolos(Token.tipo.lexema, 1, tipo_id, "param");     //MODIFICA��O //revisar se esse param existe na linguagem cmm

                while(enquanto_for_virgula){
                    if(Token.cat == SN && Token.tipo.codigo == VIRGULA ){
                        proximo_Token();

                        if(tipo()){

                            proximo_Token();

                            if(Token.cat == ID){
                                proximo_Token();
                                enquanto_for_virgula = TRUE;
                            }
                        } else
                            modulo_erros((Erro)TIPO_ERRO);
                    }
                    else
                        enquanto_for_virgula = FALSE;
                }
            }
        else{
            modulo_erros((Erro)TIPO_ERRO);
        }
    }
}

void cmd(){
    int tipo_de_comando = 0;
    Boolean enquanto_for_virgula = TRUE;
    char id_[15];

    if(Token.cat == ID && TNext.cat == SN && TNext.tipo.codigo == ATRIBUICAO){
        atrib();
        if(Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA)
            proximo_Token();
        else
            modulo_erros((Erro)PONTO_VIRGULA_ERRO);
        enquanto_for_comando = 1;

    }


    else if(Token.cat == ID){
            proximo_Token();

        if(Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE){
            proximo_Token();

            if(expr()){
                while(enquanto_for_virgula){
                    if(Token.cat == SN && Token.tipo.codigo == VIRGULA){
                        proximo_Token();

                        if(expr()){
                            enquanto_for_virgula = TRUE;
                            proximo_Token();
                        }
                        else
                            modulo_erros((Erro)EXPRESSAO_ERRO);
                    }
                    else
                        enquanto_for_virgula = FALSE;
                }
            }

            //Verifica se fechou o parentese
            if(Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
                proximo_Token();
            else
                modulo_erros((Erro)FECHAMENTO_PARENTESE_ERRO);

        }
        else
            modulo_erros((Erro)ABERTURA_PARENTESE_ERRO);

        enquanto_for_comando = 1;

    } else {

//        if(TNext.cat == SN && TNext.tipo.codigo == ATRIBUICAO)
//            proximo_Token();

        switch(Token.tipo.codigo){
            //Se
            case SE:
                proximo_Token();
                if(Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE ){
                    proximo_Token();

                    if(!expr())
                        modulo_erros((Erro)EXPR_ERRO);

                    //Verifica se fechou o parentese
                    if(Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
                        proximo_Token();
                    else
                        modulo_erros((Erro)FECHAMENTO_PARENTESE_ERRO);
                }
                else
                    modulo_erros((Erro)ABERTURA_PARENTESE_ERRO);

                cmd();

                if(Token.cat == PR && Token.tipo.codigo == SENAO){
                    proximo_Token();
                    cmd();
                }

                enquanto_for_comando = 1;
                break;


            //enquanto
            case ENQUANTO:
                proximo_Token();

                if(Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE){
                    proximo_Token();

                    if(!expr())
                        modulo_erros((Erro)EXPR_ERRO);

                    //Verifica se fechou o parentese
                    if(Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
                        proximo_Token();
                    else
                        modulo_erros((Erro)FECHAMENTO_PARENTESE_ERRO);

                } else
                    modulo_erros((Erro)ABERTURA_PARENTESE_ERRO);

                cmd();

                enquanto_for_comando = 1;
                break;

            //para
            case PARA:
                proximo_Token();

                if(Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE){
                    proximo_Token();
                    atrib();

                    if(Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA){
                        proximo_Token();
                        expr();

                        if(Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA){
                            proximo_Token();
                            atrib();

                            //Verifica se fechou o parentese
                            if(Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
                                proximo_Token();
                            else
                                modulo_erros((Erro)FECHAMENTO_PARENTESE_ERRO);
                        } else
                            modulo_erros((Erro)VIRGULA_ERRO);
                    } else
                        modulo_erros((Erro)VIRGULA_ERRO);
                } else
                    modulo_erros((Erro)ABERTURA_PARENTESE_ERRO);

                cmd();
                enquanto_for_comando = 1;
            break;

            //retorne
            case RETORNE:   //Ver a quest�o do permitir por cadeia vazia e fazer a quest�o do ponto e virgula
                proximo_Token();

                expr();

                if(!(Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA))
                    modulo_erros((Erro)PONTO_VIRGULA_ERRO);

                enquanto_for_comando = 1;
                proximo_Token();
            break;

            case ABRE_CHAVES:
                proximo_Token();
                cmd();

                if(!(Token.cat == SN && Token.tipo.codigo == FECHA_CHAVES)){
                    modulo_erros((Erro)FECHAMENTO_COMANDO_ERRO);
                }
                //PONTO E V�RGULA
            case PONTO_VIRGULA:
                enquanto_for_comando = 1;
            break;

            default:
                enquanto_for_comando = 0;
            break;
        }
    }
}

//termo, ok!
Boolean termo(){
    if(fator()){
        while((Token.cat == SN && Token.tipo.codigo == MULTIPLICACAO) || (Token.cat == SN && Token.tipo.codigo == DIVISAO) || (Token.cat == SN && Token.tipo.codigo == AND)){
            proximo_Token();

            if(fator())
                proximo_Token();
            else
                modulo_erros((Erro)FATOR_ERRO);
        }
        return TRUE;
    }
    return FALSE;
}

//expr_simp, ok!
Boolean expr_simp(){
    if((Token.cat == SN && Token.tipo.codigo == SOMA) || (Token.cat == SN && Token.tipo.codigo == SUBTRACAO))
        proximo_Token();

    if(termo()){
        while((Token.cat == SN && Token.tipo.codigo == SOMA) || (Token.cat == SN && Token.tipo.codigo == SUBTRACAO) || Token.cat == SN && Token.tipo.codigo == OR){
            proximo_Token();

            if(!termo())
                modulo_erros((Erro)TERMO_ERRO);
        }
        return TRUE;
    }
    return FALSE;
}


//expr, ok!
Boolean expr(){
    if(expr_simp()){
        if(!(Token.cat == SN /*&& Token.tipo.codigo == PONTO_VIRGULA*/))
            proximo_Token();

        if(op_rel()){
            proximo_Token();
            if(!expr_simp())
                modulo_erros((Erro)EXPR_SIMP_ERRO);
        }
        return TRUE;
    }
    return FALSE;
}


//Talvez revisar com Felipe, mas por enquanto t� ok
Boolean fator(){

    Boolean enquanto_for_virgula = TRUE;
    char id_[50], id_func[50];

    //FATOR IDS
    if(Token.cat == ID) {
        strcpy(id_,Token.tipo.lexema);

        proximo_Token();

        //FATOR ID([expr {',' expr}])
        if(Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE){

            strcpy(id_func,Token.tipo.lexema);

            proximo_Token();

            if(expr()){
                while(Token.cat == SN && Token.tipo.codigo == VIRGULA){
                        proximo_Token();

                        if(!expr())
                            modulo_erros((Erro)EXPRESSAO_ERRO);

                }
            }

            //Verifica se fechou o parentese
            if(Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
                proximo_Token();
            else
                modulo_erros((Erro)FECHAMENTO_PARENTESE_ERRO);
            return TRUE;
        }

        //pesquisar_tipo(Token.tipo.lexema);
        // valor_deslocamento = retorna_deslocamento(lookAhead.palavra);
        /* Verificar essas duas partes posteriormente, pois a fun��o
        pesquisa tipo por exemplo j� utiliza a tabela de simbolos e essa variavel de deslocamento
        eu n�o sei para que serve*/

        //if(!sinal_prog) pesquisar_Declaracao(id_, 0);
        //else pesquisar_Declaracao(id_, 1);
        /* Mesma coisa do caso acima*/

        return TRUE;
    }

    //FATOR (expr)
    if(Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE){
        veioExpressao = 1;
        proximo_Token();
        expr();
        if(veioExpressao)
            proximo_Token();
        else
            modulo_erros((Erro)EXPRESSAO_ERRO);

        //Verifica se fechou o parentese
        if(Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
            proximo_Token();
        else
            modulo_erros((Erro)FECHAMENTO_PARENTESE_ERRO);

        return TRUE;
    }

    //FATOR "!" nega��o fator
    if(Token.cat == SN && Token.tipo.codigo == NOT){
        veioExpressao = 1;
        proximo_Token();
        if(fator())
            proximo_Token();
        else
            modulo_erros((Erro)FATOR_ERRO);

        return TRUE;
    }

    //FATOR intcon
    if(Token.cat == CT_I){
        veioExpressao = 1;

        proximo_Token();
        strcpy(tipo_dado, "inteiro");

        return TRUE;
    }

    //FATOR realcon
    if(Token.cat == CT_R){
        veioExpressao = 1;

        proximo_Token();
        strcpy(tipo_dado, "real");

        return TRUE;
    }

    //FATOR caraccon
    if(Token.cat == CT_C){
        veioExpressao = 1;
        proximo_Token();
        strcpy(tipo_dado, "caracter");

        return TRUE;
    }

    //Se n�o veio fator
    veioExpressao = 0;
    return FALSE;

}

//op_rel, ok!
Boolean op_rel(){

    if(Token.cat == SN && Token.tipo.codigo == IGUAL){
       tipoRelacional = Token.tipo.codigo; //Numeros aleatorios para ajudar na compra��o posteriormente
       return TRUE;
    }

    if(Token.cat == SN && Token.tipo.codigo == DIFERENTE){
       tipoRelacional = Token.tipo.codigo;  //Numeros aleatorios para ajudar na compra��o posteriormente
       return TRUE;
    }

    if(Token.cat == SN && Token.tipo.codigo == MENORIGUAL){
       tipoRelacional = Token.tipo.codigo;  //Numeros aleatorios para ajudar na compra��o posteriormente
       return TRUE;
    }

    if(Token.cat == SN && Token.tipo.codigo == MAIORIGUAL){
       tipoRelacional = Token.tipo.codigo;  //Numeros aleatorios para ajudar na compra��o posteriormente
       return TRUE;
    }

    if(Token.cat == SN && Token.tipo.codigo == MENOR){
       tipoRelacional = Token.tipo.codigo;  //Numeros aleatorios para ajudar na compra��o posteriormente
       return TRUE;
    }

    if(Token.cat == SN && Token.tipo.codigo == MAIOR){
       tipoRelacional = Token.tipo.codigo;  //Numeros aleatorios para ajudar na compra��o posteriormente
       return TRUE;
    }

    return FALSE;
}


/* A partir daqui s�o as fun��es auxiliares para fazer
O compilador funcionar por completo. */


// TODO: Codigos da tabela de simbolos.
void adicionar_Tabela_Simbolos(char id_[], int escopo_, char tipo_[], char cat_[])
{
  strcpy(tabela_Simbolos[posicao_atual].id, id_);
  tabela_Simbolos[posicao_atual].escopo=escopo_;
  strcpy(tabela_Simbolos[posicao_atual].tipo,  tipo_);
  strcpy(tabela_Simbolos[posicao_atual].cat,  cat_);
  tabela_Simbolos[posicao_atual].param_excluido=0;

  posicao_atual++;
}

//TODO: pesquisar_Tabela_Simbolos
void pesquisar_Tabela_Simbolos(char id_[], int escopo_recebido)
{
   int x;

   for(x=posicao_fixa;x<posicao_atual;x++)
   {
       if(!strcmp(tabela_Simbolos[x].id, id_) && tabela_Simbolos[x].param_excluido != 1)
       {
       	   if(tabela_Simbolos[x].escopo == escopo_recebido)
	       {
	       	     if(escopo_recebido==1) {

					  printf("\nERRO VARIAVEL REDECLARADA EM ESCOPO LOCAL\n\n");
					  system("PAUSE");
			  	  }
			  	 else
			  	 {
			  	        if(escopo_recebido==0){
					 	   printf("\nERRO NOME REDECLARADO EM ESCOPO GLOBAL\n\n");
					       system("PAUSE");
					    }
				        else
				        {
				           printf("\nERRO NOME DE ASSINATURA REDECLARADA EM ESCOPO GLOBAL\n\n");
					       system("PAUSE");
						}

				 }

		   }

	   }

   }

}

//TODO: excluir_Tabela_Simbolos
void excluir_Tabela_Simbolos()
{
  int x;

     for(x=posicao_fixa;x<posicao_atual;x++)
     {
          if(tabela_Simbolos[x].escopo == 1)
          {
              tabela_Simbolos[x].param_excluido=1;
          }
     }

}

//TODO: fazer listar_Tabela_Simbolos
void listar_Tabela_Simbolos()
{
	int x;

     for(x=posicao_fixa;x<posicao_atual;x++)
     {
     	puts(tabela_Simbolos[x].id);
	 }
}


void prog() {
    while (Token.cat != END){

    proximo_Token();
    Boolean eh_semretorno = FALSE;

    if (Token.cat == PR && Token.tipo.codigo == SEMRETORNO) {
        eh_semretorno = TRUE;
    }

    if (Token.cat == PR && Token.tipo.codigo == PROTOTIPO) {

        proximo_Token();

        if (Token.cat == PR && Token.tipo.codigo == SEMRETORNO) {
            eh_semretorno = TRUE;
        }

        if (tipo() || eh_semretorno) {
            proximo_Token();

            if (Token.cat == ID) {
            strcpy(nome_func, Token.tipo.lexema);

            //colocar as fun��es da tabela de simbolos depois
            pesquisar_Tabela_Simbolos(Token.tipo.lexema, 0);                     //MODIFICA��O
            adicionar_Tabela_Simbolos(Token.tipo.lexema, 0, tipo_id, "func");     //MODIFICA��O

                proximo_Token();

                if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {
                    proximo_Token();

                    tipos_p_opc();

                    if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE) {
                        proximo_Token();

                        while ((Token.cat == SN && Token.tipo.codigo == VIRGULA)) {

                            proximo_Token();

                            if (Token.cat == ID) {
                                proximo_Token();

                                if ((Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE)) {
                                    proximo_Token();

                                    tipos_p_opc();

                                    if (!(Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)) {
                                        modulo_erros((Erro) FECHAMENTO_PARENTESE_ERRO);
                                    }

                                } else {
                                    modulo_erros((Erro) ABERTURA_PARENTESE_ERRO);
                                }

                                                pesquisar_Tabela_Simbolos(Token.tipo.lexema, 1);                     //MODIFICA��O
                                                adicionar_Tabela_Simbolos(Token.tipo.lexema, 1, tipo_id, "var");     //MODIFICA��O
                                eparam = 0;
                                proximo_Token();
                            } else {
                                modulo_erros((Erro) ID_ERRO);
                            }

                        }

                        if (!(Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA)) {
                            modulo_erros((Erro) PONTO_VIRGULA_ERRO);
                        }
                    } else {
                        modulo_erros((Erro) FECHAMENTO_PARENTESE_ERRO);
                    }
                }


            } else {
                modulo_erros((Erro) ID_ERRO);
            }
        } else {
            modulo_erros((Erro) TIPO_ERRO);
        }
    } else if (tipo() || eh_semretorno) {
        proximo_Token();

        if (Token.cat == ID) {
            strcpy(nome_func, Token.tipo.lexema);
//
//            //colocar as fun��es da tabela de simbolos depois
            pesquisar_Tabela_Simbolos(Token.tipo.lexema, 0);                     //MODIFICA��O
            adicionar_Tabela_Simbolos(Token.tipo.lexema, 0, tipo_id, "func");     //MODIFICA��O

            proximo_Token();

            if ((Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE)) {
                proximo_Token();

                tipos_param();

                if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE) {
                    proximo_Token();

                    if (Token.cat == SN && Token.tipo.codigo == ABRE_CHAVES) {
                        proximo_Token();

                        while (tipo()) {

                            proximo_Token();

                            if (Token.cat == ID) {
                                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, 1);                     //MODIFICA��O
                                    adicionar_Tabela_Simbolos(Token.tipo.lexema, 1, tipo_id, "var");     //MODIFICA��O //verificar se o nome � var mesmo
                                eparam = 0;

                                proximo_Token();

                                while ((Token.cat == SN && Token.tipo.codigo == VIRGULA)) {

                                    proximo_Token();

                                    if (Token.cat == ID) {
                                                pesquisar_Tabela_Simbolos(Token.tipo.lexema, 1);                     //MODIFICA��O
                                                adicionar_Tabela_Simbolos(Token.tipo.lexema, 1, tipo_id, "var");     //MODIFICA��O
                                        eparam = 0;
                                        proximo_Token();
                                    } else {
                                        modulo_erros((Erro) ID_ERRO);
                                    }

                                }

                                if (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA)
                                    proximo_Token();
                                else
                                    modulo_erros((Erro) PONTO_VIRGULA_ERRO);
                            } else {
                                modulo_erros((Erro) ID_ERRO);
                            }
                        }

                        enquanto_for_comando = 1;
                        while (enquanto_for_comando) {
                            cmd();
                        }

                        if (!(Token.cat == SN && Token.tipo.codigo == FECHA_CHAVES)) {
                            modulo_erros((Erro) FECHAMENTO_CHAVES_ERRO);
                        }

                    } else {
                        modulo_erros((Erro) ABERTURA_CHAVES_ERRO);
                    }

                } else {
                    modulo_erros((Erro) FECHAMENTO_PARENTESE_ERRO);
                }
            } else if (eh_semretorno) {
                modulo_erros((Erro) ABERTURA_PARENTESE_ERRO);
            } else if (Token.tipo.codigo == VIRGULA) {
                while (Token.tipo.codigo == VIRGULA) {
                    proximo_Token();
                    if (Token.cat != ID) {
                        modulo_erros((Erro) ID_ERRO);
                    }
                    proximo_Token();
                }

            } else if (Token.tipo.codigo == PONTO_VIRGULA) {}
            else {
                modulo_erros((Erro) PONTO_VIRGULA_ERRO);
            }
        } else {
            modulo_erros((Erro) ID_ERRO);
        }
    }

    excluir_Tabela_Simbolos();

    }
}


