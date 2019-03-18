#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node{
	int data;
	struct Node *one;
	struct Node *zero;
}node;
node *root;
int out[64],n,m;
node *getnode(){
	node *ptr=(node*)malloc(sizeof(node));
	ptr->one=NULL;
	ptr->zero=NULL;
	return ptr;
} 
void insert(int *in){
	node *ptr=root;
	for(int i = 0; i < 64; i++){
		if(in[i]==1){
			if(ptr->one==NULL){
				ptr->one=getnode();
				ptr=ptr->one;
				ptr->data=1;
			}else{
				ptr=ptr->one;
			}
		}else{
			if(ptr->zero==NULL){
				ptr->zero=getnode();
				ptr=ptr->zero;
				ptr->data=0;
			}else{
				ptr=ptr->zero;
			}
		}
	}
}
void search(int *find){
	node *ptr=root;
	int start=0;
	for(int i = 0; i < 64; i++){
		if(find[i]==0){
			if(ptr->zero!=NULL){
				ptr=ptr->zero;
			}else ptr=ptr->one;
		}else if(find[i]==1){
			if(ptr->one!=NULL){
				ptr=ptr->one;
			}else ptr=ptr->zero;
		}out[i]=ptr->data;
	}for(int i = 0; i<64;i++){
		if(out[i]==1)start=1;
		if(!start)continue;
		printf("%d",out[i]);
	}if(!start)printf("0");
	printf("\n");
}
void delete(int *data){
	node *ptr=root,*delete;
	int way;
	for(int i = 0; i < 64; i++){
		if(data[i]==0){
			if(ptr->zero==NULL)return;
			ptr=ptr->zero;
		}else if(data[i]==1){
			if(ptr->one==NULL)return;
			ptr=ptr->one;
		}if(ptr->one!=NULL && ptr->zero !=NULL){
			delete=ptr;
			way=data[i+1];
		}
	}if(!way)delete->zero=NULL;
	else delete->one=NULL;
}
int main(){
	scanf("%d",&n);
	char world[65];
	root=getnode();
	for(int i = 0; i < n; i++){
		scanf("%s",world);
		int length=strlen(world),a=64-length,in[65];
		for(int j = 0; j < a;j++){
			in[j]=0;
		}for(int j=0;j<length;j++){
			in[a+j]=world[j]-'0';
		}insert(in);
	}scanf("%d",&m);	
	for(int i = 0; i < m; i++){
		char type[1],in[65];
		scanf("%s",type);
		scanf("%s",in);
		int length=strlen(in),a=64-length,find[65],data[65];
		for(int j=0;j<a;j++)
			find[j]=1;
		for(int j = 0; j < length; j++){
			int k=in[j]-'0';
			if(k==0)find[a+j]=1;
			if(k==1)find[a+j]=0;
		}for(int j = 0; j < a;j++){
			data[j]=0;
		}for(int j=0;j<length;j++){
			data[a+j]=in[j]-'0';
		}if(type[0] =='Q'){
			search(find);
		}else if(type[0]=='U'){
			insert(data);
		}else if(type[0]=='D'){
			delete(data);
		}
	}
}