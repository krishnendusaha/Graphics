#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data structure to hold the vertices indices and colour information 
typedef struct 
{
	int f_vertices[3];
	int colour;
}Face;

//seeks the text file pointer to the  next
int  seek_next_line(FILE *f)
{
  char c;
  while((c=fgetc(f))!='\n')     // while you don't get a '\n' keep on reading  
  {
    if(feof(f))  return  1;     // if end of file comes  break the loop   return 1
  }   
  return 0;                     
}


int main(int argc,char** argv)
{
  FILE * f1,* f2;
  if(argc==1)      //if  no input file  is given as argv[1]  take  apple.obj  as  default input file  
  {
    f1=fopen("apple.obj","r");
    f2=fopen("apple_colour.obj","w");  
     printf("Output : apple_colour.obj\n" );
  }  
  else             //input file is given as argv[1] 
  {

    char * out=(char*)malloc(sizeof(char)*20);
    strncpy(out,argv[1],strlen(argv[1])-4);
    strcat(out,"_colour.obj");
    f1=fopen(argv[1],"r");
    f2=fopen(out,"w");  
    printf("Output : %s\n",out );
  }

  int v_count=0,f_count=0,i=0,p,q,r;
  float d,e,f;
  int *vertex_deg;
  char c;

  // This while loop  calculates   
  //                              - 1) the degree of vertices (no.  of edges incident on it )
  //                              - 2) counts no. of vertices
  //                              - 3) counts no. of faces   
    while(1)
    {
  	   if(feof(f1)) { break; } 
  	   c=fgetc(f1);
       
       if(c=='v')                 // if line starts with 'v'
   	   {
   		  v_count++;                // increment the  vertex counter
   		  if(seek_next_line(f1)) {  break;}  //  seek_next_line  seeks line pointer to the next line  ,
                                           // if  seek_next_line returns 1 that means end of file is reached  break the loop  
       }	
       else if(c=='f')            // if line starts with 'f'
       {
       	if(f_count==0){vertex_deg=(int*)malloc(sizeof(int)*(v_count+1));}  // if first face is read  vertex reading is finished so we may allocate a array  vertex_deg to store the degrees of vertices  
       	fscanf(f1,"%d %d %d ",&p,&q,&r);      //  read the vertices tha t makes the face
        
        vertex_deg[p]+=1;                     //  increment vertex degree if a vertex is present in a face
        vertex_deg[q]+=1;                     //  as no . of faces  the point is present is equal to its degree
        vertex_deg[r]+=1;
     	  f_count++;                            // increment face count
       }
       else                                   // if line starts with anythhing other than 'v'/'f' 
       {
         if(seek_next_line(f1)) {  break;}	  //  go to the next line 
                                              // if  seek_next_line returns 1 that means end of file is reached  break the loop    
       }
     
   }


   Face *faces=(Face*)malloc(sizeof(Face)*f_count);   //Allocate memory to store face  data  
   f_count=0;                                         // reset f_count used as index to a face 
   int min,max,min_t,max_t;

   rewind(f1);                                // brings the file pointer from the end to the beginning 

   fprintf(f2,"mtllib ./color.mtl\n" );       // print the mtl file name in out put file 

  // This while loop     
  //                              - 1) store the vertex indices of each face in face array
  //                              - 2) give colour info depending on maximum and minimum degrees of vertices of triangle
  //                                


   while(1) 
   {
    
       if(feof(f1)) { break; } 
       c=fgetc(f1);
    
      if(c=='v')                   // if line starts with 'v'
      {
      	fscanf(f1,"%f %f %f ",&d,&e,&f);      // read vertex from input file 
   		  fprintf(f2, "v %f %f %f \n",d,e,f );  // print vertices in output file

      }  
      else if(c=='f')
      {
        fscanf(f1,"%d %d %d ",&p,&q,&r);
        faces[f_count].f_vertices[0]=p;     // store  vertices indexes of face with index f_count 
        faces[f_count].f_vertices[1]=q;
        faces[f_count].f_vertices[2]=r;
        
        // calculate max degree  of face[f_count]
        max_t=(vertex_deg[p]>=vertex_deg[q])?vertex_deg[p]:vertex_deg[q];
        max=vertex_deg[r]>max_t?vertex_deg[r]:max_t;
        // calculate min degree  of face[f_count]
        min_t=(vertex_deg[p]<=vertex_deg[q])?vertex_deg[p]:vertex_deg[q];
        min=vertex_deg[r]<min_t?vertex_deg[r]:min_t;
        
        //if (max-min)==0         colour it green(1)
        //            >0 && <=2   colour it yellow(2)
        //            >2          colour it red(3)

        if(max==min) {faces[f_count].colour=1;}
        else if(max-min<=2) {faces[f_count].colour=2;}
        else { faces[f_count].colour=3; }         
        f_count++;
      }
      else
      {
        if(seek_next_line(f1)) {  break;}
      }
    
   }
     

    fprintf(f2, "usemtl green\n");   
   for(i=0;i<f_count;i++)            // prints the faces with green colour 
   {
    if(faces[i].colour==1) { fprintf(f2, "f %d %d %d \n",faces[i].f_vertices[0],faces[i].f_vertices[1],faces[i].f_vertices[2] );}
   }
    
  fprintf(f2, "usemtl  yellow\n");    // prints the faces with yellow colour
  for(i=0;i<f_count;i++)
   {
    if(faces[i].colour==2) { fprintf(f2, "f %d %d %d \n",faces[i].f_vertices[0],faces[i].f_vertices[1],faces[i].f_vertices[2] );}
   }
  
  fprintf(f2, "usemtl red\n");        // prints the faces with red  colour
  for(i=0;i<f_count;i++)
   {
    if(faces[i].colour==3) { fprintf(f2, "f %d %d %d \n",faces[i].f_vertices[0],faces[i].f_vertices[1],faces[i].f_vertices[2] );}
   }

     fclose(f1);  // close  input  file  
     fclose(f2);  // close  output file
   	return 0;
}