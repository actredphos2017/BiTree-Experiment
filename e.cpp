
typedef char ElemType;
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree Create();/* 细节在此不表 */
void Prefix(BiTree T);

int main()
{
    BiTree T = Create();
    Prefix(T);
    return 0;
}
/* 你的代码将被嵌在这里 */
#include <stdio.h>

void Prefix(BiTree T){
    if(!T)
        return;
    printf("%c ",T->data);
    Prefix(T->lchild);
    Prefix(T->rchild);
}
void Infix(BiTree T){
    if(!T)
        return;
    Infix(T->lchild);
    printf("%c ",T->data);
    Infix(T->rchild);
}

void Suffix(BiTree T){
    if(!T)
        return;
    Suffix(T->lchild);
    Suffix(T->rchild);
    printf("%c ",T->data);
}