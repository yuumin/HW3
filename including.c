/*find most linked page*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define SIZE1 52973671      //links.txt????
#define SIZE2 1483277       //pages.txt????

#define WORD_LENGTH 1000     //wikipedia????????

typedef struct data_t1{
    int id;                 //????id
    int linked;             //????????????id
}data_type1;

typedef struct data_t2{
    int id;
    char *word;
}data_type2;

data_type1 table1[SIZE1];     //???SIZE1??????
data_type2 table2[SIZE2];     //???SIZE2??????

int num_linked[SIZE2]={0};  //????????????????0????

int n;                      //??????
int m;                      //??????

void insert_linkend(int id,int linked){ /*table1????????????*/
    if(n<SIZE1-1){  /*table1????????*/
        table1[n+1].id=id;
        table1[n+1].linked=linked;
        n++;
    }else{
        printf("???????????\n");
        exit(1);
    }
}

void insert_pageend(int id,char *word){ /*table2????????????*/
    if(m<SIZE2-1){  /*table2????????*/
        table2[m+1].id=id;
        table2[m+1].word=word;
        m++;
    }else{
        printf("???????????\n");
        exit(1);
    }
}

void read_linkfile(char *filename){ /*????????????????*/
    FILE *file;
    int id,linked;
    int r;
    
    file=fopen(filename,"r");   //??????????????
    if(file==NULL){ /*??????????????*/
        printf("????%s????????\n",filename);
        exit(1);    //?????????
    }
    while(1){
        r=fscanf(file,"%d\t%d\n",&id,&linked);  //1???????????
        if(r==EOF){ /*??????????*/
            fclose(file);   //????????
            return; //??
        }else{  /*?????????*/
            insert_linkend(id,linked);  //???????????????
        }
    }
}

void read_pagefile(char *filename){ /*????????????????*/
    FILE *file;
    int id;
    char *word;
    int r;
    
    file=fopen(filename,"r");   //??????????????
    if(file==NULL){ /*??????????????*/
        printf("????%s????????\n",filename);
        exit(1);    //?????????
    }
    while(1){
        word=(char *)malloc(WORD_LENGTH);   //???????????????
        r=fscanf(file,"%d\t%s\n",&id,word); //1????????????
        if(r==EOF){ /*??????????*/
            fclose(file);   //????????
            return; //??
        }else{  /*?????????*/
            insert_pageend(id,word);    //???????????????
        }
    }
    
}

int main(void){
    n=-1;    //table1[0]????????????-1????
    read_linkfile("links.txt"); //??????????
    m=-1;   //table2[0]????????????-1????
    read_pagefile("pages.txt"); //??????????
    
    char str1[1000];
    printf("input the word you are interested in.\n");
    scanf("%s",str1);

    int i;
    for(i=0;i<SIZE2;i++){
       if(strstr(table2[i].word,str1)!=NULL){/*???????????????*/
	 printf("%s\n",table2[i].word);
       }
       else{
       }
    }
}

/*
int main(void){
    n=-1;    //table1[0]????????????-1????
    read_linkfile("links.txt"); //??????????
    m=-1;   //table2[0]????????????-1????
    read_pagefile("pages.txt"); //??????????
	int ave=
    int i;
    for(i=0;i<SIZE1;i++){   /*????????????*/
    	/*
        num_linked[table1[i].linked]+=1;    //?????????
    }
    int max=0;
    int id;
    for(i=0;i<SIZE2;i++){
        if(max<num_linked[i]){
            max=num_linked[i];
            id=i;
        }
    }
    printf("%s\n",table2[id].word);*/
