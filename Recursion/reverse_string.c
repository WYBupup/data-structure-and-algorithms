#include<stdio.h>
#include<string.h>
//ʵ�����ⳤ���ַ����ķ������ 
void str_reverse()
{
	char ch;
	scanf("%c",&ch);
	if(ch=='\n')
	{
		return;
	}
	else
	{
		str_reverse();
		printf("%c",ch);
	}
}

int main(void)
{
	printf("Enter the string!!\n");
	str_reverse();
	
	
	return 0;
}
