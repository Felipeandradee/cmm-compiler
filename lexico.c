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
    {"retorne"},
    {"prototipo"}
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
    {"abre_chaves"},
    {"fecha_chaves"}
};


void error_lexico() {
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

void montaToken(int cat, char lexema[], char ch, int pos) {
    int convert;
    float convert2;

    switch (cat) {
        case ID:
        {
            printf("<ID, %s>\n", lexema);
            TNext.cat = ID;
            strcpy(TNext.tipo.lexema, lexema);
            break;
        }
        case PR:
        {
            printf("<PR, %s>\n", pReservada[pos]);
            TNext.cat = PR;
            TNext.tipo.codigo = pos;
            break;
        }
        case SN:
        {
            printf("<SN, %s>\n", pSinais[pos]);
            TNext.cat = SN;
            TNext.tipo.codigo = pos;
            break;
        }
        case CT_I:
        {
            convert = atoi(lexema);
            printf("<CT_I, %d>\n", convert);
            TNext.cat = CT_I;
            TNext.tipo.valor_int = convert;
            break;
        }
        case CT_R:
        {
            convert2 = atof(lexema);
            printf("<CT_R, %.1f>\n", convert2);
            TNext.cat = CT_R;
            TNext.tipo.valor_real = convert2;
            break;
        }
        case CT_C:
        {
            printf("<CT_C,%s>\n", lexema);
            TNext.cat = CT_C;
            strcpy(TNext.tipo.lexema, lexema);
            break;
        }
        case CT_CD:
        {
            printf("<CT_CD, %s>\n", lexema);
            TNext.cat = CT_CD;
            strcpy(TNext.tipo.lexema, lexema);
            break;
        }
    }
}

int searchPR(char lexema[]) {
    int ativa;
    int i;
    ativa = 0;
    i = 1;

    while ((strcmp(pReservada[i], "") > 0)) {
        if ((strcmp(lexema, pReservada[i]) == 0)) {
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

void analexico() {
    int estado = 0;
    //char ch;
    char TokenAux;
    char lexema[TAM];
    int cont = 0;
    int pos = 0;

    while (1) {
//        if ((ch == '\n'))
//            printf("LINHA %d\n", linha);


        switch (estado) {
            case 0:
            {
                memset(lexema, 0, TAM);
                cont = 0;
                if(ch == '\''){
                    estado = 10;
                    lexema[cont] = ch;
                    cont++;
                }
                ch = getc(fp);
                if(ch == EOF) {
                    printf("FIM DO ARQUIVO\n");
                    TNext.cat = END;
                    return ;
                }

                else if ((ch == ' ') || (ch == '\t')) {
                    estado = 0;
                }
                else if ((ch == '\n')) {
                    estado = 0;
                    linha++;
                    printf("LINHA %d\n", linha);
                }
                else if (isdigit(ch)) {
                    estado = 2;
                    lexema[cont] = ch;
                    cont++;
                }
                else if (isalpha(ch)) {
                    estado = 1;
                    lexema[cont] = ch;
                    cont++;
                }
                else if (ch == '\'') {
                    estado = 8;
                    lexema[cont] = ch;
                    cont++;
                }
                else if (ch == '"') {
                    estado = 13;
                    lexema[cont] = ch;
                    cont++;
                }
                else if (ch == '/') {
                    estado = 16;
                    lexema[cont] = ch;
                    cont++;
                }
                else if (ch == '=') {
                    estado = 20;
                    lexema[cont] = ch;
                    cont++;
                }
                else if (ch == '!') {
                    estado = 23;
                    lexema[cont] = ch;
                    cont++;
                }
                else if (ch == '>') {
                    estado = 26;
                    lexema[cont] = ch;
                    cont++;
                }
                else if (ch == '<') {
                    estado = 29;
                    lexema[cont] = ch;
                    cont++;
                }

                else if ((ch == '{')||(ch == '}')||(ch == '(')
                    ||(ch == ')')||(ch == '+')||(ch == '-')
                    ||(ch == '*')||(ch == ',')||(ch == ';')) {
                    estado = 32;
                }
                else if (ch == '&') {
                    estado = 33;
                }
                else if (ch == '|') {
                    estado = 35;
                }

                break;
            }
            case 1:
            {
                ch = getc(fp);
                if (isalpha(ch)||isdigit(ch)||ch =='_') {
                    estado = 1;
                    lexema[cont] = ch;
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
                    lexema[cont] = ch;
                    cont++;
                } else if(ch=='.'){
                    estado = 4;
                    lexema[cont] = ch;
                    cont++;
                }
                else {
                    estado = 7;
                }
                break;
            }
            case 3:
            {
                int lpr = searchPR(lexema);
                ungetc(ch, fp);
                if(lpr){
                    montaToken(PR, lexema, '\0', lpr);return;
                }else{
                    montaToken(ID, lexema, '\0', 0);return;
                }
            }
            case 4:
            {
                ch = getc(fp);
                if (isdigit(ch)) {
                    estado = 5;
                    lexema[cont] = ch;
                    cont++;
                } else {
                    error_lexico();
                }
                break;
            }
            case 5:
            {
                ch = getc(fp);
                if (isdigit(ch)) {
                    estado = 5;
                    lexema[cont] = ch;
                    cont++;
                } else {
                    estado = 6;
                }
                break;
            }
            case 6:
            {
                montaToken(CT_R, lexema, '\0', 0);
                ungetc(ch, fp);
                return;
            }
            case 7:
            {
                montaToken(CT_I, lexema, '\0', 0);
                ungetc(ch, fp);
                return;

            }
            case 8:
            {
                ch = getc(fp);
                if (isprint(ch)) {
                    estado = 9;
                    lexema[cont] = ch;
                    cont++;
                } else if(ch=='\\'){
                    estado = 11;
                    TokenAux = ch;
                } else {
                    error_lexico();
                }
                break;
            }
            case 9:
            {
                ch = getc(fp);
                if(ch == '\''){
                    estado = 10;
                    lexema[cont] = ch;
                    cont++;
                } else if (isprint(ch)) {
                    estado = 9;
                    lexema[cont] = ch;
                    cont++;
                } else {
                    error_lexico();
                }
                break;
            }
            case 10:
            {
                montaToken(CT_C, lexema, TokenAux, 0);
                return;
            }
            case 11:
            {
                ch = getc(fp);
                if ((ch == 'n')||(ch == '0')) {
                    estado = 12;
                    lexema[cont] = ch;
                    cont++;
                } else {
                    error_lexico();
                }
                break;
            }
            case 12:
            {
                ch = getc(fp);
                if (ch == '\'') {
                    estado = 10;
                    lexema[cont] = ch;
                    cont++;
                } else {
                    error_lexico();
                }
                break;
            }
            case 13:
            {
                ch = getc(fp);
                if(ch == '"'){
                    estado = 15;
                    lexema[cont] = ch;
                    cont++;
                } else if (isprint(ch)) {
                    estado = 13;
                    lexema[cont] = ch;
                    cont++;
                } else if(ch == '"'){
                    estado = 15;
                    lexema[cont] = ch;
                    cont++;
                } else {
                    error_lexico();
                }
                break;
            }
            case 15:
            {
                montaToken(CT_CD, lexema, '\0', pos);
                return;

            }
            case 16:
            {
                ch = getc(fp);
                if (ch == '*') {
                    estado = 17;
                    lexema[cont] = ch;
                    cont++;
                } else{
                    error_lexico();
                }
                break;
            }
            case 17:
            {
                ch = getc(fp);
                lexema[cont] = ch;
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
                lexema[cont] = ch;
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
                    lexema[cont] = ch;
                    cont++;
                } else {
                    estado = 21;
                }
                break;
            }
            case 21:
            {
                montaToken(SN, "=", '\0', ATRIBUICAO);
                ungetc(ch, fp);
                return;
            }
            case 22:
            {
                montaToken(SN, "==", '\0', IGUAL);
                return;
            }
            case 23:
            {
                ch = getc(fp);
                if (ch == '=') {
                    estado = 25;
                    lexema[cont] = ch;
                    cont++;
                } else {
                    estado = 24;
                }
                break;
            }
            case 24:
            {
                montaToken(SN, "!", '\0', NOT);
                ungetc(ch, fp);
                return;

            }
            case 25:
            {
                montaToken(SN, "!=", '\0', DIFERENTE);
                return;

            }
            case 26:
            {
                ch = getc(fp);
                if (ch == '=') {
                    estado = 28;
                    lexema[cont] = ch;
                    cont++;
                } else {
                    estado = 27;
                }
                break;
            }
            case 27:
            {
                montaToken(SN, ">", '\0', MAIOR);
                ungetc(ch, fp);
                return;

            }
            case 28:
            {
                montaToken(SN, ">=", '\0', MAIORIGUAL);
                return;
            }
            case 29:
            {
                ch = getc(fp);
                if (ch == '=') {
                    estado = 31;
                    lexema[cont] = ch;
                    cont++;
                } else {
                    estado = 30;
                }
                break;
            }
            case 30:
            {
                montaToken(SN, "-", '\0', MENOR);
                ungetc(ch, fp);
                return;
            }
            case 31:
            {
                montaToken(SN, "<=", '\0', MENORIGUAL);
                return;
            }
            case 32:
            {
                char str[2];
                str[0] =ch;
                str[1] ='\0';
                if(ch == '{'){
                    montaToken(SN, str, '\0', ABRE_CHAVES);
                    return;
                }else if(ch == '}'){
                    montaToken(SN, str, '\0', FECHA_CHAVES);
                    return;
                }else if(ch == '('){
                    montaToken(SN, str, '\0', ABRE_PARENTESE);
                    return;
                }else if(ch == ')'){
                     montaToken(SN, str, '\0', FECHA_PARENTESE);
                    return;
                }else if(ch == '+'){
                    montaToken(SN, str, '\0', SOMA);
                    return;
                }else if(ch == '-'){
                    montaToken(SN, str, '\0', SUBTRACAO);
                    return;
                }else if(ch == '*'){
                    montaToken(SN, str, '\0', MULTIPLICACAO);
                    return;
                }else if(ch == ','){
                    montaToken(SN, str, '\0', VIRGULA);
                    return;
                }else if(ch == ';'){
                    montaToken(SN, str, '\0', PONTO_VIRGULA);
                    return;
                }else{
                    error_lexico();
                }
                estado = 0;
                break;
            }
            case 33:
            {
                ch = getc(fp);
                if (ch == '&') {
                    estado = 34;
                    lexema[cont] = ch;
                    cont++;
                } else {
                    error_lexico();
                }
                break;
            }
            case 34:
            {
                montaToken(SN, "&&", '\0', AND);
                return;
            }
            case 35:
            {
                ch = getc(fp);
                if (ch == '!') {
                    estado = 36;
                    lexema[cont] = ch;
                    cont++;
                } else {
                    error_lexico();
                }
                break;
            }
            case 36:
            {
                montaToken(SN, "||", '\0', OR);
                return;

            }
        }
    }
}
