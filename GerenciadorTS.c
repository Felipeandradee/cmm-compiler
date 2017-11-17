#include "GerenciadorTS.h"

int base_pilha = 0;
int topo_pilha = 0;

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
