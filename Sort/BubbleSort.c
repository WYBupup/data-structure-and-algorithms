#include<stdio.h>

void BubbleSort_up(int *array,int length)
{
    int temp,flag=1;//tell if during the succesive comparsion exchang happen, if not there is no need to continue
    for(int i=1;i<=length-1;i++)
    {
        if(flag==0)
        {
            break;
        }
        flag=0;
        for(int j=0;j<length-i;j++)
        {
            if(array[j]>array[j+1])
            {
                flag=1;
                temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
        }
    }
}

void BubbleSort_down(int *array, int length)
{
    int temp,flag=1;
    for(int i=0;i<length-1;i++)
    {   
        if(flag==0)
        {
            break;
        }
        flag=0;
        for(int j=length-1;j>i;j--)
        {
            if(array[j-1]>array[j])
            {
                flag=1;
                temp=array[j-1];
                array[j-1]=array[j];
                array[j]=temp;
            }
        }
    }
}

void show_array(int *array, int length)
{
    for(int i=0;i<length;i++)
    {
        printf("%d ",array[i]);
    }
    putchar('\n');
}

int main(void)
{
    int array[]={1,9,10,7,100,20,8,4,6,0,1,44,5};
    show_array(array,13);
    BubbleSort_up(array,13);
    //BubbleSort_up(array,13);
    show_array(array,13);
    return 1;
}