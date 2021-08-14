#include <time.h>
#include <string.h>
#include "tool.h"
#include "model.h"
int getname(char* p, Card cards[], int n)							//判定卡号是否由5位数字构成
{
	int i = 0;
	for (int j = 0; j < n; j++)
	{
		if (strcmp(cards[j].name, p) == 0)
		{
			printf("输入的卡号已经存在！\n");
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
		printf("卡号输入不正确！\n\n");
		return true;
	}
	return false;
}
int getpassword(char* p)					//判断密码构成是否符合规则
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
		printf("卡密码输入不正确!\n\n");
		return true;
	}
	return false;

}
int getmoney(float p)								//判断充值金额是否在0-10000之间
{
	if (p <= 0 || p >= 10000)
	{
		printf("充值金额不符合充值范围！\n\n");
		return true;
	}
	if (p != (int)p)
	{
		printf("充值金额不符合规范！\n\n");
		return true;
	}
	return false;
}
void timetoString(time_t *timer,char* ptr)		//将日历时间转化为字符转形式的本地时间
{
	struct tm* timeinfo;
	timeinfo = localtime(timer);
	strftime(ptr, 80, "%Y 年%m 月%e 日%H 时%M 分%S 秒", timeinfo);
}
