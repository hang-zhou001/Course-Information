#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "tool.h"
int saveCard(Card cards[], int* index)
{
	FILE* fp;
	if ((fp = fopen("data.dat", "wb+")) == NULL)
	{
		return true;
	}
	
	fwrite(cards, sizeof(struct Card), (*index), fp);
	fclose(fp);
	return false;
}
int readCard(Card cards[], int* index)
{
    FILE* fp;
	if ((fp = fopen("data.dat", "ab+"))==NULL)
	{
		return true;
	}
	while (!feof(fp))
	{
		fread(&cards[*index], sizeof(struct Card), 1, fp);
		(*index)++;
	}
	(*index)--;
	fclose(fp);
	return false;
}