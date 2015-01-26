#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct{
	int x;
	int y;
	int z;
}Point;

typedef struct node{
   Point p;
   struct node * next;
}Node;


void enqueue(Node **q,Point p)
{	
	// printf("enq\n");
	Node* t=(Node*)malloc(sizeof(Node));
	t->p.x=p.x;
	t->p.y=p.y;
	t->p.z=p.z;
	t->next=NULL;
    Node *iter=*q;
//	printf("debg\n");
    if(*q==NULL){*q=t;}
    else{
    	while(iter->next!=NULL)
        {
  // 	      printf("abc\n");
   	      iter=iter->next;

        } 
        iter->next=t;
    }

   // printf("\n\n\n");
}

void  dequeue(Node **q)
{
   //printf("debg1\n");	
   Node *t=*q;	
   //printf("debg2\n");
   *q=t->next;
   //printf("debg3\n");
   free(t);
}


int main()
{
	int i,j,k,l;
	Point  p[1502],min,max;
	min.x=10000,min.y=10000,min.z=10000;
	max.x=-10000,max.y=-10000,max.z=-10000;
	FILE * f1=fopen("ds12.txt","r");
	for(i=0;i<1502;i++)
	{
		fscanf(f1,"%d %d %d",&p[i].x,&p[i].y,&p[i].z);
		if(p[i].x<min.x){min.x=p[i].x;}
		if(p[i].y<min.y){min.y=p[i].y;}
		if(p[i].z<min.z){min.z=p[i].z;}
        
        if(p[i].x>max.x){max.x=p[i].x;}
		if(p[i].y>max.y){max.y=p[i].y;}
		if(p[i].z>max.z){max.z=p[i].z;}
        


	}
  
  int a[25][25][25]={0};
  int count=0;
  for(i=0;i<1502;i++)
  {
    j=p[i].x+12;
    k=p[i].y+12;
    l=p[i].z+12;

    a[j][k][l]=1;
  }

   Node * q=NULL;
    
    enqueue(&q,p[0]);
    // printf("%d \n",(int)q );
    // enqueue(&q,p[1]);
    // printf("%d \n",(int)q->next );
    // enqueue(&q,p[2]);
    // printf("%d \n",(int)q->next->next );
   
   // Node *iter=q;
   // while(iter!=NULL){printf("***%d %d %d \n",iter->p.x,iter->p.y,iter->p.z ); iter=iter->next;}
  
   // dequeue(&q);
   // dequeue(&q);
   // iter=q;
   // while(iter!=NULL){printf("***%d %d %d ***\n",iter->p.x,iter->p.y,iter->p.z ); iter=iter->next;}
    int x,y,z,x1,y1,z1,f;
    int face[6]={1};
    int vertex[6]={1};
   while(q!=NULL)
   {
   	  x=q->p.x+12;
   	  y=q->p.y+12;
   	  z=q->p.z+12;

   for(i=-1;i<=1;i++)
   {
   	for(j=-1;j<=1;j++)
   	{
   	  for(k=-1;k<=1;k++)
   	  {
   	  	x1=x+i,y1=y+i,z1=z+i;
   	  	if(x1>=0 && x1<=24 && y1>=0 && y1<=24 && z1>=0 && z1<=24){  
          if(a[x1][y1][z1]==1){f=i+3*j+9*k; 
          	switch(f){
          		case   3: f[5]=0;  v[2]=v[3]=v[7]=v[6]=0; break;
          		case  -3: f[4]=0;  v[0]=v[1]=v[5]=v[4]=0; break;
          		case   1: f[3]=0;  v[1]=v[2]=v[6]=v[5]=0; break;
          		case  -1: f[2]=0;  v[0]=v[4]=v[7]=v[3]=0; break;
          		case   9: f[1]=0;  v[4]=v[5]=v[6]=v[7]=0; break;
          		case  -9: f[0]=0;  v[0]=v[3]=v[2]=v[1]=0; break;
          		
          		case -12: v[0]=v[1]=0; break;
          	    case  -2: v[1]=v[5]=0; break;
          	    case   6: v[5]=v[4]=0; break;
          	    case  -4: v[4]=v[0]=0; break;

          	    case -10: v[3]=v[6]=0; break;
          	    case  -8: v[1]=v[2]=0; break;
          	    case  10: v[6]=v[5]=0; break;
          	    case   8: v[7]=v[4]=0; break;

          	    case  -6: v[0]=v[1]=0; break;
          	    case   4: v[0]=v[1]=0; break;
          	    case  12: v[0]=v[1]=0; break;
          	    case   2: v[0]=v[1]=0; break;
   
   				
   				case  -7: v[3]=0; break;
                case  -5: v[2]=0; break;
				case -11: v[1]=0; break;
				case -13: v[0]=0; break;
				case  11: v[7]=0; break;
                case  13: v[6]=0; break;
                case   7: v[5]=0; break;
                case   5: v[4]=0; break;

          	}

          	a[x1][y1][z1]=2;
          }
   	  	}
   	  }
   	}
   }


   }

  
   return 0;

}
