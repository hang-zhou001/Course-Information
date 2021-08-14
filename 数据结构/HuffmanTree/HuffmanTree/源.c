#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "源.h"

void Select(HuffmanTree T, int n, int* s1, int* s2)                  //在HT[1...n]选择parent为0且weight最小的两个结点，其序号分别为*s1,*s2
{
	int i = 0;
	int t = 0;
	int min1 = 0;
	int min2 = 0;
	int flag = 0;
	int count = 0;

	for (i = 1; i <= n; i++)                                            //选择前两个parent为0的结点，将其权重初始化赋值给min1，min2
	{
		if (T[i].parent == 0)
		{
			if (count == 0)                                                   //第一个双亲为0的给min1进行权重初始化
			{
				min1 = T[i].weight;
				*s1 = i;
			}
			if (count == 1)                                                   //第二个双亲为零的给min2进行权重初始化
			{
				min2 = T[i].weight;
				*s2 = i;
			}
			count++;                                                          //count++放在循环的最后，防止s1=s2,若每个if里面都有，则很大的可能s1=s2
		}
		if (count == 2)                                                    //min1、min2初始化结束
			break;
	}
	i++;
	for (i; i <= n; i++)                                            //从剩余的里面找权重最小的
	{
		flag = 0;                                                          //flag用于保证s1、s2不会取到相同的值
		if ((int)T[i].weight < min1 && T[i].parent == 0)
		{
			min1 = T[i].weight;
			flag = 1;
			*s1 = i;
		}
		if ((int)T[i].weight < min2 && T[i].parent == 0 && flag == 0)
		{
			min2 = T[i].weight;
			*s2 = i;
		}
	}
}

void HuffmanCoding(HuffmanTree HT, HuffmanCode HC, int* w, int n, char* s)
{
	int m, i; 
	HuffmanTree p;

	if (n <= 1)
		return;                                                            //结点个数为一，不存在哈夫曼树
	m = 2 * n - 1;                                                      //n个叶子结点的哈夫曼树共有（2n-1）个结点

	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));                 //一共（m+1)个存储空间，因为0号单元未用
	p = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	if (HT == NULL || p == NULL)
		return;

	p = HT; p++;                                                        //p从HT[1]开始存储数据，若没有这一步，第一组数据将会漏掉
	for (i = 1; i <= n; i++, p++)                                       //初始化每个存储单元，将权重赋值
	{
		p->c = i;
		p->weight = w[i];
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for (i = n + 1; i <= m; i++, p++)                                            //剩余的存储空间初始化
	{
		p->c = i;
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}

	int s1, s2;

	for (i = n + 1; i <= m; i++)                                        //构造哈夫曼树
	{
		Select(HT, i - 1, &s1, &s2);                                         //在HT[1...i-1]选择parent为0且weight最小的两个结点，其序号分别为s1,s2
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	//打印哈弗曼树  
	printf("哈夫曼树:\n");
	printf("序号\t\t权重\t\t双亲\t\t左孩子\t\t右孩子\n");

	for (i = 1; i <= m; i++)
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\n", HT[i].c, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);

	if (saveTree(HT, TREEPATH, m) == 1)
		printf("哈夫曼树保存成功！\n\n");
	else
		printf("哈夫曼树保存失败。\n\n");

	//从叶子到根逆向求每个字符的哈夫曼编码

	char* cd;
	int c = 0;
	int start = 0;
	int f = 0;

	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));                  //分配n个字符编码的头指针向量
	if (HC == NULL)
		return;
    cd = (char*)malloc(n * sizeof(char));                            //分配求编码的工作空间
	if (cd == NULL)
		return;
	cd[n - 1] = '\0';                                                   //编码结束符

	for (i = 1; i <= n; i++)                                            //逐个字符求哈夫曼编码
	{
		start = n - 1;                                                     //编码结束符
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy_s(HC[i], sizeof(&cd[start]) + 1, &cd[start]);
	}

	printf("字符\t\t编码\n");
	for (i = 1; i <= n; i++)
		printf("%c\t\t%s\n", s[i], HC[i]);

	if (saveCode(HC, CODEPATH, n, s) == 1)
		printf("哈夫曼编码保存成功！\n\n");
	else
		printf("哈夫曼编码保存失败！\n\n");

	free(cd);
}

