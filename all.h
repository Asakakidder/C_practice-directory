#pragma once
#include <stdio.h>
#include <string.h>


//结构体声明
typedef struct info
{
	char name[5];
	char number[15];
	struct info* next;
}info;

typedef struct directory
{
	struct info* head;
	int size;
}directory;

void menu();

int is_empty(FILE*);

int read_fsize(FILE*);

info* init_head(FILE*);

void check(info*, int);

void add(directory*);

void del(directory*);

void aftermath(directory*, FILE*);