#include "AnaSint.h"

int enquanto_for_comando = 1;
int tipo_proc=0; //Variavel que indica se é um procedimento ou funcão.
estrutura_fp assinatura_atual; //Assinatura das funções e procedimentos, utilizado para analise semântica
int posicao_parametros=0; //Variavel que indica a posição atual do parametro na assinatura da função
int contagem_parametros=0; //Variavel que indica a quantidade de parametros de uma assinatura de uma função ou procedimento

int contagem_parametros_mp = 0; //Variavel que indica a quantidade de parametros para maquina de pilha.

int proc_=0, func_=0; //Variaveis que indica se é procedimento ou função, para da erro semântico no retorno.

//Analisar a condição dessas variaveis, são utilizadas na analise semântica e na tabela de simbolos
int  posicao_fixa=0;
int  posicao_atual=0;
int result;

//Variaveis usadas para geração de código.
int label = 0, num_label;
int num_var = 0; //Contagem de número de variaveis usadas ao logo do programa
int tipo_relacional;
int num_label_goto = 0; //Variavel para armazenar o número da label do GOTO, para colocar no rotulo depois que ele temrina as funções (RET)
int num_label_gotrue = 0;
int num_label_gofalse=0;
void proximo_Token() {
    Token = TNext;
    if (Token.cat != END)
        analexico();
}

void modulo_erros(Erro tipo_erro) {
    switch (tipo_erro) {
        case ID_ERRO:
            printf("\n\nERRO SINTATICO NA LINHA %d, ESPERADO IDENTIFICADOR!\n\n", linha);
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
            printf("\n\nERRO SEMANTICO NA LINHA %d, TIPO DO RETORNO DA ASSINATURA DIFERENTE DO TIPO EM FUNC!\n\n", linha);
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

        case PRINCIPAL_ERROR:
            printf("\n\nERRO SEMANTICO, O PROGRAMA NAO POSSUI UMA FUNCAO PRINCIPAL!\n\n", linha);
            system("PAUSE");
            break;
    }
}

Boolean tipo() {

    if ((Token.cat == PR && Token.tipo.codigo == CARACTER)) {
    	strcpy(tipo_id, "caracter");
        return TRUE;
    }
    if (Token.cat == PR && Token.tipo.codigo == INTEIRO) {
    	strcpy(tipo_id, "inteiro");
        return TRUE;
    }
    if (Token.cat == PR && Token.tipo.codigo == REAL) {
    	strcpy(tipo_id, "real");
        return TRUE;
    }
    if (Token.cat == PR && Token.tipo.codigo == BOOLEANO) {
        strcpy(tipo_id, "booleano");
		return TRUE;
    }

    return FALSE;
}

void atrib() {
	char id_[50];
	int enderecoRelativo5;

	strcpy(id_, Token.tipo.lexema);

	if (Token.cat == ID) {
        declarado_na_tabela_simbolos(Token.tipo.lexema);
        result = pesquisar_Tipo(Token.tipo.lexema, VARIAVEL);

		proximo_Token();

        if (Token.cat == SN && Token.tipo.codigo == ATRIBUICAO) {
            proximo_Token();

			if (!expr())
                modulo_erros((Erro) EXPR_ERRO);

            enderecoRelativo5 = retorna_endereco_relativo(id_);
            if(retorna_escopo(id_) == GLOBAL){
				fprintf(arquivo_gerador,"STOR %d,%d\n",0,enderecoRelativo5);
			}else {
				fprintf(arquivo_gerador,"STOR %d,%d\n",1,enderecoRelativo5);
			}

        } else modulo_erros((Erro) ATRIBUICAO_ERRO);
    }
}

void tipos_param() {
    Boolean enquanto_for_virgula = TRUE;
	int id1Endereco; //Saber o primeiro id que foi declarado que foi o ultimo com -3

    if (Token.cat == PR && Token.tipo.codigo == SEMPARAM) {
        strcpy(assinatura_atual.parametros[0],""); //Coloando o nome do parametro na estrutura
        proximo_Token();

    } else {
        if (tipo()) {
            strcpy(assinatura_atual.parametros[posicao_parametros],tipo_id);
            adicionar_Tipos_Param(posicao_parametros, tipo_id, assinatura_atual.id);
            posicao_parametros++;
            contagem_parametros++;

            proximo_Token();

            if (Token.cat == ID) {
                pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);
                adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, LOCAL, PARAMETRO);

                proximo_Token();

                while (enquanto_for_virgula) {
                    if (Token.cat == SN && Token.tipo.codigo == VIRGULA) {
                        proximo_Token();

                        if (tipo()) {
                            strcpy(assinatura_atual.parametros[posicao_parametros],tipo_id);
                            adicionar_Tipos_Param(posicao_parametros, tipo_id, assinatura_atual.id);
                            posicao_parametros++;
                            contagem_parametros++;

                            proximo_Token();

                            if (Token.cat == ID) {
                                pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);
                                adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, LOCAL, PARAMETRO);

                                proximo_Token();
                                enquanto_for_virgula = TRUE;
                            } else
                                modulo_erros((Erro) ID_ERRO);
                        } else
                            modulo_erros((Erro) TIPO_ERRO);
                    } else
                        enquanto_for_virgula = FALSE;
                }
            } else {
                modulo_erros((Erro) ID_ERRO);
            }
        } else {
            modulo_erros((Erro) TIPO_ERRO);
        }
    }
posicao_parametros=0;


if(!tipo_proc) pesquisar_assinatura(assinatura_atual.tipo,assinatura_atual.id,assinatura_atual.parametros,1,contagem_parametros);
else {pesquisar_assinatura(assinatura_atual.tipo,assinatura_atual.id,assinatura_atual.parametros,0,contagem_parametros);}
adicionar_qtd_param(contagem_parametros, assinatura_atual.id);

addEnderecoRelativoParametros(assinatura_atual.id, LOCAL, PARAMETRO, contagem_parametros);

contagem_parametros_mp = contagem_parametros;

contagem_parametros=0;
}

