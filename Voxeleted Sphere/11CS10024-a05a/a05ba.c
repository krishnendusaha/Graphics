#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*structure to hold a 3d point */
typedef struct{
	double x;
	double y;
	double z;
}Point3D;

/*structure to hold the 2d point projected in XY plane */
typedef struct{
	double x;
	double y;

}Point2D;

typedef struct 
{
	int  corners[4];
	Point3D midpoint;
	double distance;
}Face;
typedef struct 
{
	int r;
	int b;
	int g;
}color;

typedef struct {

  double x_component;
  double y_component;
  double z_component;
}Vector3D;

  /*Illumination Parameters */
  

  
  Vector3D l,n,r,s,cross_1,cross_2;
  Point3D camera_position;






double Calculate_distance(double a,double b,double c,double x,double y,double z)
{

    double temp;
    temp = sqrt((a-x)*(a-x) + (b-y)*(b-y) + (c-z)*(c-z)) ;
    return temp;

}

void Calculate_intensity(double light_x,double light_y,double light_z,double a_x,double a_y,double a_z,double b_x,double b_y,double b_z,double c_x,double c_y,double c_z,double d_x,double d_y,double d_z,double* p)
{



    double l_length,n_length,s_length;
    double Ka = 0;
    double Ia = 100;
    double f  = 1;
    double Kd = 0.7;
    double Io = 100;
    double Ks = 0.7;
    double eta = 2 ;
    double theta;
    double phai ;
    double gamma ;
    int i;
    //printf("a x %lf\n",a_x);
    cross_1.x_component = c_x - b_x;
    cross_1.y_component = c_y - b_y;
    cross_1.z_component = c_z - b_z;

    cross_2.x_component = d_x - a_x;
    cross_2.y_component = d_y - a_y;
    cross_2.z_component = d_z - a_z;
    printf("cross1  %lf i + %lf j + %lf k \n",cross_1.x_component,cross_1.y_component,cross_1.z_component );
    printf("cross2  %lf i + %lf j + %lf k \n",cross_2.x_component,cross_2.y_component,cross_2.z_component );
    n.x_component = cross_1.y_component * cross_2.z_component - cross_1.z_component * cross_2.y_component ;
    n.y_component = (cross_1.x_component * cross_2.z_component - cross_1.z_component * cross_2.x_component) * -1 ;
    n.z_component = cross_1.x_component * cross_2.y_component - cross_1.y_component*cross_2.x_component ;
    n.x_component *= -1;
    n.y_component *= -1;
    n.z_component *= -1;
 	printf("n - %lf i + %lf j + %lf k \n",n.x_component,n.y_component,n.z_component );
    n_length = Calculate_distance(n.x_component,n.y_component,n.z_component,0,0,0);
    printf("n_length - %lf\n",n_length );
    //for point a ---->>
    l.x_component = light_x - a_x ;
    l.y_component = light_y - a_y ;
    l.z_component = light_z - a_z ;

    l_length = Calculate_distance(l.x_component,l.y_component,l.z_component,0,0,0);
    printf("l_length - %lf\n",l_length );

    s.x_component = camera_position.x - a_x;
    s.y_component = camera_position.y - a_y;
    s.z_component = camera_position.z - a_z;

    s_length = Calculate_distance(s.x_component,s.y_component,s.z_component,0,0,0);
    printf("s_length - %lf\n",s_length );

    theta = acos((l.x_component * n.x_component + l.y_component*n.y_component + l.z_component*n.z_component )/(l_length * n_length ) );
    gamma = acos((l.x_component * s.x_component + l.y_component*s.y_component + l.z_component*s.z_component)/(l_length*s_length)  );

    phai = gamma - 2*theta ;

    p[0] = (double)Ka * Ia + (f/(pow(l_length,2)) ) * (  (Kd*Io*cos(theta)) + (Ks*Io*pow(cos(phai),2)) ) ;

    // for b
    
    l.x_component = light_x - b_x ;
    l.y_component = light_y - b_y ;
    l.z_component = light_z - b_z ;

    l_length = Calculate_distance(l.x_component,l.y_component,l.z_component,0,0,0);


    s.x_component = camera_position.x - b_x;
    s.y_component = camera_position.y - b_y;
    s.z_component = camera_position.z - b_z;

    s_length = Calculate_distance(s.x_component,s.y_component,s.z_component,0,0,0);


    theta = acos((l.x_component * n.x_component + l.y_component*n.y_component + l.z_component*n.z_component )/(l_length * n_length ) );
    gamma = acos((l.x_component * s.x_component + l.y_component*s.y_component + l.z_component*s.z_component)/(l_length*s_length)  );

    phai = gamma - 2*theta ;

    p[1] = Ka*Ia + (f/(pow(l_length,2)) ) * (  (Kd*Io*cos(theta)) + (Ks*Io*pow(cos(phai),2)) ) ;

    //for c
    l.x_component = light_x - c_x ;
    l.y_component = light_y - c_y ;
    l.z_component = light_z - c_z ;

    l_length = Calculate_distance(l.x_component,l.y_component,l.z_component,0,0,0);


    s.x_component = camera_position.x - c_x;
    s.y_component = camera_position.y - c_y;
    s.z_component = camera_position.z - c_z;

    s_length = Calculate_distance(s.x_component,s.y_component,s.z_component,0,0,0);


    theta = acos((l.x_component * n.x_component + l.y_component*n.y_component + l.z_component*n.z_component )/(l_length * n_length ) );
    gamma = acos((l.x_component * s.x_component + l.y_component*s.y_component + l.z_component*s.z_component)/(l_length*s_length)  );

    phai = gamma - 2*theta ;

    p[2] = Ka*Ia + (f/(pow(l_length,2)) ) * (  (Kd*Io*cos(theta)) + (Ks*Io*pow(cos(phai),2)) ) ;

    //for d

    l.x_component = light_x - d_x ;
    l.y_component = light_y - d_y ;
    l.z_component = light_z - d_z ;

    l_length = Calculate_distance(l.x_component,l.y_component,l.z_component,0,0,0);


    s.x_component = camera_position.x - d_x;
    s.y_component = camera_position.y - d_y;
    s.z_component = camera_position.z - d_z;

    s_length = Calculate_distance(s.x_component,s.y_component,s.z_component,0,0,0);


    theta = acos((l.x_component * n.x_component + l.y_component*n.y_component + l.z_component*n.z_component )/(l_length * n_length ) );
    gamma = acos((l.x_component * s.x_component + l.y_component*s.y_component + l.z_component*s.z_component)/(l_length*s_length)  );

    phai = gamma - 2*theta ;

    p[3] = Ka*Ia + (f/(pow(l_length,2)) ) * (  (Kd*Io*cos(theta)) + (Ks*Io*pow(cos(phai),2) )) ;

    printf("They are %lf %lf %lf %lf\n",p[0],p[1],p[2],p[3]);
  //  for(i=0;i<4;i++)
   // 	if(p[i] < 0){printf("blah\n"); exit(0);}
   // exit(0);
    return;

}

