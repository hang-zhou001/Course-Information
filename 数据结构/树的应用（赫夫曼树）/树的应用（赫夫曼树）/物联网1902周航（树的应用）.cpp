#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>  
#include<string.h>  
#include<stdlib.h> 
typedef struct
{
	int weight;
	int parent, lchild, rchild;
}HTnode, * Huffmantree;
typedef char** Huffmancode;
typedef struct
{
	int s1;
	int s2;
}Mincode;
static char m[100];
Mincode Select(Huffmantree HT, int n);
Huffmantree Tree(int * w, int n)
{
	Huffmantree HT, p;
	Mincode code;
	int i,s1,s2;
	if (n <= 1)
		return NULL;
	int m = 2 * n - 1;
	HT = (Huffmantree)malloc((m + 1) * sizeof(HTnode));
	for (p = HT, i = 0; i <= n; ++i,++p,w++)
	{
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for (i=n+1; i <= m; i++,p++)
	{
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for (i = n + 1; i <= m; i++)
	{
		code = Select(HT, i-1);
		s1 = code.s1;
		s2 = code.s2;
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	return HT;
}
Huffmancode Huffmancoding(Huffmantree HT, int n)
{
	Huffmancode HC;
	char* cd;
	int i,start,f,c;
	HC = (Huffmancode)malloc((n + 1) * sizeof(char*));
	cd = (char*)malloc(n * sizeof(char*));
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		HC[i] = (char*)malloc((n - start) * sizeof(char*));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
	return HC;
}
Mincode Select(Huffmantree HT, int n)
{
	Mincode code;
	int  i,a=10000, b=10000;
	for (i = 1; i <= n; i++)
	{
		if (HT[i].weight < a && HT[i].parent == 0)
		{
			a = HT[i].weight;
			code.s1 = i;
		}
	}
	for (i = 1; i <= n; i++)
	{
		if (HT[i].weight < b && HT[i].parent == 0&&(i!=code.s1))
		{
			b = HT[i].weight;
			code.s2 = i;
		}
	}
	return code;
}
int main()
{
		Huffmantree HT;
		Huffmancode HC;
		int i, n,j=1;
		char N[100],p[100],tran[100];
		p[0] = '0';
		int	c[200] = { 0 };
		scanf("%s", N);
		fflush(stdin);
		n = strlen(N);
		int* w;
		w = (int*)malloc((n + 1) * sizeof(int));
		w[0] = 0;
		for(i=0;i<=n-1;i++)
		{
			c[N[i]]++;
			if (c[N[i]] == 1)
			{
				p[j] = N[i];
				j++;
			}
	    }  
		printf("%d\n", j-1);
		for (i = 1; i <= j-1; i++)
		{
			w[i] = c[p[i]];
		}
		HT = Tree(w , j-1);
		if (!HT)
		{
			printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\n", 1, w[1], 0, 0, 0);
		}
		else
		{
			printf("HT  List:\n");
			printf("Number\t\tweight\t\tparent\t\tlchild\t\trchild\n");
			for (i = 1; i <= 2 * j - 3; i++)
			{
				printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
			}
		}
		HC = Huffmancoding(HT, j-1);
		for (i = 1; i <= j-1; i++)
		{
			printf("%c\t\t%d\t\t%s\n", p[i], w[i], HC[i]);
		}
		printf("Input HuffmanTranslateCoding:");
		return 0;
}