//Colocar erro em semparam?? Verificar a gramática com Felipe.
void tipos_p_opc() {

    if (Token.cat == PR && Token.tipo.codigo == SEMPARAM) {
        strcpy(assinatura_atual.parametros[0],Token.tipo.lexema);
		proximo_Token();
    } else {
        if (tipo()) {
        	//strcpy(assinatura_atual.parametros[posicao_parametros],Token.tipo.lexema);
			adicionar_Tipos_Param(posicao_parametros, tipo_id, assinatura_atual.id);
			posicao_parametros++;
			contagem_parametros++;

            proximo_Token();

            if (Token.cat == ID) {
                pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);
                adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, LOCAL, PARAMETRO);

                proximo_Token();
            }

            while (Token.cat == SN && Token.tipo.codigo == VIRGULA) {
                if (Token.cat == SN && Token.tipo.codigo == VIRGULA) {
                    proximo_Token();

                    if (tipo()) {
					    adicionar_Tipos_Param(posicao_parametros, tipo_id, assinatura_atual.id);
						posicao_parametros++;
					    contagem_parametros++;

                        proximo_Token();

                        if (Token.cat == ID) {
                            pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);
                            adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, LOCAL, PARAMETRO);

                            proximo_Token();
                        }

                    } else
                        modulo_erros((Erro) TIPO_ERRO);
                } else {
                    modulo_erros((Erro) VIRGULA_ERRO);
                }
            }
            if ((Token.cat == SN && Token.tipo.codigo == VIRGULA))
                modulo_erros((Erro) TIPO_ERRO);
            else if (tipo())
                modulo_erros((Erro) VIRGULA_ERRO);

            adicionar_qtd_param(contagem_parametros, assinatura_atual.id);
            contagem_parametros=0;
        } else {
            modulo_erros((Erro) TIPO_ERRO);
        }
    }
posicao_parametros=0;
//if(!tipo_proc) pesquisar_assinatura(assinatura_atual.tipo,assinatura_atual.id,assinatura_atual.parametros,1,contagem_parametros);
//else {pesquisar_assinatura(assinatura_atual.tipo,assinatura_atual.id,assinatura_atual.parametros,0,contagem_parametros);}

}

void cmd() {
    Boolean enquanto_for_virgula = TRUE;
    char id_[15], id_declaracao[15];  //Analise semântica
    char controle_fluxo[8]; //geração de códugo.

    if (Token.cat == ID && TNext.cat == SN && TNext.tipo.codigo == ATRIBUICAO) {
        atrib();
        if (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA)
            proximo_Token();
        else
            modulo_erros((Erro) PONTO_VIRGULA_ERRO);
        enquanto_for_comando = 1;

    } else if (Token.cat == ID) {
        declarado_na_tabela_simbolos(Token.tipo.lexema);
        proximo_Token();

        if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {
            proximo_Token();

            if (expr()) {
                while (enquanto_for_virgula) {
                    if (Token.cat == SN && Token.tipo.codigo == VIRGULA) {
                        proximo_Token();

                        if (expr()) {
                            enquanto_for_virgula = TRUE;
//                            proximo_Token();
                        } else
                            modulo_erros((Erro) EXPRESSAO_ERRO);
                    } else
                        enquanto_for_virgula = FALSE;
                }
            }

            //Verifica se fechou o parentese
            if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
                proximo_Token();
            else
                modulo_erros((Erro) FECHAMENTO_PARENTESE_ERRO);

            if (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA)
                proximo_Token();
            else
                modulo_erros((Erro) PONTO_VIRGULA_ERRO);

        } else
            modulo_erros((Erro) ABERTURA_PARENTESE_ERRO);

        enquanto_for_comando = 1;

    } else {

        switch (Token.tipo.codigo) {
            //Se
            case SE:
                proximo_Token();
                if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {
                    proximo_Token();

                    if (!expr())
                        modulo_erros((Erro) EXPR_ERRO);

                    //Verifica se fechou o parentese
                    if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
                        proximo_Token();
                    else
                        modulo_erros((Erro) FECHAMENTO_PARENTESE_ERRO);
                } else
                    modulo_erros((Erro) ABERTURA_PARENTESE_ERRO);

                //GERA CÓDIGO
				strcpy(controle_fluxo, "GOFALSE ");
	            gera_Label(controle_fluxo);

                cmd();

                strcpy(nome_label, "LABEL ");
	            gera_Label(nome_label);

                if (Token.cat == PR && Token.tipo.codigo == SENAO) {
                	//GERA CÓDIGO
					strcpy(controle_fluxo, "GOTO ");
	                gera_Label(controle_fluxo);
					strcpy(nome_label, "LABEL ");
	                gera_Label(nome_label);

                    proximo_Token();
                    cmd();

                    strcpy(nome_label, "LABEL ");
	                gera_Label(nome_label);
                }

                enquanto_for_comando = 1;
                break;


            case ENQUANTO:
                proximo_Token();

                if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {
                    proximo_Token();

                    //GERA CÓDIGO
					strcpy(nome_label, "LABEL ");
	                gera_Label(nome_label);

                    if (!expr())
                        modulo_erros((Erro) EXPR_ERRO);

                    //Verifica se fechou o parentese
                    if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
                        proximo_Token();
                    else
                        modulo_erros((Erro) FECHAMENTO_PARENTESE_ERRO);

                } else
                    modulo_erros((Erro) ABERTURA_PARENTESE_ERRO);

                //GERA CÓDIGO
				strcpy(controle_fluxo, "GOFALSE ");
	            gera_Label(controle_fluxo);

                cmd();

				//GERA CÓDIGO
				strcpy(controle_fluxo, "GOTO ");
	            gera_Label(controle_fluxo);
	            strcpy(nome_label, "LABEL ");
	            gera_Label(nome_label);

                enquanto_for_comando = 1;
                break;

                //para
            case PARA:
                proximo_Token();

                if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {
                    proximo_Token();
                    atrib();

					//GERA CÓDIGO
					strcpy(nome_label, "LABEL ");
	                gera_Label(nome_label);

                    if (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA) {
                        proximo_Token();
                        expr();

                        //GERA CÓDIGO
						strcpy(controle_fluxo, "GOFALSE ");
	           			gera_Label(controle_fluxo);

                        //GERA CÓDIGO
						strcpy(controle_fluxo, "GOTO ");
	                    gera_Label(controle_fluxo);
						strcpy(nome_label, "LABEL ");
	                    gera_Label(nome_label);

                        if (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA) {
                            proximo_Token();
                            atrib();

                            //GERA CÓDIGO
							strcpy(controle_fluxo, "GOTO ");
	                        gera_Label(controle_fluxo);
	                        strcpy(nome_label, "LABEL ");
	                        gera_Label(nome_label);

                            //Verifica se fechou o parentese
                            if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
                                proximo_Token();
                            else
                                modulo_erros((Erro) FECHAMENTO_PARENTESE_ERRO);
                        } else
                            modulo_erros((Erro) VIRGULA_ERRO);
                    } else
                        modulo_erros((Erro) VIRGULA_ERRO);
                } else
                    modulo_erros((Erro) ABERTURA_PARENTESE_ERRO);

                cmd();

                //GERA CÓDIGO
				strcpy(controle_fluxo, "GOTO ");
	            gera_Label(controle_fluxo);
				strcpy(nome_label, "LABEL ");
	            gera_Label(nome_label);

                enquanto_for_comando = 1;
                break;

                //retorne
            case RETORNE:   //Ver a quest?o do permitir por cadeia vazia e fazer a quest?o do ponto e virgula
                proximo_Token();
				strcpy(id_declaracao, Token.tipo.lexema);  //Está copiando o id, para depois achar o tipo de retorno.

                if(expr()){
                	if(proc_)
						modulo_erros((Erro)RETURN_PROC_ERRO);
                }else {
					if(func_)
						modulo_erros((Erro)RETURN_FUNC_ERRO);
                    else strcpy(tipo_retorno, "");

				}

				verificar_retorno_expr(nome_func, tipo_retorno, id_declaracao);

				fprintf(arquivo_gerador,"STOR %d,%d\n", 1, -3 -contagem_parametros_mp);
				fprintf(arquivo_gerador,"RET %d,%d\n", 1,contagem_parametros_mp);
				
				//Gera código Label (Goto Lx, Label lx)
				strcpy(nome_label, "LABEL ");
				sprintf(label_num_s, "%i", num_label_goto);
				strcpy(label_letra, "L");
				strcat(label_letra, label_num_s);
				strcat(nome_label, label_letra);
				strcat(nome_label, "\n");
				fprintf(arquivo_gerador,nome_label);

                if (!(Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA))
                    modulo_erros((Erro) PONTO_VIRGULA_ERRO);

				func_=0;
				proc_=0;

                enquanto_for_comando = 1;
                proximo_Token();
                break;

            case ABRE_CHAVES:
                proximo_Token();

                while(enquanto_for_comando) {
                    cmd();
                }

                 //GERA CÓDIGO (Verificar se este gerar código está correto)
				strcpy(controle_fluxo, "GOTO ");
	            gera_Label(controle_fluxo);
				strcpy(nome_label, "LABEL ");
	            gera_Label(nome_label);

                if (!(Token.cat == SN && Token.tipo.codigo == FECHA_CHAVES)) {
                    modulo_erros((Erro) FECHAMENTO_CHAVES_ERRO);
                }

            case PONTO_VIRGULA:
                enquanto_for_comando = 1;
                proximo_Token();
                break;

            default:
                enquanto_for_comando = 0;
                break;
        }
    }
}

