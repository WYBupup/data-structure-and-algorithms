#include<stdio.h>

void show_array(int *array, int length)
{
    for(int i=0;i<length;i++)
    {
        printf("%d ",array[i]);
    }
}

void swap(int *array, int i, int j)
{
    int temp;
    temp=array[i];
    array[i]=array[j];
    array[j]=temp;
}

void QuickSort(int *array, int length)
{
    if(length<=1)
    {
        return;
    }

    int low=0,high=length-1;
    int reference=array[low];//under optimization

    while(low<high)
    {
        while(low<high && array[high]>=reference)
        {
            high--;
        }
        swap(array,low,high);//under optimization

        while(low<high && array[low]<=reference)
        {
            low++;
        }
        swap(array,low,high);//under optimization
    }
    //under optimization
    QuickSort(array,low);
    QuickSort(array+low+1,length-low-1);
}

void QuickSort_optimized(int *array, int length)
{
    if(length<=1)
    {
        return;
    }

    int low=0,high=length-1;
    int mid=(low+high)/2;
    //optimize the choice of reference
    if(array[low]>array[high])
    {
        swap(array,low,high);
    }
    if(array[mid]>array[high])
    {
        swap(array,mid,high);
    }
    if(array[low]<array[mid])
    {
        swap(array,mid,low);
    }
    int reference=array[low];

    while(low<high)
    {
        while(low<high && array[high]>=reference)
        {
            high--;
        }
        array[low]=array[high];//under optimization

        while(low<high && array[low]<=reference)
        {
            low++;
        }
        array[high]=array[low];//under optimization
    }
    array[low]=reference;
    //under optimization
    QuickSort(array,low);
    QuickSort(array+low+1,length-low-1);
}


int main(void)
{
    int array[]={592,401,874,141,348,72,911,887,820,283,0,7,66,592};

    show_array(array,14);
    printf("\n");

    QuickSort_optimized(array,14);

    show_array(array,14);
    printf("\n");

    return 1;
}