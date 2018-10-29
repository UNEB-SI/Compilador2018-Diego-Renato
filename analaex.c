#include "analex.h"

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=')
        return (true);
    return (false);
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char *str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char *str)
{
    if (!strcmp(str, "bool") || !strcmp(str, "call") ||
        !strcmp(str, "char") || !strcmp(str, "display") ||
        !strcmp(str, "else") || !strcmp(str, "endfor") ||
        !strcmp(str, "endif") || !strcmp(str, "endproc") ||
        !strcmp(str, "endprog") || !strcmp(str, "endvar") ||
        !strcmp(str, "endwhile") || !strcmp(str, "for") ||
        !strcmp(str, "fwd") || !strcmp(str, "id") ||
        !strcmp(str, "if") || !strcmp(str, "int") ||
        !strcmp(str, "noparam") || !strcmp(str, "pl") ||
        !strcmp(str, "proc") || !strcmp(str, "prog") ||
        !strcmp(str, "real") || !strcmp(str, "return") ||
        !strcmp(str, "var") || !strcmp(str, "while"))
        return (true);
    return (false);
}

bool isLogic(char *str)
{
    if (!strcmp(str, "true") || !strcmp(str, "false"))
        return (true);
    return (false);
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(char *str)
{
    int i, len = strlen(str);

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && 
        str[i] != '3' && str[i] != '4' && str[i] != '5' && 
        str[i] != '6' && str[i] != '7' && str[i] != '8' && 
        str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char *str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && 
            str[i] != '3' && str[i] != '4' && str[i] != '5' && 
            str[i] != '6' && str[i] != '7' && str[i] != '8' && 
            str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

// Extracts the SUBSTRING.
char *subString(char *str, int left, int right)
{
    int i;
    char *subStr = (char *)malloc(
        sizeof(char) * (right - left + 2));

    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

// Parsing the input STRING. 
void parse_token(char *str)
{
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right)
    {
        if (isDelimiter(str[right]) == false)
            right++;

        if (isDelimiter(str[right]) == true && left == right)
        {
            if (isOperator(str[right]) == true)
                printf("'%c' IS AN OPERATOR\n", str[right]);

            right++;
            left = right;
        }
        else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right))
        {
            char *subStr = subString(str, left, right - 1);

            if (isKeyword(subStr) == true)
                printf("'%s' IS A KEYWORD\n", subStr);

            else if (isInteger(subStr) == true)
                printf("'%s' IS AN INTEGER\n", subStr);

            else if (isRealNumber(subStr) == true)
                printf("'%s' IS A REAL NUMBER\n", subStr);

            else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false)
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);

            else if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false)
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
            left = right;
        }
    }
    return;
}

void append(char *s, char c){
    int tam = strlen(s);
    s[tam] = c;
    s[tam + 1] = '\0';
}

token createToken(char type[], char buffer[]){
    token returnToken;
    returnToken.categories = type;
    if (validIdentifier(type))
    {
        strcpy(returnToken.categories, "IDENTIFIER");
        strcpy(returnToken.value, buffer);
    }
    else if(isKeyword(type)){
        strcpy(returnToken.categories, "RESERVED");
        strcpy(returnToken.value, buffer);
    }
    else if(isInteger(type)){
        strcpy(returnToken.categories, "CT_INT");
        strcpy(returnToken.value, buffer);
    }
    else if (isRealNumber(type))
    {
        strcpy(returnToken.categories, "CT_FLOAT");
        strcpy(returnToken.value, buffer);
    }
    else if (isLogic(type))
    {
        strcpy(returnToken.categories, "LOGICO");
        strcpy(returnToken.value, buffer);
    }
    else if(isOperator(type)){
        strcpy(returnToken.categories, "OPERADOR");
        strcpy(returnToken.value, buffer);
    }
    return returnToken;
}

int mapState(char sliceChar[], int *linha, int *coluna)
{
    if (isalpha(sliceChar)) return 1;
    else if (isdigit(sliceChar))
        return 3;
    else if (sliceChar == '.')
        return 36;
    else if (sliceChar == '=')
        return 7;
    else if (sliceChar == '>')
        return 10;
    else if (sliceChar == '<')
        return 9;
    else if (sliceChar == '\'')
        return 15;
    else if (sliceChar == '\"')
        return 23;
    else if (sliceChar == '\\')
        return 27;
    else if (sliceChar == '+')
        return 31;
    else if (sliceChar == '-')
        return 33;
    else if (sliceChar == '*')
        return 35;
    else if (sliceChar == '/')
        return 37;
    else if (sliceChar == '#')
        return 25;
    else if (sliceChar == '\n'){
        linha++; coluna = 1;
    } else if (sliceChar == ' '){
        coluna++;
    } else  {
        printf("Error: linha %i: coluna %i\n", linha, coluna);
        exit(1);
    }
}


