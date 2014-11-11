%{ 
	#include <stdio.h>
	#include "y.tab.h"
%} 

%% 

[0-9]+	{yylval=atoi(yytext); return DIGIT;}
";"	return END;
\-	return MINUS;
\+	return PLUS;
\*	return MUL;		
\/	return DIV;
\(	return LEFT;
\)	return RIGHT;
\%	return MOD;
%%

