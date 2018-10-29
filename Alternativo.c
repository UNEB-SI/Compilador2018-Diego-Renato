#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define TAM 20


char palavrasRes[][TAM] = { "bool", "call", "char", "display", "else", "endfor", "endif", "endproc",
                                "endprog", "endvar", "endwhile", "for", "fwd", "id", "if", "int","keyboard", "noparam",
                                "pl", "proc", "prog", "real", "return", "var", "while" };


typedef enum{
    ID, PR, OP, CT_I, CT_R, CT_CH,CT_S
}categoria;

typedef enum{
    MAIS,MENOS,MAIOR,MENOR,
    MENOROUIGUAL,MAIOROUIGUAL,
    ABREPARENTESE,FECHAPARENTESE,
    AND,OR,NOT,
}operador;

typedef  enum {
         BOOL, CALL, CHAR, DISPLAY,
         ELSE, ENDFOR, ENDIF, ENDPROC,
         ENDPROG, ENDVAR, ENDWHILE, FOR,
         FWD, ID, IF, INT,
         KEYBOARD, NOPARAM, PL, PROC, 
         PROG, REAL, RETURN, VAR, WHILE         
}palavra;

typedef struct {
	categoria cat;
	union{
		int n;
		float r;
		char s[10];
	}
}Token;

int isPalavraRes(char[] s);

Token new_token();

char getCaracter(FILE *p, int coluno,int linha);

int buscaBinaria(char *palavra, char palavrasRes[][TAM] , int ini, int fim)


int main(){
    FILE *codFonte;
    char c;
    char buffer[20];
    int estado,coluna=0,linha=0;
    Token token;
    codFonte=fopen("teste.txt", "r");
    if(codFonte == NULL){
        printf("erro ao abrir o arquivo\n");
        return -1;
    }
    i=0;
    estado =0;
    while(1){
    switch(estado)
        {
       case 0:
            c = getCaracter(codFonte,coluna,linha);
            buffer[i]=c;
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
                break;
            }
            break;
        case 1:
            c = getCaracter(codFonte,coluna,linha);
            if(!(isalnum(c))){
                estado = 2;
            }
            buffer[i] = c;
            i++;
            break;
        case 2:
            // FINAL
            ungetc(c,codFonte);
            if(isPalavraRes(buffer){
                //case seja palavra reservadoa identificar qual a palavra reservada

               }else {
                   strcpy(buffer,token.s);
                   print("<ID, %s>\n", token.s);
                }

            resetBuffer(buffer);
            estado = 0;
            break;
        case 3:
            c = getCaracter(codFonte,coluna,linha);
            if(isdigit(c)){
                buffer[i] = c;
                i++;
            }else if (c ==  '.'){
                buffer[i] = c;
                i++;
                estado = 4;
            }else {
                buffer[i] = c;
                i++;
                estado = 5;
            }
            break;
        case 4:
            c = getCaracter(codFonte,coluna,linha);
            if(isdigit(c)){
                buffer[i] = c;
                i++;
            }else {
                //volta dois caracteres do arquivo
                ungetc(c,codFonte);
                estado = 5;
            }
            break;
        case 5:
            ungetc(c,codFonte);
            token.cat = 3;

            pritnf("<CT_I,%s>",token.cat);
            printaToken();
            estado = 0;
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
            montaToken(buffer);
            printaToken();
            estado = 0;
            break;
        case 8:
            montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
            break;
        case 9:
            c = getCaracter(codFonte,coluna,linha);
            if(c == '='){
                buffer[i] = c;
                i++;
                estado = 10;
            }else {
                ungetc(codFonte);
                estado = 11;
            }
            break;
        case 10:
            montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
            break;
        case 11:
            montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
            break;
        case 12:
            c = getCaracter(codFonte,coluna,linha);
            if(c == '='){
                buffer[i] = c;
                i++;
                estado = 13;
            }else {
                ungetc(codFonte);
                estado = 14;
            }
            break;
        case 13:
             montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
            break;
        case 14:
             montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
            break;
        case 15:
             montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
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
            }else ERRO();
            break;
        case 17:
            c = getCaracter(codFonte,coluna,linha);
            if(c == 'n'){
                buffer[i] = c;
                i++;
                estado = 18;
            }else ERRO();
            break;
        case 18:
            c = getCaracter(codFonte,coluna,linha);
            if(c == 'd'){
                buffer[i] = c;
                i++;
                estado = 19;
            }else ERRO();
            break;
        case 19:
            c = getCaracter(codFonte,coluna,linha);
            if(c == '.'){
                buffer[i] = c;
                i++;
                estado = 20;
            }else ERRO();
            break;
        case 20:
            montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
            break;
        case 21:
            c = getCaracter(codFonte,coluna,linha);
            if(c == 'r'){
                buffer[i] = c;
                i++;
                estado = 22;
            }else ERRO();
            break;
        case 22:
            c = getCaracter(codFonte,coluna,linha);
            if(c == '.'){
                buffer[i] = c;
                i++;
                estado = 20;
            }else ERRO();
            break;
        case 23:
             c = getCaracter(codFonte,coluna,linha);;
            if(c == 'o'){
                buffer[i] = c;
                i++;
                estado = 24;
            }else ERRO();
            break;
        case 24:
             c = getCaracter(codFonte,coluna,linha);
            if(c == 't'){
                buffer[i] = c;
                i++;
                estado = 25;
            }else ERRO();
            break;
        case 25:
             c = getCaracter(codFonte,coluna,linha);
            if(c == '.'){
                buffer[i] = c;
                i++;
                estado = 20;
            }else ERRO();
            break;
        case 26:
             c = getCaracter(codFonte,coluna,linha);
            if(c == '='){
                buffer[i] = c;
                i++;
                estado = 27;
            }else {
                estado = 28;
                ungetc(codFonte);
            }
            break;
        case 27:
            montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
            break;
        case 28:
            montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
            break;
        case 29:
            montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
            break;
        case 30:
            montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
            break;
        case 31:
            c = getCaracter(codFonte,coluna,linha);
            if(c == '"'){
                estado = 32;
            }
            break;
        case 32:
            estado = 0;
            break;
        case 33:
            c = getCaracter(codFonte,coluna,linha);
            if(c == '/'){
                estado = 34;
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
            montaToken(buffer);
            printaToken();
            resetBuffer();
            estado = 0;
            break;
        }//fim switch


   } //fim while

    fclose(codFonte);
    return 0;
}


int isPalavraRes(char s[]){

}


char getCaracter(FILE *p, int *coluna,int *linha){
 char c;
 c = fgetc(p);
 if(c == '\n'){}
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

