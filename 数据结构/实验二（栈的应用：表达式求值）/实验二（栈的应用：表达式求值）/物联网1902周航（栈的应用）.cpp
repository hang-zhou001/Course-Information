#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	char* top;
	char* base;
	int stacksize;
}Sqstack1;
typedef struct              //输入一个表达式，以=作为表达式输入完成标志
{
	int* top;
	int* base;
	int stacksize;
}Sqstack2;
Sqstack1 Initstack1()
{
	Sqstack1 s;
	s.base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	if (!s.base)
		exit(0);
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return s;
}
Sqstack2 Initstack2()
{
	Sqstack2 s;
	s.base = (int*)malloc(STACK_INIT_SIZE * sizeof(int));
	if (!s.base)
		exit(0);
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return s;
}
int Gettop1(Sqstack1 s, char& e)
{
	if (s.top == s.base)
		return 0;
	e = *(s.top - 1);
	return 1;
}
int Gettop2(Sqstack2 s, int& e)
{
	if (s.top == s.base)
		return 0;
	e = *(s.top - 1);
	return 1;
}
int Push1(Sqstack1& s, char e)
{
	if (s.top - s.base >= s.stacksize)
	{
		s.base = (char*)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(char));
		if (!s.base)
			return 0;
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	}
	*s.top++ = e;
	return 1;
}
int Push2(Sqstack2& s, int e)
{
	if (s.top - s.base >= s.stacksize)
	{
		s.base = (int*)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(int));
		if (!s.base)
			return 0;
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	}
	*s.top++ = e;
	return 1;
}
int Pop1(Sqstack1& s, char& e)
{
	if (s.top == s.base)
		return 0;
	e = *--s.top;
	return 1;
}
int Pop2(Sqstack2& s, int& e)
{
	if (s.top == s.base)
		return 0;
	e = *--s.top;
	return 1;
}
int In(char c)
{
	switch (c)
	{
	case'+':
	case'-':
	case'*':
	case'/':
	case'(':
	case')':
	case'=':
		return 1;
	default:
		return 0;
	}
}
char Precede(char a, char b)
{
	int i, j;
	char pre[][10] =
	{
		{'>','>','<','<','<','>','>'},
		{'>','>','<','<','<','>','>'},
		{'>','>','>','>','<','>','>'},
		{'>','>','>','>','<','>','>'},
		{'<','<','<','<','<','=','0'},
		{'>','>','>','>','0','>','>'},
		{'<','<','<','<','<','0','='}
	};
	switch (a)
	{
	case'+':i = 0; break;
	case'-':i = 1; break;
	case'*':i = 2; break;
	case'/':i = 3; break;
	case'(':i = 4; break;
	case')':i = 5; break;
	case'=':i = 6; break;
	}
	switch (b)
	{
	case'+':j = 0; break;
	case'-':j = 1; break;
	case'*':j = 2; break;
	case'/':j = 3; break;
	case'(':j = 4; break;
	case')':j = 5; break;
	case'=':j = 6; break;
	}
	return pre[i][j];
}
int Operate(int a, char b, int c)
{
	switch (b)
	{
	case'+':a = a + c; break;
	case'-':a = a - c; break;
	case'*':a = a * c; break;
	case'/':a = a / c; break;
	}
	return a;
}
int Evaluateexpression()
{
	char c, x, m, theta;
	int a, b, d;
	Sqstack1 Optr;
	Sqstack2 Opnd;
	Optr = Initstack1();
	Opnd = Initstack2();
	Push1(Optr, '=');
	c = getchar();
	Gettop1(Optr, x);
	while (c != '=' || x != '=')
	{
		if (In(c))
		{
			switch (Precede(x, c))
			{
			case'<':
				Push1(Optr, c);
				c = getchar();
				break;
			case'=':
				if (c == '=')
					break;
				Pop1(Optr, m);
				c = getchar();
				break;
			case'>':
				Pop1(Optr, theta);
				Pop2(Opnd, b);
				Pop2(Opnd, a);
				d = Operate(a, theta, b);
				Push2(Opnd, d);
				break;
			}
		}
		else if (c >= '0' && c <= '9')
		{
			a = c - 48;
			c = getchar();
			while (c >= '0' && c <= '9')
			{
				a = a * 10 + c - 48;
				c = getchar();
			}
			Push2(Opnd, a);


		}
		else
			return 0;
		Gettop1(Optr, x);
	}
	Gettop2(Opnd, a);
	return a;
}
int main()
{
	int a;
	a = Evaluateexpression();
	printf("%d", a);
	return 0;
}