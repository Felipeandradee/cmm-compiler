#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"

//TODO: revisar Lista de variaveis
int enquanto_for_comando = 1;
int veioExpressao = 0;
int veioFator = 0;
int veioAtribuicao = 0;
int base_pilha = 0;
int topo_pilha = 0;
int tipoRelacional;

void proximo_Token() {
    Token = TNext;
    if (Token.cat != END)
        analexico();
}

//TODO: revisar o modulo_erros
void modulo_erros(Erro tipo_erro) {
    switch (tipo_erro) {
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
            printf("\n\nERRO SEMANTICO NA LINHA %d, TIPO DO RETORNO DA ASSINATURA DIFERENTE DO TIPO EM FUNC!\n\n",
                   linha);
            system("PAUSE");
            break;

        case QUANTIDADE_ARGUMENTOS_ERROR:
            printf("\n\nERRO SEMANTICO NA LINHA %d, QUANTIDADE DE ARGUMENTOS EM FUNC OU PROC DIFERENTE DA ASSINATURA!\n\n",
                   linha);
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

//atrib, ok!
void atrib() {
    if (Token.cat == ID) {
        proximo_Token();

        if (Token.cat == SN && Token.tipo.codigo == ATRIBUICAO) {
            proximo_Token();

            if (!expr())
                modulo_erros((Erro) EXPR_ERRO);

            veioAtribuicao = 1;

        } else modulo_erros((Erro) ATRIBUICAO_ERRO);
    }
}

void tipos_param() {
    Boolean enquanto_for_virgula = TRUE;

    if (Token.cat == PR && Token.tipo.codigo == SEMPARAM) {
        proximo_Token();
    } else {
        if (tipo()) {
            proximo_Token();

            if (Token.cat == ID) {
                pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);
                adicionar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);

                proximo_Token();

                while (enquanto_for_virgula) {
                    if (Token.cat == SN && Token.tipo.codigo == VIRGULA) {
                        proximo_Token();

                        if (tipo()) {

                            proximo_Token();

                            if (Token.cat == ID) {
                                pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);
                                adicionar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);

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
}

void tipos_p_opc() {

    if (Token.cat == PR && Token.tipo.codigo == SEMPARAM) {
        proximo_Token();
    } else {
        if (tipo()) {
            proximo_Token();

            if (Token.cat == ID) {
                pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);
                adicionar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);

                proximo_Token();
            }

            while (Token.cat == SN && Token.tipo.codigo == VIRGULA) {
                if (Token.cat == SN && Token.tipo.codigo == VIRGULA) {
                    proximo_Token();

                    if (tipo()) {

                        proximo_Token();

                        if (Token.cat == ID) {
                            pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);
                            adicionar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, PARAMETRO);

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
    int tipo_de_comando = 0;
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
            case RETORNE:   //Ver a quest�o do permitir por cadeia vazia e fazer a quest�o do ponto e virgula
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
                    modulo_erros((Erro) FECHAMENTO_COMANDO_ERRO);
                }
                //PONTO E V�RGULA
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

//termo, ok!
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

//expr_simp, ok!
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


//expr, ok!
Boolean expr() {
    if (expr_simp()) {

        if (op_rel()) {
            proximo_Token();
            if (!expr_simp())
                modulo_erros((Erro) EXPR_SIMP_ERRO);
        }
        return TRUE;
    }
    return FALSE;
}


//Talvez revisar com Felipe, mas por enquanto t� ok
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
        veioExpressao = 1;
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

        //FATOR "!" nega��o fator
    else if (Token.cat == SN && Token.tipo.codigo == NOT) {
        veioExpressao = 1;
        proximo_Token();
        if (fator())
            proximo_Token();
        else
            modulo_erros((Erro) FATOR_ERRO);

        return TRUE;
    }

        //FATOR intcon
    else if (Token.cat == CT_I) {
        veioExpressao = 1;
        strcpy(tipo_dado, "inteiro");
        proximo_Token();

        return TRUE;
    }

        //FATOR realcon
    else if (Token.cat == CT_R) {
        veioExpressao = 1;
        strcpy(tipo_dado, "real");
        proximo_Token();

        return TRUE;
    }

        //FATOR caraccon
    else if (Token.cat == CT_C) {
        veioExpressao = 1;
        strcpy(tipo_dado, "caracter");
        proximo_Token();

        return TRUE;
    }

        //FATOR cadeiaccon
    else if (Token.cat == CT_CD) {
        veioExpressao = 1;
        proximo_Token();
//        strcpy(tipo_dado, "cadeiacon");

        return TRUE;
    }

    //Se n�o veio fator
    veioExpressao = 0;
    return FALSE;

}

//op_rel, ok!
Boolean op_rel() {

    if (Token.cat == SN && Token.tipo.codigo == IGUAL) {
        tipoRelacional = Token.tipo.codigo;
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == DIFERENTE) {
        tipoRelacional = Token.tipo.codigo;
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MENORIGUAL) {
        tipoRelacional = Token.tipo.codigo;
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MAIORIGUAL) {
        tipoRelacional = Token.tipo.codigo;
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MENOR) {
        tipoRelacional = Token.tipo.codigo;
        return TRUE;
    }

    if (Token.cat == SN && Token.tipo.codigo == MAIOR) {
        tipoRelacional = Token.tipo.codigo;
        return TRUE;
    }

    return FALSE;
}

void adicionar_Tabela_Simbolos(char id_[], Escopo escopo_, TipoSimbolo tipo_) {
    strcpy(tabela_Simbolos[topo_pilha].id, id_);
    tabela_Simbolos[topo_pilha].escopo = escopo_;
    tabela_Simbolos[topo_pilha].tipo = tipo_;
    tabela_Simbolos[topo_pilha].zumbi = FALSE;
    topo_pilha++;
}

void pesquisar_Tabela_Simbolos(char id_[], Escopo escopo_recebido, TipoSimbolo tipo_) {
    int x;

    for (x = topo_pilha - 1; x >= base_pilha; x--) {
        if (!strcmp(tabela_Simbolos[x].id, id_) && tabela_Simbolos[x].zumbi == FALSE
            && tabela_Simbolos[x].escopo == escopo_recebido && tabela_Simbolos[x].tipo != PARAMETRO) {
            if (tipo_ == FUNCAO && tabela_Simbolos[x].tipo == FUNCAO_PROTOTIPO)
                continue;

            listar_Tabela_Simbolos();
            if (escopo_recebido == LOCAL) {

                printf("\nERRO LINHA %d VARIAVEL %s REDECLARADA EM ESCOPO LOCAL\n\n", linha, tabela_Simbolos[x].id);
                system("PAUSE");
            } else {
                printf("\nERRO LINHA %d VARIAVEL %s REDECLARADA EM ESCOPO GLOBAL\n\n", linha, tabela_Simbolos[x].id);
                system("PAUSE");

            }

        }

    }

}

//TODO: excluir_Tabela_Simbolos
void excluir_Tabela_Simbolos() {

    while (tabela_Simbolos[topo_pilha - 1].escopo == LOCAL
           && tabela_Simbolos[topo_pilha - 1].tipo != FUNCAO) {

        if (tabela_Simbolos[topo_pilha - 1].tipo == PARAMETRO)
            tabela_Simbolos[topo_pilha - 1].zumbi = TRUE;

        topo_pilha--;

    }
}

//TODO: fazer listar_Tabela_Simbolos
void listar_Tabela_Simbolos() {
    int x;

    for (x = base_pilha; x <= topo_pilha; x++) {
        printf("\n");
        printf(tabela_Simbolos[x].id);
    }
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
                    strcpy(nome_func, Token.tipo.lexema);

                    //colocar as fun��es da tabela de simbolos depois
                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, FUNCAO_PROTOTIPO);
                    adicionar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, FUNCAO_PROTOTIPO);

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
                                    adicionar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, FUNCAO_PROTOTIPO);
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
        }
        else if (tipo() || eh_semretorno) {
            proximo_Token();

            if (Token.cat == ID) {
                strcpy(nome_func, Token.tipo.lexema);


                if (TNext.cat == SN && TNext.tipo.codigo == ABRE_PARENTESE) {
                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, FUNCAO);
                    adicionar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, FUNCAO);
                } else {
                    pesquisar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, VARIAVEL);
                    adicionar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, VARIAVEL);
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
                                    adicionar_Tabela_Simbolos(Token.tipo.lexema, LOCAL,
                                                              VARIAVEL);

                                    proximo_Token();

                                    while ((Token.cat == SN && Token.tipo.codigo == VIRGULA)) {

                                        proximo_Token();

                                        if (Token.cat == ID) {
                                            pesquisar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, VARIAVEL);
                                            adicionar_Tabela_Simbolos(Token.tipo.lexema, LOCAL, VARIAVEL);
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
                        adicionar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, VARIAVEL);

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
                    adicionar_Tabela_Simbolos(Token.tipo.lexema, GLOBAL, VARIAVEL);
                } else if (Token.cat == SN && Token.tipo.codigo == PONTO_VIRGULA) {
//                    proximo_Token();
                } else
                    modulo_erros((Erro) PONTO_VIRGULA_ERRO);
            } else {
                modulo_erros((Erro) ID_ERRO);
            }
        }
    }
}


