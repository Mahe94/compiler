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
\+	{	return *yytext;}
\-	{	return *yytext;}
\*	{	return *yytext;}
\/	{	return *yytext;}
\(	return *yytext;
\)	return *yytext;
[\n]	return *yytext;
%%

