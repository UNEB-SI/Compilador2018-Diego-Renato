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
} meuvetor;



//void my_push(simbolo p){
//>>>>>>> 8ef1ed92386f6498079c20d10cce9019f3dd2c1b

#endif
