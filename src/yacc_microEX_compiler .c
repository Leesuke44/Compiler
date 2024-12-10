%{
#include "hdr.h"
char progName[100] = {'\0'};
struct symtab **varList; 
int varCount = 0, tmpCount = 0, labelCount=0;
%}

%union {
	int ival;
	float fval;
	struct symtab *symp;
	char* charp;
	int dataType;
	struct AssignInfo *assignInfo;
	struct ForloopInfo *forloopInfo;  
}

%token <symp> NAME 
%token <ival> INUMBER
%token <fval> FNUMBER
%token PROGRAM START END DECLARE AS INTEGER INTEGER_ARRAY FLOAT FLOAT_ARRAY FOR ENDFOR TO DOWNTO 
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%type <symp> variable assignment for_start
%type <dataType> data_type
%type <assignInfo> expression
%%

program_list:	PROGRAM program_name '\n'
		program '\n'	{}
	;

program_name:	NAME {strcpy(progName, $1->name); printf("START %s\n", progName); varList = malloc(sizeof(struct symtab*)*20);}
	;

program: 	START '\n'
		statement_list '\n' 
		END	{ printf("HALT %s\n", progName); }
	;

statement_list:	statement 	{}
	|	statement_list '\n' statement	{}
	;		
statement:	declaration ';'	{}
	|	assignment ';'	{}
	|	forloop		{}
	;

declaration:	DECLARE variable_list AS data_type	{
				int i=0;
				for(i;i<varCount;i++){
						varList[i]->dataType = $4;					
						if(varList[i]->isArray){
						if($4 == 0) printf("Declare %s, Integer_array, %d\n", varList[i]->name, varList[i]->arraySize);
						else if($4==1) printf("Declare %s, Float_array, %d\n", varList[i]->name, varList[i]->arraySize);
					}else{
						if($4 == 0)printf("Declare %s, Integer\n", varList[i]->name);
						else if($4 == 1) printf("Declare %s, Float\n", varList[i]->name);
					}
				}
				varCount = 0;
			}
	;

assignment:	NAME ':' '=' expression 	{
						//determine the data type of expression
                                                char type;
                                                if($1->dataType == 0) type='I';
                                                else type = 'F';
						 
						//output assembly
						printf("%c_STORE %s, %s\n", type, $4->name, $1->name);
						$1->value = $4->value;
						$$ = $1;	
					}
	|	NAME '['INUMBER ']' ':''=' expression 	{	
						//determine the data type of expression
                                                char type;
                                                if($1->dataType == 0) type='I';
                                                else type = 'F';
						
						//output assembly
						printf("%c_STORE %s, %s[%d]\n", type, $7->name, $1->name, $3);  
						$1->array[$3] = $7->value;
						$$ = $1;
					}
	|	NAME '[' NAME ']' ':''=' expression 	{
						//determine the data type of expression
                                                char type;
                                                if($1->dataType == 0) type='I';
                                                else type = 'F';
						
						//output assembly
						printf("%c_STORE %s, %s[%s]\n",type, $7->name, $1->name, $3->name);
						$1->array[(int)$3->value] = $7->value;
						$$ = $1;
					}
	;

