#include <stdio.h>
#include <stdlib.h>
#include "analex.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Token newToken;
	newToken = verifyToken();
	printf("Resultado do Token: %i\n", newToken.s);
	return 0;
}
