/* Project AutoTest
 * 
 * Copyright (C) 2019 - Arijit Kundu <arikundu9@gmail.com>
 * 
 * AutoTest.cpp
 * This file belongs to the Project AutoTest.
 * Any commercial use of this file is prohibited.
 */

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<cstring>

#define LINE_MAX 100
#define QUSTION_PATTERN "test.pattern"
#define QUSTION_STORE "qustion.store"
#define DASHES "\n--------------------------------------------------------------------\n"

using namespace std;

typedef struct {
    int marks;
    char q[LINE_MAX];
} group;
typedef vector<group> qset;

void printh(FILE *f,int h=1,int m=30,int fm=30);
qset scanq(FILE *qs);
void printq(FILE *q,qset &qs,int marks,int opt);
int getNOQ(qset &qs,int marks);
void test(qset qs);
char* getQSN(qset &qs,int marks,int qno);

int main(){
    FILE *qp,*qs,*q;
    char ln[LINE_MAX],qfn[30];
    int marks,noq,sum,opt,i=1;
    qset tset;
    qp=fopen(QUSTION_PATTERN,"rb");
    if(qp==NULL){
		fprintf(stderr,"\nERROR::Failed to open PATTERN file.\n");
		exit(1);
	}
    else{
        qs=fopen(QUSTION_STORE,"rb");
        if(qs==NULL){
		    fprintf(stderr,"\nERROR::Failed to open STORE file.\n");
		    exit(2);
	    }
        else{
            printf("Enter Output Filename: ");
            scanf("%s",&qfn);
            q=fopen(qfn,"wb");
            if(q==NULL){
                fprintf(stderr,"\nERROR::Failed to open OUTPUT file.\n");
                exit(3);
            }
            else{
                printh(q);
                tset=scanq(qs);
                //test(tset);
                while(fgets(ln,LINE_MAX,qp)){
                    sscanf(ln,"%dx%d,%d",&marks,&noq,&opt);
                    sum=noq*marks;
                    fprintf(q,DASHES);
                    fprintf(q,"%d) Ans any %d qustion out of following %d.                      %dx%d=%d",i++,noq,opt,noq,marks,sum);
                    fprintf(q,DASHES);
                    printq(q,tset,marks,opt);
                }
                fclose(q);
            }
            fclose(qs);
        }
        fclose(qp);
    }
    return 0;
}
void printh(FILE *f,int h,int m,int fm){
    time_t mt=time(NULL);
    clock_t t=time(NULL);
    fprintf(f,"             ------------------------------------------\n");
    fprintf(f,"             Auto Test v1.0 :: %s",ctime(&mt));
    fprintf(f,"             ------------------------------------------\n");
    fprintf(f,"====================================================================\n");
    fprintf(f,"Duration: %d:%d                                              F.M.: %d\n",h,m,fm);
    fprintf(f,"====================================================================\n");
}
qset scanq(FILE *qs){
    qset q;
    group g;
    char ln[LINE_MAX];
    while(fgets(ln,LINE_MAX,qs)){
        sscanf(ln,"%d|%[^\n]s",&g.marks,g.q);
        q.push_back(g);
    }
    return q;
}
void printq(FILE *q,qset &qs,int marks,int opt){
    int noq=0,rnd=0,i=0,j=0;
    static vector<pair<int,int>> use;
    for(;i<=opt;i++){
        noq=getNOQ(qs,marks);
        for(j=1;j<=noq;j++){
            rnd= 1+(rand() % static_cast<int>(noq-1+1));
            if(std::find(use.begin(),use.end(),pair<int,int>(marks,rnd))==use.end()){
                fprintf(q,"\t%d) %s",i,getQSN(qs,marks,rnd));
                use.push_back(pair<int,int>(marks,rnd));
                break;
            }
        }

    }
}
char* getQSN(qset &qs,int marks,int qno){
    int i=0;
    char *r=NULL;
    for(group x : qs){
        if(x.marks==marks)
            i++;
        if(i==qno){
            break;
            r=x.q;
        }
    }
    return(r);
}
int getNOQ(qset &qs,int marks){
    int i=0;
    for(group x : qs){
        if(x.marks==marks)
            i++;
    }
    return(i);
}
void test(qset qs){
    for(group x : qs){
        printf("No: %d, Q: %s\n",x.marks,x.q);
    }
}