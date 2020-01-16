#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Create a struct
struct TTNodeType{
	int data;
	struct TTNodeType *left;
	struct TTNodeType *middle;
	struct TTNodeType *right;
};
typedef struct TTNodeType ternary;
typedef ternary *terP;

//function prototypes
void print_menu();
void preorder(terP s);
void postorder(terP s);
void inorder(terP s);
int insertN(terP *s,int a);
terP removeN(terP s,int a);
terP findN(terP s,int a,int i);
terP findMax(terP s);
terP findMin(terP s);

int main(){
	FILE *f;
	terP root=NULL;
	int value;
	//open file 
	f=fopen("input.txt","r");
	//untill end of file take keys and insert them to the tree
	while(!feof(f)){
		fscanf(f,"%d",&value);
		insertN(&root,value);
	}
	
	//for options to find,remove or print
	int choice;
	int key;
	int choice2;
	print_menu();
	scanf("%d",&choice);
	while(choice!=0){
		switch(choice){
			case 1: printf("\nEnter the key : "); scanf("%d",&key); if(!findN(root,key,0)) printf("\nThe key is not in the tree!\n"); break;
			case 2: printf("\nEnter the key : "); scanf("%d",&key); removeN(root,key); break;
			case 3: menu2:printf("\n- 1 for inorder\n- 2 for preorder\n- 3 for postorder\nEnter your choice : "); scanf("%d",&choice2);
					switch(choice2){
						case 1: inorder(root); break;
						case 2: preorder(root); break;
						case 3: postorder(root); break;
						default: printf("\nInvalid choice\n"); goto menu2; break;
					}
					break;
			default: printf("\nInvalid choice\n"); break;
		}
		printf("\n");
		print_menu();
		scanf("%d",&choice);
		printf("\n");
	}
	return 0;			
}

//prints the menu
void print_menu(){
	printf("- To exit 0\n- To find a key 1\n- To remove a key 2\n- To print the tree 3\nEnter your choice : ");
}

