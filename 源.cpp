#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<Windows.h>
#include <malloc.h>
#define Mname "123"//����Ա�˺�
#define Mpassword "123"//����Ա����
typedef struct Student
{
	char Meword[8];  //ѧ�����룬��ʼΪ123456
	char cNumber[13]; //ѧ��
	char cName[11];   //����
	int year;         //���ڣ��� 
	int month;        //���ڣ��� 
	int day;          //���ڣ��� 
	int hour;         //ʱ
	int min;          //��
	int sec;          //��
	float balance;    //���
	float recharge;   //��ֵ���
	float consume;    //���ѽ�� 
	int Y;            //���ֲ�������ֵΪ0������Ϊ1�����ѧ��Ϊ2
	struct Student* pNext;
}STU, * PSTU;
char UserName[20];//�û���
char UserWord[20];//����

PSTU pHead = NULL;	//��Ϣѧ��ͷ���
PSTU pNew = NULL;	//�����ѧ����Ϣ

size_t iCount = 0;	//��������ڵ�
size_t Z = 0;    //�������ֹ���Ա��ѧ�����ڵ�¼ʱ����ֵͬ��
void Head();  //һ��ͨ����ϵͳ�ַ�ͼ��
void StuManage(); //����Ա��¼���ַ�ͼ��
void Stuage();    //ѧ����¼���ַ�ͼ��
void ReadData();  //��ȡ����
void SaveData();  //��������

void Slogin();    //����Ա��¼
int SisLogin();   //�жϹ���Ա���������Ƿ���ȷ
int SMenuSelect();  //����Աѡ����
void SMainMenu(); //����Ա���˵�

void login();     //ѧ����¼
int isLogin();    //�ж�ѧ�����������Ƿ���ȷ
int MenuSelect();   //ѧ��ѡ����
void MainMenu();  //ѧ�����˵�

void Addup();     //���ѧ��
void Recharge();  //��ֵ
void Consume();   //����
void CCYE();     //����ѯ
void Show_all();  //��ʾȫ��ѧ��
void Show_single(char* user);//��ʾ����ѧ��
void Bill();         //�����˵�
void statistics();     //���Ѱ���ͳ��
void Change_WORD();  //�޸�����
void Quit();        //�˳�
int main()
{
	pHead = (PSTU)malloc(sizeof(STU));
	pHead->pNext = NULL; /*��ʼ������*/
	ReadData(); /*��ȡ�����ļ��е�����*/
	char a;
	do
	{
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t      ���ǹ���Ա(Z)����ѧ��(X)��\n\n");
		printf("\t\t\t\t\t     ��  ��������������������  ��\n");
		printf("\t\t\t\t\t     ��   1. ����Ա:�밴��z    ��\n");
		printf("\t\t\t\t\t     ��  ��������������������  ��\n");
		printf("\t\t\t\t\t     ��   2. ѧ��  :�밴��x    ��\n");
		printf("\t\t\t\t\t     ��  ��������������������  ��\n");
		a = getch();
		if (a == 'z' || a == 'Z')
		{
			system("CLS");//����
			Slogin();
			SMainMenu();
		}
		else if (a == 'x' || a == 'X')
		{
			system("CLS");//����
			login();
			if (isLogin())
			{
				MainMenu();
			}
		}
		else
		{
			printf("�������,�����ԡ�");
			system("cls");//����
		}

	} while (a != 'Z' && a != 'z' && a != 'x' && a != 'X');
	return 0;
}
/************ һ��ͨ����ϵͳ�ַ�ͼ�� ***********/
void Head()
{
	printf("\n\n\n");
	printf("\t\t\t\t\t �� ������������������������������ ��\n");
	printf("\t\t\t\t\t ��           һ��ͨϵͳ           ��\n");
	printf("\t\t\t\t\t �� ������������������������������ ��\n");
	printf("\n\n\n");
}
/************ ����Ա��¼���ַ�ͼ�� ***********/
void StuManage()
{
	printf("\n\n\n");
	printf("\t\t\t\t\t�� �������������������������������������������� ��\n");
	printf("\t\t\t\t\t��          һ��ͨ����ϵͳ   ����Ա��¼��       ��\n");
	printf("\t\t\t\t\t�� �������������������������������������������� ��\n");
	printf("\n\n\n");
}
/************ ѧ����¼���ַ�ͼ�� ***********/
void Stuage()
{
	printf("\n\n\n");
	printf("\t\t\t\t\t�� �������������������������������������������� ��\n");
	printf("\t\t\t\t\t��          һ��ͨ����ϵͳ   ѧ����¼��         ��\n");
	printf("\t\t\t\t\t�� �������������������������������������������� ��\n");
	printf("\n\n\n");
}

