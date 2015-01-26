#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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
   float distance;   	
}Face;


typedef struct {

  float x_component;
  float y_component;
  float z_component;
}Vector3D;



float distance(Point3D A,Vertex B)
{
	return(sqrt( pow(A.x-B.x,2)+pow(A.y-B.y,2)+pow(A.z-B.z,2) ));
}


int main()
{
	FILE * input=fopen("a05_ds12.obj","r");
	FILE * output=fopen("a05_ds12.svg","w");
	Vertex vertex[4240];
	Face  face[7236];
	char  c;
	int p=0,f=0;
    int index[4];
    int face_sorted[7236];
    Point3D cam_pos,light_pos;
    Point2D projection[4];
    int i,j,min;
    Face temp;
    int scaling_factor=50;
    Colour col; 
    double min_value = RAND_MAX * 1.0 ;
    double x_min= RAND_MAX * 1.0 ;
    double y_min= RAND_MAX * 1.0 ;
    printf("\nPlease Enter the coordinates of Camera : ");
    scanf("%f %f %f",&cam_pos.x,&cam_pos.y,&cam_pos.z);

    if(cam_pos.z<0) {printf("\nError:the camera should be in the +ve z axis"); return 0;}   

    // printf("Please enter the coordinates of light position \n");
    // scanf("%f %f %f",&light_pos.x,&light_pos.y,&light_pos.z);
    

    for(i=0;i<4240;i++)
	{

		fscanf(input,"%c%f%f%f\n",&c,&(vertex[i].x),&(vertex[i].y),&(vertex[i].z));
		vertex[i].z -=50;
	}
    printf("debg\n");
    for(i=0;i<7236;i++)
    {
    	fscanf(input,"%c%d%d%d%d\n",&c,&face[i].vertex_index[0],&face[i].vertex_index[1],&face[i].vertex_index[2],&face[i].vertex_index[3]);
    	index[0]=face[i].vertex_index[0]-1,index[1]=face[i].vertex_index[1]-1,index[2]=face[i].vertex_index[2]-1,index[3]=face[i].vertex_index[3]-1;
    	face[i].mid_point.x=(vertex[index[0]].x+vertex[index[1]].x+vertex[index[2]].x+vertex[index[3]].x)/4;
    	face[i].mid_point.y=(vertex[index[0]].y+vertex[index[1]].y+vertex[index[2]].y+vertex[index[3]].y)/4;
    	face[i].mid_point.z=(vertex[index[0]].z+vertex[index[1]].z+vertex[index[2]].z+vertex[index[3]].z)/4;
    	
    	if(face[i].mid_point.x==vertex[index[0]].x)  {face[i].colour=0;}
    	else if(face[i].mid_point.y==vertex[index[0]].y) {face[i].colour=1;}
    	else{face[i].colour=2;}
        
    	face[i].distance=distance(cam_pos,face[i].mid_point);
    	face_sorted[i]=i;
    }	
       

       
	for(i=0;i<=7235;i++)
	{

		min_value = RAND_MAX * 1.0 ;
		for(j=i;j<=7235;j++)
		{

			if(face[j].distance <= min_value)
			{
				min_value = face[j].distance;
				min = j;
			}


		}

		temp = face[i];
		face[i] = face[min];
		face[min] = temp;

	}
    
      
       fprintf(output,"<svg height=\"1000\" width=\"1000\">\n");
       fprintf(output,"<rect width=\"1000\" height=\"1000\" style=\"fill:rgb(255,255,255);stroke-width:3;stroke:rgb(0,0,0)\" />\n" );


        x_min = RAND_MAX * 1.0;
        y_min = RAND_MAX * 1.0;
        


    for(i=7235;i>=0;i--)
    {
    	for(j=0;j<4;j++)
    	{
    		projection[j].x= (double)cam_pos.x-cam_pos.z*(  vertex[face[i].vertex_index[j] -1].x-cam_pos.x)/(double)(vertex[face[i].vertex_index[j] - 1].z-cam_pos.z);
     		if(projection[j].x < x_min) x_min = projection[j].x; 
     		projection[j].y=(double)cam_pos.y-cam_pos.z*(vertex[face[i].vertex_index[j] - 1].y-cam_pos.y)/(double)(vertex[face[i].vertex_index[j] - 1].z-cam_pos.z);
     		if(projection[j].y < y_min) y_min = projection[j].y;

		}
	}	

   
	 for(i=7235;i>=0;i--)
    {
    	
    	for(j=0;j<4;j++)
    	{
    		projection[j].x= (double)cam_pos.x-cam_pos.z*(vertex[face[i].vertex_index[j] -1].x-cam_pos.x)/(double)(vertex[face[i].vertex_index[j] - 1].z-cam_pos.z);
     		projection[j].y=(double)cam_pos.y-cam_pos.z*(vertex[face[i].vertex_index[j]- 1].y-cam_pos.y)/(double)(vertex[face[i].vertex_index[j] - 1].z-cam_pos.z);
     		
		}
		

		for(j=0;j<4;j++){
    	
    	projection[j].x-=x_min;
    	projection[j].y-=y_min;
    	
    	
    	}
  

		
		for(j=0;j<4;j ++)
		{
    	
    	
    	projection[j].x*=scaling_factor; 
    	projection[j].y*=scaling_factor;
    	
      
    	projection[j].x+=150;
    	projection[j].y+=150;
    	
    	}   

    	  if(face[i].colour==0){ col.r=138,col.g=8,col.b=34;}
          else if(face[i].colour==1){ col.r=41,col.g=204,col.b=255;}
          else{ col.r=255,col.g=128,col.b=0;}

    fprintf(output,"<polygon points=\"%f,%f %f,%f %f,%f %f,%f\" style=\"fill:rgb(%d,%d,%d);stroke:black;stroke-width:1\" />\n",projection[0].x,projection[0].y,projection[1].x,projection[1].y,projection[2].x,projection[2].y,projection[3].x,projection[3].y,col.r,col.g,col.b); 
   }

       fprintf(output,"</svg>");
       fclose(output);
    return 0;
}
