/*************************************************************************
	> File Name: my_and.c
	> Author:Eval 
	> Mail: 
	> Created Time: 2015年12月09日 星期三 16时20分34秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 3                                //hang xiao biao
#define M 4                                //lie xia biao

#define TRUE 1
#define FALSE 0

typedef struct node
{
    int i;    //andian hengzuobiao
    int j;    //andian liezuobiao
    int n;    //andian zhi
}Node;

int my_check(int a[N][M], Node *cout)
{
    int i,j,k,m;        //m bao cun hang zuixiao yuansu de lie

    int min, max;
    for(i=0; i < N; i++){

        min=a[i][0];
        m=0;

        for(j=0; j < M ; j++){
            if(min > a[i][j]){
                min = a[i][j];
                m=j;
            }
        }

        max=a[i][m];                          //cong hang zuixiao delie zhao lie zuida
        for(k=0; k < N && max >= a[k][m]; k++);    //kong xunhuan pan duan shi bu shi lie zui da
        
        //ru guo shi andian
        if(k==N){
            (*cout).i=i;(*cout).j=m;
            (*cout).n=max;

            return TRUE;                        //an dian zhiyou yige
        }
    }

    return FALSE;
}


int main(int argc,char *argv[])
{
    int a[N][M];                     //juzhen
    int i, j;
    Node cout={0,0,0};
    printf("input:\n");
    for(i=0; i<N; i++){
        for(j=0; j<M; j++){
            scanf("%d", &a[i][j]);
        }
    }
    if( my_check(a, &cout) ){

        printf("andian wei:A[%d][%d]=%d\n",cout.i, cout.j, cout.n);  
    }else{
        printf("mei you andian\n");
    }

    return 0;
}
