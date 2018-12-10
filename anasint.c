#include "anasint.h"

void freevetor(meuvetor *v){
    for(int i=0; i<v.total;i++)
        free (v[i].simb);
}

void my_push(simbolo p, int top){
   // if(top>=TAMMAX)erro;
    //else{
        v[++top].simbolo = p;
        v.top++;
    //}
}


void my_pop(){
    if(v.top>-1)
        free(v.[v.top]simbolo);
}

simbolo findSymbol(){
    do{

    }while(v[top].simbolo):
}

void check_var(){
    while(type()) {
        next_token();
        if(token.cat == ID) {
            while(next_token() && token.cat == OP) {
                next_token();
                if(!token.cat == ID) {
                    error_message(ERROR_SINTATICO, linha);
                }
            }
        }
    }
}

int check_declaration(){
}

int check_param(){
}

int check_function(){
}

int check_term(){
}
