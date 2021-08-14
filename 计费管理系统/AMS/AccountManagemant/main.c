#include <stdio.h>
#include "menu.h"
#include "model.h"
#include "service.h"
#include "tool.h"
int main()
{
	int i;
	Card cards[100] = { "\0" };
	char c[10];
	int index = 0;
	if (readCard(cards, &index))
	{
		printf("文件读取失败！\n");
		return 0;
	}
	printf("*****欢迎来到计费管理系统*****\n\n");
	do
	{
		Outputmenu();		//打印菜单
		scanf("%d", &i);
		switch (i)
		{
		case 1:
			printf("1、添加新卡\n\n");
			add(cards,&index);
			break;
		case 2:
			printf("2、查询卡\n\n");
			printf("输入需查询的卡号若干位:");
			scanf("%6s", c);
			refer(cards, &index,c);
			break;
		case 3:
			printf("3、上机\n\n");
			break;
		case 4:
			printf("4、下机\n\n");
			break;
		case 5:
			printf("5、充值\n\n");
			break;
		case 6:
			printf("6、退费\n\n");
			break;
		case 7:
			printf("7、统计\n");
			break;
		case 8:
			printf("8、销卡\n\n");
			xiaoka(cards, &index);
			break;
		case 0:
			if (saveCard(cards, &index))
			{
				printf("文件保存失败!\n");
			}
			break;
		default:
			printf("输入的菜单号不正确\n");
			break;
		}
	} while (i != 0);

}