
#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree Create();/* 细节在此不表 */

int Depth(BiTree T);

int main()
{
    BiTree T = Create();

    printf("%d\n", Depth(T));
    return 0;
}
/* 你的代码将被嵌在这里 */
int Depth(BiTree T){
    if(T==NULL)
        return 0;
    int ldepth = Depth(T->lchild);
    int rdepth = Depth(T->rchild);
    return ldepth>rdepth?ldepth+1:rdepth+1;
}