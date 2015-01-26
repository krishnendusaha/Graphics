#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define STEPS 100
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


typedef struct 
{
  int point[4];
  int colour;  //  0= #Ox8a0822  1= #Ox2eccff  2=#Oxff8000    
}Face;


typedef  struct{
   int r;
   int g;
   int b;
}Colour;


int main()
{
  Colour  colour[3];
  colour[0].r=138,colour[0].g=8,colour[0].b=34;
  colour[1].r=41,colour[1].g=204,colour[1].b=255;
  colour[2].r=255,colour[2].g=128,colour[2].b=0;
  Point centre,cam_pos;
  float x_min=10000,y_min=10000;
  int i;

  //get the centre position of the cube
   printf("\nEnter the coordinates of Centre of the cube: ");
   scanf("%f %f %f",&centre.x,&centre.y,&centre.z);
 
  // no point in cube should not be in the +z axis side
  if(centre.z>-SIDE*1.71/2){printf("\nError:no point in cube should not be in the +z axis side  during rotaton\n"); return 0;} 
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
    
   
    Point array3[8];   //to store the current  rotation  position 
    Point2d array2[8]; //to store the screen points
    
    for(i=0;i<8;i++){
       array3[i].x=cube.array[i].x;
       array3[i].y=cube.array[i].y;
       array3[i].z=cube.array[i].z;
    }
    
   Face face[6];

    face[0].point[0]=4;
    face[0].point[1]=5;
    face[0].point[2]=6;
    face[0].point[3]=7;
    face[0].colour=0;

    face[1].point[0]=0;
    face[1].point[1]=1;
    face[1].point[2]=2;
    face[1].point[3]=3;
    face[1].colour=0;
    
    face[2].point[0]=5;
    face[2].point[1]=1;
    face[2].point[2]=2;
    face[2].point[3]=6;
    face[2].colour=1;

    face[3].point[0]=4;
    face[3].point[1]=0;
    face[3].point[2]=3;
    face[3].point[3]=7;
    face[3].colour=1;

    face[4].point[0]=2;
    face[4].point[1]=3;
    face[4].point[2]=7;
    face[4].point[3]=6;
    face[4].colour=2;


    face[5].point[0]=5;
    face[5].point[1]=1;
    face[5].point[2]=0;
    face[5].point[3]=4;
    face[5].colour=2;

  

    int k;
    float  rot_x,rot_y,rot_z;
    float  del_x,del_y,del_z;
    float  temp_x,temp_y,temp_z;
    printf("\nEnter  the rotaton angles:\n");
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
          int j;
          int face_to_project[3]={-1,-1,-1};
          float x_a,x_b,y_a,y_b,z_a,z_b,d_a,d_b;
          float d[3];
         


          //Algo:out of two parallely opposite planes in the only one plane may be seen at any particular moment
          //finding the distance from the viewer position to the centre of each  face  
          //the face with less distance from viewer may possibly be seen out of those two parallely opposite faces 
          //Now those three selected faces out of the six are printed in decending order of distances  
          for(i=0;i<3;i++){
                  x_a=0,x_b=0,y_a=0,y_b=0,z_a=0,z_b=0;
                 for(j=0;j<4;j++){
                    int t1=face[2*i].point[j];
                    int t2=face[2*i+1].point[j];
                    x_a+=array3[t1].x;
                    x_b+=array3[t2].x;
                    y_a+=array3[t1].y;
                    y_b+=array3[t2].y;
                    z_a+=array3[t1].z;
                    z_b+=array3[t2].z;
                 }

                 x_a/=4;
                 y_a/=4;
                 z_a/=4;

                 x_b/=4;
                 y_b/=4;
                 z_b/=4;
                 
                 x_a-=cam_pos.x;
                 y_a-=cam_pos.y;
                 z_a-=cam_pos.z;

                 x_b-=cam_pos.x;
                 y_b-=cam_pos.y;
                 z_b-=cam_pos.z;


                 d_a=sqrt(pow(x_a,2)+pow(y_a,2)+pow(z_a,2));
                 d_b=sqrt(pow(x_b,2)+pow(y_b,2)+pow(z_b,2));

        
                 if(d_a<d_b)
                  {face_to_project[i]=2*i;   d[i]=d_a;}
                 else if(d_a>d_b)
                  {face_to_project[i]=2*i+1; d[i]=d_b;}
                 else
                  {face_to_project[i]=-1;}

        
          }  

          int t=0; 
          for(i=0;i<2;i++)
          { 
            for(j=i+1;j<3;j++)
            {
              if(d[i]<d[j])
              {t=face_to_project[j]; face_to_project[j]=face_to_project[i]; face_to_project[i]=t;  } 
            }
          }  

        //making the svg filename    
        char*  fileName=(char*)malloc(sizeof(char)*15);
        strcpy(fileName,"frame");
        char*  fileNo=(char*)malloc(sizeof(char)*5);
        snprintf(fileNo,sizeof(fileNo),"%d",k+100);
        strcat(fileName,fileNo);
        strcat(fileName,".svg");
 
      FILE* graphic=fopen(fileName,"w");
      int c,c0,c1,c2,c3,col;
      fprintf(graphic,"<svg height=\"1000\" width=\"1000\">\n");
      fprintf(graphic,"<rect width=\"1000\" height=\"1000\" style=\"fill:rgb(255,255,255);stroke-width:3;stroke:rgb(0,0,0)\" />\n" );


      for(i=0;i<3;i++)
       {
          if(face_to_project[i]>=0) 
           {
        
             c=face_to_project[i]; 
             col=face[c].colour; 
             c0=face[c].point[0]; 
             c1=face[c].point[1]; 
             c2=face[c].point[2]; 
             c3=face[c].point[3]; 
           fprintf(graphic,"<polygon points=\"%f,%f %f,%f %f,%f %f,%f\" style=\"fill:rgb(%d,%d,%d);stroke:black;stroke-width:1\" />\n",array2[c0].x,array2[c0].y,array2[c1].x,array2[c1].y,array2[c2].x,array2[c2].y,array2[c3].x,array2[c3].y,colour[col].r,colour[col].g,colour[col].b); 
           }  
       } 
    
      fprintf(graphic,"</svg>");
      fclose(graphic);
   }
   return 0;
}



