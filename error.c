#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "analex.h"
#include "error.h"

void error_message(int flag, int line_number)
{
    switch (flag)
    {
    case ESPERANDO_ID:
        printf("Esperado identificador na linha %d\n", line_number);
        break;
    case ESPERANDO_FECHA_PAREN:
        printf("Esperado ')' na linha %d\n", line_number);
        break;
    case ESPERANDO_PT:
        printf("';' Esperado na linha %d\n", line_number);
        break;
    case ESPERANDO_ABRE_PAREN:
        printf("Esperado '(' na linha %d\n", line_number);
        break;
    case ESPERANDO_CLOSE_KEY:
        printf("'}' Esperado na linha %d\n", line_number);
        break;
    case ESPERANDO_ABRE_KEY:
        printf("'{' Esperado na linha %d\n", line_number);
        break;
    case ESPERANDO_CMD:
        printf("Comando esperado na linha %d\n ", line_number);
        break;
    case ESPERANDO_IGUAL_SNG:
        printf("Esperado sinal '=' na linha %d", line_number);
        break;
    case NAO_INDENTIFICADO:
        printf("Simbolo nao identificado na linha %d\n", line_number);
        break;
    case ESPERANDO_TIPO:
        printf("Erro esperado tipo na linha %d\n", line_number);
        break;
    case RETORNO_ESPERADO:
        printf("Retorno esperado na linha %d\n", line_number);
        break;
    case ATRIBUICAO_INVALIDA:
        printf("Atribuicao invalida na linha %d\n", line_number);
        break;
    case ESPERANDO_VIRGULA:
        printf("Erro esperado ',' na linha %d\n", line_number);
        break;
    case ERRO_PASSAGEM_ARQUIVO:
        printf("Voce deve indicar um arquivo para ser analisado.");
        break;
    case ERRO_ARQUIVO_NAO_ENCONTRADO:
        printf("Arquivo nao encontrado!");
        break;
    case ERRO_NUMERO_FLOAT_FORMAT:
        printf("Esperado um número após ");
        break;
    case FINAL_DO_ARQUIVO:
        printf("Final do arquivo (%d\n)", line_number);
        break;
        exit(-1);
}