Boolean termo() {
    int mult, div;
    char controle_fluxo[8];
    int ee = FALSE;

	if (fator()) {

		if(Token.cat == SN && Token.tipo.codigo == MULTIPLICACAO){
    		mult = TRUE;
    		div = FALSE;
    	}
    	if(Token.cat == SN && Token.tipo.codigo == DIVISAO){
    		div = TRUE;
    		mult = FALSE;
    	}

        while ((Token.cat == SN && Token.tipo.codigo == MULTIPLICACAO) ||
               (Token.cat == SN && Token.tipo.codigo == DIVISAO) || (Token.cat == SN && Token.tipo.codigo == AND)) {


		   if(Token.cat == SN && Token.tipo.codigo == AND){
            	//Gera Código
				fprintf(arquivo_gerador,"COPY\n");
   				if(!ee){
   					strcpy(controle_fluxo, "GOFALSE ");
   					gera_Label(controle_fluxo);
   					num_label_gofalse = num_label;
				}else{
					strcpy(nome_label, "GOFALSE ");
   					sprintf(label_num_s, "%i", num_label_gofalse);
  					strcpy(label_letra, "L");
  					strcat(label_letra, label_num_s);
  					strcat(nome_label, label_letra);
  					strcat(nome_label, "\n");
  					fprintf(arquivo_gerador,nome_label);
				}
   				fprintf(arquivo_gerador,"POP\n");

   				mult = FALSE;
   				div = FALSE;
   				ee = TRUE;
			}
		
		    proximo_Token();

            if (!fator())
                modulo_erros((Erro) FATOR_ERRO);
                
            strcpy(tipo_dado_2, tipo_dado); //Consertar problema no return

            //GERA CÓDIGO	 //Instrução aritimetica simples
			if(mult){
				if(!strcmp(tipo_dado, "real")){
					fprintf(arquivo_gerador,"MULTF\n");
				}else{
					fprintf(arquivo_gerador,"MULT\n");
				}
			}

			if(div){
				if(!strcmp(tipo_dado, "real")){
					fprintf(arquivo_gerador,"DIVF\n");
				}else {
					fprintf(arquivo_gerador,"DIV\n");
				}
			}

        }
        
        if(ee){
			strcpy(nome_label, "LABEL ");
			sprintf(label_num_s, "%i", num_label_gofalse);
  			strcpy(label_letra, "L");
  			strcat(label_letra, label_num_s);
  			strcat(nome_label, label_letra);
  			strcat(nome_label, "\n");
  			fprintf(arquivo_gerador,nome_label);
		
		}
		
        return TRUE;
    }
    return FALSE;
}

