#include "AnaSint.h"

int enquanto_for_comando = 1;
int tipo_proc=0; //Variavel que indica se � um procedimento ou func�o.
estrutura_fp assinatura_atual; //Assinatura das fun��es e procedimentos, utilizado para analise sem�ntica
int posicao_parametros=0; //Variavel que indica a posi��o atual do parametro na assinatura da fun��o
int contagem_parametros=0; //Variavel que indica a quantidade de parametros de uma assinatura de uma fun��o ou procedimento

//Analisar a condi��o dessas variaveis, s�o utilizadas na analise sem�ntica e na tabela de simbolos
int  posicao_fixa=0;
int  posicao_atual=0;
int result;

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

        /*
        case PROTOTIPO_ERROR:
			 	printf("\n\nERRO SEMANTICO NA LINHA %d, DECLARE ASSINATURA ANTES DE FUNC�O OU PROCEDIMENTO!\n\n", linha);
                system("PAUSE");
			 break;

        Ver o funcionamento desde erro depois
        */

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
	
	if (Token.cat == ID) {
	result = pesquisar_Tipo(Token.tipo.lexema, tipo_id, VARIAVEL);
		
		proximo_Token();

        if (Token.cat == SN && Token.tipo.codigo == ATRIBUICAO) {
            proximo_Token();

            
			if (!expr())
                modulo_erros((Erro) EXPR_ERRO);

        } else modulo_erros((Erro) ATRIBUICAO_ERRO);
    }
}

