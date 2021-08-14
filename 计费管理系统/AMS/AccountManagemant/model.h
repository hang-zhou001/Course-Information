#pragma once
#include <time.h>
typedef struct Card
{
	char name[10] ;			//卡号
	char password[10];		//密码
	float money;				//开卡金额
	int status;				//卡状态：0表示未上机 ，1表示正在上机，2表示卡已注销
	int time;				//使用次数
	time_t starttime;		//开卡时间
	time_t lasttime;		//最后使用时间
	double sumtime;			//累计使用时间

}Card;