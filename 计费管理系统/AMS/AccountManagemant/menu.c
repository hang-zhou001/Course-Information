#include <stdio.h>
#include <string.h>
#include "model.h"
#include "tool.h"

void Outputmenu()
{
	printf("----------菜单----------\n");
	printf("1、添加新卡\n");
	printf("2、查询卡\n");
	printf("3、上机\n");
	printf("4、下机\n");
	printf("5、充值\n");
	printf("6、退费\n");
	printf("7、统计\n");
	printf("8、销卡\n");
	printf("0、退卡\n");
	printf("请输入菜单编号（0-8）：");
}
void add(Card cards[],int* index)
{
	printf("%d\n\n", *index);
	char Name[10] = { '\0' };
	char Password[10] = { '\0' };
	char startTime[80];
	char lastTime[80];
	Card card;
	do {
        while (getchar() != '\n');					//清空缓冲区
		printf("请输入5位由数字构成的卡号:");
		scanf("%9s", Name);
	} while (getname(Name,cards,*index));					//判定卡号是否如何构成规则

	strcpy(card.name, Name);

	do {
		while (getchar() != '\n');					//清空缓冲区
		printf("请输入6位密码(密码需同时包含数字和字符):");
		scanf("%9s", Password);
	} while (getpassword(Password));			//判断密码构成是否符合规则

	strcpy(card.password, Password);
	printf("请输入充值金额:");
	if (!scanf("%f", &card.money))
	{
		printf("输入的金额不符合规范！\n");
		while (getchar() != '\n');					//清空缓冲区
		return;
	}
	if (getmoney(card.money))				//判断充值金额是否在0-10000之间
		return;

	card.status = 0;
	card.time = 0;
	card.sumtime = 0;						
	card.starttime = card.lasttime = time(NULL);
	timetoString(&card.starttime, startTime);
	timetoString(&card.lasttime, lastTime);
	cards[*index] = card;
	printf("\n卡号：%s\n", card.name);
	(*index) ++ ;
	printf("金额：%.1f\n", card.money);
	if(card.status==0)
	    printf("状态：%s\n","未上机");
	else if(card.status==1)
		printf("状态：%s\n", "正在上机");
	else
		printf("状态：%s\n", "已注销");
	printf("使用次数：%d\n", card.time);
	printf("开卡时间：%s\n", startTime);
	printf("最后使用时间：%s\n", lastTime);
	printf("累计使用时间：%.1f分\n", card.sumtime);
	printf("开卡成功!\n\n");
		
}

void refer(Card card[],int* index,char c[])				//查询卡
{

	char startTime[80];			//存放开卡时间
	char lastTime[80];			//存放最后使用时间
	int j = 0;
	int num = 0;
	int m = 0;
	int flag = 1;
	for(int i=0;i<*index;i++)
	{
		j = 0;
		m = 0;
		flag = 1;
		while (card[i].name[m] != '\0')
		{
			if (card[i].name[m] == c[j])
			{ 
				j++;
			}
			
			m++;
		}
		if (c[j] != '\0')
			flag = 0;
		if (flag)
		{
			num++;
			printf("\n卡号：%s\n", card[i].name);
			printf("金额：%.1f\n", card[i].money);
			if (card[i].status == 0)
				printf("状态：%s\n", "未上机");
			else if (card[i].status == 1)
				printf("状态：%s\n", "正在上机");
			else
				printf("状态：%s\n", "已注销");
			printf("使用次数：%d\n", card[i].time);
			timetoString(&card[i].starttime, startTime);
			timetoString(&card[i].lasttime, lastTime);
			printf("开卡时间：%s\n", startTime);
			printf("最后使用时间：%s\n", lastTime);
			printf("累计使用时间：%.1f分\n\n", card[i].sumtime);
		}
	}
	if (num == 0)
		printf("该卡不存在！\n\n");
	
}


void xiaoka(Card cards[], int* index)
{
	int flag = 1;
	int j=0;
	char Name[10] = { '\0' };
	char Password[10] = { '\0' };
	while (getchar() != '\n');
	printf("输入要注销的卡号：");
	scanf("%9s", Name);
	while (getchar() != '\n');
	printf("请输入密码：");
	scanf("%9s", Password);
	for (int i = 0; i < *index; i++)
	{
		if (strcmp(Name, cards[i].name) == 0)
		{
			flag = 0;
			j = i;
			break;
		}
	}
	if (flag==1)
	{
		printf("卡不存在！\n");
		return;
	}
	if (strcmp(cards[j].password, Password) != 0)
	{
		printf("密码错误！\n");
		return;
	}
	if (cards[j].status >2)
	{
		printf("该卡已经注销，不能重复注销！\n");
		return;
	}
	if (cards[j].status ==1)
	{
		printf("正在使用的卡不能注销！\n");
		return;
	}
	cards[j].money = 0;
	cards[j].status = 3;
	printf("注销成功！\n\n");

}