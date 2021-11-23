#include<stdio.h>
/*
implement Interpolation search 
prerequisite : the array is sorted in ascending order
Conditions for good performance of algorithm:
1:The length of the array is very long
2:The element of the array increase linearly or steadily as the index increase. 1->2->3-...
under the above condition Interpolation search is better than half search. However, if the array increase extremely it performs worse tha that of halfsearch
*/
typedef int Elemtype;

int InterpolationSearch(Elemtype *array, Elemtype length,Elemtype key)
{
    int start=0,end=length-1,pivot;
    while(start<=end)
    {
        if(array[start]!=array[end])
        {
            pivot=start+(end-start)*(key-array[start])/(array[end]-array[start]); //part different from half search TODO divide by zero
        }
        else{
            pivot=(start+end)/2;
        }
        // there may occurs over bound problem
        if(pivot<start)
        {
            pivot=start;
        }
        if(pivot>end)
        {
            pivot =end;
        }

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
    int array[]={3,5,7,9,10};
    int key=8;
    int index; 
    index=InterpolationSearch(array,5,key);
    if(index>=0)
    {
        printf("%d is No.%d element in array",key,index);
    }
    else{
        printf("%d is not in the array!\n",key);
    }

    return 1;
}