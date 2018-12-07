#include <stdio.h>
#include <stdlib.h>
#include "analex.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Token newToken;
	FILE* codFonte = openFile();
	while (1) {
		newToken = verifyToken(codFonte);
		printf("\nResultado do Token: %d\n", newToken.cat);
	}
	return 0;
}