Boolean expr_simp() {
    int add, sub; //Variaveis usadas para indicar se é soma ou subtração.
    int ou = FALSE;
	char controle_fluxo[8];

	if ((Token.cat == SN && Token.tipo.codigo == SOMA) || (Token.cat == SN && Token.tipo.codigo == SUBTRACAO))
        proximo_Token();

    if (termo()) {

		if(Token.cat == SN && Token.tipo.codigo == SOMA){
    		add = TRUE;
    		sub = FALSE;
    	}

    	if(Token.cat == SN && Token.tipo.codigo == SUBTRACAO){
    		sub = TRUE;
    		add = FALSE;
    	}

        while ((Token.cat == SN && Token.tipo.codigo == SOMA) || (Token.cat == SN && Token.tipo.codigo == SUBTRACAO) ||
               Token.cat == SN && Token.tipo.codigo == OR) {

            if(Token.cat == SN && Token.tipo.codigo == OR){
            	//Gera Código
				fprintf(arquivo_gerador,"COPY\n");
   				strcpy(controle_fluxo, "GOTRUE ");
   				
   				if(!ou){
   					gera_Label(controle_fluxo);
   					num_label_gotrue = num_label;
				}else{
					strcpy(nome_label, "GOTRUE ");
   					sprintf(label_num_s, "%i", num_label_gotrue);
  					strcpy(label_letra, "L");
  					strcat(label_letra, label_num_s);
  					strcat(nome_label, label_letra);
  					strcat(nome_label, "\n");
  					fprintf(arquivo_gerador,nome_label);
				}
				
   				fprintf(arquivo_gerador,"POP\n");

   				add = FALSE;
   				sub = FALSE;
   				ou = TRUE;
			}
			
			proximo_Token();

            if (!termo())
                modulo_erros((Erro) TERMO_ERRO);

			//strcpy(tipo_dado_2, tipo_dado); //Consertar problema no return
			
			//GERA CÓDIGO	 //Instrução aritimetica simples
			if(add){
				if(!strcmp(tipo_dado, "real")){
					fprintf(arquivo_gerador,"ADDF\n");
				}
				else{
					fprintf(arquivo_gerador,"ADD\n");
				}
			}

			if(sub){
				if(!strcmp(tipo_dado, "real")){
					fprintf(arquivo_gerador,"SUBF\n");
				}else{
					fprintf(arquivo_gerador,"SUB\n");
				}
			}

        }
        
        if(ou){
			strcpy(nome_label, "LABEL ");
			sprintf(label_num_s, "%i", num_label_gotrue);
  			strcpy(label_letra, "L");
  			strcat(label_letra, label_num_s);
  			strcat(nome_label, label_letra);
  			strcat(nome_label, "\n");
  			fprintf(arquivo_gerador,nome_label);
		
		}
        return TRUE;
    }
    return FALSE;
}

Boolean expr() {
    if (expr_simp()) {
            strcpy(tipo_dado_1,tipo_dado);

        //Analise semântica: Consistência de tipos na atribuição.
        if(result == 1)
        	strcpy(tipo_dado_2,"inteiro");
        else if(result == 2)
        	strcpy(tipo_dado_2,"caracter");
        else if(result == 3)
        	strcpy(tipo_dado_2,"real");
        else
            strcpy(tipo_dado_2,"");

        if(strcmp(tipo_dado_1, ""))
            verificar_consistencia_tipos(tipo_dado_1, tipo_dado_2);
        else
            strcpy(tipo_retorno, tipo_dado_2);

        if (op_rel()) {
            proximo_Token();
            if (!expr_simp())
                modulo_erros((Erro) EXPR_SIMP_ERRO);

			//Gera código dependendo do operador relacional
			gerador_Codigo_Expr(tipo_relacional);

            strcpy(tipo_dado_1,tipo_dado);
            if(strcmp(tipo_dado_1, ""))
                verificar_consistencia_tipos(tipo_dado_1, tipo_dado_2);
            else
                strcpy(tipo_retorno, tipo_dado_2);
        }
        return TRUE;
    }
    return FALSE;
}

