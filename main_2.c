#include<stdio.h>
#include<string.h>
char in[100000000], element[100000000]={0};
int main()
{
	int take,top=0;
	scanf("%s%d",in,&take);
	int a=strlen(in);
	char c;
	for(int i = 0; i < a; i++){
		c=element[top-1];
		while(top>0 && take>0){
			if(c=='0' && in[i]>'0' && take>=top && element[0]>in[i]){
	   			take-=top;
				top=0;
				strcpy(element,"");
				break;
			}else if((c>in[i]&&in[i]>'0') || (in[i]=='0'&& c>'0'&& top>1)){
				element[top-1]=0;
				top--;
				c=element[top-1];
				take--;
			}else break;
		}element[top]=in[i];
		top++;
	}for(;take>0;take--){
		element[top-1]=0;
		top--;
	}printf("%s\n",element);
}