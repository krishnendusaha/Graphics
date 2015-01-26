#include <iostream>
#include <set>
#include <stdio.h>
#include <fstream>

using namespace std;


typedef struct{
	int x;
	int y;
	int z;
}Centre;

typedef struct{
  float x;
  float y;
  float z;
}Vertices;

typedef struct{
	int v[4];
}Face;

struct Compare1
{
    bool operator () (const Vertices & p_lhs, const Vertices & p_rhs)
    {
    	
      
      if(p_lhs.z!=p_rhs.z)
      {return(p_lhs.z<p_rhs.z);}  
      else
      {
        if(p_lhs.y!=p_rhs.y)
        {return(p_lhs.y<p_rhs.y);}
        else
        {return(p_lhs.x<p_rhs.x);}
          
      }   
    }
} ;


int main()
{
  int vertex_index ;
  Vertices centre;
  Vertices v[8];
  Vertices m[6];
  int index[8];
  int i,j;
  set<Vertices,Compare1>  vertices ;
  set<Vertices,Compare1> face_mid_point;
  pair<set<Vertices>::iterator,bool> ret;
  FILE * f1=fopen("ds12.txt","r");
  FILE * f2=fopen("a05_ds12.obj","w");
 
  int p,q,r;
  for(j=0;j<1502;j++)
  {
     fscanf(f1,"%f %f %f",&centre.x,&centre.y,&centre.z);
      
      for(i=0;i<8;i++)
      {
        p=i%2; 
        v[i].x=(p==0)?(centre.x-0.5):(centre.x+0.5);
        p=(i>>1)%2;
        v[i].y=(p==0)?(centre.y-0.5):(centre.y+0.5);
        p=(i>>2)%2;
        v[i].z=(p==0)?(centre.z-0.5):(centre.z+0.5);
        vertices.insert(v[i]);
      }
  }
  for (set<Vertices>::const_iterator l = vertices.begin(); l != vertices.end(); ++l) {
    fprintf(f2, "v  %f %f %f  \n",l->x,l->y,l->z );
  }
  rewind(f1);
  for(j=0;j<1502;j++)
  {
      fscanf(f1,"%f %f %f",&centre.x,&centre.y,&centre.z);
      
      for(i=0;i<8;i++)
      {
        p=i%2; 
        v[i].x=(p==0)?(centre.x-0.5):(centre.x+0.5);
        p=(i>>1)%2;
        v[i].y=(p==0)?(centre.y-0.5):(centre.y+0.5);
        p=(i>>2)%2;
        v[i].z=(p==0)?(centre.z-0.5):(centre.z+0.5); 
        index[i]=1+distance(vertices.begin(),vertices.find(v[i]));

      }
    
        m[0].x=centre.x+0.5;
        m[0].y=centre.y;
        m[0].z=centre.z;    
        ret=face_mid_point.insert(m[0]);
         if(ret.second==true){
             fprintf(f2, "f %d %d %d %d\n",index[1],index[3],index[7],index[5] );
         } 

        m[1].x=centre.x-0.5;
        m[1].y=centre.y;
        m[1].z=centre.z;  
        ret=face_mid_point.insert(m[1]);
        if(ret.second==true){
          fprintf(f2, "f %d %d %d %d\n",index[4],index[6],index[2],index[0] );
        } 

        m[2].x=centre.x;
        m[2].y=centre.y+0.5;
        m[2].z=centre.z;  
        face_mid_point.insert(m[2]); 
        if(ret.second==true){
          fprintf(f2, "f %d %d %d %d\n",index[7],index[3],index[2],index[6] );
        }   

        m[3].x=centre.x;
        m[3].y=centre.y-0.5;
        m[3].z=centre.z;  
        ret=face_mid_point.insert(m[3]); 
        if(ret.second==true){
          fprintf(f2, "f %d %d %d %d\n",index[0],index[1],index[5],index[4] );
        }   
        
        m[4].x=centre.x;
        m[4].y=centre.y;
        m[4].z=centre.z+0.5; 
        ret=face_mid_point.insert(m[4]); 
        if(ret.second==true){
          fprintf(f2, "f %d %d %d %d\n",index[4],index[5],index[7],index[6] );
        }  
       
        m[5].x=centre.x;
        m[5].y=centre.y;
        m[5].z=centre.z-0.5; 
        ret=face_mid_point.insert(m[5]); 
        if(ret.second==true){
          fprintf(f2, "f %d %d %d %d\n",index[0],index[2],index[3],index[1] );
       
      }
  } 
   
 
     cout<<"\n***********" <<"Total Number of vertices : "vertices.size()<<"\n";

     cout<<"\n***********" <<"Total Number of faces : "face_mid_point.size()<<"\n";
  return 0;
  
}
