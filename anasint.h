#include "analex.h"


typedef struct{
    int escopo;
    char nome[20];
    char categoria[10];
    char tipo[10];
}simbolo;

typedef struct{
    int topo;
    simbolo simb;
}meuvetor;

void freevetor(meuvetor *v){
    for(int i=0; i<v.total;i++)
        free (v[i].simb);
}

void my_push(simb p){

}
