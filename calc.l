%{
#include<stdio.h>
%}

%%
[0-9]+ {printf("number");}
[-|+|*|/|^|=]	{printf("operator");}
%%

int main() {
	yylex();
	return 1;
}
