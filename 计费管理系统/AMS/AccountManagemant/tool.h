#pragma once
#include <time.h>
#include <stdio.h>
#include "model.h"
#define true 1
#define false  0

int getname(char* p, Card cards[], int n);	//�жϿ����Ƿ���5λ�������
int getpassword(char* p);					//�ж������Ƿ���6λ����ͬʱ�������ֺ��ַ�
int getmoney(float p);						//�жϳ�ֵ����Ƿ���0-10000֮��
void timetoString(time_t* timer, char* ptr);//������ʱ��ת�����ַ���