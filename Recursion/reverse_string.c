#include<stdio.h>
#include<string.h>
//实现任意长度字符串的反向输出 
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