void tipos_param() {
    Boolean enquanto_for_virgula = TRUE;

    if (Token.cat == PR && Token.tipo.codigo == SEMPARAM) {
        strcpy(assinatura_atual.parametros[0],Token.tipo.lexema); //Coloando o nome do parametro na estrutura
        proximo_Token();

    } else {
        if (tipo()) {
            strcpy(assinatura_atual.parametros[posicao_parametros],Token.tipo.lexema);
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
                            strcpy(assinatura_atual.parametros[posicao_parametros],Token.tipo.lexema);
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

//if(!tipo_proc) pesquisar_assinatura(assinatura_atual.tipo,assinatura_atual.id,assinatura_atual.parametros,1,contagem_parametros);
//else {pesquisar_assinatura(assinatura_atual.tipo,assinatura_atual.id,assinatura_atual.parametros,0,contagem_parametros);}

contagem_parametros=0;
}

void tipos_p_opc() {

    if (Token.cat == PR && Token.tipo.codigo == SEMPARAM) {
        proximo_Token();
    } else {
        if (tipo()) {
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
        } else {
            modulo_erros((Erro) TIPO_ERRO);
        }
    }
}

void cmd() {
    Boolean enquanto_for_virgula = TRUE;
    char id_[15];

    if (Token.cat == ID && TNext.cat == SN && TNext.tipo.codigo == ATRIBUICAO) {
        atrib();
        if (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA)
            proximo_Token();
        else
            modulo_erros((Erro) PONTO_VIRGULA_ERRO);
        enquanto_for_comando = 1;

    } else if (Token.cat == ID) {
        proximo_Token();

        if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {
            proximo_Token();

            if (expr()) {
                while (enquanto_for_virgula) {
                    if (Token.cat == SN && Token.tipo.codigo == VIRGULA) {
                        proximo_Token();

                        if (expr()) {
                            enquanto_for_virgula = TRUE;
                            proximo_Token();
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

//        if(TNext.cat == SN && TNext.tipo.codigo == ATRIBUICAO)
//            proximo_Token();

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

                cmd();

                if (Token.cat == PR && Token.tipo.codigo == SENAO) {
                    proximo_Token();
                    cmd();
                }

                enquanto_for_comando = 1;
                break;


                //enquanto
            case ENQUANTO:
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

                cmd();

                enquanto_for_comando = 1;
                break;

                //para
            case PARA:
                proximo_Token();

                if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {
                    proximo_Token();
                    atrib();

                    if (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA) {
                        proximo_Token();
                        expr();

                        if (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA) {
                            proximo_Token();
                            atrib();

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
                enquanto_for_comando = 1;
                break;

                //retorne
            case RETORNE:   //Ver a quest?o do permitir por cadeia vazia e fazer a quest?o do ponto e virgula
                proximo_Token();

                expr();

                if (!(Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA))
                    modulo_erros((Erro) PONTO_VIRGULA_ERRO);

                enquanto_for_comando = 1;
                proximo_Token();
                break;

            case ABRE_CHAVES:
                proximo_Token();
                cmd();

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
    if (fator()) {
        while ((Token.cat == SN && Token.tipo.codigo == MULTIPLICACAO) ||
               (Token.cat == SN && Token.tipo.codigo == DIVISAO) || (Token.cat == SN && Token.tipo.codigo == AND)) {
            proximo_Token();

            if (fator())
                proximo_Token();
            else
                modulo_erros((Erro) FATOR_ERRO);
        }
        return TRUE;
    }
    return FALSE;
}

Boolean expr_simp() {
    if ((Token.cat == SN && Token.tipo.codigo == SOMA) || (Token.cat == SN && Token.tipo.codigo == SUBTRACAO))
        proximo_Token();

    if (termo()) {
        while ((Token.cat == SN && Token.tipo.codigo == SOMA) || (Token.cat == SN && Token.tipo.codigo == SUBTRACAO) ||
               Token.cat == SN && Token.tipo.codigo == OR) {
            proximo_Token();

            if (!termo())
                modulo_erros((Erro) TERMO_ERRO);
        }
        return TRUE;
    }
    return FALSE;
}

Boolean expr() {
    if (expr_simp()) {
        strcpy(tipo_dado_1,tipo_dado);
        
        //Analise sem�ntica: Consist�ncia de tipos na atribui��o.
        if(result == 1)
        	strcpy(tipo_dado_2,"inteiro");
        if(result == 2)
        	strcpy(tipo_dado_2,"caracter");
        if(result == 3)
        	strcpy(tipo_dado_2,"real");	
        
		verificar_consistencia_tipos(tipo_dado_1, tipo_dado_2);
		
        if (op_rel()) {
            proximo_Token();
            if (!expr_simp())
                modulo_erros((Erro) EXPR_SIMP_ERRO);

            strcpy(tipo_dado_2,tipo_dado);
            verificar_consistencia_tipos(tipo_dado_1, tipo_dado_2);
        }
        return TRUE;
    }
    return FALSE;
}

Boolean fator() {

    Boolean enquanto_for_virgula = TRUE;
    char id_[50], id_func[50];

    //FATOR IDS
    if (Token.cat == ID) {
        strcpy(id_, Token.tipo.lexema);

        proximo_Token();

        if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {

            strcpy(id_func, Token.tipo.lexema);

            proximo_Token();

            if (expr()) {
                while (Token.cat == SN && Token.tipo.codigo == VIRGULA) {
                    proximo_Token();

                    if (!expr())
                        modulo_erros((Erro) EXPRESSAO_ERRO);

                }
            }


            if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE)
                proximo_Token();
            else
                modulo_erros((Erro) FECHAMENTO_PARENTESE_ERRO);
            return TRUE;

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
        if (fator())
            proximo_Token();
        else
            modulo_erros((Erro) FATOR_ERRO);

        return TRUE;
    }

        //FATOR intcon
    else if (Token.cat == CT_I) {
		proximo_Token();

        strcpy(tipo_dado, "inteiro"); //Copia para compara��o de tipos na analise sem�ntica
        return TRUE;
    }

        //FATOR realcon
    else if (Token.cat == CT_R) {
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
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == DIFERENTE) {
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MENORIGUAL) {
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MAIORIGUAL) {
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MENOR) {
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MAIOR) {
        return TRUE;
    }

    return FALSE;
}

void prog() {
    while (Token.cat != END) {

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

                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, FUNCAO_PROTOTIPO);
                    adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, GLOBAL, FUNCAO_PROTOTIPO);

                    proximo_Token();

                    if (Token.cat == SN && Token.tipo.codigo == ABRE_PARENTESE) {
                        proximo_Token();

                        tipos_p_opc();

                        if (Token.cat == SN && Token.tipo.codigo == FECHA_PARENTESE) {
                            proximo_Token();

                            while ((Token.cat == SN && Token.tipo.codigo == VIRGULA)) {

                                proximo_Token();

                                if (Token.cat == ID) {
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
        } else if (tipo() || eh_semretorno) {
            proximo_Token();

            if (Token.cat == ID) {

                if (TNext.cat == SN && TNext.tipo.codigo == ABRE_PARENTESE) {
                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, FUNCAO);
                    adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, GLOBAL, FUNCAO);
                } else {
                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, VARIAVEL);
                    adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, GLOBAL, VARIAVEL);
                }


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
                                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL,
                                                              VARIAVEL);
                                    adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, LOCAL,
                                                              VARIAVEL);

                                    proximo_Token();

                                    while ((Token.cat == SN && Token.tipo.codigo == VIRGULA)) {

                                        proximo_Token();

                                        if (Token.cat == ID) {
                                            pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, VARIAVEL);
                                            adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, LOCAL, VARIAVEL);
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
                            } else
                                excluir_Tabela_Simbolos();
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
                        pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, VARIAVEL);
                        adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, GLOBAL, VARIAVEL);

                        if (Token.cat != ID) {
                            modulo_erros((Erro) ID_ERRO);
                        }
                        proximo_Token();

                        if ((Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA) ||
                            (Token.cat == SN && Token.tipo.codigo == VIRGULA)) {
                            if ((Token.cat == ID) || (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA) ||
                                (Token.cat == SN && Token.tipo.codigo == VIRGULA)) {
                                proximo_Token();
                            } else {
                                modulo_erros((Erro) ID_ERRO);
                            }
                        } else
                            modulo_erros((Erro) PONTO_VIRGULA_ERRO);
                    }
                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, VARIAVEL);
                    adicionar_Tabela_Simbolos(Token.tipo.lexema, tipo_id, GLOBAL, VARIAVEL);
                } else if (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA) {
                } else
                    modulo_erros((Erro) PONTO_VIRGULA_ERRO);
            } else {
                modulo_erros((Erro) ID_ERRO);
            }
        }
    }
}

