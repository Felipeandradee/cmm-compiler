#ifndef LEX_H_INCLUDED
#define LEX_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define TAM 1001

FILE *fp;
FILE *f_out;
int linha;

/*
ID = identificador
PR = palavra Reservada
SN = simbolo
CT_I = constante Inteiro
CT_R = constante Real
CT_C = caracter
CT_CD = cadeia de caracter
*/
typedef enum {
    ID, PR, SN, CT_I, CT_R, CT_C, CT_CD, END
} categoria;

typedef enum {
    		OR=0,
            AND=1,
            NOT=2,
            MULTIPLICACAO=3,
            DIVISAO=4,
            SOMA=5,
            SUBTRACAO=6,
            MENOR=7,
            MENORIGUAL=8,
            MAIOR=9,
            MAIORIGUAL=10,
            IGUAL=11,
            ATRIBUICAO=12,
            DIFERENTE=13,
            VIRGULA=14,
            PONTO_VIRGULA=15,
            ABRE_PARENTESE=16,
            FECHA_PARENTESE=17,
            ABRE_CHAVES=18,
            FECHA_CHAVES=19
} sinais;


typedef enum {
        SEMRETORNO=1,
        CARACTER,
        INTEIRO,
        REAL,
        BOOLEANO,
        SEMPARAM,
        SE,
        SENAO,
        ENQUANTO,
        PARA,
        RETORNE,
        PROTOTIPO
} PalavraReservada;

extern char pReservada[100][11];

typedef struct t {
    categoria cat;

    union {
        char lexema[TAM];
        int codigo;
        int valor_int;
        float valor_real;
    } tipo;
} TOKEN;


int posPR;
char ch;
TOKEN TNext;
TOKEN Token;
//void error_lexico();

FILE * abrirArquivo(char nomeArquivo[]);
FILE * salvarArquivo(char nomeArquivo[]);

//TOKEN montaToken(int cat, char token[], char ch, int pos);

int searchPR(char token[]);

void analexico();

#endif
