#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraysStrings.h"

#define BUFFERSIZE 4

//Part 1 - 2 points
	//write a function joinrev that takes 2 strings and returns a 3rd string that is th first string followed by the 2nd string reversed
	//Output should be:
	//Hello dlroW
	//Hint: joining the strings first and then reversing part of the joined string may be easier - ymmv
char* joinrev(char *a, char *b) {
	int len = strlen(a) + strlen(b);
	//char c[len];
	char* p;
	//p = c;
	p = (char*)malloc(len * sizeof(char));
	strcpy(p, a);
	strcat(p, b);
    printf("a: %s\n", p);
    int i = strlen(a);
	int j = len - 1;
	
	char temp;
	while(i <= j) {
		temp = p[j];
		p[j] = p[i];
		p[i] = temp;
		i++;
		j--;
	}
	return p;
}	

//Part 2 - 2 points 
	//write a function joinrev_generic that takes pointers to any two arrays, a typesize, and the number of elements in each array and does the same 
	//thing as joinrev except that it will return a void pointer and will work on any type of array. HINT - copy the code from part 1 and change the code so that the pointer arithmetic is done explicitly and the copies are done using memcpy and memmove as in the class example reverse3

void* joinrev_generic(void *a, void *b, int typeSize, int aElements, int bElements) {
	void* c;
	c =  malloc(typeSize*(aElements + bElements));
	memcpy(c, a, typeSize*aElements);
	char *left = (char*) b;
	char *right = (char*)b + (bElements-1)*typeSize;

	char temp[typeSize];
	
	while(left < right) {
		memcpy(temp,right,typeSize);
		memmove(right,left,typeSize);
		memcpy(left,temp,typeSize);
		left += typeSize;
		right -=typeSize;
	}
	
	memcpy(c + typeSize*aElements, b, typeSize*bElements);
	return c;
}
//Part 3 - 2 points
	//Write a function readTextAddBinary that takes two strings (filenames) and returns 0 if the function completes successfully. The function reads from the first filename,  a set of vectors, 2 per line and add them together and writes out a binary file (the second filename) with the new vectors (just the vectors - no spaces or other delimiters)
	//A test file is given to you along with the expected output - you can use the Unix diff function to compare your output with the expected output in testFiles
int readTextAddBinary(char *filename1, char *filename2) {
	char buffer[BUFFERSIZE];
	char *line = malloc(BUFFERSIZE);
	
	if(!line) {
		fprintf(stderr, "unable to allocate BUFFERSIZE bytes to line\n");
		return 1;
	}
	
	int lineSize = BUFFERSIZE;
	int lineno=0;
	
	int lineStrLen=0, bufferStrLen=0;
	
	FILE *fp = fopen(filename1,"r");
	
	if(!fp) {
		fprintf(stderr,"unable to open file \n");
		return 1;
	}
	
	FILE *fw = fopen(filename2, "wb");
	
	float a, b, c, x, y, z;
	while (fscanf(fp, "%f %f %f %f %f %f", &a, &b, &c, &x, &y, &z) == 6)  {
		vector v3 = vector_add(vector_init(a,b,c), vector_init(x,y,z));
		float va[] = {v3.x, v3.y, v3.z, v3.length};
		fwrite((void*) va, sizeof(float), 4, fw);
	}
	fclose(fp);
	fclose(fw);
	return 0;
}

	//Part 4 - 2 points
	//Write a function readBinaryNormText that takes two strings as input (filenames) and returns 0 if the function completes successfully. 
	//The first argument is a binary file of type produced in part 3. 
	//The function will read it in,  normalize a, and print out to the text file in argument 2, the components, x,y,z, and length separated by tabs (all as one big line)
	