//inserts given key to the tree
int insertN(terP *s,int a){

	terP newN;
	//if tree is empty insert at root
	if(*s==NULL){

		newN=(terP)malloc(sizeof(ternary));
		newN->data=a;
		newN->left=NULL;
		newN->middle=NULL;	
		newN->right=NULL;	
		*s=newN;
		
	}
	//if it is not empty find right place for key and insert
	else{
		if(a>pow((*s)->data,2)){
			insertN(&((*s)->right),a);
		}
		else if(a>(*s)->data && (a<pow((*s)->data,2) || a==pow((*s)->data,2))){
			insertN(&((*s)->middle),a);
		}
		else if(a<(*s)->data){
			insertN(&((*s)->left),a);
		}
	}
	return 1;
}
//removes key from the tree
terP removeN(terP s,int a){
	int v=0;
	terP h=s;
	terP parent;
	//to find key
	while(h->data!=a && h){
		if(a<h->data){
			parent=h;
			h=h->left;
		}
		if(a==h->data) break;
		if(a>h->data && (a<pow(h->data,2)) || a==pow(h->data,2)){
			parent=h;
			h=h->middle;
		}
		if(a==h->data) break;
		if(a>pow(h->data,2)){
			parent=h;
			h=h->right;
		}
		if(a==h->data) break;
	}

	//if key is not in the tree
	if(!h){
		printf("the key %d is not in the tree !\n",a);
		return NULL;
	}
	//if key is in the tree according to the cases remove it
	else{
		if(!h->right && !h->middle && !h->left){
			if(parent && v==0){
				if(parent->left) if(h->data==parent->left->data) parent->left=NULL;
				if(parent->right) if(h->data==parent->right->data) parent->right=NULL;
				if(parent->middle) if(h->data==parent->middle->data) parent->middle=NULL;
			}
			h=NULL;
			free(h);
		} 
		else{
			if(!h->right && !h->middle){
				v++;
				h->data=h->left->data;
				removeN(h->left,h->data);
				if(h->left) if(h->data==h->left->data) h->left=NULL;
				if(h->right) if(h->data==h->right->data) h->right=NULL;
				if(h->middle) if(h->data==h->middle->data) h->middle=NULL;								
			}
			else if(!h->left && !h->middle){
				v++;
				h->data=h->right->data;
				removeN(h->right,h->data);
				if(h->left) if(h->data==h->left->data) h->left=NULL;
				if(h->right) if(h->data==h->right->data) h->right=NULL;
				if(h->middle) if(h->data==h->middle->data) h->middle=NULL;				
			}
			else if(!h->right && !h->left){
				v++;
				terP mina=findMin(h->middle);
				h->data=mina->data;
				removeN(h->middle,h->data);
				if(h->left) if(h->data==h->left->data) h->left=NULL;
				if(h->right) if(h->data==h->right->data) h->right=NULL;
				if(h->middle) if(h->data==h->middle->data) h->middle=NULL;
			}
			else if(!h->right){
				v++;
				terP min=findMin(h->middle);
				h->data=min->data;
				removeN(h->middle,h->data);
				if(h->left) if(h->data==h->left->data) h->left=NULL;
				if(h->right) if(h->data==h->right->data) h->right=NULL;
				if(h->middle) if(h->data==h->middle->data) h->middle=NULL;
			}
			else if(!h->middle){
				v++;
				terP max=findMax(h->left);
				h->data=max->data;
				removeN(h->left,h->data);
				if(h->left) if(h->data==h->left->data) h->left=NULL;
				if(h->right) if(h->data==h->right->data) h->right=NULL;
				if(h->middle) if(h->data==h->middle->data) h->middle=NULL;
			}
			else if(!h->left || (h->right && h->middle && h->left)){
				v++;
				terP min=findMin(h->middle);
				h->data=min->data;
				int val=h->right->data;
				if(pow(h->data,2)<val){
					
				}
				else{
					terP mid=h->middle;
					while(mid->middle){
						mid=mid->middle;
					}	
					mid->middle=h->right;
					h->right=NULL;				
				}				
				removeN(h->middle,h->data);
				if(h->left) if(h->data==h->left->data) h->left=NULL;
				if(h->right) if(h->data==h->right->data) h->right=NULL;
				if(h->middle) if(h->data==h->middle->data) h->middle=NULL;
			}
		}
	}
	v=0;
	return h;	
}

//finds given key
terP findN(terP s,int a,int i){
	if(i==0)
	printf("\nSteps to find key from root :\n");
	if(!s){
		return NULL;
	}
	if(s->data==a){
		printf("The key %d is in %d . depth level.\n",a,i);
		return s;
	}
	else if(a>pow(s->data,2)){
		printf("right\n");
		i++;
		findN(s->right,a,i);
	}
	else if(a>s->data && (a<pow(s->data,2) || a==pow(s->data,2))){
		printf("middle\n");
		i++;
		findN(s->middle,a,i);
	}
	else if(a<s->data){
		printf("left\n");
		i++;
		findN(s->left,a,i);
	}	
}

//finds the maximum key 
terP findMax(terP s){
	terP p=s;
	terP max=NULL;
	while(p){
		max=p;
		s=p;
		p=p->right;
	}
	while(s){
		max=s;
		s=s->middle;		
	}

	return max;
}

//finds the minimum key
terP findMin(terP s){
	terP min=(terP)malloc(sizeof(ternary));
	min=s;
	while(s->left){
		min=s->left;
		s=s->left;
	}
	return min;
}

//prints the tree in preorder
void preorder(terP s){
	if(s){
		printf("%d\n",s->data);
		preorder(s->left);
		preorder(s->middle);
		preorder(s->right);
	}
}

//prints the tree in postorder
void postorder(terP s){
	if(s){
		postorder(s->left);
		postorder(s->middle);
		postorder(s->right);
		printf("%d\n",s->data);
	}
}

//prints the tree in inorder
void inorder(terP s){
	if(s){
		inorder(s->left);
		printf("%d\n",s->data);
		inorder(s->middle);
		inorder(s->right);
	}
}