expression:	expression '+' expression 	{
							$$ = malloc(sizeof(struct AssignInfo));
							//determine the data type of expression
                                                        char type;
                                                        if($1->dataType == 0) type='I';
                                                        else type = 'F';

                                                        //prepare a tmp register
                                                        char* tmpName = calloc(5, sizeof(char));
                                                        sprintf(tmpName, "T&%d", tmpCount);

                                                        //output assembly
                                                        printf("%c_ADD %s, %s, %s\n", type, $1->name, $3->name, tmpName);
                                                        $$->value = $1->value+$3->value; $$->dataType = $1->dataType; $$->name = tmpName;
                                                        tmpCount++;
						}
	|	expression '-' expression 	{		
							$$ = malloc(sizeof(struct AssignInfo));
							//determine the data type of expression
                                                        char type;
                                                        if($1->dataType == 0) type='I';
                                                        else type = 'F';

                                                        //prepare a tmp register
                                                        char* tmpName = calloc(5, sizeof(char));
                                                        sprintf(tmpName, "T&%d", tmpCount);

                                                        //output assembly
                                                        printf("%c_SUB %s, %s, %s\n", type, $1->name, $3->name, tmpName);
                                                        $$->value = $1->value-$3->value; $$->dataType = $1->dataType; $$->name = tmpName;
                                                        tmpCount++;
						}
	|	expression '*' expression 	{	
							$$ = malloc(sizeof(struct AssignInfo));
							//determine the data type of expression
                                                        char type;
                                                        if($1->dataType == 0) type='I';
                                                        else type = 'F';

                                                        //prepare a tmp register
                                                        char* tmpName = calloc(5, sizeof(char));
                                                        sprintf(tmpName, "T&%d", tmpCount);

                                                        //output assembly
                                                        printf("%c_MUL %s, %s, %s\n", type, $1->name, $3->name, tmpName);
                                                        $$->value = $1->value*$3->value; $$->dataType = $1->dataType; $$->name = tmpName;
                                                        tmpCount++;
						}
	|	expression '/' expression 	{
							if($3 == 0) yyerror("divide by zero");
							else{
								$$ = malloc(sizeof(struct AssignInfo));
								//determine the data type of expression
                                                       		char type;
                                                        	if($1->dataType == 0) type='I';
                                                        	else type = 'F';

                                                        	//prepare a tmp register
                                                        	char* tmpName = calloc(5, sizeof(char));
                                                        	sprintf(tmpName, "T&%d", tmpCount);
								
								//output assembly
								printf("%c_DIV %s, %s, %s\n", type, $1->name, $3->name, tmpName);
								$$->value = $1->value*$3->value; $$->dataType = $1->dataType; $$->name = tmpName;
								tmpCount++;	
							}
							
						}
	|	'-' expression %prec UMINUS 	{	
							$$ = malloc(sizeof(struct AssignInfo));
							//determine the data type of expression
							char type;
							if($2->dataType == 0) type='I';
							else type = 'F';

							//prepare a tmp register	
							char* tmpName = calloc(5, sizeof(char));
                                                        sprintf(tmpName, "T&%d", tmpCount);
									
							//output assembly
							printf("%c_UMINUS %s, %s\n",type, $2->name, tmpName);
							$$->value = -$2->value; $$->dataType=$2->dataType; $$->name = tmpName;		
							tmpCount++;	
						}	
	|	INUMBER	{ 		
					$$ = malloc(sizeof(struct AssignInfo));
								
					$$->value =(float)$1; $$->dataType = 0;
					int len = snprintf(NULL, 0, "%d", $1);
					$$->name = calloc(len + 1, sizeof(char));
					snprintf($$->name, len + 1, "%d", $1);
					
			}	
	|	FNUMBER	{
					$$ = malloc(sizeof(struct AssignInfo));
					$$->value = $1; $$->dataType = 1;
					
					int len = snprintf(NULL, 0, "%f", $1);
                                        $$->name = calloc(len + 1, sizeof(char));
                                        snprintf($$->name, len + 1, "%f", $1);
				}
	|	NAME	{$$ = malloc(sizeof(struct AssignInfo)); $$->value = $1->value; $$->dataType=1; $$->name=$1->name;}
	|	NAME '[' INUMBER ']' 	{
						$$ = malloc(sizeof(struct AssignInfo));

                                        	$$->value =$1->array[$3]; $$->dataType = $1->dataType;
                                        	int literalLen = snprintf(NULL, 0, "%d", $3);
						int varLen = strlen($1->name);
                                        	$$->name = calloc(varLen+literalLen+3, sizeof(char));
                                        	snprintf($$->name, varLen+literalLen+3, "%s[%d]\0", $1->name, $3);
					}
	|	NAME '[' NAME ']'	{
						$$ = malloc(sizeof(struct AssignInfo));

                                                $$->value =$1->array[(int)$3->value]; $$->dataType = $1->dataType;
                                                int biasLen = strlen($3->name);
                                                int varLen = strlen($1->name);
                                                $$->name = calloc(varLen+biasLen+3, sizeof(char));
                                                snprintf($$->name, varLen+biasLen+3, "%s[%s]\0", $1->name, $3->name);
					
					}
	;

forloop:	for_start  TO INUMBER ')' '\n'
		statement_list '\n'
		ENDFOR					{
								printf("INC %s\n", $1->name);
								printf("I_CMP %s, %d\n", $1->name, $3);
								printf("JLE lb&%d\n", labelCount++);
							}
	|	for_start  DOWNTO INUMBER ')' '\n'
                statement_list '\n'
                ENDFOR                                  {
								printf("DEC %s\n", $1->name);
                                                                printf("I_CMP %s, %d\n", $1->name, $3);
                                                                printf("JGE lb&%d\n", labelCount++);					
							}
	;

for_start:	FOR '(' assignment 	{	
								printf("lb&%d:    ", labelCount); 
								$$ = $3;	
					}

variable_list:	variable			{add_var($1); }
	|	variable_list ',' variable	{add_var($3); }
	;

variable:	NAME			{$1->isArray = false; $1->arraySize = 0; $$ = $1; }
	|	NAME '['INUMBER ']'	{$1->isArray = true; $1->arraySize = $3; $$ = $1; }
	;

data_type:	INTEGER	{$$ = 0; }
	|	FLOAT	{$$ = 1; }
	;



%%
/* look up a symbol table entry, add if not present */
struct symtab *
symlook(s)
char *s;
{
	char *p;
	struct symtab *sp;
	
	for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
		/* is it already here? */
		if(sp->name && !strcmp(sp->name, s))
			return sp;
		
		/* is it free */
		if(!sp->name) {
			sp->name = strdup(s);
			return sp;
		}
		/* otherwise continue to next */
	}
	yyerror("Too many symbols");
	exit(1);	/* cannot continue */
} /* symlook */

void add_var(struct symtab* var){
	varList[varCount++] = var;
}
