#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SHOW_STU   1
#define ADD_STU    2
#define DEL_STU    3
#define SEAR_STU   4
#define SAVE_STU   5
#define UPDATE_STU 6
#define QUIT_STU   7

#define NO_ERROR  0
#define SEX_ERROR 1
#define AGE_ERROR 2
#define ID_ERROR  3
#define PK_ERROR  4

typedef struct
{
	char msg[100];
	int id;
}Error;

typedef struct Student
{
	char stu_name[10];     // 学生姓名
	char stu_sex[10];      // 学生性别
	int stu_age;           // 学生年龄
	int stu_id;            // 学生学号
	struct Student *next;
}Node;

typedef struct
{
	Node *head;
}List;

static void menu_show(void)
{
	printf("\nThere are some options, Please select a option.(You must input a number!)\n");
	printf("***************************************************************************\n");
	printf("1 : Show all student\n");
	printf("2 : Add a student\n");
	printf("3 : Delete a student by stu_id\n");
	printf("4 : Search a student by stu_id\n");
	printf("5 : Save all student\n");
	printf("6 : Update a student by stu_id\n");
	printf("7 : Quit student mangement system\n");
	printf("***************************************************************************\n");
}

static int stu_id_constraint_primary_key(const List *p_list, const Node *node)
{
	int result = 0;
	Node *p = p_list->head;
	while (p != NULL)
	{
		if (p->stu_id == node->stu_id)
		{
			result = -1;
			break;
		}
		p = p->next;
	}

	return result;
}

static int student_information_check(const List *p_list, const Node *node, Error *err)
{
	int repetition = stu_id_constraint_primary_key(p_list, node);
	if (0 != repetition)
	{
		err->id = PK_ERROR;
		sprintf(err->msg, "%%学生学号: %d 重复(有效学号范围:1000~9999)", node->stu_id);
		return -1;
	}
	else if (9999 < node->stu_id || node->stu_id < 1000)
	{
		err->id = ID_ERROR;
		sprintf(err->msg, "%%学生学号: %d 不合法(有效学号范围:1000~9999)", node->stu_id);
		return -1;
	}
	else if (0 != strcmp("男", node->stu_sex) && 0 != strcmp("女", node->stu_sex))
	{
		err->id = SEX_ERROR;
		sprintf(err->msg, "%%学生性别: \'%s\' 不合法(有效性别: \'男\' 或 \'女\')", node->stu_sex);
		return -1;
	}
	else if (50 < node->stu_age || node->stu_age <= 0)
	{
		err->id = AGE_ERROR;
		sprintf(err->msg, "%%学生年龄: %d 不合法(有效年龄范围:1~50)", node->stu_age);
		return -1;
	}
	else
	{
		err->id = NO_ERROR;
	}
	return 0;
}

static void student_information_show(List *p_list)
{
	if (NULL == p_list->head)
	{
		printf("There is not any student. Maybe you can add a student.\n");
	}
	else
	{
		printf("学号      姓名      性别      年龄      \n");
		int stu_num = 0;
		Node *last;
		for(last = p_list->head; last; last = last->next)
		{
			char age_txt[10] = {0};
			sprintf(age_txt, "%d", last->stu_age);
			char id_txt[10] = {0};
			sprintf(id_txt, "%d", last->stu_id);

			int stu_id_len = strlen(id_txt);
			int stu_name_len = strlen(last->stu_name);
			int stu_age_len = strlen(age_txt);
			char record[50] = {0};
			
			strcat(record, id_txt);
			for (int i = 0; i < 10 - stu_id_len; i++)
			{
				strcat(record, " ");
			}
			strcat(record, last->stu_name);
			for (int i = 0; i < 10 - stu_name_len; i++)
			{
				strcat(record, " ");
			}
			strcat(record, last->stu_sex);
			for (int i = 0; i < 8; i++)
			{
				strcat(record, " ");
			}
			strcat(record, age_txt);
			for (int i = 0; i < 10 - stu_age_len; i++)
			{
				strcat(record, " ");
			}
			printf("%s\n", record);
			stu_num++;
		}
		printf("Total Student:%d\n", stu_num);
	}
}

static void student_information_add(List *p_list)
{
	printf("Now you can add a student information.\n");
	printf("Tips:there are some attributes that like stu_id, stu_name, stu_sex and stu_age with student.\n\
Of course, the attribute has some limitation.\n");
	printf("stu_id range 1000 to 9999.\n");
	printf("stu_name character max (4 Chinese or 9 English).\n");
	printf("stu_sex range 男 or 女.\n");
	printf("stu_age range 1 to 50.\n\n");
	Node *p = malloc(sizeof(Node));
	Error err;
	memset(&err, 0, sizeof(err));
	p->next = NULL;

	printf("stu_id(学生学号):");
	scanf("%d", &(p->stu_id));
	printf("stu_name(学生姓名):");
	scanf("%s", p->stu_name);
	printf("stu_sex(学生性别):");
	scanf("%s", p->stu_sex);
	printf("stu_age(学生年龄):");
	scanf("%d", &(p->stu_age));

	p->stu_name[9] = '\0';
	p->stu_sex[9] = '\0';
	while(student_information_check(p_list, p, &err) < 0)
	{ 
		if (NO_ERROR != err.id)
		{
			printf("%s\n", err.msg);
			if (PK_ERROR == err.id)
			{
				printf("学生学号:");
				scanf("%d", &(p->stu_id));
				continue;
			}
			else if (ID_ERROR == err.id)
			{
				printf("学生学号:");
				scanf("%d", &(p->stu_id));
				continue;
			}
			else if (SEX_ERROR == err.id)
			{
				printf("学生性别:");
				scanf("%s", p->stu_sex);
				continue;
			}
			else if (AGE_ERROR == err.id)
			{
				printf("学生年龄:");
				scanf("%d", &(p->stu_age));
				continue;
			}
		}
	}
	printf("Adding a student successful.\n");
	Node *last = p_list->head;
	if (last != NULL)  // 判断第一个结点是否存在
	{
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = p;
	}
	else
	{
		p_list->head = p;
	}
}

