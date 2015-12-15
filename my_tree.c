/*************************************************************************
	> File Name: my_tree.c
	> Author:Eval 
	> Mail: 
	> Created Time: 2015年11月27日 星期五 16时06分50秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define FALSE 0
#define TRUE 1

typedef struct Datatype
{
    int x;
}Datatype;

//data structure of Tree_node
typedef struct Node
{
    //Datatype data;

    int data;
    struct Node *Lchild;
    struct Node *Rchild;
}BITNode;

//linked Stacks structure
typedef struct my_stack
{
    BITNode *T;
    struct my_stack *next;
}my_stack;


//Postorder Traversal delete node
void my_free(BITNode *root)
{
    if(root != NULL)
    {
        my_free(root->Lchild);
        my_free(root->Rchild);
        free(root);
    }
}   

//Recursive create  binary tree
void create_bittree(BITNode** root)
{
    int i;
    printf("input:");
    scanf("%d", &i);
    if(i == 0)
    {
        *root = NULL;
    }
    else
    {
        *root = (BITNode *)malloc(sizeof(BITNode));
        (*root)->data = i;

        create_bittree(&( (*root)->Lchild));
        create_bittree(&( (*root)->Rchild));
    }

}

//Visit my tree
void my_visit(BITNode *p)
{
    printf("%d\n", p->data);
}

//My preorder Traversal
void my_preorder(BITNode *root)
{
    if(root != NULL)
    {
        my_visit(root);
        my_preorder(root->Lchild);
        my_preorder(root->Rchild);
    }
}

//my_stack init
my_stack * init_stack()
{
    my_stack *s;

    if((s=(my_stack *)malloc(sizeof(my_stack))) == NULL)
    {

        printf("malloc error\n");
        exit(-1);
    }
    s->next = NULL;
    s->T = NULL;

    return s;
}
//Contracting_Stack
int empty_stack(my_stack *s)
{
    if(s->next == NULL)
        return FALSE;   return TRUE;
}

//Take_top_Node
int my_get_top(my_stack *head,BITNode **p)
{
    if(head->next == NULL)
    {
        return FALSE;
    }

    *p=(head->next)->T;
    return TRUE;
}

//my_push_stack
int my_push(my_stack *head, BITNode *p)
{
    my_stack *s=NULL;
    if((s=(my_stack *)malloc(sizeof(my_stack))) == NULL)
        return FALSE;
    s->T = p;
    s->next=head->next;
    head->next=s;
    return TRUE;   
}

//my_pop_stack
int my_pop(my_stack *head, BITNode **p)
{
    my_stack *s=NULL;
    if(head->next == NULL)
        return FALSE;
    s=head->next;
    head->next=s->next;
    *p=s->T;
    free(s);
    return TRUE;
}
// My unR_preorder Traversal
void preorder_traval(BITNode *root)
{
    my_stack *S;
    BITNode *p;
    S=init_stack();
    p=root;
    
    while(p != NULL || empty_stack(S) )
    {
        while(p != NULL)
        {
            my_visit(p);
            my_push(S, p);
            p=p->Lchild;
        }
        if(empty_stack(S))
        {
            my_pop(S, &p);
            p=p->Rchild;
        }
    }
}
int main(void)
{
    BITNode *s;
    create_bittree(&s);
    preorder_traval(s);
    //my_preorder(s);
    my_free(s);
    my_preorder(s);
    return 0;
}

