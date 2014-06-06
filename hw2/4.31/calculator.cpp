#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
char token;

float exp(void);
float term(void);
float factor(void);

void error(void)
{
	fprintf(stderr, "Error\n");
	exit(1);
}

void match(char expectedToken)
{
	if (token == expectedToken)
	{
		token = getchar();
	}
	else error();
}

int main()
{
	float result;
	token = getchar();

	result = exp();
	if (token == '\n')
	{
		printf("Result = %f\n", result);
	}
	else
		error();
	return 0;
}

float exp(void)
{
	float temp = term();
	while (token == '+' || token == '-')
	{
		switch (token)
		{
		case '+':
			match('+');
			temp += term();
			break;
		case '-':
			match('-');
			temp -= term();
			break;
		}
	}
	return temp;
}

float term(void)
{
	float temp = factor();
	while (token == '*')
	{
		match('*');
		temp *= factor();
	}
	return temp;
}

float factor(void)
{
	float temp;
	if (token == '(')
	{
		match('(');
		temp = exp();
		match(')');
	}
	else if (isdigit(token))
	{
		ungetc(token, stdin);
		scanf("%f", &temp);
		token = getchar();
	}
	else
		error();
	return temp;
}