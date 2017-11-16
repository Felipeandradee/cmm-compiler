#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"


//estrutura boolean
typedef
    enum{TRUE=1,FALSE=0}
Boolean;

//estrutura Escopo
typedef
    enum{LOCAL=1,GLOBAL=0}
Escopo;

//estrutura tiposimbolo
typedef enum{
        VARIAVEL=1,
        FUNCAO,
        FUNCAO_PROTOTIPO,
        PARAMETRO,

} TipoSimbolo;


//Estrutura para analise de erros.
typedef
   enum{ID_ERRO=1,ENDVAR_ERRO,TOKEN_ERRO,TIPO_ERRO,ABERTURA_PARENTESE_ERRO,FECHAMENTO_PARENTESE_ERRO, ABERTURA_CHAVES_ERRO, FECHAMENTO_CHAVES_ERRO,ENDFUNC_ERRO,NOPARAM_ERRO, ENDPROC_ERRO, EXPRESSAO_ERRO,
       FATOR_ERRO, TERMO_ERRO, EXPR_SIMP_ERRO, EXPR_ERRO, COMANDO_VAZIO_ERRO, FECHAMENTO_COMANDO_ERRO, ATRIBUICAO_ERRO, VIRGULA_ERRO, PONTO_VIRGULA_ERRO, DISPLAY_ERRO,
	   ASSINATURA_RETORNO_ERROR, QUANTIDADE_ARGUMENTOS_ERROR, ARGUMENTO_INVALIDO_ERROR, ID_NAO_ENCONTRADO_ERROR, VAR_NAO_DECLARADA_ERROR,
	   TIPO_INCOMPATIVEL_ERRO, ID_CALL_ERRO, RETURN_PROC_ERRO, RETURN_FUNC_ERRO, RETURN_EXPR_ERRO}
Erro;

//Estrutura da tabela de simbolos (revisar...)
typedef
   struct
   {
       char id[32];
       Escopo escopo;
       TipoSimbolo tipo;
       Boolean zumbi;
   }
tabela;

//variaveis
char tipo_id[20];
char tipo_dado[15];
char nome_func[15];
int topo_pilha;

//Tabela de simbolos.
tabela tabela_Simbolos[1000];
void adicionar_Tabela_Simbolos(char id_[], Escopo escopo_, TipoSimbolo tipo_);
void pesquisar_Tabela_Simbolos(char id_[], Escopo escopo_recebido, TipoSimbolo tipo_);
void excluir_Tabela_Simbolos();
void listar_Tabela_Simbolos();



Boolean expr();
Boolean fator();
Boolean op_rel();
Boolean expr_simp();
Boolean termo();
void prog();

#endif // SINTATICO_H_INCLUDED
