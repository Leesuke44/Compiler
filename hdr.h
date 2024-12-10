/*
 *	Header for calculator program
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define NSYMS 20	/* maximum number of symbols */
#define ARRSIZE 100
struct symtab {
	char *name;
	int dataType;
	float value;
	
	bool isArray;
	int arraySize;
	float array[ARRSIZE];
	
} symtab[NSYMS];

struct AssignInfo{
	char* name;
	int dataType;
	float value;	
};

struct ForloopInfo{
	char* name;
	int limit;
};

struct symtab *symlook();

void add_var();


