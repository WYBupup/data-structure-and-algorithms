#include<stdio.h>

//implement half search's recursion and iteration version
// prerequsite: the array is sort in ascending order

//recursion
//O(logN)
int HalfSearch_Recursion(int *array, int start,int end,int key)
{
    int pivot=(start+end)/2;
    if(array[pivot]==key)
    {
        return pivot;
    }
    else if(array[pivot]>key)
    {
        end=pivot-1;
    }
    else
    {
        start=pivot+1;
    }

    if(start<=end)
    {
        return HalfSearch_Recursion(array,start,end,key);
    }
    else
    {
        return -1;
    }
}

int HalfSearch_Iteration(int *array,int start,int end,int key)
{
    int pivot;
    while(start<=end)
    {
        pivot=(start+end)/2;
        if(array[pivot]==key)
        {
            return pivot;
        }
        else if(array[pivot]>key)
        {
            end =pivot-1;
        }
        else
        {
            start=pivot+1;
        }
    }
    return -1;
}

int main(void)
{
    int array[]={1,1,2,3,5,8,13,21,34,55,89};
    int key=55;
    int index; 
    //index=HalfSearch_Recursion(array,0,10,key);
    index=HalfSearch_Iteration(array,0,10,key);
    if(index>=0)
    {
        printf("%d is No.%d element in array",key,index);
    }
    else{
        printf("%d is not in the array!/n",key);
    }

    return 1;
}