calculate_max_min(double x,double a,double y,double b,double z,double c,double t,double d,double* x_max,double* x_min,double *y_max,double *y_min)
{

  if(x > *x_max)
    *x_max = x;
  if(x < *x_min)
    *x_min = x;
  if(y > *x_max)
    *x_max = y;
  if(y < *x_min)
    *x_min = y;
  if(z > *x_max)
    *x_max = z;
  if(z < *x_min)
    *x_min = z;
  if(t > *x_max)
    *x_max = t;
  if(t < *x_min)
    *x_min = t;
  if(a > *y_max)
    *y_max = a;
  if(a < *y_min)
    *y_min = a;
  if(b > *y_max)
    *y_max = b;
  if(b < *y_min)
    *y_min = b;
  if(c > *y_max)
    *y_max = c;
  if(c < *y_min)
    *y_min = c;
  if(d > *y_max)
    *y_max = d;
  if(d < *y_min)
    *y_min = d;

  return;
}


int main()
{

	color face_color;
	Point3D light_position;
	Point3D Vertices[4240];
	Point3D light_point;
	Point2D projections_corners[4];
	int Vertices_iterator = 0;
	int scaling_factor;
	
	Face Faces[7236],temp;
	int Face_iterator = 0;
	int i,j,min;
	double min_value = RAND_MAX * 1.0 ;
	double x_min= RAND_MAX * 1.0 ;
    double y_min= RAND_MAX * 1.0 ; 
    double PASE[4],PASE_X[4],PASE_Y[4];
	char c;
	FILE* reader = fopen("a05_ds12.obj","r");
	FILE* graphic_svg=fopen("a05_ds12.svg","w");
	printf("Please enter the coordinates of the camera position\n");
	scanf("%lf",&camera_position.x);
	scanf("%lf",&camera_position.y);
	scanf("%lf",&camera_position.z);
	printf("Please enter the coordinates of light position \n");
  	scanf("%lf",&light_point.x);
  	scanf("%lf",&light_point.y);
  	scanf("%lf",&light_point.z);
  	printf("Please enter scaling factor (100 is standard)\n");
  	scanf("%d",&scaling_factor);
  	double percentage_x_min= RAND_MAX * 1.00;
  	double percentage_x_max = RAND_MAX *-1.00 ;
  	double percentage_y_min= RAND_MAX * 1.00;
  	double percentage_y_max = RAND_MAX *-1.00 ;
  
	for(i=1;i<=4240;i++)
	{

		fscanf(reader,"%c %lf %lf %lf\n",&c,&(Vertices[i-1].x),&(Vertices[i-1].y),&(Vertices[i-1].z));
		Vertices[i-1].z -= 50.0;

	}


	for(i=4241;i<=11476;i++)
	{

		fscanf(reader,"%c %d %d %d %d\n",&c,&(Faces[i-4241].corners[0]) ,&(Faces[i-4241].corners[1]) , &(Faces[i-4241].corners[2]) , &(Faces[i-4241].corners[3]) );

		Faces[i-4241].midpoint.x = 0.25*(Vertices[Faces[i-4241].corners[0] - 1].x + Vertices[Faces[i-4241].corners[1] -1].x + Vertices[Faces[i-4241].corners[2] - 1 ].x + Vertices[Faces[i-4241].corners[3] - 1].x );
		Faces[i-4241].midpoint.y = 0.25*(Vertices[Faces[i-4241].corners[0] - 1].y + Vertices[Faces[i-4241].corners[1] -1].y + Vertices[Faces[i-4241].corners[2] - 1 ].y + Vertices[Faces[i-4241].corners[3] - 1].y );
		Faces[i-4241].midpoint.z = 0.25*(Vertices[Faces[i-4241].corners[0] - 1].z + Vertices[Faces[i-4241].corners[1] -1].z + Vertices[Faces[i-4241].corners[2] - 1 ].z + Vertices[Faces[i-4241].corners[3] - 1].z );
		Faces[i-4241].distance = Calculate_distance(camera_position.x,camera_position.y,camera_position.z,Faces[i-4241].midpoint.x,Faces[i-4241].midpoint.y,Faces[i-4241].midpoint.z);
		
	}
	
	//sorting the faces

	for(i=0;i<=7235;i++)
	{

		min_value = RAND_MAX * 1.0 ;
		for(j=i;j<=7235;j++)
		{

			if(Faces[j].distance <= min_value)
			{
				min_value = Faces[j].distance;
				min = j;
			}


		}

		temp = Faces[i];
		Faces[i] = Faces[min];
		Faces[min] = temp;

	}
	
	//Need to take stroke width as input and scaling factor as well for the zooming part.	

	fprintf(graphic_svg,"<svg height=\"800\" width=\"800\">\n");
     //Create Background
    fprintf(graphic_svg,"<rect width=\"800\" height=\"800\" style=\"fill:rgb(255,255,255);stroke-width:3;stroke:rgb(0,0,255)\" />\n" );
    	
    x_min = RAND_MAX * 1.0;
    y_min = RAND_MAX * 1.0;

    for(i=7235;i>=0;i--)
    {
    	for(j=0;j<4;j++)
    	{
    		projections_corners[j].x= (double)camera_position.x-camera_position.z*(  Vertices[Faces[i].corners[j] -1].x-camera_position.x)/(double)(Vertices[Faces[i].corners[j] - 1].z-camera_position.z);
     		if(projections_corners[j].x < x_min) x_min = projections_corners[j].x; 
     		projections_corners[j].y=(double)camera_position.y-camera_position.z*(Vertices[Faces[i].corners[j] - 1].y-camera_position.y)/(double)(Vertices[Faces[i].corners[j] - 1].z-camera_position.z);
     		if(projections_corners[j].y < y_min) y_min = projections_corners[j].y;

		}
	//Calculate_intensity(light_point.x,light_point.y,light_point.z,Vertices[Faces[i].corners[0] -1].x,Vertices[Faces[i].corners[0] -1].y,Vertices[Faces[i].corners[0] -1].z ,Vertices[Faces[i].corners[1] -1].x,Vertices[Faces[i].corners[1] -1].y,Vertices[Faces[i].corners[1] -1].z ,Vertices[Faces[i].corners[2] -1].x,Vertices[Faces[i].corners[2] -1].y,Vertices[Faces[i].corners[2] -1].z ,Vertices[Faces[i].corners[3] -1].x,Vertices[Faces[i].corners[3] -1].y,Vertices[Faces[i].corners[3] -1].z , PASE ); 
	calculate_max_min(projections_corners[0].x,projections_corners[0].y,projections_corners[1].x,projections_corners[1].y,projections_corners[2].x,projections_corners[2].y,projections_corners[3].x,projections_corners[3].y,&percentage_x_max,&percentage_x_min,&percentage_y_max,&percentage_y_min);

    }

    printf("%lf %lf %lf %lf\n",percentage_x_max,percentage_x_min,percentage_y_max,percentage_y_min );
   // if(percentage_x_min == x_min)
   // exit(0);

    percentage_x_max -= x_min;
    percentage_x_min -= x_min;
    percentage_y_max -= y_min;
    percentage_y_min -= y_min;
    percentage_x_max *= scaling_factor;
    percentage_x_min *= scaling_factor;
   	percentage_y_max *= scaling_factor;
   	percentage_y_min *= scaling_factor;
   	percentage_x_max += 20;
    percentage_x_min += 20;
   	percentage_y_max += 20;
   	percentage_y_min += 20;



    for(i=7235;i>=0;i--)
    {
    	printf("%d start\n",i );
    	

    	for(j=0;j<4;j++)
    	{
    		projections_corners[j].x= (double)camera_position.x-camera_position.z*(  Vertices[Faces[i].corners[j] -1].x-camera_position.x)/(double)(Vertices[Faces[i].corners[j] - 1].z-camera_position.z);
     		//if(projections_corners[j].x < x_min) x_min = projections_corners[j].x; 
     		projections_corners[j].y=(double)camera_position.y-camera_position.z*(Vertices[Faces[i].corners[j] - 1].y-camera_position.y)/(double)(Vertices[Faces[i].corners[j] - 1].z-camera_position.z);
     		//if(projections_corners[j].y < y_min) y_min = projections_corners[j].y;

		}
		printf("%d projections calculated!\n",i );

		for(j=0;j<4;j++){
    	
    	projections_corners[j].x-=x_min;
    	projections_corners[j].y-=y_min;
    	
    	
    	}
    	printf("%d projections propered up\n",i );

		
		for(j=0;j<4;j ++)
		{
    	
    	//Multiplication enlarges the image,zoom in and zoom out.The parameters can be changed (for all projected points)
    	projections_corners[j].x*=scaling_factor; 
    	projections_corners[j].y*=scaling_factor;
    	
        //Addition translates the image in the image plane.

    	projections_corners[j].x+=20;
    	projections_corners[j].y+=20;
    	
    	}    
    	printf("%d projections scaled\n",i );
    	if((Vertices[Faces[i].corners[0] - 1].x == Vertices[Faces[i].corners[1] - 1].x )&& (Vertices[Faces[i].corners[1] - 1].x == Vertices[Faces[i].corners[2] - 1].x) && (Vertices[Faces[i].corners[2] -1].x == Vertices[Faces[i].corners[3] - 1].x))
    	{
    		face_color.r = 138;
    		face_color.b = 8;
    		face_color.g = 34;
    	}
    	else if((Vertices[Faces[i].corners[0] - 1].y == Vertices[Faces[i].corners[1] -1].y )&& (Vertices[Faces[i].corners[1] -1].y == Vertices[Faces[i].corners[2]-1].y) && (Vertices[Faces[i].corners[2]-1].y == Vertices[Faces[i].corners[3]-1].y))
    	{
    		face_color.r = 41;
    		face_color.b = 204;
    		face_color.g = 255;
    	}
    	else if((Vertices[Faces[i].corners[0]-1].z == Vertices[Faces[i].corners[1]-1].z )&& (Vertices[Faces[i].corners[1]-1].z == Vertices[Faces[i].corners[2]-1].z) && (Vertices[Faces[i].corners[2]-1].z == Vertices[Faces[i].corners[3]-1].z))
    	{
    		face_color.r = 255;
    		face_color.b = 128;
    		face_color.g = 0;
    	}
    	printf("%d projections color set\n",i );
    	
    	Calculate_intensity(light_point.x,light_point.y,light_point.z,Vertices[Faces[i].corners[0] -1].x,Vertices[Faces[i].corners[0] -1].y,Vertices[Faces[i].corners[0] -1].z ,Vertices[Faces[i].corners[1] -1].x,Vertices[Faces[i].corners[1] -1].y,Vertices[Faces[i].corners[1] -1].z ,Vertices[Faces[i].corners[3] -1].x,Vertices[Faces[i].corners[3] -1].y,Vertices[Faces[i].corners[3] -1].z ,Vertices[Faces[i].corners[2] -1].x,Vertices[Faces[i].corners[2] -1].y,Vertices[Faces[i].corners[2] -1].z , PASE ); 
    		//calculate_max_min(projections_corners[0].x,projections_corners[0].y,projections_corners[1].x,projections_corners[1].y,projections_corners[2].x,projections_corners[2].y,projections_corners[3].x,projections_corners[3].y,&percentage_x_max,&percentage_x_min,&percentage_y_max,&percentage_y_min);

    	if(PASE[0] < 0 || PASE[1] < 0 || PASE[2] < 0 || PASE[3] < 0)
       {
    	fprintf(graphic_svg, " <polygon points=\"%f,%f,%f,%f,%f,%f,%f,%f\" style=\"fill:rgb(%d,%d,%d);stroke:black;stroke-width:1\" />\n",projections_corners[0].x,projections_corners[0].y,projections_corners[1].x,projections_corners[1].y,projections_corners[2].x,projections_corners[2].y,projections_corners[3].x,projections_corners[3].y,face_color.r,face_color.b,face_color.g);					
    	}
    	else{
    		    	fprintf(graphic_svg, " <polygon points=\"%f,%f,%f,%f,%f,%f,%f,%f\" style=\"fill:rgb(%d,%d,%d);stroke:black;stroke-width:1\" />\n",projections_corners[0].x,projections_corners[0].y,projections_corners[1].x,projections_corners[1].y,projections_corners[2].x,projections_corners[2].y,projections_corners[3].x,projections_corners[3].y,face_color.r,face_color.b,face_color.g);					

    						PASE_X[0] = (projections_corners[0].x - percentage_x_min )*100/(percentage_x_max - percentage_x_min) ;
                            PASE_Y[0] = (projections_corners[0].y - percentage_y_min )*100/(percentage_y_max - percentage_y_min) ;
                            PASE_X[1] = (projections_corners[1].x - percentage_x_min )*100/(percentage_x_max - percentage_x_min) ;
                            PASE_Y[1] = (projections_corners[1].y - percentage_y_min )*100/(percentage_y_max - percentage_y_min) ;
                            PASE_X[2] = (projections_corners[2].x - percentage_x_min )*100/(percentage_x_max - percentage_x_min) ;
                            PASE_Y[2] = (projections_corners[2].y - percentage_y_min )*100/(percentage_y_max - percentage_y_min) ;
                            PASE_X[3] = (projections_corners[3].x - percentage_x_min )*100/(percentage_x_max - percentage_x_min) ;
                            PASE_Y[3] = (projections_corners[3].y - percentage_y_min )*100/(percentage_y_max - percentage_y_min) ;
        fprintf(graphic_svg,"<defs>\n");
                            if(PASE[1] > PASE[3])
                            {
                              fprintf(graphic_svg, "<linearGradient id=\"grad1\" x1=\"%f%c\" y1=\"%f%c\" x2=\"%f%c\" y2=\"%f%c\">\n",PASE_X[1],37,PASE_Y[1],37,PASE_X[3],37,PASE_Y[3],37 );
                            }
                            else
                            {
                              fprintf(graphic_svg, "<linearGradient id=\"grad1\" x1=\"%f%c\" y1=\"%f%c\" x2=\"%f%c\" y2=\"%f%c\">\n",PASE_X[3],37,PASE_Y[3],37,PASE_X[1],37,PASE_Y[1],37 );
                            }
                             fprintf(graphic_svg, " <stop offset=\"0%c\" style=\"stop-color:rgb(255,255,255);stop-opacity:0.5\" />\n",37);
                             fprintf(graphic_svg, " <stop offset=\"100%c\" style=\"stop-color:rgb(0,0,0);stop-opacity:0.5\" />\n",37 );
                             fprintf(graphic_svg, " </linearGradient>\n" );
                             if(PASE[0] > PASE[2])
                            {
                              fprintf(graphic_svg, "<linearGradient id=\"grad1\" x1=\"%f%c\" y1=\"%f%c\" x2=\"%f%c\" y2=\"%f%c\">\n",PASE_X[0],37,PASE_Y[0],37,PASE_X[2],37,PASE_Y[2],37 );
                            }
                            else
                            {
                              fprintf(graphic_svg, "<linearGradient id=\"grad1\" x1=\"%f%c\" y1=\"%f%c\" x2=\"%f%c\" y2=\"%f%c\">\n",PASE_X[2],37,PASE_Y[2],37,PASE_X[0],37,PASE_Y[0],37 );
                            }
        fprintf(graphic_svg, " <stop offset=\"0%c\" style=\"stop-color:rgb(255,255,255);stop-opacity:0.5\" />\n",37);
        fprintf(graphic_svg, " <stop offset=\"100%c\" style=\"stop-color:rgb(0,0,0);stop-opacity:0.5\" />\n",37 );
        fprintf(graphic_svg, " </linearGradient>\n" );
        fprintf(graphic_svg, "</defs>\n");
        fprintf(graphic_svg, "<polygon points=\"%f,%f %f,%f %f,%f %f,%f\" fill=\"url(#grad1)\" />\n",projections_corners[0].x,projections_corners[0].y,projections_corners[1].x,projections_corners[1].y,projections_corners[2].x,projections_corners[2].y,projections_corners[3].x,projections_corners[3].y); 
        fprintf(graphic_svg, "<polygon points=\"%f,%f %f,%f %f,%f %f,%f\" fill=\"url(#grad2)\" />\n",projections_corners[0].x,projections_corners[0].y,projections_corners[1].x,projections_corners[1].y,projections_corners[2].x,projections_corners[2].y,projections_corners[3].x,projections_corners[3].y);

        }



    	printf("%d done\n",i);

    }


    fprintf(graphic_svg,"</svg>");
	fclose(graphic_svg);


	return 0;
}