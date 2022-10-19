#define _CRT_SECURE_NO_WARNINGS 1
#include "all.h"

//��ʼ���˵�
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

//�ж϶�ȡ���ļ��Ƿ�Ϊ��
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

//����txt�ļ���������Ա������
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
			printf("����ʧ�ܣ�����");
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
		printf("�������κ���Ա��Ϣ��\n");
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
		printf("�Ƿ���������Ա������(��1/��0)��->");
		scanf("%d", &c);
		if (!c)
		{
			printf("���˳��ù��ܡ�\n");
			break;
		}
		else
		{
			char name[5] = { 0 };
			char number[15] = { 0 };
			printf("����������->");
			scanf("%s", name);
			printf("������绰����->");
			scanf("%s", number);
			info* po = (info*)malloc(sizeof(info));
			po->next = parr->head;
			parr->head = po;
			strcpy(parr->head->name, name);
			strcpy(parr->head->number, number);
			parr->size += 1;
			printf("��ӳɹ�������\n");
			po = NULL;
		}
	}
}

void del(directory* parr)
{
	if (parr->head == NULL)
	{
		printf("�������κ���Ա��Ϣ���޷����ñ����ܡ�\n");
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
			printf("�Ƿ�Ҫ����ɾ��ģ�飿(��1/��0)��->");
			scanf("%d", &c);
			if (!c)
			{
				printf("���˳��ù��ܡ�\n");
				break;
			}
			else
			{
				printf("������Ҫɾ������Ա������->");
				scanf("%s", nam);
				for (int i = 0; i < parr->size; i++)
				{
					if (strcmp(poi->name, nam) == 0)
					{
						printf("���ҵ�%s��\n", nam);
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
					printf("δ�ҵ�%s �����������룡\n", nam);
					continue;
				}
				pre->next = poi->next;
				poi = NULL;
				parr->size -= 1;
				printf("ɾ���ɹ���\n");
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
		printf("�˳��ɹ���");
	}
	else
	{
		printf("�˳��ɹ���");
	}
}