Boolean fator() {

    Boolean enquanto_for_virgula = TRUE;
    char id_[50], id_func[50];
	char controle_fluxo[8]; //geração de códugo.
	int enderecoRelativo5, local, global;

    //FATOR IDS
    if (Token.cat == ID) {
        strcpy(id_, Token.tipo.lexema);

        declarado_na_tabela_simbolos(id_);
        result = pesquisar_Tipo(Token.tipo.lexema, VARIAVEL);

        proximo_Token();

        if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {
            char params[20][8];
            int count_param = 0;

			//GERA CÓDIGO PARA CHAMADA DE FUNÇÃO
            pesquisar_nome_func(id_);   //Verificar esta função.

            proximo_Token();

            if (expr()) {
                strcpy(params[count_param], tipo_dado);
                count_param++;

                while (Token.cat == SN && Token.tipo.codigo == VIRGULA) {
                    proximo_Token();

                    if (!expr())
                        modulo_erros((Erro) EXPRESSAO_ERRO);

                    strcpy(params[count_param], tipo_dado);
                    count_param++;

                }
            }

            if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE) {
                verificar_param_func(id_, count_param, params);
                proximo_Token();

            }
            else
                modulo_erros((Erro) FECHAMENTO_PARENTESE_ERRO);

        return TRUE;
        }

    enderecoRelativo5 = retorna_endereco_relativo(id_);

    if(retorna_escopo(id_) == GLOBAL){
		 //GERA CÓDIGO
		strcpy(nome_label, "LOAD ");
		sprintf(label_num_s, "%d", enderecoRelativo5);
		strcpy(label_letra, label_num_s);
		strcat(nome_label, "0, ");
		strcat(nome_label, label_letra);
		strcat(nome_label, "\n");
		fprintf(arquivo_gerador,nome_label);
	}else {
	//GERA CÓDIGO
		strcpy(nome_label, "LOAD ");
		sprintf(label_num_s, "%d", enderecoRelativo5);
		strcpy(label_letra, label_num_s);
		strcat(nome_label, "1, ");
		strcat(nome_label, label_letra);
		strcat(nome_label, "\n");
		fprintf(arquivo_gerador,nome_label);
	}

    return TRUE;
    }

        //FATOR (expr)
    else if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {
        proximo_Token();
        if (!expr())
            modulo_erros((Erro) EXPRESSAO_ERRO);

        //Verifica se fechou o parentese
        if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
            proximo_Token();
        else
            modulo_erros((Erro) FECHAMENTO_PARENTESE_ERRO);

        return TRUE;
    }

        //FATOR "!" nega??o fator
    else if (Token.cat == SN && Token.tipo.codigo == NOT) {

		proximo_Token();
        if (!fator())
            modulo_erros((Erro) FATOR_ERRO);

        //Gera Código
		strcpy(controle_fluxo, "GOFALSE ");
		gera_Label(controle_fluxo);
		num_label_gofalse = num_label;
		
		fprintf(arquivo_gerador,"PUSH %d\n", 0);
		strcpy(controle_fluxo, "GOTO ");
		gera_Label(controle_fluxo);
		num_label_goto = num_label;
		
		strcpy(nome_label, "LABEL ");
		sprintf(label_num_s, "%i", num_label_gofalse);
 		strcpy(label_letra, "L");
  		strcat(label_letra, label_num_s);
  		strcat(nome_label, label_letra);
  		strcat(nome_label, "\n");
  		fprintf(arquivo_gerador,nome_label);
		
		fprintf(arquivo_gerador,"PUSH %d\n", 1);
		
		strcpy(nome_label, "LABEL ");
		sprintf(label_num_s, "%i", num_label_goto);
  		strcpy(label_letra, "L");
  		strcat(label_letra, label_num_s);
  		strcat(nome_label, label_letra);
  		strcat(nome_label, "\n");
  		fprintf(arquivo_gerador,nome_label);

        return TRUE;
    }

        //FATOR intcon
    else if (Token.cat == CT_I) {
		//GERA CÓDIGO
		fprintf(arquivo_gerador,"PUSH %d\n", Token.tipo.valor_int);

		proximo_Token();

        strcpy(tipo_dado, "inteiro"); //Copia para comparação de tipos na analise semântica
        return TRUE;
    }

        //FATOR realcon
    else if (Token.cat == CT_R) {
        //GERA CÓDIGO
		fprintf(arquivo_gerador,"PUSH %g\n", Token.tipo.valor_real);

		proximo_Token();

        strcpy(tipo_dado, "real");
        return TRUE;
    }

        //FATOR caraccon
    else if (Token.cat == CT_C) {
        proximo_Token();

        strcpy(tipo_dado, "caracter");
        return TRUE;
    }

        //FATOR cadeiaccon
    else if (Token.cat == CT_CD) {
        proximo_Token();

        return TRUE;
    }

    return FALSE;

}

Boolean op_rel() {

    if (Token.cat == SN && Token.tipo.codigo == IGUAL) {
        tipo_relacional = 5; //Saber o tipo relacional para gerar código.
		return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == DIFERENTE) {
    	tipo_relacional = 6;
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MENORIGUAL) {
    	tipo_relacional = 2;
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MAIORIGUAL) {
    	tipo_relacional = 1;
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MENOR) {
    	tipo_relacional = 4;
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MAIOR) {
    	tipo_relacional = 3;
        return TRUE;
    }

    return FALSE;
}

