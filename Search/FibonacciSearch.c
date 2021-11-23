#include<stdio.h>
#include<stdlib.h>
//implement Fibonacci Search algorithm
//prerequsite the array is sorted 

int Fibonacci_generator(int);
int FibonacciSearch(int *, int,int);

int Fibonacci_generator(int index)
{
    if(index<0)
    {
        printf("wrong index of array!\n");
        exit(0);
    }
    else if(index<2)
    {
        return 1;
    }
    else
    {
        return Fibonacci_generator(index-1)+Fibonacci_generator(index-2);
    }
}
int FibonacciSearch(int *array,int length, int key)
{
    //padding the array to make its length one of the element of Fibonacci array
    int index=0;//represent the operated array's length
    int length_new;
    while(!(Fibonacci_generator(index)>=length))
    {
        index++;
    }
    length_new=Fibonacci_generator(index);
    int *array_new=(int *)malloc(sizeof(int)*length_new);
    for(int i=0;i<length_new;i++)
    {
        if(i<length)
        {
            array_new[i]=array[i];
        }
        else{
            array_new[i]=array[length-1];
        }
    }

    //fibonaci search
    int low=0,high=length_new-1,mid;
    while(1)
    {
        printf("length:%d\n",high-low+1);
        //end condition
        if(index<2)
        {
            if(low!=high)
            {
                printf("error!\n");
                exit(0);
            }

            if(array_new[low]!=key)
            {
                return -1;
            }
            else
            {
                return low;
            }
        }

        mid=low+Fibonacci_generator(index-1)-1;
        if(array_new[mid]==key)
        {
            if(mid>=length)
            {
                return length-1;
            }
            else
            {
                return mid;
            }
        }
        else if(array_new[mid]>key)
        {
            high=mid;
            index=index-1;
        }
        else
        {
            low=mid+1;
            index=index-2;
        }
    }
    return -1;
}


int main(void)
{
    int array[]={1,1,2,3,5,8,13,21,34,55,89};
    int key=1;
    int index; 
    index=FibonacciSearch(array,11,key);
    if(index>=0)
    {
        printf("%d is No.%d element in array",key,index+1);
    }
    else{
        printf("%d is not in the array!\n",key);
    }
    return 1;
}