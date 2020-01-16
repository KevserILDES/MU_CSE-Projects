#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include<locale.h> 



// Struct for documents
struct document {
	int docID;
	int numOfOcc;
	int length;
	char cName[10];
	struct document *nextD;
};
//typedef document struct and pointer
typedef struct document Doc;
typedef Doc *DPtr;

// Struct for terms
struct term {
	char word[20];
	int numOfDoc;
	struct term *nextT;
	DPtr newLL;
};
//typedef term struct and pointer
typedef struct term Term;
typedef Term *TPtr;

//Functions prototypes
int insert(TPtr *, char[],char[],int);
void stopWords(TPtr);
void discriminatingWords(TPtr);
void lengthAssignment(TPtr,int,int,int,int [],int [],int []);

/*
void printAll(TPtr head){
		TPtr tm;
	tm=head;
	DPtr dc;
	while(tm!=NULL){
		printf("%s       %d\n",tm->word,tm->numOfDoc);
		dc=tm->newLL;
		while(dc!=NULL){
			printf("cat name : %s    doc id : %d     doc num occ : %d    doc length : %d\n",dc->cName,dc->docID,dc->numOfOcc,dc->length);
			dc=dc->nextD;
		}
		tm=tm->nextT;

	}
}*/

int main(){
	
	//to read the turkish alphabets from files
	setlocale(LC_ALL, "Turkish"); 

	//Assignments
	TPtr head=NULL;
	char c[10];//for category name
	DIR *dir;
	FILE *f;
	struct dirent *ent;
	char w[20];//for word that is taken from file
	char filee[25]=".\\dataset\\econ\\"; //path for economy folder
	char fileh[25]=".\\dataset\\health\\"; //path for health folder
	char filem[25]=".\\dataset\\magazin\\"; //path for magazin folder
	
	//variables for calculating the number of files in folders
	int numOfEcon=0,numOfHealth=0,numOfMagazin=0;

	//open directory for econ and count the number of files in economy
	if ((dir = opendir (".\\dataset\\econ")) != NULL) {
 	 	while ((ent = readdir (dir)) != NULL) {
  			if((*ent->d_name=='.' || *ent->d_name=='..')){
  				continue;
			}
			numOfEcon++;
		}
  		closedir (dir);
	}
	else {
  		perror ("");
  		return -1;
	}
	
	//open directory for health and count the number of files in health
	if ((dir = opendir (".\\dataset\\health")) != NULL) {
 	 	while ((ent = readdir (dir)) != NULL) {
  			if((*ent->d_name=='.' || *ent->d_name=='..')){
  				continue;
			}
			numOfHealth++;
		}
  		closedir (dir);
	}
	else {
  		perror ("");
  		return -1;
	}
	
	//open directory for magazin and count the number of files in magazin
	if ((dir = opendir (".\\dataset\\magazin")) != NULL) {
 	 	while ((ent = readdir (dir)) != NULL) {
  			if((*ent->d_name=='.' || *ent->d_name=='..')){
  				continue;
			}
			numOfMagazin++;
		}
  		closedir (dir);
	}
	else {
  		perror ("");
  		return -1;
	}
	
	//Assignments
	int  i,e=0,h=0,m=0; //e,h,m are to determine the index of length arrays of categories
	int lengthE[numOfEcon]; //to find length of each documents in economy folder
	int lengthH[numOfHealth]; //to find length of each documents in health folder
	int lengthM[numOfMagazin]; //to find length of each documents in magazin folder
	
	//Initialize all elements of all arrays
	for(i=0;i<numOfEcon;i++){
		lengthE[i]=0;
	}
	for(i=0;i<numOfHealth;i++){
		lengthH[i]=0;
	}
	for(i=0;i<numOfMagazin;i++){
		lengthM[i]=0;
	}
	

	//open econ directory and read all files in it
	if ((dir = opendir (".\\dataset\\econ")) != NULL) {
 	 	while ((ent = readdir (dir)) != NULL) {
  			if((*ent->d_name=='.' || *ent->d_name=='..')){
  				continue;
			}
			//set category name as ECONOMY
			strcpy(c,"ECONOMY");
			//take id number from file name 
		  	int id=atoi(ent->d_name);
		  	//concatenate econ directory and file name in it
		  	strcat(filee,ent->d_name);
		  	//open defined file to read only
		   	f=fopen(filee,"r");
		   	//until end of file read words from file , increase the length of file for each word and invoke insert function to insert that word to MLL
		    while(!feof(f)){
		  	   	fscanf(f,"%s",w);
		  	   	lengthE[e]++;
		  	   	insert(&head,w,c,id);
		    }
		    //close file 
			fclose(f);
			e++;
			//update economy file name as beginning
			strcpy(filee,".\\dataset\\econ\\");	 
			 
  		}		
  		closedir (dir);
		}
	else {
  		perror ("");
  		return -1;
	}
	
	
	//open health directory and read all files in it
	if ((dir = opendir (".\\dataset\\health")) != NULL) {
 	 	while ((ent = readdir (dir)) != NULL) {
  			if((*ent->d_name=='.' || *ent->d_name=='..')){
  				continue;
			}
			//set category name as HEALTH
			strcpy(c,"HEALTH");
			//take id number from file name 
	  		int id=atoi(ent->d_name);
		  	//concatenate health directory and file name in it
	  	    strcat(fileh,ent->d_name);
		  	//open defined file to read only
	   	 	f=fopen(fileh,"r");
	   	 	//until end of file read words from file , increase the length of file for each word and invoke insert function to insert that word to MLL
	    	while(!feof(f)){
	  	    	fscanf(f,"%s",w);
	  	    	lengthH[h]++;
	  	    	insert(&head,w,c,id);
	    	}
			fclose(f);
			h++;
			strcpy(fileh,".\\dataset\\health\\");	 
			 
  		}		
  		closedir (dir);
	}
	else {
  		perror ("");
  		return -1;
	}
	
	//open magazin directory and read all files in it
	if ((dir = opendir (".\\dataset\\magazin")) != NULL) {
 	 	while ((ent = readdir (dir)) != NULL) {
  			if((*ent->d_name=='.' || *ent->d_name=='..')){
  				continue;
			}
			//set category name as MAGAZIN
			strcpy(c,"MAGAZIN");
			//take id number from file name 
	  		int id=atoi(ent->d_name);
		  	//concatenate magazin directory and file name in it
	  	    strcat(filem,ent->d_name);
   		  	//open defined file to read only
	   	 	f=fopen(filem,"r");
		   	//until end of file read words from file , increase the length of file for each word and invoke insert function to insert that word to MLL
	    	while(!feof(f)){
	  	    	fscanf(f,"%s",w);
	  	    	lengthM[m]++;
	  	    	insert(&head,w,c,id);
	    	}
			fclose(f);
			m++;
			strcpy(filem,".\\dataset\\magazin\\");	 
			 
  		}		
  		closedir (dir);
	}
	else {
  		perror ("");
  		return -1;
	}
	
	
	//Invoke all functions
	lengthAssignment(head,e,h,m,lengthE,lengthH,lengthM);
	stopWords(head);
	discriminatingWords(head);
	
		
/*	to test all assignments' values (in structs)

	printAll(head);
	
*/	
	
}

