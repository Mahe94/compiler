%{ 

	#include<stdio.h> 
	#include<string.h>

void yyerror(const char *str)
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

%} 

%right '='
%left '+' '-'
%left '*' '/'
%token DIGIT PLUS END
	 
%% 

start : expr '\n'      {printf("%d\n",$$); return 1;} 
    ; 

expr: expr '+' expr	{$$ = $1 + $3;} 
    | expr '-' expr	{$$ = $1 - $3;} 
    | expr '*' expr	{$$ = $1 * $3;}
    | expr '/' expr	{$$ = $1 / $3;}
    | '(' expr ')'	{$$ = $2;}
    | DIGIT             {$$ = $1;} 
    ; 

%%     
