#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include <string.h>

struct Student
{
	char name[20];
	int id;
	int score[3];
	int class_id;
	double sc_ave;
	int sc_sum;
	//在不同链表中使用的next
	struct Student*next;
	struct Student*classNext;
};
typedef struct Student STU;
struct Class
{
	int class_id;
	STU* head;
	int stu_count;
	int sum_score[3];
	double avg_score[3];
	struct Class*next;
};

typedef struct Class CLA;
STU* head;
CLA* claHead;






int meau();
void add();
void disp();
void search();
void insert();
void del();
void cal();
void sort();
void count();
void clear();
void save()
{
	//dump to  file
	FILE* fp;
	fopen_s(&fp, "student.data", "wb");
	STU* p = head->next;
	while (p)
	{
		fwrite(p, sizeof(STU), 1, fp);
		p = p->next;
	}
	fclose(fp);
}
void load()
{
	//load from  file
	FILE* fp;
	fopen_s(&fp, "student.data", "rb");
	if (fp == NULL)return;
	STU stu;
	size_t size;
	STU* last = head;
	while (1)
	{		
		size = fread_s(&stu, sizeof(STU), sizeof(STU), 1, fp);
		if (size <= 0)break;
		else
		{
			STU* temp = malloc(sizeof(STU));
			memcpy(temp, &stu, sizeof(STU));
			last->next = temp;
			temp->next = NULL;
			last = temp;
		}
	}
	fclose(fp);
}
void defaultDo()
{
	printf("incorrect command!\n");
}
// s1 < s2 return -1 
// s1 = s2 return 0
// s1 > s2 return 1
int cmpBySum(STU* s1, STU*s2)
{
	return (s1->sc_sum == s2->sc_sum) ? 0 : ((s1->sc_sum < s2->sc_sum) ? -1 : 1);
}
int cmpByAvg(STU* s1, STU*s2)
{
	return (s1->sc_ave == s2->sc_ave) ? 0 : ((s1->sc_ave < s2->sc_ave) ? -1 : 1);
}
int cmpById(STU* s1, STU*s2)
{
	return (s1->id == s2->id) ? 0 : ((s1->id < s2->id) ? -1 : 1);

}
int cmpByName(STU* s1, STU*s2)
{
	return strcmp(s1->name, s2->name);
}
int cmpByChinese(STU* s1, STU*s2)
{
	return (s1->score[0] == s2->score[0]) ? 0 : ((s1->score[0] < s2->score[0]) ? -1 : 1);
}
int cmpByMath(STU* s1, STU*s2)
{
	return (s1->score[1] == s2->score[1]) ? 0 : ((s1->score[1] < s2->score[1]) ? -1 : 1);
}
int cmpByEnglish(STU* s1, STU*s2)
{
	return (s1->score[2] == s2->score[2]) ? 0 : ((s1->score[2] < s2->score[2]) ? -1 : 1);
}
int main()
{
	// 初始化链表头,链表头也是具体的对象
	head = malloc(sizeof(STU));
	head->next = NULL;
	claHead = malloc(sizeof(CLA));
	claHead->next = NULL;
	//加载数据
	load();
	int key;
	while (1)
	{
		key = meau();
		if (key == 9) break;
		switch (key)
		{
		case 1:add(); save(); break;
		case 2:disp(); break;
		case 3:search(); break;
		case 4:insert(); save(); break;
		case 5:del(); save(); break;
		case 6:cal(); break;
		case 7:sort(); save(); break;
		case 8:count(); break;
		case 10:clear(); save(); break;
		default:defaultDo(); break;
		}
	}
	save();
	return 0;
}
int meau()
{
	char choice[10];
	printf("----------------MEAU----------------\n");
	printf("|  1 add students information      |\n");
	printf("|  2 display students information  |\n");
	printf("|  3 search a student              |\n");
	printf("|  4 insert a student              |\n");
	printf("|  5 delete a student              |\n");
	printf("|  6 calculate                     |\n");
	printf("|  7 sort                          |\n");
	printf("|  8 count                         |\n");
	printf("|  9 exit                          |\n");
	printf("|  10 clear all                    |\n");
	printf("------------------------------------\n");
	printf("Input your choice:");
	scanf_s("%s", choice,10);
	return atoi(choice)? atoi(choice) : -1 ;
}
void clear()
{
	head->next = NULL;
}
void addOne(int id, char *name, int sc1, int sc2, int sc3, int cl_id)
{
	STU* stu = malloc(sizeof(STU));
	stu->id = id;
	strcpy_s(stu->name,20, name);
	stu->score[0] = sc1;
	stu->score[1] = sc2;
	stu->score[2] = sc3;
	stu->class_id = cl_id;
	stu->sc_sum = sc1 + sc2 + sc3;
	stu->sc_ave = stu->sc_sum / 3.0;
	stu->next = head->next;
	head->next = stu;
}
void add()
{
	STU s1;
	int count;
	printf("please input student number:");
	scanf_s("%d", &count);
	for (int i = 0; i < count; i++)
	{
		printf("Input student information[id name score(Chinese Math Engilsh) class_id]\n");
		scanf_s("%d%s%d%d%d%d", &s1.id, s1.name, 20, &s1.score[0], &s1.score[1], &s1.score[2], &s1.class_id);
		addOne(s1.id, s1.name, s1.score[0], s1.score[1], s1.score[2], s1.class_id);
	}
}
void disp()
{

	printf("-------------------------所有学生信息-----------------------\n");
	printf("id        class      name    Chinese    Math    Engilsh    average    sum\n");
	STU* p = head->next;
	while (p) {
		printf("%-10d%-11d%-8s%-9d  %-6d  %-9d  %-8.2f   %-7d\n", p->id, p->class_id, p->name, p->score[0], p->score[1], p->score[2], p->sc_ave, p->sc_sum);
		p = p->next;
	}

	printf("-----------------------------------------------------------\n");
}

