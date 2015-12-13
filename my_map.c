/*************************************************************************
	> File Name: my_map.c
	> Author:Eval 
	> Mail: 
	> Created Time: 2015年12月13日 星期日 12时25分48秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define MAXVEX 20
#define INFINITY 32765

typedef struct vextype
{
    int No;          //景点序号
    char name[20];   //景点名
}my_vextype;

typedef struct adjmatrix
{
    int arcs[MAXVEX][MAXVEX];  //边集
    my_vextype vex[MAXVEX];    //顶点集
    int vexnum;                //顶点数目
    int arcnum;                //边数目
    
}adjmatrix; //邻阶矩阵

//根据景点名确定景点序号
int Locate(adjmatrix *G, char name[])
{
    int i;
    for(i=1; i <= G->vexnum; i++)
    {
        if(!strcmp(name, G->vex[i].name)){
            return i;
        }
    }

    return 0;
}

//邻阶矩阵创建无向图
int create(adjmatrix *G)
{
    int i,j,k,weight;
    char city[20];
    printf("输入景点数目和路线数目:\n");
    scanf("%d,%d",&G->vexnum);
    printf("输入路线数目:\n");
    scanf("%d", &G->arcnum);

    for(i=1; i <= G->vexnum; i++) {
        for(j=1; j <= G->vexnum; j++){
            G->arcs[i][j]=INFINITY;
        }
    }
    printf("请输入景点图的%d个景点的景点名:\n",G->vexnum );
    for(i=1; i <= G->vexnum; i++)
    {
        G->vex[i].No=i;
        //flushall();
        scanf("%s", G->vex[i].name);
    }

    printf("请输入景点图的 %d 条路线:\n", G->arcnum);

    for(k=0; k<G->arcnum; k++)
    {
        printf("No.%d 条路线:", k+1);
        printf("\n起点结点:");
        scanf("%s", city); 

        i=Locate(G, city);

        printf("终点结点:");
        scanf("%s", city);

        j=Locate(G, city);

        printf("公里数:");
        scanf("%d" ,&weight);      //这里是无向图
        G->arcs[i][j]=weight;
        G->arcs[j][i]=weight;
    }

    return 1;
}

//显示图的信息
void dispaly(adjmatrix *G)
{
    int i,j;
    printf("景点情况为:\n");
    for(i=1; i <= G->vexnum; i++)
    {
        for(j=1; j <= i; j++)
        {
            if(G->arcs[i][j] != INFINITY){
                printf("%s<---->%s:%6dkm\n", G->vex[i].name, G->vex[j].name, G->arcs[i][j]);
            }
        }
    }
}

//查询某个景点的交通情况
void serach(adjmatrix *G)
{
    char city[20];
    int no, i,j;
    printf("请输入查询的景点:");
    scanf("%s", city);
    printf("该景点的交通情况为:\n");
    for(i=1; i <= G->vexnum; i++)
    {
        if(i==no){
            for(j=1; j <= G->vexnum; j++)
                printf("%s<---->%s:%6dkm\n", G->vex[no].name, G->vex[j].name, G->arcs[i][j]);
        }
        
    }
    
}

//用dijkstra算法求起点城市到终点城市的最短路径
void dijkstra(adjmatrix *G, int start, int end, int dist[], int path[][MAXVEX])
{
    int mindist, i, j,k,t=1;
    for(i=1; i <= G->vexnum; i++)
    {
        dist[i]=G->arcs[start][i];
        if( G->arcs[start][i] != INFINITY ){
            path[i][1]=start;
        }
    }
    path[start][0]=1;
    for(i=2; i <= G->vexnum; i++)
    {
        mindist=INFINITY;
        for(j=1; j<=G->vexnum; j++)
        {
            if(!path[j][0] && dist[j]<mindist)
            {
                k=j;
                mindist=dist[j];
                
            }
        }
       // if(mindist == INFINITY)   return ;
        path[k][0]=1;
        for(j=1; j<= G->vexnum; j++)
        {
            if(!path[j][0] && G->arcs[k][j]<INFINITY && dist[k]+G->arcs[k][j] < dist[j])
            {
                dist[j]=dist[k]+G->arcs[k][j];
                t=1;
                while(path[k][t] != 0)
                {
                    path[j][t]=path[k][t];
                    t++;
                }
                path[j][t]=k;
                path[j][t+1]=0;
            }
        }
    }

    for(i=1; i <= G->vexnum;i++)
    {
        if(i==end) break;
    }printf("%s<---->%s的最短路径为:cong %s", G->vex[start].name, G->vex[end].name, G->vex[start].name);
    for(i=2; path[i][j]; i++){
    printf("%s<---->%s的最短路径为:从 %s", G->vex[start].name, G->vex[end].name, G->vex[start].name);
    }
        printf("->%s, 距离为 %d km\n", G->vex[end].name, dist[i]);
}


//寻找两景点间最短连通路线
void shortcut(adjmatrix *G)
{
    char city[20];
    int start, end;
    int dist[MAXVEX],path[MAXVEX][MAXVEX]={0};
    printf("请输入起始结点:");

    scanf("%s", city);
    start=Locate(G, city);
    printf("请输入终点结点:");
    scanf("%s", city);
    end=Locate(G, city);
    dijkstra(G, start, end, dist, path);
}

int main(int argc,char *argv[])
{
    adjmatrix G;
    create(&G);
    printf("显示图的基本信息:\n");
    dispaly(&G);
    printf("查询从某个景点到另一个景点的最短路线:\n");
    shortcut(&G);
    //printf("hello, world\n");
    return 0;
}
