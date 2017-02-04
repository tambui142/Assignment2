//other includes are necessary
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vectors.h"

//fill in the parameters and return type
char* joinrev(char *a, char *b);
void* joinrev_generic(void *a, void *b, int typeSize, int aElements, int bElements);
int readTextAddBinary(char *filename1, char *filename2);
int readBinaryNormText(char *filename1, char *filename2);
int readNormTextWriteNormBinary(char *filename1, char *filename2);
//wc();
