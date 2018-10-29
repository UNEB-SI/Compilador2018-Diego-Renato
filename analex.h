#ifndef ANALEX_H
#define ANALEX_H

#include <stdbool.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct token{
    char categories[200];
    char value[200];
} token;
