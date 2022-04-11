#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

BiTree Create();/* 细节在此不表 */

int LeafCount ( BiTree T);

int main()
{
    BiTree T = Create();
    
    printf("%d\n", LeafCount(T));
    return 0;
}
/* 你的代码将被嵌在这里 */
int LeafCount ( BiTree T){
    if(T==NULL)
        return 0;
    if(T->lchild==NULL && T->rchild==NULL)
        return 1;
    return LeafCount(T->lchild)+LeafCount(T->rchild);
}