int searchDo(int (*cmpFun)(STU*,STU*),STU* stu)
{
	STU* p = head->next;
	while (p) {
		if (cmpFun(stu,p)==0)
		{
			printf("-------------------------查找学生信息-----------------------\n");
			printf("id        class      name    Chinese    Math    Engilsh    average    sum\n");

			printf("%-10d%-11d%-8s%-9d  %-6d  %-9d  %-8.2f   %-7d\n", p->id, p->class_id, p->name, p->score[0], p->score[1], p->score[2], p->sc_ave, p->sc_sum);
			printf("-----------------------------------------------------------\n");
			return 0;
		}
		p = p->next;
	}
	printf("none student be found!\n");
	return -1;
}

void search()
{
	printf("input search command[id name ]:");
	char cmd[20];
	scanf_s("%s", cmd, 20);
	if (strcmp(cmd, "id") == 0)
	{
		int id;
		printf("input student id:");
		scanf_s("%d", &id);
		STU stu;
		stu.id = id;
		searchDo(cmpById, &stu);
	}
	else if (strcmp(cmd, "name") == 0)
	{
		char name[20];
		printf("input student name:");
		scanf_s("%s", name,20);
		STU stu;
		strcpy_s(stu.name, 20, name);
		searchDo(cmpByName, &stu);
	}
	else
	{
		printf("incorrect command!\n");
	}

}
void insert()
{
	STU s1;
	printf("Input studnet information[id name score(Chinese Math Engilsh) class_id]\n");
	scanf_s("%d%s%d%d%d%d", &s1.id, s1.name, 20, &s1.score[0], &s1.score[1], &s1.score[2], &s1.class_id);
	addOne(s1.id, s1.name, s1.score[0], s1.score[1], s1.score[2], s1.class_id);
	printf("insert successfully!\n");
}
void delDo(int(*cmpFun)(STU*, STU*), STU* stu)
{
	STU* p = head;
	while (p->next)
	{
		if (cmpFun(stu,p->next)==0)
		{
			STU* temp = p->next;
			p->next = p->next->next;
			free(temp);
			printf("delete successfully!\n");
			return;
		}
		p = p->next;
	}
}

