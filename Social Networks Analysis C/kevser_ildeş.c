#include <stdio.h>
#include <string.h>
#include <math.h>

struct person{
	char name[10];
	struct person *nextFriend;
	struct person *nextPerson;
};
typedef struct person P;
typedef P *pPtr;
int i=0;
char mName[20][10];

//Function prototypes
int matrixPow(int adj[10][10],int pow,int i,int j);
void insert(pPtr *,char[10],char,int);

int main(){
	printf("\n");
	int adj[10][10]={0};
	FILE *f;
	pPtr ptr=NULL;
	char names[10];
	//to hold the value in last element of string ,that is, ; or ,
	char c;
	f=fopen("input.txt","r");
	//Read and insert all names to raph as struct according to punctuations at the end
	while(!feof(f)){
		fscanf(f,"%s",names);
		int a=strlen(names);
		char c=names[a-1];
		insert(&ptr,names,c,a);
	}
	pPtr p=ptr;
	//for printing graph in graph structure ,that is, as in theinput file firstly prints person's name one by one then prints their friends at each line
	while(p){
		printf("%s; ",p->name);
		pPtr pn=p->nextFriend;
		while(pn){
			if(pn->nextFriend)
			printf("%s, ",pn->name);
			else
			printf("%s ",pn->name);
			pn=pn->nextFriend;
		}
		printf("\n");
		p=p->nextPerson;
	}	
	printf("\n\n\t");
	p=ptr;
	//for printing names (as for declaration of adj. matrix) for upper ones
	while(p){
		printf("%s\t",p->name);	
		p=p->nextPerson;	
	}
	printf("\n\n");
	p=ptr;
	int j,k=0;
	int count=0;
	//Initialize adj. matrix
	while(p){
		pPtr t=p->nextFriend;
		while(t){
			j=0;
			while(mName[j][0]!='\0'){
				if(strcmp(mName[j],t->name)==0){
					adj[k][j]=1;					
				}
				j++;
			}

			t=t->nextFriend;
		}
		k++;
		p=p->nextPerson;
	}
	
	int n=0;
	p=ptr;
	while(p){
		n++;
		p=p->nextPerson;
	}
	
	p=ptr;
	int a,b;
	//prints firstly names and than corresponding adj. matrix representations
	for(a=0;a<10,p;a++){
		printf("%s",p->name);
		for(b=0;b<10;b++){
			printf("\t %d ",adj[a][b]);
		}
		printf("\n\n");
		p=p->nextPerson;
	}

	
	//Degree centrality
	j=0,k=0;
	int deg[10]={0};
	for(j=0;j<10;j++){
		for(k=0;k<10;k++){
			deg[j]+=adj[k][j];
		}	
	}

	//Closeness centrality
	int closs[10]={0};
	for(a=0;a<10;a++){
		for(b=0;b<10;b++){
			if(b==a) continue;
			if(adj[a][b]==1) closs[a]++;
			else{
				int c=2;
				while(c<10){
					if(matrixPow(adj,c,a,b)>0){
						closs[a]+=c;
						break;
					}
					c++;
				}
			}		
		}
	}
	
	int y=0;
	printf("\n\nSource \t Degree Centrality \t Closeness Centrality \t Betweenness Centrality\n\n");
	while(y<10){
		printf("%s\t\t%d/%d\t\t\t%d/%d\t\t\t /%d\n\n",mName[y],deg[y],n-1,n-1,closs[y],((n-1)*(n-2)/2)*((n-1)*(n-2)/2));
		y++;
	}
}

//it calculates the powers of matrix (to find closeness centrality) -Note : as 5 is enough for this input it calculates till 5-
int matrixPow(int adj[10][10],int pow,int i,int j){
	int sum=0,a,b,c,d,matrix[10][10]={0},result[10][10];
	for(a=0;a<10;a++){
		for(b=0;b<10;b++){
			matrix[a][b]=adj[a][b];
		}
	}
    for ( a = 0 ; a < 10 ; a++ ){
        for (b = 0 ; b < 10 ; b++ ){
            for (c = 0 ; c < 10 ; c++ ){
                sum += matrix[a][c]*matrix[c][b];
            }
            result[a][b] = sum;
            sum = 0;
        }
    }
    sum=0;
    int result1[10][10]={0};
	if(pow==3){
    	for ( a = 0 ; a < 10 ; a++ ){
            for (b = 0 ; b < 10 ; b++ ){
                for (c = 0 ; c < 10 ; c++ ){
                    sum += result[a][c]*matrix[c][b];
                }
                result1[a][b] = sum;
                sum = 0;
            }
        }         	
	}
	int result2[10][10]={0};
	if(pow==4){
    	for ( a = 0 ; a < 10 ; a++ ){
            for (b = 0 ; b < 10 ; b++ ){
                for (c = 0 ; c < 10 ; c++ ){
                    sum += result[a][c]*result[c][b];
                }
                result2[a][b] = sum;
                sum = 0;
            }
        }
    }
	int result3[10][10]={0};
 	if(pow==5){
	  	for ( a = 0 ; a < 10 ; a++ ){
            for (b = 0 ; b < 10 ; b++ ){
                for (c = 0 ; c < 10 ; c++ ){
                    sum += result[a][c]*matrix[c][b];
                }
                result1[a][b] = sum;
                sum = 0;
            }
        } 
        sum=0;
        for ( a = 0 ; a < 10 ; a++ ){
            for (b = 0 ; b < 10 ; b++ ){
                for (c = 0 ; c < 10 ; c++ ){
                    sum += result1[a][c]*result[c][b];
                }
                result3[a][b] = sum;
                sum = 0;
            }
        }
    }
	int result4[10][10]={0};
 	if(pow==6){
	   	for ( a = 0 ; a < 10 ; a++ ){
            for (b = 0 ; b < 10 ; b++ ){
                for (c = 0 ; c < 10 ; c++ ){
                    sum += result2[a][c]*result[c][b];
                }
                result4[a][b] = sum;
                sum = 0;
            }
        }
    }
    if(result[i][j]!=0) return result[i][j];
    else if(result1[i][j]!=0) return result1[i][j];
    else if(result2[i][j]!=0) return result2[i][j];
    else if(result3[i][j]!=0) return result3[i][j];
    else if(result4[i][j]!=0) return result4[i][j];
    else return -1;
}

//it inserts people into graph
void insert(pPtr *ptr,char names[10],char c,int a){
	pPtr newN,curr,prev;
	newN=(pPtr)malloc(sizeof(P));
	//if at the end of name there is ; ,that is, it is person then insert it as person after eliminating ;
	if(c==';'){
		names[a-1]='\0';
		strcpy(mName[i],names);
		mName[i+1][0]='\0';
		i++;
		strcpy(newN->name,names);
		newN->nextFriend=NULL;
		newN->nextPerson=NULL;
		if(!(*ptr)){
			*ptr=newN;
		}	
		else{
			pPtr s=*ptr;
			while(s->nextPerson){
				s=s->nextPerson;
			}
			s->nextPerson=newN;	
		}		
	}
	else{
		//if at the end of name there is , or it is at the end of line ,that is, it is friend of a person then insert it as friend of that person after eliminating ,
		if(c==',')
			names[a-1]='\0';
		strcpy(newN->name,names);
		newN->nextFriend=NULL;
		newN->nextPerson=NULL;
		pPtr s=*ptr;
		while(s->nextPerson){
			s=s->nextPerson;
		}
		pPtr f=s;
		while(f->nextFriend)
			f=f->nextFriend;
		f->nextFriend=newN;
	}
}
