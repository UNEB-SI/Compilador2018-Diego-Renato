#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "analex.h"
#include "error.h"

#define TAM 20

char palavrasRes[][TAM] = {
    "bool", "call", "char", "display", "else", "endfor", "endif", "endproc",
    "endprog", "endvar", "endwhile", "for", "fwd", "id", "if", "int", "keyboard",
    "noparam", "pl", "proc", "prog", "real", "return", "var", "while"
};

int isPalavraRes(char s[]){
    //VERIFICA SE A STRING S É UMA PALAVRA RESERVADA
    return buscaBinaria(s, palavrasRes[], 0, TAM);
}

char getCaracter(FILE *p, int *coluna,int *linha){
    char c;
    c = fgetc(p);
    if(c == '\n'){
        linha++;
        col = 0;
    }else col++;
    return c;
}

int buscaBinaria(char *palavra, char palavrasRes[][TAM], int ini, int fim){
    int cmp;
    cmp = strcmp(palavra, palavrasRes[(ini+fim)/2]);
    if(cmp == 0){
        //ACHOU
        return (ini + fim)/2;
    }
    if(cmp < 0){
        // palavra menor que a metade
        if(ini > fim) return -1;
        return buscaBinaria(palavra, palavrasRes,ini , ini+fim -1);
    }
    if (cmp > 0){
        //palavra maior que a metade
        if(ini >= fim)
            return -1;
        return buscaBinaria(palavra,palavrasRes,(ini + fim)/2 +1,fim);
    }
}

Token  return createToken(categoria type, void *buffer)
{
    Token returnToken;
    returnToken.cat = type;
    if (type == ID)
    {
        strcpy(returnToken.cat, ID);
        strcpy(returnToken.s, (char *) buffer);
    }
    else if (type == PR)
    {
        strcpy(returnToken.cat, PR);
        strcpy(returnToken.s, (char *) buffer);
    }
    else if (type == CT_I)
    {
        strcpy(returnToken.cat, CT_I);
        strcpy(returnToken.n, (int *) buffer);
    }
    else if (type == CT_R)
    {
        strcpy(returnToken.cat, CT_R);
        strcpy(returnToken.r, (float *) buffer);
    }
    else if (type == LOG)
    {
        strcpy(returnToken.cat, LOG);
        strcpy(returnToken.n, (int *) buffer);
    }
    else if (type == OP)
    {
        strcpy(returnToken.cat, OP);
        strcpy(returnToken.s, (char *) buffer);
    }
    return returnToken;
}

void resetBuffer(int *i) {
    *i = 0;
}

