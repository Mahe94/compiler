%{ 
	#include <stdio.h>
	#include <string.h>
	#include "y.tab.h"
	
	int a;	
%} 

%option yylineno

%% 
[0-9]+	{	yylval.n = (struct node*)malloc(sizeof(struct node));
		yylval.n->type = 6;
		yylval.n->integer=atoi(yytext); 
		yylval.n->right=NULL;
		yylval.n->left=NULL;
		yylval.n->datatype=1;
		return DIGIT;}
"enddecl" {	return ENDDECL;}	
"decl"	{	return DECL;}
"integer" {	yylval.n = (struct node*)malloc(sizeof(struct node));
		yylval.n->type = 1;
		return TYPE;}
"boolean" {	yylval.n = (struct node*)malloc(sizeof(struct node));
		yylval.n->type = 0;
		return TYPE;}
"begin"	{	return BEGINING;}
"end"	{	return END;}
"write"	{	return WRITE;}
"read"	{	return READ;}
"if"	{	return IF;}
"then"	{	return THEN;}
"else"	{	return ELSE;}
"endif"	{	return ENDIF;}
"while" {	return WHILE;}
"do"	{	return DO;}
"endwhile" {	return ENDWHILE;}
"TRUE"	{	yylval.n = (struct node*)malloc(sizeof(struct node));
		yylval.n->type = 9;
		yylval.n->integer = 1;
		yylval.n->name = (char*)malloc(sizeof(yytext));
		strcpy(yylval.n->name,yytext); 
		yylval.n->right=NULL;
		yylval.n->left=NULL;
		yylval.n->datatype=0;
		return TRUE;}
"FALSE"	{	yylval.n = (struct node*)malloc(sizeof(struct node));
		yylval.n->type = 9;
		yylval.n->integer =  0;
		yylval.n->name = (char*)malloc(sizeof(yytext));
		strcpy(yylval.n->name,yytext); 
		yylval.n->right=NULL;
		yylval.n->left=NULL;
		yylval.n->datatype=0;
		return FALSE;}
"AND"	{	yylval.n->datatype=0;
		return AND;}
"OR"	{	yylval.n->datatype=0;
		return OR;}
"NOT"	{	yylval.n->datatype=0;
		return NOT;}
[a-z]+	{	yylval.n = (struct node*)malloc(sizeof(struct node));
		yylval.n->type = 7;
		yylval.n->name = (char*)malloc(sizeof(yytext));
		strcpy(yylval.n->name,yytext); 
		yylval.n->right=NULL;
		yylval.n->left=NULL;
		return ID;}	
\=	{	return *yytext;}
\+	{	return *yytext;}
\-	{	return *yytext;}
\*	{	return *yytext;}
\/	{	return *yytext;}
\<	{	return *yytext;}
\>	{	return *yytext;}
">="	{	return *yytext;}
"<="	{	return *yytext;}
\(	return *yytext;
\)	return *yytext;
"%"	return *yytext;
";"	return *yytext;
","	return *yytext;
"["	return *yytext;
"]"	return *yytext;
[\n\t' ']	{};
%%

