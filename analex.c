#include "analex.h"
#include "error.h"

#define TAM 20;


int estado = 0, coluna = 0, linha = 0, i = 0;
Token token;

char palavrasRes[][TAM] = {
    "bool", "call", "char", "display", "else", "endfor", "endif", "endproc",
    "endprog", "endvar", "endwhile", "for", "fwd", "id", "if", "int", "keyboard",
    "noparam", "pl", "proc", "prog", "real", "return", "var", "while"
};

int isPalavraRes(char *s){
    return buscaBinaria(s, palavrasRes, 0, TAM-1);
}

char getCaracter(FILE *p, int col, int linha){
    char c = fgetc(p);
    printf("%c", c);
    if (c == '\n') {
        linha++;
        col = 0;
    } else col++;
    return c;
}

void concat(char *string, char c) {
    int size = strlen(string);
    string[size] = c;
    string[size + 1] = '\0';
}

int buscaBinaria(char *palavra, char palavrasRes[][TAM], int ini, int fim){
    int cmp;
    cmp = strcmp(palavra, palavrasRes[(ini+fim)/2]);
    printf("Search Binary: [%d] [%s]\n", cmp, palavra);
    if(cmp == 0) //ACHOU
        return (ini + fim)/2;    
    if(cmp < 0) {
        // palavra menor que a metade
        if(ini >= fim) 
            return -1;
        return buscaBinaria(palavra, palavrasRes,ini , ((ini+fim)/2) -1);
    }
    if (cmp > 0){
        //palavra maior que a metade
        if(ini >= fim)
            return -1;
        return buscaBinaria(palavra,palavrasRes,((ini + fim)/2) +1, fim);
    }
}

char desconcat(char *string){
    int size = strlen(string);
    char c = string[size - 1];
    if(size > 0) {
    	string[size - 1] = '\0';
	}
    return c;
}

Token createToken(categoria type, void *buffer)
{
    Token returnToken;
    returnToken.cat = type;
    if (type == ID) {
        strcpy(returnToken.s, (char *) buffer);
    } else if (type == PR) {
        strcpy(returnToken.s, (char *) buffer);
    } else if (type == CT_I) {
        returnToken.n = atoi(buffer);
    } else if (type == CT_R) {
        returnToken.r = atof(buffer);
    } else if (type == LOG) {
        returnToken.n = atoi(buffer);
    } else if (type == OP) {
        strcpy(returnToken.s, (char *) buffer);
    }
    return returnToken;
}

void clearBuffer(char *buffer) {
	memset(buffer, 0, 199);
}

FILE* openFile() {
	FILE *codFonte;
	printf("================ Abrindo arquivo ==============\n\n");
    codFonte = fopen("teste.txt", "r");
    if (codFonte == NULL) {
        printf("erro ao abrir o arquivo\n");
        exit(-1);
    }
    return codFonte;
}

