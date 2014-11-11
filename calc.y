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

%token DIGIT PLUS MINUS MUL DIV MOD LEFT RIGHT END 
	 
%% 

start : expr END           {printf("%d\n", $1); return 1;} 
    ; 

expr: expr PLUS expr	{$$ = $1 + $3;} 
    | expr MINUS expr	{$$ = $1 - $3;} 
    | expr MUL expr	{$$ = $1 * $3;}
    | expr DIV expr	{$$ = $1 / $3;}
    | expr MOD expr	{$$ = $1 -(($1/$3)*$3);}
    | LEFT expr RIGHT	{$$ = $2;}
    | DIGIT             {$$ = $1;} 
    ; 

%%     