//Insert function takes 4 parameters and add new struct with that term to the MLL if it doesnot exist already
int insert(TPtr *s, char w[],char cat[],int id){
	TPtr newT,preT,currT;
	DPtr newD,currD,preD;	
	currT=*s;
	
	//if word already exist then add a new document struct to documents' linked list of that term and return
	while(currT!=NULL){
		if(0==strcmp(w,currT->word)){
			currD=currT->newLL;
			while(currD!=NULL && (currD->docID!=id || strcmp(currD->cName,cat)!=0)){
				preD=currD;
				currD=currD->nextD;				
			}		
			if(currD==NULL){
				(currT->numOfDoc)++;
				newD=(DPtr)malloc(sizeof(Doc));
				newD->numOfOcc=1;
				newD->docID=id;
				strcpy(newD->cName,cat);
				newD->nextD=NULL;
				preD->nextD=newD;				
			}
			else{
				(currD->numOfOcc)++;
			}
			return 1;
		}		
		currT=currT->nextT;
	}
	
	//if it doesnot exist add a new term to MLL and new document to linked list of term
	newT=(TPtr)malloc(sizeof(Term));
	if(newT!=NULL){
		strcpy(newT->word,w);
		newT->nextT=NULL;
		newT->newLL=NULL;
		newT->numOfDoc=1;
		preT=NULL;
	
		currT=*s;

		while(currT!=NULL && 0<strcmp(w,currT->word)){
			preT=currT;
			currT=currT->nextT;
		}
		if(preT==NULL){
			newT->nextT=*s;
			*s=newT;
		}
		else{
			preT->nextT=newT;
			newT->nextT=currT;
		}
		newD=(DPtr)malloc(sizeof(Doc));
		newD->docID=id;
		newD->numOfOcc=1;
		strcpy(newD->cName,cat);
		newD->nextD=NULL;
		currD=newT->newLL;
		preD=NULL;
		while(currD!=NULL){
			preD=currD;
			currD=currD->nextD;
		}
		if(preD==NULL){
			newT->newLL=newD;
			newD->nextD=NULL;
		}	
		else{
			preD->nextD=newD;
			newD->nextD=NULL;
		}

	}
	else{
    	printf("No memory available.\n");
	}
	
	return 1;
}

