#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<Windows.h>
#include <malloc.h>
#define Mname "123"//管理员账号
#define Mpassword "123"//管理员密码
typedef struct Student
{
	char Meword[8];  //学生密码，初始为123456
	char cNumber[13]; //学号
	char cName[11];   //姓名
	int year;         //日期：年 
	int month;        //日期：月 
	int day;          //日期：天 
	int hour;         //时
	int min;          //分
	int sec;          //秒
	float balance;    //余额
	float recharge;   //充值金额
	float consume;    //消费金额 
	int Y;            //区分操作，充值为0，消费为1，添加学生为2
	struct Student* pNext;
}STU, * PSTU;
char UserName[20];//用户名
char UserWord[20];//密码

PSTU pHead = NULL;	//信息学生头结点
PSTU pNew = NULL;	//待添加学生信息

size_t iCount = 0;	//计数链表节点
size_t Z = 0;    //用于区分管理员和学生，于登录时赋不同值。
void Head();  //一卡通管理系统字符图标
void StuManage(); //管理员登录端字符图标
void Stuage();    //学生登录端字符图标
void ReadData();  //读取数据
void SaveData();  //保存数据

void Slogin();    //管理员登录
int SisLogin();   //判断管理员密码输入是否正确
int SMenuSelect();  //管理员选择功能
void SMainMenu(); //管理员主菜单

void login();     //学生登录
int isLogin();    //判断学生密码输入是否正确
int MenuSelect();   //学生选择功能
void MainMenu();  //学生主菜单

void Addup();     //添加学生
void Recharge();  //充值
void Consume();   //消费
void CCYE();     //余额查询
void Show_all();  //显示全部学生
void Show_single(char* user);//显示单个学生
void Bill();         //消费账单
void statistics();     //消费按月统计
void Change_WORD();  //修改密码
void Quit();        //退出
int main()
{
	pHead = (PSTU)malloc(sizeof(STU));
	pHead->pNext = NULL; /*初始化数据*/
	ReadData(); /*读取本地文件中的数据*/
	char a;
	do
	{
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t      您是管理员(Z)还是学生(X)？\n\n");
		printf("\t\t\t\t\t     │  ——————————  │\n");
		printf("\t\t\t\t\t     │   1. 管理员:请按下z    │\n");
		printf("\t\t\t\t\t     │  ——————————  │\n");
		printf("\t\t\t\t\t     │   2. 学生  :请按下x    │\n");
		printf("\t\t\t\t\t     │  ——————————  │\n");
		a = getch();
		if (a == 'z' || a == 'Z')
		{
			system("CLS");//清屏
			Slogin();
			SMainMenu();
		}
		else if (a == 'x' || a == 'X')
		{
			system("CLS");//清屏
			login();
			if (isLogin())
			{
				MainMenu();
			}
		}
		else
		{
			printf("输入错误,请重试。");
			system("cls");//清屏
		}

	} while (a != 'Z' && a != 'z' && a != 'x' && a != 'X');
	return 0;
}
/************ 一卡通管理系统字符图标 ***********/
void Head()
{
	printf("\n\n\n");
	printf("\t\t\t\t\t │ ——————————————— │\n");
	printf("\t\t\t\t\t │           一卡通系统           │\n");
	printf("\t\t\t\t\t │ ——————————————— │\n");
	printf("\n\n\n");
}
/************ 管理员登录端字符图标 ***********/
void StuManage()
{
	printf("\n\n\n");
	printf("\t\t\t\t\t│ —————————————————————— │\n");
	printf("\t\t\t\t\t│          一卡通管理系统   管理员登录端       │\n");
	printf("\t\t\t\t\t│ —————————————————————— │\n");
	printf("\n\n\n");
}
/************ 学生登录端字符图标 ***********/
void Stuage()
{
	printf("\n\n\n");
	printf("\t\t\t\t\t│ —————————————————————— │\n");
	printf("\t\t\t\t\t│          一卡通管理系统   学生登录端         │\n");
	printf("\t\t\t\t\t│ —————————————————————— │\n");
	printf("\n\n\n");
}

