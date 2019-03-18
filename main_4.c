#include<stdio.h>
#include<string.h>
char pattern[10000000],target[10000000];
unsigned long long p_distance[10000000]={0}, t_distance[10000000]={0}, t_Revdistance[10000000]={0},mypow[10000000];
unsigned int rabin_karp(int length1,int length2){
	unsigned long long p=0,t=0;
	unsigned int hit=0;
	mypow[0]=1;
	for(int i =0; i < length2; i++){
		p=p*100007+p_distance[i];
		t=t*100007+t_distance[i];
		mypow[i+1]=mypow[i]*100007;
	}for(int i = 0; i < length1-length2; i++){
		if(p==t)hit++;
		if(t_Revdistance[i]>0){
			if(t_Revdistance[i]<length2)
				t=t-t_distance[i+t_Revdistance[i]]*mypow[length2-t_Revdistance[i]-1];
			t_distance[i+t_Revdistance[i]]=0;
		}t=100007*(t-t_distance[i]*mypow[length2-1])+t_distance[i+length2];
	}if(p==t)hit++;
	return hit;
}
int main(){
	scanf("%s%s",target,pattern);
	unsigned int length1=strlen(target),length2=strlen(pattern),hit=0;
	if(length2==1){
		printf("%u\n",length1);
		return 0;
	}if(length2>length1){
		printf("0\n");
		return 0;
	}unsigned int pos1[26]={0},pos2[26]={0},pos3[26]={0};
	for(int i = 0; i<length1; i++){
		if(pos1[target[i]-'a']<i+1 && pos1[target[i]-'a']>0 ){
			t_distance[i]=i-pos1[target[i]-'a']+1;
		}pos1[target[i]-'a']=i+1;
	}for(int i = length1-1; i>=0; i--){
		if(pos2[target[i]-'a']>i){
			t_Revdistance[i]=pos2[target[i]-'a']-i;
		}pos2[target[i]-'a']=i;
	}for(int i = 0; i<length2; i++){
		if(pos3[pattern[i]-'a']<i+1 &&pos3[pattern[i]-'a']>0){
			p_distance[i]=i-pos3[pattern[i]-'a']+1;
		}pos3[pattern[i]-'a']=i+1;
	}hit=rabin_karp(length1,length2);
	printf("%u\n",hit);
}