void prog() {
	abrir_Arquivo_Gerador();

    int num_var_prog = 0;

	//GERA CÓDIGO
	fprintf(arquivo_gerador, "INIP\n");  //Inicio do programa

	while (Token.cat != END) {

        proximo_Token();
        Boolean eh_semretorno = FALSE;

        if (Token.cat == PR && Token.tipo.codigo == SEMRETORNO) {
            eh_semretorno = TRUE;
            strcpy(tipo_id, "");
            tipo_proc = 1;     //Saber se é procedimento ou função.
        }else {
        	tipo_proc = 0;
		}

        if (Token.cat == PR && Token.tipo.codigo == PROTOTIPO) {

            proximo_Token();

            if (Token.cat == PR && Token.tipo.codigo == SEMRETORNO) {
                eh_semretorno = TRUE;
                strcpy(tipo_id, "");
            }

            if (tipo() || eh_semretorno) {
                proximo_Token();

                if (Token.cat == ID) {
					strcpy(assinatura_atual.id,Token.tipo.lexema);

                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, FUNCAO_PROTOTIPO);
                    adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, GLOBAL, FUNCAO_PROTOTIPO);

					if(!tipo_proc){
						strcpy(assinatura_atual.tipo, tipo_id);
					}

                    proximo_Token();

                    if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {
                        proximo_Token();

                        tipos_p_opc();

                        if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE) {
                            proximo_Token();

                            while ((Token.cat == SN && Token.tipo.codigo == VIRGULA)) {

                                proximo_Token();

                                if (Token.cat == ID) {
                                	strcpy(assinatura_atual.id,Token.tipo.lexema);

                                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, FUNCAO_PROTOTIPO);
                                    adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, GLOBAL, FUNCAO_PROTOTIPO);
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
                    } else {
                        modulo_erros((Erro) ABERTURA_PARENTESE_ERRO);
                    }
                } else {
                    modulo_erros((Erro) ID_ERRO);
                }
            } else {
                modulo_erros((Erro) TIPO_ERRO);
            }

//            adicionar_qtd_param(contagem_parametros, assinatura_atual.id);
//			contagem_parametros=0;
//
        } else if (tipo() || eh_semretorno) {
            proximo_Token();

            if (Token.cat == ID) {

            	strcpy(nome_func, Token.tipo.lexema);

                if (TNext.cat == SN && TNext.tipo.codigo == ABRE_PARENTESE) {
					//GERA CÓDIGO
					strcpy(nome_label, "GOTO "); //Goto (para pular função)
					label++;
					num_label=label;
					sprintf(label_num_s, "%i", num_label);
					strcpy(label_letra, "L");
					strcat(label_letra, label_num_s);
					strcat(nome_label, label_letra);
					strcat(nome_label, "\n");
					fprintf(arquivo_gerador,nome_label);
					
					//Armazenando Label do GOTO, para colocar no Rotulo depois que ele gerou código de RET.
				 	num_label_goto = num_label;

					//label (Rotulo da função)
					strcpy(nome_label, "LABEL ");
					label++;
					num_label=label;
					sprintf(label_num_s, "%i", num_label);
					strcpy(label_letra, "L");
					strcat(label_letra, label_num_s);
					strcat(nome_label, label_letra);
					strcat(nome_label, "\n");
					fprintf(arquivo_gerador,nome_label);

                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, FUNCAO);
                    adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, GLOBAL, FUNCAO);
					adicionar_label_Tabela(Token.tipo.lexema, label_letra);
                } else {
                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, VARIAVEL);
                    adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, GLOBAL, VARIAVEL);
                    addEnderecoRelativo(Token.tipo.lexema, GLOBAL, VARIAVEL);
                    num_var++;
                }

				strcpy(assinatura_atual.id,Token.tipo.lexema);

				if(!tipo_proc)
				strcpy(assinatura_atual.tipo, tipo_id);

                proximo_Token();

                if ((Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE)) {
                    proximo_Token();

                    tipos_param();

					strcpy(assinatura_atual.parametros[posicao_parametros],tipo_id);

                    if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE) {
                        proximo_Token();

                        if (Token.cat == SN && Token.tipo.codigo == ABRE_CHAVES) {
                            proximo_Token();

                            //GERA CÓDIGO (inicio de função)
							fprintf(arquivo_gerador, "INIPR\n");

                            while (tipo()) {

                                proximo_Token();

                                if (Token.cat == ID) {
                                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, VARIAVEL);
                                    adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, LOCAL, VARIAVEL);
                                    addEnderecoRelativo(Token.tipo.lexema, LOCAL, VARIAVEL);
                                	num_var++;

                                    proximo_Token();

                                    while ((Token.cat == SN && Token.tipo.codigo == VIRGULA)) {

                                        proximo_Token();

                                        if (Token.cat == ID) {
                                            pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, VARIAVEL);
                                            adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, LOCAL, VARIAVEL);
                                            addEnderecoRelativo(Token.tipo.lexema, LOCAL, VARIAVEL);
											num_var++;

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

                            //GERA CÓDIGO
                            if(num_var != 0)
	                        	fprintf(arquivo_gerador, "AMEM %d\n", num_var);

                            proc_ = eh_semretorno;
                            func_ = !eh_semretorno;

                            enquanto_for_comando = 1;
                            while (enquanto_for_comando) {
                                cmd();
                            }

                            if (!(Token.cat == SN && Token.tipo.codigo == FECHA_CHAVES)) {
                                modulo_erros((Erro) FECHAMENTO_CHAVES_ERRO);
                            } else
                                excluir_Tabela_Simbolos();

						//GERA CÓDIGO
						if(num_var != 0)
	       					fprintf(arquivo_gerador, "DMEM %d\n", num_var);    //Utilizado para representar as variaveis locais.
					
						num_var=0;
						
						if(eh_semretorno){
							//Gera código RET
							fprintf(arquivo_gerador,"RET %d,%d\n", 1,0);
							
							//Gera código Label
							strcpy(nome_label, "LABEL ");
							sprintf(label_num_s, "%i", num_label_goto);
							strcpy(label_letra, "L");
							strcat(label_letra, label_num_s);
							strcat(nome_label, label_letra);
							strcat(nome_label, "\n");
							fprintf(arquivo_gerador,nome_label);
						}
						
						} else {
                            modulo_erros((Erro) ABERTURA_CHAVES_ERRO);
                        }
                    } else {
                        modulo_erros((Erro) FECHAMENTO_PARENTESE_ERRO);
                    }
                } else if (eh_semretorno) {
                    modulo_erros((Erro) ABERTURA_PARENTESE_ERRO);
                } else if (Token.tipo.codigo == VIRGULA) {   //Declaração de variavel
                  	while (Token.tipo.codigo == VIRGULA) {
                        proximo_Token();
                        pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, VARIAVEL);
                        adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, GLOBAL, VARIAVEL);
                        addEnderecoRelativo(Token.tipo.lexema, GLOBAL, VARIAVEL);
						num_var++;

                        if (Token.cat != ID) {
                            modulo_erros((Erro) ID_ERRO);
                        }
                        proximo_Token();

                        if (!(Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA) && !(Token.cat == SN && Token.tipo.codigo == VIRGULA))
                        	modulo_erros((Erro) PONTO_VIRGULA_ERRO);

						//GERA CÓDIGO
	                    if(Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA){
							fprintf(arquivo_gerador, "AMEM %d\n", num_var);
	                   		//label++;
	                    	//num_label=label;
	                    	//sprintf(label_num_s, "%i", num_label);
	                    	//strcpy(label_letra, "L");
	                    	//strcat(label_letra, label_num_s);
	                    	//fprintf(arquivo_gerador, "GO TO %s\n", label_letra);
	                    	num_var_prog = num_var;

							num_var=0;
						}
                    }
                } else if (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA) {

					//GERA CÓDIGO (Quando a declaração é uma unica variavel)
					fprintf(arquivo_gerador, "AMEM %d\n", num_var);
	                label++;
	                num_label=label;
	                sprintf(label_num_s, "%i", num_label);
	                strcpy(label_letra, "L");
	                strcat(label_letra, label_num_s);
	                fprintf(arquivo_gerador, "GO TO %s\n", label_letra);
	                num_var_prog = num_var;

					num_var=0;
                } else
                    modulo_erros((Erro) PONTO_VIRGULA_ERRO);
            } else {
                modulo_erros((Erro) ID_ERRO);
            }
//            adicionar_qtd_param(contagem_parametros, nome_func);
//            contagem_parametros=0;
        }
    }   

    if(!tem_principal())
        modulo_erros((Erro) PRINCIPAL_ERROR);
    else
		pesquisar_nome_func("principal");
        
	 //GERA CÓDIGO
    if(num_var_prog != 0)
        fprintf(arquivo_gerador, "DMEM %d\n",  num_var_prog);
        
fprintf(arquivo_gerador, "HALT\n");

fechar_Arquivo_Gerador();
}

//Erros semânticos