Token verifyToken(FILE *codFonte) {
    char buffer[200], c;
    memset(buffer, 0, 199);

    while(1) {
        switch(estado)
        {
            case 0:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                concat(buffer, c);                
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
                    clearBuffer(buffer);
                }else if (c == '\''){
                    estado = 39;
                } else if(c == '('){
                    estado = 42;
                }else if(c == ')'){
                    estado = 43;
                }else if(c == '['){
                    estado = 44;
                }else if(c == ']'){
                    estado = 45;
                }else if(c == ','){
                    estado = 46;
                }else if(c == ';'){
                    estado = 47;
                }else if(c == '\n') {
                    linha++; coluna = 0;
                    break;
                }else if (feof(codFonte)) error_message(FINAL_DO_ARQUIVO, -1, -1);
                break;
            case 1:
            	c = getCaracter(codFonte, coluna, linha);
                coluna++;
            	if(!(isalpha(c) || isdigit(c))) estado = 2;
                concat(buffer, c);
                break;
            case 2:
                // FINAL Lexema
                ungetc(desconcat(buffer), codFonte);
                int tmp = isPalavraRes(buffer);
                if(tmp == -1){
                	return createToken(ID, buffer);

                } else {
                    return createToken(PR, buffer);
                }
                return token;
            case 3:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(isdigit(c)) {
                	concat(buffer, c);             
                }else if (c ==  '.') {
                    concat(buffer, c);
                    estado = 4;
                }else estado = 5;
                break;
            case 4:
                c = getCaracter(codFonte, coluna, linha);
                if(isdigit(c)) {                    
                    concat(buffer, c);
                }else {
                    //volta um caracter do arquivo e vai para o estado 5
                    desconcat(buffer);
                    coluna--;
                    estado = 5;
                }
                break;
            case 5:
                //FINAL
                desconcat(buffer);
                return createToken(3, buffer);
            case 6:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if( isdigit(c) ){
                    concat(buffer, c);
                }else {
                    estado = 7;
                    concat(buffer, c);
                }
                break;
            case 7:
                //FINAL NUMERO REAL
                return createToken(CT_R, buffer);
                break;
            case 8:
                //FINAL MAIS
                return createToken(OP, buffer);
                break;
            case 9:
            	printf("Coluna: [9]\n", i);
                c = getCaracter(codFonte, coluna, linha);
                if(c == '=') {
                    concat(buffer, c);
                    coluna++;                    
                    estado = 10;
                } else {
                    desconcat(buffer);
                    coluna--;
                    estado = 11;
                }
                break;
            case 10:
                //FINAL MENOR IGUAL
                return createToken(OP,buffer);
            case 11:
                //FINAL MENOR 
                desconcat(buffer);
                coluna--;
                break;
            case 12:
                c = getCaracter(codFonte, coluna, linha);
                if(c == '=') {
                    concat(buffer, c);  
                    coluna++;
                    estado = 13;
                }else {
                    desconcat(buffer);
                    coluna--;
                    estado = 14;
                }
                break;
            case 13:
                //FINAL MAIOROUIGUAL
                return createToken(OP,buffer);
            case 14:
                //FINAL MAIOR
                return createToken(OP, buffer);
            case 15:
                //FINAL MENOS
                return createToken(OP,buffer);
            case 16:
                c = getCaracter(codFonte, coluna, linha);
                coluna++; 
                if( c == 'a') {
                    concat(buffer, c);
                    estado = 17;
                }else if (c == 'o') {
                    concat(buffer, c);
                    estado = 21;
                }else if (c == 'n'){
                    concat(buffer, c);
                    estado = 25;
                } 
				else error_message(ESPERANDO_ID, linha, coluna);
                break;
            case 17:
                c = getCaracter(codFonte, coluna, linha);
                if(c == 'n'){
                    concat(buffer, c);
                    estado = 18;
                }
				else error_message(ESPERANDO_ID, linha, coluna);
                break;
            case 18:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == 'd') {
                    concat(buffer, c);
                    estado = 19;
                }
                else error_message(ESPERANDO_ID, linha, coluna);
                break;
            case 19:
            	printf("Coluna: [19]\n", i);
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == '.') {
                    concat(buffer, c);                    
                    estado = 20;
                }
                else error_message(ESPERANDO_ID, linha, coluna);
                break;
            case 20:
                //FINAL .and.
                return createToken(LOG, buffer);
            case 21:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == 'r') {
                    concat(buffer, c);                    
                    estado = 22;
                }
				else error_message(ESPERANDO_ID, linha, coluna);
                break;
            case 22:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == '.') {
                    concat(buffer, c);                    
                    estado = 26;
                }
                break;
            case 23:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == 'o') {
                    concat(buffer, c);                    
                    estado = 24;
                }
                else error_message(ESPERANDO_ID, linha, coluna);
                break;
            case 24:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == 't') {
                    concat(buffer, c);                    
                    estado = 25;
                }
                else error_message(ESPERANDO_ID, linha, coluna);
                break;
            case 25:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == '.') {
                    concat(buffer, c);                    
                    estado = 20;
                }
				else error_message(ESPERANDO_ID, linha, coluna);
                break;
            case 26:
                //FINAL .OR.
                return createToken(LOG, buffer);
            case 27:
                //FINAL  .NOT.
                return createToken(OP, buffer);
            case 28:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == '=') {                    
                    concat(buffer, c);
                    estado = 29;
                }else estado = 30;
                break;
            case 29:
                //FINAL ==
                return createToken(OP, buffer);
            case 30:
                //FINAL DIVISAO
                desconcat(buffer);
                coluna--;
                return createToken(OP, buffer);
            case 31:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == '"') estado = 32;
                concat(buffer, c);
                break;
            case 32:
                return createToken(CT_S, buffer);
            case 33:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == '/') {
                }else estado = 36;
                break;
            case 34:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == '\n') {
                    estado = 35;
                }
                break;
            case 35:
                estado = 0;
                break;
            case 36:
                return createToken(OP, buffer);
            case 37:
                break;
            case 38:
                return createToken(OP, buffer);
            case 39:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                concat(buffer, c);
				estado = 40;
				break;
            case 40:
                c = getCaracter(codFonte, coluna, linha);
                coluna++;
                if(c == '\'') {
	                concat(buffer, c);
	                estado = 41;
				}else {
					error_message(ESPERANDO_FECHA_APOSTROFO, linha, coluna);
				}
				break;
            case 41:
                return createToken(CT_CH, buffer);
	     	case 42:
                return createToken(ABREPARENTESE, buffer);
	    	case 43:
                return createToken(FECHAPARENTESE, buffer);
	   		case 44:
                return createToken(ABRECOLCHETE, buffer);
	   		case 45:
                return createToken(FECHACOLCHETE, buffer);
	      	case 46:
                return createToken(VIRGULA, buffer);
	      	case 47:
                return createToken(PONTO_VIRGULA, buffer);
            default:
                error_message(FINAL_DO_ARQUIVO, linha);
        }//fim switch
    } //fim while
    fclose(codFonte);
}


