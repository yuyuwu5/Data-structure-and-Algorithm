#include<stdio.h>
#include<string.h>
char in[30000000],compare[30000000],name[2][15];
long long int pi[30000000],add[30000000],addT[30000000],ans=0,how_many_time=0,k = -1;
int main(){
	scanf("%s%s%s%s",name[0],name[1],in,compare);
	int length1=strlen(in),length2=strlen(compare);
	pi[0] = k;
	addT[0]=1;
	add[0]=1;
	for (int i = 1; i < length2; i++) {
		while (k > -1 && compare[k+1] != compare[i])
			k = pi[k];
		if (compare[i] == compare[k+1])
			k++;
		pi[i] = k;
		addT[i]=1;
		add[i]+=i+1;
		int tmp=pi[i];
		if(tmp>-1){
			add[i]+=add[tmp];
			addT[i]+=addT[tmp];
			if(add[i]>=1000000007)
			add[i]%=1000000007;
		}
	}k = -1;
	for (int i = 0; i < length1; i++) {
		while (k > -1 && compare[k+1] !=in[i])
			k = pi[k];
		if (in[i] == compare[k+1]){
			k++;
			ans+=add[k];
			how_many_time+=addT[k];	
		}if (k == length2-1) 
			k=pi[k];
	}if(ans>=1000000007)
			ans%=1000000007;
	printf("%s\n%lld\n",name[(how_many_time+1)&1],ans);
}