Token verifyToken()
{
    FILE *codFonte;
    char c;
    char buffer[20];
    int estado, coluna=0, linha=0;
    Token token;
    codFonte=fopen("teste.txt", "r");
    if(codFonte == NULL){
        printf("erro ao abrir o arquivo\n");
        return -1;
    }
    int i = 0;
    estado = 0;
    while(1){
        switch(estado)
        {
            case 0:
                c = getCaracter(codFonte,coluna,linha);
                buffer[i] = c;
                if(isalpha(c)){
                    estado = 1;
                }else if(isdigit(c)){
                    estado = 3;
                }else if (c == '<'){
                    estado = 9;
                }else if (c == '>'){
                    estado = 12;
                }else if (c == '.'){
                    estado = 16;
                }else if (c == '='){
                    estado = 28;
                }else if (c == '-'){
                    estado = 15;
                }else if (c == '+'){
                    estado = 8;
                }else if (c == '"'){
                    estado = 31;
                }else if (c == '#'){
                    estado = 38;
                }else if (c == '/'){
                    estado = 33;
                }else if (c == '*'){
                    estado = 37;
                }else if (c == ' '){
                    estado = 0;
                }else if (c = '\''){
                    estado =39;
                }else if (feof(codFonte)){
                    error_message(FINAL_DO_ARQUIVO, -1);
                    break;
                }
                break;
            case 1:
                c = getCaracter(codFonte,coluna,linha);
                if(!(isalnum(c))){
                    estado = 2;
                }
                i++;
                buffer[i] = c;
                break;
            case 2:
                // FINAL
                ungetc(c,codFonte);
                int tmp = isPalavraRes(buffer); 
                if(tmp){
                    //case seja palavra reservadoa identificar qual a palavra reservada
                     return createToken(tmp, buffer);
                }else {
                     return createToken(0, buffer);
                }
                return token;
                break;
            case 3:
                c = getCaracter(codFonte,coluna,linha);
                if(isdigit(c)){
                    i++;
                    buffer[i] = c;
                }else if (c ==  '.'){
                    i++;
                    buffer[i] = c;
                    estado = 4;
                }else 
                    estado = 5;
                break;
            case 4:
                c = getCaracter(codFonte,coluna,linha);
                if(isdigit(c)){
                    i++;
                    buffer[i] = c;
                }else {
                    //volta um caracter do arquivo e vai para o estado 5
                    ungetc(c,codFonte);
                    estado = 5;
                }
                break;
            case 5:
                   //FINAL
                ungetc(c,codFonte);
                return createToken(3,buffer);
                break;
            case 6:
                c = getCaracter(codFonte,coluna,linha);
                if( isdigit(c) ){
                    buffer[i] = c;
                    i++;
                }else {
                    estado = 7;
                    buffer[i] = c;
                    i++;
                }
                break;
            case 7:
                //FINAL NUMERO REAL
                 return createToken(CT_R,buffer);
                break;
            case 8:
                //FINAL MAIS
                return createToken(OP,buffer);
                break;
            case 9:
                c = getCaracter(codFonte,coluna,linha);
                if(c == '='){
                    buffer[i] = c;
                    i++;
                    estado = 10;
                } else {
                    ungetc(codFonte);
                    estado = 11;
                }
                break;
            case 10:
                //FINAL MENOR IGUAL
                 return createToken(OP,buffer);
                break;
            case 11:
                //FINAL MENOR 
                ungetc(c,codFonte);
                break;
            case 12:
                c = getCaracter(codFonte,coluna,linha);
                if(c == '='){
                    buffer[i] = c;
                    i++;
                    estado = 13;
                }else {
                    ungetc(c, codFonte);
                    estado = 14;
                }
                break;
            case 13:
                //FINAL MAIOROUIGUAL
                 return createToken(OP,buffer);
                break;
            case 14:
                //FINAL MAIOR
                 return createToken(OP, buffer);
                break;
            case 15:
                //FINAL MENOS
                 return createToken(OP,buffer);
                break;
            case 16:
                c = getCaracter(codFonte,coluna,linha);
                if( c == 'a'){
                    buffer[i] = c;
                    i++;
                    estado = 17;
                }else if (c == 'o'){
                    buffer[i] = c;
                    i++;
                    estado = 21;
                }else if (c == 'n'){
                    buffer[i] = c;
                    i++;
                    estado = 25;
                }else error_message();
                break;
            case 17:
                c = getCaracter(codFonte,coluna,linha);
                if(c == 'n'){
                    buffer[i] = c;
                    i++;
                    estado = 18;
                }else error_message();
                break;
            case 18:
                c = getCaracter(codFonte,coluna,linha);
                if(c == 'd'){
                    buffer[i] = c;
                    i++;
                    estado = 19;
                }else error_message();
                break;
            case 19:
                c = getCaracter(codFonte,coluna,linha);
                if(c == '.'){
                    buffer[i] = c;
                    i++;
                    estado = 20;
                }else error_message();
                break;
            case 20:
                //FINAL .and.
                 return createToken(LOG, buffer);
                break;
            case 21:
                c = getCaracter(codFonte,coluna,linha);
                if(c == 'r'){
                    buffer[i] = c;
                    i++;
                    estado = 22;
                }else error_message();
                break;
            case 22:
                break;
            case 23:
                if(c == 'o'){
                    buffer[i] = c;
                    i++;
                    estado = 24;
                }else error_message();
                break;
            case 24:
                c = getCaracter(codFonte,coluna,linha);
                if(c == 't'){
                    buffer[i] = c;
                    i++;
                    estado = 25;
                }else error_message();
                break;
            case 25:
                c = getCaracter(codFonte,coluna,linha);
                if(c == '.'){
                    buffer[i] = c;
                    i++;
                    estado = 20;
                } else error_message();
                break;
            case 26:
                //FINAL .OR.
                 return createToken(LOG, buffer);
                break;
            case 27:
                //FINAL .not.
                 return createToken(LOG, buffer);
                break;
            case 28:
                  c = getCaracter(codFonte,coluna,linha);
                if(c == '='){
                    buffer[i] = c;
                    i++;
                    estado = 29;
                }else {
                    estado = 30;
                    ungetc(codFonte);
                }
                break;
            case 27:
                 return createToken(buffer);
                printaToken();
                resetBuffer();
                estado = 0;
                break;
            case 28:
                 return createToken(buffer);
                printaToken();
                resetBuffer();
                estado = 0;
                break;
            case 29:
            case 32:
                 return createToken(CT_S, buffer);
                break;
            case 33:
                c = getCaracter(codFonte,coluna,linha);
                if(c == '/'){
                }else estado = 36;
                break;
            case 34:
                c = getCaracter(codFonte,coluna,linha);
                if(c == '\n'){
                    estado = 35;
                }
                break;
            case 35:
                estado = 0;
                break;
            case 36:
                 return createToken(OP, buffer);
                break;
            case 37:
                 return createToken(OP, buffer);
                break;
            case 38:
                 return createToken(OP, buffer);
                break;
            case 39:
                c = getCaracter(codFonte,coluna,linha);
                estado = 40;
            case 40:
                 c = getCaracter(codFonte,coluna,linha);
                estado = 41;
            case 41:
                 return createToken(CT_CH, buffer);
            default:
                error_message(FINAL_DO_ARQUIVO, linha);
        }//fim switch
    } //fim while

    fclose(codFonte);
    return 0;
}

