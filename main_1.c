#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct Listnode{
    char data;
    struct Listnode *next;
    struct Listnode *pre;
}listnode;
listnode *begin=NULL, *head=NULL, *now=NULL, *select_h=NULL,*clip_head=NULL, *clip_tail=NULL;
int selected=0,right_left=0;
listnode* getnode(char data){
    listnode *s=(listnode *)malloc(sizeof(listnode));
    s->data=data;
    s->pre=NULL;
    s->next=NULL;
    return s;
}void insert(char data){
    listnode *new1=getnode(data);
    if(!selected || (selected && right_left==0)){
        if(now!=head){
            if(now->pre!=NULL)
                now->pre->next=new1;
            new1->pre=now->pre;
        }now->pre=new1;
        new1->next=now;
    }else if(selected && right_left!=0){
        if(right_left>0){
            new1->pre=now->pre;
            new1->next=select_h;
            select_h->pre=new1;
            if(now->pre!=NULL)
                now->pre->next=new1;
        }if(right_left<0){
            new1->pre=select_h->pre;
            new1->next=now;
            now->pre=new1;
            if(select_h->pre!=NULL)
                select_h->pre->next=new1;
        }
    }now=new1;
    if(now->pre==NULL)
        head=now;
    selected=0;
}void print(listnode *in){
    listnode *tmp=in;
    for(;tmp!=NULL;tmp=tmp->pre)
        printf("%c",tmp->data);
    printf("\n");
}
int what_commend(char c){
    if(c=='H'){
        if(now->next!=NULL){
            now=now->next;
            if(selected){
                right_left--;
            }
        }return selected;
    }if(c=='L'){
        if(now->pre!=NULL){
            now=now->pre;
            if(selected){
                right_left++;
            }
        }return selected;//move right
    }if(c=='I'){
        now=begin;
        if(selected){
            right_left-=50;;
            }
        return selected;//move begining
    }if(c=='A'){
        now=head;
        if(selected){
                right_left+=50;
            }
        return selected;
    }if(c=='V'){
        if(!selected){
            select_h=now;
            right_left=0;
            return 1;
        }select_h=NULL;
        return 0;
    }if(c=='D'){
        if(!selected || (selected && right_left==0))
            return selected;
        if(selected){
            clip_head=NULL;
            clip_tail=NULL;
            if(right_left>0){
                clip_head=select_h->pre;
                clip_tail=now;
                select_h->pre=now->pre;
                if(now->pre!=NULL)
                    now->pre->next=select_h;
                now=select_h;
            }else if(right_left<0){
                clip_head=now->pre;
                clip_tail=select_h;
                now->pre=select_h->pre;
                if(select_h->pre!=NULL)
                    select_h->pre->next=now;
            }clip_head->next=NULL;
            clip_tail->pre=NULL;
            if(now->pre==NULL)
                head=now;
            select_h=NULL;
            return 0;
        }
    }if(c=='P'){
        if(clip_head==NULL && clip_tail==NULL){
            if(!selected || (selected && right_left==0))
                return 0;
            if(selected){
                if(right_left>0){
                    select_h->pre=now->pre;
                    if(now->pre!=NULL)
                        now->pre->next=select_h;
                    now=select_h;
                }if(right_left<0){
                    now->pre=select_h->pre;
                    if(select_h->pre!=NULL)
                        select_h->pre->next=now;
                }if(now->pre==NULL)
                    head=now;
                return 0;
            }
        }if(!selected || (selected && right_left==0)){
            clip_head->next=now;
            clip_tail->pre=now->pre;
            if(now->pre!=NULL)
                now->pre->next=clip_tail;
            now->pre=clip_head;
        }else{
            if(right_left>0){
                clip_head->next=select_h;
                clip_tail->pre=now->pre;
                select_h->pre=clip_head;
                if(now->pre!=NULL)
                    now->pre->next=clip_tail;
            }if(right_left<0){
                clip_head->next=now;
                clip_tail->pre=select_h->pre;
                now->pre=clip_head;
                if(select_h->pre!=NULL)
                    select_h->pre->next=clip_tail;  
            }
        }now=clip_tail;
        clip_head=NULL;
        clip_tail=NULL;
        select_h=NULL; 
        if(now->pre==NULL)
            head=now;
        return 0;
    }return selected;
}int main(void)
{
    int T;
    scanf("%d",&T);
    for(int times=0; times<T;times++){
        char in[2000000]={0};
        selected=0;
        clip_head=NULL;
        clip_tail=NULL;
        select_h=NULL; 
        scanf("%s",in);
        int a=strlen(in);
        begin=getnode(0);
        now=begin;
        head=now;
        for(int i = 0; i < a; i++){
            if(!isalpha(in[i]))
                continue;
            if(isupper(in[i]))
                selected=what_commend(in[i]);
            if(islower(in[i]))
                insert(in[i]);
        }print(begin->pre);
    }
}