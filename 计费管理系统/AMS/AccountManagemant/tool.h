#pragma once
#include <time.h>
#include <stdio.h>
#include "model.h"
#define true 1
#define false  0

int getname(char* p, Card cards[], int n);	//判断卡号是否由5位数字组成
int getpassword(char* p);					//判断密码是否是6位，且同时包含数字和字符
int getmoney(float p);						//判断充值金额是否在0-10000之间
void timetoString(time_t* timer, char* ptr);//将日历时间转换成字符串