//Revisar essa estrutura da assinatura posteriormente
//Compara a assinatura da função e procedimento com suas devidas definições

void verificar_consistencia_tipos(char tipo1[], char tipo2[]){
	int tipo_dado;

	if(!strcmp(tipo1, "inteiro"))  tipo_dado=1;
	if(!strcmp(tipo1, "caracter")) tipo_dado=2;
	if(!strcmp(tipo1, "real")) tipo_dado=3;

	switch(tipo_dado){
	//INT

		case 1:
			if(strcmp(tipo2,"inteiro") != 0){
				if(strcmp(tipo2,"caracter") != 0) modulo_erros((Erro)TIPO_INCOMPATIVEL_ERRO);
			}
			strcpy(tipo_retorno, "inteiro");
		break;

	//CHAR
		case 2:
			if(strcmp(tipo2,"caracter") != 0){
				if(strcmp(tipo2,"inteiro") != 0) modulo_erros((Erro)TIPO_INCOMPATIVEL_ERRO);
			}
			strcpy(tipo_retorno, "caracter");
		break;

	//REAL
		case 3:
			if(strcmp(tipo2,"real") != 0){modulo_erros((Erro)TIPO_INCOMPATIVEL_ERRO);}
			strcpy(tipo_retorno, "real");
		break;

		default:
			if(strcmp(tipo2,"") != 0){modulo_erros((Erro)TIPO_INCOMPATIVEL_ERRO);}
					strcpy(tipo_retorno, "");

				break;
	}
}

//Geração de código
void gera_codigo_Maior_Igual()
{
	char controle_fluxo[8];

	fprintf(arquivo_gerador,"SUB\n");
	fprintf(arquivo_gerador,"COPY\n");
	strcpy(controle_fluxo, "GOTRUE ");
	gera_Label(controle_fluxo);
	num_label_gotrue = num_label;
	
	strcpy(controle_fluxo, "GOFALSE ");
	gera_Label(controle_fluxo);
	num_label_gofalse = num_label;
	
	fprintf(arquivo_gerador,"PUSH %d\n", 0);
	strcpy(controle_fluxo, "GOTO ");
	gera_Label(controle_fluxo);
	num_label_goto = num_label;
	
	strcpy(nome_label, "LABEL ");
		fprintf(arquivo_gerador,"SUB\n");
	fprintf(arquivo_gerador,"COPY\n");
	strcpy(controle_fluxo, "GOFALSE ");
	gera_Label(controle_fluxo);
	num_label_gofalse = num_label;
	
	strcpy(controle_fluxo, "GOTRUE ");
	gera_Label(controle_fluxo);
	num_label_gotrue = num_label;
	
	fprintf(arquivo_gerador,"PUSH %d\n", 1);
	strcpy(controle_fluxo, "GOTO ");
	gera_Label(controle_fluxo);
	num_label_goto = num_label;
	
	strcpy(nome_label, "LABEL ");	
    sprintf(label_num_s, "%i", num_label_gotrue);
    strcpy(label_letra, "L");
    strcat(label_letra, label_num_s);
    strcat(nome_label, label_letra);
    strcat(nome_label, "\n");
    fprintf(arquivo_gerador,nome_label);
	
	fprintf(arquivo_gerador,"POP\n");
	
	strcpy(nome_label, "LABEL ");
	sprintf(label_num_s, "%i", num_label_gofalse); //VER PQ ESSE DIABO TÁ COLOCANDO 0
    strcpy(label_letra, "L");
    strcat(label_letra, label_num_s);
    strcat(nome_label, label_letra);
    strcat(nome_label, "\n");
    fprintf(arquivo_gerador,nome_label);
	
	fprintf(arquivo_gerador,"PUSH %d\n", 0);
	
	strcpy(nome_label, "LABEL ");
	sprintf(label_num_s, "%i", num_label_goto);
    strcpy(label_letra, "L");
    strcat(label_letra, label_num_s);
    strcat(nome_label, label_letra);
    strcat(nome_label, "\n");
    fprintf(arquivo_gerador,nome_label);
}

void gera_codigo_Menor_Igual()
{
   char controle_fluxo[8];

   fprintf(arquivo_gerador,"SUB\n");
   strcpy(controle_fluxo, "GOTRUE ");
   gera_Label(controle_fluxo);
   num_label_gotrue = num_label;
   
   fprintf(arquivo_gerador,"PUSH %d\n", 1);
   strcpy(controle_fluxo, "GOTO ");
   gera_Label(controle_fluxo);
   num_label_goto = num_label;
   
   strcpy(nome_label, "LABEL ");
   sprintf(label_num_s, "%i", num_label_gotrue);
   strcpy(label_letra, "L");
   strcat(label_letra, label_num_s);
   strcat(nome_label, label_letra);
   strcat(nome_label, "\n");
   fprintf(arquivo_gerador,nome_label);
   
   fprintf(arquivo_gerador,"PUSH %d\n", 0);
   strcpy(nome_label, "LABEL ");
    sprintf(label_num_s, "%i", num_label_goto);
    strcpy(label_letra, "L");
    strcat(label_letra, label_num_s);
    strcat(nome_label, label_letra);
    strcat(nome_label, "\n");
    fprintf(arquivo_gerador,nome_label);
}

void gera_codigo_Maior()
{
  char controle_fluxo[8];
  
  fprintf(arquivo_gerador,"SUB\n");
  strcpy(controle_fluxo, "GOTRUE ");
  gera_Label(controle_fluxo);
  num_label_gotrue = num_label;
    
  fprintf(arquivo_gerador,"PUSH %d\n", 0);
  strcpy(controle_fluxo, "GOTO ");
  gera_Label(controle_fluxo);
  num_label_goto = num_label;
  
  strcpy(nome_label, "LABEL ");
  sprintf(label_num_s, "%i", num_label_gotrue);
  strcpy(label_letra, "L");
  strcat(label_letra, label_num_s);
  strcat(nome_label, label_letra);
  strcat(nome_label, "\n");
  fprintf(arquivo_gerador,nome_label);
  
  fprintf(arquivo_gerador,"PUSH %d\n", 1);
  strcpy(nome_label, "LABEL ");
  sprintf(label_num_s, "%i", num_label_goto);
  strcpy(label_letra, "L");
  strcat(label_letra, label_num_s);
  strcat(nome_label, label_letra);
  strcat(nome_label, "\n");
  fprintf(arquivo_gerador,nome_label);
}

