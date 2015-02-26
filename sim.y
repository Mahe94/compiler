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
	
	
	struct Gsymbol {	// for Symbol table
		char *NAME;
		int type;
		int size;
		int binding;
		struct Gsymbol *next;
	}*Symbol=NULL;
	
	void start(struct node *n);	//starting of parse tree generation
	int getloc(char *name);	
	void printSymbol();		
	void Ginstall(char *N, int t, int s);	//creating an entry in symbol table
	struct Gsymbol *Glookup(char *name);	//getting pointing from symbol table
	struct node *nodeCreate(int t, char *n, int i, struct node *l, struct node *m, struct node *r);	//creating a node for tree
	int get_datatype(struct node *n);	//returning datatype of node
	void check_datatypes(int t1, int t2, char *op); //checking datatypes
	
	int currentType;	//storing the current datatype while making the symbol table
	int currentBinding = 0;	//storing the starting available address for binding
	int array[26];	
	int loc, t1, t2;
	int val;
	
	FILE *fp=NULL;	//file pointer for storing the machine code
	
	int avail_reg=0, avail_l=0;	//for storing the current available register and jump symbol
	
%} 

%union {
	struct node *n;	
}

%right '='
%left "==" "!="
%left '<' "<=" '>' ">="
%left '+' '-'
%left '*' '/' '%'
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
	
id_list: ID ',' id_list	{ Ginstall($1->name, currentType, 1);}
	| ID'['DIGIT']' ',' id_list	{ Ginstall($1->name, currentType, $3->integer); }
	| ID 	{ Ginstall($1->name, currentType, 1); }
	| ID'['DIGIT']'	{ Ginstall($1->name, currentType, $3->integer); }	
	;

Body : BEGINING Slist END	{
				  $$=$2;
				  printf("Code\n");
				  scanf("%d",&loc);
				  fp = fopen("output", "w+");	
				  fprintf(fp, "START\n");
				  start($$);
				  fprintf(fp, "HALT");
				  fclose(fp);
				  return 0; }
	;
	
Slist : Stmt Slist 	{ $$ = nodeCreate(100, NULL, 0, $1, NULL, $2);
			}
	| 		{$$=NULL;}
	;

Stmt : ID '=' expr ';'     	{ $$ = nodeCreate(3, NULL, 0, $1, NULL, $3); } 
	| ID '[' expr ']' '=' expr ';'	{ $$ = nodeCreate(3, NULL, 0, $1, $3, $6); }
				
	| READ '(' ID ')' ';'
				{$$ = nodeCreate(1, NULL, 0, $3, NULL, NULL); }
	| READ '(' ID '[' expr ']' ')' ';'
				{$$ = nodeCreate(1, NULL, 0, $3, NULL, $5); }
				
	| WRITE '(' expr ')' ';'	
				{ $$ = nodeCreate(2, NULL, 0, $3, NULL, NULL); }
	
	|IF '(' expr ')' THEN  Slist ELSE  Slist ENDIF 
				{ $$ = nodeCreate(4, NULL, 0, $3, $6, $8); }
				
	|WHILE '(' expr ')' DO  Slist ENDWHILE 
				{ $$ = nodeCreate(5, NULL, 0, $3, NULL, $6); }
    ; 

expr:	expr '+' expr	{ $$ = nodeCreate(0, "+", 0, $1, NULL, $3); }
    	|expr '-' expr	{ $$ = nodeCreate(0, "-", 0, $1, NULL, $3); }
	|expr '*' expr	{ $$ = nodeCreate(0, "*", 0, $1, NULL, $3); }
	|expr '/' expr	{ $$ = nodeCreate(0, "/", 0, $1, NULL, $3); }
	|expr '%' expr	{ $$ = nodeCreate(0, "%", 0, $1, NULL, $3); }
	|expr '<' expr	{ $$ = nodeCreate(0, "<", 0, $1, NULL, $3); }	
	|expr '>' expr	{ $$ = nodeCreate(0, ">", 0, $1, NULL, $3); }
	|expr "!=" expr	{ $$ = nodeCreate(0, "!=", 0, $1, NULL, $3); }
	|expr "==" expr	{ $$ = nodeCreate(0, "==", 0, $1, NULL, $3); }
	|expr "<=" expr	{ $$ = nodeCreate(0, "<=", 0, $1, NULL, $3); }	  
	|expr ">=" expr	{ $$ = nodeCreate(0, ">=", 0, $1, NULL, $3); }     
	| '(' expr ')'	{ $$ = $2; }
	| DIGIT         { $$ = $1; } 
	| ID		{ $$ = $1; }
