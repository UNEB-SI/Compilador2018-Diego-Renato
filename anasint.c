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


