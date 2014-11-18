%{ 

	#include<stdio.h> 
	#include<string.h>
	
	struct node {
		char character;
		int integer;
		struct node *right, *left;
	};
	
	void inorder(struct node *n);	
%} 

%union {
	struct node *n;	
}

%right '='
%left '+' '-'
%left '*' '/'
%token <n> DIGIT  

%type <n> expr
	 
%% 

start : expr '\n'     	{inorder($1); return 0;} 
    ; 

expr:	expr '+' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->character='+';
			$$->right=$3;
			$$->left=$1;}
    	|expr '-' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->character='-';
    			$$->right=$3;
			$$->left=$1;}
	|expr '*' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->character='*';
			$$->right=$3;
			$$->left=$1;}
	|expr '/' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->character='/';
			$$->right=$3;
			$$->left=$1;}		       
	| '(' expr ')'	{$$=$2;}
	| DIGIT             {$$=$1;} 
; 

%%     

#include "lex.yy.c"

int leaf(struct node *n) {
	if(n->right==NULL && n->left==NULL)
		return 1;
	else
		return 0;
}
void inorder(struct node *n) {
	if(leaf(n)) {
		printf("%d ", n->integer);
	}
	else {
		printf("( ");
		inorder(n->left);
		printf("%c ", n->character);
		inorder(n->right);
		printf(") ");
	}
}

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

