#include<stdlib.h>
#include<stdio.h>
#define INFINITY 65535

//define graph structure
typedef struct 
{
    int key;
}Vertex;

typedef struct
{
    int *adjacent;
    Vertex *vertex;
    int length;
}Graph;

//init graph
void init_graph(Graph *graph)
{
    graph->length=4;
    graph->vertex=(Vertex *)malloc(sizeof(Vertex)*graph->length);
    graph->adjacent=(int *)malloc(sizeof(int)*graph->length*graph->length);

    //init vertex
    for(int i=0;i<graph->length;i++)
    {
        graph->vertex[i].key=i+1;
    }
    for(int i=0;i<graph->length;i++)
    {
        for(int j=0;j<graph->length;j++)
        {
            if(i==j)
            {
                graph->adjacent[i*graph->length+j]=0;
            }
            else
            {
                graph->adjacent[i*graph->length+j]=INFINITY;
            }
        }
    }

    //init adjacent matrix
    /*
    graph->adjacent[0*graph->length+1]=10;
    graph->adjacent[0*graph->length+5]=3;
    graph->adjacent[1*graph->length+2]=7;
    graph->adjacent[1*graph->length+3]=5;
    graph->adjacent[3*graph->length+0]=3;
    graph->adjacent[3*graph->length+2]=4;
    graph->adjacent[3*graph->length+4]=7;
    graph->adjacent[5*graph->length+1]=2;
    graph->adjacent[5*graph->length+3]=6;
    graph->adjacent[5*graph->length+4]=1;
    */
    graph->adjacent[0*graph->length+2]=1;
    graph->adjacent[1*graph->length+0]=1;
    graph->adjacent[1*graph->length+3]=1;
    graph->adjacent[2*graph->length+1]=1;
    graph->adjacent[3*graph->length+2]=1;
}

//Time complexity O(V^2)
//space complexity O(1)
void ShortestPath_Dijistra(Graph *graph, int start_index)
{
    int *flag=(int *)malloc(sizeof(int)*graph->length);
    int *weight=(int *)malloc(sizeof(int)*graph->length);
    int *path=(int *)malloc(sizeof(int)*graph->length);

    //init the above three array
    for(int i=0;i<graph->length;i++)
    {
        flag[i]=0;
        weight[i]=graph->adjacent[start_index*graph->length+i];
        path[i]=start_index;
    }
    flag[start_index]=1;

    int min,index;
    //core part
    for(int time=0;time<graph->length-1;time++)
    {
        min=INFINITY;
        index=-1;
        //find the smallest path in the not found vertex
        for(int i=0;i<graph->length;i++)
        {
            if(flag[i]!=1 && weight[i]<min)
            {
                min=weight[i];
                index=i;
            }
        }
        //assign the path to smallest path
        flag[index]=1;
        //adjust the shorest path
        for(int i=0;i<graph->length;i++)
        {
            if(flag[i]!=1 && weight[i]>(weight[index]+graph->adjacent[index*graph->length+i]))
            {
                weight[i]=weight[index]+graph->adjacent[index*graph->length+i];
                path[i]=index;
            }
        }
    }

    //show the result
    printf("flag:");
    for(int i=0;i<graph->length;i++)
    {
        printf("%d, ",flag[i]);
    }
    printf("\nweight:");
    for(int i=0;i<graph->length;i++)
    {
        printf("%d, ",weight[i]);
    }
    printf("\npath:");
    for(int i=0;i<graph->length;i++)
    {
        printf("%d, ",path[i]);
    }
}

//Time complexity O(N)=O(V(V+E))
//Space Complexity TODO
//may face dead lock when there exits cyclic graph
int ShortestPath_MemoizedDP(Graph *graph, int start, int end, int *flag, int *weight, int *path)
{
    if(flag[end]!=0)
    {
        return weight[end];
    }
    printf("%d->%d\n",start+1,end+1);
    if(start==end)
    {
        flag[end]=1;
        weight[end]=0;
        path[end]=start;
        return weight[end];
    }

    int min=INFINITY,index=-1,temp;
    //tranverse the indegree of the end vertex
    //choose the best one 
    for(int i=0;i<graph->length;i++)
    {
        if(graph->adjacent[i*graph->length+end]!=INFINITY && i!=end)
        {
            temp=ShortestPath_MemoizedDP(graph,start,i,flag,weight,path)+graph->adjacent[i*graph->length+end];
            //printf("%d->%d->%d:%d\n",start+1,i+1,end+1,temp);
            if(temp<min)
            {
                min=temp;
                index=i;
            }
        }
    }
    weight[end]=min;
    path[end]=index;
    flag[end]=1;
    //printf("final:%d->%d: %d->%d->%d:%d\n",start+1,end+1,start+1,path[end]+1,end+1,weight[end]);
    return weight[end];
}

void ShortestPath_Memoized_Wrapper(Graph *graph, int start)
{
    int *flag=(int *)malloc(sizeof(int)*graph->length);
    int *weight=(int *)malloc(sizeof(int)*graph->length);
    int *path=(int *)malloc(sizeof(int)*graph->length);

    //init the above three array
    for(int i=0;i<graph->length;i++)
    {
        flag[i]=0;
    }

    for(int i=0;i<graph->length;i++)
    {
        ShortestPath_MemoizedDP(graph,start,i,flag,weight,path);
    }

    //show result
    printf("flag:");
    for(int i=0;i<graph->length;i++)
    {
        printf("%d, ",flag[i]);
    }
    printf("\nweight:");
    for(int i=0;i<graph->length;i++)
    {
        printf("%d, ",weight[i]);
    }
    printf("\npath:");
    for(int i=0;i<graph->length;i++)
    {
        printf("%d, ",path[i]);
    }


}