int saveTree(HuffmanTree HT, char* path,int total)
{
	int i = 0;
	FILE* fp = NULL;
	errno_t err;
	err = fopen_s(&fp, path, "a");
	if (err != 0) return 0;
	for (i = 1; i <= total; i++)
		fprintf(fp, "%d##%d##%d##%d##%d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	                                      //序号  权重  双亲  左孩子  右孩子
	fclose(fp);
	return 1;
}

int readTree(HuffmanTree HT, char* path)
{

	FILE* fp = NULL;
	char cBuf[256] = { '0' };
	int i = 1;
	errno_t err;
	err = fopen_s(&fp, path, "r");
	if (err != 0) return 0;
	while (!feof(fp))                            //feof()是检测流上的文件结束符的函数，如果文件结束，则返回非0值，否则返回0
	{
		memset(cBuf, '0', 256);          //清空数组
		if (fgets(cBuf, 256, fp) != NULL)
		{
			if (strlen(cBuf) > 0)
			{
				HT[i] = praseTree(cBuf);
				i++;
			}
		}
	}
	fclose(fp);
	return i - 1;
}

HTNode praseTree(char* pBuf)
{
	HTNode node;
	char* delims = "##";
	char* buf = NULL;
	char* str = NULL;
	char* context;
	char flag[20][20] = { '0' };                 //保存分割后的字符串
	int index = 0;
	buf = pBuf;
	str = strtok_s(buf, delims, &context);
	while (str != NULL)
	{
		if (str != NULL)
		{
			strcpy_s(flag[index], sizeof(str) + 20, str);
			buf = NULL;
			str = strtok_s(buf, delims, &context);
			index++;
		}
	}

	//序号  权重  双亲  左孩子  右孩子
	node.c = atoi(flag[0]);
	node.weight = atoi(flag[1]);
	node.parent = atoi(flag[2]);
	node.lchild = atoi(flag[3]);
	node.rchild = atoi(flag[4]);

	return node;
}

int readCode(char* s, char* path)
{

	FILE* fp = NULL;
	char cBuf[256] = { '0' };
	int i = 1;
	errno_t err;
	err = fopen_s(&fp, path, "r");
	if (err != 0) return 0;
	while (!feof(fp))                            //feof()是检测流上的文件结束符的函数，如果文件结束，则返回非0值，否则返回0
	{
		memset(cBuf, '0', 256);          //清空数组
		if (fgets(cBuf, 256, fp) != NULL)
		{
			if (strlen(cBuf) > 0)
			{
				s[i] = praseCode(cBuf);
				i++;
			}
		}
	}
	fclose(fp);
	return 1;
}

char praseCode(char* pBuf)
{
	char c;
	char* delims = "##";
	char* buf = NULL;
	char* str = NULL;
	char* context;
	char flag[10][10] = { '0' };                 //保存分割后的字符串
	int index = 0;
	buf = pBuf;
	str = strtok_s(buf, delims, &context);
	while (str != NULL)
	{
		if (str != NULL)
		{
			strcpy_s(flag[index], sizeof(str) + 20, str);
			buf = NULL;
			str = strtok_s(buf, delims, &context);
			index++;
		}
	}

	//序号  权重  双亲  左孩子  右孩子
	c = *flag[0];

	return c;
}

int saveCode(HuffmanCode HC, char* path, int n,char* s)
{
	int i = 0;
	FILE* fp = NULL;
	errno_t err;
	err = fopen_s(&fp, path, "a");
	if (err != 0) return 0;
	for (i = 1; i <= n; i++)
		fprintf(fp, "%c##%s\n", s[i], HC[i]);
	fclose(fp);
	return 1;
}

void makeTreeCode()
{
	char s[100] = { 0 };
	int w[100] = { 0 };
	char c;
	int n = 0;
	int i = 0;
	int flag = 0;

	printf("请输入需要编码的字符：");
	c = getchar();
	while (c != '\n')
	{
		flag = 0;
		for (i = 0; i <= n; i++)
		{
			if (s[i] == c)
			{
				w[i]++;
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			n++;
			s[n] = c;
			w[n] = 1;
		}
		c = getchar();
	}

	printf("字符\t权重\n");
	for (i = 1; i <= n; i++)
	{
		printf("%c\t", s[i]);
		printf("%d\n", w[i]);
	}

	HuffmanTree HT;
	HT = (HuffmanTree)malloc(sizeof(HTNode));
	HuffmanCode HC;
	HC = (HuffmanCode)malloc(sizeof(char*));

	HuffmanCoding(HT, HC, w, n, s);
}

void HuffmanTranslateCoding()
{
	char ch[100];
	printf("请输入您要译码的0-1序列：\n");
	scanf_s("%s", ch, 100);

	HuffmanTree HT;
	HT = (HuffmanTree)malloc(100*sizeof(HTNode));
	int m = readTree(HT, TREEPATH);                                     //m为哈夫曼树的节点个数

	char s[20] = { '\0' };
	readCode(s, CODEPATH);

	int i = 0;
	int j = 0;

	printf("译码后：\n");
	while (ch[j] != '\0') 
	{
		i = m;
		while ((HT[i].lchild != 0) && (HT->rchild != 0))                     //从顶部找到最下面  
		{
			if (ch[j] == '0')                                                 //0 往左子树走  
			{
				i = HT[i].lchild;
			}
			else                                                              //1 往右子树走  
			{
				i = HT[i].rchild;
			}
			++j;                                                              //下一个路径  
		}
		printf("%c", s[i]);                                                //打印出来  
	}
	printf("\n");
}

int main()
{
	int choice = 0;
	char c;

	do
	{
		printf("请选择：1.编码 2.解码 0.退出\n");
		printf("注：若已编码，请不要再次编码！\n");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1: 
			c = getchar();
			makeTreeCode();
			break;
		case 2: 
			c = getchar();
			HuffmanTranslateCoding();
			break;
		case 0:
			printf("退出成功！\n");
			break;
		default:
			printf("选项有误！\n");
			break;
		}
	}while (choice != 0);



	return 0;
}