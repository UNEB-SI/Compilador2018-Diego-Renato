#ifndef ANASINT_H
#define ANASINT_H

#include "analex.h"
#include "error.h"

#define TAMMAX 200

typedef struct{
    int escopo;
    char nome[20];
    char cat[10];
    char tipo[10];
} simbolo;

typedef struct{
    int topo;
    simbolo simb[200];
<<<<<<< HEAD
} meuvetor;
=======
}meuvetor;

void freevetor(meuvetor *v){
    for(int i=0; i<v.total;i++)
        free (v[i].simb);
}

void my_push(simb p){
>>>>>>> 8ef1ed92386f6498079c20d10cce9019f3dd2c1b

#endif
