#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Դ.h"

void Select(HuffmanTree T, int n, int* s1, int* s2)                  //��HT[1...n]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊ*s1,*s2
{
	int i = 0;
	int t = 0;
	int min1 = 0;
	int min2 = 0;
	int flag = 0;
	int count = 0;

	for (i = 1; i <= n; i++)                                            //ѡ��ǰ����parentΪ0�Ľ�㣬����Ȩ�س�ʼ����ֵ��min1��min2
	{
		if (T[i].parent == 0)
		{
			if (count == 0)                                                   //��һ��˫��Ϊ0�ĸ�min1����Ȩ�س�ʼ��
			{
				min1 = T[i].weight;
				*s1 = i;
			}
			if (count == 1)                                                   //�ڶ���˫��Ϊ��ĸ�min2����Ȩ�س�ʼ��
			{
				min2 = T[i].weight;
				*s2 = i;
			}
			count++;                                                          //count++����ѭ������󣬷�ֹs1=s2,��ÿ��if���涼�У���ܴ�Ŀ���s1=s2
		}
		if (count == 2)                                                    //min1��min2��ʼ������
			break;
	}
	i++;
	for (i; i <= n; i++)                                            //��ʣ���������Ȩ����С��
	{
		flag = 0;                                                          //flag���ڱ�֤s1��s2����ȡ����ͬ��ֵ
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
		return;                                                            //������Ϊһ�������ڹ�������
	m = 2 * n - 1;                                                      //n��Ҷ�ӽ��Ĺ����������У�2n-1�������

	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));                 //һ����m+1)���洢�ռ䣬��Ϊ0�ŵ�Ԫδ��
	p = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	if (HT == NULL || p == NULL)
		return;

	p = HT; p++;                                                        //p��HT[1]��ʼ�洢���ݣ���û����һ������һ�����ݽ���©��
	for (i = 1; i <= n; i++, p++)                                       //��ʼ��ÿ���洢��Ԫ����Ȩ�ظ�ֵ
	{
		p->c = i;
		p->weight = w[i];
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for (i = n + 1; i <= m; i++, p++)                                            //ʣ��Ĵ洢�ռ��ʼ��
	{
		p->c = i;
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}

	int s1, s2;

	for (i = n + 1; i <= m; i++)                                        //�����������
	{
		Select(HT, i - 1, &s1, &s2);                                         //��HT[1...i-1]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1,s2
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	//��ӡ��������  
	printf("��������:\n");
	printf("���\t\tȨ��\t\t˫��\t\t����\t\t�Һ���\n");

	for (i = 1; i <= m; i++)
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\n", HT[i].c, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);

	if (saveTree(HT, TREEPATH, m) == 1)
		printf("������������ɹ���\n\n");
	else
		printf("������������ʧ�ܡ�\n\n");

	//��Ҷ�ӵ���������ÿ���ַ��Ĺ���������

	char* cd;
	int c = 0;
	int start = 0;
	int f = 0;

	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));                  //����n���ַ������ͷָ������
	if (HC == NULL)
		return;
    cd = (char*)malloc(n * sizeof(char));                            //���������Ĺ����ռ�
	if (cd == NULL)
		return;
	cd[n - 1] = '\0';                                                   //���������

	for (i = 1; i <= n; i++)                                            //����ַ������������
	{
		start = n - 1;                                                     //���������
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy_s(HC[i], sizeof(&cd[start]) + 1, &cd[start]);
	}

	printf("�ַ�\t\t����\n");
	for (i = 1; i <= n; i++)
		printf("%c\t\t%s\n", s[i], HC[i]);

	if (saveCode(HC, CODEPATH, n, s) == 1)
		printf("���������뱣��ɹ���\n\n");
	else
		printf("���������뱣��ʧ�ܣ�\n\n");

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
	                                      //���  Ȩ��  ˫��  ����  �Һ���
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
	while (!feof(fp))                            //feof()�Ǽ�����ϵ��ļ��������ĺ���������ļ��������򷵻ط�0ֵ�����򷵻�0
	{
		memset(cBuf, '0', 256);          //�������
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
	char flag[20][20] = { '0' };                 //����ָ����ַ���
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

	//���  Ȩ��  ˫��  ����  �Һ���
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
	while (!feof(fp))                            //feof()�Ǽ�����ϵ��ļ��������ĺ���������ļ��������򷵻ط�0ֵ�����򷵻�0
	{
		memset(cBuf, '0', 256);          //�������
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
	char flag[10][10] = { '0' };                 //����ָ����ַ���
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

	//���  Ȩ��  ˫��  ����  �Һ���
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

	printf("��������Ҫ������ַ���");
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

	printf("�ַ�\tȨ��\n");
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
	printf("��������Ҫ�����0-1���У�\n");
	scanf_s("%s", ch, 100);

	HuffmanTree HT;
	HT = (HuffmanTree)malloc(100*sizeof(HTNode));
	int m = readTree(HT, TREEPATH);                                     //mΪ���������Ľڵ����

	char s[20] = { '\0' };
	readCode(s, CODEPATH);

	int i = 0;
	int j = 0;

	printf("�����\n");
	while (ch[j] != '\0') 
	{
		i = m;
		while ((HT[i].lchild != 0) && (HT->rchild != 0))                     //�Ӷ����ҵ�������  
		{
			if (ch[j] == '0')                                                 //0 ����������  
			{
				i = HT[i].lchild;
			}
			else                                                              //1 ����������  
			{
				i = HT[i].rchild;
			}
			++j;                                                              //��һ��·��  
		}
		printf("%c", s[i]);                                                //��ӡ����  
	}
	printf("\n");
}

int main()
{
	int choice = 0;
	char c;

	do
	{
		printf("��ѡ��1.���� 2.���� 0.�˳�\n");
		printf("ע�����ѱ��룬�벻Ҫ�ٴα��룡\n");
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
			printf("�˳��ɹ���\n");
			break;
		default:
			printf("ѡ������\n");
			break;
		}
	}while (choice != 0);



	return 0;
}