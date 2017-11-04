#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexico.h"
#define TAM 1001

int linha = 1;
char pReservada[100][11] = {
    {"semretorno"},
    {"caracter"},
    {"inteiro"},
    {"real"},
    {"booleano"},
    {"semparam"},
    {"se"},
    {"senao"},
    {"enquanto"},
    {"para"},
    {"retorne"}
};

char pSinais[100][18] = {
    {"or"},
    {"and"},
    {"not"},
    {"multiplicacao"},
    {"divisao"},
    {"soma"},
    {"subtracao"},
    {"menor"},
    {"menor_igual"},
    {"maior"},
    {"maior_igual"},
    {"igual"},
    {"atribuicao"},
    {"diferente"},
    {"virgula"},
    {"ponto_virgula"},
    {"abre_parenteses"},
    {"fecha_parenteses"},
    {"abre_colchetes"},
    {"fecha_colchetes"},
    {"abre_chaves"},
    {"fecha_chaves"}
};


void error() {
    fprintf(f_out,"Erro lexico na linha %d\n", linha);
    exit(1);
}


FILE * abrirArquivo(char nomeArquivo[]) {
    FILE *fp;
    if ((fp = fopen(nomeArquivo, "r")) != NULL) {
        return fp;
    } else {

        printf("Erro ao abrir o arquivo %d", errno);
        exit(1);
    }
}

FILE * salvarArquivo(char nomeArquivo[]) {
    FILE *f_out;
    if ((f_out = fopen(nomeArquivo, "w")) != NULL) {
        return f_out;
    } else {

        printf("Erro ao abrir o arquivo %d", errno);
        exit(1);
    }
}

TOKEN montaToken(int cat, char token[], char ch, int pos) {
    int convert;
    float convert2;
    TOKEN estruturaToken;

    switch (cat) {
        case ID:
        {
            fprintf(f_out,"<ID, %s>\n", token);
            estruturaToken.cat = ID;
            strcpy(estruturaToken.tipo.lexema, token);
            return estruturaToken;
        }
        case PR:
        {
            fprintf(f_out,"<PR, %s>\n", pReservada[pos]);
            estruturaToken.cat = PR;
            estruturaToken.tipo.codigo = pos;
            return estruturaToken;
        }
        case SN:
        {
            fprintf(f_out,"<SN, %s>\n", pSinais[pos]);
            estruturaToken.cat = SN;
            estruturaToken.tipo.codigo = pos;

            return estruturaToken;
        }
        case CT_I:
        {
            convert = atoi(token);
            fprintf(f_out,"<CT_I, %d>\n", convert);
            estruturaToken.cat = CT_I;
            estruturaToken.tipo.valor_int = convert;
            return estruturaToken;
        }
        case CT_R:
        {
            convert2 = atof(token);
            fprintf(f_out,"<CT_R, %.1f>\n", convert2);
            estruturaToken.cat = CT_R;
            estruturaToken.tipo.valor_real = convert2;
            return estruturaToken;
        }
        case CT_C:
        {
            fprintf(f_out,"<CT_C,%s>\n", token);
            estruturaToken.cat = CT_C;
            strcpy(estruturaToken.tipo.lexema, token);
            return estruturaToken;
        }
        case CT_CD:
        {
            fprintf(f_out,"<CT_CD, %s>\n", token);
            estruturaToken.cat = CT_CD;
            strcpy(estruturaToken.tipo.lexema, token);
            return estruturaToken;
        }
    }
}

int searchPR(char token[]) {
    int ativa;
    int i;
    ativa = 0;
    i = 1;

    while ((strcmp(pReservada[i], "") > 0)) {
        if ((strcmp(token, pReservada[i]) == 0)) {
            ativa = 1;
            break;
        }
        i++;
    }
    if (ativa == 1) {
        return i;
    } else {

        i = 0;
        return i;
    }
}

