#define _CRT_SECURE_NO_WARNINGS 1
#include "all.h"

//初始化菜单
void menu()
{
	printf(" _____________________________________________________\n");
	printf("|                                                     |\n");
	printf("|               1.check all inforamtion               |\n");
	printf("|               2.add somone                          |\n");
	printf("|               3.delete someone                      |\n");
	printf("|               4.exit                                |\n");
	printf("|_____________________________________________________|\n");
}

//判断读取的文件是否为空
int is_empty(FILE* stream)
{
	if ((fgetc(stream)) == EOF)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//返回txt文件中已有人员的数量
int read_fsize(FILE* stream)
{
	int cou = 0;
	int c = 0;
	fseek(stream, 0, SEEK_SET);
	while ((c = fgetc(stream)) != EOF)
	{
		if ((char)c == '\n')
		{
			cou += 1;
		}
	}
	return cou;
}

info* init_head(FILE* stream)
{
	info* container = NULL;
	int fsize = read_fsize(stream);
	for (int i = 0; i < fsize; i++)
	{
		info* np = (info*)malloc(sizeof(info));
		if (!np)
		{
			printf("分配失败！！！");
		}
		np->next = container;
		container = np;
	}
	return container;
}

void check(info* p, int x)
{
	if (p == NULL)
	{
		printf("表里无任何人员信息。\n");
	}
	else
	{
		printf("----------------------------------------------------------\n");
		printf("                          list                            \n");
		printf("----------------------------------------------------------\n");
		printf("           name                     telephone_number      \n");
		printf("----------------------------------------------------------\n");
		printf("                                                          \n");
		for (int i = 0; i < x; i++)
		{
			printf("           %s                     %s\n", p->name, p->number);
			printf("\n");
			p = p->next;
		}
	}

}

void add(directory* parr)
{
	int c = 0;
	while (1)
	{
		printf("是否进行添加人员操作？(是1/否0)：->");
		scanf("%d", &c);
		if (!c)
		{
			printf("已退出该功能。\n");
			break;
		}
		else
		{
			char name[5] = { 0 };
			char number[15] = { 0 };
			printf("请输入姓名->");
			scanf("%s", name);
			printf("请输入电话号码->");
			scanf("%s", number);
			info* po = (info*)malloc(sizeof(info));
			po->next = parr->head;
			parr->head = po;
			strcpy(parr->head->name, name);
			strcpy(parr->head->number, number);
			parr->size += 1;
			printf("添加成功！！！\n");
			po = NULL;
		}
	}
}

void del(directory* parr)
{
	if (parr->head == NULL)
	{
		printf("表里无任何人员信息，无法启用本功能。\n");
	}
	else
	{
		int c = 0;
		int light = 0;
		char nam[5] = { 0 };
		while (1)
		{
			info* poi = parr->head;
			info* pre = parr->head;
			printf("是否要动用删除模块？(是1/否0)：->");
			scanf("%d", &c);
			if (!c)
			{
				printf("已退出该功能。\n");
				break;
			}
			else
			{
				printf("请输入要删除的人员姓名：->");
				scanf("%s", nam);
				for (int i = 0; i < parr->size; i++)
				{
					if (strcmp(poi->name, nam) == 0)
					{
						printf("已找到%s。\n", nam);
						light++;
						break;
					}
					else
					{
						if (i == 1)
						{
							poi = poi->next;
						}
						else
						{
							poi = poi->next;
							pre = pre->next;
						}
					}
				}
				if (!light)
				{
					printf("未找到%s ！请重新输入！\n", nam);
					continue;
				}
				pre->next = poi->next;
				poi = NULL;
				parr->size -= 1;
				printf("删除成功！\n");
			}
		}
	}

}


void aftermath(directory* parr, FILE* stream)
{
	if (parr->head)
	{
		info* pt = parr->head;
		for (int i = 0; i < parr->size; i++)
		{
			fprintf(stream, "%s %s\n", pt->name, pt->number);
			pt = pt->next;
		}
		printf("退出成功！");
	}
	else
	{
		printf("退出成功！");
	}
}