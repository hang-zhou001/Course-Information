#include <time.h>
#include <string.h>
#include "tool.h"
#include "model.h"
int getname(char* p, Card cards[], int n)							//�ж������Ƿ���5λ���ֹ���
{
	int i = 0;
	for (int j = 0; j < n; j++)
	{
		if (strcmp(cards[j].name, p) == 0)
		{
			printf("����Ŀ����Ѿ����ڣ�\n");
			return true;
		}
	}
	while ((*p) != '\0')
	{
		if (*p >= '0' && *p <= '9')
			i++;
		p++;
	}

	if (i != 5)
	{
		printf("�������벻��ȷ��\n\n");
		return true;
	}
	return false;
}
int getpassword(char* p)					//�ж����빹���Ƿ���Ϲ���
{
	int i = 0;
	int j = 0;
	int k = 0;
	while ((*p) != '\0')
	{

		if (*p >= '0' && *p <= '9')
			i++;
		else if (*p >= 'a' && *p <= 'z')
			j++;
		p++;
	}

	if (i == 0 || j == 0 || (i + j != 6))
	{
		printf("���������벻��ȷ!\n\n");
		return true;
	}
	return false;

}
int getmoney(float p)								//�жϳ�ֵ����Ƿ���0-10000֮��
{
	if (p <= 0 || p >= 10000)
	{
		printf("��ֵ�����ϳ�ֵ��Χ��\n\n");
		return true;
	}
	if (p != (int)p)
	{
		printf("��ֵ�����Ϲ淶��\n\n");
		return true;
	}
	return false;
}
void timetoString(time_t *timer,char* ptr)		//������ʱ��ת��Ϊ�ַ�ת��ʽ�ı���ʱ��
{
	struct tm* timeinfo;
	timeinfo = localtime(timer);
	strftime(ptr, 80, "%Y ��%m ��%e ��%H ʱ%M ��%S ��", timeinfo);
}
