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
 return(token.cat == PR && (token.cat == INT || token.cat == REAL || token.cat == CHAR
                             || token.cat == BOOL));
}

void var(){
}

bool declaration(){
}

bool param(){
}

bool function(){
}

bool procedure(){
}

bool factor(){
}

bool term(){
}

bool simple_expr(){
}

bool op_rel(){
}

bool expr(){
}

bool attribution(){
}

bool cmd(){
}

void prog(){
}
