#include<stdio.h>
//利用递归实现折半查找
void fast_sort(int array[],int left,int right,int num)
{
	int pivot=array[(left+right)/2+1];
	int i=left;
	int j=right;
	while(i<=j)//这里有等于好的原因是 要让j<i.因为在i前面的必定小于等于pivot，在j后面的必定大于等于pivot。所以i=j时：1、假设此时array[i]=pivot则i、j均自动向前向后一位 ;2、array[i]>pivot，j向前一位；3、array[i]<pivoti向前一位 
	{
		while(array[i]<pivot)
		{
			i++;
		}
		while(array[j]>pivot)
		{
			j--;
		}
		if(i<=j)//小于等于的原因：当a[i]==a[j]==pivot(i==j)时 ，如果不对i,j加减则陷入死循环 
		{
			if(i!=j)
			{
				int temp=array[i];
		    	array[i]=array[j];
		    	array[j]=temp;
			}
			//print the list after sorting
			for (int i=0;i<num;i++)
        	{
	        	printf("%d ",array[i]);
        	} 
        	putchar('\n');
        	
			i++;
			j--;
		}
	}
	if(i<right)
	{
		fast_sort(array, i,right,num);
	}
	if(j>left)
	{
		fast_sort(array, left,j,num);
	}
}

int half_search(int array[],int target,int left,int right)
{
	int mid=(left+right)/2;
	int pivot=array[mid];
	if(pivot>target)
	{
		if(mid-1<left)
		{
			return -1;
		}
		return half_search(array, target,left,mid-1);
	}
	else if(pivot<target)
	{
		if(mid+1>right)
		{
			return -1;
		}
		return half_search(array, target,mid+1,right);
	}
	else if(pivot==target)
	{
		return mid;
	}
	
}

int main(void)
{
	//get the array
	int num;
	printf("How many number do you want to insert:");
	if(scanf("%d",&num)!=1)
	{
		printf("Please enter the appropriate number!!\n");
		return 0;
	}
	int array[num];
	printf("Enter a series of integer:");
	for(int i=0;i<num;i++)
	{
		if(scanf("%d",array+i)!=1)
		{
			printf("Please enter the appropraite number!!\n");
			return 0;
		}
	}
	printf("You have enter:");
	for (int i=0;i<num;i++)
	{
		printf("%d ",array[i]);
	} 
	putchar('\n');
	
	//sort
	fast_sort(array,0,num-1,num);
	printf("After sort:");
	for (int i=0;i<num;i++)
	{
		printf("%d ",array[i]);
	} 
	
	//search
	int target;
	printf("\nenter the number you want to search:");	 
	if(scanf("%d",&target)!=1)
	{
		printf("Please enter the appropriate number!!\n");
		return 0;
	}
	int index=half_search(array,target,0,num-1);
	if(index>=0)
	{
		printf("index:%d  value:%d",index,array[index]);
	}
	else
	{
		printf("No such element!!\n");
	}
	
	return 0;
} 
