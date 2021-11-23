#include<stdio.h>
#include<stdlib.h>
//implement dimension queens problems
int dim=8;

int conflict(int (*a)[dim],int x, int y)
{
	// horizontal
	for(int i=x,j=0;j<dim;j++)
	{
		//printf("search [%d,%d]:%d\n",i,j,a[i][j]);
		if(a[i][j]==1)
		{
			return 1;
		}
	}
	
	//vertical
	for (int i=0,j=y;i<dim;i++)
	{
		if(i==x && j==y)
		{
			continue;
		}
		//printf("search [%d,%d]:%d\n",i,j,a[i][j]);
		if(a[i][j]==1)
		{
			return 1;
		}
	}
	
	
	//right down
	for (int i=x+1,j=y+1;i<dim && j<8;i++,j++)
	{
		//printf("search [%d,%d]:%d\n",i,j,a[i][j]);
		if(a[i][j]==1)
		{
			return 1;
		}
	}
	
	//left up
	for (int i=x-1,j=y-1;i>=0 && j>=0;i--,j--)
	{
		//printf("search [%d,%d]:%d\n",i,j,a[i][j]);
		if(a[i][j]==1)
		{
			return 1;
		}
	}
	
	//right up
	for (int i=x-1,j=y+1;i>=0 && j<dim;i--,j++)
	{
		//printf("search [%d,%d]:%d\n",i,j,a[i][j]);
		if(a[i][j]==1)
		{
			return 1; 
		}
	}
	
	//left down
	for (int i=x+1,j=y-1;i<dim && j>=0;i++,j--)
	{
		//printf("search [%d,%d]:%d\n",i,j,a[i][j]);
		if(a[i][j]==1)
		{
			return 1;
		}
	}	
	return 0;
}


void print_matrix(int (*a)[dim])
{
	for (int i=0;i<dim*dim;i++)
	{
		printf("%d ",*(*a+i));
		if((i+1)%dim==0)
		{
			putchar('\n');
		}
	}
	printf("\n\n");
}


int eight_queen(int (*a)[dim], int x,int *count)
{
	for (int i=x,j=0;j<dim;j++)
	{
		if(!conflict(a,i,j))
		{
			a[i][j]=1;
			if(i==dim-1)
			{
			    (*count)++;
				printf("num:%d\n",*count);
				print_matrix(a);
				a[i][j]=0;
			}
			else
			{
				if(!eight_queen(a,i+1,count))
				{
					a[i][j]=0;
				}
		    }	
		}
		
	}
	return 0;
}



int main(void)
{
	int a[dim][dim];
	//initialize the matrix with zero!!
	for (int i=0;i<dim;i++)
	{
		for (int j=0;j<dim;j++)
		{
			a[i][j]=0;
		}
	}
	
	
	int count=0;
	eight_queen(a,0,&count);
	
	printf("there are %d results!\n",count);
	
	
	return 0;
}
