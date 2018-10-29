#ifndef ANALEX_H
#define ANALEX_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

// CATEGORIA
typedef enum{ ID, PR, OP, CT_I, CT_R, CT_CH, CT_S, LOG } categoria;

// OPERADORES
typedef enum{ MAIS, MENOS, MAIOR, MENOR, MENOROUIGUAL, MAIOROUIGUAL, ABREPARENTESE, FECHAPARENTESE, AND, OR, NOT } operador;

// PALAVRAS RESERVADAS
typedef  enum { BOOL, CALL, CHAR, DISPLAY,ELSE, ENDFOR, ENDIF, ENDPROC, ENDPROG, ENDVAR, ENDWHILE, FOR,
    FWD, ID, IF, INT,KEYBOARD, NOPARAM, PL, PROC,PROG, REAL, RETURN, VAR, WHILE } palavra;

// ESTRUTURA DO TOKEN
typedef struct {
    categoria cat;
    union{ int n; float r; char s[10]; };
} Token;


// ASSINATURAS DE FUNÇÕES
int isPalavraRes(char[] s);

Token createToken(categoria type, void *buffer);

Token new_token();

char getCaracter(FILE *p, int coluno,int linha);

int buscaBinaria(char *palavra, char palavrasRes[][TAM] , int ini, int fim);