//	| ID'['DIGIT']' { $$ = nodeCreate(8, $1->name, 0, $2, NULL, NULL); }
//	| ID'['ID']'	{ $$ = nodeCreate(8, $1->name, 0, $2, NULL, NULL); }
	| ID'['expr']'	{ $$ = nodeCreate(8, $1->name, 0, $3, NULL, NULL); }
; 

%%     

#include "lex.yy.c"

void printSymbol() {
	struct Gsymbol *symbol = Symbol;
	while(symbol != NULL) {
		printf("%s %d %d %d\n", symbol->NAME, symbol->type, symbol->size, symbol->binding);
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

struct node *nodeCreate(int t, char *n, int i, struct node *l, struct node *m, struct node *r) {
	struct node *N = (struct node*)malloc(sizeof(struct node));
	N->type = t;
	if(n!=NULL) {
		N->name = (char *)malloc(sizeof(n));
		strcpy(N->name, n);
	}
	N->integer  = i;
	N->right = r;
	N->left = l;
	N->middle = m;
	return N;
}

void compute(char *op) {
	if(!strcmp(op, "+")) {
		fprintf(fp, "ADD R%d, R%d\n", avail_reg, avail_reg+1);
		return ;
	}
	if(!strcmp(op, "-")) {
		fprintf(fp, "SUB R%d, R%d\n", avail_reg, avail_reg+1);	
		return ;
	}
	if(!strcmp(op, "*")) {
		fprintf(fp, "MUL R%d, R%d\n", avail_reg, avail_reg+1);
		return ;
	}
	if(!strcmp(op, "/")) {
		fprintf(fp, "DIV R%d, R%d\n", avail_reg, avail_reg+1);
		return ;
	}
	if(!strcmp(op, "%")) {
		fprintf(fp, "MOV R%d, R%d\n", avail_reg+2, avail_reg);
		fprintf(fp, "DIV R%d, R%d\n", avail_reg+2, avail_reg+1);
		fprintf(fp, "MUL R%d, R%d\n", avail_reg+2, avail_reg+1);
		fprintf(fp, "SUB R%d, R%d\n", avail_reg, avail_reg+2);
		return ;
	}
	if(!strcmp(op, "<")) {
		fprintf(fp, "LT R%d, R%d\n", avail_reg, avail_reg+1);
		return ;
	}
	if(!strcmp(op, ">")) {
		fprintf(fp, "GT R%d, R%d\n", avail_reg, avail_reg+1);
		return ;
	}
	if(!strcmp(op, "!=")) {
		fprintf(fp, "NE R%d, R%d\n", avail_reg, avail_reg+1);
		return ;
	}
	if(!strcmp(op, "==")) {
		fprintf(fp, "EQ R%d, R%d\n", avail_reg, avail_reg+1);
		return ;
	}
	if(!strcmp(op, "<=")) {
		fprintf(fp, "LE R%d, R%d\n", avail_reg, avail_reg+1);
		return ;
	}
	if(!strcmp(op, ">=")) {
		fprintf(fp, "GE R%d, R%d\n", avail_reg, avail_reg+1);
		return ;
	}
	char error[100] = "Operands not matching with operator ";
	strcat(error, op);
	yyerror(error);
}

int leaf(struct node *n) {
	if(n->right==NULL && n->left==NULL)
		return 1;
	else
		return 0;
}

int getloc(char *name) {
	struct Gsymbol *symbol = Glookup(name);
	return symbol->binding;
}

int get_datatype(struct node *n) {
	struct Gsymbol *s;
	s = Glookup(n->name);
	return s->type;
}

void check_datatypes(int t1, int t2, char *op) {
	if(t1 != t2) {
		char error[100] = "Conflicting operands for operator ";
		strcat(error, op);
		yyerror(error);
		exit(1);
	}
	currentType = t1;
}

void start(struct node *n) {
//	printf("STARTED\n");
//	scanf("%d", avail_reg);
	int l1, l2;
	if(!leaf(n)) {
		switch(n->type) {
			case 0:						//operations
				switch(n->left->type) {
					case 0:
						start(n->left);
						break;
					case 6:
						fprintf(fp, "MOV R%d, %d\n", avail_reg, n->left->integer);
						t1 = 1;
						break;
					
					case 7:
						loc = getloc(n->left->name);
						fprintf(fp, "MOV R%d, [%d]\n", avail_reg, loc);
						t1 = get_datatype(n->left);
						break;
					case 8:
						start(n->left);
						loc = getloc(n->left->name);
						fprintf(fp, "MOV R%d, %d\n", avail_reg+1, loc);
						fprintf(fp, "ADD R%d, R%d\n", avail_reg, avail_reg+1);
						fprintf(fp, "MOV R%d, [R%d]\n", avail_reg, avail_reg);
						t1 = get_datatype(n->left);
						break;
					default:
						yyerror("Type 0 error");				
					}
				
				++avail_reg;
				switch(n->right->type) {
					case 0:
						start(n->right);
						break;
					case 6:
						fprintf(fp, "MOV R%d, %d\n", avail_reg, n->right->integer);
						t2 = 1;
						break;
					
					case 7:
						loc = getloc(n->right->name);
						fprintf(fp, "MOV R%d, [%d]\n", avail_reg, loc);
						t2 = get_datatype(n->right);
						break;
					case 8:
						start(n->right);
						loc = getloc(n->right->name);
						fprintf(fp, "MOV R%d, %d\n", avail_reg+1, loc);
						fprintf(fp, "ADD R%d, R%d\n", avail_reg, avail_reg+1);
						fprintf(fp, "MOV R%d, [R%d]\n", avail_reg, avail_reg);
						t2 = get_datatype(n->right);
						break;
					default:
						yyerror("Type 0 error");				
				}
				--avail_reg;
				check_datatypes(t1, t2	, n->name);
				compute(n->name);
				break;
			case 1:					//read
				loc = getloc(n->left->name);
				fprintf(fp, "MOV R%d, [%d]\n", avail_reg+1, loc);
				if(n->right != NULL) {
					avail_reg = avail_reg + 2;
					switch(n->right->type) {
						case 0:
							start(n->right);
							break;
						case 6:
							fprintf(fp, "MOV R%d, %d\n", avail_reg, n->right->integer);
							t2 = 1;
							break;
					
						case 7:
							loc = getloc(n->right->name);
							fprintf(fp, "MOV R%d, [%d]\n", avail_reg, loc);
							t2 = get_datatype(n->right);
							break;
						case 8:
							start(n->right);
							loc = getloc(n->right->name);
							fprintf(fp, "MOV R%d, %d\n", avail_reg+1, loc);
							fprintf(fp, "ADD R%d, R%d\n", avail_reg, avail_reg+1);
							fprintf(fp, "MOV R%d, [R%d]\n", avail_reg, avail_reg);
							t2 = get_datatype(n->right);
							break;
						default:
							yyerror("Type 0 error");				
					}
					avail_reg = avail_reg - 2;
					fprintf(fp, "ADD R%d, R%d\n", avail_reg+1, avail_reg+2);
				}
				fprintf(fp, "IN R%d\n", avail_reg);
				fprintf(fp, "MOV [R%d], R%d\n", avail_reg+1, avail_reg);
				break;
			case 2:						//write
				
				switch(n->left->type) {
					case 0:
						start(n->left);
					case 6:
						fprintf(fp, "MOV R%d, %d\n", avail_reg, n->left->integer);
						break;
					
					case 7:
						loc = getloc(n->left->name);
						fprintf(fp, "MOV R%d, [%d]\n", avail_reg, loc);
						t1 = get_datatype(n->left);
						break;
					case 8:
						start(n->left);
						loc = getloc(n->left->name);
						fprintf(fp, "MOV R%d, %d\n", avail_reg+1, loc);
						fprintf(fp, "ADD R%d, R%d\n", avail_reg, avail_reg+1);
						fprintf(fp, "MOV R%d, [R%d]\n", avail_reg, avail_reg);
						t1 = get_datatype(n->left);
						break;
					default:
						yyerror("Type 2 error");
				}
				break;
			case 3:				//assignment
				loc = getloc(n->left->name);
				fprintf(fp, "MOV R%d, [%d]\n", avail_reg+1, loc);
				t1 = get_datatype(n->left);
				if(n->middle != NULL) {
					avail_reg = avail_reg + 2;
					start(n->right);
					avail_reg = avail_reg - 2;
					fprintf(fp, "ADD R%d, R%d\n", avail_reg+1, avail_reg+2);
				}
				++avail_reg;
				switch(n->left->type) {
					case 0:
						start(n->left);
						break;
					case 6:
						fprintf(fp, "MOV R%d, %d\n", avail_reg, n->left->integer);
						t1 = 1;
						break;
					
					case 7:
						loc = getloc(n->left->name);
						fprintf(fp, "MOV R%d, [%d]\n", avail_reg, loc);
						t1 = get_datatype(n->left);
						break;
					case 8:
						start(n->left);
						loc = getloc(n->left->name);
						fprintf(fp, "MOV R%d, %d\n", avail_reg+1, loc);
						fprintf(fp, "ADD R%d, R%d\n", avail_reg, avail_reg+1);
						fprintf(fp, "MOV R%d, [R%d]\n", avail_reg, avail_reg);
						t1 = get_datatype(n->left);
						break;
					default:
						yyerror("Type 3 error");				
				}
				--avail_reg;
				fprintf(fp, "MOV [R%d], R%d\n", avail_reg, avail_reg+1);
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

