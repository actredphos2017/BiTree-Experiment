#include<stdio.h>
#include<stdlib.h>
#include <list>
#include <math.h>
using namespace std;

typedef int ElemType;

typedef struct BiNode{
    ElemType data;
    struct BiNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct SXNode{
	ElemType *data;
	int n;
}Sx;

typedef struct ExpNode{
	bool isOperator;
	union{
		ElemType num;
		char exp;
	};
	struct ExpNode *l,*r;
}ExpTNode, *ExpTree;

// 1 2 0 0 3 4 0 0 5 0 0

void CreateBiTree(BiTree &T)
{
	int ch;
	scanf("%d",&ch);
	if(ch == 0)
		T = NULL;
	else{
		T=(BiTNode*)malloc(sizeof(BiTNode));
		T->data=ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	
}
void PreOrder(BiTree T)
{
	if(T)
	{
		printf("%d",T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

void InOrder(BiTree T)
{
	if(T)
	{
		
		InOrder(T->lchild);
		printf("%d",T->data);
		InOrder(T->rchild);
	}
}

void PostOrder(BiTree T)
{
	if(T)
	{
		
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%d",T->data);
	}
}
void LevelOrder(BiTree T)
{
	if(T)
	{
		list<BiTree> l;
		l.push_front(T);
	 	while(!l.empty()){
	 		printf("%d",l.front()->data);
	 		if(l.front()->lchild)
	 			l.push_back(l.front()->lchild);
 			if(l.front()->rchild)
 				l.push_back(l.front()->rchild);
			l.pop_front();
	 	}
	}
}

void InitSx(Sx& r, BiTree T, int loc){
	if(T)
	{
		r.data[loc] = T->data;
		InitSx(r,T->lchild,loc*2);
		InitSx(r,T->rchild,loc*2+1);
	}
}


int Depth(BiTree T)
{
	int count = 0;
	if(T == NULL)
		return 0;
 	else
 	{
	 	count ++;
	    if(Depth(T->lchild) > Depth(T->rchild))
    		count = count + Depth(T->lchild);
    	else
	    	count = count + Depth(T->rchild);
    }
    return count;
}

Sx ToSxTree(BiTree T){
	Sx r;
	printf("%d\n",Depth(T));
	r.n = (int)pow(2,Depth(T))-1;
	r.data = (ElemType*)malloc(sizeof(ElemType)*(r.n+1));
	for(int i = 0; i <= r.n; i ++)
		r.data[i] = 0;
 	InitSx(r,T,1);
 	return r;
}

void SxOutput(Sx s){
	printf("%d\n",s.n);
	for(int i = 0; i < s.n; i ++)
		printf("%d",s.data[i]);
}

void CreateExpTree(ExpTree &E)
{
	
}

int main(){
	BiTree T;
	CreateBiTree(T);
	Sx s = ToSxTree(T);
	SxOutput(s);
	return 0;
}