void gera_codigo_Menor()
{
    char controle_fluxo[8];
    
	fprintf(arquivo_gerador,"SUB\n");
	fprintf(arquivo_gerador,"COPY\n");
	strcpy(controle_fluxo, "GOFALSE ");
	gera_Label(controle_fluxo);
	num_label_gofalse = num_label;
	
	strcpy(controle_fluxo, "GOTRUE ");
	gera_Label(controle_fluxo);
	num_label_gotrue = num_label;
	
	fprintf(arquivo_gerador,"PUSH %d\n", 1);
	strcpy(controle_fluxo, "GOTO ");
	gera_Label(controle_fluxo);
	num_label_goto = num_label;
	
	strcpy(nome_label, "LABEL ");	
    sprintf(label_num_s, "%i", num_label_gofalse);
    strcpy(label_letra, "L");
    strcat(label_letra, label_num_s);
    strcat(nome_label, label_letra);
    strcat(nome_label, "\n");
    fprintf(arquivo_gerador,nome_label);
	
	fprintf(arquivo_gerador,"POP\n");
	
	strcpy(nome_label, "LABEL ");
	sprintf(label_num_s, "%i", num_label_gotrue); //VER PQ ESSE DIABO TÁ COLOCANDO 0
    strcpy(label_letra, "L");
    strcat(label_letra, label_num_s);
    strcat(nome_label, label_letra);
    strcat(nome_label, "\n");
    fprintf(arquivo_gerador,nome_label);
	
	fprintf(arquivo_gerador,"PUSH %d\n", 0);
	
	strcpy(nome_label, "LABEL ");
	sprintf(label_num_s, "%i", num_label_goto);
    strcpy(label_letra, "L");
    strcat(label_letra, label_num_s);
    strcat(nome_label, label_letra);
    strcat(nome_label, "\n");
    fprintf(arquivo_gerador,nome_label);

}

void gera_codigo_Diferente()
{
   char controle_fluxo[8];

   fprintf(arquivo_gerador,"SUB\n");
   strcpy(controle_fluxo, "GOTRUE ");
   gera_Label(controle_fluxo);
   num_label_gotrue = num_label;
   
   fprintf(arquivo_gerador,"PUSH %d\n", 1);
   strcpy(controle_fluxo, "GOTO ");
   gera_Label(controle_fluxo);
   num_label_goto = num_label;
   
   strcpy(nome_label, "LABEL ");
   sprintf(label_num_s, "%i", num_label_gotrue);
   strcpy(label_letra, "L");
   strcat(label_letra, label_num_s);
   strcat(nome_label, label_letra);
   strcat(nome_label, "\n");
   fprintf(arquivo_gerador,nome_label);
   
   fprintf(arquivo_gerador,"PUSH %d\n", 0);
   strcpy(nome_label, "LABEL ");
   sprintf(label_num_s, "%i", num_label_goto);
   strcpy(label_letra, "L");
   strcat(label_letra, label_num_s);
   strcat(nome_label, label_letra);
   strcat(nome_label, "\n");
   fprintf(arquivo_gerador,nome_label);
}

void gera_codigo_Igualdade()
{
   char controle_fluxo[8];

   fprintf(arquivo_gerador,"SUB\n");
   strcpy(controle_fluxo, "GOFALSE ");
   gera_Label(controle_fluxo);
   num_label_gofalse = num_label;
   
   fprintf(arquivo_gerador,"PUSH %d\n", 0);
   strcpy(controle_fluxo, "GOTO ");
   gera_Label(controle_fluxo);
   num_label_goto = num_label;
   
   strcpy(nome_label, "LABEL ");
   sprintf(label_num_s, "%i", num_label_gofalse);
   strcpy(label_letra, "L");
   strcat(label_letra, label_num_s);
   strcat(nome_label, label_letra);
   strcat(nome_label, "\n");
   fprintf(arquivo_gerador,nome_label);
   
   fprintf(arquivo_gerador,"PUSH %d\n", 1);
   strcpy(nome_label, "LABEL ");
   sprintf(label_num_s, "%i", num_label_goto);
   strcpy(label_letra, "L");
   strcat(label_letra, label_num_s);
   strcat(nome_label, label_letra);
   strcat(nome_label, "\n");
   fprintf(arquivo_gerador,nome_label);
}

void gera_Label(char controle_fluxo[])
{
	label++;
	num_label=label;
    sprintf(label_num_s, "%i", num_label);
	strcpy(label_letra, "L");
	strcat(label_letra, label_num_s);
	strcat(controle_fluxo, label_letra);
	strcat(controle_fluxo, "\n");

	fprintf(arquivo_gerador,controle_fluxo);
}

void gerador_Codigo_Expr(int condicao)
{

	     switch(condicao)
	     {
	     	//MAIOR OU IGUAL
			case 1:
	     	     //GERA CÓDIGO
	             gera_codigo_Maior_Igual();
	     	break;

	     	//MENOR OU IGUAL
			case 2:
	     	     //GERA CÓDIGO
	             gera_codigo_Menor_Igual();
	     	break;


			//MAIOR
			case 3:
	     	    //GERA CÓDIGO
	            gera_codigo_Maior();
	     	break;


			//MENOR
	     	case 4:
	     		 //GERA CÓDIGO
	             gera_codigo_Menor();
	     	break;

	     	//IGUALDADE
	     	case 5:
				 //GERA CÓDIGO
	             gera_codigo_Igualdade();
	        break;


	        //DIFERENTE
	     	case 6:
	     		//GERA CÓDIGO
	            gera_codigo_Diferente();
	     	break;


		 }

}

void  abrir_Arquivo_Gerador()
{
    arquivo_gerador = fopen("codigo_objeto.obj","w");
    if(arquivo_gerador == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");

}

void fechar_Arquivo_Gerador()
{

	fclose(arquivo_gerador);

}
