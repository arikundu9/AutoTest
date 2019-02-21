/* Project AutoTest
 * 
 * Copyright (C) 2019 - Arijit Kundu <arikundu9@gmail.com>
 * 
 * AutoTest.cpp
 * This file belongs to the Project AutoTest.
 * Any commercial use of this file is prohibited.
 */

#include<cstdio>
#include<cstdlib>
#include<ctime>
#define LINE_MAX 100
#define QUSTION_PATTERN "test.pattern"
#define QUSTION_STORE "qustion.store"
#define DASHES "\n--------------------------------------------------------------------\n"
void printh(FILE *f,int h=1,int m=30,int fm=30);
int main(){
    FILE *qp,*qs,*q;
	char ln[LINE_MAX],qfn[30];
    int marks,noq,sum,opt,i=1;
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
                //scanq(qs);
                while(fgets(ln,LINE_MAX,qp)){
                    sscanf(ln,"%dx%d,%d",&marks,&noq,&opt);
                    sum=noq*marks;
                    fprintf(q,DASHES);
                    fprintf(q,"%d) Ans any %d qustion out of following %d.                      %dx%d=%d",i++,noq,opt,noq,marks,sum);
                    fprintf(q,DASHES);
                    //printq(q,marks,opt);
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