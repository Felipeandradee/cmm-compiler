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
       TIPO_INCOMPATIVEL_ERRO, RETURN_PROC_ERRO, RETURN_FUNC_ERRO, RETURN_EXPR_ERRO, PRINCIPAL_ERROR
   }
Erro;

//Estrutura de fun��es e procedimentos que define: Tipo, Nome, Quantidade de parametros,etc.
typedef
   struct{
       char tipo[500];
       char id[100];
       int  tipo_func;
       int  num_param;
       char parametros[20][8];
   } estrutura_fp;

//Variaveis utilizadas para a compara��o de tipos na analise sem�ntica.
char tipo_dado_1[15],tipo_dado_2[15], tipo_dado[15], tipo_retorno[15], tipo_retorno_func[15], nome_func[15];

void verificar_consistencia_tipos(char tipo1[], char tipo2[]);

Boolean expr();
Boolean fator();
Boolean op_rel();
Boolean expr_simp();
Boolean termo();
void prog();

//Gera��o de c�digo
FILE	*arquivo_gerador;

char 	nome_label[8], label_num_s[50], label_letra[40];


void	gera_Label(char []);
void    gera_codigo_Maior_Igual();
void    gera_codigo_Menor_Igual();
void    gera_codigo_Maior();
void    gera_codigo_Menor();
void    gera_codigo_Diferente();
void    gera_codigo_Igualdade();

void	abrir_Arquivo_Gerador();
void    fechar_Arquivo_Gerador();
void    gerador_Codigo_Expr(int condicao);

#endif // SINTATICO_H_INCLUDED