//to find common words of all categories
void stopWords(TPtr a){
	DPtr b;
	int e=0,h=0,m=0,c=0;
	printf("\nSTOP WORDS\n--------------------\n");
	while(a!=NULL){
		if(a->numOfDoc>=3){
			b=a->newLL;
			while(b!=NULL){
				if(strcmp(b->cName,"ECONOMY")==0){
					e++;
				}
				if(strcmp(b->cName,"HEALTH")==0){
					h++;
				}	
				if(strcmp(b->cName,"MAGAZIN")==0){
					m++;
				}				
				b=b->nextD;				
			}
			if(e>0 && h>0 && m>0){
				c++;
				printf("Term - %d : %s\n",c,a->word);
				if(c==5){
					break;
				}
			}						
		}
		a=a->nextT;
		e=m=h=0;
	}
}

//to find discriminating words for each categories
void discriminatingWords(TPtr t){
	DPtr d;
	char econ[5][20]={'\0'};
	char health[5][20]={'\0'};
	char magazin[5][20]={'\0'};
	int e=0,h=0,m=0,a=0,b=0,c=0;
	printf("\n\nDISCRIMINATING WORDS\n--------------------\n");
	while(t!=NULL){
		d=t->newLL;
		while(d!=NULL){
			
			if(strcmp(d->cName,"ECONOMY")==0 ){
				e++;
			}
			
			if(strcmp(d->cName,"HEALTH")==0 ){
				h++;
			}	
			
			if(strcmp(d->cName,"MAGAZIN")==0 ){
				m++;
			}	
			
			d=d->nextD;	
		}

		if(e>0 && h==0 && m==0 && a!=5 ){
			strcpy(econ[a],t->word);
			a++;
		}
		
		if(e==0 && h>0 && m==0 && b!=5 ){
			strcpy(health[b],t->word);
			b++;
		}
			
		if(e==0 && h==0 && m>0 && c!=5 ){
			strcpy(magazin[c],t->word);
			c++;
		}
	
		t=t->nextT;
		e=m=h=0;
	}	
int i;
	printf("\nECONOMY\n--------------------\n");
	for(i=0;i<5;i++){
		printf("Term - %d : %s\n",i+1,econ[i]);
	}

	printf("\nHEALTH\n--------------------\n");
	for(i=0;i<5;i++){
		printf("Term - %d : %s\n",i+1,health[i]);
	}

	printf("\nMAGAZIN\n--------------------\n");
	for(i=0;i<5;i++){
		printf("Term - %d : %s\n",i+1,magazin[i]);
	}	
}

//to assign lengths of files to length variable of docuent structs (for each file)
void lengthAssignment(TPtr t,int e,int h,int m,int lengthE[],int lengthH[],int lengthM[]){
	DPtr d;
	int i;
	while(t!=NULL){
		d=t->newLL;
		while(d!=NULL){
			for(i=0;i<e;i++){
				if(d->docID==(i+1) && strcmp(d->cName,"ECONOMY")==0){
					d->length=lengthE[i];					
				}
			}
			for(i=0;i<h;i++){
				if(d->docID==(i+1) && strcmp(d->cName,"HEALTH")==0){
					d->length=lengthH[i];					
				}
			}
			for(i=0;i<m;i++){
				if(d->docID==(i+1) && strcmp(d->cName,"MAGAZIN")==0){
					d->length=lengthM[i];					
				}
			}			
			d=d->nextD;				
		}	
		t=t->nextT;
	}		
}
