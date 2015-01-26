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

  printf("\nEnter the coordinates of Camera : ");
  scanf("%f %f %f",&cam_pos.x,&cam_pos.y,&cam_pos.z);
    
    // the camera should be in the +ve z axis       
  if(cam_pos.z<0) {printf("\nError:the camera should be in the +ve z axis"); return 0;}   
    int i,j,temp;
    while((p+f)<=11475)
    {
    	//printf("++++++++++++++\n");
    	fscanf(input,"%c",&c);
    	if(c=='v')
    	{
           fscanf(input,"%f%f%f",&vertex[p].x,&vertex[p].y,&vertex[p].z);
           p++;
    	}
    	else if(c=='f')
    	{
    		//printf("--face %d %c \n.",f,c);
    		fscanf(input,"%d%d%d%d",&face[f].vertex_index[0],&face[f].vertex_index[1],&face[f].vertex_index[2],&face[f].vertex_index[3]);
    		index[0]=face[f].vertex_index[0]-1,index[1]=face[f].vertex_index[1]-1,index[2]=face[f].vertex_index[2]-1,index[3]=face[f].vertex_index[3]-1;
    		face[f].mid_point.x=(vertex[index[0]].x+vertex[index[1]].x+vertex[index[2]].x+vertex[index[3]].x)/4;
    		face[f].mid_point.y=(vertex[index[0]].y+vertex[index[1]].y+vertex[index[2]].y+vertex[index[3]].y)/4;
    		face[f].mid_point.z=(vertex[index[0]].z+vertex[index[1]].z+vertex[index[2]].z+vertex[index[3]].z)/4;
    		if(face[f].mid_point.x==vertex[index[0]].x)  {face[f].colour=0;}
    		else if(face[f].mid_point.y==vertex[index[0]].y) {face[f].colour=1;}
    		else{face[f].colour=2;}
    		face_sorted[f]=f;
    		f++;
            
    	}
    	else
    	{
           // printf("%d %d\n",c,(p+f));
    	}	
    }	
     
     // for(j=0;j<4240;j++){ printf("%d: %f %f %f\n",j,vertex[j].x,vertex[j].y,vertex[j].z );}
     // for(j=0;j<7236;j++){   
     //    printf("____________________________________________________________________\n");
     //    index[0]=face[j].vertex_index[0]-1,index[1]=face[j].vertex_index[1]-1,index[2]=face[j].vertex_index[2]-1,index[3]=face[j].vertex_index[3]-1;
     //    for(i=0;i<4;i++){printf("v %f %f %f \n",vertex[index[i]].x,vertex[index[i]].y,vertex[index[i]].z);}
     //        printf("m %f %f %f \n",face[j].mid_point.x,face[j].mid_point.y,face[j].mid_point.z);
     //    printf("%d\n",face[j].colour );
     //    printf("%d\n",face_sorted[j] );
     //  }

     //return 0; 
      // float distance[7235];
      // for (i = 0; i < 7235; i++){
      //     distance[i]=distance(cam_pos,face[i].mid_point);
      // }
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
     
       // for (i = 0; i < 7236; i++)
       // {
       //   printf("%d\n",face_sorted[i] );
       // } 
       // return 0;
       Point2D  array[4];
       Colour col;
       float x_min=10000,y_min=10000;

       fprintf(output,"<svg height=\"1000\" width=\"1000\">\n");
       fprintf(output,"<rect width=\"1000\" height=\"1000\" style=\"fill:rgb(255,255,255);stroke-width:3;stroke:rgb(0,0,0)\" />\n" );
        printf("************\n");
         for(i=0;i<7236;i++)
         {
           index[0]=face[i].vertex_index[0]-1,index[1]=face[i].vertex_index[1]-1,index[2]=face[i].vertex_index[2]-1,index[3]=face[i].vertex_index[3]-1;
           for(j=0;j<4;j++)
           {
             vertex[index[j]].z-=100;
             if(vertex[index[j]].z>=0 )     {printf("error****************\n");}
             array[j].x= (double)cam_pos.x-cam_pos.z*(  vertex[index[j]].x-cam_pos.x)/(double)(vertex[index[j]].z-cam_pos.z);
             if(array[j].x < x_min) x_min = array[j].x; 
             array[j].y=(double)cam_pos.y-cam_pos.z*(  vertex[index[j]].y-cam_pos.y)/(double)(vertex[index[j]].z-cam_pos.z);
             if(array[j].y < y_min) y_min = array[j].y;

           }

        }
        // printf("****************%f %f ****************\n",x_min,y_min );
        // return 0;
        for (i = 0; i <7236; i++)
        {
        	  //printf("%d\n",face_sorted[i] );
         // printf("**************************************************\n");
          j=face_sorted[i];
          index[0]=face[j].vertex_index[0]-1,index[1]=face[j].vertex_index[1]-1,index[2]=face[j].vertex_index[2]-1,index[3]=face[j].vertex_index[3]-1;
          if(face[j].colour==0){ col.r=138,col.g=8,col.b=34;}
          else if(face[j].colour==1){ col.r=41,col.g=204,col.b=255;}
          else{ col.r=255,col.g=128,col.b=0;}
        

          for(j=0;j<4;j++){
              
            
             if(vertex[index[j]].z>=0 )     {printf("error****************\n");}
          	  array[j].x=cam_pos.x-cam_pos.z*(vertex[index[j]].x-cam_pos.x)/(double)(vertex[index[j]].z-cam_pos.z);   	  
          	  array[j].y=cam_pos.y-cam_pos.z*(vertex[index[j]].y-cam_pos.y)/(double)(vertex[index[j]].z-cam_pos.z);          	                
          }  
           
            for(j=0;j<4;j++){
      
              array[j].x-=x_min;
              array[j].y-=y_min;
        
             }
          //printf("%d array propered up\n",i );

    
           for(j=0;j<4;j ++)
           {
      
         //Multiplication enlarges the image,zoom in and zoom out.The parameters can be changed (for all projected points)
             array[j].x*=100; 
             array[j].y*=100;

        //Addition translates the image in the image plane.

             array[j].x+=200;
             array[j].y+=200;
      
          } 
            fprintf(output,"<polygon points=\"%f,%f %f,%f %f,%f %f,%f\" style=\"fill:rgb(%d,%d,%d);stroke:black;stroke-width:1\" />\n",array[0].x,array[0].y,array[1].x,array[1].y,array[2].x,array[2].y,array[3].x,array[3].y,col.r,col.g,col.b); 

       }
       fprintf(output,"</svg>");
       fclose(output);
       // printf("***************\n");
       // printf("%d %d %d \n",face[0].colour.r,face[0].colour.g,face[0].colour.b );
       // printf("%f %f %f \n",vertex[face[0].vertex_index[0]].x,vertex[face[0].vertex_index[0]].y,vertex[face[0].vertex_index[0]].z );
       // printf("%f %f %f \n",vertex[face[0].vertex_index[1]].x,vertex[face[0].vertex_index[1]].y,vertex[face[0].vertex_index[1]].z );
       // printf("%f %f %f \n",vertex[face[0].vertex_index[2]].x,vertex[face[0].vertex_index[2]].y,vertex[face[0].vertex_index[2]].z );
       // printf("%f %f %f \n",vertex[face[0].vertex_index[3]].x,vertex[face[0].vertex_index[3]].y,vertex[face[0].vertex_index[3]].z );
       // printf("%f %f %f \n",face[0].mid_point.x,face[0].mid_point.y,face[0].mid_point.z );
      // printf("%f %f %f \n",vertex[4239].x,vertex[4239].y,vertex[4239].z ); 
      // printf("%d %d %d %d\n",face[0].vertex_index[0],face[0].vertex_index[1],face[0].vertex_index[2],face[0].vertex_index[3]);
      // printf("%d %d %d %d\n",face[7235].vertex_index[0],face[7235].vertex_index[1],face[7235].vertex_index[2],face[7235].vertex_index[3]);
     
   return 0;
}