int readBinaryNormText(char *filename1, char *filename2) {
	char buffer[BUFFERSIZE];
	char *line = malloc(BUFFERSIZE);
	
	if(!line) {
		fprintf(stderr, "unable to allocate BUFFERSIZE bytes to line\n");
		return 1;
	}
	
	int lineSize = BUFFERSIZE;
	int lineno=0;
	
	int lineStrLen=0, bufferStrLen=0;
	
	FILE *fp = fopen(filename1,"rb");
	if(!fp) {
		fprintf(stderr,"unable to open file \n");
		return 1;
	}
	
	FILE *fw = fopen(filename2, "w");
	if(!fw) {
		fprintf(stderr,"unable to open file \n");
		return 1;
	}
	
	float a, b, c, d;
	float vals[4] = {a, b, c, d};
	//printf("fscanf return: %i\n", fscanf(fp, "%f %f %f %f", &a, &b, &c, &d));
	//printf("%f %f %f %f\n", a, b, c, d);
	
	/*int length;
	fseek(fp, 0L, SEEK_END);
	element = ftell(fp);*/
	
	/*for(int i =0; i < element/(sizeof(float)*4); i++) {
	    printf("a: %f b: %f c: %f", a,b,c);
		vector v = vector_init(a,b,c);
		vector_normalize(&v);
		float normalize[] = {v.x, v.y, v.z, v.length};
		fwrite((void*) normalize, sizeof(float), 4, fw);
	}*/
	//fseek(fp, 0L, SEEK_SET);
	while (feof(fp) != 1)  {
		//fseek(fp, sizeof(float) * 4, SEEK_CUR);
		fread((void *) vals, sizeof(float), 4, fp);
		if (feof(fp) != 0)
			break;
		//fscanf(fp, "%f %f %f %f", &a, &b, &c, &d);
		//printf("a: %f b: %f c: %f \n", a,b,c);
		//printf("feof(fp): %i a: %f b: %f c: %f length: %f\n", feof(fp), vals[0],vals[1],vals[2], vals[3]);
		vector v = vector_init(vals[0],vals[1],vals[2]);
		vector_normalize(&v);
		float normalize[] = {v.x, v.y, v.z, v.length};
		fprintf(fw,"%f\t%f\t%f\t%f", v.x, v.y, v.z, v.length);
		if(feof(fp) == 0) {
			fprintf(fw,"\t");
		} 
		//fwrite((void*) normalize, sizeof(float), 4, fw);
	}
	fclose(fp);
	fclose(fw);
	return 0;
}	
	
	//Part 5 - 2 points
	//Write a function readNormTextWriteNormBinary that takes two strings as input (filenames) and returns 0 if the function completes successfully
	//. The first argument is the text file of type produced in part 4.  
	//Read in the line using fgets or fread. Either use realloc or check for the size of the file using fseek, ftell to allocate enough space to store the line. 
	//Then use strtok to parse the file. Print the results out to a binary file in the same format as the binary file produced in part 3. Remember to free the memory.
int readNormTextWriteNormBinary(char *filename1, char *filename2) {
	puts("hi......");
	FILE *fp = fopen(filename1,"r");
	if(!fp) {
		fprintf(stderr,"unable to open file \n");
		return 1;
	}
	
	FILE *fw = fopen(filename2,"wb");
	if(!fw) {
		fprintf(stderr,"unable to open file \n");
		return 1;
	}
	
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	
	char str[size];
	
	fgets(str, size , fp);
	
	const char s[2] = "\t";
	char* token;
	token = strtok(str, s);
	int sz = size/sizeof(float);
	
	float f[size];
	
	/*while(token != NULL) {
		sscanf(token, "%f\n", &f
	}*/
	printf("size: %i sz: %i sizeof float:%lu\n", size, sz, sizeof(float));
	for(int i = 0; i < sz; i++){
		if(token != NULL) {
			//printf("f[i]: %f\n", &f[i]);
			sscanf(token, "%f\n", &f[i]);
			token = strtok(NULL, s);
		}
	}
	//for(int i = 0; i < sz; i+=4) {
		fwrite((void*) f, sizeof(float), 40, fw);
	//}
	fclose(fp);
	fclose(fw);
	return 0;
}
