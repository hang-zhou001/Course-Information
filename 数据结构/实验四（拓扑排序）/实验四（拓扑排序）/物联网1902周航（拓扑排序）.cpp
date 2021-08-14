#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h> 
using namespace std;
typedef int SElemType;
#define STACK_INIT_SIZE 10
#define STACKINCREMENT 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
typedef int Status; 
typedef int Boolean;
#define MAX_NAME 10   
#define MAX_CLASS_NUM 100
typedef int InfoType;
typedef char VertexType[MAX_NAME]; 
#define MAX_VERTEX_NUM 100
typedef enum { DG }GraphKind;  
typedef struct SqStack 
{
    SElemType* base;
    SElemType* top;
    int stacksize;
}SqStack;
typedef struct ArcNode 
{     
    int adjvex;      //该弧所指向的顶点的位置
    struct ArcNode* nextarc;   //指向下一条弧的指针
    InfoType* info;   //该弧相关信息的指针
}ArcNode;    
typedef struct 
{
    VertexType data; //顶点信息
    ArcNode* firstarc; //指向第一条依附于该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct 
{
    AdjList vertices, vertices2;   
    int vexnum, arcnum;//图的顶点数和弧数
    int kind;
}ALGraph;
int LocateVex(ALGraph G, VertexType u) 
{
    int i;
    for (i = 0; i < G.vexnum; ++i)
        if (strcmp(u, G.vertices[i].data) == 0)
           return i;
    return -1;
}
Status CreateGraph(ALGraph& G) {
    int i, j, k;
    VertexType v1, v2;  
    ArcNode* p;       
    printf("请输入教学计划的课程数: ");
    scanf("%d", &G.vexnum);
    printf("请输入课程先修关系数（弧的数目）: ");
    scanf("%d", &G.arcnum);
    printf("请输入%d个课程的代表值(如:c01):\n", G.vexnum);
    for (i = 0; i < G.vexnum; ++i) {
       scanf("%s", G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    printf("请输入%d个课程的学分值:\n", (G).vexnum);
    for (i = 0; i < G.vexnum; ++i) 
    {
        scanf("%s", G.vertices2[i].data);
    }
    printf("请顺序输入每条弧的弧尾和弧头(以空格作为间隔):\n");
    for (k = 0; k < G.arcnum; ++k) 
    {
        scanf("%s%s", v1, v2);
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        p = (ArcNode*)malloc(sizeof(ArcNode)); 
        p->adjvex = j;
        p->info = NULL;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }
    return OK;
}
void FindInDegree(ALGraph G, int indegree[]) 
{
    int i;
    ArcNode* p;
    for (i = 0; i < G.vexnum; i++)
        indegree[i] = 0;
    for (i = 0; i < G.vexnum; i++) 
    {
        p = G.vertices[i].firstarc;
        while (p) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
}
Status InitStack(SqStack* S) {
    (*S).base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!(*S).base)
        exit(OVERFLOW);
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}
Status StackEmpty(SqStack S) {
    if (S.top == S.base)
        return TRUE;
    else
        return FALSE;
}
Status Pop(SqStack* S, SElemType* e) {
    if ((*S).top == (*S).base)
        return ERROR;
    *e = *--(*S).top;
    return OK;
}
Status Push(SqStack* S, SElemType e) {
    if ((*S).top - (*S).base >= (*S).stacksize) {
        (*S).base = (SElemType*)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!(*S).base)
            exit(OVERFLOW);
        (*S).top = (*S).base + (*S).stacksize;
        (*S).stacksize += STACKINCREMENT;
    }
    *((*S).top)++ = e;
    return OK;
}
Status zxf(ALGraph G) { //求大学所有课程总学分；
    int z = 0;
    for (int i = 0; i < G.vexnum; i++) {
        z += atoi(G.vertices2[i].data);
    }
    return z;
}
Status TopologicalSort(ALGraph G) 
{
    int i, k, count, indegree[MAX_VERTEX_NUM];
    bool has = false;
    SqStack S;
    int a[MAX_CLASS_NUM];
    int b[MAX_CLASS_NUM];
    ArcNode* p;
    FindInDegree(G, indegree);
    InitStack(&S);
    for (i = 0; i < G.vexnum; ++i) 
    {
        if (!indegree[i])
            Push(&S, i);
    }
    count = 0;
    while (!StackEmpty(S)) 
    {
        Pop(&S, &i);
        a[i] = *G.vertices[i].data;  //课程名；
        b[i] = *G.vertices2[i].data;  //学分；
        printf("课程%s→学分%s  ", G.vertices[i].data, G.vertices2[i].data);
        ++count;
        for (p = G.vertices[i].firstarc; p; p = p->nextarc) 
        {
            k = p->adjvex;
            if (!(--indegree[k]))
                Push(&S, k);
        }
    }
    if (count < G.vexnum) 
    {
        printf("此有向图有回路\n");
        return ERROR;
    }
    else {
        return OK;
    }



