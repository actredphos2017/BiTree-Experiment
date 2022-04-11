#include<iostream>
using namespace std;
typedef struct BiNode{
    char data;
    struct BiNode *lchild,*rchild;
}BiTNode,*BiTree;

void CreateBiTree(BiTree &T);//根据输入的字符串，创建二叉树。 
void PreOrder(BiTree T);//先序遍历二叉树 
void InOrder(BiTree T);//中序遍历二叉树 
void PostOrder(BiTree T);//后序遍历二叉树 
void LevelOrder(BiTree T);//层次遍历二叉树  

int main(){
 BiTree T;
 CreateBiTree(T);
 cout<<"PreOrder:"; 
 PreOrder(T);
 cout<<endl<<"InOrder:";
 InOrder(T);
 cout<<endl<<"PostOrder:";
 PostOrder(T);
 cout<<endl<<"LevelOrder:";
 LevelOrder(T);
 return 0;
} 
/* 请在这里填写答案 */
void CreateBiTree(BiTree &T){
    char ch;
    cin>>ch;
    if(ch=='#'){
        T=NULL;
    }else{
        T=(BiTree)malloc(sizeof(BiTNode));
        T->data=ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void PreOrder(BiTree T){
    if(T==NULL)
        return;
    cout<<T->data;
    PreOrder(T->lchild);
    PreOrder(T->rchild);
}

void InOrder(BiTree T){
    if(T==NULL)
        return;
    InOrder(T->lchild);
    cout<<T->data;
    InOrder(T->rchild);
}
void PostOrder(BiTree T){
    if(T==NULL)
        return;
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    cout<<T->data;
}

#if 1
#include <vector>
void LevelOrder(BiTree T){
    if(!T)
        return;
    vector<BiTree> vec;
    vec.push_back(T);
    while(!vec.empty()){
        cout<<vec.front()->data;
        if(vec.front()->lchild)
            vec.push_back(vec.front()->lchild);
        if(vec.front()->rchild)
            vec.push_back(vec.front()->rchild);
        for(int i = 0; i < vec.size(); i++)
            vec[i] = vec[i+1];
        vec.pop_back();
    }
}

#elif 0
#include <list>
void LevelOrder(BiTree T){
    if(!T)
        return;
    list<BiTree> l = {T};
    while(!l.empty()){
        cout<<p->data<<" ";
        if(l.front()->lchild)
            l.push_back(l.front()->lchild);
        if(l.front()->rchild)
            l.push_back(l.front()->rchild);
        l.pop_front();
    }
}

#else
#include <queue>
void LevelOrder(BiTree T){
    if(T==NULL)
        return;
    queue<BiTree> q;
    q.push(T);
    while(!q.empty()){
        BiTree p=q.front();
        cout<<p->data<<" ";
        q.pop();
        if(p->lchild!=NULL)
            q.push(p->lchild);
        if(p->rchild!=NULL)
            q.push(p->rchild);
    }
}
#endif