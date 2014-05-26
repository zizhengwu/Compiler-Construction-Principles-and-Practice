%{
#include <stdio.h> 
int characterCount = 0, wordCount = 0, lineCount = 0;
%}
character [a-zA-Z]
digit [0-9]
word ({character}|{digit})+
line \n
%% 
{line} {lineCount++;}
{word} {wordCount++; characterCount += strlen(yytext);}
. {characterCount++;}
%%
main( )
{
	yylex( ); 
	printf("characterCount = %d\n", characterCount);
	printf("wordCount = %d\n", wordCount);
	printf("lineCount = %d\n", lineCount);
	return 0;
}