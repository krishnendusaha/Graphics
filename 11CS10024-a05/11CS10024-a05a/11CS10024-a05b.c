#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
	float x;
	float y;
	float z;
}Vertex;

typedef struct{
	float x;
	float y;
	float z;
}Point3D;


typedef struct{
	float x;
	float y;
}Point2D;

typedef  struct{
   int r;
   int g;
   int b;
}Colour;

typedef struct 
{
   int vertex_index[4];
   int colour;
   Vertex mid_point;   	
}Face;


float distance(Point3D A,Vertex B)
{
	return(sqrt( pow(A.x-B.x,2)+pow(A.y-B.y,2)+pow(A.z-B.z,2) ));
}

int main()
{
	FILE * input=fopen("11CS10024-a05a.obj","r");
	FILE * output=fopen("11CS10024-a05b.svg","w");
	Vertex vertex[4240];
	Face  face[7236];
	char  c;
	int p=0,f=0;
    int index[4];
    int face_sorted[7236];
    Point3D cam_pos;
    
    int i,j,temp;
    for(i=0;i<4240;)
    {
    	
    	fscanf(input,"%c%f%f%f",&c,&vertex[i].x,&vertex[i].y,&vertex[i].z);
    	printf("%c%f%f%f\n",c,vertex[i].x,vertex[i].y,vertex[i].z);
    }
    printf("vertex \n");
    for(i=0;i<7236;i++)
    {
        printf("a\n");
        fscanf(input,"%c%d%d%d%d",&c,&face[i].vertex_index[0],&face[i].vertex_index[1],&face[i].vertex_index[2],&face[i].vertex_index[3]);
        index[0]=face[i].vertex_index[0]-1, index[1]=face[i].vertex_index[1]-1,index[2]=face[i].vertex_index[2]-1,index[3]=face[i].vertex_index[3]-1;
        
        face[i].mid_point.x=(vertex[index[0]].x+vertex[index[1]].x+vertex[index[2]].x+vertex[index[3]].x)/4;
    	face[i].mid_point.y=(vertex[index[0]].y+vertex[index[1]].y+vertex[index[2]].y+vertex[index[3]].y)/4;
    	face[i].mid_point.z=(vertex[index[0]].z+vertex[index[1]].z+vertex[index[2]].z+vertex[index[3]].z)/4;
    	
    	if(face[i].mid_point.x==vertex[index[0]].x)  {face[f].colour=0;}
    	else if(face[i].mid_point.y==vertex[index[0]].y) {face[f].colour=1;}
    	else{face[i].colour=2;}	
    	face_sorted[i]=i;
    }
     
    printf("faces\n"); 
     for (i = 0; i < 7235; i++)
        {
        	for(j=i+1;j<7236;j++)
        	{
               if(distance(cam_pos,face[i].mid_point)<distance(cam_pos,face[j].mid_point))
               {
                  temp=face_sorted[i];
                  face_sorted[i]=face_sorted[j];
                  face_sorted[j]=temp;
               }	
        	}
        }

       Point2D  projections[4];
       Colour colour;
       float x_min=10000,y_min=10000;
       
       fprintf(output,"<svg height=\"1000\" width=\"1000\">\n");
       fprintf(output,"<rect width=\"1000\" height=\"1000\" style=\"fill:rgb(255,255,255);stroke-width:3;stroke:rgb(0,0,0)\" />\n" );
       
       
        // for (i = 0; i <7236; i++)
        // {
        // 	 array2[i].x=cam_pos.x-cam_pos.z*(array3[i].x-cam_pos.x)/(double)(array3[i].z-cam_pos.z);
        //     if(array2[i].x < x_min) x_min = array2[i].x; 
        //     array2[i].y=cam_pos.y-cam_pos.z*(array3[i].y-cam_pos.y)/(double)(array3[i].z-cam_pos.z);
        //     if(array2[i].y < y_min) y_min = array2[i].y;
        // }
        // for (i = 0; i <7236; i++)
        // {
        //   j=face_sorted[i];
        //   index[0]=face[j].vertex_index[0]-1,index[1]=face[j].vertex_index[1]-1,index[2]=face[j].vertex_index[2]-1,index[3]=face[j].vertex_index[3]-1;
        //   if(face[j].colour==0){ colour.r=138,colour.g=8,colour.b=34;}
        //   else if(face[j].colour==1){ colour.r=41,colour.g=204,colour.b=255;}
        //   else{ colour.r=255,colour.g=128,colour.b=0;}

        for(i=0;i<7236;i--)
         {
         	index[0]=face[i].vertex_index[0]-1,index[1]=face[i].vertex_index[1]-1,index[2]=face[i].vertex_index[2]-1,index[3]=face[i].vertex_index[3]-1;
    	    for(j=0;j<4;j++)
    	   {
    		projections[j].x= (double)cam_pos.x-cam_pos.z*(  vertex[index[i]].x-cam_pos.x)/(double)(vertex[index[i]].z-cam_pos.z);
     		if(projections[j].x < x_min) x_min = projections[j].x; 
     		projections[j].y=(double)cam_pos.y-cam_pos.z*(  vertex[index[i]].y-cam_pos.y)/(double)(vertex[index[i]].z-cam_pos.z);
     		if(projections[j].y < y_min) y_min = projections[j].y;

		   }

        }

         for(i=0;i<7236;i--)
         {
         	index[0]=face[i].vertex_index[0]-1,index[1]=face[i].vertex_index[1]-1,index[2]=face[i].vertex_index[2]-1,index[3]=face[i].vertex_index[3]-1;
    	    for(j=0;j<4;j++)
    	    {
    		projections[j].x= (double)cam_pos.x-cam_pos.z*(  vertex[index[i]].x-cam_pos.x)/(double)(vertex[index[i]].z-cam_pos.z);
     		if(projections[j].x < x_min) x_min = projections[j].x; 
     		projections[j].y=(double)cam_pos.y-cam_pos.z*(  vertex[index[i]].y-cam_pos.y)/(double)(vertex[index[i]].z-cam_pos.z);
     		if(projections[j].y < y_min) y_min = projections[j].y;

		    }

		    for(j=0;j<4;j++){
    	
    	     projections[j].x-=x_min;
    	     projections[j].y-=y_min;
    	
    	    }
    	    printf("%d projections propered up\n",i );

		
		    for(j=0;j<4;j ++)
		    {
    	
    	//Multiplication enlarges the image,zoom in and zoom out.The parameters can be changed (for all projected points)
    	     projections[j].x*=100; 
    	     projections[j].y*=100;

        //Addition translates the image in the image plane.

    	     projections[j].x+=20;
    	     projections[j].y+=20;
    	
    	    } 

    	      fprintf(output,"<polygon points=\"%f,%f %f,%f %f,%f %f,%f\" style=\"fill:rgb(%d,%d,%d);stroke:black;stroke-width:1\" />\n",projections[0].x,projections[0].y,projections[1].x,projections[1].y,projections[2].x,projections[2].y,projections[3].x,projections[3].y,colour.r,colour.g,colour.b);    
         }
       fprintf(output,"</svg>");
       fclose(output);
return 0;
 }  
