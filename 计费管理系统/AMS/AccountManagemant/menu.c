#include <stdio.h>
#include <string.h>
#include "model.h"
#include "tool.h"

void Outputmenu()
{
	printf("----------�˵�----------\n");
	printf("1������¿�\n");
	printf("2����ѯ��\n");
	printf("3���ϻ�\n");
	printf("4���»�\n");
	printf("5����ֵ\n");
	printf("6���˷�\n");
	printf("7��ͳ��\n");
	printf("8������\n");
	printf("0���˿�\n");
	printf("������˵���ţ�0-8����");
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
        while (getchar() != '\n');					//��ջ�����
		printf("������5λ�����ֹ��ɵĿ���:");
		scanf("%9s", Name);
	} while (getname(Name,cards,*index));					//�ж������Ƿ���ι��ɹ���

	strcpy(card.name, Name);

	do {
		while (getchar() != '\n');					//��ջ�����
		printf("������6λ����(������ͬʱ�������ֺ��ַ�):");
		scanf("%9s", Password);
	} while (getpassword(Password));			//�ж����빹���Ƿ���Ϲ���

	strcpy(card.password, Password);
	printf("�������ֵ���:");
	if (!scanf("%f", &card.money))
	{
		printf("����Ľ����Ϲ淶��\n");
		while (getchar() != '\n');					//��ջ�����
		return;
	}
	if (getmoney(card.money))				//�жϳ�ֵ����Ƿ���0-10000֮��
		return;

	card.status = 0;
	card.time = 0;
	card.sumtime = 0;						
	card.starttime = card.lasttime = time(NULL);
	timetoString(&card.starttime, startTime);
	timetoString(&card.lasttime, lastTime);
	cards[*index] = card;
	printf("\n���ţ�%s\n", card.name);
	(*index) ++ ;
	printf("��%.1f\n", card.money);
	if(card.status==0)
	    printf("״̬��%s\n","δ�ϻ�");
	else if(card.status==1)
		printf("״̬��%s\n", "�����ϻ�");
	else
		printf("״̬��%s\n", "��ע��");
	printf("ʹ�ô�����%d\n", card.time);
	printf("����ʱ�䣺%s\n", startTime);
	printf("���ʹ��ʱ�䣺%s\n", lastTime);
	printf("�ۼ�ʹ��ʱ�䣺%.1f��\n", card.sumtime);
	printf("�����ɹ�!\n\n");
		
}

void refer(Card card[],int* index,char c[])				//��ѯ��
{

	char startTime[80];			//��ſ���ʱ��
	char lastTime[80];			//������ʹ��ʱ��
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
			printf("\n���ţ�%s\n", card[i].name);
			printf("��%.1f\n", card[i].money);
			if (card[i].status == 0)
				printf("״̬��%s\n", "δ�ϻ�");
			else if (card[i].status == 1)
				printf("״̬��%s\n", "�����ϻ�");
			else
				printf("״̬��%s\n", "��ע��");
			printf("ʹ�ô�����%d\n", card[i].time);
			timetoString(&card[i].starttime, startTime);
			timetoString(&card[i].lasttime, lastTime);
			printf("����ʱ�䣺%s\n", startTime);
			printf("���ʹ��ʱ�䣺%s\n", lastTime);
			printf("�ۼ�ʹ��ʱ�䣺%.1f��\n\n", card[i].sumtime);
		}
	}
	if (num == 0)
		printf("�ÿ������ڣ�\n\n");
	
}


void xiaoka(Card cards[], int* index)
{
	int flag = 1;
	int j=0;
	char Name[10] = { '\0' };
	char Password[10] = { '\0' };
	while (getchar() != '\n');
	printf("����Ҫע���Ŀ��ţ�");
	scanf("%9s", Name);
	while (getchar() != '\n');
	printf("���������룺");
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
		printf("�������ڣ�\n");
		return;
	}
	if (strcmp(cards[j].password, Password) != 0)
	{
		printf("�������\n");
		return;
	}
	if (cards[j].status >2)
	{
		printf("�ÿ��Ѿ�ע���������ظ�ע����\n");
		return;
	}
	if (cards[j].status ==1)
	{
		printf("����ʹ�õĿ�����ע����\n");
		return;
	}
	cards[j].money = 0;
	cards[j].status = 3;
	printf("ע���ɹ���\n\n");

}