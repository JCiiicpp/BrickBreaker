 #include <iostream>
#include <conio.h>
#include <string>
using namespace std;

int main3() {

	char username[20] = { "" };
	char password[20] = { "" };
	printf("�û���:");
	gets_s(username, 20);
	printf("��  ��:");
	int key = 0;
	int i = 0;
	while ((key = _getch()) != '\r')
	{
		if (key == '\b')
		{
			printf("\b \b");
			password[i] = '\0';
			i--;
			continue;
		}
		putchar('*');
		password[i++] = key;
	}
	//password[i]='\0';
	printf("\n");
	//strcmp(username, "root") ����0  !0
	//if (strcmp(username, "root")==0 && strcmp(password, "123456")==0) 
	if (!strcmp(username, "root") && !strcmp(password, "123456"))
	{
		printf("��¼�ɹ���\n");
	}
	else
	{
		printf("��¼ʧ��!\n");
	}

	return 0;
}