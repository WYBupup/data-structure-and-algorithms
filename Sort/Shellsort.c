#include<stdio.h>

void show_array(int *array, int length)
{
    for(int i=0;i<length;i++)
    {
        printf("%d ",array[i]);
    }
    putchar('\n');
}

void ShellSort(int *array, int length)
{
    int insert_index,temp;
    int i,j,increment;
    for(increment=length/2;increment>=1;increment/=2)
    {
        printf("increment %d\n",increment);
        for(i=0;i<increment;i++)
        {
            for(j=i+increment;j<length;j+=increment)
            {
                temp=array[j];
                for(insert_index=j;insert_index-increment>=0&&array[insert_index-increment]>temp;insert_index-=increment)
                {
                    array[insert_index]=array[insert_index-increment];
                }
                if(insert_index!=j)
                {
                    array[insert_index]=temp;
                }
            }
        }
    }
}

int main(void)
{
    int array[]={592,401,874,141,348,72,911,887,820,283,0,7};
    show_array(array,12);
    ShellSort(array,12);
    show_array(array,12);
    return 1;
}