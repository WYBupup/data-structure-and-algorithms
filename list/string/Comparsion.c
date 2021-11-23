#include<stdio.h>
#include<string.h>

//效率不高 O(M*N)  回溯法  M:len_attern, N:len_objective
void Brute_Force(char *objective, char *pattern)
{
	int len_pattern = strlen(pattern);
	int len_objective = strlen(objective);
	
	int tar=0,pos=0;
	while(tar<len_objective)
	{
		if(objective[tar]==pattern[pos])
		{
			pos++;
			tar++;
		}
		else
		{
			//当匹配失败时 tar pos 都要后退/回溯 
			tar=tar-pos+1; 
			pos=0;
		}
		
		if(pos==len_pattern)
		{
			printf("The first index of the pattern in objective:%d\n",tar-pos);
			tar=tar-pos+1;
			pos=0;
		}
	}
}




//KMP algorithm

//low efficiency 
/*
void get_next_array(char *pattern, int *next)
{
	int len_pattern = strlen(pattern);
	
	for (int i=0;i<len_pattern;i++)
	{
		//compute next comparsion's start position j
		int j;
		for(j=1;j<=i;j++)
		{
			// tell if the comparsion may succeed if the comparsion starts from j
			int flag=1;
			for(int m=j;m<=i;m++)
			{
				if(m!=i)
				{
					if(pattern[m]!=pattern[m-j])
					{
						flag=0;
						break;
					}
				}
				if(m==i)
				{
					if(pattern[m]==pattern[m-j])
					{
						flag=0;
						break;
					}
				}
			}
			if(flag==1)
			{
				break;
			}
			
		}
		next[i]=j;
	}
 } */
 
 /* 
 void get_next_array(char *pattern, int *next)
 {
 	int len_pattern = strlen(pattern);
 	next[0]=0;
 	int now;
 	for(int i=1;i<len_pattern;i++)
 	{
 		now=next[i-1];
 		while(1)
 		{
 			if(pattern[now]==pattern[i])
 			{
 				next[i]=now+1;
 				break;
			}
			
			if(now<=0)
			{
				next[i]=0;
				break;
			}
			now=next[now-1];
		}
	}
 }




int KMP(char *pattern, char *objective)
{
	int len_pattern=strlen(pattern);
	int len_objective=strlen(objective);
	int next[len_pattern];
	get_next_array(pattern, next);
	
	for(int i=0;i<len_pattern;i++)
	{
		printf("%d ",next[i]);
	}
	putchar('\n');
	
	
	int i=0,j=0,flag;
	while(i+len_pattern<=len_objective)
	{
		flag=1;
		for(;j<len_pattern;j++)
		{
			if(objective[i+j]!=pattern[j])
			{
				flag=0;
				if(j==0)
				{
					i=i+1;
					break;
				}
				//decide next i;
				if(next[j-1]==0)
				{
					if(pattern[j]==pattern[0])
					{
						i=i+j+1;
					}
					else
					{
						i=i+j;
					}
				}
				else
				{
					i=i+j-next[j-1];
				}
				//decide the j
				j= next[j-1];
				break;
			}
		}
		if(flag==1)
		{
			return i;
		}
	}
	return -1;
}*/

//o(M)
void get_next(char *pattern, int *next)
{
	// index : The index of the next which is computed
	// now next[index-1]
	next[0]=0;
	int index=1;
	int now=next[index-1];
	int len_pattern = strlen(pattern);
	while(index<len_pattern)
	{
		if(pattern[now]==pattern[index])
		{
			next[index]=now+1;
			now++;
			index++;
		}
		else if(now>0)
		{
			now=next[now-1];
		}
		else
		{
			next[index]=0;
			index++;
		}
	}
 } 

//o(N) 
void KMP(char *pattern, char *objective)
{
	//可以实现匹配显示objective 中所有pattern的位置 
	int len_pattern =strlen(pattern);
	int len_objective = strlen(objective);
	int tar=0;
	int p=0;
	int next[len_pattern];
	get_next(pattern, next);
	
	for (int i=0;i<len_pattern;i++)
	{
		printf("%d ",next[i]);
	}
	printf("\n");
	
	while(tar<len_objective)
	{
		//当匹配失败是，变化的只有pos，tar不变 
		if(pattern[p]==objective[tar])
		{
			tar++;
			p++;
		}
		else if(p>0)
		{
			p=next[p-1]; 
		}
		else
		{
			tar++;
		}
		if(p==len_pattern)
		{
			//显示当前pattern最开始位置，并进行下一次匹配 
			printf("index:%d\n",tar-p);
			p=next[p-1];
		}
	}
}


int main(void)
{
	/*
	char objective[1000001];
	for (int i=0;i< 999999;i++)
	{
		objective[i]='A';
	}
	objective[ 999999]='B';
	objective[1000000]='\0';
	char pattern[]="AAAB";*/
	
	
	
	char objective[]="ababaabaabacababaabaabac";
	char pattern[]="abaabac";
	//KMP(pattern,objective);
	Brute_Force(objective,pattern);
	/*
	if(index>=0)
	{
		printf("the index of first character of str2 in str1:%d\n\t",index);
		for (int i=0;i<strlen(pattern);i++)
		{
			putchar(objective[index+i]);
		}
		putchar('\n');
	}
	else
	{
		printf("pattern is not in objective\n");
	}*/
	
	
	
	/*
    char pattern[]="beabec";
    int next[strlen(pattern)];
    get_next_array(pattern, next);
    for(int i=0;i<strlen(pattern);i++)
    {
    	printf("%d ",next[i]);
	}*/
	
	
	
	
	
	return 0;
}
