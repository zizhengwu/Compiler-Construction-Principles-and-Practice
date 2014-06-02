%{
#include "stdio.h"
#include "ctype.h"
#include <string>
using namespace std;
extern "C"
{
	int yylex(void);
	int yyerror(char *s);
}
class Value
{
public:
	double val;
	string type;
};
#define YYSTYPE Value
%}

%token NUMBER

%%

command:
	exp { printf("%lf\n", $1.val); }
	;

exp:
	exp '+' term { $$.val = $1.val + $3.val; } |
	exp '-' term {$$.val = $1.val - $3.val; } |
	term { $$.val = $1.val; }

term:
	term '*' factor { $$.val = $1.val * $3.val; } |
	factor { $$.val = $1.val; }

factor:
	NUMBER { $$.val = $1.val; } |
	'(' exp ')' { $$.val = $2.val; }
	;
%%

int main()
{
	return yyparse();
}

int yylex(void)
{
	const double delta = 1e-5;
	int isInt (double a);
	int c;
	while((c = getchar()) == ' ');
	// eliminate blanks
	if (isdigit(c))
	{
		ungetc(c, stdin);
		scanf("%lf", &yylval.val);
		if (yylval.val - (int) yylval.val < delta )
			yylval.type = "int";
		else
			yylval.type = "float";
		return (NUMBER);
	}
	if (c == '\n')
		return 0;
	// makes the parse stop
	return (c);
}

int yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
	return 0;
}
