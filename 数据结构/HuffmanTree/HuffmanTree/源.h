#ifndef Դ_H
#define Դ_H

typedef struct
{
	int c;
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;                                              //��̬��������洢��������

typedef char** HuffmanCode;                                          //��̬��������洢����������

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

#endif // !Դ_H