void del()
{
	printf("input delete command[id name ]:");
	char cmd[20];
	scanf_s("%s", cmd, 20);
	if (strcmp(cmd, "id") == 0)
	{
		int id;		
		printf("input student id:");
		scanf_s("%d", &id);
		STU stu;
		stu.id = id;
		int rst = searchDo(cmpById,&stu);
		if (rst == 0)
		{
			printf("comfirm your operation[yes or no]:");
			char cmdC[10];
			scanf_s("%s", cmdC, 10);
			if (strcmp(cmdC, "yes") == 0)delDo(cmpById,&stu);
			else return;
		}
		else return;	
	}
	else if (strcmp(cmd, "name") == 0)
	{
		char name[20];
		printf("input student name:");
		scanf_s("%s", name,20);
		STU stu;
		strcpy_s(stu.name, 20, name);
		int rst = searchDo(cmpByName,&stu);
		if (rst == 0)
		{
			printf("comfirm your operation[yes or no]:");
			char cmdC[10];
			scanf_s("%s", cmdC, 10);
			if (strcmp(cmdC, "yes") == 0)delDo(cmpByName, &stu);
			else return;
		}
		else return;
	}
	else
	{
	printf("incorrect command!\n");
	}
}
void addStuToCla(STU* stu)
{
	CLA* p = claHead->next;
	while (p)
	{
		if (stu->class_id == p->class_id)
		{
			stu->classNext = p->head->classNext;
			p->head->classNext = stu;
			p->stu_count++;
			p->sum_score[0] += stu->score[0];
			p->sum_score[1] += stu->score[1];
			p->sum_score[2] += stu->score[2];
			return;
		}
		p = p->next;
	}
	CLA* newCla = malloc(sizeof(CLA));
	newCla->class_id = stu->class_id;
	newCla->head = malloc(sizeof(STU));
	newCla->head->classNext = stu;
	newCla->stu_count = 1;
	newCla->sum_score[0] = stu->score[0];
	newCla->sum_score[1] = stu->score[1];
	newCla->sum_score[2] = stu->score[2];
	newCla->next = claHead->next;
	claHead->next = newCla;
}
void claUpdate()
{
	claHead->next = NULL;
	STU* p = head->next;
	while (p)
	{
		addStuToCla(p);
		p = p->next;
	}
	//计算每个班级每门课程的平均分
	CLA* cp = claHead->next;
	while (cp)
	{
		cp->avg_score[0] = (double)cp->sum_score[0] / cp->stu_count;
		cp->avg_score[1] = (double)cp->sum_score[1] / cp->stu_count;
		cp->avg_score[2] = (double)cp->sum_score[2] / cp->stu_count;
		cp = cp->next;
	}

}
void cal()
{
	claUpdate();
	printf("------------------------所有班级信息-----------------------\n");
	printf("class_id    stu_amount  Avg_Chinese  Avg_Math  Avg_Engilsh\n");
	CLA* p = claHead->next;
	while (p) {
		printf("%-12d%-11d %-12.2lf %-9.2lf %-9.2lf\n", p->class_id, p->stu_count, p->avg_score[0], p->avg_score[1], p->avg_score[2]);
		p = p->next;
	}
	printf("-----------------------------------------------------------\n");

}
void insert_(STU* head, STU* stu, int(*cmpFun)(STU*, STU*),int reverse)
{
	STU* p = head;
	while (p->next)
	{
		if ((cmpFun(stu,p->next)==-1 && !reverse)|| (cmpFun(stu, p->next) == 1 && reverse))
		{
			stu->next = p->next;
			p->next = stu;
			return;
		}
		p = p->next;
	}
	//没找到位置,放在最后面
	p->next = stu;
	stu->next = NULL;
}


void sortDo(int(*cmpFun)(STU*, STU*),int reverse)
{
	STU* tempHead = malloc(sizeof(STU));
	tempHead->next = NULL;
	STU* p = head->next;
	STU* temp;
	while (p)
	{
		temp = p->next;
		insert_(tempHead, p, cmpFun, reverse);
		p = temp;
	}
	free(head);
	head = tempHead;
}
void sort()
{
	printf("please input sort command[sum avg id name chinese math english]:");
	char cmd[20];
	int reverse;
	scanf_s("%s", cmd, 20);
	printf("排序规则\t0:升序1降序:");
	scanf_s("%d", &reverse);
	if (strcmp(cmd, "sum") == 0)
	{
		//sort by sum
		sortDo(cmpBySum, reverse);

	}
	else if (strcmp(cmd, "avg") == 0)
	{
		sortDo(cmpByAvg, reverse);
	}
	else if (strcmp(cmd, "id") == 0)
	{
		sortDo(cmpById, reverse);
	}
	else if (strcmp(cmd, "name") == 0)
	{
		sortDo(cmpByName, reverse);
	}
	else if (strcmp(cmd, "chinese") == 0)
	{
		sortDo(cmpByChinese, reverse);
	}
	else if (strcmp(cmd, "math") == 0)
	{
		sortDo(cmpByMath, reverse);
	}
	else if (strcmp(cmd, "english") == 0)
	{
		sortDo(cmpByEnglish, reverse);
	}
	else
	{
		defaultDo();
	}
}
void count()
{
	claUpdate();
	printf("---------------------------------分类统计--------------------------------\n");
	printf("class_id    stu_amount  Avg_Chinese  Avg_Math  Avg_Engilsh  Sum_Chinese  Sum_Math  Sum_Chinese\n");
	CLA* p = claHead->next;
	while (p) {
		printf("%-12d%-11d %-12.2lf %-9.2lf %-12.2lf %-12d %-9d %-9d\n", p->class_id, p->stu_count, p->avg_score[0], p->avg_score[1], p->avg_score[2],
			p->sum_score[0], p->sum_score[1], p->sum_score[2]);
		p = p->next;
	}
	printf("-----------------------------------------------------------------------------\n");
}