static void student_information_del(List *p_list, int stu_id)
{
	Node *p, *q;
	int is_found = 0;
	for (q = NULL, p = p_list->head; p != NULL; q = p, p = p->next)
	{
		if (stu_id == p->stu_id)
		{
			if (q != NULL) // 判断是否为头节点
			{
				q->next = p->next;
			}
			else
			{
				p_list->head = p->next;
			}
			free(p);
			is_found = 1;
			break;
		}
	}
	if (is_found)
	{
		printf("Delete successful.\n");
	}
	else
	{
		printf("Delete failure.\n");
	}
}

static void student_information_save(const List *p_list, const char *filename)
{
	Node *last;
	char stu_info[100] = { 0 };
	FILE *file_handle = fopen(filename, "a");
	if(NULL != file_handle)
	{ 
		for (last = p_list->head; last != NULL; last = last->next)
		{
			sprintf(stu_info, "{\"stu_id\":%d,\"stu_name\":\"%s\",\"stu_sex\":\"%s\",\"stu_age\":%d}\n",
				last->stu_id, last->stu_name, last->stu_sex, last->stu_age);
			fwrite(stu_info, sizeof(char), strlen(stu_info), file_handle);
		}
		fclose(file_handle);
	}
	printf("Save all student Successful.\n");
}

static void student_mamgement_system_quit(List *p_list)
{
	Node *temp;
	while (p_list->head != NULL)
	{
		temp = p_list->head;   //从第一个结点开始释放
		p_list->head = temp->next;
		free(temp);
	}
}

static int student_information_search_by_stu_id(List *p_list, int stu_id)
{
	int is_found = 0;
	Node *last;
	char stu_info[100] = {0};
	for (last = p_list->head; last != NULL; last = last->next)
	{
		if (stu_id == last->stu_id)
		{
			sprintf(stu_info, "{\"stu_id\":%d,\"stu_name\":\"%s\",\"stu_sex\":\"%s\",\"stu_age\":%d}", 
				last->stu_id, last->stu_name, last->stu_sex, last->stu_age);
			is_found = 1;
			break;
		}
	}
	if (is_found)
	{
		printf("Found a student: %s.\n", stu_info);
	}
	else
	{
		printf("Not Found.\n");
	}
	return 0;
}

static int student_information_update(List *p_list, int stu_id, const char *stu_name)
{
	int result = 0;
	Node *p = p_list->head;
	while (p != NULL)
	{
		if (p->stu_id == stu_id)
		{
			strcpy(p->stu_name, stu_name);
			result = 1;
			break;
		}
		p = p->next;
	}
	if (1 == result)
	{
		printf("Update successful.\n");
	}
	else
	{
		printf("Update failure: %d not exist.\n", stu_id);
	}

	return 0;
}

static int function_select(int option, List *p_list)
{
	int stu_id = 0;
	int result = 0;
	char filename[300] = { 0 };
	char stu_name[10] = {0};
	switch (option)
	{
		case SHOW_STU:
			student_information_show(p_list);
			break;
		case ADD_STU:
			student_information_add(p_list);
			break;
		case DEL_STU:
			printf("Please input a student's id:");
			scanf("%d", &stu_id);
			student_information_del(p_list, stu_id);
			break;
		case SEAR_STU:
			printf("Please input a student's id:");
			scanf("%d", &stu_id);
			student_information_search_by_stu_id(p_list, stu_id);
			break;
		case SAVE_STU:
			printf("Please input file name that you want to save:");
			scanf("%s", filename);
			student_information_save(p_list, filename);
			break;
		case UPDATE_STU:
			printf("Please input a student's id:");
			scanf("%d", &stu_id);
			printf("Please input a student's name that you want to update:");
			scanf("%s", stu_name);
			stu_name[9] = '\0';
			student_information_update(p_list, stu_id, stu_name);
			break;
		case QUIT_STU:
			student_mamgement_system_quit(p_list);
			result = 1;
			break;
		default:
			break;
	}
	return result;
}

int main(int argc, const char *argv[])
{
	List list;
	list.head = NULL;

	printf("Welcome to Student Mangement System(Version 1.0).\n\n");
Loop:
	menu_show();
	
	int option = 0;
	printf("Pick a Num:");
	scanf("%d", &option);
	while (option != SHOW_STU && option != ADD_STU  && option != DEL_STU  && 
		   option != SEAR_STU && option != QUIT_STU && option != SAVE_STU && 
		   option != UPDATE_STU)
	{
		printf("Error: Please valid number.\n");
		printf("Pick a Num:");
		scanf("%d", &option);
	}
	if (function_select(option, &list) > 0)
	{
		printf("Free link List memory and Quit program.\n");
	}
	else
	{
		goto Loop;
	}
	
	return 0;
}