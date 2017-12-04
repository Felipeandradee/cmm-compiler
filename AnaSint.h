#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Analex.h"
#include "GerenciadorTS.h"

//Estrutura para analise de erros.
typedef
   enum{ID_ERRO=1, TIPO_ERRO,ABERTURA_PARENTESE_ERRO,FECHAMENTO_PARENTESE_ERRO, ABERTURA_CHAVES_ERRO, FECHAMENTO_CHAVES_ERRO, EXPRESSAO_ERRO,
       FATOR_ERRO, TERMO_ERRO, EXPR_SIMP_ERRO, EXPR_ERRO, ATRIBUICAO_ERRO, VIRGULA_ERRO, PONTO_VIRGULA_ERRO,
       //erros sem�nticos
       ASSINATURA_RETORNO_ERROR, QUANTIDADE_ARGUMENTOS_ERROR, ARGUMENTO_INVALIDO_ERROR, ID_NAO_ENCONTRADO_ERROR,
       TIPO_INCOMPATIVEL_ERRO
   }
Erro;

//Estrutura de fun��es e procedimentos que define: Tipo, Nome, Quantidade de parametros,etc.
typedef
   struct{
       char tipo[50];
       char id[100];
       int  tipo_func;
       int  num_param;
       char parametros[20][8];
   } estrutura_fp;

//Variaveis utilizadas para a compara��o de tipos na analise sem�ntica.
char tipo_dado_1[15],tipo_dado_2[15], tipo_dado[15], tipo_retorno[15];

void verificar_consistencia_tipos(char tipo1[], char tipo2[]);
Boolean expr();
Boolean fator();
Boolean op_rel();
Boolean expr_simp();
Boolean termo();
void prog();

#endif // SINTATICO_H_INCLUDED

