#include<stdio.h>
#include<stdlib.h>
#define MAX 128

void show_array(int *array, int length)
{
    for(int i=0;i<length;i++)
    {
        printf("%d ",array[i]);
    }
}

void merging(int *array_left, int length_left, int *array_right, int length_right)
{
    // array_left and array_right is already well sorted
    int temp[MAX];
    int index_temp=0,index_left=0,index_right=0;

    while(index_left<length_left && index_right<length_right)
    {
        if(array_left[index_left]<array_right[index_right])
        {
            temp[index_temp++]=array_left[index_left++];
        }
        else
        {
            temp[index_temp++]=array_right[index_right++];
        }
    }

    //put the left element in the array
    while(index_left<length_left)
    {
        temp[index_temp++]=array_left[index_left++];
    }

    while(index_right<length_right)
    {
        temp[index_temp++]=array_right[index_right++];
    }

    for(int i=0;i<index_temp;i++)
    {
        array_left[i]=temp[i];
    }
}

void MergeSort_Recursion(int *array, int length)
{
    if(length<=1)
    {
        return;
    }
    int *array_left=array;
    int length_left=length/2;
    int *array_right=array+length_left;
    int length_right=length-length_left;

    MergeSort_Recursion(array_left,length_left);
    MergeSort_Recursion(array_right,length_right);
    //array_left and array_right is sorted 
    merging(array_left,length_left,array_right, length_right);
}

void MergeSort_Iteration(int *array, int length)
{
    int left_min,left_max,right_min,right_max;
    int sublength;
    int *temp=(int *)malloc(sizeof(int)*length);
    int next=0;

    for(sublength=1;sublength<length;sublength*=2)
    {
        //printf("sublength:%d\n",sublength);
        for(left_min=0;left_min+sublength<length;left_min=right_max)
        {
            left_max=left_min+sublength;
            right_min=left_max;
            right_max=(right_min+sublength)<=length?(right_min+sublength):length;
            /*
            printf("sort left(");
            show_array(array+left_min,left_max-left_min);
            printf(") right(");
            show_array(array+right_min,right_max-right_min);
            printf(")");
            */
            //implement sort
            while(left_min<left_max && right_min<right_max)
            {
                if(array[left_min]<array[right_min])
                {
                    temp[next++]=array[left_min++];
                }
                else
                {
                    temp[next++]=array[right_min++];
                }
            }
            /*
            printf("temp:(");
            show_array(temp,next);
            printf(")\n");

            printf("left_min:%d, left_max:%d, right_min:%d, right_max:%d\n",left_min,left_max,right_min,right_max);
            */
            //assign value to the original array
            while(left_min<left_max)
            {
                array[--right_min]=array[--left_max];
            }

            while(next>0)
            {
                array[--right_min]=temp[--next];
            }
            /*
            show_array(array,length);
            printf("\n\n");
            */
        }
    }
}

int main(void)
{
    int array[]={592,401,874,141,348,72,911,887,820,283,0,7,66};
    show_array(array,13);
    printf("\n");
    MergeSort_Iteration(array,13);
    show_array(array,13);
    printf("\n");

    return 1;
}