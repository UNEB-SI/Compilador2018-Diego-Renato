#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "analex.h"
#include "error.h"

void error_message(int flag, int line_number, int coluna_number)
{
    switch (flag)
    {
    case ERROR_STACK_FULL:
        printf("Error: endereco maior do que o permitido no vetor... \n", line_number, coluna_number);
        exit(1);
	case ERROR_STACK_EMPTY:
        printf("Error: endereco abaixo do permitido no vetor... \n", line_number, coluna_number);
        exit(1);
    case ESPERANDO_FECHA_APOSTROFO:
        printf("Error: esperava-se um apostrofo na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ESPERANDO_ENDVAR:
        printf("Error: esperava-se um endvar na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ERROR_SINTATICO:
        printf("Error: esperava-se que fosse um identificador na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ESPERANDO_ID:
        printf("Esperado identificador na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ESPERANDO_FECHA_PAREN:
        printf("Esperado ')' na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ESPERANDO_PT:
        printf("';' Esperado na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ESPERANDO_ABRE_PAREN:
        printf("Esperado '(' na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ESPERANDO_CLOSE_KEY:
        printf("'}' Esperado na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ESPERANDO_ABRE_KEY:
        printf("'{' Esperado na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ESPERANDO_CMD:
        printf("Comando esperado na linha [%d] e coluna [%d]\n ", line_number, coluna_number);
        exit(1);
    case ESPERANDO_IGUAL_SNG:
        printf("Esperado sinal '=' na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case NAO_INDENTIFICADO:
        printf("Simbolo nao identificado na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ESPERANDO_TIPO:
        printf("Erro esperado tipo na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case RETORNO_ESPERADO:
        printf("Retorno esperado na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ATRIBUICAO_INVALIDA:
        printf("Atribuicao invalida na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ESPERANDO_VIRGULA:
        printf("Erro esperado ',' na linha [%d] e coluna [%d]\n", line_number, coluna_number);
        exit(1);
    case ERRO_PASSAGEM_ARQUIVO:
        printf("Voce deve indicar um arquivo para ser analisado.");
        exit(1);
    case ERRO_ARQUIVO_NAO_ENCONTRADO:
        printf("Arquivo nao encontrado!");
        exit(1);
    case ERRO_NUMERO_FLOAT_FORMAT:
        printf("Esperado um n�mero ap�s ");
        exit(1);
    case FINAL_DO_ARQUIVO:
        printf("Final do arquivo ([%d])\n", line_number);
        exit(1);
	}
    exit(1);
}
