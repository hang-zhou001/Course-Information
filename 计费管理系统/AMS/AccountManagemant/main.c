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
		printf("�ļ���ȡʧ�ܣ�\n");
		return 0;
	}
	printf("*****��ӭ�����Ʒѹ���ϵͳ*****\n\n");
	do
	{
		Outputmenu();		//��ӡ�˵�
		scanf("%d", &i);
		switch (i)
		{
		case 1:
			printf("1������¿�\n\n");
			add(cards,&index);
			break;
		case 2:
			printf("2����ѯ��\n\n");
			printf("�������ѯ�Ŀ�������λ:");
			scanf("%6s", c);
			refer(cards, &index,c);
			break;
		case 3:
			printf("3���ϻ�\n\n");
			break;
		case 4:
			printf("4���»�\n\n");
			break;
		case 5:
			printf("5����ֵ\n\n");
			break;
		case 6:
			printf("6���˷�\n\n");
			break;
		case 7:
			printf("7��ͳ��\n");
			break;
		case 8:
			printf("8������\n\n");
			xiaoka(cards, &index);
			break;
		case 0:
			if (saveCard(cards, &index))
			{
				printf("�ļ�����ʧ��!\n");
			}
			break;
		default:
			printf("����Ĳ˵��Ų���ȷ\n");
			break;
		}
	} while (i != 0);

}