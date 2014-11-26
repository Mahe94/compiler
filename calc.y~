%{ 

	#include<stdio.h> 
	#include<string.h>
	#include<stdlib.h>
	
	struct node {
		int type;	// 0 means operator, 1 means read, 2 means write, 3 means ID
		char character;
		int integer;
		struct node *right, *middle, *left;
	};
	
	void inorder(struct node *n);
	void start(struct node *n);
	int getloc(struct node *n);
	
	int array[26];	
	int loc;
	int val;
%} 

%union {
	struct node *n;	
}

%right '='
%left '+' '-'
%left '*' '/'
%left '<' '>'
%token <n> DIGIT READ WRITE ID IF THEN ENDIF ELSE WHILE DO ENDWHILE

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
	| '\n'		{$$=NULL;}
	;

Stmt : ID '=' expr '\n'     	{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=3;
				$$->right=$3;
				$$->left=$1;} 
				
	| READ '(' ID ')' '\n'
				{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=1;
				$$->left=$3;}
				
	| WRITE '(' expr ')' '\n'	
				{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=2;
				$$->left=$3;}
	
	|IF '(' expr ')' THEN '\n' Slist ELSE '\n' Slist ENDIF '\n'
				{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=4;
				$$->left=$3;
				$$->middle=$7;
				$$->right=$10;
				}
				
	|WHILE '(' expr ')' DO '\n' Slist ENDWHILE '\n'
				{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=5;
				$$->left=$3;
				$$->right=$7;}
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
	|expr '<' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->character='<';
			$$->right=$3;
			$$->left=$1;}	
	|expr '>' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->character='>';
			$$->right=$3;
			$$->left=$1;}
	|expr '=''=' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->character='=';
			$$->right=$4;
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
		case '<': return (a<b);
		case '>': return (a>b);
		case '=': return (a==b);
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

int getloc(struct node *n) {
	return (n->character)-97;
}

void start(struct node *n) {
	if(!leaf(n)) {
		switch(n->type) {
			case 0:	start(n->left);
				start(n->right);
				if(n->left->type==3 && n->right->type==3)
					n->integer = compute(n->character, array[getloc(n->left)], array[getloc(n->right)]);
				else
					if(n->left->type==3)
						n->integer = compute(n->character, array[getloc(n->left)], n->right->integer);
					else
						if(n->right->type==3)
							n->integer = compute(n->character, n->left->integer, array[getloc(n->right)]);
						else
							n->integer = compute(n->character, n->left->integer, n->right->integer);
				break;
			case 1:
				loc = getloc(n->left);
				scanf("%d", &val);
				array[loc] = val;
				break;
			case 2:
				if(n->left->type==3)
					printf("%d\n", array[getloc(n->left)]);
				else {
					start(n->left);
					printf("%d\n", n->left->integer);
				}
				break;
			case 3:	
				loc = (n->left->character)-97;
				start(n->right);
				if(n->right->type==3)
					array[loc] = array[getloc(n->right)];
				else
					array[loc] = n->right->integer;
				break;
				
			case 4:
				start(n->left);
				if(n->left->integer == 1) 
					start(n->middle);	
				
				else	
					start(n->right);
				
				break;
			
			case 5:
				start(n->left);
				if(n->left->integer == 1) {
					start(n->right);
					start(n);
				}
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

