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

#endif
