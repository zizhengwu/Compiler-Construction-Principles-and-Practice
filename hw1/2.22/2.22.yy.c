%{
#include <stdio.h> 
%}
comments "/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"
%% 
{comments}  { 
	int i;
	for (i = 0; i < yyleng; ++i)
	{
		if (yytext[i] >= 97 && yytext[i] <= 122)
		{
			yytext[i] = yytext[i] - 32;
		}
	}
	printf ("%s", yytext);
}
%%
main( )
{ yylex( );  return 0;  }