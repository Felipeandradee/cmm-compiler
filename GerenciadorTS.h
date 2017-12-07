#ifndef GERENCIADOR_H_INCLUDED
#define GERENCIADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Analex.h"

//estrutura boolean
typedef
enum {
    TRUE = 1, FALSE = 0
}
        Boolean;

//estrutura Escopo
typedef
enum {
    LOCAL = 1, GLOBAL = 0
}
Escopo;

//estrutura tiposimbolo     //N�o tem estrutura para procedimento?
typedef enum {
    VARIAVEL = 1,
    FUNCAO,
    FUNCAO_PROTOTIPO,
    PARAMETRO,

} TipoSimbolo;

// Estrutura da tabela de simbolos
typedef
struct {
    char id[32];
    char tipoVariavel[20];
    Escopo escopo;
    TipoSimbolo tipo;
    Boolean zumbi;
    int  qtd_param;
    char parametros[20][8];
}
tabela;

char tipo_id[20]; //Para capturar o id atual da variavel
//variaveis
//int topo_pilha;

//Tabela de simbolos.
tabela tabela_Simbolos[1000];

void adicionar_Tabela_Simbolos(char id_[], char tipoDaVariavel[] , Escopo escopo_, TipoSimbolo tipo_);

void pesquisar_Tabela_Simbolos(char id_[], Escopo escopo_recebido, TipoSimbolo tipo_);

int pesquisar_Tipo(char id_[],char tipoDaVariavel[], TipoSimbolo tipo_);

void pesquisar_assinatura(char tipo_recebido[],char id_recebido[],char parametros[][8],int sinal, int num_parametros);

void adicionar_qtd_param(int qtd, char id_[]); //Add os parametros da assinatura

void addParamFunc(char id2[]); //Add o numero de parametros da assinatura na fun��o propriamente dita

void addParamFunc2(char id2[], int posicaoParam);

void adicionar_Tipos_Param(int posicao_parametro , char tipo_Param[], char id_[]);

void verificar_retorno_expr(char nome_funcao[], char tipo_retorno_expr[]);

void excluir_Tabela_Simbolos();

void listar_Tabela_Simbolos();

#endif // GERENCIADOR_H_INCLUDED

