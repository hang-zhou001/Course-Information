#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct
{
    char ch;
    int weight;
    int parent, lchild, rchild;
}HTnode, * Huffmantree;
typedef char** Huffmancode;       //��̬��������洢�շ��������
int main()
{
    //------------����շ��������շ�������-------------------
    //---------Huffmancoding---------------------------------
    Huffmantree HT;
    Huffmancode HC;
    char* cd, s[100], g[100];
    int n, mm, m, i, j = 0, f, start, c, s1 = 0, s2 = 0, temp1, temp2;
    int w[26];

    int a[26] = { 0 };
    printf("������һ���ַ���");
    gets_s(s);
    n = strlen(s);
    //HT=(Huffmantree )malloc((m+1)*sizeof(HTnode));//0�ŵ�Ԫδ��
    for (i = 0; i < n; i++)
        a[s[i] - 'a']++;
    for (i = 0; i < 26; i++)
        if (a[i] != 0)
        {
            w[j] = a[i];
            j++;
        }
    //w���n���ַ���Ȩֵ����>0��������շ�����HT�������n���ַ��ĺշ�������HC
    n = j;
    m = 2 * j - 1;
    HT = (Huffmantree)malloc((m + 1) * sizeof(HTnode));//0�ŵ�Ԫδ��
    for (i = 0, j = 0; i < 26; i++)
        if (a[i] != 0)
        {
            HT[j + 1].ch = i + 'a';
            j++;
        }

    for (i = 1, j = 0; i <= n; ++i, ++j)
    {
        HT[i].weight = w[j];
        HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
    }      //n��Ҷ�Ӹ���ֵ
    for (; i <= m; ++i)
        HT[i].weight = HT[i].parent = HT[i].lchild = HT[i].rchild = 0;        //��Ҷ����Ľڵ㸳��ֵ

    for (i = n + 1; i <= m; i++)
    {
        //���շ�����
        //��HT[1..i-1]ѡ��parentΪ0��weight��С�������ڵ㣬�����Ϊ��Ϊs1,s2.
        temp1 = temp2 = 100;
        for (j = 1; j <= i - 1; j++)
            if (HT[j].parent == 0)
                if (HT[j].weight < temp1)
                {
                    temp1 = HT[j].weight;
                    s1 = j;
                }
        for (j = 1; j <= i - 1; j++)
            if (HT[j].parent == 0 && j != s1)
                if (HT[j].weight < temp2)
                {
                    temp2 = HT[j].weight;
                    s2 = j;
                }
        HT[s1].parent = i; HT[s2].parent = i;
        HT[i].lchild = s1; HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;//���ڵ�ȨֵΪ����������Ȩֵ֮��
    }
    printf("num  weight lchild parent rchild    ch\n");
    for (i = 1; i <= m; i++)
        printf("%-4d%4d%8d%8d%8d%6c\n", i, HT[i].weight, HT[i].lchild, HT[i].parent, HT[i].rchild, HT[i].ch);

    //---------------��Ҷ�ӵ���������ÿ���ַ��ĺշ�������--------------------

    HC = (Huffmancode)malloc((n + 1) * sizeof(char*)); //����n���ַ������ͷָ������
    cd = (char*)malloc(n * sizeof(char));      //���������Ĺ����ռ�
    cd[n - 1] = '\0';                //���������
    for (i = 1; i <= n; ++i)            //�����շ�������
    {
        start = n - 1;               //���������λ��
        for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)   //��Ҷ�ӵ������������
            if (HT[f].lchild == c)
                cd[--start] = '0';
            else cd[--start] = '1';
        HC[i] = (char*)malloc((n - start) * sizeof(char));  //Ϊ��i���ַ��������ռ�
        strcpy(HC[i], cd + start);     //��cd���Ʊ��뵽HC
    }
    free(cd);
    printf("\nnum  bianma\n");
    for (i = 1; i <= n; i++)
        printf("%-5d%s\n", i, HC[i]);
    //--------------Huffmancoding-----------------------------------------------------
    printf("\n������һ��0-1����\n");
    gets_s(g);
    printf("\n�����Ϊ:");
    mm = m;
    for (i = 0; i <= (signed)strlen(g);)
    {
        if (HT[mm].lchild == 0 && HT[mm].rchild == 0)
        {
            printf("%c", HT[mm].ch);
            mm = m;
            //continue;
        }
        else
        {
            if (g[i] == '0')
            {
                mm = HT[mm].lchild;
                i++;
            }
            else
            {
                mm = HT[mm].rchild;
                i++;
            }
        }
    }
    printf("\n");
    return 0;
}