TOKEN analexico(FILE *fp, FILE *f_out) {
    int estado = 0;
    char ch;
    char tokenAux;
    char token[TAM];
    int cont = 0;
    int pos = 0;
    TOKEN estruturaToken;

    while (ch != EOF) {
        if ((ch == '\n'))
            fprintf(f_out,"LINHA %d\n", linha);


        switch (estado) {
            case 0:
            {
                memset(token, 0, TAM);
                cont = 0;
                if(ch == '\''){
                    estado = 10;
                    token[cont] = ch;
                    cont++;
                }
                ch = getc(fp);
                if(ch == EOF) {
                    printf("FIM DO ARQUIVO\n");
                    return ;
                }

                if ((ch == ' ') || (ch == '\t')) {
                    estado = 0;
                }
                if ((ch == '\n')) {
                    estado = 0;
                    linha++;
                    //fprintf(f_out,"LINHA %d\n", linha);
                }
                if (isdigit(ch)) {
                    estado = 2;
                    token[cont] = ch;
                    cont++;
                }
                if (isalpha(ch)) {
                    estado = 1;
                    token[cont] = ch;
                    cont++;
                }
                if (ch == '\'') {
                    estado = 8;
                    token[cont] = ch;
                    cont++;
                }
                if (ch == '"') {
                    estado = 13;
                    token[cont] = ch;
                    cont++;
                }
                if (ch == '\/') {
                    estado = 16;
                    token[cont] = ch;
                    cont++;
                }
                if (ch == '=') {
                    estado = 20;
                    token[cont] = ch;
                    cont++;
                }
                if (ch == '!') {
                    estado = 23;
                    token[cont] = ch;
                    cont++;
                }
                if (ch == '>') {
                    estado = 26;
                    token[cont] = ch;
                    cont++;
                }
                if (ch == '<') {
                    estado = 29;
                    token[cont] = ch;
                    cont++;
                }

                if ((ch == '[')||(ch == ']')||(ch == '{')||(ch == '}')||
                    (ch == '(')||(ch == ')')||(ch == '+')||(ch == '-')||
                    (ch == '*')||(ch == ',')||(ch == ';')) {
                    estado = 32;
                }
                if (ch == '&') {
                    estado = 33;
                }
                if (ch == '|') {
                    estado = 35;
                }

                break;
            }
            case 1:
            {
                ch = getc(fp);
                if (isalpha(ch)||isdigit(ch)||ch =='_') {
                    estado = 1;
                    token[cont] = ch;
                    cont++;
                } else {
                    estado = 3;
                }
                break;
            }
            case 2:
            {
                ch = getc(fp);
                if (isdigit(ch)) {
                    estado = 2;
                    token[cont] = ch;
                    cont++;
                } else if(ch=='.'){
                    estado = 4;
                    token[cont] = ch;
                    cont++;
                }
                else {
                    estado = 7;
                }
                break;
            }
            case 3:
            {
                int lpr = searchPR(token);
                if(lpr){
                    estruturaToken = montaToken(PR, token, '\0', lpr);
                }else{
                    estruturaToken = montaToken(ID, token, '\0', 0);
                }

                estado = 0;
                ungetc(ch, fp);break;
                return estruturaToken;
            }
            case 4:
            {
                ch = getc(fp);
                if (isdigit(ch)) {
                    estado = 5;
                    token[cont] = ch;
                    cont++;
                } else {
                    error();
                }
                break;
            }
            case 5:
            {
                ch = getc(fp);
                if (isdigit(ch)) {
                    estado = 5;
                    token[cont] = ch;
                    cont++;
                } else {
                    estado = 6;
                }
                break;
            }
            case 6:
            {
                estruturaToken = montaToken(CT_R, token, '\0', 0);
                estado = 0;
                ungetc(ch, fp);break;
                return estruturaToken;
            }
            case 7:
            {
                estruturaToken = montaToken(CT_I, token, '\0', 0);
                estado = 0;
                ungetc(ch, fp);break;
                return estruturaToken;
            }
            case 8:
            {
                ch = getc(fp);
                if (isprint(ch)) {
                    estado = 9;
                    token[cont] = ch;
                    cont++;
                } else if(ch=='\\'){
                    estado = 11;
                    tokenAux = ch;
                } else {
                    error();
                }
                break;
            }
            case 9:
            {
                ch = getc(fp);
                if(ch == '\''){
                    estado = 10;
                    token[cont] = ch;
                    cont++;
                } else if (isprint(ch)) {
                    estado = 9;
                    token[cont] = ch;
                    cont++;
                } else {
                    error();
                }
                break;
            }
            case 10:
            {
                estruturaToken = montaToken(CT_C, token, tokenAux, 0);
                estado = 0;break;
                return estruturaToken;
            }
            case 11:
            {
                ch = getc(fp);
                if ((ch == 'n')||(ch == '0')) {
                    estado = 12;
                    token[cont] = ch;
                    cont++;
                } else {
                    error();
                }
                break;
            }
            case 12:
            {
                ch = getc(fp);
                if (ch == '\'') {
                    estado = 10;
                    token[cont] = ch;
                    cont++;
                } else {
                    error();
                }
                break;
            }
            case 13:
            {
                ch = getc(fp);
                if(ch == '"'){
                    estado = 15;
                    token[cont] = ch;
                    cont++;
                } else if (isprint(ch)) {
                    estado = 13;
                    token[cont] = ch;
                    cont++;
                } else if(ch == '"'){
                    estado = 15;
                    token[cont] = ch;
                    cont++;
                } else {
                    error();
                }
                break;
            }
            case 15:
            {
                estruturaToken = montaToken(CT_CD, token, '\0', pos);
                estado = 0;break;
                return estruturaToken;
            }
            case 16:
            {
                ch = getc(fp);
                if (ch == '*') {
                    estado = 17;
                    token[cont] = ch;
                    cont++;
                } else{
                    error();
                }
                break;
            }
            case 17:
            {
                ch = getc(fp);
                token[cont] = ch;
                cont++;
                if (ch == '*') {
                    estado = 18;
                } else if (ch == '\n'){
                    linha++;
                } else {
                    estado = 17;
                }
                break;
            }
            case 18:
            {
                ch = getc(fp);
                token[cont] = ch;
                cont++;
                if (ch == '*') {
                    estado = 18;
                } else if (ch == '/'){
                    estado = 19;
                } else if (ch == '\n'){
                    linha++;
                    estado = 17;
                 }else {
                    estado = 17;
                }
                break;
            }
            case 19:
            {
                estado = 0;
                break;
            }
            case 20:
            {
                ch = getc(fp);
                if (ch == '=') {
                    estado = 22;
                    token[cont] = ch;
                    cont++;
                } else {
                    estado = 21;
                }
                break;
            }
            case 21:
            {
                estruturaToken = montaToken(SN, "=", '\0', IGUAL);
                estado = 0;break;
                return estruturaToken;
            }
            case 22:
            {
                estruturaToken = montaToken(SN, "==", '\0', ATRIBUICAO);
                estado = 0;break;
                return estruturaToken;
            }
            case 23:
            {
                ch = getc(fp);
                if (ch == '=') {
                    estado = 25;
                    token[cont] = ch;
                    cont++;
                } else {
                    estado = 24;
                }
                break;
            }
            case 24:
            {
                estruturaToken = montaToken(SN, "!", '\0', NOT);
                estado = 0;break;
                return estruturaToken;
            }
            case 25:
            {
                estruturaToken = montaToken(SN, "!=", '\0', DIFERENTE);
                estado = 0;break;
                return estruturaToken;
            }
            case 26:
            {
                ch = getc(fp);
                if (ch == '=') {
                    estado = 28;
                    token[cont] = ch;
                    cont++;
                } else {
                    estado = 27;
                }
                break;
            }
            case 27:
            {
                estruturaToken = montaToken(SN, ">", '\0', MAIOR);
                estado = 0;
                ungetc(ch, fp);break;
                return estruturaToken;
            }
            case 28:
            {
                estruturaToken = montaToken(SN, ">=", '\0', MAIORIGUAL);
                estado = 0;
                ungetc(ch, fp);break;
                return estruturaToken;
            }
            case 29:
            {
                ch = getc(fp);
                if (ch == '=') {
                    estado = 31;
                    token[cont] = ch;
                    cont++;
                } else {
                    estado = 30;
                }
                break;
            }
            case 30:
            {
                estruturaToken = montaToken(SN, "-", '\0', MENOR);
                estado = 0;
                ungetc(ch, fp);break;
                return estruturaToken;
            }
            case 31:
            {
                estruturaToken = montaToken(SN, "<=", '\0', MENORIGUAL);
                estado = 0;break;
                return estruturaToken;
            }
            case 32:
            {
                char str[2];
                str[0] =ch;
                str[1] ='\0';
                if(ch == '['){
                    estruturaToken = montaToken(SN, str, '\0', ABRE_COLCHETES);
                }else if(ch == ']'){
                    estruturaToken = montaToken(SN, str, '\0', FECHA_COLCHETES);
                }else if(ch == '{'){
                    estruturaToken = montaToken(SN, str, '\0', ABRE_CHAVES);
                }else if(ch == '}'){
                    estruturaToken = montaToken(SN, str, '\0', FECHA_CHAVES);
                }else if(ch == '('){
                    estruturaToken = montaToken(SN, str, '\0', ABRE_PARENTESE);
                }else if(ch == ')'){
                    estruturaToken = montaToken(SN, str, '\0', FECHA_PARENTESE);
                }else if(ch == '+'){
                    estruturaToken = montaToken(SN, str, '\0', SOMA);
                }else if(ch == '-'){
                    estruturaToken = montaToken(SN, str, '\0', SUBTRACAO);
                }else if(ch == '*'){
                    estruturaToken = montaToken(SN, str, '\0', MULTIPLICACAO);
                }else if(ch == ','){
                    estruturaToken = montaToken(SN, str, '\0', VIRGULA);
                }else if(ch == ';'){
                    estruturaToken = montaToken(SN, str, '\0', PONTO_VIRGULA);
                }else{
                    error();
                }
                estado = 0;break;
                return estruturaToken;
            }
            case 33:
            {
                ch = getc(fp);
                if (ch == '&') {
                    estado = 34;
                    token[cont] = ch;
                    cont++;
                } else {
                    error();
                }
                break;
            }
            case 34:
            {
                estruturaToken = montaToken(SN, "&&", '\0', AND);
                estado = 0;break;
                return estruturaToken;
            }
            case 35:
            {
                ch = getc(fp);
                if (ch == '!') {
                    estado = 36;
                    token[cont] = ch;
                    cont++;
                } else {
                    error();
                }
                break;
            }
            case 36:
            {
                estruturaToken = montaToken(SN, "||", '\0', OR);
                estado = 0;break;
                return estruturaToken;
            }
        }
    }
}
