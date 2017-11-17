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

//estrutura tiposimbolo
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
    Escopo escopo;
    TipoSimbolo tipo;
    Boolean zumbi;
}
        tabela;

//variaveis
int topo_pilha;

//Tabela de simbolos.
tabela tabela_Simbolos[1000];

void adicionar_Tabela_Simbolos(char id_[], Escopo escopo_, TipoSimbolo tipo_);

void pesquisar_Tabela_Simbolos(char id_[], Escopo escopo_recebido, TipoSimbolo tipo_);

void excluir_Tabela_Simbolos();

void listar_Tabela_Simbolos();

#endif // GERENCIADOR_H_INCLUDED
