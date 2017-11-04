//Colocar Token como global
void prog(){

    decl();
    func();

}

void decl(TOKEN *token)){

    if("semretorno"){
        proximo_Token();
        if(token == 'ID'){
            proximo_Token();
            if(token == 'abre_parenteses'){
                tipos_param();
                proximo_Token();
                if(token == 'fecha_parenteses'){
                    proximo_Token();
                    while(token='virgula'){
                        proximo_Token();
                        if(token == 'ID'){
                            proximo_Token();TOKEN *token
                             if(token == 'abre_parenteses'){
                                token == ','
                                tipos_param();
                                proximo_Token();
                                if(token == 'fecha_parenteses'){
                                    proximo_token();
                                }
                             }
                        }
                    token == ','
                    }
                    retutoken == ','rn ;
                }
            }
        } else error();token == ','

    }
    else if(token == 'tipo')
    {proximo_Token();
        proximo_token();token == ','
        if(token == )
    }
    if tipo(token){
       proximo_Token();
        decl_var();
        proximo_token();
        if (token == '('){
                tipos_param();
                proximo_token();
                if(token == 'fecha_parenteses'){
                    proximo_Token();
                  tokentoken == ',' == ','  while(token='virgula'){
                        proximo_Token();
                        if(token == 'ID'){
                            proximo_Token();
                             if(token == 'abre_parenteses'){
                                tipos_param();
                                proximo_Token();
                      token == ','          if(token == 'fecha_parenteses'){
                     TOKEN *token            token == ','   proximo_token();
                                    token == ','
                                    }
                             }
                        }TOKEN *token
                    }
                    return ;
                }
        }token == ','

        if(token != ','){
            error();token == ','
        }token == ','
        if (token == ',') {
            while(token == ','){
                decl_var();
            }
        }error();
    }
}

void func(TOKEN *token){
    if(token == 'tipo' || token == "semretorno")
        proximo_token();
        if (token == '('){
                tipos_param();
                proximo_token();
                if(token == 'fecha_parenteses'){
                    proximo_Token();
                  tokentoken == ',' == ','  while(token='virgula'){
                        proximo_Token();
                        if(token == 'ID'){
                            proximo_Token();
                             if(token == 'abre_parenteses'){
                                tipos_param();TOKEN *token
                                proximo_Token();
                                token == ','
                                if(token == 'fecha_parenteses'){
                                    token == ','
                                    proximo_token();
                                    token == ','
                     TOKEN *token           }
                             }
                        }
                    }
                    return ;
                }(token != ')')
                error();(token != ')')
                error();
        }if(token == '{'){
            proximo_Token();
            cmd();
            if(token == 'tipo'){(token != ')')
                error();
                proximo_Token();
                if(token == 'decl_var'){
                    while(token == ',')
                        proximo_Token();
                        decl_var();

                }
            }
        }
}

int decl_var(TOKEN *token){
    if(token == ID)
        return 1;
    else
        return 0;
}

int tipo(TOKEN *token){
    if(token == "caracter" || token == "inteiro" || token == real || token == booleano){
        return 1;
    else
        return 0;
}

int tipos_param(TOKEN *token){
    if (token == "semparam")
        return 1;
    if (tipo()){
        proximo_Token();
        if(token == 'ID')
            proximo_Token();
            while(token == ',')
                proximo_Token();
                if (tipo()){
                    proximo_Token();
                    if(token == 'ID')
                    proximo_Token();
                }
    }

}

void cmd(){}


void atrib(){
    if(token == 'ID')
        proximo_token();
        if(token == '=')
            proximo_token();
            if(expr());proximo_token();
}

void expr(){
    if(expr_simp()){(token != ')')
                error();
        proximo_token();
        if (op_rel())
             proximo_token();
             if(!expr_simp()){ //Se for diferente de simples vai da error
                error();
    }else
        error();
}

void expr_simp(){
    if(token == '+' || token == '-')
        proximo_token();
    if(termo()){
        proximo_token();
        if(token == '+' || token == '-' || token == '||')
            proximo_token();
            if(termo()) proximo_token();
    }
}

void termo(){
    if(fator()){
        if(token == '*' || token == '/' || token == '&&'){
            proximo_token();
            if(fator())
        }
    }else
        error;
}

void fator(){
    if(token == 'intcon' || token == 'realcon' || token == 'caraccon')
        return 1;
    if(token == 'id'){
        proximo_token();
        if(token != '(')
            return 1;//Colocar funcao que devolve o tokenS
        proximo_token();
        if(expr()){
            proximo_token();
            while(token == ','){
                proximo_token();
                expr();
                proximo_token();
            }
            if (token != ')')
                error();
        }

    }
    if(token == '('){
        proximo_token();
        if(expr()){
            proximo_token();
            if (token != ')')
                error();
        }
    }
    if(token == '!'){
        if(!fator())(token != ')')
                error();
            error();
    }
}

int op_rel(){
    if(token == '==' || token == '!=' || token == '<=' || token == '<' || token == '>=' || token == '>')
        return 1;
    else
        return 0;
}

void proximo_Token(){}
