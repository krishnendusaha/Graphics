#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define STEPS 100
#define  SIDE  10
#define ka  0.01
#define kd  0.1
#define ks  0.5
#define c_att   0.3
#define I0  100
#define Ia  50
#define eta 1

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

typedef struct 
{
  float x_comp;
  float y_comp;
  float z_comp;
}Vector;


float mod_vect(Vector A)
{
  return (float)sqrt(A.x_comp*A.x_comp+A.y_comp*A.y_comp+A.z_comp*A.z_comp);
}


float dot_prod(Vector A,Vector B)
{
  float t=(A.x_comp*B.x_comp+A.y_comp*B.y_comp+A.z_comp*B.z_comp);
  t/=mod_vect(A)*mod_vect(B);
  return t;    
}


float  Find_intensity(Point point,Point view,Point light,Vector N)
{
   float i=0;
   // float eta=0.75;
   Vector L,V,R;

   L.x_comp=light.x-point.x;
   L.y_comp=light.y-point.y;
   L.z_comp=light.z-point.z;
   
   V.x_comp=view.x-point.x;
   V.y_comp=view.y-point.y;
   V.z_comp=view.z-point.z;
   
   float cosa=dot_prod(L,N);
   R.x_comp=2*L.x_comp*cosa-L.x_comp;
   R.y_comp=2*L.y_comp*cosa-L.y_comp;
   R.z_comp=2*L.z_comp*cosa-L.z_comp;

   float f_att=c_att/mod_vect(L)*mod_vect(L);
   i=ka*Ia;                               // for ambient lighting
   // printf("%f\n",i );
   i+=f_att*kd*I0*dot_prod(N,L);          // for diffusive lighting
   // printf("%f\n",i );
   float t=dot_prod(R,V);
   i+=ks*I0*pow(t,eta);                   // for specular lighting
   // printf("%f\n",i );
   return i;
}

 
void Find_normal(Point X,Point Y,Point Z,Vector *R)
{
  Vector U,V;
  U.x_comp=X.x-Y.x;
  U.y_comp=X.y-Y.y;
  U.z_comp=X.z-Y.z;

  V.x_comp=Z.x-Y.x;
  V.y_comp=Z.y-Y.y;
  V.z_comp=Z.z-Y.z;

  (*R).x_comp=U.y_comp*V.z_comp-U.z_comp*V.y_comp;
  (*R).y_comp=U.z_comp*V.x_comp-U.x_comp*V.z_comp;
  (*R).z_comp=U.x_comp*V.y_comp-U.y_comp*V.x_comp;
   

  return; 
}



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

  


