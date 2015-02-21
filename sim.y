%{ 

	#include<stdio.h> 
	#include<string.h>
	#include<stdlib.h>
	
	struct node {
		int type;	// 0 means operator, 1 means read, 2 means write, 3 means ID
		char *name;
		int integer;
		struct node *right, *middle, *left;
	};
	
	
	struct Gsymbol {
		char *NAME;
		int type;
		int size;
		int binding;
		struct Gsymbol *next;
	}*Symbol=NULL;
	
	void start(struct node *n);
	int getloc(struct node *n);
	void printSymbol();
	void Ginstall(char *N, int t, int s);
	struct Gsymbol *Glookup(char *name);
//	struct *node nodeCreate(int t, char *n, int i, struct node *r, struct node *m, struct node *l);
	
	int currentType;
	int currentBinding = 0;
	int array[26];	
	int loc;
	int val;
	
	FILE *fp=NULL;
	
	int avail_reg=0, avail_l=0;
	
%} 

%union {
	struct node *n;	
}

%right '='
%left "==" "!="
%left '<' "<=" '>' ">="
%left '+' '-'
%left '*' '/'
%token <n> DECL ENDDECL TYPE DIGIT READ WRITE ID IF THEN ENDIF ELSE WHILE DO ENDWHILE BEGINING END 

%type <n> expr Stmt Slist Body Decl_list decl id_list type
	 
%% 

Prog : Declaration Body ;

Declaration : DECL Decl_list ENDDECL {printSymbol();};

Decl_list : decl Decl_list
	| decl	
	;
	
decl :	type id_list ';'
	;

type : TYPE {currentType = $1->type;}
	;
	
id_list: ID ',' id_list		{Ginstall($1->name, currentType, 1);}
	| ID'['DIGIT']' ',' id_list	{Ginstall($1->name, currentType, $3->integer);}
	| ID 	{Ginstall($1->name, currentType, 1);}
	| ID'['DIGIT']'	{Ginstall($1->name, currentType, $3->integer);}	
	;

Body : BEGINING Slist END		{$$=(struct node*)malloc(sizeof(struct node));
			$$=$2;
			printf("Code\n");
			scanf("%d",&loc);
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
	| 		{$$=NULL;}
	;

Stmt : ID '=' expr ';'     	{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=3;
				$$->right=$3;
				$$->left=$1;} 
				
	| READ '(' ID ')' ';'
				{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=1;
				$$->left=$3;}
				
	| WRITE '(' expr ')' ';'	
				{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=2;
				$$->left=$3;}
	
	|IF '(' expr ')' THEN  Slist ELSE  Slist ENDIF 
				{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=4;
				$$->left=$3;
				$$->middle=$6;
				$$->right=$8;
				}
				
	|WHILE '(' expr ')' DO  Slist ENDWHILE 
				{$$=(struct node*)malloc(sizeof(struct node));
				$$->type=5;
				$$->left=$3;
				$$->right=$6;}
    ; 

expr:	expr '+' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->name[0]='+';
			$$->right=$3;
			$$->left=$1;}
    	|expr '-' expr	{$$=(struct node*)malloc(sizeof(struct node));
    			$$->type=0;
			$$->name[0]='-';
    			$$->right=$3;
			$$->left=$1;}
	|expr '*' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->name[0]='*';
			$$->right=$3;
			$$->left=$1;}
	|expr '/' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->name[0]='/';
			$$->right=$3;
			$$->left=$1;}
	|expr '<' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->name[0]='<';
			$$->right=$3;
			$$->left=$1;}	
	|expr '>' expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->name[0]='>';
			$$->right=$3;
			$$->left=$1;}
	|expr "!=" expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->name[0]='!';
			$$->right=$3;
			$$->left=$1;}
	|expr "==" expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->name[0]='=';
			$$->right=$3;
			$$->left=$1;}
	|expr "<=" expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->name[0]='l';
			$$->right=$3;
			$$->left=$1;}	  
	|expr ">=" expr	{$$=(struct node*)malloc(sizeof(struct node));
			$$->type=0;
			$$->name[0]='g';
			$$->right=$3	;
			$$->left=$1;}     
	| '(' expr ')'	{$$=$2;}
	| DIGIT         {$1->type=6;
			$$=$1;} 
	| ID		{$1->type=7;
			$$=$1;}
; 

%%     

#include "lex.yy.c"

void printSymbol() {
	struct Gsymbol *symbol = Symbol;
	while(symbol != NULL) {
		printf("%s %d %d %d", symbol->NAME, symbol->type, symbol->size, symbol->binding);
		symbol = symbol->next;
	}
}

struct Gsymbol *Glookup(char *name) {
	struct Gsymbol *symbol = Symbol;
	while(symbol != NULL) {
		if(strcmp(symbol->NAME,name)==0)
			return symbol;
		symbol = symbol->next;
	}
	return NULL;
}

