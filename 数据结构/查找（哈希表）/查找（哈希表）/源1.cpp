#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
typedef struct
{
	int key;
	string s;
}Hash;
int Key(string s)
{
	int num=0;
	for (int i = 0; i < s.length(); i++)
	{
		num += (int)s[i];
	}
	num = num % 39;
	return num;
}
void Namelist(Hash ha)
{
	string name[24] = {"gaojian","limeiqi","chengneiya","fengyu",
	"liuyuanjie","zhouhang","wangzeren","xuxin","zengyinjun","chenhao",
	"chenqihui","chengwenxuan","chenxuan","gongxinlong","huangwei",
	"jiangyueao","liuhang","likaijie","lizhengming","tianchanglong",
	"moufeipeng","wuzhenshan","xushilong","zhangyadong" };
	for (int i = 0; i < 40; i++)
	{
		ha[i].key = -1;
	}
	for (int i = 0; i < 24; i++)
	{
		int n = Key(name[i]);
		if (ha[n].key == -1)
		{
			ha[n].s = name[i];
			ha[n].key = n;
		}
		else
		{

			for (int j = 1; j < 25; ++j)
			{
				int m = (n + j) % 40;
				if (ha[m].key == -1)
				{
					ha[m].s = name[i];
					ha[m].key = m;
					break;
				}
			}
		}
	}
}
int Search(Hash ha,string s)
{
	int i = Key(s);
	int m;
	if (ha[i].s==s)
		return i;
	else
	{
		for (int j = 1; j < 25; j++)
		{
			m = (i + j) % 40;
			if ( ha[m].s == s)
				return m;
			else if(ha[m].key == -1)
				return -1;	
		}
	}
}
int main()
{
	int i;
	printf("需要查找的同学姓名:");
	string name;
	Hash ha;
	Namelist(ha);
	for (i = 0; i < 40; i++)
	{
		printf("%d  ", ha[i].key);
	}
	scanf("%s", name);
	i = Search(ha, name);
	if (i == -1)
		printf("查找不成功");
	else
		printf("查找成功，同学在哈希表%d位置",  i);
	return 0;
}