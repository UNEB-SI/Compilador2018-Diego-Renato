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
