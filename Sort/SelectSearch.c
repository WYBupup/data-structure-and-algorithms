#include<stdio.h>

void SelectSearch(int *array, int length)
{
    int temp,index;//the minimum's index
    for(int i=0;i<length-1;i++)
    {
        index=i;
        for(int j=i+1;j<length;j++)
        {
            if(array[index]>array[j])
            {
               index=j; 
            }
        }
        if(index!=i)
        {
            temp=array[i];
            array[i]=array[index];
            array[index]=temp;
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
    SelectSearch(array,13);
    show_array(array,13); 
    return 1;
}