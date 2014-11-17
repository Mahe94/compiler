%{ 

	#include<stdio.h> 
	#include<string.h>
	
%} 

%union {
	char character;
	int integer;
};

%token <integer> DIGIT 
%token <character> OP 

%type <integer> expr
	 
%% 

start : expr '\n'      {;} 
    ; 

expr: expr OP expr { ;}
    | '(' expr ')'	{$$ = $2;}
    | DIGIT             {$$ = $1;} 
    ; 

%%     

#include "lex.yy.c"

yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
 
int yywrap()
{
        return 1;
} 

main() 
{ 
    yyparse(); 
} 