//#####################CONFIGURE  THE CUBE #########################################################################

  Cube cube; // contains the corner point coordinates end edges   

  //calculation of the coordinates of corners from the cente coordinates  
  
  //POINTS********************************************************
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

   //FACES************************************************************   
   Face face[6];

    face[0].point[0]=4;
    face[0].point[1]=5;
    face[0].point[2]=6;
    face[0].point[3]=7;
    face[0].colour=0;

    // face[0].point[0]=6;
    // face[0].point[1]=5;
    // face[0].point[2]=4;
    // face[0].point[3]=7;
    // face[0].colour=0;


    face[1].point[0]=0;
    face[1].point[1]=1;
    face[1].point[2]=2;
    face[1].point[3]=3;
    face[1].colour=0;
    
    //  face[1].point[0]=0;
    // face[1].point[1]=1;
    // face[1].point[2]=2;
    // face[1].point[3]=3;
    // face[1].colour=0;
    
    face[2].point[0]=5;
    face[2].point[1]=1;
    face[2].point[2]=2;
    face[2].point[3]=6;
    face[2].colour=1;
     
    // face[2].point[0]=2;
    // face[2].point[1]=1;
    // face[2].point[2]=5;
    // face[2].point[3]=6;
    // face[2].colour=1;

    // face[3].point[0]=4;
    // face[3].point[1]=0;
    // face[3].point[2]=3;
    // face[3].point[3]=7;
    // face[3].colour=1;
   
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

    // face[4].point[0]=7;
    // face[4].point[1]=3;
    // face[4].point[2]=2;
    // face[4].point[3]=6;
    // face[4].colour=2;
    
    face[5].point[0]=5;
    face[5].point[1]=1;
    face[5].point[2]=0;
    face[5].point[3]=4;
    face[5].colour=2;

    // face[5].point[0]=1;
    // face[5].point[1]=0;
    // face[5].point[2]=4;
    // face[5].point[3]=5;
    // face[5].colour=2;
    

   //##############################################################Normals################################################# 
   // int c0,c1,c2,c3;
   //  Vector  S;
   //  for (i = 0; i < 6; ++i)
   //  {
   //           c0=face[i].point[0]; 
   //           c1=face[i].point[1]; 
   //           c2=face[i].point[2]; 
   //           c3=face[i].point[3];
   //           Find_normal(cube.array[c0],cube.array[c1],cube.array[c2],&S);
        
   //      printf("%d :%f %f %f \n",i,S.x_comp,S.y_comp,S.z_comp );

   //  }
   //  return 0;
   //##############################################################Normals################################################# 
   
  //#####################CONFIGURE  THE CUBE ######################################################################### 

    Point light_pos;
    printf("\nEnter position of light :");  
    scanf("%f%f%f",&light_pos.x,&light_pos.y,&light_pos.z);
  
    int k;
    float  rot_x,rot_y,rot_z;
    float  del_x,del_y,del_z;
    float  temp_x,temp_y,temp_z;
    printf("\nEnter  the rotaton angles:");
    scanf("%f%f%f",&rot_x,&rot_y,&rot_z);
     
    del_x=rot_x/STEPS;
    del_y=rot_y/STEPS;
    del_z=rot_z/STEPS;
    
    Point array3[8];   //to store the current  rotation  position 
    Point2d array2[8]; //to store the screen points
    
    for(i=0;i<8;i++){
       array3[i].x=cube.array[i].x;
       array3[i].y=cube.array[i].y;
       array3[i].z=cube.array[i].z;
    }
    


    //######################ROTATE AND PROJECT##################################################################################################
    for(k=0;k<3*STEPS;k++)
    {
         
        //################################################MODELLING BY ROTATION#########################################################
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
          
        //################################################MODELLING#########################################################


          //#############################PROJECTION###########################################################################
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


          //#############################PROJECTION###########################################################################   
          

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

                 printf("%d\n",k );
                 if(d_a<d_b)
                  {face_to_project[i]=2*i;   d[i]=d_a;   if(k>16 && k<25 ){printf("%f %f  %d\n",d_a,d_b,face_to_project[i]);} }
                 else if(d_a>d_b)
                  {face_to_project[i]=2*i+1; d[i]=d_b;   if(k>16 && k<25 ){printf("%f %f  %d\n",d_a,d_b,face_to_project[i]);} }
                 else
                  {face_to_project[i]=-1;                if(k>16 && k<25 ){printf("%f %f  %d\n",d_a,d_b,face_to_project[i]);} }
              
        
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
      
      float intensity[4],min_intensity=10000;  
      Vector N; 
      float x_min=10000,x_max=-10000;
      float y_min=10000,y_max=-10000;
      float p_x[4],p_y[4];

      FILE* graphic=fopen(fileName,"w");
      int e,c[4],col;
      fprintf(graphic,"<svg height=\"1000\" width=\"1000\">\n");
      fprintf(graphic,"<rect width=\"1000\" height=\"1000\" style=\"fill:rgb(255,255,255);stroke-width:3;stroke:rgb(0,0,0)\" />\n" );


      for(i=0;i<3;i++)
       {
          if(face_to_project[i]>=0) 
           {
        
             // c=face_to_project[i]; 
             // col=face[c].colour; 
             // c[0]=face[c].point[0]; 
             // c[1]=face[c].point[1]; 
             // c[2]=face[c].point[2]; 
             // c[3]=face[c].point[3]; 
            e=face_to_project[i]; 
            col=face[e].colour; 
            for(j=0;j<4;j++){ c[j]=face[e].point[j];} 
            
            for(j=0;j<4;j++){ x_min=(array2[c[j]].x<x_min)?array2[c[j]].x:x_min; }
            for(j=0;j<4;j++){ y_min=(array2[c[j]].y<y_min)?array2[c[j]].y:y_min; }
            for(j=0;j<4;j++){ x_max=(array2[c[j]].x>x_max)?array2[c[j]].x:x_max; }
            for(j=0;j<4;j++){ y_max=(array2[c[j]].y<y_max)?array2[c[j]].y:y_max; } 

            for(j=0;j<4;j++){ p_x[j]=(array2[c[j]].x-x_min)/(x_max-x_min)*100;  p_y[j]=(array2[c[j]].y-y_min)/(y_max-y_min)*100; }
           
            if(face_to_project[i]==0)   Find_normal(cube.array[c[2]],cube.array[c[1]],cube.array[c[0]],&N);
            if(face_to_project[i]==1)   Find_normal(cube.array[c[0]],cube.array[c[1]],cube.array[c[2]],&N);
            if(face_to_project[i]==2)   Find_normal(cube.array[c[2]],cube.array[c[1]],cube.array[c[0]],&N);         
            if(face_to_project[i]==3)   Find_normal(cube.array[c[0]],cube.array[c[1]],cube.array[c[2]],&N);         
            if(face_to_project[i]==4)   Find_normal(cube.array[c[2]],cube.array[c[1]],cube.array[c[0]],&N);         
            if(face_to_project[i]==5)   Find_normal(cube.array[c[0]],cube.array[c[1]],cube.array[c[2]],&N);         

            for(j=0;j<4;j++){ printf("%d ",c[j]); intensity[j]=Find_intensity(cube.array[c[j]],cam_pos,light_pos,N);} 
            for(j=0;j<4;j++){  if(min_intensity>intensity[j]){min_intensity=intensity[j];} }
            for(j=0;j<4;j++){  intensity[j]-=min_intensity; }

              
          // fprintf(graphic,"<polygon points=\"%f,%f %f,%f %f,%f %f,%f\" style=\"fill:rgb(%d,%d,%d);stroke:black;stroke-width:1\" />\n",array2[c[0]].x,array2[c[0]].y,array2[c[1]].x,array2[c[1]].y,array2[c[2]].x,array2[c[2]].y,array2[c[3]].x,array2[c[3]].y,colour[col].r,colour[col].g,colour[col].b); 
          fprintf(graphic,"<polygon points=\"%f,%f %f,%f %f,%f %f,%f\" style=\"fill:rgb(%d,%d,%d);stroke:black;stroke-width:1\" />\n",array2[c[0]].x,array2[c[0]].y,array2[c[1]].x,array2[c[1]].y,array2[c[2]].x,array2[c[2]].y,array2[c[3]].x,array2[c[3]].y,colour[col].r,colour[col].g,colour[col].b); 
          fprintf(graphic, "<defs>\n" );
          if(p_x[0]>p_y[2]){fprintf(graphic, "<linearGradient id=\"grad1\" x1=\"%f%c\" y1=\"%f%c\" x2=\"%f%c\" y2=\"%f%c\">\n",p_x[0],37,p_y[0],37,p_x[2],37,p_y[2],37); }
          else             {fprintf(graphic, "<linearGradient id=\"grad1\" x1=\"%f%c\" y1=\"%f%c\" x2=\"%f%c\" y2=\"%f%c\">\n",p_x[2],37,p_y[2],37,p_x[0],37,p_y[0],37); }
          fprintf(graphic, " <stop offset=\"0%c\" style=\"stop-color:rgb(255,255,255);stop-opacity:0.5\" />\n",37);
          fprintf(graphic, " <stop offset=\"100%c\" style=\"stop-color:rgb(0,0,0);stop-opacity:0.5\" />\n",37 );
          fprintf(graphic, " </linearGradient>\n" );
          if(p_x[1]>p_y[3]){fprintf(graphic, "<linearGradient id=\"grad2\" x1=\"%f%c\" y1=\"%f%c\" x2=\"%f%c\" y2=\"%f%c\">\n",p_x[1],37,p_y[1],37,p_x[3],37,p_y[3],37); }
          else             {fprintf(graphic, "<linearGradient id=\"grad2\" x1=\"%f%c\" y1=\"%f%c\" x2=\"%f%c\" y2=\"%f%c\">\n",p_x[3],37,p_y[3],37,p_x[1],37,p_y[1],37); }
          fprintf(graphic, " <stop offset=\"0%c\" style=\"stop-color:rgb(255,255,255);stop-opacity:0.5\" />\n",37);
          fprintf(graphic, " <stop offset=\"100%c\" style=\"stop-color:rgb(0,0,0);stop-opacity:0.5\" />\n",37 );
          fprintf(graphic, " </linearGradient>\n" );
          fprintf(graphic, "</defs>\n");
          fprintf(graphic, "<polygon points=\"%f,%f %f,%f %f,%f %f,%f\" fill=\"url(#grad1)\" />\n",array2[c[0]].x,array2[c[0]].y,array2[c[1]].x,array2[c[1]].y,array2[c[2]].x,array2[c[2]].y,array2[c[3]].x,array2[c[3]].y ); 
          fprintf(graphic, "<polygon points=\"%f,%f %f,%f %f,%f %f,%f\" fill=\"url(#grad2)\" />\n",array2[c[0]].x,array2[c[0]].y,array2[c[1]].x,array2[c[1]].y,array2[c[2]].x,array2[c[2]].y,array2[c[3]].x,array2[c[3]].y ); 
         

           }  
       } 
    
      fprintf(graphic,"</svg>");
      fclose(graphic);
   }


   //######################ROTATE AND PROJECT##################################################################################################
    
   return 0;
}


