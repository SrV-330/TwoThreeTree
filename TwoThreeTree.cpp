#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<memory.h>
#define NUM(p) (p==NULL?0:p->num)
#define GETP(p) (p==NULL?NULL:p->parent)
#define GETR(p) (p==NULL?NULL:p->rightNode)
#define GETL(p) (p==NULL?NULL:p->leftNode)
#define GETM(p) (p==NULL?NULL:p->midNode)
#define nil NULL;
#define null NULL;

/**
*title:2-3Tree
*time:2019-3-23 11:04:04 
*author:SrV-330
*
*/
typedef struct TreeNode{
	int value[3];
	int num;
	struct TreeNode* rightNode;	
	struct TreeNode* leftNode;
	struct TreeNode* midNode;
	struct TreeNode* tmpNode;
	struct TreeNode* parent;

}tn,*ptn;

void fixup(ptn p,ptn *root);
ptn createTreeNode(int value);
void change(int* a,int* b);
ptn insertTreeNode(ptn p,ptn* rootp){
	ptn pn;
	ptn move=p;
	
	ptn movep=p;

	int value =0;
	for(fflush(stdin);scanf("%d",&value)!=1;fflush(stdin),value=0);
	if(value==-1)return null;

	ptn tr=GETR(move);
	ptn tl=GETL(move);
	ptn tm=GETM(move);
	while(!(!tr&&!tl&&!tm)){
		
		if(NUM(move)==1){
			if(value<move->value[0]){
				movep=move;
				move=move->leftNode;
			}else {
				movep=move;
				move=move->rightNode;
			}
			
		}else if(NUM(move)==2){
			if(value<move->value[0]){
				movep=move;
				move=move->leftNode;
			}else if(value>move->value[1]){
				movep=move;
				move=move->rightNode;
			}else {
				movep=move;
				move=move->midNode;
			}
			
		}
		tm=GETM(move);
		tr=GETR(move);
		tl=GETL(move);
	}
	
	if(NUM(move)==1){
		move->value[move->num]=value;
		move->num++;
		if(move->value[0]>move->value[1])
		change(&(move->value[0]),&(move->value[1]));
		fixup(move,rootp);
		return move;
	}else if(NUM(move)==2){
		move->value[move->num]=value;
		move->num++;
		if(move->value[1]>move->value[2])
		change(&(move->value[1]),&(move->value[2]));
		if(move->value[0]>move->value[1])
		change(&(move->value[0]),&(move->value[1]));
		fixup(move,rootp);
		return move;	
		
	}else{
		
		pn=createTreeNode(value);
		pn->parent=p;
		fixup(pn,rootp);
		return pn;
		
	}
	
	
	
	
}
ptn createTreeNode(int value){
	ptn pn=(ptn)malloc(sizeof(tn));
	pn->num=0;
	pn->value[pn->num]=value;
	pn->num++;
	pn->leftNode=null;
	pn->rightNode=null;
	pn->midNode=null;
	pn->tmpNode=null;
	pn->parent=null;
	return pn;
}
void printTree(ptn root,int deep){
	if(NUM(root)==0) return;
	deep++;
	printTree(root->rightNode,deep);
	
	for(int i=(root->num)-1;i>=0;i--){
		for(int j=0;j<deep;j++){
			printf(" ");
		}
		printf("%d\n",root->value[i]);
		
	}
	
	printTree(root->midNode,deep);
	printTree(root->leftNode,deep);
	
	
}
void change(int *a,int *b){
	int t=(*a);
	(*a)=(*b);
	(*b)=t;
}
void fixup(ptn p,ptn *root){
	ptn move=p;
	ptn movep=GETP(p);
	if(!p) return;
	if(NUM(move)==3&&!movep){//root node
		ptn b=createTreeNode(move->value[1]);
		ptn c=createTreeNode(move->value[2]);
		move->num=1;
		b->leftNode=move;
		b->rightNode=c;
		move->parent=b;
		c->parent=b;
		
		c->rightNode=move->rightNode;
		c->leftNode=move->tmpNode;
		move->rightNode=move->midNode;
		move->midNode=null;
		move->tmpNode=null;
		
		(*root)=b;
		
		
			
	}else if(NUM(move)==3&&NUM(movep)==1&&GETL(movep)==move){
		movep->value[movep->num]=move->value[1];
		(movep->num)++;
		change(&(movep->value[0]),&(movep->value[1]));
		ptn c=createTreeNode(move->value[2]);
		c->parent=movep;
		movep->midNode=c;
		move->num=1;
		
		c->rightNode=move->rightNode;
		move->rightNode=move->midNode;
		
		c->leftNode=move->tmpNode;
		move->tmpNode=null;
		move->midNode=null;
		
		
		
	}else if(NUM(move)==3&&NUM(movep)==1&&GETR(movep)==move){
		
		movep->value[movep->num]=move->value[1];
		movep->num++;
		
		ptn d=createTreeNode(move->value[2]);
		d->parent=movep;
		movep->rightNode=d;
		move->num=1;
		movep->midNode=move;
		
		d->rightNode=move->rightNode;
		move->rightNode=move->midNode;
		d->leftNode=move->tmpNode;
		move->tmpNode=null;
		move->midNode=null;
		
		
		
	}else if(NUM(move)==3&&NUM(movep)==2&&GETL(movep)==move){
		
		movep->value[movep->num]=move->value[1];
		movep->num++;
		change(&(movep->value[0]),&(movep->value[2]));
		change(&(movep->value[1]),&(movep->value[2]));
		ptn c=createTreeNode(move->value[2]);
		c->parent=movep;
		movep->midNode=c;
		move->num=1;
		
		c->rightNode=move->rightNode;
		move->rightNode=move->midNode;
		c->leftNode=move->tmpNode;
		move->midNode=null;
		move->tmpNode=null;
		
		fixup(movep,root);
	}else if(NUM(move)==3&&NUM(movep)==2&&GETM(movep)==move){
		
		movep->value[movep->num]=move->value[1];
		movep->num++;
		change(&(movep->value[1]),&(movep->value[2]));
		ptn d=createTreeNode(move->value[2]);
		d->parent=movep;
		movep->tmpNode=d;
		move->num=1;
		
		
		d->rightNode=move->rightNode;
		move->rightNode=move->midNode;
		d->leftNode=move->tmpNode;
		move->midNode=null;
		move->tmpNode=null;
		
		fixup(movep,root);
	}else if(NUM(move)==3&&NUM(movep)==2&&GETR(movep)==move){
		movep->value[movep->num]=move->value[1];
		movep->num++;
		change(&(movep->value[1]),&(movep->value[2]));
		ptn c=createTreeNode(move->value[2]);
		c->parent=movep;
		movep->tmpNode=c;
		move->num=1;
		
		
		c->leftNode=move->leftNode;
		move->leftNode=move->tmpNode;
		c->rightNode=move->midNode;
		move->midNode=null;
		move->tmpNode=null;
		
		fixup(movep,root);
		
	}else{
		return;
	}
	
}

void dropTree(ptn root){
	if(!root) return;
	if(root->leftNode){
		free(root->leftNode);
	}
	if(root->rightNode){
		free(root->rightNode);
	}
	if(root->midNode){
		
		free(root->midNode);
	}
	if(root->tmpNode){
		free(root->tmpNode);
	}
	free(root);
	root=null;
}
main(){
	
	ptn root=null;
	ptn* rootp=null; 
	ptn node=null;
	
	node=insertTreeNode(root,rootp);
	root=node;
	rootp=&root;
	do{
		node=insertTreeNode(root,rootp);	
	}while(node!=NULL);
	
	printTree(root,0);
	dropTree(root);
	
	
	
}