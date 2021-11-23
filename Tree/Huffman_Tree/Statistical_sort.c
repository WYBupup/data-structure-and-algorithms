#include<stdio.h>
#define MAX 128
//这部分包括对输入的字符串的统计 
//统计输入字符串的所有字符的出现次数
//对字符串内出现的字符，根据出现的频率进行排序 

typedef struct
{
	char data;
	int frequency;
}Freq_Char;

typedef struct 
{
	Freq_Char list[MAX];
	int length;
}Freq_List;

Freq_List Compute_ch_freq(char *str);
void Tranverse_freq_list(Freq_List list);
void Sort_freq_list(Freq_List *list);



Freq_List Compute_ch_freq(char *str) //Compute frequency for every character in str
{
	//Initialize frequency list
	Freq_List freq_list;
	freq_list.length=0;
	
	//compute frequency
	for (int i=0;str[i]!='\0';i++)
	{
		//find the location of str[i] in freq_list
		int index=0;
		for (index; index<freq_list.length; index++)
		{
			if(freq_list.list[index].data==str[i])
			{
				break;
			}
		}
		
		//
		if (index<freq_list.length)
		{
			freq_list.list[index].frequency++;
		}
		else
		{
			freq_list.list[index].data=str[i];
			freq_list.list[index].frequency=1;
			freq_list.length++;
		}
	}
	return freq_list;
}

void Tranverse_freq_list(Freq_List list)
{
	printf("Index    Character      Frequency\n");
	int index=1;
	for (int i=0;i<list.length;i++)
	{
		if(index>9)
		{
			printf(" %d         %c               %d\n",index++, list.list[i].data,list.list[i].frequency);
		}
		else
		{
			printf("  %d         %c               %d\n",index++, list.list[i].data,list.list[i].frequency);
		}
		
	}
	printf("\n\n");
}


// sort the Frequency list
void Sort_freq_list(Freq_List *list)
{
	int length=(*list).length;

	
	//冒泡排序
	for (int i=0;i<length-1;i++)
	{
		for (int j=0;j<length-i-1;j++)
		{
			if(list->list[j].frequency>list->list[j+1].frequency)
			{
				Freq_Char temp=list->list[j];
				list->list[j]=list->list[j+1];
				list->list[j+1]=temp;
			}	
		}	
	} 
	
}

