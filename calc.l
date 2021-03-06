%{ 
	#include <stdio.h>
	#include "y.tab.h"
%} 

%% 

[0-9]+	{	yylval.n = (struct node*)malloc(sizeof(struct node));
		yylval.n->integer=atoi(yytext); 
		yylval.n->right=NULL;
		yylval.n->left=NULL;
		return DIGIT;}	
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
		yylval.n->character=yytext[0]; 
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
[\n]	return *yytext;
%%

