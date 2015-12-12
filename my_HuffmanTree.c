/*************************************************************************
	> File Name: my_HuffmanTree.c
	> Author:Eval 
	> Mail: 
	> Created Time: 2015年12月07日 星期一 13时25分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 30                //叶子结点最大个数 
#define M 2*N-1
typedef struct my_tree
{
    int weight;
    int parent, Lchild, Rchild;
    char ch;
}HuffmanTree;

typedef struct Decod
{
    int c;     //译码的字符
    int w;     //译码字符的权值
}Decod;


void my_select(HuffmanTree *ht, int n, int *s1, int *s2);                 
void create_HuffmanTree(HuffmanTree *ht, int w[], int n, char *s);           //create_HuffmanTree
void Huffmancode(HuffmanTree *ht, char *hc[M], int n);                       //HuffmanTree

int input_and_sort(char *S, int *a);                                         //input
void my_t(char *s, Decod *a, HuffmanTree *ht);                               //translate

void my_code(HuffmanTree *ht,int *a, char *hc[30], char *S);                 //Y
void my_code(HuffmanTree *ht,int *a, char *hc[30], char *S);                 //B


//选择权值最小的两个结点de xia biao
void my_select(HuffmanTree *ht, int n, int *s1, int *s2)
{
    int i, m=1;                  //m 临时保存最小值下标

    int min;
    int min1;

    //找s1的初始值
    for(i=1; i<=n && ht[i].parent; i++);
    *s1=i;
    m=i;
    min=ht[i].weight;

    //确定s1的值
    for(i=1; i <= n; i++)
    {
        //该结点必须没有建立过 
        if( ht[i].parent == 0 &&  min > ht[i].weight) {

            min = ht[i].weight;
            m=i;
            *s1 = i;
        }
    }

    //找s2初始值
    for(i=1; i <= n; i++){
        if( i != m && ht[i].parent == 0){
            min1=ht[i].weight;
            *s2 = i;
            break;
        }
    }

    //确定 s2
    for(i=1; i <= n; i++)
    {
        if(i != m && ht[i].parent ==0 && min1 > ht[i].weight) {
            min1 = ht[i].weight;
            *s2 = i;
        }
    }
}

//create my_Huffman Tree
void create_HuffmanTree(HuffmanTree *ht, int w[], int n, char *s)
{
    int i;
    int m = 2*n-1;
    int s1, s2;                        //临时保存下标
    for(i=1; i <= n; i++){

        ht[i].weight=w[i];
        ht[i].ch=s[i];
        ht[i].parent=0;
        ht[i].Lchild=0;
        ht[i].Rchild=0;
    }                                  //初始化前n个元素
    for(i=n+1; i <= m; i++){
        
        ht[i].weight=0;
        ht[i].parent=0;
        ht[i].Lchild=0;
        ht[i].Rchild=0;
    }                                 //初始化元素为空，构造二叉树根节点
    for(i=n+1; i <= m; i++)
    {
        my_select(ht, i-1, &s1, &s2);
        ht[i].weight=ht[s1].weight + ht[s2].weight;   //建新节点赋权值
        ht[i].Lchild=s1;
        ht[i].Rchild=s2;

        ht[s1].parent=i;
        ht[s2].parent=i;
    }
}

void Huffmancode(HuffmanTree *ht, char *hc[M], int n)
{
    char *cd;
    int c, p;                               //临时变量保存当前节点和双亲节点
    int start, i;
    cd=(char *)malloc(n*sizeof(char));      //编码个数大小不会超过n
    cd[n-1]='\0';

    for(i=1; i <= n; i++)
    {
        start=n-1;
        c=i;                               //c 为当前节点，p为双亲节点
        p=ht[i].parent;

        while(p != 0)
        {
         --start;
            if(ht[p].Lchild == c){
                cd[start]='0';             //左分支为 0
             }else{
                cd[start]='1';             //右分支为 1
             }
            
            c=p;
            p=ht[p].parent;                //上溯一层
         }
        hc[i]=(char *)malloc((n-start+1)*sizeof(char));     //动态申请编码空间
        strcpy(hc[i], &cd[start]);
    }
}

//输入编码字符串并按顺序把每个字符出现的频率存入a
int input_and_sort(char *S, int *a)
{
    char array[M];               //
    int i, j=1;
    int cout[27];                //英文数字只有26个 保存每个出现的字符的个数

    for(i=1; i<27; i++){
        cout[i]=0;
    }

    printf("input:\n");
    scanf("%s", array);

    //i 从1开始计数
    for(i=1; i <= (strlen(array)); i++){
        cout[array[i-1]-96]++;
    }

    //S 保存a-z中出现过得字符，cout 保存每个字符的个数
    for(i=1; i <= 26; i++){
        if(cout[i] != 0){
            S[j]=i+96;
            a[j++]=cout[i];
        }
    }

    return (j-1);
}

//我的译码函数 s 保存未翻译的01 串，a 存翻译好的译码字符和每个字符权值
void my_t(char *s, Decod *a, HuffmanTree *ht)
{
    HuffmanTree p;
    HuffmanTree root;   //bao cun shu de genjiedian
    int i=0;
    int k = 0;          //k 保存译码下标

    //xian cong di yige wei zhi de jiedian bian li dao gen
    p=ht[1];

    while(p.parent){
        p=ht[p.parent];
    }
    root = p;
    //zhao ge yezi jiedian jilu qi zifu he quanzhi
    while(i<strlen(s)){
        p=root;
        while(p.Lchild != 0){
            if(s[i] == '0'){
                p=ht[p.Lchild];
            }else if(s[i] == '1'){
                p=ht[p.Rchild];
            }

            i++;
        } 

        a[k].c=p.ch;
        a[k++].w=p.weight;
    }
    a[k].c='\0';
}

//B
void my_code(HuffmanTree *ht,int *a, char *hc[30], char *S)
{
    int i,n;

    n=input_and_sort(S, a);           //输入并统计权值       
    create_HuffmanTree(ht, a, n,S);   //创建哈夫曼树
    Huffmancode(ht, hc, n);           //哈夫曼编码

    //输出哈夫曼编码
    printf("编码是:\n\n");
    for(i=1; i <= n; i++){
        printf("%c:", S[i]);
        printf("%s\n", hc[i]);
    }
}

//Y
void my_dec(HuffmanTree* ht, char *t, Decod *array, char *my_decod)
{
    int i,j;
    printf("输入要翻译的01字符串:\n");
    scanf("%s",t);

    int k=0;
    my_t(t, array, ht);      //译码

    //解析译码得到的字符整合成有用信息
    for(i=0; array[i].c; i++){
        for(j=0; j<array[i].w; j++){
            my_decod[k++]=array[i].c;
        }
    }
    my_decod[k]='\0';
    printf("yima is:%s",my_decod);
}

int main(int argc,char *argv[])
{
    HuffmanTree ht[N];

    //编码需要的变量
    int a[N];                      //用于在编码时保存每个出现的字符的权值
    char *hc[30];                  //数组指针，每一个指针代表一串编码，用于编码时叶子字符的编码
    char S[27];                    //用于编码时，保存输入的a-z中每个出现的字符，最多有26个

    //译码需要的变量
    char t[M];                        //用于译码时保存翻译之前的01字符串
    Decod array[M];                   //保存 初步翻译出来的a-z中出现过的字符及其频率
    char my_decod[N*M];               //用于译码时，保存最终要输出的译码字符串

    my_code(ht,a, hc, S);
    my_dec(ht,t, array, my_decod);
    return 0;
}

