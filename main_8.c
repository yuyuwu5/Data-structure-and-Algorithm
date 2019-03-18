#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char name[200005][15];
int n,list[200005],priority[200005],pos[200005];
int find_root(int a){
    while(list[a]>0)
        a=list[a];
    return a;
}
int parent(int index) {
    return (index - 1) / 2;
}
int left(int index) {
    return 2 * index + 1;
}
int right(int index) {
    return 2 * index + 2;
}
void MinHeapify(int i){ 
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if(l<=n && r <=n){
    	if (list[priority[l]] != list[priority[r]]){
    		if (list[priority[l]] < list[priority[i]])smallest = l;
    		if (list[priority[r]] < list[priority[smallest]])smallest = r;
		}else if (list[priority[l]] == list[priority[r]]){
    		if(priority[r]<priority[l])smallest = r;
    		if(priority[l]<priority[r])smallest = l;
    	}
    }else if(l<=n){ 
    	if(list[priority[l]]<list[priority[smallest]])smallest=l;
    	if (list[priority[l]==list[priority[smallest]]] && priority[l]<priority[smallest])smallest=l;	
    }else if(r<=n){
    	if(list[priority[r]]<list[priority[smallest]])smallest=r;
    	if (list[priority[r]==list[priority[smallest]]] && priority[r]<priority[smallest])smallest=r;	
 
    }if (smallest != i){
    	int tmp=priority[i];
    	pos[priority[i]]=smallest;
    	pos[priority[smallest]]=i;
    	priority[i]=priority[smallest];
    	priority[smallest]=tmp;
        MinHeapify(smallest);
    }
}
int extractMin(int i){
    int root = priority[i];
    if(i == 0)list[priority[i]]=200005;
    MinHeapify(i);
    return root;
}
void shiftup(int i) {
    int parentIndex, tmp;
  	parentIndex = parent(i);
    if (list[priority[parentIndex]] >list[priority[i]] || (list[priority[parentIndex]] == list[priority[i]] && priority[parentIndex]>priority[i])) {
        tmp = priority[parentIndex];
        pos[priority[i]]=parentIndex;
    	pos[priority[parentIndex]]=i;
        priority[parentIndex] = priority[i];
        priority[i] = tmp;
        shiftup(parentIndex);
    }
}
int main(){
    scanf("%d",&n);
    list[0]=2000005;
    for(int i = 1; i <= n; i++){
        scanf("%s",name[i]);
        list[i]=-1;
        priority[i-1]=i;
        pos[i]=i-1;
    }
    int m;
    scanf("%d",&m);
    for(int i = 0; i < m; i++){
        int type,a,b;
        scanf("%d",&type);
        if(type==1){
            scanf("%d%d",&a,&b);
            int root1=a,root2=b;
            if(list[a]>0){
                root1=find_root(a);
                list[a]=root1;
            }if(list[b]>0){
                root2=find_root(b);
                list[b]=root2;
            }if(root2>root1){
                list[root1]+=list[root2];
                shiftup(pos[root1]);
                list[root2]=root1;
                extractMin(pos[root2]);
            }if(root1>root2){
                list[root2]+=list[root1];
                shiftup(pos[root2]);
                list[root1]=root2;
                extractMin(pos[root1]);
            }
        }if(type==2){
            printf("%s\n",name[extractMin(0)]);
        }
    }
}