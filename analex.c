#include "analex.h"
#include "error.h"

#define TAM 20

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
	printf("================ Abrindo arquivo ==============\n");
    codFonte = fopen("teste.txt", "r");
    if (codFonte == NULL) {
        printf("erro ao abrir o arquivo\n");
        exit(-1);
    }
    return codFonte;
}

Token verifyToken(FILE *codFonte) {
    char buffer[200], c;
    int estado = 0, coluna = 0, linha = 0, i = 0;
    memset(buffer, 0, 199);
    Token token;

    while(1) {
        switch(estado)
        {
            case 0:
//            	printf("\nBuffer: [%s]\n", buffer);
                c = getCaracter(codFonte, coluna, linha);
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
                } 
				else if(c == '\n'){
                    linha++;
                    coluna = 1;
                    break;
                }
				else if (feof(codFonte)){
                    error_message(FINAL_DO_ARQUIVO, -1);
                    break;
                }
                break;
            case 1:
//            	printf("Coluna: [1]\n", i);
            	c = getCaracter(codFonte, coluna, linha);
            	if(!(isalpha(c) || isdigit(c))) estado = 2;
                i++;
                concat(buffer, c);
                break;
            case 2:
//            	printf("Coluna: [2]\n", i);
                // FINAL Lexema
                ungetc(desconcat(buffer), codFonte);
                int tmp = isPalavraRes(buffer);
                if(tmp == -1){
                	printf("Coluna: [2-1][%c]\n", c);
                	return createToken(ID, buffer);

                } else {
                	printf("Coluna: [2-2]\n", i);
                    return createToken(PR, buffer);
                }
                return token;
                break;
            case 3:
//            	printf("Coluna: [3]\n", i);
                c = getCaracter(codFonte, coluna, linha);
                if(isdigit(c)){
                	concat(buffer, c);
                    i++;                    
                }else if (c ==  '.'){
                    i++;
                    concat(buffer, c);
                    estado = 4;
                }else 
                    estado = 5;
                break;
            case 4:
            	printf("Coluna: [4]\n", i);
                c = getCaracter(codFonte, coluna, linha);
                if(isdigit(c)){
                    i++;
                    concat(buffer, c);
                }else {
                    //volta um caracter do arquivo e vai para o estado 5
                    desconcat(buffer);
                    estado = 5;
                }
                break;
            case 5:
            	printf("Coluna: [5]\n", i);
                //FINAL
                desconcat(buffer);
                return createToken(3, buffer);
                break;
            case 6:
            	printf("Coluna: [6]\n", i);
                c = getCaracter(codFonte, coluna, linha);
                if( isdigit(c) ){
                    concat(buffer, c);
                    i++;
                }else {
                    estado = 7;
                    concat(buffer, c);
                    i++;
                }
                break;
            case 7:
            	printf("Coluna: [7]\n", i);
                //FINAL NUMERO REAL
                 return createToken(CT_R, buffer);
                break;
            case 8:
            	printf("Coluna: [8]\n", i);
                //FINAL MAIS
                return createToken(OP, buffer);
                break;
            case 9:
            	printf("Coluna: [9]\n", i);
                c = getCaracter(codFonte, coluna, linha);
                if(c == '='){
                    concat(buffer, c);
                    i++;
                    estado = 10;
                } else {
                    desconcat(buffer);
                    estado = 11;
                }
                break;
            case 10:
            	printf("Coluna: [10]\n", i);
                //FINAL MENOR IGUAL
                 return createToken(OP,buffer);
                break;
            case 11:
            	printf("Coluna: [11]\n", i);
                //FINAL MENOR 
                desconcat(buffer);
                break;
            case 12:
            	printf("Coluna: [12]\n", i);
                c = getCaracter(codFonte, coluna, linha);
                if(c == '='){
                    concat(buffer, c);
                    i++;
                    estado = 13;
                }else {
                    desconcat(buffer);
                    estado = 14;
                }
                break;
            case 13:
            	printf("Coluna: [13]\n", i);
                //FINAL MAIOROUIGUAL
                 return createToken(OP,buffer);
                break;
            case 14:
            	printf("Coluna: [14]\n", i);
                //FINAL MAIOR
                 return createToken(OP, buffer);
                break;
            case 15:
            	printf("Coluna: [15]\n", i);
                //FINAL MENOS
                 return createToken(OP,buffer);
                break;
            case 16:
            	printf("Coluna: [16]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if( c == 'a'){
                    concat(buffer, c);
                    i++;
                    estado = 17;
                }else if (c == 'o'){
                    concat(buffer, c);
                    i++;
                    estado = 21;
                }else if (c == 'n'){
                    concat(buffer, c);
                    i++;
                    estado = 25;
                } 
//				else error_message();
                break;
            case 17:
            	printf("Coluna: [17]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == 'n'){
                    concat(buffer, c);
                    i++;
                    estado = 18;
                }
//				else error_message();
                break;
            case 18:
            	printf("Coluna: [18]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == 'd'){
                    concat(buffer, c);
                    i++;
                    estado = 19;
                }
//				else error_message();
                break;
            case 19:
            	printf("Coluna: [19]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == '.'){
                    concat(buffer, c);
                    i++;
                    estado = 20;
                }
//				else error_message();
                break;
            case 20:
            	printf("Coluna: [20]\n", i);
                //FINAL .and.
                 return createToken(LOG, buffer);
                break;
            case 21:
            	printf("Coluna: [21]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == 'r'){
                    concat(buffer, c);
                    i++;
                    estado = 22;
                }
//				else error_message();
                break;
            case 22:
            	printf("Coluna: [22]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == '.'){
                    concat(buffer, c);
                    i++;
                    estado = 26;
                }
                break;
            case 23:
            	printf("Coluna: [23]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == 'o'){
                    concat(buffer, c);
                    i++;
                    estado = 24;
                }
//				else error_message();
                break;
            case 24:
            	printf("Coluna: [24]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == 't'){
                    concat(buffer, c);
                    i++;
                    estado = 25;
                }
//				else error_message();
                break;
            case 25:
            	printf("Coluna: [25]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == '.'){
                    concat(buffer, c);
                    i++;
                    estado = 20;
                }
//				else error_message();
                break;
            case 26:
            	printf("Coluna: [26]\n", i);
                //FINAL .OR.
                 return createToken(LOG, buffer);
                break;
            case 27:
            	printf("Coluna: [27]\n", i);
                //FINAL  .NOT.
                return createToken(OP, buffer);
                break;
            case 28:
            	printf("Coluna: [28]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == '='){
                    i++;
                    concat(buffer, c);
                    estado = 29;
                }else estado = 30;
                break;
            case 29:
            	printf("Coluna: [29]\n", i);
                //FINAL ==
                return createToken(OP, buffer);
                break;
            case 30:
            	printf("Coluna: [30]\n", i);
                //FINAL DIVISAO
                desconcat(buffer);
                return createToken(OP,buffer);
                break;
            case 31:
            	printf("Coluna: [31]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == '"')
                    estado = 32;
                i++;
                concat(buffer, c);
            case 32:
            	printf("Coluna: [32]\n", i);
                return createToken(CT_S, buffer);
                break;
            case 33:
            	printf("Coluna: [33]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == '/'){
                }else estado = 36;
                break;
            case 34:
            	printf("Coluna: [34]\n", i);
                c = getCaracter(codFonte,coluna,linha);
                if(c == '\n'){
                    estado = 35;
                }
                break;
            case 35:
            	printf("Coluna: [35]\n", i);
                estado = 0;
                break;
            case 36:
            	printf("Coluna: [36]\n", i);
                return createToken(OP, buffer);
                break;
            case 37:
            	printf("Coluna: [37]\n", i);
                break;
            case 38:
            	printf("Coluna: [38]\n", i);
                return createToken(OP, buffer);
                break;
            case 39:
            	printf("Coluna: [39]\n", i);
                c = getCaracter(codFonte, coluna, linha);
                concat(buffer, c);
				estado = 40;
				break;
            case 40:
            	printf("Coluna: [40]\n", i);
                c = getCaracter(codFonte, coluna, linha);
                if(c == '\''){
	                concat(buffer, c);
	                estado = 41;
				}else {
					//mensagem de erro
				}
				break;
            case 41:
            	printf("Coluna: [41]\n", i);
                return createToken(CT_CH, buffer);
				break;
	     	case 42:
            	printf("Coluna: [42]\n", i);
                return createToken(ABREPARENTESE, buffer);
				break;
	    	case 43:
         	   	printf("Coluna: [43]\n", i);
                return createToken(FECHAPARENTESE, buffer);
                system("pause");
				break;	
	   		case 44:
            	printf("Coluna: [44]\n", i);
                return createToken(ABRECOLCHETE, buffer);
				break;
	   		case 45:
            	printf("Coluna: [45]\n", i);
                return createToken(FECHACOLCHETE, buffer);
				break;
	      	case 46:
            	printf("Coluna: [46]\n", i);
                return createToken(VIRGULA, buffer);
				break;
	      	case 47:
            	printf("Coluna: [47]\n", i);
                return createToken(PONTO_VIRGULA, buffer);
				break;
            default:
            	printf("Coluna: [42]\n", i);
                error_message(FINAL_DO_ARQUIVO, linha);
        }//fim switch
    } //fim while

//    fclose(codFonte);
//    return token;
}


