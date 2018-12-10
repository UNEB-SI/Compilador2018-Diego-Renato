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

void newId(int escopo, char *nome, char *tipo, char *categoria) {
    simbolo criado;
    criado.escopo = escopo;
    strcpy(criado.nome, nome);
    strcpy(criado.cat, categoria);
    strcpy(criado.tipo, tipo);
}

void my_pop(){
    if(v.top>-1)
        free(v.[v.top]simbolo);
}

simbolo findSymbol(simbolo t){
    int tmp = -1;
    int atual = v.top;
    while(1){
        tmp = strcmp(t.nome, v[atual].nome) && v[atual].escopo == t.escopo
            && strcmp(v[atual].categoria, t.categoria) && strcmp(v[atual].tipo, t.tipo);
        if(tmp == 0)return atual;
        if(atual == -1)return -1;
   }
}

bool type(){
 return(token.cat == PR && (token.cat == INT || token.cat == REAL || token.cat == CHAR || token.cat == BOOL));
}

int check_var(){
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
