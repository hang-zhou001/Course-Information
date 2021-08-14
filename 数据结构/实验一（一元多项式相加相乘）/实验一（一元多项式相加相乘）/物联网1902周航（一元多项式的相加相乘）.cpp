#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct Lnode
{
	int coef;
	int expn;
	struct Lnode* next;
}Lnode, * Linklist;
Linklist  Creatpolyn() //按指数递减依次输入每一项的系数和指数，最后多项式以0 0表示多项式输入完毕
{
	Linklist p, head, L;
	head = (Linklist)malloc(sizeof(Lnode));
	L = (Lnode*)malloc(sizeof(Lnode));
	printf("输入多项式的系数和指数:\n");
	scanf("%d%d", &L->coef, &L->expn);
	p = head;
	while (L->coef != 0 )
	{
		p->next = L;
		p = L;
		L = (Lnode*)malloc(sizeof(Lnode));
		printf("继续输入多项式的系数和指数:\n");
		scanf("%d%d", &L->coef, &L->expn);
	}
	p->next = NULL;
	return head;
}
int Compare(int x, int y)
{
	if (x > y)
		return 1;
	else if (x == y)
		return 0;
	else
		return -1;
}

Linklist Addpolyn(Linklist L1, Linklist L2)
{
	Linklist p1, p2, p3, node;
	Linklist L = (Linklist)malloc(sizeof(Lnode));
	p3 = L;
	p1 = L1->next;
	p2 = L2->next;
	while (p1 && p2)
	{
		node = (Linklist)malloc(sizeof(Lnode));
		if (p1->expn > p2->expn)
		{
			node->coef = p1->coef;
			node->expn = p1->expn;
			p3->next = node;
			p3 = node;
			p1 = p1->next;
		}
		else if (p1->expn == p2->expn)
		{
			if (p1->coef + p2->coef != 0)
			{
				node->coef = p1->coef + p2->coef;
				node->expn = p1->expn;
				p3->next = node;
				p3 = node;
				p1 = p1->next;
				p2 = p2->next;
			}
			else
			{
				p1 = p1->next;
				p2 = p2->next;
			}
		}
		else
		{
			node->coef = p2->coef;
			node->expn = p2->expn;
			p3->next = node;
			p3 = node;
			p2 = p2->next;
		}
	}
	while (p1)
	{
		node = (Linklist)malloc(sizeof(Lnode));
		node = p1;
		p3->next = node;
		p3 = node;
		p1 = p1->next;
	}
	while (p2)
	{
		node = (Linklist)malloc(sizeof(Lnode));
		node = p2;
		p3->next = node;
		p3 = node;
		p2 = p2->next;
	}
	p3->next = NULL;
	return L;
}
void show(Linklist L)
{
	Linklist p;
	p = L->next;
	if (p)
	{
		while (p)
		{
			if (p->next)
			{
				printf("(%dx^%d)+", p->coef, p->expn);
				p = p->next;
			}
			else
			{
				printf("(%dx^%d)", p->coef, p->expn);
				p = p->next;
			}
		}
	}
	else
		printf("0 0");

}
Linklist Multply(Linklist L1, Linklist L2)
{
	Linklist p, L3, L4, p1, p2,p0;
	L3 = (Linklist)malloc(sizeof(Lnode));
	
	L3->next = NULL;
	p1 = L1->next;
	p2 = L2->next;
	while (p1 != NULL)
	{
		L4 = (Linklist)malloc(sizeof(Lnode));
		p = L4;
		while (p2 != NULL)
		{
			Linklist p3 = (Linklist)malloc(sizeof(Lnode));
			p3->coef = p1->coef * p2->coef;
			p3->expn = p1->expn + p2->expn;
			p->next = p3;
			p = p3;
			p2 = p2->next;
		}
		p2 = L2->next;
		p->next = NULL;
		L3 = Addpolyn(L3, L4);
		p1 = p1->next;
	}
	return L3;
}


int main()
{
	Linklist L1, L2, L3, L4;
	L1 = Creatpolyn();
	L2 = Creatpolyn();
	L3 = Addpolyn(L1, L2);
	printf("多项式相加的结果为：\n");
	show(L3);
	printf("\n");
	printf("多项式相乘的结果为：\n");
	L4 = Multply(L1, L2);
	show(L4);
	return 0;

}