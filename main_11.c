#include<stdio.h>
#include<stdlib.h>
int step[600000]={0};
typedef struct Node{
	int data;
	int edge_num;
	int distance;
	int xor;
	struct Node *next;
	struct Node *foot[50];
}node ;
node *leave[51],*head;
node *init_node(int event){
	node *tmp=(node *)malloc(sizeof(node));
	tmp->data=event;
	tmp->next=NULL;
	tmp->edge_num=0;
	return tmp;
}
void make_graph(int num){
	for(int i = 0; i < num; i++)leave[i]->foot[leave[i]->edge_num++]=leave[num];
}
int bfs(int i){
	head=leave[i];
	head->xor=leave[i]->data;
	head->distance=0;
	while(head!=NULL){
		node *u=head;
		head=head->next;
		for(int i = 0; i < u->edge_num; i++){
			node *v=u->foot[i];
			v->distance=u->distance+1;
			v->xor=u->xor^v->data;
			if(!step[v->xor] || step[v->xor]&&v->distance+1<step[v->xor]){
				step[v->xor]=v->distance+1;
				v->next=head;
				head=v;
			}
		}
	}	
}
int main(){
	int n,m;
	scanf("%d",&n);
	int event,time,s=0;
	for(int i = 0; i < n; i++){
		scanf("%d",&event);//,&time);
		/*if(!time){
			s++;
			continue;
		}*/step[event]=1;
		leave[i]=init_node(event);
		make_graph(i-s);
	}step[0]=0;
	for(int i = 0; i < n; i++)bfs(i);
	for(int i = 0; i < 30; i++)
		printf("%d ",step[i]);
	printf("\n");
	/*
	scanf("%d",&m);
	for(int i = 0; i < m; i++){
		int now,target,find;
		scanf("%d%d",&now,&target);
		find=now^target;
		if(now==target)printf("0\n");
		else !step[find]? printf("UNREACHABLE\n"):printf("%d\n",step[find]);
	}*/
}