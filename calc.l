%{ 
	#include <stdio.h>
	#include "y.tab.h"
%} 

%% 

[0-9]+	{yylval.integer=atoi(yytext); return DIGIT;}
\+	{yylval.character=*yytext; return OP;}
\-	{yylval.character=*yytext; return OP;}
\*	{yylval.character=*yytext; return OP;}
\/	{yylval.character=*yytext; return OP;}
[\n]	return *yytext;
%%

