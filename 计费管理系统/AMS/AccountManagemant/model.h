#pragma once
#include <time.h>
typedef struct Card
{
	char name[10] ;			//����
	char password[10];		//����
	float money;				//�������
	int status;				//��״̬��0��ʾδ�ϻ� ��1��ʾ�����ϻ���2��ʾ����ע��
	int time;				//ʹ�ô���
	time_t starttime;		//����ʱ��
	time_t lasttime;		//���ʹ��ʱ��
	double sumtime;			//�ۼ�ʹ��ʱ��

}Card;