#include <stdio.h>
#include <stdlib.h>
# include <string.h>

#define SIZE1 52973671      //total links.txt
#define SIZE2 1483277       //total pages.txt
#define SIZE3 4552836    //total cat_linkstxt
#define SIZE4 229895      //total cats.txt

#define WORD_LENGTH 1000     //length of wikipedia
#define WORD_LENGTH 1000     //length of categoryname

typedef struct data_t1{
    int id;                 //id of the page
    int linked;             //id of the linked page
}data_type1;

typedef struct data_t2{
    int id;
    char *word;
}data_type2;

typedef struct data_t3{
    int id2;
    int linked2;                //id of the linked page  
}data_type3;

typedef struct data_t4{
    int id2;
    char *name;                  //name=categoryname
}data_type4;

data_type1 table1[SIZE1];     //declare array whose size is SIZE1
data_type2 table2[SIZE2];     //declare array whose size is SIZE2
data_type3 table3[SIZE3];     //declare array whose size is SIZE3
data_type4 table4[SIZE4];     //declare array whose size is SIZE4

int num_linked[SIZE2]={0};
int num_linked2[SIZE4]={0};  //declare array ,inithiarize by 0

int n;                      //number of the links
int m;                      //number of the pages
int l;                      //number of the catlinks
int k;                      //number of the cats

void insert_linkend(int id,int linked){ /*add the data at the end of table1*/
    if(n<SIZE1-1){  /*table1 has another room*/
        table1[n+1].id=id;
        table1[n+1].linked=linked;
        n++;
    }else{
        printf("table1 is full\n");
        exit(1);
    }
}

void insert_pageend(int id,char *word){ /*add the data at the end of table2*/
    if(m<SIZE2-1){  /*table2 has another room*/
        table2[m+1].id=id;
        table2[m+1].word=word;
        m++;
    }else{
        printf("table2 is full\n");
        exit(1);
    }
}

void insert_catlinkend(int id2,int linked2){ /*add the data at the end of table3*/
    if(l<SIZE3-1){  /*table3 has another room*/
        table3[l+1].id2=id2;
        table3[l+1].linked2=linked2;
        l++;
    }else{
        printf("table3 is full\n");
        exit(1);
    }
}


void insert_catend(int id2,char *name){ /*add the data at the end of table4*/
    if(k<SIZE4-1){  /*table4 has another room*/
        table4[k+1].id2=id2;
        table4[k+1].name=name;
        k++;
    }else{
        printf("table4 is full\n");
        exit(1);
    }
}

void read_linkfile(char *filename){ /*read links*/
    FILE *file;
    int id,linked;
    int r;
    
    file=fopen(filename,"r");   
    if(file==NULL){ 
        printf("couldn't find %s\n",filename);
        exit(1);    
    }
    while(1){
        r=fscanf(file,"%d\t%d\n",&id,&linked);  //read 1 raw
        if(r==EOF){ 
            fclose(file);   
            return; 
        }else{  
            insert_linkend(id,linked);  //add it then repeat
        }
    }
}

void read_pagefile(char *filename){ /*read pages*/
    FILE *file;
    int id;
    char *word;
    int r;
    
    file=fopen(filename,"r");  
    if(file==NULL){ 
        printf("couldn't find%s\n",filename);
        exit(1);    
    }
    while(1){
        word=(char *)malloc(WORD_LENGTH);   //save memori
        r=fscanf(file,"%d\t%s\n",&id,word); //read 1 raw
        if(r==EOF){ 
            fclose(file);   
            return; 
        }else{  
            insert_pageend(id,word);    //add and continue
        }
    }   
}

void read_catlinkfile(char *filename){ /*read cat_links*/
    FILE *file;
    int id2,linked2;
    int r;
    
    file=fopen(filename,"r");   
    if(file==NULL){ 
        printf("couldn't find %s\n",filename);
        exit(1);    
    }
    while(1){
        r=fscanf(file,"%d\t%d\n",&id2,&linked2);  //read 1 raw
        if(r==EOF){ 
            fclose(file);   
            return; 
        }else{  
            insert_catlinkend(id2,linked2);  //add it then repeat
        }
    }
}

void read_catfile(char *filename){ /*read cats*/
    FILE *file;
    int id2;
    char *name;
    int r;
    
    file=fopen(filename,"r");  
    if(file==NULL){ 
        printf("couldn't find%s\n",filename);
        exit(1);    
    }
    while(1){
        name=(char *)malloc(WORD_LENGTH);   //save memori
        r=fscanf(file,"%d\t%s\n",&id2,name); //read 1 raw
        if(r==EOF){ 
            fclose(file);   
            return; 
        }else{  
            insert_catend(id2,name);    //add and continue
        }
    }   
}


int main(void){
  int category_id2=0;
 int i,j,dumy,k;
	int rank;
	int count=0;
	int a[1000];
	int id[1000];
	char str1[1000];
	//char str2[1000];
	
    n=-1;    //inithiarize by -1
    read_linkfile("links.txt"); //read links
    m=-1;   //inithiarize -1
    read_pagefile("pages.txt"); // read pages
    l=-1;
    read_catlinkfile("cat_links.txt");
    k=-1;
    read_catfile("cats.txt");
    
		for(i=0;i<SIZE1;i++){   //for all links
		num_linked[table1[i].linked]+=1;    //count linked number
		}
    
		 /*check if word interested is categoryname?*/
		printf("input the word you are interested in.\n");
		scanf("%s",str1);
		for(i=0;i<SIZE4;i++){
		  dumy=i;//for all cats
		   if(strstr(table4[dumy].name,str1)!=NULL){ //if find the categoryname
		      category_id2=dumy; //memorize id of the category
		     break;}
		   else{
		   }
		   
		   /*if(dumy==SIZE4-1){
		     printf("input the word you are interested in.\n");
		     scanf("%s",str2);
			for(i=0;i<SIZE4;i++){ //for all cats
			  if(strstr(table4[i].name,str1)!=NULL){
			   break;}
			   else{
			   }
			    check=i;
			    if(check==SIZE4-1){
			      printf("could'nt find.\n");
			      exit(1);
			    }
			}
		   }*/
		}
		
		/*search words which has the category*/
		
		for(i=0;i<SIZE3;i++){
		  dumy=i;//for all cat_links
		  if(table3[dumy].linked2==category_id2){
		    a[count]=num_linked[dumy];
		    id[count]=dumy;
		    count+=1;
		  }
		  else{
		  }
		 /*sorting*/
		  for(i = 0; i < count; i++){ 
			for(j = i + 1; j < count; j++){
				if(a[i] > a[j]){
					dumy = a[i];
					a[i] = a[j];
					a[j] = dumy;
					}
				else{
				}
			}
		} 
		/*show rank*/
		for(i=0;i<10;i++){
			k=id[i];
			rank=i;
			printf("rank%d ",rank+1);
			printf("%s\n",table2[k].word);
		}
	}
}