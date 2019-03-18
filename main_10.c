#include<stdio.h>
#include<stdlib.h>
typedef struct List{
	int x;
	int y;
	struct List *next;
}list;
typedef struct f_Map{
	int data;
	int indegree;
	list *neighbor;
}f_map;
typedef struct Sort{
	int data;
	int pos;
}sort;
int compare(const void *a,const void *b){
	sort *ptr1=(sort*)a;
	sort *ptr2=(sort*)b;
	if(ptr1->data<ptr2->data)return 1;
	if(ptr1->data>ptr2->data)return -1;
	if(ptr1->pos<ptr2->pos)return -1;
	if(ptr1->pos>ptr2->pos)return 1;
	return 0;
}
int comp(const void *a,const void *b){
	int *ptr1=(int*)a;
	int *ptr2=(int*)b;
	if(*ptr1<*ptr2)return 1;
	if(*ptr1>*ptr2)return -1;
	return 0;
}
int main(){
	int n,m,z;
	scanf("%d%d",&n,&m);
	if(n==1||m==1){
		int *in;
		in=(int*)malloc(n*m*sizeof(int));
		for(int i = 0; i < n*m; i++)scanf("%d",&in[i]);
		int total=n*m;
		qsort(in,total,sizeof(int),comp);
		for(int i = 1; i < n*m; i++){
			if(in[i]==in[i-1])total--;
		}printf("%d\n",total );
		return 0;
	}f_map **map,*d;
	map=(f_map**)malloc(n*sizeof(f_map*)+n*m*(sizeof(f_map)));
	for(z=0,d=(f_map*)(map+n);z<n;z++,d+=m)map[z]=d;
	sort **sort_x,*x,**sort_y,*y;
	sort_x=(sort**)malloc(n*sizeof(sort*)+n*m*(sizeof(sort)));
	for(z=0,x=(sort*)(sort_x+n);z<n;z++,x+=m)sort_x[z]=x;
	sort_y=(sort**)malloc(m*sizeof(sort*)+n*m*(sizeof(sort)));
	for(z=0,y=(sort*)(sort_y+m);z<m;z++,y+=n)sort_y[z]=y;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++){
			scanf("%d",&map[i][j].data);
			map[i][j].indegree=0;
			map[i][j].neighbor=NULL;
			sort_x[i][j].data=map[i][j].data;
			sort_x[i][j].pos=j;
			sort_y[j][i].data=map[i][j].data;
			sort_y[j][i].pos=i;
		}
	for(int i = 0; i < n; i++)qsort(sort_x[i],m,sizeof(sort),compare);
	for(int i = 0; i < m; i++)qsort(sort_y[i],n,sizeof(sort),compare);
	int now_front,now_end,compare_front,compare_end;
	for(int i = 0; i < n; i++){
		now_front=now_end=0;
		while(now_end+1<m&&sort_x[i][now_end+1].data==sort_x[i][now_front].data)now_end++;
		compare_end=compare_front=now_end+1;
		if(compare_end>=m)continue;
		while(compare_end+1<m&&sort_x[i][compare_end+1].data==sort_x[i][compare_front].data)compare_end++;	
		while(compare_end<m){
			for(int j = now_front;j<=now_end;j++){
				for(int k=compare_front;k<=compare_end;k++){
					list *new=(list*)malloc(sizeof(list));
					new->next=map[i][sort_x[i][j].pos].neighbor;
					new->x=sort_x[i][k].pos;
					new->y=i;
					map[i][sort_x[i][j].pos].neighbor=new;
					map[i][sort_x[i][k].pos].indegree++;
				}
			}now_front=compare_front;
			now_end=compare_end;
			compare_front=compare_end+1;
			compare_end++;
			while(compare_end+1<m&&sort_x[i][compare_end+1].data==sort_x[i][compare_front].data)compare_end++;	
		}
	}list *now_empty=NULL,*wait=NULL;
	for(int i = 0; i < m; i++){
		now_front=now_end=0;
		while(now_end+1<n&&sort_y[i][now_end+1].data==sort_y[i][now_front].data)now_end++;
		compare_end=compare_front=now_end+1;
		if(compare_end>=n){
			for(int j=now_front;j<=now_end;j++){
				if(map[sort_y[i][j].pos][i].indegree==0){
						list *tmp=(list*)malloc(sizeof(list));
						tmp->y=sort_y[i][j].pos;
						tmp->x=i;
						tmp->next=now_empty;
						now_empty=tmp;
					}
				}continue;
		}while(compare_end+1<n&&sort_y[i][compare_end+1].data==sort_y[i][compare_front].data)compare_end++;	
		while(compare_end<n){
			for(int j=now_front;j<=now_end;j++){
				for(int k=compare_front;k<=compare_end;k++){
					list *new=(list*)malloc(sizeof(list));
					new->next=map[sort_y[i][j].pos][i].neighbor;
					new->y=sort_y[i][k].pos;
					new->x=i;
					map[sort_y[i][j].pos][i].neighbor=new;
					map[sort_y[i][k].pos][i].indegree++;
				}if(map[sort_y[i][j].pos][i].indegree==0){
					list *tmp=(list*)malloc(sizeof(list));
					tmp->y=sort_y[i][j].pos;
					tmp->x=i;
					tmp->next=now_empty;
					now_empty=tmp;
				}
			}now_front=compare_front;
			now_end=compare_end;
			compare_front=compare_end+1;
			compare_end++;
			while(compare_end+1<n&&sort_y[i][compare_end+1].data==sort_y[i][compare_front].data)compare_end++;
		}
	}int total=n*m,step=0;
	while(total>0){
		while(now_empty!=NULL){
			list *tmp=now_empty;
			tmp=map[tmp->y][tmp->x].neighbor;
			while(tmp!=NULL){
				map[tmp->y][tmp->x].indegree--;
				if(map[tmp->y][tmp->x].indegree==0){
					list *t=(list*)malloc(sizeof(list));
					t->x=tmp->x;
					t->y=tmp->y;
					t->next=wait;
					wait=t;
				}tmp=tmp->next;
			}total--;
			now_empty=now_empty->next;
		}now_empty=wait;
		wait=NULL;
		step++;	
	}printf("%d\n",step);
}