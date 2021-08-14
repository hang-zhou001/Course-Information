#ifndef 源_H
#define 源_H

typedef struct
{
	int c;
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;                                              //动态分配数组存储哈夫曼树

typedef char** HuffmanCode;                                          //动态分配数组存储哈夫曼编码

void Select(HuffmanTree HT, int n, int* s1, int* s2);
void HuffmanCoding(HuffmanTree HT, HuffmanCode HC, int* w, int n, char* s);
int saveTree(HuffmanTree HT, char* path, int total);
int saveCode(HuffmanCode HC, char* path, int n, char* s);
int readTree(HuffmanTree HC, char* path);
HTNode praseTree(char* pBuf);
int readCode(char* s, char* path);
char praseCode(char* pBuf);
void makeTreeCode();
void HuffmanTranslateCoding();

#define TREEPATH "tree.txt"
#define CODEPATH "code.txt"

#endif // !源_H