void Ginstall(char *N, int t, int s) {
	if(Glookup(N)!=NULL) {
		yyerror(strcat(N ," has been declared earlier"));
		exit(1);
	}
	struct Gsymbol *symbol = Symbol;
	if(symbol != NULL) {
		while(symbol->next != NULL)
			symbol = symbol->next;
		symbol->next = (struct Gsymbol*)malloc(sizeof(struct Gsymbol));
		symbol = symbol->next;
	}
	else {
		symbol = (struct Gsymbol*)malloc(sizeof(struct Gsymbol));
		Symbol = symbol;
	}

	symbol->NAME = (char*)malloc(sizeof(N));
	strcpy(symbol->NAME,N);
	symbol->type = t;
	symbol->size = s;
	symbol->binding = currentBinding;
	symbol->next = NULL;

	currentBinding = currentBinding + s;	
}

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
		case '<': fprintf(fp, "LT R%d, R%d\n", avail_reg, avail_reg+1);
			return (a<b);
		case '>': fprintf(fp, "GT R%d, R%d\n", avail_reg, avail_reg+1);
			return (a>b);
		case '!': fprintf(fp, "NE R%d, R%d\n", avail_reg, avail_reg+1);
			return (a==b);
		case '=': fprintf(fp, "EQ R%d, R%d\n", avail_reg, avail_reg+1);
			return (a==b);
		case 'l': fprintf(fp, "LE R%d, R%d\n", avail_reg, avail_reg+1);
			return (a<=b);
		case 'g': fprintf(fp, "GE R%d, R%d\n", avail_reg, avail_reg+1);
			return (a>=b);
	}
	return 0;
}

int leaf(struct node *n) {
	if(n->right==NULL && n->left==NULL)
		return 1;
	else
		return 0;
}

int getloc(struct node *n) {
	return (n->name[0])-97;
}

void start(struct node *n) {
//	printf("STARTED\n");
//	scanf("%d", avail_reg);
	int l1, l2;
	if(!leaf(n)) {
		switch(n->type) {
			case 0:	
//				start(n->left);
//				start(n->right);
				if(n->left->type==7 && n->right->type==7) {
					fprintf(fp, "MOV R%d, [%d]\n", avail_reg, getloc(n->left));
					fprintf(fp, "MOV R%d, [%d]\n", avail_reg+1, getloc(n->right));
					n->integer = compute(n->name[0], array[getloc(n->left)], array[getloc(n->right)]);
				}
				else {
					if(n->left->type==7) {
						if(n->right->type==6) 
							fprintf(fp, "MOV R%d, %d\n", avail_reg+1, n->right->integer);
						else {
							++avail_reg;
							start(n->right);
							--avail_reg;
						}
						fprintf(fp, "MOV R%d, [%d]\n", avail_reg, getloc(n->left));
//						fprintf(fp, "MOV R%d, R%d\n", avail_reg, avail_reg+1);
						n->integer = compute(n->name[0], array[getloc(n->left)], n->right->integer);	
					}
					else {
						if(n->right->type==7) {
							if(n->left->type==6) 
								fprintf(fp, "MOV R%d, %d\n", avail_reg+1, n->left->integer);
							else {
								++avail_reg;
								start(n->left);
								--avail_reg;
							}
							fprintf(fp, "MOV R%d, [%d]\n", avail_reg, getloc(n->right));
//							fprintf(fp, "MOV R%d, R%d\n", avail_reg, avail_reg+1);
							n->integer = compute(n->name[0], n->left->integer, array[getloc(n->right)]);	
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
							n->integer = compute(n->name[0], n->left->integer, n->right->integer);
						}
					}
				}
				break;
			case 1:
				loc = getloc(n->left);
//				scanf("%d", &val);
// 				array[loc] = val;
				fprintf(fp, "IN R%d\n", avail_reg);
				fprintf(fp, "MOV [%d], R%d\n", loc, avail_reg);
				break;
			case 2:
				if(n->left->type==7) {
//					printf("%d\n", array[getloc(n->left)]);
					fprintf(fp, "MOV R%d, [%d]\n", avail_reg, loc);
					fprintf(fp, "OUT R%d\n", avail_reg);
				}
				else { if(n->left->type==6) {
						fprintf(fp, "MOV R%d, %d\n", avail_reg, n->left->integer);
						fprintf(fp, "OUT R%d\n", avail_reg);
					}
					else {
						start(n->left);
						fprintf(fp, "OUT R%d\n", avail_reg);
//						printf("%d\n", n->left->integer);
					}
				}
				break;
			case 3:	
				
				loc = (n->left->name[0])-97;
				start(n->right);
				if(n->right->type==7) {
					array[loc] = array[getloc(n->right)];
					fprintf(fp, "MOV R%d, [%d]\n", avail_reg, getloc(n->right));
					fprintf(fp, "MOV [%d], R%d\n", loc, avail_reg);
				}
				else if(n->right->type==6) {
					array[loc] = n->right->integer;
					fprintf(fp, "MOV [%d], %d\n", loc, n->right->integer);
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
				l1=avail_l, l2=avail_l+1;
				avail_l+=2;
				start(n->left);
				fprintf(fp, "JZ R%d, L%d\n", avail_reg, l1);
				start(n->middle);
				fprintf(fp, "JMP L%d\nL%d:\n", l2, l1);
				start(n->right);
				fprintf(fp, "L%d:\n", l2);
				
//				if(n->left->integer == 1) 
//					start(n->middle);	
//				
//				else	
//					start(n->right);
//				
				break;
			
			case 5:
				l1=avail_l, l2=avail_l+1;
				avail_l+=2;
				fprintf(fp, "L%d:\n", l1);
				start(n->left);
				fprintf(fp, "JZ R%d, L%d\n", avail_reg, l2);
				start(n->right);
//				if(n->left->integer == 1) {
//					start(n->right);
//					start(n);
//				}
				fprintf(fp, "JMP L%d\nL%d:\n", l1, l2);
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

int main(int argc, char *argv[]) 
{ 
   if(argc > 1) {
   	FILE *fp = fopen(argv[1], "r");
   	if(fp)
   		yyin = fp;
   }
    yyparse(); 
} 

