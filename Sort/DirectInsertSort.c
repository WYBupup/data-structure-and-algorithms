#include<stdio.h>
#include<stdlib.h>

void show_array(int *array, int length)
{
    for(int i=0;i<length;i++)
    {
        printf("%d ",array[i]);
    }
    putchar('\n');
}

void DirectInsertSort(int *array,int length)
{
    int temp;
    int insert_index,target_index;
    for(target_index=1;target_index<length;target_index++)
    {
        temp=array[target_index];
        for(insert_index=target_index;insert_index>0&&array[insert_index-1]>temp;insert_index--)
        {
            array[insert_index]=array[insert_index-1];
        }
        if(insert_index!=target_index)
        {
            array[insert_index]=temp;
        }
    }
}



int main(void)
{
    int array[]={1,9,10,7,100,20,8,4,6,0,1,44,5};
    show_array(array,13);
    DirectInsertSort(array,13);
    show_array(array,13);
    return 1;
}


