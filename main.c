#include "all.h"


int main()
{
	//�ԡ�������ʽ���ļ���
	FILE* pf = fopen("information.txt", "r");

	//����ͨѶ¼ָ�����parr����Ϊ��ָ��
	directory* parr = (directory*)malloc(sizeof(directory));
	if (parr == NULL)
	{
		printf("����ʧ�ܣ�");
	}
	parr->head = NULL;
	parr->size = 0;
	int judge = is_empty(pf);
	if (judge)
	{
		parr->head = init_head(pf);
		int asize = read_fsize(pf);
		parr->size = asize;
		info* p = parr->head;
		fseek(pf, 0, SEEK_SET);
		for (int i = 0; i < parr->size; i++)
		{
			char name[5] = { 0 };
			char number[15] = { 0 };
			fscanf(pf, "%s %s", name, number);
			strcpy(p->name, name);
			strcpy(p->number, number);
			p = p->next;
		}
	}

	int choice = 0;
	do
	{
		menu();
		printf("��ѡ���Ӧ������ţ�->");
		scanf("%d", &choice);
		if (choice <= 3 && choice > 0)
		{
			switch (choice)
			{
				case 1:
					check(parr->head, parr->size);
					break;
				case 2:
					add(parr);
					break;
				case 3:
					del(parr);
					break;
			}
		}
		else if (choice == 4)
		{
			FILE* pw = fopen("information.txt", "w");
			aftermath(parr, pw);
			fclose(pw);
			break;
		}
		else
		{
			printf("����Ƿ���������");
			break;
		}
	} while (1);

	fclose(pf);
	free(parr);
}


