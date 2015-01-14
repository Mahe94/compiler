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
	
	FILE *fp=NULL;
	
	int avail_reg=0;
	
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
			fp = fopen("output", "w+");	
			fprintf(fp, "START\n");
			start($$);
			fprintf(fp, "HALT");
			fclose(fp);
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
	| DIGIT         {$1->type=6;
			$$=$1;} 
	| ID		{$1->type=3;
			$$=$1;}
; 

%%     

#include "lex.yy.c"

int compute(char c, int a, int b) {
	switch(c) {
		case '+': fprintf(fp, "ADD R%d, R%d\n", avail_reg, avail_reg+1);
			return (a+b);
		case '-': fprintf(fp, "SUB R%d, R%d\n", avail_reg, avail_reg+1);
			return (a-b);
		case '*': fprintf(fp, "MUL R%d, R%d\n", avail_reg, avail_reg+1);
			return (a*b);
		case '/': fprintf(fp, "DIV R%d, R%d\n", avail_reg, avail_reg+1);
			return (a/b);
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
//	printf("STARTED\n");
//	scanf("%d", avail_reg);
	if(!leaf(n)) {
		switch(n->type) {
			case 0:	
//				start(n->left);
//				start(n->right);
				if(n->left->type==3 && n->right->type==3) {
					fprintf(fp, "MOV R%d, [%d]\n", avail_reg, getloc(n->left));
					fprintf(fp, "MOV R%d, [%d]\n", avail_reg+1, getloc(n->right));
					n->integer = compute(n->character, array[getloc(n->left)], array[getloc(n->right)]);
				}
				else {
					if(n->left->type==3) {
						if(n->right->type==6) 
							fprintf(fp, "MOV R%d, %d\n", avail_reg+1, n->right->integer);
						else {
							++avail_reg;
							start(n->right);
							--avail_reg;
						}
						fprintf(fp, "MOV R%d, [%d]\n", avail_reg, getloc(n->left));
//						fprintf(fp, "MOV R%d, R%d\n", avail_reg, avail_reg+1);
						n->integer = compute(n->character, array[getloc(n->left)], n->right->integer);	
					}
					else {
						if(n->right->type==3) {
							if(n->left->type==6) 
								fprintf(fp, "MOV R%d, %d\n", avail_reg+1, n->left->integer);
							else {
								++avail_reg;
								start(n->left);
								--avail_reg;
							}
							fprintf(fp, "MOV R%d, [%d]\n", avail_reg, getloc(n->right));
//							fprintf(fp, "MOV R%d, R%d\n", avail_reg, avail_reg+1);
							n->integer = compute(n->character, n->left->integer, array[getloc(n->right)]);	
						}
						else {
							if(n->left->type==6)
								fprintf(fp, "MOV R%d, %d\n", avail_reg, n->left->integer);
							else
								start(n->left);
							++avail_reg;
							if(n->right->type==6) 
								fprintf(fp, "MOV R%d, %d\n", avail_reg, n->right->integer);
							else 
								start(n->right);
							--avail_reg;
							n->integer = compute(n->character, n->left->integer, n->right->integer);
						}
					}
				}
				break;
			case 1:
				loc = getloc(n->left);
				scanf("%d", &val);
 				array[loc] = val;
				fprintf(fp, "IN R%d\n", avail_reg);
				fprintf(fp, "MOV [%d], R%d\n", loc, avail_reg);
				break;
			case 2:
				if(n->left->type==3) {
					printf("%d\n", array[getloc(n->left)]);
					fprintf(fp, "MOV R%d, [%d]\n", avail_reg, loc);
					fprintf(fp, "OUT R%d\n", avail_reg);
				}
				else {
					start(n->left);
					fprintf(fp, "OUT R%d\n", avail_reg);
					printf("%d\n", n->left->integer);
				}
				break;
			case 3:	
				loc = (n->left->character)-97;
				start(n->right);
				if(n->right->type==3) {
					array[loc] = array[getloc(n->right)];
					fprintf(fp, "MOV R%d, [%d]\n", avail_reg, getloc(n->right));
					fprintf(fp, "MOV [%d], R%d\n", loc, avail_reg);
				}
				else {
//					++avail_reg;
					array[loc] = n->right->integer;
//					--avail_reg;
//					fprintf(fp, "MOV R%d, R%d\n", avail_reg, avail_reg+1);
					fprintf(fp, "MOV [%d], R%d\n", loc, avail_reg);
				}
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