//Erros sem�nticos

//Revisar essa estrutura da assinatura posteriormente
//Compara a assinatura da fun��o e procedimento com suas devidas defini��es
//void pesquisar_assinatura(int tipo_recebido,char id_recebido[],char parametros[][8],int sinal, int num_parametros){
//    //Sinal: 1 para indicar fun��o, 0 para indicar procedimento (ou � o contr�rio)
//
//    int posicao_assinaturas, posicao_param_func, achou_id=0, x;
//
//    if(sinal){
//
//        for(x=posicao_fixa;x<posicao_atual;x++) {
//
//            //Verifica se possui o mesmo id da assinatura
//            if(!strcmp(tabela_Simbolos[x].id, id_recebido) /*&& !strcmp(tabela_Simbolos[x].cat, "fwd_func")*/){ //verificar esta valida��o com Felipe
//                achou_id=1;
//
//                //Tipo recebido n�o pode ser int (Lucas)
//                if(tabela_Simbolos[x].tipo == tipo_recebido){  //Verifia se possui mesmo tipo de retorno da assinatura
//
//                    //Verifica a quantidade de argumentos da assinatura em rela��o a func
//                    if(tabela_Simbolos[x].qtd_param == num_parametros){
//
//                        if(strcmp(parametros[0],"semparam") != 0){
//
//                            //Verifica se os tipos dos argumentos da fun��o s�o os mesmos da assinatura
//                            for(posicao_param_func=0; posicao_param_func < num_parametros; posicao_param_func++)
//                            {
//                                if(strcmp(tabela_Simbolos[x].parametros[posicao_param_func],parametros[posicao_param_func]) != 0)
//                                    modulo_erros((Erro)ARGUMENTO_INVALIDO_ERROR);
//                            }
//
//                        }
//
//                    }else modulo_erros((Erro)QUANTIDADE_ARGUMENTOS_ERROR);
//
//                }
//                else modulo_erros((Erro)ASSINATURA_RETORNO_ERROR);
//            }
//
//        }
//
//        if(!achou_id) modulo_erros((Erro)ID_NAO_ENCONTRADO_ERROR);
//    }
//    else if(sinal == 0){
//
//        for(x=posicao_fixa;x<posicao_atual;x++) {
//
//            //Verifica se possui o mesmo id da assinatura
//            if(!strcmp(tabela_Simbolos[x].id, id_recebido) /*&& !strcmp(tabela_Simbolos[x].cat, "fwd_proc")*/){
//                achou_id=1;
//
//                //Verifica a quantidade de argumentos de proc em rela��o a assinatura
//                if(tabela_Simbolos[x].qtd_param == num_parametros){
//
//                    if(strcmp(parametros[0],"semparam") != 0){
//                        //Verifica se os tipos dos argumentos de proc s�o os mesmos da assinatura
//                        for(posicao_param_func=0; posicao_param_func < num_parametros; posicao_param_func++){
//                            if(strcmp(tabela_Simbolos[x].parametros[posicao_param_func],parametros[posicao_param_func]) != 0)
//                                modulo_erros((Erro)ARGUMENTO_INVALIDO_ERROR);
//                        }
//
//                    }
//
//                } else modulo_erros((Erro)QUANTIDADE_ARGUMENTOS_ERROR);
//            }
//        }
//
//        if(!achou_id) modulo_erros((Erro)ID_NAO_ENCONTRADO_ERROR);
//
//    }
//
//}

void verificar_consistencia_tipos(char tipo1[], char tipo2[]){
  int tipo_dado;

  if(!strcmp(tipo1, "inteiro"))  tipo_dado=1;
  if(!strcmp(tipo1, "caracter")) tipo_dado=2;
  if(!strcmp(tipo1, "real")) tipo_dado=3;


				switch(tipo_dado)
                {

				  //INT
                  case 1:

				      if(strcmp(tipo2,"inteiro") != 0)
			          {
						 if(strcmp(tipo2,"caracter") != 0) modulo_erros((Erro)TIPO_INCOMPATIVEL_ERRO);

					  }
				      strcpy(tipo_retorno, "inteiro");
				  break;

			      //CHAR
				  case 2:

				      if(strcmp(tipo2,"caracter") != 0)
			          {
						 if(strcmp(tipo2,"inteiro") != 0) modulo_erros((Erro)TIPO_INCOMPATIVEL_ERRO);
					  }
					  strcpy(tipo_retorno, "caracter");
				  break;

				  //REAL
				  case 3:
					  if(strcmp(tipo2,"real") != 0){modulo_erros((Erro)TIPO_INCOMPATIVEL_ERRO);}
					  strcpy(tipo_retorno, "real");
				  break;

			   }

}

