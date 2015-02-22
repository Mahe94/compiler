%{ 
	#include <stdio.h>
	#include <string.h>
	#include "y.tab.h"
	
	int a;	
%} 

%% 
[0-9]+	{	yylval.n = (struct node*)malloc(sizeof(struct node));
		yylval.n->type = 6;
		yylval.n->integer=atoi(yytext); 
		yylval.n->right=NULL;
		yylval.n->left=NULL;
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
\(	return *yytext;
\)	return *yytext;
"%"	return *yytext;
";"	return *yytext;
","	return *yytext;
"["	return *yytext;
"]"	return *yytext;
[\n\t' ']	{};
%%