token analex(FILE *fileWithString){
    int estado = 0;
    static int linha = 1, coluna = 1;
    char valor = -1;
    char buffer[200];
    memset(buffer, 0, 200);
    while(true){
        char sliceChar;
        switch(estado){
            case 0:
                sliceChar = getc(fileWithString);
                estado = mapState(sliceChar, &linha, &coluna);
                append(buffer, sliceChar);
                break;
            case 1:
                sliceChar = getc(fileWithString);
                coluna++;
                if (!(isalpha(sliceChar) || isdigit(sliceChar)))
                    estado = 2;
                append(buffer, sliceChar);
                break;
            case 2:
                //FINAL
                ungetc(sliceChar, fileWithString);
                if (validIdentifier(buffer) == true)
                    return createToken("IDENTIFIER", buffer);
                else return createToken("RESERVED", buffer);
            case 3:
                sliceChar = getc(fileWithString);
                coluna++;
                estado = mapState(sliceChar, &linha, &coluna);
                estado = mapState(sliceChar, &linha, &coluna);
                append(buffer, sliceChar);
                break;
            case 4:
                //FINAL
                ungetc(sliceChar, fileWithString);
                return createToken("CT_INT", buffer);
            case 5:
                sliceChar = getc(fileWithString);
                coluna++;
                if(isdigit(sliceChar)) estado = 38;
                else if (sliceChar == 'a' || sliceChar == 'o' || sliceChar == 'n')
                    estado = 14;
                else estado = -1;
                append(buffer, sliceChar);
                break;
            case 6:
                //FINAL
                ungetc(sliceChar, fileWithString);
                return createToken("CT_FLOAT", buffer);
            case 7:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == '=')
                    estado = 18;
                else estado = 8;
                append(buffer, sliceChar);
                break;
            case 8:
                //FINAL
                ungetc(sliceChar, fileWithString);
                return createToken("OPERADOR", "ATRIBUIÇÃO");
            case 9:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == '=')
                    estado = 16;
                else estado = 12;
                append(buffer, sliceChar);
                break;
            case 10:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == '=')
                    estado = 13;
                else estado = 11;
                append(buffer, sliceChar);
                break;
            case 11:
                //FINAL
                ungetc(sliceChar, fileWithString);
                return createToken("LOGICO", "MAIOR");
            case 12:
                //FINAL
                ungetc(sliceChar, fileWithString);
                return createToken("LOGICO", "MENOR");
                break;
            case 13:
                //FINAL
                return createToken("LOGICO", "MAIORIGUAL");
            case 14:
                ungetc(sliceChar, fileWithString);
                ungetc(buffer[strlen(buffer) - 1], fileWithString);
                buffer[strlen(buffer) - 1] = '\0';
                return createToken("CT_FLOAT", buffer);
            case 15:
                sliceChar = getc(fileWithString);
                coluna++;
                if (isalpha(sliceChar) || sliceChar == '\r' || sliceChar == 0)
                    estado = 20;
                append(buffer, sliceChar);
                break;
            case 16:
                //FINAL
                return createToken("LOGICO", "MENORIGUAL");
            case 17:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == '.')
                    estado = 22;
                else estado = -1;
                break;
            case 18:
                return createToken("LOGICO", "IGUAL");
            case 19:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == '.')
                    estado = 32;
                else estado = -1;
                break;
            case 20:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == '\'')
                    estado = 32;
                else estado = -1;
                append(buffer, sliceChar);
                break;
            case 21:
                return createToken("CT_CARACTER", buffer);
            case 22:
                return createToken("LOGICO", "AND");
            case 23:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == '\"')
                    estado = 24;
                append(buffer, sliceChar);
                break;
            case 24:
                return createToken("CT_STRING", buffer);
            case 25:
                return createToken("OPERADOR", "HASHTAG");
            case 26:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == '/')
                    estado = 27;
                else estado = 29;
                break;
            case 27:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == '\n')
                    estado = 0;
                break;
            case 28:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == 'd')
                    estado = 17;
                else if (sliceChar != 'n')
                    estado = -1;
                break;
            case 29:
                ungetc(sliceChar, fileWithString);
                return createToken("OPERADOR", "DIVISAO");
            case 30:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == '.')
                    estado = 34;
                else estado = -1;
                break;
            case 31:
                return createToken("OPERADOR", "MAIS");
            case 32:
                return createToken("LOGICO", "OR");
            case 33:
                return createToken("OPERADOR", "MENOS");
            case 34:
                return createToken("LOGICO", "NOT");
            case 35:
            case 36:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == 'a')
                    estado = 28;
                else if (sliceChar == 'o')
                    estado = 37;
                else if (sliceChar == 'n')
                    estado = 39;
                break;
            case 37:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == 'r')
                    estado = 19;
                else estado = -1;
                break;
            case 38:
                sliceChar = getc(fileWithString);
                coluna++;
                if (!isdigit(sliceChar))
                    estado = 6;
                else
                    append(buffer, sliceChar);
                break;
            case 39:
                sliceChar = getc(fileWithString);
                coluna++;
                if (sliceChar == 't')
                    estado = 30;
                else if (sliceChar != 'o')
                    estado = -1;
                break;
            default:
                printf("Error: linha %i: coluna %i\n", linha, coluna);
                exit(1);
        }
    }
}