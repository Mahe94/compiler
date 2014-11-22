%{ 

	#include<stdio.h> 
	#include<string.h>
	
	struct node {
		int type;	// 0 means operator, 1 means read, 2 means write, 3 means ID
		char character;
		int integer;
		struct node *right, *left;
	};
	
	void inorder(struct node *n);
	void start(struct node *n);
	
	int array[26];	
	int loc;
%} 

%union {
	struct node *n;	
}

%right '='
%left '+' '-'
%left '*' '/'
%token <n> DIGIT READ WRITE STOP ID

%type <n> expr Stmt Slist Start
	 
%% 

Start : Slist		{$$=(struct node*)malloc(sizeof(struct node));
			$$=$1;
			start($$);
			return 0;}
	;
	
Slist : Stmt Slist 	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=100;
			$$->left=$1;
			$$->right=$2;
			}
	| STOP		{$$=NULL;}
	;

Stmt : ID '=' expr '\n'     	{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=3;
				$$->right=$3;
				$$->left=$1;} 
	| READ '(' ID ')' '\n'	{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=1;
				$$->left=$3;}
	| WRITE '(' expr ')' '\n'	{$$=(struct node*)malloc(sizeof(struct node));
					$$->type=2;
					$$->left=$3;}
    ; 

expr:	expr '+' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->character='+';
			$$->right=$3;
			$$->left=$1;}
    	|expr '-' expr	{$$=(struct node*)malloc(sizeof(struct node));
    			$$->type=0;
			$$->character='-';
    			$$->right=$3;
			$$->left=$1;}
	|expr '*' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->character='*';
			$$->right=$3;
			$$->left=$1;}
	|expr '/' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->character='/';
			$$->right=$3;
			$$->left=$1;}		       
	| '(' expr ')'	{$$=$2;}
	| DIGIT         {$$=$1;} 
	| ID		{$1->type=3;
			$$=$1;}
; 

%%     

#include "lex.yy.c"

int compute(char c, int a, int b) {
	switch(c) {
		case '+': return (a+b);
		case '-': return (a-b);
		case '*': return (a*b);
		case '/': return (a/b);
	}
	return 0;
}

int leaf(struct node *n) {
	if(n->right==NULL && n->left==NULL)
		return 1;
	else
		return 0;
}

/*
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
		n->integer = compute(n->character, n->left->integer, n->right->integer);
	}
}
*/

void start(struct node *n) {
	if(!leaf(n)) {
		switch(n->type) {
			case 0:	start(n->left);
				start(n->right);
				n->integer = compute(n->character, n->left->integer, n->right->integer);
				break;
			
			case 3:	
				loc = (n->left->character)-97;
				start(n->right);
				if(n->right->type==3)
					array[loc] = array[(n->right->character)-97];
				else
					array[loc] = n->right->integer;
				printf("%d\n", array[loc]);
				break;
				
			case 100:
				start(n->left);
				if(n->right!=NULL)
					start(n->right);
				break;
				
			default:
				break;
		}	
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