void ReadData()
{
	FILE* fRead = fopen("fee.dat", "rb");//打开fee.dat文件

	if (fRead == NULL)
	{
		SaveData();	/*文件不存在就创建文件*/
		return;
	}
	rewind(fRead);	/*将文件内部指针移回文件开头*/
	while (1)
	{

		pNew = (PSTU)malloc(sizeof(STU));	/*申请一块内存*/
		if (pNew)
		{
			fread(pNew, sizeof(STU), 1, fRead);	/* 1 表示读取一个STU字节大小单元*/
			if (feof(fRead)) break;		/*文件末尾退出*/
			/*头插法插入数据*/
			pNew->pNext = NULL;/*将新元素pNext置为空*/
			PSTU temp = pHead->pNext;/*定义一个临时指针变量指向表头*/
			if (pHead->pNext == NULL)
			{
				pHead->pNext = pNew;/*pHead为空则赋予pNew为第一个新结点*/
				pNew->pNext = NULL;
			}
			else
			{
				while (temp->pNext != NULL)/*最终让temp指向尾结点*/
				{
					temp = temp->pNext;
				}
				temp->pNext = pNew;/*将尾结点temp的pNext设为pNew,即将pNew设为尾结点*/
			}
			iCount++;
		}

	}
	fclose(fRead);
}
void SaveData()
{
	FILE* fWrite = fopen("fee.dat", "wb");

	if (fWrite == NULL)
	{
		system("cls");
		printf("保存失败...\n");
		Quit();
	}
	PSTU pCurrent = pHead->pNext;	/*指向第一个节点*/
	while (pCurrent != NULL)		/*遍历所有学生信息*/
	{
		fwrite(pCurrent, sizeof(STU), 1, fWrite);/*由文件到链表*/
		pCurrent = pCurrent->pNext;/*指向下一个节点*/
	}
	pCurrent = NULL;
	fclose(fWrite);/*关闭文件*/
}
void Slogin()//管理员登录
{
	SetConsoleTitle(L"                       一卡通管理系统(管理员)");
	StuManage();
	int  i;
	char Separation[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
	for (i = 0; i < strlen(Separation); i++)
	{
		printf("%c", Separation[i]);
		Sleep(10);
	}
	printf("\n\n\t\t\t\t\t\t请输入您的账号密码\n\n");
	printf("\n\t\t\t\t\t\t账号:");
	scanf("%s", UserName);
	printf("\n\t\t\t\t\t\t密码:");
	scanf("%s", UserWord);
	Z = 1;/*全局变量，为1表示为管理员身份*/

}
int SisLogin()
{
	int i;
	int times = 0;	//密码输入次数
	while (!(strcmp(UserName, Mname) == 0 && strcmp(UserWord, Mpassword) == 0))
	{
		times++;	//密码输入错误 times++
		if (times > 3)
		{
			printf("\n\n\n\n\t\t\t\t账号或密码输入错误累计达到%d次，系统将于3秒后关闭", times);
			Sleep(1000);
			system("cls");
			char shutdown[] = { "系统将于%d秒后关闭..." };
			for (i = 0; i < 3; i++)
			{
				printf(shutdown, 3 - i);
				Sleep(1000);
				system("cls");
			}
			exit(0);
		}
		printf("\n\n\n\n\t\t\t\t账号或密码输入错误,你还有%d次登录机会，按任意键重新登录...", 4 - times);
		char a = getch();
		system("cls");
		Slogin();
	}
	return 1;
}
void login()//学生登录
{
	SetConsoleTitle(L"                        一卡通管理系统(学生)");
	Stuage();
	int  i;
	char Separation[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * " };
	for (i = 0; i < strlen(Separation); i++)
	{
		printf("%c", Separation[i]);
		Sleep(10);
	}
	printf("\n\n\t\t\t\t\t\t请输入您的学号密码\n\n");
	printf("\n\t\t\t\t\t\t学号:");
	scanf("%s", UserName);
	printf("\n\t\t\t\t\t\t密码:");
	scanf("%s", UserWord);
	Z = 2;/*全局变量，为2表示为学生身份*/
}
int isLogin()
{
	int  i;
	int times = 0;	/**密码输入次数**/

	while (1)
	{
		PSTU p;
		p = pHead->pNext;/*指向第一个节点*/
		while (p != NULL)
		{
			if (strcmp(p->cNumber, UserName) == 0 && strcmp(p->Meword, UserWord) == 0)
			{
				return 1;
			}
			p = p->pNext;
		}
		times++;
		if (times > 3)
		{
			printf("\n\n\n\n\t\t\t\t账号或密码输入错误累计达到%d次，系统将于3秒后关闭", times);
			Sleep(1000);
			system("cls");
			char shutdown[] = { "系统将于%d秒后关闭..." };
			for (i = 0; i < 3; i++)
			{
				printf(shutdown, 3 - i);
				Sleep(1000);
				system("cls");
			}
			exit(0);
		}
		printf("\n\n\n\n\t\t\t\t账号或密码输入错误,你还有%d次登录机会，按任意键重新登录...", 4 - times);
		char h = getch();
		system("cls");
		login();

	}
}
int SMenuSelect()
{
	char c;
	do
	{
		system("cls");
		Head();
		printf("\t\t\t\t  │═══════════════════════════════════════════════│\n");
		printf("\t\t\t\t  │                一卡通管理员菜单               │\n");
		printf("\t\t\t\t  │═══════════════════════════════════════════════│\n");
		printf("\t\t\t\t    ┌───────────────────────────────────────────┐\n");
		printf("\t\t\t\t    │                     │                     │\n");
		printf("\t\t\t\t    │ 1. 添加数据         │         2. 余额充值 │\n");
		printf("\t\t\t\t    │—————————— │ ——————————│\n");
		printf("\t\t\t\t    │ 3. 月消费           │         4. 全部学生 │\n");
		printf("\t\t\t\t    │—————————— │ ——————————│\n");
		printf("\t\t\t\t    │ 5. 余额查询         │         6. 消费账单 │\n");
		printf("\t\t\t\t    │—————————— │ ——————————│\n");
		printf("\t\t\t\t    │ 0. 退出界面         │                     │\n");
		printf("\t\t\t\t    └───────────────────────────────────────────┘\n");
		printf("\t\t\t\t\t\t  请您选择(0-5):");
		c = getche();
	} while (c < '0' || c > '6');
	return c - '0';
}

void SMainMenu()
{
	if (SisLogin())
	{
		//登录成功
		switch (SMenuSelect())	//菜单选择
		{
		case 1:	//添加学生信息
			system("cls");
			Addup();
			Quit();
			break;
		case 2:	//充值
			system("cls");
			Recharge();
			Quit();
			break;
		case 3:	//消费按每月统计
			system("cls");
			statistics();
			Quit();
			break;
		case 4:	//全部信息
			system("cls");
			Show_all();
			Quit();
			break;
		case 5:	//查询余额
			system("cls");
			CCYE();
			Quit();
			break;
		case 6:	//消费账单
			system("cls");
			Bill();
			Quit();
			break;
		case 0:	//退出程序
			system("cls");
			Head();
			Quit();	//退出或返回主菜单
			break;
		}
	}
}
int MenuSelect()
{
	char A;
	do
	{
		system("cls");
		Head();
		printf("\t\t\t\t  │═══════════════════════════════════════════════│\n");
		printf("\t\t\t\t  │                一卡通学生功能菜单             │\n");
		printf("\t\t\t\t  │═══════════════════════════════════════════════│\n");
		printf("\t\t\t\t    ┌───────────────────────────────────────────┐\n");
		printf("\t\t\t\t    │                     │                     │\n");
		printf("\t\t\t\t    │ 1. 每月消费         │         2. 查询余额 │\n");
		printf("\t\t\t\t    │—————————— │ ——————————│\n");
		printf("\t\t\t\t    │ 3. 消费账单         │         4. 消费     │\n");
		printf("\t\t\t\t    │—————————— │ ——————————│\n");
		printf("\t\t\t\t    │ 5. 充值             │         6. 修改密码 │\n");
		printf("\t\t\t\t    │—————————— │ ——————————│\n");
		printf("\t\t\t\t    │ 0. 退出程序         │                     │\n");
		printf("\t\t\t\t    └───────────────────────────────────────────┘\n");
		printf("\t\t\t\t\t\t  请您选择(0-6):");
		A = getche();
	} while (A < '0' || A > '6');
	return A - '0';
}

void MainMenu()
{
	switch (MenuSelect())	//菜单选择
	{
	case 1:	//消费按每月统计
		system("cls");
		statistics();
		Quit();
		break;
	case 2:	//查询余额
		system("cls");
		CCYE();
		Quit();
		break;
	case 3:	//消费账单
		system("cls");
		Bill();
		Quit();
		break;
	case 4:	//消费
		system("cls");
		Consume();
		Quit();
		break;
	case 5:	//充值
		system("cls");
		Recharge();
		Quit();
		break;
	case 6:	//修改密码
		system("cls");
		Change_WORD();
		Quit();
		break;
	case 0:		//退出程序
		system("cls");
		Head();
		Quit();	//退出或返回主菜单
		break;
	}
}
void Addup()
{
	time_t t;
	struct tm* lt;
	time(&t);//获取Unix时间戳。
	lt = localtime(&t);//转为时间结构。
	unsigned int i;
	char a;
	for (i = 1; i <= 3; i++)
	{
		Sleep(100);
		printf(".");
	}
	system("CLS");
	Head();
	pNew = (PSTU)malloc(sizeof(STU));
	if (pNew)
	{
		printf("\t\t\t\t\t\t添加学生信息:\n\n\n\n\t\t\t\t\t\t学号:");
		scanf("%s", pNew->cNumber);
		printf("\n\t\t\t\t\t\t姓名:");
		scanf("%s", pNew->cName);
		pNew->year = lt->tm_year + 1900;//添加日期：年 
		pNew->month = lt->tm_mon + 1;//添加日期：月 
		pNew->day = lt->tm_mday;//添加日期：天 
		pNew->hour = lt->tm_hour;//时 
		pNew->min = lt->tm_min;//分
		pNew->sec = lt->tm_sec;//秒
		pNew->recharge = 0;//充值金额
		pNew->consume = 0;//消费金额
		pNew->balance = 0;//余额
		pNew->Y = 2;
		char words[10] = { "123456" };
		strcpy(pNew->Meword, "123456");
		printf("\n\n\t您输入的信息为：");
		printf("\n\n\t学号 \t\t学生姓名 \t\t 余额 ");
		printf("\n\t%-12s\t%-20s\t%-6.2f\t", pNew->cNumber, pNew->cName, pNew->balance);
		printf("\n\n\t");
		printf("您是否确认添加该学生？");
		a = getch();
		if (a == 'y' || a == 'Y' || a == 13)
		{
			pNew->pNext = pHead->pNext;/*新建节点的数据域指向头节点*/
			pHead->pNext = pNew; /* 将新建节点数据域传给头节点*/
			pNew = NULL;/*释放pNew的内存*/
			iCount++;
		}
	}
	printf("\n\n\n\n\n\t\t\t\t\t录入学生成功...\n\n");
	printf("\t\t\t\t\t按任意键退出...\n\n");
	a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		system("cls");
}
void Recharge()
{
	Head();
	char ID[20];
	int a;
	time_t t;
	struct tm* lt;
	time(&t);//获取Unix时间戳。
	lt = localtime(&t);//转为时间结构。
	pNew = (PSTU)malloc(sizeof(STU));
	printf("\t\t\t\t\t\t查询一卡通余额：\n\n\n");
	printf("\t\t\t\t\t\t请输入学号：");
	scanf("%s", ID);
	system("CLS");
	PSTU p1;
	p1 = pHead->pNext;	//指向第一个节点 如果链表为 NULL ，则p1为 NULL
	while (p1 != NULL)		//遍历所有学生
	{
		if (strcmp(p1->cNumber, ID) == 0)
		{
			char i[50], j[50], l[50];
			float k = p1->balance;
			strcpy(i, p1->cNumber); strcpy(j, p1->cName);  strcpy(l, p1->Meword);
			printf("\n\n\n\t\t\t\t\t要查询的学生信息...\n\n");
			printf("\n\n\t学号 \t\t学生姓名 \t\t 余额 ");
			printf("\n\t%-12s\t%-20s\t%-6.2f\t", p1->cNumber, p1->cName, p1->balance);
			printf("\n\n\t");
			strcpy(pNew->cNumber, i); strcpy(pNew->cName, j); strcpy(pNew->Meword, l);
			pNew->balance = k;
			pNew->year = lt->tm_year + 1900;//充值日期：年 
			pNew->month = lt->tm_mon + 1;//充值日期：月 
			pNew->day = lt->tm_mday;//充值日期：天 
			pNew->hour = lt->tm_hour;//时 
			pNew->min = lt->tm_min;//分
			pNew->sec = lt->tm_sec;//秒
			printf("%d/%d/%d %d:%d:%d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
			printf("\n\t\t\t\t\t\t充值金额:");
			scanf("%f", &pNew->recharge);
			pNew->consume = 0;
			pNew->Y = 0;//与消费区分
			pNew->balance = pNew->balance + pNew->recharge;//修改余额(增)

			pNew->pNext = pHead->pNext;/*新建节点的数据域指向头节点*/
			pHead->pNext = pNew; /* 将新建节点数据域传给头节点*/
			pNew = NULL;/*释放pNew的内存*/
			iCount++;
			if (Z == 1)
			{
				printf("\n\n\n\n\n\t\t\t\t\t录入充值信息成功...\n\n");
			}
			else
			{
				printf("\n\n\n\n\n\t\t\t\t\t充值成功...\n\n");
			}
			printf("\n\n\n\n\n\t\t\t\t\t按任意键退出...\n\n");
			a = getch();
			if (a == 'y' || a == 'Y' || a == 13)
				system("CLS");
			return;
		}
		p1 = p1->pNext;
	}
	printf("\n\n\n\n\t\t\t\t\t   没有找到要查询的学生信息......\n\n");
	printf("\n\n\n\n\n\t\t\t\t\t按任意键退出...\n\n");
	a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		system("CLS");
	return;
}
void Consume()
{
	Head();
	char ID[20];
	int a;
	pNew = (PSTU)malloc(sizeof(STU));
	printf("\t\t\t\t\t\t查询一卡通余额：\n\n\n");
	if (Z == 1)
	{
		printf("\t\t\t\t\t\t请输入学号：");//管理员输入要查询的学生
		scanf("%s", ID);
	}
	else
	{
		strcpy(ID, UserName);//学生登陆
	}
	system("CLS");
	//遍历学生信息
	PSTU p1;
	p1 = pHead->pNext;	//指向第一个节点 如果链表为 NULL ，则p1为 NULL
	while (p1 != NULL)		//遍历所有学生
	{
		if (strcmp(p1->cNumber, ID) == 0)
		{
			char i[50], j[50], l[50];//作为中介向新节点传递信息
			float k = p1->balance;
			strcpy(i, p1->cNumber); strcpy(j, p1->cName);  strcpy(l, p1->Meword);
			printf("\n\n\n\t\t\t\t\t要查询的学生信息...\n\n");
			printf("\n\n\t学号 \t\t学生姓名 \t\t 余额 ");
			printf("\n\t%-12s\t%-20s\t%-6.2f\t", p1->cNumber, p1->cName, p1->balance);
			printf("\n\n\t");
			time_t t;
			struct tm* lt;
			time(&t);//获取Unix时间戳。
			lt = localtime(&t);//转为时间结构。				
			strcpy(pNew->cNumber, i); strcpy(pNew->cName, j); strcpy(pNew->Meword, l);
			pNew->balance = k;
			pNew->year = lt->tm_year + 1900;//消费日期：年 
			pNew->month = lt->tm_mon + 1;   //消费日期：月 
			pNew->day = lt->tm_mday;        //消费日期：天 
			pNew->hour = lt->tm_hour;       //消费日期：时 
			pNew->min = lt->tm_min;         //消费日期：分
			pNew->sec = lt->tm_sec;         //消费日期：秒
			printf("%d/%d/%d %d:%d:%d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
			printf("\n\t\t\t\t\t\t消费金额:");
			scanf("%f", &pNew->consume);
			pNew->recharge = 0;
			pNew->Y = 1;//与充值区分
			pNew->balance = pNew->balance - pNew->consume;//修改余额(减)
			pNew->pNext = pHead->pNext;/*新建节点的数据域指向头节点*/
			pHead->pNext = pNew; /* 将新建节点数据域传给头节点*/
			pNew = NULL;
			iCount++;
			if (Z == 1)
			{
				printf("\n\n\n\n\n\t\t\t\t\t录入消费信息成功...\n\n");
			}
			else
			{
				printf("\n\n\n\n\n\t\t\t\t\t消费成功...\n\n");
			}
			printf("\n\n\n\n\n\t\t\t\t\t按任意键退出...\n\n");
			a = getch();
			if (a == 'y' || a == 'Y' || a == 13)
				system("CLS");
			return;
		}
		p1 = p1->pNext;
	}
	printf("\n\n\n\n\t\t\t\t\t   没有找到要查询的学生信息......\n\n");
	printf("\t\t\t\t\t按任意键退出...\n\n");
	a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		system("CLS");
	return;
}
void CCYE()
{

	char ID[20];
	char a;
	printf("\t\t\t\t\t\t查询学生的余额：\n\n\n");
	if (Z == 1)
	{
		printf("\t\t\t\t\t\t请输入学生学号：");
		scanf("%s", ID);
	}
	else
	{
		strcpy(ID, UserName);
	}
	//遍历学生信息
	PSTU p1;
	p1 = pHead->pNext;	//指向第一个节点 如果链表为 NULL ，则p1为 NULL
	Head();
	while (p1 != NULL)		//遍历所有学生
	{
		if (strcmp(p1->cNumber, ID) == 0)
		{
			printf("\n\n\t\t\t学号 \t\t学生姓名 \t\t 余额 ");
			printf("\n\t\t\t%-12s\t%-20s\t%-6.2f\t", p1->cNumber, p1->cName, p1->balance);
			printf("\n\n\t");
			Show_single(p1->cNumber);
			return;
		}
		p1 = p1->pNext;
	}
	printf("\n\n\n\n\t\t\t\t\t   没有找到要查询的学生信息......\n\n");
	printf("\t\t\t\t\t按任意键退出...\n\n");
	a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		system("CLS");
	return;
}
void Show_all()
{
	Head();
	PSTU pCurrent = pHead->pNext;	//指向第一个节点 如果链表为 NULL pCurrent为 NULL
	int index = 1;
	printf("\t\t\t**********************本名单共有 %d 条学生信息*********************\n\n\n", iCount);
	printf("\t\t\t\t\t学号\t\t\t姓名\t充值\t消费\t余额\n\n");
	while (pCurrent != NULL)	//遍历输出所有学生
	{
		printf("\t%d:时间：%d年%d月%d日%d.%d.%d", index, pCurrent->year, pCurrent->month, pCurrent->day, pCurrent->hour, pCurrent->min, pCurrent->sec);
		printf("\t%s\t\t%s\t%.2f\t%.2f\t%.2f\n", pCurrent->cNumber, pCurrent->cName, pCurrent->recharge, pCurrent->consume, pCurrent->balance);

		pCurrent = pCurrent->pNext;	//指向下一个节点
		index++;	//下标加加
	}
	pCurrent = NULL;
	printf("\n\t\t\t\t\t按任意键退出...\n\n");
	char a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		system("CLS");
	return;
}

/************显示查询余额的学生的所有充值消费信息***********/
void Show_single(char* user)
{

	PSTU pCurrent = pHead->pNext;	//指向第一个节点 如果链表为 NULL pCurrent为 NULL
	int index = 1;
	char a;
	printf("\t\t\t**********************充值消费记录*********************\n\n\n");
	printf("\t\t\t\t\t\t学号\t\t姓名\t充值\t消费\t余额\n\n");
	while (pCurrent != NULL)	//遍历所有学生
	{
		if (strcmp(pCurrent->cNumber, user) == 0 && pCurrent->Y != 2)
		{
			printf("\t%d:时间：%d年%d月%d日%d.%d.%d", index, pCurrent->year, pCurrent->month, pCurrent->day, pCurrent->hour, pCurrent->min, pCurrent->sec);
			printf("\t%s\t\t%s\t%.2f\t%.2f\t%.2f\n", pCurrent->cNumber, pCurrent->cName, pCurrent->recharge, pCurrent->consume, pCurrent->balance);
			index++;	//下标加 1		
		}
		pCurrent = pCurrent->pNext;	//指向下一个节点

	}
	pCurrent = NULL;
	printf("\n\t\t\t\t\t按任意键退出...\n\n");
	a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		system("CLS");
	return;
}
void Bill()
{
	Head();
	char ID[100];
	float sume = 0;
	int i = 1;
	printf("\t\t\t\t(注：该账单仅记录消费信息，不会与充值信息抵消)：\n");
	printf("\t\t\t\t**********************消费记录*********************\n\n\n");

	if (Z == 1)
	{
		printf("\t\t\t\t\t\t请输入学生学号：");
		scanf("%s", ID);
	}
	else
	{
		strcpy(ID, UserName);
	}
	PSTU pCurrent;
	pCurrent = pHead->pNext;/*指向第一个节点*/
	printf("\t\t\t\t\t学号\t\t姓名\t消费\t余额\n\n");
	while (pCurrent != NULL)		//遍历所有学生
	{
		if (strcmp(pCurrent->cNumber, ID) == 0)
		{
			if (pCurrent->Y == 1)/*仅显示消费的记录*/
			{
				printf("\t%d:时间：%d年%d月%d日%d.%d.%d", i, pCurrent->year, pCurrent->month, pCurrent->day, pCurrent->hour, pCurrent->min, pCurrent->sec);
				printf("\t%s\t%s\t%.2f\t%.2f\n", pCurrent->cNumber, pCurrent->cName, pCurrent->consume, pCurrent->balance);
				printf("\n\n");
				sume += pCurrent->consume;
				i++;
			}

		}
		pCurrent = pCurrent->pNext;	//指向下一个节点
	}
	printf("\t\t\t\t\t该学生消费总额：%.2f", sume);
	pCurrent = NULL;
	printf("\n\n\t\t\t\t\t按任意键退出...\n\n");
	char a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		printf("\n\n\n");
}
void statistics()
{
	Head();
	int i = 1;
	char ID[13];
	int Year = 0, Month = 0;
	float sume = 0;
	printf("\t\t\t\t(注：该账单仅记录消费信息，不会与充值信息抵消)：\n");
	printf("\t\t\t\t\t\t查询学生的月消费账单：\n\n\n");
	if (Z == 1)
	{
		printf("\t\t\t\t\t\t请输入学生学号:");
		scanf("%s", ID);
	}
	else
	{
		strcpy(ID, UserName);/**直接把学生登录时的账户(学号)复制过来**/
	}
	printf("\t\t\t\t\t\t请输入年:");
	scanf("%d", &Year);
	printf("\n\t\t\t\t\t\t请输入月:");
	scanf("%d", &Month);
	PSTU pCurrent;
	pCurrent = pHead->pNext;
	printf("\n\t\t\t\t\t\t学号\t\t姓名\t消费\t余额\n\n");
	while (pCurrent != NULL)		/**遍历所有学生**/
	{
		if (strcmp(pCurrent->cNumber, ID) == 0 && pCurrent->Y == 1)
		{
			if (Year == pCurrent->year && Month == pCurrent->month)/**显示该月的消费记录**/
			{
				//printf(" \n\t学号 \t\t学生姓名 \t\t 余额 \t\t 消费 ");
				printf("\t%d:时间：%d年%d月%d日%d.%d.%d", i, pCurrent->year, pCurrent->month, pCurrent->day, pCurrent->hour, pCurrent->min, pCurrent->sec);
				printf("\t\t%s\t%s\t%.2f\t%.2f\n", pCurrent->cNumber, pCurrent->cName, pCurrent->consume, pCurrent->balance);
				sume += pCurrent->consume;/**统计该月消费总额**/
				i++;
			}
		}
		pCurrent = pCurrent->pNext;	/**指向下一个节点**/
	}
	printf("\n\t\t该月消费总额：%.2f", sume);
	pCurrent = NULL;
	printf("\n\n\n\t\t\t\t\t按任意键退出...\n\n");
	char a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		printf("\n\n\n");
}
void Change_WORD()
{
	Head();
	char operate, a;
	int i = 0;
	printf("\t\t\t\t\t\t修改一卡通密码：\n\n\n");
	char word[20];
	printf("\n\t\t\t\t\t\t请输入您要想要的密码: ");
	scanf("%s", word);
	printf("\n\n\n\t\t\t\t\t是否确认修改密码(y/Enter):");
	a = getch();
	if (a == 'y' || a == 'Y' || a == 13)/**13是回车键Enter的ASCII值**/
	{
		PSTU pCurrent = pHead->pNext;	/**指向第一个节点**/
		while (pCurrent != NULL)	    /**遍历全部的节点**/
		{
			if (strcmp(pCurrent->cNumber, UserName) == 0)/*仅对最新*/
			{
				strcpy(pCurrent->Meword, word);/*为每个节点修改密码*/
				i = 1;
			}
			pCurrent = pCurrent->pNext;	/**指向下一个节点**/
		}
		pCurrent = NULL;
		if (i == 1)
		{
			printf("\n\n\n\t\t\t\t\t修改成功...\n\n");
			printf("\t\t\t\t\t按任意键退出...\n\n");
			a = getch();
			if (a == 'y' || a == 'Y' || a == 13)
				printf("\n\n\n");
			return;
		}
		else
		{
			printf("\n\n\n\n\t\t\t\t\t   没有找到要查询的学生信息......\n\n");
			printf("\t\t\t\t\t按任意键退出...\n\n");
			a = getch();
			if (a == 'y' || a == 'Y' || a == 13)
				printf("\n\n\n");
			return;
		}
	}
	else
	{
		printf("\n\n\n\t\t\t\t\t取消修改...\n\n");
		printf("\t\t\t\t\t按任意键退出...\n\n");
		a = getch();
		if (a == 'y' || a == 'Y' || a == 13)
			printf("\n\n\n");
		return;
	}
}
void Quit()
{
	char ch;
	unsigned int i;
	printf("\n\t ");
	for (i = 0; i < 50; i++)
	{
		printf("* ");
		Sleep(10);
	}
	printf("\n\n\t\t\t\t要返回登录界面按任意键\t\t退出并保存数据请按Esc键\n");
	ch = getch();
	if (ch == 0x1b)	//按下esc键
	{
		SaveData();//保存数据
		exit(0);//退出程序
	}
	//重新进入主菜单
	if (Z == 1)
	{
		SMainMenu();//返回管理员主菜单
	}
	else if (Z == 2)
	{
		MainMenu();//返回学生菜单
	}
}