void ReadData()
{
	FILE* fRead = fopen("fee.dat", "rb");//��fee.dat�ļ�

	if (fRead == NULL)
	{
		SaveData();	/*�ļ������ھʹ����ļ�*/
		return;
	}
	rewind(fRead);	/*���ļ��ڲ�ָ���ƻ��ļ���ͷ*/
	while (1)
	{

		pNew = (PSTU)malloc(sizeof(STU));	/*����һ���ڴ�*/
		if (pNew)
		{
			fread(pNew, sizeof(STU), 1, fRead);	/* 1 ��ʾ��ȡһ��STU�ֽڴ�С��Ԫ*/
			if (feof(fRead)) break;		/*�ļ�ĩβ�˳�*/
			/*ͷ�巨��������*/
			pNew->pNext = NULL;/*����Ԫ��pNext��Ϊ��*/
			PSTU temp = pHead->pNext;/*����һ����ʱָ�����ָ���ͷ*/
			if (pHead->pNext == NULL)
			{
				pHead->pNext = pNew;/*pHeadΪ������pNewΪ��һ���½��*/
				pNew->pNext = NULL;
			}
			else
			{
				while (temp->pNext != NULL)/*������tempָ��β���*/
				{
					temp = temp->pNext;
				}
				temp->pNext = pNew;/*��β���temp��pNext��ΪpNew,����pNew��Ϊβ���*/
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
		printf("����ʧ��...\n");
		Quit();
	}
	PSTU pCurrent = pHead->pNext;	/*ָ���һ���ڵ�*/
	while (pCurrent != NULL)		/*��������ѧ����Ϣ*/
	{
		fwrite(pCurrent, sizeof(STU), 1, fWrite);/*���ļ�������*/
		pCurrent = pCurrent->pNext;/*ָ����һ���ڵ�*/
	}
	pCurrent = NULL;
	fclose(fWrite);/*�ر��ļ�*/
}
void Slogin()//����Ա��¼
{
	SetConsoleTitle(L"                       һ��ͨ����ϵͳ(����Ա)");
	StuManage();
	int  i;
	char Separation[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
	for (i = 0; i < strlen(Separation); i++)
	{
		printf("%c", Separation[i]);
		Sleep(10);
	}
	printf("\n\n\t\t\t\t\t\t�����������˺�����\n\n");
	printf("\n\t\t\t\t\t\t�˺�:");
	scanf("%s", UserName);
	printf("\n\t\t\t\t\t\t����:");
	scanf("%s", UserWord);
	Z = 1;/*ȫ�ֱ�����Ϊ1��ʾΪ����Ա���*/

}
int SisLogin()
{
	int i;
	int times = 0;	//�����������
	while (!(strcmp(UserName, Mname) == 0 && strcmp(UserWord, Mpassword) == 0))
	{
		times++;	//����������� times++
		if (times > 3)
		{
			printf("\n\n\n\n\t\t\t\t�˺Ż�������������ۼƴﵽ%d�Σ�ϵͳ����3���ر�", times);
			Sleep(1000);
			system("cls");
			char shutdown[] = { "ϵͳ����%d���ر�..." };
			for (i = 0; i < 3; i++)
			{
				printf(shutdown, 3 - i);
				Sleep(1000);
				system("cls");
			}
			exit(0);
		}
		printf("\n\n\n\n\t\t\t\t�˺Ż������������,�㻹��%d�ε�¼���ᣬ����������µ�¼...", 4 - times);
		char a = getch();
		system("cls");
		Slogin();
	}
	return 1;
}
void login()//ѧ����¼
{
	SetConsoleTitle(L"                        һ��ͨ����ϵͳ(ѧ��)");
	Stuage();
	int  i;
	char Separation[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * " };
	for (i = 0; i < strlen(Separation); i++)
	{
		printf("%c", Separation[i]);
		Sleep(10);
	}
	printf("\n\n\t\t\t\t\t\t����������ѧ������\n\n");
	printf("\n\t\t\t\t\t\tѧ��:");
	scanf("%s", UserName);
	printf("\n\t\t\t\t\t\t����:");
	scanf("%s", UserWord);
	Z = 2;/*ȫ�ֱ�����Ϊ2��ʾΪѧ�����*/
}
int isLogin()
{
	int  i;
	int times = 0;	/**�����������**/

	while (1)
	{
		PSTU p;
		p = pHead->pNext;/*ָ���һ���ڵ�*/
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
			printf("\n\n\n\n\t\t\t\t�˺Ż�������������ۼƴﵽ%d�Σ�ϵͳ����3���ر�", times);
			Sleep(1000);
			system("cls");
			char shutdown[] = { "ϵͳ����%d���ر�..." };
			for (i = 0; i < 3; i++)
			{
				printf(shutdown, 3 - i);
				Sleep(1000);
				system("cls");
			}
			exit(0);
		}
		printf("\n\n\n\n\t\t\t\t�˺Ż������������,�㻹��%d�ε�¼���ᣬ����������µ�¼...", 4 - times);
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
		printf("\t\t\t\t  ���T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T��\n");
		printf("\t\t\t\t  ��                һ��ͨ����Ա�˵�               ��\n");
		printf("\t\t\t\t  ���T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T��\n");
		printf("\t\t\t\t    ������������������������������������������������������������������������������������������\n");
		printf("\t\t\t\t    ��                     ��                     ��\n");
		printf("\t\t\t\t    �� 1. �������         ��         2. ����ֵ ��\n");
		printf("\t\t\t\t    ���������������������� �� ����������������������\n");
		printf("\t\t\t\t    �� 3. ������           ��         4. ȫ��ѧ�� ��\n");
		printf("\t\t\t\t    ���������������������� �� ����������������������\n");
		printf("\t\t\t\t    �� 5. ����ѯ         ��         6. �����˵� ��\n");
		printf("\t\t\t\t    ���������������������� �� ����������������������\n");
		printf("\t\t\t\t    �� 0. �˳�����         ��                     ��\n");
		printf("\t\t\t\t    ������������������������������������������������������������������������������������������\n");
		printf("\t\t\t\t\t\t  ����ѡ��(0-5):");
		c = getche();
	} while (c < '0' || c > '6');
	return c - '0';
}

void SMainMenu()
{
	if (SisLogin())
	{
		//��¼�ɹ�
		switch (SMenuSelect())	//�˵�ѡ��
		{
		case 1:	//���ѧ����Ϣ
			system("cls");
			Addup();
			Quit();
			break;
		case 2:	//��ֵ
			system("cls");
			Recharge();
			Quit();
			break;
		case 3:	//���Ѱ�ÿ��ͳ��
			system("cls");
			statistics();
			Quit();
			break;
		case 4:	//ȫ����Ϣ
			system("cls");
			Show_all();
			Quit();
			break;
		case 5:	//��ѯ���
			system("cls");
			CCYE();
			Quit();
			break;
		case 6:	//�����˵�
			system("cls");
			Bill();
			Quit();
			break;
		case 0:	//�˳�����
			system("cls");
			Head();
			Quit();	//�˳��򷵻����˵�
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
		printf("\t\t\t\t  ���T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T��\n");
		printf("\t\t\t\t  ��                һ��ͨѧ�����ܲ˵�             ��\n");
		printf("\t\t\t\t  ���T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T��\n");
		printf("\t\t\t\t    ������������������������������������������������������������������������������������������\n");
		printf("\t\t\t\t    ��                     ��                     ��\n");
		printf("\t\t\t\t    �� 1. ÿ������         ��         2. ��ѯ��� ��\n");
		printf("\t\t\t\t    ���������������������� �� ����������������������\n");
		printf("\t\t\t\t    �� 3. �����˵�         ��         4. ����     ��\n");
		printf("\t\t\t\t    ���������������������� �� ����������������������\n");
		printf("\t\t\t\t    �� 5. ��ֵ             ��         6. �޸����� ��\n");
		printf("\t\t\t\t    ���������������������� �� ����������������������\n");
		printf("\t\t\t\t    �� 0. �˳�����         ��                     ��\n");
		printf("\t\t\t\t    ������������������������������������������������������������������������������������������\n");
		printf("\t\t\t\t\t\t  ����ѡ��(0-6):");
		A = getche();
	} while (A < '0' || A > '6');
	return A - '0';
}

void MainMenu()
{
	switch (MenuSelect())	//�˵�ѡ��
	{
	case 1:	//���Ѱ�ÿ��ͳ��
		system("cls");
		statistics();
		Quit();
		break;
	case 2:	//��ѯ���
		system("cls");
		CCYE();
		Quit();
		break;
	case 3:	//�����˵�
		system("cls");
		Bill();
		Quit();
		break;
	case 4:	//����
		system("cls");
		Consume();
		Quit();
		break;
	case 5:	//��ֵ
		system("cls");
		Recharge();
		Quit();
		break;
	case 6:	//�޸�����
		system("cls");
		Change_WORD();
		Quit();
		break;
	case 0:		//�˳�����
		system("cls");
		Head();
		Quit();	//�˳��򷵻����˵�
		break;
	}
}
void Addup()
{
	time_t t;
	struct tm* lt;
	time(&t);//��ȡUnixʱ�����
	lt = localtime(&t);//תΪʱ��ṹ��
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
		printf("\t\t\t\t\t\t���ѧ����Ϣ:\n\n\n\n\t\t\t\t\t\tѧ��:");
		scanf("%s", pNew->cNumber);
		printf("\n\t\t\t\t\t\t����:");
		scanf("%s", pNew->cName);
		pNew->year = lt->tm_year + 1900;//������ڣ��� 
		pNew->month = lt->tm_mon + 1;//������ڣ��� 
		pNew->day = lt->tm_mday;//������ڣ��� 
		pNew->hour = lt->tm_hour;//ʱ 
		pNew->min = lt->tm_min;//��
		pNew->sec = lt->tm_sec;//��
		pNew->recharge = 0;//��ֵ���
		pNew->consume = 0;//���ѽ��
		pNew->balance = 0;//���
		pNew->Y = 2;
		char words[10] = { "123456" };
		strcpy(pNew->Meword, "123456");
		printf("\n\n\t���������ϢΪ��");
		printf("\n\n\tѧ�� \t\tѧ������ \t\t ��� ");
		printf("\n\t%-12s\t%-20s\t%-6.2f\t", pNew->cNumber, pNew->cName, pNew->balance);
		printf("\n\n\t");
		printf("���Ƿ�ȷ����Ӹ�ѧ����");
		a = getch();
		if (a == 'y' || a == 'Y' || a == 13)
		{
			pNew->pNext = pHead->pNext;/*�½��ڵ��������ָ��ͷ�ڵ�*/
			pHead->pNext = pNew; /* ���½��ڵ������򴫸�ͷ�ڵ�*/
			pNew = NULL;/*�ͷ�pNew���ڴ�*/
			iCount++;
		}
	}
	printf("\n\n\n\n\n\t\t\t\t\t¼��ѧ���ɹ�...\n\n");
	printf("\t\t\t\t\t��������˳�...\n\n");
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
	time(&t);//��ȡUnixʱ�����
	lt = localtime(&t);//תΪʱ��ṹ��
	pNew = (PSTU)malloc(sizeof(STU));
	printf("\t\t\t\t\t\t��ѯһ��ͨ��\n\n\n");
	printf("\t\t\t\t\t\t������ѧ�ţ�");
	scanf("%s", ID);
	system("CLS");
	PSTU p1;
	p1 = pHead->pNext;	//ָ���һ���ڵ� �������Ϊ NULL ����p1Ϊ NULL
	while (p1 != NULL)		//��������ѧ��
	{
		if (strcmp(p1->cNumber, ID) == 0)
		{
			char i[50], j[50], l[50];
			float k = p1->balance;
			strcpy(i, p1->cNumber); strcpy(j, p1->cName);  strcpy(l, p1->Meword);
			printf("\n\n\n\t\t\t\t\tҪ��ѯ��ѧ����Ϣ...\n\n");
			printf("\n\n\tѧ�� \t\tѧ������ \t\t ��� ");
			printf("\n\t%-12s\t%-20s\t%-6.2f\t", p1->cNumber, p1->cName, p1->balance);
			printf("\n\n\t");
			strcpy(pNew->cNumber, i); strcpy(pNew->cName, j); strcpy(pNew->Meword, l);
			pNew->balance = k;
			pNew->year = lt->tm_year + 1900;//��ֵ���ڣ��� 
			pNew->month = lt->tm_mon + 1;//��ֵ���ڣ��� 
			pNew->day = lt->tm_mday;//��ֵ���ڣ��� 
			pNew->hour = lt->tm_hour;//ʱ 
			pNew->min = lt->tm_min;//��
			pNew->sec = lt->tm_sec;//��
			printf("%d/%d/%d %d:%d:%d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
			printf("\n\t\t\t\t\t\t��ֵ���:");
			scanf("%f", &pNew->recharge);
			pNew->consume = 0;
			pNew->Y = 0;//����������
			pNew->balance = pNew->balance + pNew->recharge;//�޸����(��)

			pNew->pNext = pHead->pNext;/*�½��ڵ��������ָ��ͷ�ڵ�*/
			pHead->pNext = pNew; /* ���½��ڵ������򴫸�ͷ�ڵ�*/
			pNew = NULL;/*�ͷ�pNew���ڴ�*/
			iCount++;
			if (Z == 1)
			{
				printf("\n\n\n\n\n\t\t\t\t\t¼���ֵ��Ϣ�ɹ�...\n\n");
			}
			else
			{
				printf("\n\n\n\n\n\t\t\t\t\t��ֵ�ɹ�...\n\n");
			}
			printf("\n\n\n\n\n\t\t\t\t\t��������˳�...\n\n");
			a = getch();
			if (a == 'y' || a == 'Y' || a == 13)
				system("CLS");
			return;
		}
		p1 = p1->pNext;
	}
	printf("\n\n\n\n\t\t\t\t\t   û���ҵ�Ҫ��ѯ��ѧ����Ϣ......\n\n");
	printf("\n\n\n\n\n\t\t\t\t\t��������˳�...\n\n");
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
	printf("\t\t\t\t\t\t��ѯһ��ͨ��\n\n\n");
	if (Z == 1)
	{
		printf("\t\t\t\t\t\t������ѧ�ţ�");//����Ա����Ҫ��ѯ��ѧ��
		scanf("%s", ID);
	}
	else
	{
		strcpy(ID, UserName);//ѧ����½
	}
	system("CLS");
	//����ѧ����Ϣ
	PSTU p1;
	p1 = pHead->pNext;	//ָ���һ���ڵ� �������Ϊ NULL ����p1Ϊ NULL
	while (p1 != NULL)		//��������ѧ��
	{
		if (strcmp(p1->cNumber, ID) == 0)
		{
			char i[50], j[50], l[50];//��Ϊ�н����½ڵ㴫����Ϣ
			float k = p1->balance;
			strcpy(i, p1->cNumber); strcpy(j, p1->cName);  strcpy(l, p1->Meword);
			printf("\n\n\n\t\t\t\t\tҪ��ѯ��ѧ����Ϣ...\n\n");
			printf("\n\n\tѧ�� \t\tѧ������ \t\t ��� ");
			printf("\n\t%-12s\t%-20s\t%-6.2f\t", p1->cNumber, p1->cName, p1->balance);
			printf("\n\n\t");
			time_t t;
			struct tm* lt;
			time(&t);//��ȡUnixʱ�����
			lt = localtime(&t);//תΪʱ��ṹ��				
			strcpy(pNew->cNumber, i); strcpy(pNew->cName, j); strcpy(pNew->Meword, l);
			pNew->balance = k;
			pNew->year = lt->tm_year + 1900;//�������ڣ��� 
			pNew->month = lt->tm_mon + 1;   //�������ڣ��� 
			pNew->day = lt->tm_mday;        //�������ڣ��� 
			pNew->hour = lt->tm_hour;       //�������ڣ�ʱ 
			pNew->min = lt->tm_min;         //�������ڣ���
			pNew->sec = lt->tm_sec;         //�������ڣ���
			printf("%d/%d/%d %d:%d:%d", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
			printf("\n\t\t\t\t\t\t���ѽ��:");
			scanf("%f", &pNew->consume);
			pNew->recharge = 0;
			pNew->Y = 1;//���ֵ����
			pNew->balance = pNew->balance - pNew->consume;//�޸����(��)
			pNew->pNext = pHead->pNext;/*�½��ڵ��������ָ��ͷ�ڵ�*/
			pHead->pNext = pNew; /* ���½��ڵ������򴫸�ͷ�ڵ�*/
			pNew = NULL;
			iCount++;
			if (Z == 1)
			{
				printf("\n\n\n\n\n\t\t\t\t\t¼��������Ϣ�ɹ�...\n\n");
			}
			else
			{
				printf("\n\n\n\n\n\t\t\t\t\t���ѳɹ�...\n\n");
			}
			printf("\n\n\n\n\n\t\t\t\t\t��������˳�...\n\n");
			a = getch();
			if (a == 'y' || a == 'Y' || a == 13)
				system("CLS");
			return;
		}
		p1 = p1->pNext;
	}
	printf("\n\n\n\n\t\t\t\t\t   û���ҵ�Ҫ��ѯ��ѧ����Ϣ......\n\n");
	printf("\t\t\t\t\t��������˳�...\n\n");
	a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		system("CLS");
	return;
}
void CCYE()
{

	char ID[20];
	char a;
	printf("\t\t\t\t\t\t��ѯѧ������\n\n\n");
	if (Z == 1)
	{
		printf("\t\t\t\t\t\t������ѧ��ѧ�ţ�");
		scanf("%s", ID);
	}
	else
	{
		strcpy(ID, UserName);
	}
	//����ѧ����Ϣ
	PSTU p1;
	p1 = pHead->pNext;	//ָ���һ���ڵ� �������Ϊ NULL ����p1Ϊ NULL
	Head();
	while (p1 != NULL)		//��������ѧ��
	{
		if (strcmp(p1->cNumber, ID) == 0)
		{
			printf("\n\n\t\t\tѧ�� \t\tѧ������ \t\t ��� ");
			printf("\n\t\t\t%-12s\t%-20s\t%-6.2f\t", p1->cNumber, p1->cName, p1->balance);
			printf("\n\n\t");
			Show_single(p1->cNumber);
			return;
		}
		p1 = p1->pNext;
	}
	printf("\n\n\n\n\t\t\t\t\t   û���ҵ�Ҫ��ѯ��ѧ����Ϣ......\n\n");
	printf("\t\t\t\t\t��������˳�...\n\n");
	a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		system("CLS");
	return;
}
void Show_all()
{
	Head();
	PSTU pCurrent = pHead->pNext;	//ָ���һ���ڵ� �������Ϊ NULL pCurrentΪ NULL
	int index = 1;
	printf("\t\t\t**********************���������� %d ��ѧ����Ϣ*********************\n\n\n", iCount);
	printf("\t\t\t\t\tѧ��\t\t\t����\t��ֵ\t����\t���\n\n");
	while (pCurrent != NULL)	//�����������ѧ��
	{
		printf("\t%d:ʱ�䣺%d��%d��%d��%d.%d.%d", index, pCurrent->year, pCurrent->month, pCurrent->day, pCurrent->hour, pCurrent->min, pCurrent->sec);
		printf("\t%s\t\t%s\t%.2f\t%.2f\t%.2f\n", pCurrent->cNumber, pCurrent->cName, pCurrent->recharge, pCurrent->consume, pCurrent->balance);

		pCurrent = pCurrent->pNext;	//ָ����һ���ڵ�
		index++;	//�±�Ӽ�
	}
	pCurrent = NULL;
	printf("\n\t\t\t\t\t��������˳�...\n\n");
	char a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		system("CLS");
	return;
}

/************��ʾ��ѯ����ѧ�������г�ֵ������Ϣ***********/
void Show_single(char* user)
{

	PSTU pCurrent = pHead->pNext;	//ָ���һ���ڵ� �������Ϊ NULL pCurrentΪ NULL
	int index = 1;
	char a;
	printf("\t\t\t**********************��ֵ���Ѽ�¼*********************\n\n\n");
	printf("\t\t\t\t\t\tѧ��\t\t����\t��ֵ\t����\t���\n\n");
	while (pCurrent != NULL)	//��������ѧ��
	{
		if (strcmp(pCurrent->cNumber, user) == 0 && pCurrent->Y != 2)
		{
			printf("\t%d:ʱ�䣺%d��%d��%d��%d.%d.%d", index, pCurrent->year, pCurrent->month, pCurrent->day, pCurrent->hour, pCurrent->min, pCurrent->sec);
			printf("\t%s\t\t%s\t%.2f\t%.2f\t%.2f\n", pCurrent->cNumber, pCurrent->cName, pCurrent->recharge, pCurrent->consume, pCurrent->balance);
			index++;	//�±�� 1		
		}
		pCurrent = pCurrent->pNext;	//ָ����һ���ڵ�

	}
	pCurrent = NULL;
	printf("\n\t\t\t\t\t��������˳�...\n\n");
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
	printf("\t\t\t\t(ע�����˵�����¼������Ϣ���������ֵ��Ϣ����)��\n");
	printf("\t\t\t\t**********************���Ѽ�¼*********************\n\n\n");

	if (Z == 1)
	{
		printf("\t\t\t\t\t\t������ѧ��ѧ�ţ�");
		scanf("%s", ID);
	}
	else
	{
		strcpy(ID, UserName);
	}
	PSTU pCurrent;
	pCurrent = pHead->pNext;/*ָ���һ���ڵ�*/
	printf("\t\t\t\t\tѧ��\t\t����\t����\t���\n\n");
	while (pCurrent != NULL)		//��������ѧ��
	{
		if (strcmp(pCurrent->cNumber, ID) == 0)
		{
			if (pCurrent->Y == 1)/*����ʾ���ѵļ�¼*/
			{
				printf("\t%d:ʱ�䣺%d��%d��%d��%d.%d.%d", i, pCurrent->year, pCurrent->month, pCurrent->day, pCurrent->hour, pCurrent->min, pCurrent->sec);
				printf("\t%s\t%s\t%.2f\t%.2f\n", pCurrent->cNumber, pCurrent->cName, pCurrent->consume, pCurrent->balance);
				printf("\n\n");
				sume += pCurrent->consume;
				i++;
			}

		}
		pCurrent = pCurrent->pNext;	//ָ����һ���ڵ�
	}
	printf("\t\t\t\t\t��ѧ�������ܶ%.2f", sume);
	pCurrent = NULL;
	printf("\n\n\t\t\t\t\t��������˳�...\n\n");
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
	printf("\t\t\t\t(ע�����˵�����¼������Ϣ���������ֵ��Ϣ����)��\n");
	printf("\t\t\t\t\t\t��ѯѧ�����������˵���\n\n\n");
	if (Z == 1)
	{
		printf("\t\t\t\t\t\t������ѧ��ѧ��:");
		scanf("%s", ID);
	}
	else
	{
		strcpy(ID, UserName);/**ֱ�Ӱ�ѧ����¼ʱ���˻�(ѧ��)���ƹ���**/
	}
	printf("\t\t\t\t\t\t��������:");
	scanf("%d", &Year);
	printf("\n\t\t\t\t\t\t��������:");
	scanf("%d", &Month);
	PSTU pCurrent;
	pCurrent = pHead->pNext;
	printf("\n\t\t\t\t\t\tѧ��\t\t����\t����\t���\n\n");
	while (pCurrent != NULL)		/**��������ѧ��**/
	{
		if (strcmp(pCurrent->cNumber, ID) == 0 && pCurrent->Y == 1)
		{
			if (Year == pCurrent->year && Month == pCurrent->month)/**��ʾ���µ����Ѽ�¼**/
			{
				//printf(" \n\tѧ�� \t\tѧ������ \t\t ��� \t\t ���� ");
				printf("\t%d:ʱ�䣺%d��%d��%d��%d.%d.%d", i, pCurrent->year, pCurrent->month, pCurrent->day, pCurrent->hour, pCurrent->min, pCurrent->sec);
				printf("\t\t%s\t%s\t%.2f\t%.2f\n", pCurrent->cNumber, pCurrent->cName, pCurrent->consume, pCurrent->balance);
				sume += pCurrent->consume;/**ͳ�Ƹ��������ܶ�**/
				i++;
			}
		}
		pCurrent = pCurrent->pNext;	/**ָ����һ���ڵ�**/
	}
	printf("\n\t\t���������ܶ%.2f", sume);
	pCurrent = NULL;
	printf("\n\n\n\t\t\t\t\t��������˳�...\n\n");
	char a = getch();
	if (a == 'y' || a == 'Y' || a == 13)
		printf("\n\n\n");
}
void Change_WORD()
{
	Head();
	char operate, a;
	int i = 0;
	printf("\t\t\t\t\t\t�޸�һ��ͨ���룺\n\n\n");
	char word[20];
	printf("\n\t\t\t\t\t\t��������Ҫ��Ҫ������: ");
	scanf("%s", word);
	printf("\n\n\n\t\t\t\t\t�Ƿ�ȷ���޸�����(y/Enter):");
	a = getch();
	if (a == 'y' || a == 'Y' || a == 13)/**13�ǻس���Enter��ASCIIֵ**/
	{
		PSTU pCurrent = pHead->pNext;	/**ָ���һ���ڵ�**/
		while (pCurrent != NULL)	    /**����ȫ���Ľڵ�**/
		{
			if (strcmp(pCurrent->cNumber, UserName) == 0)/*��������*/
			{
				strcpy(pCurrent->Meword, word);/*Ϊÿ���ڵ��޸�����*/
				i = 1;
			}
			pCurrent = pCurrent->pNext;	/**ָ����һ���ڵ�**/
		}
		pCurrent = NULL;
		if (i == 1)
		{
			printf("\n\n\n\t\t\t\t\t�޸ĳɹ�...\n\n");
			printf("\t\t\t\t\t��������˳�...\n\n");
			a = getch();
			if (a == 'y' || a == 'Y' || a == 13)
				printf("\n\n\n");
			return;
		}
		else
		{
			printf("\n\n\n\n\t\t\t\t\t   û���ҵ�Ҫ��ѯ��ѧ����Ϣ......\n\n");
			printf("\t\t\t\t\t��������˳�...\n\n");
			a = getch();
			if (a == 'y' || a == 'Y' || a == 13)
				printf("\n\n\n");
			return;
		}
	}
	else
	{
		printf("\n\n\n\t\t\t\t\tȡ���޸�...\n\n");
		printf("\t\t\t\t\t��������˳�...\n\n");
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
	printf("\n\n\t\t\t\tҪ���ص�¼���水�����\t\t�˳������������밴Esc��\n");
	ch = getch();
	if (ch == 0x1b)	//����esc��
	{
		SaveData();//��������
		exit(0);//�˳�����
	}
	//���½������˵�
	if (Z == 1)
	{
		SMainMenu();//���ع���Ա���˵�
	}
	else if (Z == 2)
	{
		MainMenu();//����ѧ���˵�
	}
}