//Version to deal with cyclic graph
int ShortestPath_MemoizedDP_improved(Graph *graph,int start, int end, int *flag, int *weight, int *path, int maximum_steps)
{
    if(flag[maximum_steps*graph->length+end]==1)
    {
        return weight[maximum_steps*graph->length+end];
    }

    if(start==end)
    {
        weight[maximum_steps*graph->length+end]=0;
        path[maximum_steps*graph->length+end]=start;
        flag[maximum_steps*graph->length+end]=1;
        return weight[maximum_steps*graph->length+end];
    }

    if(maximum_steps==0)
    {
        weight[maximum_steps*graph->length+end]=INFINITY;
        path[maximum_steps*graph->length+end]=-1;
        flag[maximum_steps*graph->length+end]=1;
        return weight[maximum_steps*graph->length+end];
    }
    printf("%d->%d(in %d steps)\n",start+1,end+1,maximum_steps);
    int index=-1,mini=INFINITY,temp;
    for(int i=0;i<graph->length;i++)
    {
        if(graph->adjacent[i*graph->length+end]!=INFINITY)
        {
            temp=ShortestPath_MemoizedDP_improved(graph,start,i,flag,weight,path,maximum_steps-1)+graph->adjacent[i*graph->length+end];
            printf("%d->%d->%d(in %d steps):%d\n",start+1,i+1,end+1,maximum_steps,temp);
            if(temp<mini)
            {
                mini=temp;
                index=i;
            }
        }
    }
    flag[maximum_steps*graph->length+end]=1;
    weight[maximum_steps*graph->length+end]=mini;
    path[maximum_steps*graph->length+end]=index;
    return weight[maximum_steps*graph->length+end];
}

void ShortestPath_MemoizeDP_improved_wrapper(Graph *graph, int start)
{
    int *flag=(int *)malloc(sizeof(int)*graph->length*graph->length);
    int *weight=(int *)malloc(sizeof(int)*graph->length*graph->length);
    int *path=(int *)malloc(sizeof(int)*graph->length*graph->length);
    
    //init flags
    for(int i=0;i<graph->length;i++)
    {
        for(int j=0;j<graph->length;j++)
        {
            flag[i*graph->length+j]=0;
        }
    }

    for(int end=0;end<graph->length;end++)
    {
        ShortestPath_MemoizedDP_improved(graph,start,end,flag,weight,path,graph->length-1);
    }

    //show result
    printf("(horizontal:vertex index //vertical: minimal steps)\nflags:\n");
    for(int i=0;i<graph->length;i++)
    {
        for(int j=0;j<graph->length;j++)
        {
            printf("%d  ",flag[i*graph->length+j]);
        }
        printf("\n");
    } 
    printf("\nweight:\n");
    for(int i=0;i<graph->length;i++)
    {
        for(int j=0;j<graph->length;j++)
        {
            if(weight[i*graph->length+j]>=INFINITY)
            {
                printf("N  ");
            }
            else
            {
                printf("%d  ",weight[i*graph->length+j]);
            }
        }
        printf("\n");
    } 
    printf("\npath:\n");
    for(int i=0;i<graph->length;i++)
    {
        for(int j=0;j<graph->length;j++)
        {
            printf("%d  ",path[i*graph->length+j]);
        }
        printf("\n");
    } 
}

//Version to deal with cyclic graph
int ShortestPath_MemoizedDP_improved_Iterations(Graph *graph,int start)
{
    int *weight=(int *)malloc(sizeof(int)*graph->length*graph->length);
    int *path=(int *)malloc(sizeof(int)*graph->length*graph->length);

    //initiate weight and path when steps=0
    for(int end=0;end<graph->length;end++)
    {
        if(end==start)
        {
            path[0*graph->length+end]=start;
            weight[0*graph->length+end]=0;
        }
        else
        {
            path[0*graph->length+end]=-1;
            weight[0*graph->length+end]=INFINITY;
        }
    }
    //core part
    int temp,mini,index;
    for(int steps=1;steps<=graph->length-1;steps++)
    {
        for(int end=0;end<graph->length;end++)
        {
            index=-1;
            mini=INFINITY;
            for(int u=0;u<graph->length;u++)
            {
                temp=weight[(steps-1)*graph->length+u]+graph->adjacent[u*graph->length+end];
                if(temp<mini)
                {
                    mini=temp;
                    index=u;
                }
            }
            weight[steps*graph->length+end]=mini;
            if(index==end)
            {
                path[steps*graph->length+end]=path[(steps-1)*graph->length+end];
            }
            else
            {
                path[steps*graph->length+end]=index;
            }
        }
    }
    //show result:
    printf("\nweight:\n");
    for(int i=0;i<graph->length;i++)
    {
        for(int j=0;j<graph->length;j++)
        {
            if(weight[i*graph->length+j]>=INFINITY)
            {
                printf("N  ");
            }
            else
            {
                printf("%d  ",weight[i*graph->length+j]);
            }
        }
        printf("\n");
    } 
    printf("\npath:\n");
    for(int i=0;i<graph->length;i++)
    {
        for(int j=0;j<graph->length;j++)
        {
            printf("%d  ",path[i*graph->length+j]);
        }
        printf("\n");
    } 
}

int main(void)
{
    Graph graph;
    init_graph(&graph);
    //ShortestPath_Dijistra(&graph,0);
    //ShortestPath_Wrapper(&graph, 0);
    //ShortestPath_MemoizeDP_improved_wrapper(&graph,0);
    ShortestPath_MemoizedDP_improved_Iterations(&graph,0);
    return 1;
}