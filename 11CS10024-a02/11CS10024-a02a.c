#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define STEPS 1
#define  SIDE  10

typedef struct{
	float x;
	float y;
	float z;
}Point;

//edge formed by points indexed in cube.array[] as a  and b
typedef  struct 
{
  int a;
  int b;
}Edge;

//to store the screen coordinates of the cube
typedef  struct 
{
  float x;
  float y;
}Point2d;

//cube  array to store  8  corners and  array1 to store 12 edges of  a cube
typedef struct 
{
  Point  array[8]; 
  Edge   array1[12];
}Cube;





int main()
{
  Point centre,cam_pos;
  float x_min=10000,y_min=10000;
  int i;

  //get the centre position of the cube
   printf("\nEnter the coordinates of Centre of the cube: ");
   scanf("%f %f %f",&centre.x,&centre.y,&centre.z);
 
  // no point in cube should not be in the +z axis side
  if(centre.z>-SIDE*1.71/2){printf("\nError:no point in cube should not be in the +z axis side during rotation\n"); return 0;} 
  printf("\nEnter the coordinates of Camera : ");
  scanf("%f %f %f",&cam_pos.x,&cam_pos.y,&cam_pos.z);
    
   // the camera should be in the +ve z axis       
   if(cam_pos.z<0) {printf("\nError:the camera should be in the +ve z axis"); return 0;}   

  Cube cube; // contains the corner point coordinates end edges   

  //calculation of the coordinates of corners from the cente coordinates  
    for(i=0;i<8;i++)
    {
      if(i%4==1||i%4==2)
    	{cube.array[i].x=centre.x+(SIDE/2);}
      else
      {cube.array[i].x=centre.x-(SIDE/2);}

      if(i%4==2||i%4==3)
      {cube.array[i].y=centre.y+(SIDE/2); }
      else
      {cube.array[i].y=centre.y-(SIDE/2);}

      if(i/4==1)
      {cube.array[i].z=centre.z+(SIDE/2);}
      else
      {cube.array[i].z=centre.z-(SIDE/2);}

    
         
    }


   // sides : if cube.array1[i].a=x  and  cube.array1[i].b=y  points  cube.array[x] & cube.array[y]  is an edge 
    for(i=0;i<8;i++)
    {
      if(i%4!=3)
      {cube.array1[i].a=i;  cube.array1[i].b=i+1;}
      else  
      {cube.array1[i].a=i;  cube.array1[i].b=i-3;}
     
    }
    for(i=8;i<12;i++){
      cube.array1[i].a=i%4;
      cube.array1[i].b=i%4+4;
    } 
    
    Point array3[8];   //to store the current  rotation  position 
    Point2d array2[8]; //to store the screen points
    
    for(i=0;i<8;i++){
       array3[i].x=cube.array[i].x;
       array3[i].y=cube.array[i].y;
       array3[i].z=cube.array[i].z;
    }
    
   
    int k;
    float  rot_x,rot_y,rot_z;
    float  del_x,del_y,del_z;
    float  temp_x,temp_y,temp_z;
    printf("\nEnter  the rotaton angles:");
    scanf("%f%f%f",&rot_x,&rot_y,&rot_z);
     
    del_x=rot_x/STEPS;
    del_y=rot_y/STEPS;
    del_z=rot_z/STEPS;
    
    
    
    for(k=0;k<3*STEPS;k++)
    {
         for(i=0;i<8;i++)
          {
		   //rotation around x axis 
           if(k<STEPS){
                      temp_y=centre.y+(array3[i].y-centre.y)*cos(del_x)-(array3[i].z-centre.z)*sin(del_x);
                      temp_z=centre.z+(array3[i].y-centre.y)*sin(del_x)+(array3[i].z-centre.z)*cos(del_x);
                      array3[i].y=temp_y;
                      array3[i].z=temp_z;
                      } 
           //rotation around y axis 
           if(k>=STEPS && k<2*STEPS){
                      temp_z=centre.z+(array3[i].z-centre.z)*cos(del_y)-(array3[i].x-centre.x)*sin(del_y);
                      temp_x=centre.x+(array3[i].z-centre.z)*sin(del_y)+(array3[i].x-centre.x)*cos(del_y);
                      array3[i].z=temp_z;
                      array3[i].x=temp_x;
                      }
           //rotation around z axis 
           if(k>=2*STEPS && k<3*STEPS){
                      temp_x=centre.x+(array3[i].x-centre.x)*cos(del_z)-(array3[i].y-centre.y)*sin(del_z);
                      temp_y=centre.y+(array3[i].x-centre.x)*sin(del_z)+(array3[i].y-centre.y)*cos(del_z);
                      array3[i].x=temp_x;
                      array3[i].y=temp_y;
                      }
          }
           //Projection  
          for(i=0;i<8;i++)
          {
            array2[i].x=cam_pos.x-cam_pos.z*(array3[i].x-cam_pos.x)/(double)(array3[i].z-cam_pos.z);
            if(array2[i].x < x_min) x_min = array2[i].x; 
            array2[i].y=cam_pos.y-cam_pos.z*(array3[i].y-cam_pos.y)/(double)(array3[i].z-cam_pos.z);
            if(array2[i].y < y_min) y_min = array2[i].y;
            
          }
          //no points should have -ve x or y coordinates
          for(i=0;i<8;i++){
    	
    	    array2[i].x-=x_min;
    	    array2[i].y-=y_min;
    	
          }

          for(i=0;i<8;i++){
    	      array2[i].x*=100;//  magnifying 
    	      array2[i].y*=100;//  for clear image

    	      array2[i].x+=250;
    	      array2[i].y+=250;
          }    
     
 
        
   }
   
      FILE* graphic=fopen("11CS10024-a02a.svg","w");
        int u,v;
        fprintf(graphic,"<svg height=\"1000\" width=\"1000\">\n");
        fprintf(graphic,"<rect width=\"1000\" height=\"1000\" style=\"fill:rgb(255,255,255);stroke-width:3;stroke:rgb(0,0,0)\" />\n" );
        for(i=0;i<12;i++){
         u=cube.array1[i].a;
         v=cube.array1[i].b;
         fprintf(graphic," <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n",array2[u].x,array2[u].y,array2[v].x,array2[v].y);  
        }

      for(i=0;i<8;i++){
            fprintf(graphic, "<circle cx=\"%f\" cy=\"%f\" r=\"4\" stroke=\"black\"  fill=\"red\" />\n",array2[i].x,array2[i].y);
        }
  
      fprintf(graphic,"</svg>");
      fclose(graphic);
   
   return 0;
}
