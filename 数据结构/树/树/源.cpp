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
typedef char** Huffmancode;       //动态分配数组存储赫夫曼编码表
int main()
{
    //------------构造赫夫曼树及赫夫曼编码-------------------
    //---------Huffmancoding---------------------------------
    Huffmantree HT;
    Huffmancode HC;
    char* cd, s[100], g[100];
    int n, mm, m, i, j = 0, f, start, c, s1 = 0, s2 = 0, temp1, temp2;
    int w[26];

    int a[26] = { 0 };
    printf("请输入一段字符：");
    gets_s(s);
    n = strlen(s);
    //HT=(Huffmantree )malloc((m+1)*sizeof(HTnode));//0号单元未用
    for (i = 0; i < n; i++)
        a[s[i] - 'a']++;
    for (i = 0; i < 26; i++)
        if (a[i] != 0)
        {
            w[j] = a[i];
            j++;
        }
    //w存放n个字符的权值（均>0），构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
    n = j;
    m = 2 * j - 1;
    HT = (Huffmantree)malloc((m + 1) * sizeof(HTnode));//0号单元未用
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
    }      //n个叶子赋初值
    for (; i <= m; ++i)
        HT[i].weight = HT[i].parent = HT[i].lchild = HT[i].rchild = 0;        //除叶子外的节点赋初值

    for (i = n + 1; i <= m; i++)
    {
        //建赫夫曼树
        //在HT[1..i-1]选择parent为0且weight最小的两个节点，其序号为别为s1,s2.
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
        HT[i].weight = HT[s1].weight + HT[s2].weight;//父节点权值为左右两孩子权值之和
    }
    printf("num  weight lchild parent rchild    ch\n");
    for (i = 1; i <= m; i++)
        printf("%-4d%4d%8d%8d%8d%6c\n", i, HT[i].weight, HT[i].lchild, HT[i].parent, HT[i].rchild, HT[i].ch);

    //---------------从叶子到根逆向求每个字符的赫夫曼编码--------------------

    HC = (Huffmancode)malloc((n + 1) * sizeof(char*)); //分配n个字符编码的头指针向量
    cd = (char*)malloc(n * sizeof(char));      //非配求编码的工作空间
    cd[n - 1] = '\0';                //编码结束符
    for (i = 1; i <= n; ++i)            //逐个求赫夫曼编码
    {
        start = n - 1;               //编码结束符位置
        for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)   //从叶子到根逆向求编码
            if (HT[f].lchild == c)
                cd[--start] = '0';
            else cd[--start] = '1';
        HC[i] = (char*)malloc((n - start) * sizeof(char));  //为第i个字符编码分配空间
        strcpy(HC[i], cd + start);     //从cd复制编码到HC
    }
    free(cd);
    printf("\nnum  bianma\n");
    for (i = 1; i <= n; i++)
        printf("%-5d%s\n", i, HC[i]);
    //--------------Huffmancoding-----------------------------------------------------
    printf("\n请输入一段0-1编码\n");
    gets_s(g);
    printf("\n解码后为:");
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