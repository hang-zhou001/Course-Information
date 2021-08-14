#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
typedef struct
{
	int key;
}Hash[40];
int Address(string s)
{
	int num = 0;
	for (int i = 1; i <4; i++)
	{
		num += (int)s[i];
	}
	num = num % 39;
	return num;
}
int Key(string s)
{
	int num = 0;
	for (int i = 1; i < 4; i++)
	{
		num += (int)s[i];
	}
	return num;
}
void Namelist(Hash ha)
{
	string name[30] = {"gaojian","limeiqi","chengneiya","fengyu",
	"liuyuanjie","zhouhang","wangzeren","xuxin","zengyinjun","chenhao",
	"chenqihui","chengwenxuan","chenxuan","gongxinlong","huangwei",
	"jiangyueao","liuhang","likaijie","lizhengming","tianchanglong",
	"moufeipeng","wuzhenshan","xushilong","zhangyadong"};
	for (int i = 0; i < 40; i++)
	{
		ha[i].key = -1;
	}
	for (int i = 0; i < 24; i++)
	{
		int n = Address(name[i]);
		if (ha[n].key == -1)
		{
			ha[n].key = Key(name[i]);
		}
		else
		{

			for (int j = 1; j < 25; ++j)
			{
				int m = (n + j) % 25;
				if (ha[m].key == -1)
				{
					ha[m].key = Key(name[i]);
					break;
				}
			}
		}
	}
}
int Search(Hash ha, string s)
{
	int i = Address(s);
	int m;
	int count = 0;
	if (ha[i].key == Key(s))
		return ++count;
	else
	{
		for (int j = 1; j <=40; j++)
		{
			m = (i + j) % 40;
			count++;
			if (ha[m].key == Key(s))
				return count;
			else if (ha[m].key == -1)
				return 0;
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
	scanf("%s", name);
	i = Search(ha, name);
	if (i)
		printf("查找成功,查找次数为%d",i);
	else
	{
		printf("查找不成功");
	}
	return 0;
}