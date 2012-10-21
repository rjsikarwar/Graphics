#include <iostream>
#include <stdlib.h>

#include <GL/glut.h>
#include <cmath>
#include "octree.h"
using namespace std;


#define PI 3.14159265

voxel oct_content[1000000];	
voxel vox_content[1000000];	
int iter=0,oct_iter=0,tot=-8;

int comp_point(point x1,point x2)
{
	if(x1.x==x2.x && x1.y==x2.y && x1.z==x2.z)
		return 1;
	else return 0;
}
point fill_point(float x,float y,float z)
{
	point x1;
	x1.x=x;x1.y=y;x1.z=z;
	return x1;
}

int check_in_out_line(point x1,float x,float y,float z, float l)
{
	if(x1.y+l/2 +y- (2*y/(x/8))*(x1.x+l/2 + x/8) >0)
		return 1;
	else return 0;
}


void create_hill_voxel( float x,float y, float z)
{
	point x1,x2,x3,x4,x5,x6,x7,x8;
	x1=fill_point(-x/2,y/2,z/2);
	x2=fill_point(x/2,y/2,z/2);
	x3=fill_point(x/2,-y/2,z/2);
	x4=fill_point(-x/2,-y/2,z/2);
	x5=fill_point(-x/2,y/2,-z/2);
	x6=fill_point(x/2,y/2,-z/2);
	x7=fill_point(x/2,-y/2,-z/2);
	x8=fill_point(-x/2,-y/2,-z/2);


	
	lookup_table_hill(x1,x2,x3,x4,x5,x6,x7,x8,x,y,z);
	cout<<"No. of voxels = "<<iter<<endl;
	
	for(int i=0;i<iter;i++)
	{
		glColor3f(vox_content[i].col.x,vox_content[i].col.y,vox_content[i].col.z);
		cout<<i<<" : "<<vox_content[i].col.x<<" ,"<<vox_content[i].col.y<<" ,"<< vox_content[i].col.z<<endl;	
		if(vox_content[i].col.x!=1.0f)
		{
			glPushMatrix();
			glTranslatef(vox_content[i].mid.x,vox_content[i].mid.y,vox_content[i].mid.z);
			glutSolidCube(vox_content[i].size);
			glPopMatrix();
		}

	}
	iter=0;


}


void lookup_table_hill(point x1,point x2,point x3,point x4,point x5,point x6,point x7,point x8,float x,float y,float z)
{
	
	float length=pow( ( pow(x1.x-x2.x,2)+ pow(x1.y-x2.y,2)+ pow(x1.z-x2.z,2)),.5);
	float breadth=pow( ( pow(x1.x-x4.x,2)+ pow(x1.y-x4.y,2)+ pow(x1.z-x4.z,2)),.5);
	float height=pow( ( pow(x1.x-x5.x,2)+ pow(x1.y-x5.y,2)+ pow(x1.z-x5.z,2)),.5);

	point cube_midpt;
	cube_midpt.x= (x1.x+ x2.x+ x3.x + x4.x + x5.x + x6.x + x7.x + x8.x)/8;
	cube_midpt.y= (x1.y +x2.y +x3.y+ x4.y+ x5.y + x6.y + x7.y + x8.y)/8;
	cube_midpt.z= (x1.z +x2.z +x3.z +x4.z+ x5.z + x6.z + x7.z + x8.z)/8;
	float vol= length*breadth*height;

	float d= (pow( (pow(length,2)+pow(height,2)),.5) )/2;
	float dis_x=cube_midpt.x-(-x/2);
	float dis_z=cube_midpt.z-(-z/2);
	double angle_x=dis_x*x*PI;
	double angle_z=dis_z*z*PI;
	cout<<angle_x<<endl;
	
	double xy=pow ( (pow(cube_midpt.x,2)+pow(cube_midpt.y+y/2,2)),.5);
	double zy=pow ( (pow(cube_midpt.z,2)+pow(cube_midpt.y+y/2,2)),.5);
	
	double xy_c=pow ( (pow(cube_midpt.x,2)+pow(sin(angle_x)/2,2)),.5);
	double zy_c=pow ( (pow(cube_midpt.x,2)+pow(sin(angle_z)/2,2)),.5);


	color col;
	if ( ! ( (xy_c<(xy+d) && xy_c>(xy-d)) || (zy_c<(zy+d) && zy_c>(zy-d)) )) 
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;

		
		if( xy_c>(xy+d) && zy_c>(zy+d))
		{
			col.x=2.0;
			col.y=0.1;
			col.z=0.2;
			vox_content[iter++].col=col;
		}
		else 
		{		
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[iter++].col=col;
			
		}

	}
	else if(vol <0.000001)
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;
		col.x=1.0;
		col.y=1.0;
		col.z=1.0;
		vox_content[iter++].col=col;
	}
	else {

		
/*1*/		lookup_table_hill(x1,midpt_side(x1,x2),midpt_surface(x1,x2,x3,x4),midpt_side(x1,x4),midpt_side(x1,x5),midpt_surface(x1,x5,x6,x2),cube_midpt,midpt_surface(x1,x5,x8,x4),x,y,z );

/*2*/		lookup_table_hill(midpt_side(x1,x2),x2,midpt_side(x2,x3),midpt_surface(x1,x2,x3,x4),midpt_surface(x1,x5,x6,x2),midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,x,y,z );

/*3*/		lookup_table_hill(midpt_surface(x1,x2,x3,x4),midpt_side(x2,x3),x3,midpt_side(x3,x4),cube_midpt,midpt_surface(x2,x6,x3,x7),midpt_side(x3,x7), midpt_surface(x3,x7,x8,x4) ,x,y,z );

/*4*/		lookup_table_hill(midpt_side(x1,x4),midpt_surface(x1,x2,x3,x4),midpt_side(x3,x4),x4,midpt_surface(x1,x5,x8,x4),cube_midpt,midpt_surface(x4,x8,x3,x7),midpt_side(x4,x8),x,y,z  );

/*5*/		lookup_table_hill(midpt_side(x1,x5) ,midpt_surface(x1,x2,x6,x5),cube_midpt,midpt_surface(x1,x5,x8,x4),x5,midpt_side(x6,x5),midpt_surface(x5,x6,x7,x8),midpt_side(x5,x8),x,y,z );

/*6*/		lookup_table_hill(midpt_surface(x1,x2,x6,x5) ,midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,midpt_side(x5,x6),x6, midpt_side(x6,x7), midpt_surface(x5,x6,x7,x8) ,x,y,z );

/*7*/		lookup_table_hill(cube_midpt, midpt_surface(x2,x6,x7,x3),midpt_side(x3,x7),midpt_surface(x3,x7,x8,x4), midpt_surface(x5,x6,x7,x8), midpt_side(x6,x7), x7,midpt_side(x7,x8),x,y,z  );

/*8*/		lookup_table_hill(midpt_surface(x1,x5,x8,x4), cube_midpt, midpt_surface(x3,x7,x8,x4) , midpt_side(x4,x8),midpt_side(x5,x8) ,midpt_surface(x5,x6,x7,x8),midpt_side(x7,x8),x8 ,x,y,z );

	}

}

void create_cuboid(float x,float y,float z)
{
	float max= x>y? (x>z?x:z): (y>z?y:z);
	
	float r=max/2;
	point x1,x2,x3,x4,x5,x6,x7,x8;
	x1=fill_point(-r,r,r);
	x2=fill_point(r,r,r);
	x3=fill_point(r,-r,r);
	x4=fill_point(-r,-r,r);
	x5=fill_point(-r,r,-r);
	x6=fill_point(r,r,-r);
	x7=fill_point(r,-r,-r);
	x8=fill_point(-r,-r,-r);

	lookup_table_cuboid(x1,x2,x3,x4,x5,x6,x7,x8,x,y,z);


	for(int i=0;i<iter;i++)
	{
		glColor3f(vox_content[i].col.x,vox_content[i].col.y,vox_content[i].col.z);
		cout<<i<<" : "<<vox_content[i].col.x<<" ,"<<vox_content[i].col.y<<" ,"<< vox_content[i].col.z<<endl;	
		if(vox_content[i].col.x!=1.0f)
		{
			glPushMatrix();
			glTranslatef(vox_content[i].mid.x,vox_content[i].mid.y,vox_content[i].mid.z);
			glutWireCube(vox_content[i].size);
			glPopMatrix();
		}

	}
	iter=0;

}

void lookup_table_cuboid(point x1,point x2,point x3,point x4,point x5,point x6,point x7,point x8,float x,float y,float z)
{
//	if(parent==0)
//		cout<<"Root Node \n";
//	cout<<"Node : "<<iter<<" , Parent Node : "<<parent<<endl;

	float length=pow( ( pow(x1.x-x2.x,2)+ pow(x1.y-x2.y,2)+ pow(x1.z-x2.z,2)),.5);
	float breadth=pow( ( pow(x1.x-x4.x,2)+ pow(x1.y-x4.y,2)+ pow(x1.z-x4.z,2)),.5);
	float height=pow( ( pow(x1.x-x5.x,2)+ pow(x1.y-x5.y,2)+ pow(x1.z-x5.z,2)),.5);

	point cube_midpt;
	cube_midpt.x= (x1.x+ x2.x+ x3.x + x4.x + x5.x + x6.x + x7.x + x8.x)/8;
	cube_midpt.y= (x1.y +x2.y +x3.y+ x4.y+ x5.y + x6.y + x7.y + x8.y)/8;
	cube_midpt.z= (x1.z +x2.z +x3.z +x4.z+ x5.z + x6.z + x7.z + x8.z)/8;
	float vol= length*breadth*height;


	float mid_dis= pow( (pow(cube_midpt.x,2)+pow(cube_midpt.y,2)+pow(cube_midpt.z,2)),.5);
	float d= (pow( (pow(length,2)+pow(breadth,2)+pow(height,2)),.5) )/2;

	color col;

	if ( !( (x/2 > (abs(cube_midpt.x)-length/2) && x/2 <= (abs(cube_midpt.x)+length/2) )  || (y/2 > (abs(cube_midpt.y)-length/2) && y/2 <= (abs(cube_midpt.y)+length/2) ) || (z/2 > (abs(cube_midpt.z)-length/2) && z/2 <= (abs(cube_midpt.z)+length/2) ) ) )
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;

		if (x/2 > (abs(cube_midpt.x)+length/2) && y/2 > (abs(cube_midpt.y)+length/2) && z/2 > (abs(cube_midpt.z)+length/2))
		{
			col.x=0.2;
			col.y=2.1;
			col.z=0.2;
			vox_content[iter++].col=col;
			
		}
		else{
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[iter++].col=col;
		}
		
	}
	else if(vol <0.00001)
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;
		col.x=1.0;
		col.y=1.0;
		col.z=1.0;
		vox_content[iter++].col=col;
	}
	else {

		
/*1*/		lookup_table_cuboid(x1,midpt_side(x1,x2),midpt_surface(x1,x2,x3,x4),midpt_side(x1,x4),midpt_side(x1,x5),midpt_surface(x1,x5,x6,x2),cube_midpt,midpt_surface(x1,x5,x8,x4),x,y,z);

/*2*/		lookup_table_cuboid(midpt_side(x1,x2),x2,midpt_side(x2,x3),midpt_surface(x1,x2,x3,x4),midpt_surface(x1,x5,x6,x2),midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,x,y,z);

/*3*/		lookup_table_cuboid(midpt_surface(x1,x2,x3,x4),midpt_side(x2,x3),x3,midpt_side(x3,x4),cube_midpt,midpt_surface(x2,x6,x3,x7),midpt_side(x3,x7), midpt_surface(x3,x7,x8,x4) ,x,y,z);

/*4*/		lookup_table_cuboid(midpt_side(x1,x4),midpt_surface(x1,x2,x3,x4),midpt_side(x3,x4),x4,midpt_surface(x1,x5,x8,x4),cube_midpt,midpt_surface(x4,x8,x3,x7),midpt_side(x4,x8),x,y,z );

/*5*/		lookup_table_cuboid(midpt_side(x1,x5) ,midpt_surface(x1,x2,x6,x5),cube_midpt,midpt_surface(x1,x5,x8,x4),x5,midpt_side(x6,x5),midpt_surface(x5,x6,x7,x8),midpt_side(x5,x8),x,y,z );

/*6*/		lookup_table_cuboid(midpt_surface(x1,x2,x6,x5) ,midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,midpt_side(x5,x6),x6, midpt_side(x6,x7), midpt_surface(x5,x6,x7,x8) ,x,y,z);

/*7*/		lookup_table_cuboid(cube_midpt, midpt_surface(x2,x6,x7,x3),midpt_side(x3,x7),midpt_surface(x3,x7,x8,x4), midpt_surface(x5,x6,x7,x8), midpt_side(x6,x7), x7,midpt_side(x7,x8),x,y,z );

/*8*/		lookup_table_cuboid(midpt_surface(x1,x5,x8,x4), cube_midpt, midpt_surface(x3,x7,x8,x4) , midpt_side(x4,x8),midpt_side(x5,x8) ,midpt_surface(x5,x6,x7,x8),midpt_side(x7,x8),x8 ,x,y,z);

	}

}


void create_house(float x,float y,float z)
{
	float max= x>y? (x>z?x:z): (y>z?y:z);
	
	float r=max/2;
	point x1,x2,x3,x4,x5,x6,x7,x8;
	x1=fill_point(-r,r,r);
	x2=fill_point(r,r,r);
	x3=fill_point(r,-r,r);
	x4=fill_point(-r,-r,r);
	x5=fill_point(-r,r,-r);
	x6=fill_point(r,r,-r);
	x7=fill_point(r,-r,-r);
	x8=fill_point(-r,-r,-r);

	lookup_table_house(x1,x2,x3,x4,x5,x6,x7,x8,x,y,z);


	for(int i=0;i<iter;i++)
	{
		glColor3f(vox_content[i].col.x,vox_content[i].col.y,vox_content[i].col.z);
	//	cout<<i<<" : "<<vox_content[i].col.x<<" ,"<<vox_content[i].col.y<<" ,"<< vox_content[i].col.z<<endl;	
		if(vox_content[i].col.x!=1.0f)
		{
			glPushMatrix();
			glTranslatef(vox_content[i].mid.x,vox_content[i].mid.y,vox_content[i].mid.z);
			glutWireCube(vox_content[i].size);
			glPopMatrix();
		}

	}
	iter=0;

}

void lookup_table_house(point x1,point x2,point x3,point x4,point x5,point x6,point x7,point x8,float x,float y,float z)
{
//	if(parent==0)
//		cout<<"Root Node \n";
//	cout<<"Node : "<<iter<<" , Parent Node : "<<parent<<endl;

	float length=pow( ( pow(x1.x-x2.x,2)+ pow(x1.y-x2.y,2)+ pow(x1.z-x2.z,2)),.5);
	float breadth=pow( ( pow(x1.x-x4.x,2)+ pow(x1.y-x4.y,2)+ pow(x1.z-x4.z,2)),.5);
	float height=pow( ( pow(x1.x-x5.x,2)+ pow(x1.y-x5.y,2)+ pow(x1.z-x5.z,2)),.5);

	point cube_midpt;
	cube_midpt.x= (x1.x+ x2.x+ x3.x + x4.x + x5.x + x6.x + x7.x + x8.x)/8;
	cube_midpt.y= (x1.y +x2.y +x3.y+ x4.y+ x5.y + x6.y + x7.y + x8.y)/8;
	cube_midpt.z= (x1.z +x2.z +x3.z +x4.z+ x5.z + x6.z + x7.z + x8.z)/8;
	float vol= length*breadth*height;


	float mid_dis= pow( (pow(cube_midpt.x,2)+pow(cube_midpt.y,2)+pow(cube_midpt.z,2)),.5);
	float d= (pow( (pow(length,2)+pow(breadth,2)+pow(height,2)),.5) )/2;

	color col;

	if ( !( (x/2 > (abs(cube_midpt.x)-length/2) && x/2 <= (abs(cube_midpt.x)+length/2) )  || (y/2 > (abs(cube_midpt.y)-length/2) && y/2 <= (abs(cube_midpt.y)+length/2) ) || (z/2 > (abs(cube_midpt.z)-length/2) && z/2 <= (abs(cube_midpt.z)+length/2) ) ) )
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;

		if (x/2 > (abs(cube_midpt.x)+length/2) && y/2 > (abs(cube_midpt.y)+length/2) && z/2 > (abs(cube_midpt.z)+length/2))
		{
			
		//	cout<<abs(cube_midpt.x)<<"  "<<cube_midpt.y<<endl;
			if( ( abs(cube_midpt.x) <= (3*x/8-x/10) && abs(cube_midpt.x) >(x/4-x/10)) && (cube_midpt.y <=3*y/8+(y/5-y/4) -y/4) && cube_midpt.y >=(y/5 -y/4) )
			{
				col.x=0.5;
				col.y=0.7;
				col.z=0.7;
				vox_content[iter++].col=col;
		//		cout<<"Window color \n";
			}
			else if( ( abs(cube_midpt.x) <= x/8 ) && (cube_midpt.y >= -y/2 && cube_midpt.y <-y/10) )
			{
				col.x=0.8;
				col.y=0.5;
				col.z=0.5;
				vox_content[iter++].col=col;
		//		cout<<"Door color \n";
			}
			else if( cube_midpt.y >y/3-y/8)
			{

				if( cube_midpt.x<0 && (abs((cube_midpt.y- (y/3-y/8))/(cube_midpt.x +x/2))  < tan(PI/2.5) ) )
				{
					col.x=1.1;
					col.y=1.5;
					col.z=1.5;
					vox_content[iter++].col=col;
				}
				else if( cube_midpt.x>0 && (abs((cube_midpt.y- (y/3-y/8))/(cube_midpt.x -x/2))  < tan(PI/2.5) ) )
				{
					
					col.x=1.1;
					col.y=1.5;
					col.z=1.5;
					vox_content[iter++].col=col;
				}
				else
				{
					col.x=1.0;
					col.y=1.0;
					col.z=1.0;
					vox_content[iter++].col=col;
				}
				
			}
			else if( abs(cube_midpt.x) > x/2-x/8)
			{
				col.x=1.0;
				col.y=1.0;
				col.z=1.0;
				vox_content[iter++].col=col;
			}
				
			else{
				col.x=0.5;
				col.y=1.5;
				col.z=0.5;
				vox_content[iter++].col=col;
			}
			
		}
		else{
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[iter++].col=col;
		}
		
	}
	else if(vol <0.00001)
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;
		col.x=1.0;
		col.y=1.0;
		col.z=1.0;
		vox_content[iter++].col=col;
	}
	else {

		
/*1*/		lookup_table_house(x1,midpt_side(x1,x2),midpt_surface(x1,x2,x3,x4),midpt_side(x1,x4),midpt_side(x1,x5),midpt_surface(x1,x5,x6,x2),cube_midpt,midpt_surface(x1,x5,x8,x4),x,y,z);

/*2*/		lookup_table_house(midpt_side(x1,x2),x2,midpt_side(x2,x3),midpt_surface(x1,x2,x3,x4),midpt_surface(x1,x5,x6,x2),midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,x,y,z);

/*3*/		lookup_table_house(midpt_surface(x1,x2,x3,x4),midpt_side(x2,x3),x3,midpt_side(x3,x4),cube_midpt,midpt_surface(x2,x6,x3,x7),midpt_side(x3,x7), midpt_surface(x3,x7,x8,x4) ,x,y,z);

/*4*/		lookup_table_house(midpt_side(x1,x4),midpt_surface(x1,x2,x3,x4),midpt_side(x3,x4),x4,midpt_surface(x1,x5,x8,x4),cube_midpt,midpt_surface(x4,x8,x3,x7),midpt_side(x4,x8),x,y,z );

/*5*/		lookup_table_house(midpt_side(x1,x5) ,midpt_surface(x1,x2,x6,x5),cube_midpt,midpt_surface(x1,x5,x8,x4),x5,midpt_side(x6,x5),midpt_surface(x5,x6,x7,x8),midpt_side(x5,x8),x,y,z );

/*6*/		lookup_table_house(midpt_surface(x1,x2,x6,x5) ,midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,midpt_side(x5,x6),x6, midpt_side(x6,x7), midpt_surface(x5,x6,x7,x8) ,x,y,z);

/*7*/		lookup_table_house(cube_midpt, midpt_surface(x2,x6,x7,x3),midpt_side(x3,x7),midpt_surface(x3,x7,x8,x4), midpt_surface(x5,x6,x7,x8), midpt_side(x6,x7), x7,midpt_side(x7,x8),x,y,z );

/*8*/		lookup_table_house(midpt_surface(x1,x5,x8,x4), cube_midpt, midpt_surface(x3,x7,x8,x4) , midpt_side(x4,x8),midpt_side(x5,x8) ,midpt_surface(x5,x6,x7,x8),midpt_side(x7,x8),x8 ,x,y,z);

	}

}












//Tree 
void create_tree(float x,float y,float z)
{
	float max= x>y? (x>z?x:z): (y>z?y:z);
	
	float r=max/2;
	point x1,x2,x3,x4,x5,x6,x7,x8;
	x1=fill_point(-r,r,r);
	x2=fill_point(r,r,r);
	x3=fill_point(r,-r,r);
	x4=fill_point(-r,-r,r);
	x5=fill_point(-r,r,-r);
	x6=fill_point(r,r,-r);
	x7=fill_point(r,-r,-r);
	x8=fill_point(-r,-r,-r);

	lookup_table_tree(x1,x2,x3,x4,x5,x6,x7,x8,x,y,z);


	for(int i=0;i<iter;i++)
	{
		glColor3f(vox_content[i].col.x,vox_content[i].col.y,vox_content[i].col.z);
	//	cout<<i<<" : "<<vox_content[i].col.x<<" ,"<<vox_content[i].col.y<<" ,"<< vox_content[i].col.z<<endl;	
		if(vox_content[i].col.x!=1.0f)
		{
			glPushMatrix();
			glTranslatef(vox_content[i].mid.x,vox_content[i].mid.y,vox_content[i].mid.z);
			glutWireCube(vox_content[i].size);
			glPopMatrix();
		}

	}
	iter=0;

}

void lookup_table_tree(point x1,point x2,point x3,point x4,point x5,point x6,point x7,point x8,float x,float y,float z)
{
//	if(parent==0)
//		cout<<"Root Node \n";
//	cout<<"Node : "<<iter<<" , Parent Node : "<<parent<<endl;

	float length=pow( ( pow(x1.x-x2.x,2)+ pow(x1.y-x2.y,2)+ pow(x1.z-x2.z,2)),.5);
	float breadth=pow( ( pow(x1.x-x4.x,2)+ pow(x1.y-x4.y,2)+ pow(x1.z-x4.z,2)),.5);
	float height=pow( ( pow(x1.x-x5.x,2)+ pow(x1.y-x5.y,2)+ pow(x1.z-x5.z,2)),.5);

	point cube_midpt;
	cube_midpt.x= (x1.x+ x2.x+ x3.x + x4.x + x5.x + x6.x + x7.x + x8.x)/8;
	cube_midpt.y= (x1.y +x2.y +x3.y+ x4.y+ x5.y + x6.y + x7.y + x8.y)/8;
	cube_midpt.z= (x1.z +x2.z +x3.z +x4.z+ x5.z + x6.z + x7.z + x8.z)/8;
	float vol= length*breadth*height;


	float mid_dis= pow( (pow(cube_midpt.x,2)+pow(cube_midpt.y,2)+pow(cube_midpt.z,2)),.5);
	float d= (pow( (pow(length,2)+pow(breadth,2)+pow(height,2)),.5) )/2;

	color col;

	if ( !( (x/2 > (abs(cube_midpt.x)-length/2) && x/2 <= (abs(cube_midpt.x)+length/2) )  || (y/2 > (abs(cube_midpt.y)-length/2) && y/2 <= (abs(cube_midpt.y)+length/2) ) || (z/2 > (abs(cube_midpt.z)-length/2) && z/2 <= (abs(cube_midpt.z)+length/2) ) ) )
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;

		if (x/2 > (abs(cube_midpt.x)+length/2) && y/2 > (abs(cube_midpt.y)+length/2) && z/2 > (abs(cube_midpt.z)+length/2))
		{
			
		//	
			if(abs(cube_midpt.x)< (x/10) && cube_midpt.y<-y/10 && cube_midpt.y >-y/1.7 && cube_midpt.z>z/2.3)
			{ 
				col.x=0.5;
				col.y=0.2;
				col.z=0.2;
			vox_content[iter++].col=col;
			}
			else if( cube_midpt.y >= -y/10 && cube_midpt.z>z/2.3)
			{

				if( cube_midpt.x<0 && (abs((cube_midpt.y+y/10)/(cube_midpt.x +x/2))  < tan(PI/2.5) ) )
				{
					col.x=0.2;
					col.y=2.1;
					col.z=0.2;
					vox_content[iter++].col=col;
				}
				else if( cube_midpt.x>0 && (abs((cube_midpt.y+y/10 )/(cube_midpt.x -x/2))  < tan(PI/2.5) ) )
				{
					
					col.x=0.2;
					col.y=2.1;
					col.z=0.2;
					vox_content[iter++].col=col;
				}
				else
				{
					col.x=1.0;
					col.y=1.0;
					col.z=1.0;
					vox_content[iter++].col=col;
				}
			}
			
			
		}
		else{
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[iter++].col=col;
		}
		
	}
	else if(vol <0.000005)
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;
		col.x=1.0;
		col.y=1.0;
		col.z=1.0;
		vox_content[iter++].col=col;
	}
	else {

		
/*1*/		lookup_table_tree(x1,midpt_side(x1,x2),midpt_surface(x1,x2,x3,x4),midpt_side(x1,x4),midpt_side(x1,x5),midpt_surface(x1,x5,x6,x2),cube_midpt,midpt_surface(x1,x5,x8,x4),x,y,z);

/*2*/		lookup_table_tree(midpt_side(x1,x2),x2,midpt_side(x2,x3),midpt_surface(x1,x2,x3,x4),midpt_surface(x1,x5,x6,x2),midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,x,y,z);

/*3*/		lookup_table_tree(midpt_surface(x1,x2,x3,x4),midpt_side(x2,x3),x3,midpt_side(x3,x4),cube_midpt,midpt_surface(x2,x6,x3,x7),midpt_side(x3,x7), midpt_surface(x3,x7,x8,x4) ,x,y,z);

/*4*/		lookup_table_tree(midpt_side(x1,x4),midpt_surface(x1,x2,x3,x4),midpt_side(x3,x4),x4,midpt_surface(x1,x5,x8,x4),cube_midpt,midpt_surface(x4,x8,x3,x7),midpt_side(x4,x8),x,y,z );

/*5*/		lookup_table_tree(midpt_side(x1,x5) ,midpt_surface(x1,x2,x6,x5),cube_midpt,midpt_surface(x1,x5,x8,x4),x5,midpt_side(x6,x5),midpt_surface(x5,x6,x7,x8),midpt_side(x5,x8),x,y,z );

/*6*/		lookup_table_tree(midpt_surface(x1,x2,x6,x5) ,midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,midpt_side(x5,x6),x6, midpt_side(x6,x7), midpt_surface(x5,x6,x7,x8) ,x,y,z);

/*7*/		lookup_table_tree(cube_midpt, midpt_surface(x2,x6,x7,x3),midpt_side(x3,x7),midpt_surface(x3,x7,x8,x4), midpt_surface(x5,x6,x7,x8), midpt_side(x6,x7), x7,midpt_side(x7,x8),x,y,z );

/*8*/		lookup_table_tree(midpt_surface(x1,x5,x8,x4), cube_midpt, midpt_surface(x3,x7,x8,x4) , midpt_side(x4,x8),midpt_side(x5,x8) ,midpt_surface(x5,x6,x7,x8),midpt_side(x7,x8),x8 ,x,y,z);

	}

}














void create_cylinder_voxel(float r1, float r2,float l)
{
	point x1,x2,x3,x4,x5,x6,x7,x8;
	x1=fill_point(-r1,l/2,r1);
	x2=fill_point(r1,l/2,r1);
	x3=fill_point(r1,-l/2,r1);
	x4=fill_point(-r1,-l/2,r1);
	x5=fill_point(-r1,l/2,-r1);
	x6=fill_point(r1,l/2,-r1);
	x7=fill_point(r1,-l/2,-r1);
	x8=fill_point(-r1,-l/2,-r1);

	lookup_table_cylinder(x1,x2,x3,x4,x5,x6,x7,x8,r1,r2,l,0,0);
	
	cout<<"No. of voxels for cylinder = "<<iter<<endl;

	for(int i=0;i<iter;i++)
	{
		glColor3f(vox_content[i].col.x,vox_content[i].col.y,vox_content[i].col.z);
	//	cout<<i<<" : "<<vox_content[i].col.x<<" ,"<<vox_content[i].col.y<<" ,"<< vox_content[i].col.z<<endl;	
		if(vox_content[i].col.x!=1.0f)
		{
			glPushMatrix();
			glTranslatef(vox_content[i].mid.x,vox_content[i].mid.y,vox_content[i].mid.z);
			glutSolidCube(vox_content[i].size);
			glPopMatrix();
		}

	}
	iter=0;

}

void lookup_table_cylinder(point x1,point x2,point x3,point x4,point x5,point x6,point x7,point x8,float r1,float r2,float l,int node,int parent)
{
		if(node!=0)
		cout<<"Node : "<<node<<" , Parent Node : "<<parent<<" "<<endl;

	float length=pow( ( pow(x1.x-x2.x,2)+ pow(x1.y-x2.y,2)+ pow(x1.z-x2.z,2)),.5);
	float breadth=pow( ( pow(x1.x-x4.x,2)+ pow(x1.y-x4.y,2)+ pow(x1.z-x4.z,2)),.5);
	float height=pow( ( pow(x1.x-x5.x,2)+ pow(x1.y-x5.y,2)+ pow(x1.z-x5.z,2)),.5);

	point cube_midpt;
	cube_midpt.x= (x1.x+ x2.x+ x3.x + x4.x + x5.x + x6.x + x7.x + x8.x)/8;
	cube_midpt.y= (x1.y +x2.y +x3.y+ x4.y+ x5.y + x6.y + x7.y + x8.y)/8;
	cube_midpt.z= (x1.z +x2.z +x3.z +x4.z+ x5.z + x6.z + x7.z + x8.z)/8;
	float vol= length*breadth*height;


	float mid_dis= pow( (pow(cube_midpt.x,2)+pow(cube_midpt.z,2)),.5);
	float d= (pow( (pow(length,2)+pow(height,2)),.5) )/2;

	
	color col;
	if ( !  ( (r1<(mid_dis+d) && r1>(mid_dis-d))||(r2<(mid_dis+d) &&r2>(mid_dis-d) ) )) 
	{

	

		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;

		
		if( r2>(mid_dis+d) )
		{
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[iter++].col=col;
		}
		else if(r1>(mid_dis+d) )
		{
			col.x=2.0;
			col.y=0.1;
			col.z=0.2;
			vox_content[iter++].col=col;
			
		}
		else{
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[iter++].col=col;
		}
		
	}
	else if(vol <0.00001)
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;
		col.x=1.0;
		col.y=1.0;
		col.z=1.0;
		vox_content[iter++].col=col;
	}
	else {
		tot+=7;
		int iter1=tot;
		
/*1*/		lookup_table_cylinder(x1,midpt_side(x1,x2),midpt_surface(x1,x2,x3,x4),midpt_side(x1,x4),midpt_side(x1,x5),midpt_surface(x1,x5,x6,x2),cube_midpt,midpt_surface(x1,x5,x8,x4),r1,r2,l,iter1+1,node );

/*2*/		lookup_table_cylinder(midpt_side(x1,x2),x2,midpt_side(x2,x3),midpt_surface(x1,x2,x3,x4),midpt_surface(x1,x5,x6,x2),midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,r1,r2,l,iter1+2,node);

/*3*/		lookup_table_cylinder(midpt_surface(x1,x2,x3,x4),midpt_side(x2,x3),x3,midpt_side(x3,x4),cube_midpt,midpt_surface(x2,x6,x3,x7),midpt_side(x3,x7), midpt_surface(x3,x7,x8,x4) ,r1,r2,l,iter1+3,node);

/*4*/		lookup_table_cylinder(midpt_side(x1,x4),midpt_surface(x1,x2,x3,x4),midpt_side(x3,x4),x4,midpt_surface(x1,x5,x8,x4),cube_midpt,midpt_surface(x4,x8,x3,x7),midpt_side(x4,x8),r1,r2,l,iter1+4,node);

/*5*/		lookup_table_cylinder(midpt_side(x1,x5) ,midpt_surface(x1,x2,x6,x5),cube_midpt,midpt_surface(x1,x5,x8,x4),x5,midpt_side(x6,x5),midpt_surface(x5,x6,x7,x8),midpt_side(x5,x8),r1,r2,l,iter1+5,node);

/*6*/		lookup_table_cylinder(midpt_surface(x1,x2,x6,x5) ,midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,midpt_side(x5,x6),x6, midpt_side(x6,x7), midpt_surface(x5,x6,x7,x8) ,r1,r2,l,iter1+6,node);

/*7*/		lookup_table_cylinder(cube_midpt, midpt_surface(x2,x6,x7,x3),midpt_side(x3,x7),midpt_surface(x3,x7,x8,x4), midpt_surface(x5,x6,x7,x8), midpt_side(x6,x7), x7,midpt_side(x7,x8),r1,r2,l,iter1+7,node);

/*8*/		lookup_table_cylinder(midpt_surface(x1,x5,x8,x4), cube_midpt, midpt_surface(x3,x7,x8,x4) , midpt_side(x4,x8),midpt_side(x5,x8) ,midpt_surface(x5,x6,x7,x8),midpt_side(x7,x8),x8 ,r1,r2,l,iter1+8,node);

	}

}




void create_sphere_voxel( float r)
{
	point x1,x2,x3,x4,x5,x6,x7,x8;
	x1=fill_point(-r,r,r);
	x2=fill_point(r,r,r);
	x3=fill_point(r,-r,r);
	x4=fill_point(-r,-r,r);
	x5=fill_point(-r,r,-r);
	x6=fill_point(r,r,-r);
	x7=fill_point(r,-r,-r);
	x8=fill_point(-r,-r,-r);

//	create_voxel(x1,x2,x3,x4,x5,x6,x7,x8);
	lookup_table_sphere(x1,x2,x3,x4,x5,x6,x7,x8,r,0,1);
	
	cout<<"No. of voxels for sphere = "<<iter<<endl;
	
	for(int i=0;i<iter;i++)
	{
		glColor3f(vox_content[i].col.x,vox_content[i].col.y,vox_content[i].col.z);
//		cout<<i<<" : "<<vox_content[i].col.x<<" ,"<<vox_content[i].col.y<<" ,"<< vox_content[i].col.z<<endl;	
		if(vox_content[i].col.x!=1.0f)
		{
			glPushMatrix();
			glTranslatef(vox_content[i].mid.x,vox_content[i].mid.y,vox_content[i].mid.z);
			glutSolidCube(vox_content[i].size);
			glPopMatrix();
		}

	}
	iter=0;
	
}

void lookup_table_sphere(point x1,point x2,point x3,point x4,point x5,point x6,point x7,point x8,float r,int parent,int node)
{
//	if(parent==0)
//		cout<<"Root Node \n";
//	cout<<"Node : "<<iter<<" , Parent Node : "<<parent<<endl;

	float length=pow( ( pow(x1.x-x2.x,2)+ pow(x1.y-x2.y,2)+ pow(x1.z-x2.z,2)),.5);
	float breadth=pow( ( pow(x1.x-x4.x,2)+ pow(x1.y-x4.y,2)+ pow(x1.z-x4.z,2)),.5);
	float height=pow( ( pow(x1.x-x5.x,2)+ pow(x1.y-x5.y,2)+ pow(x1.z-x5.z,2)),.5);

	point cube_midpt;
	cube_midpt.x= (x1.x+ x2.x+ x3.x + x4.x + x5.x + x6.x + x7.x + x8.x)/8;
	cube_midpt.y= (x1.y +x2.y +x3.y+ x4.y+ x5.y + x6.y + x7.y + x8.y)/8;
	cube_midpt.z= (x1.z +x2.z +x3.z +x4.z+ x5.z + x6.z + x7.z + x8.z)/8;
	float vol= length*breadth*height;


	float mid_dis= pow( (pow(cube_midpt.x,2)+pow(cube_midpt.y,2)+pow(cube_midpt.z,2)),.5);
	float d= (pow( (pow(length,2)+pow(breadth,2)+pow(height,2)),.5) )/2;

	color col;
	if ( !( r<(mid_dis+d) && r>(mid_dis-d) ) )
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;

		if(r>(mid_dis+d))
		{
			col.x=0.2;
			col.y=2.1;
			col.z=0.2;
			vox_content[iter++].col=col;
			
		}
		else{
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[iter++].col=col;
		}
		
	}
	else if(vol <0.00001)
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;
		col.x=1.0;
		col.y=1.0;
		col.z=1.0;
		vox_content[iter++].col=col;
	}
	else {

		
/*1*/		lookup_table_sphere(x1,midpt_side(x1,x2),midpt_surface(x1,x2,x3,x4),midpt_side(x1,x4),midpt_side(x1,x5),midpt_surface(x1,x5,x6,x2),cube_midpt,midpt_surface(x1,x5,x8,x4),r,node,node+1);

/*2*/		lookup_table_sphere(midpt_side(x1,x2),x2,midpt_side(x2,x3),midpt_surface(x1,x2,x3,x4),midpt_surface(x1,x5,x6,x2),midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,r,node,node+2);

/*3*/		lookup_table_sphere(midpt_surface(x1,x2,x3,x4),midpt_side(x2,x3),x3,midpt_side(x3,x4),cube_midpt,midpt_surface(x2,x6,x3,x7),midpt_side(x3,x7), midpt_surface(x3,x7,x8,x4) ,r,node,node+3);

/*4*/		lookup_table_sphere(midpt_side(x1,x4),midpt_surface(x1,x2,x3,x4),midpt_side(x3,x4),x4,midpt_surface(x1,x5,x8,x4),cube_midpt,midpt_surface(x4,x8,x3,x7),midpt_side(x4,x8),r,node,node+4 );

/*5*/		lookup_table_sphere(midpt_side(x1,x5) ,midpt_surface(x1,x2,x6,x5),cube_midpt,midpt_surface(x1,x5,x8,x4),x5,midpt_side(x6,x5),midpt_surface(x5,x6,x7,x8),midpt_side(x5,x8),r,node,node+5 );

/*6*/		lookup_table_sphere(midpt_surface(x1,x2,x6,x5) ,midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,midpt_side(x5,x6),x6, midpt_side(x6,x7), midpt_surface(x5,x6,x7,x8) ,r,node,node+6);

/*7*/		lookup_table_sphere(cube_midpt, midpt_surface(x2,x6,x7,x3),midpt_side(x3,x7),midpt_surface(x3,x7,x8,x4), midpt_surface(x5,x6,x7,x8), midpt_side(x6,x7), x7,midpt_side(x7,x8),r,node,node+7 );

/*8*/		lookup_table_sphere(midpt_surface(x1,x5,x8,x4), cube_midpt, midpt_surface(x3,x7,x8,x4) , midpt_side(x4,x8),midpt_side(x5,x8) ,midpt_surface(x5,x6,x7,x8),midpt_side(x7,x8),x8 ,r,node,node+8);

	}

}

void create_road(float x,float y,float z)
{
	float max= x>y? (x>z?x:z): (y>z?y:z);
	
	float r=max/2;
	point x1,x2,x3,x4,x5,x6,x7,x8;
	x1=fill_point(-r,r,r);
	x2=fill_point(r,r,r);
	x3=fill_point(r,-r,r);
	x4=fill_point(-r,-r,r);
	x5=fill_point(-r,r,-r);
	x6=fill_point(r,r,-r);
	x7=fill_point(r,-r,-r);
	x8=fill_point(-r,-r,-r);

	lookup_table_road(x1,x2,x3,x4,x5,x6,x7,x8,x,y,z);


	for(int i=0;i<iter;i++)
	{
		glColor3f(vox_content[i].col.x,vox_content[i].col.y,vox_content[i].col.z);
	//	cout<<i<<" : "<<vox_content[i].col.x<<" ,"<<vox_content[i].col.y<<" ,"<< vox_content[i].col.z<<endl;	
		if(vox_content[i].col.x!=1.0f)
		{
			glPushMatrix();
			glTranslatef(vox_content[i].mid.x,vox_content[i].mid.y,vox_content[i].mid.z);
			glutWireCube(vox_content[i].size);
			glPopMatrix();
		}

	}
	iter=0;

}

void lookup_table_road(point x1,point x2,point x3,point x4,point x5,point x6,point x7,point x8,float x,float y,float z)
{
//	if(parent==0)
//		cout<<"Root Node \n";
//	cout<<"Node : "<<iter<<" , Parent Node : "<<parent<<endl;

	float length=pow( ( pow(x1.x-x2.x,2)+ pow(x1.y-x2.y,2)+ pow(x1.z-x2.z,2)),.5);
	float breadth=pow( ( pow(x1.x-x4.x,2)+ pow(x1.y-x4.y,2)+ pow(x1.z-x4.z,2)),.5);
	float height=pow( ( pow(x1.x-x5.x,2)+ pow(x1.y-x5.y,2)+ pow(x1.z-x5.z,2)),.5);

	point cube_midpt;
	cube_midpt.x= (x1.x+ x2.x+ x3.x + x4.x + x5.x + x6.x + x7.x + x8.x)/8;
	cube_midpt.y= (x1.y +x2.y +x3.y+ x4.y+ x5.y + x6.y + x7.y + x8.y)/8;
	cube_midpt.z= (x1.z +x2.z +x3.z +x4.z+ x5.z + x6.z + x7.z + x8.z)/8;
	float vol= length*breadth*height;


	float mid_dis= pow( (pow(cube_midpt.x,2)+pow(cube_midpt.y,2)+pow(cube_midpt.z,2)),.5);
	float d= (pow( (pow(length,2)+pow(breadth,2)+pow(height,2)),.5) )/2;

	color col;

	if ( !( (x/2 > (abs(cube_midpt.x)-length/2) && x/2 <= (abs(cube_midpt.x)+length/2) )  || (y/2 > (abs(cube_midpt.y)-length/2) && y/2 <= (abs(cube_midpt.y)+length/2) ) || (z/2 > (abs(cube_midpt.z)-length/2) && z/2 <= (abs(cube_midpt.z)+length/2) ) ) )
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;

		if (x/2 > (abs(cube_midpt.x)+length/2) && y/2 > (abs(cube_midpt.y)+length/2) && z/2 > (abs(cube_midpt.z)+length/2))
		{
			

			if(cube_midpt.y<0 && cube_midpt.x<0)
			{
				col.x=0.5;
				col.y=0.5;
				col.z=0.5;
				vox_content[iter++].col=col;
			}
			else if( (cube_midpt.x>0  && cube_midpt.z > z/2.2 && (cube_midpt.y/(cube_midpt.x))<tan(PI*45/180)  ) )
			{
				if( ((cube_midpt.y+y/2) /(cube_midpt.x))<tan(PI*45/180) )
				{
					col.x=1;
					col.y=1;
					col.z=1;
					vox_content[iter++].col=col;
				}
				else {					
				col.x=0.5;
				col.y=0.5;
				col.z=0.5;
				vox_content[iter++].col=col;
				}
			}



			
			
		}
		else{
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[iter++].col=col;
		}
		
	}
	else if(vol <0.00001)
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;
		col.x=1.0;
		col.y=1.0;
		col.z=1.0;
		vox_content[iter++].col=col;
	}
	else {

		
/*1*/		lookup_table_road(x1,midpt_side(x1,x2),midpt_surface(x1,x2,x3,x4),midpt_side(x1,x4),midpt_side(x1,x5),midpt_surface(x1,x5,x6,x2),cube_midpt,midpt_surface(x1,x5,x8,x4),x,y,z);

/*2*/		lookup_table_road(midpt_side(x1,x2),x2,midpt_side(x2,x3),midpt_surface(x1,x2,x3,x4),midpt_surface(x1,x5,x6,x2),midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,x,y,z);

/*3*/		lookup_table_road(midpt_surface(x1,x2,x3,x4),midpt_side(x2,x3),x3,midpt_side(x3,x4),cube_midpt,midpt_surface(x2,x6,x3,x7),midpt_side(x3,x7), midpt_surface(x3,x7,x8,x4) ,x,y,z);

/*4*/		lookup_table_road(midpt_side(x1,x4),midpt_surface(x1,x2,x3,x4),midpt_side(x3,x4),x4,midpt_surface(x1,x5,x8,x4),cube_midpt,midpt_surface(x4,x8,x3,x7),midpt_side(x4,x8),x,y,z );

/*5*/		lookup_table_road(midpt_side(x1,x5) ,midpt_surface(x1,x2,x6,x5),cube_midpt,midpt_surface(x1,x5,x8,x4),x5,midpt_side(x6,x5),midpt_surface(x5,x6,x7,x8),midpt_side(x5,x8),x,y,z );

/*6*/		lookup_table_road(midpt_surface(x1,x2,x6,x5) ,midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,midpt_side(x5,x6),x6, midpt_side(x6,x7), midpt_surface(x5,x6,x7,x8) ,x,y,z);

/*7*/		lookup_table_road(cube_midpt, midpt_surface(x2,x6,x7,x3),midpt_side(x3,x7),midpt_surface(x3,x7,x8,x4), midpt_surface(x5,x6,x7,x8), midpt_side(x6,x7), x7,midpt_side(x7,x8),x,y,z );

/*8*/		lookup_table_road(midpt_surface(x1,x5,x8,x4), cube_midpt, midpt_surface(x3,x7,x8,x4) , midpt_side(x4,x8),midpt_side(x5,x8) ,midpt_surface(x5,x6,x7,x8),midpt_side(x7,x8),x8 ,x,y,z);

	}

}






















/*Human Voxels */

void create_human(float x,float y,float z)
{
	float max= x>y? (x>z?x:z): (y>z?y:z);
	
	float r=max/2;
	point x1,x2,x3,x4,x5,x6,x7,x8;
	x1=fill_point(-r,r,r);
	x2=fill_point(r,r,r);
	x3=fill_point(r,-r,r);
	x4=fill_point(-r,-r,r);
	x5=fill_point(-r,r,-r);
	x6=fill_point(r,r,-r);
	x7=fill_point(r,-r,-r);
	x8=fill_point(-r,-r,-r);

	lookup_table_human(x1,x2,x3,x4,x5,x6,x7,x8,x,y,z);


	for(int i=0;i<iter;i++)
	{
		glColor3f(vox_content[i].col.x,vox_content[i].col.y,vox_content[i].col.z);
	//	cout<<i<<" : "<<vox_content[i].col.x<<" ,"<<vox_content[i].col.y<<" ,"<< vox_content[i].col.z<<endl;	
		if(vox_content[i].col.x!=1.0f)
		{
			glPushMatrix();
			glTranslatef(vox_content[i].mid.x,vox_content[i].mid.y,vox_content[i].mid.z);
			glutWireCube(vox_content[i].size);
			glPopMatrix();
		}

	}
	iter=0;

}

void lookup_table_human(point x1,point x2,point x3,point x4,point x5,point x6,point x7,point x8,float x,float y,float z)
{
	float length=pow( ( pow(x1.x-x2.x,2)+ pow(x1.y-x2.y,2)+ pow(x1.z-x2.z,2)),.5);
	float breadth=pow( ( pow(x1.x-x4.x,2)+ pow(x1.y-x4.y,2)+ pow(x1.z-x4.z,2)),.5);
	float height=pow( ( pow(x1.x-x5.x,2)+ pow(x1.y-x5.y,2)+ pow(x1.z-x5.z,2)),.5);

	point cube_midpt;
	cube_midpt.x= (x1.x+ x2.x+ x3.x + x4.x + x5.x + x6.x + x7.x + x8.x)/8;
	cube_midpt.y= (x1.y +x2.y +x3.y+ x4.y+ x5.y + x6.y + x7.y + x8.y)/8;
	cube_midpt.z= (x1.z +x2.z +x3.z +x4.z+ x5.z + x6.z + x7.z + x8.z)/8;
	float vol= length*breadth*height;


	float mid_dis= pow( (pow(cube_midpt.x,2)+pow(cube_midpt.y,2)+pow(cube_midpt.z,2)),.5);
	float d= (pow( (pow(length,2)+pow(breadth,2)+pow(height,2)),.5) )/2;

	color col;

	if ( !( (x/2 > (abs(cube_midpt.x)-length/2) && x/2 <= (abs(cube_midpt.x)+length/2) )  || (y/2 > (abs(cube_midpt.y)-length/2) && y/2 <= (abs(cube_midpt.y)+length/2) ) || (z/2 > (abs(cube_midpt.z)-length/2) && z/2 <= (abs(cube_midpt.z)+length/2) ) ) )
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;

		if (x/2 > (abs(cube_midpt.x)+length/2) && y/2 > (abs(cube_midpt.y)+length/2) && z/2 > (abs(cube_midpt.z)+length/2))
		{
			
		//	cout<<abs(cube_midpt.x)<<"  "<<cube_midpt.y<<endl;
			if( (cube_midpt.y <=y/4) && (cube_midpt.y >-y/8) )
			{/*Torso Color*/
				if(abs(cube_midpt.x)<x/4)
				{
				col.x=0.3;
				col.y=0.5;
				col.z=0.5;
				vox_content[iter++].col=col;
			    }
			    else if(cube_midpt.x<0 && ((cube_midpt.y +y/4)/(cube_midpt.x+x/2))<=tan(PI*80/180) )
				{
				
				if(((cube_midpt.y +y/4)/(cube_midpt.x+x/2-x/10))<=tan(PI*80/180) )
				{
					col.x=1;
					col.y=1;
					col.z=1;
					vox_content[iter++].col=col;
				}
				else{
					col.x=1.4;
					col.y=0.4;
					col.z=0.5;
					vox_content[iter++].col=col;
				}
				
			    }
			else if( cube_midpt.x> 0 && ((cube_midpt.y +y/4)/(cube_midpt.x-x/2))>=tan(-PI*80/180) )
				{
				if(((cube_midpt.y +y/4)/(cube_midpt.x-x/2+x/10))>=tan(-PI*80/180) )
				{
					col.x=1;
					col.y=1;
					col.z=1;
					vox_content[iter++].col=col;
				}
				else{
				
					col.x=1.4;
					col.y=0.4;
					col.z=0.5;
					vox_content[iter++].col=col;
					}
				
			    }
			    
			   
			}
			else if( ( abs(cube_midpt.x) <= x/10 ) && (cube_midpt.y >y/4) && (cube_midpt.y <3*y/10) && (cube_midpt.z>=z/3))
			{
				/*neck color*/
				col.x=0.3;
				col.y=0.5;
				col.z=0.5;
				vox_content[iter++].col=col;
		
			}
			else if((abs(cube_midpt.x)<= x/6) && (cube_midpt.y >3*y/10))
			{
				if((abs(cube_midpt.x)<= x/8) && (abs(cube_midpt.x)>= x/10) && (cube_midpt.y <=y/2.1) &&(cube_midpt.y>=y/2.25))
				{
				/*Eye Color*/
					col.x=0.2;
					col.y=2.1;
					col.z=0.2;
					vox_content[iter++].col=col;
				}
				else if((abs(cube_midpt.x)<= x/45) && (cube_midpt.y <=y/2.35) &&(cube_midpt.y>=y/2.6))
				{
				/*Nose Color*/
					col.x=0.2;
					col.y=2.1;
					col.z=0.2;
					vox_content[iter++].col=col;
				}
				else if((abs(cube_midpt.x)<=x/13) && (cube_midpt.y <=y/2.7) &&(cube_midpt.y>=y/2.85))
				{
				/*Mouth Color Color*/
					col.x=0.2;
					col.y=2.1;
					col.z=0.2;
					vox_content[iter++].col=col;
				}	
				else if(cube_midpt.z >=z/3)
				{		
				/*Face color*/
				col.x=0.3;
				col.y=0.5;
				col.z=0.5;
				vox_content[iter++].col=col;
			    }
			}		
			else if((abs(cube_midpt.x)<= 2*x/8) && (abs(cube_midpt.x)>= x/8) && (cube_midpt.y <-y/8) && (cube_midpt.z>=z/3))
			{
				/*Leg Color*/
				col.x=0.3;
				col.y=0.5;
				col.z=0.5;
				vox_content[iter++].col=col;
			}		
			/*else if( cube_midpt.y >y/3-y/8)
			{

				if( cube_midpt.x<0 && (abs((cube_midpt.y- (y/3-y/8))/(cube_midpt.x +x/2))  < tan(PI/2.5) ) )
				{
					col.x=1.3;
					col.y=1.5;
					col.z=1.5;
					vox_content[iter++].col=col;
				}
				else if( cube_midpt.x>0 && (abs((cube_midpt.y- (y/3-y/8))/(cube_midpt.x -x/2))  < tan(PI/2.5) ) )
				{
					
					col.x=1.3;
					col.y=1.5;
					col.z=1.5;
					vox_content[iter++].col=col;
				}
				else
				{
					col.x=1.0;
					col.y=1.0;
					col.z=1.0;
					vox_content[iter++].col=col;
				}
				
			}*/
			else if( abs(cube_midpt.x) > x/2-x/8)
			{
				col.x=1.0;
				col.y=1.0;
				col.z=1.0;
				vox_content[iter++].col=col;
			}
				
			else{
				col.x=1.0;
				col.y=1.0;
				col.z=1.0;
				vox_content[iter++].col=col;
			}
			
		}
		else{
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[iter++].col=col;
		}
		
	}
	else if(vol <0.00001)
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter].size=length;
		col.x=1.0;
		col.y=1.0;
		col.z=1.0;
		vox_content[iter++].col=col;
	}
	else {

		
/*1*/		lookup_table_human(x1,midpt_side(x1,x2),midpt_surface(x1,x2,x3,x4),midpt_side(x1,x4),midpt_side(x1,x5),midpt_surface(x1,x5,x6,x2),cube_midpt,midpt_surface(x1,x5,x8,x4),x,y,z);

/*2*/		lookup_table_human(midpt_side(x1,x2),x2,midpt_side(x2,x3),midpt_surface(x1,x2,x3,x4),midpt_surface(x1,x5,x6,x2),midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,x,y,z);

/*3*/		lookup_table_human(midpt_surface(x1,x2,x3,x4),midpt_side(x2,x3),x3,midpt_side(x3,x4),cube_midpt,midpt_surface(x2,x6,x3,x7),midpt_side(x3,x7), midpt_surface(x3,x7,x8,x4) ,x,y,z);

/*4*/		lookup_table_human(midpt_side(x1,x4),midpt_surface(x1,x2,x3,x4),midpt_side(x3,x4),x4,midpt_surface(x1,x5,x8,x4),cube_midpt,midpt_surface(x4,x8,x3,x7),midpt_side(x4,x8),x,y,z );

/*5*/		lookup_table_human(midpt_side(x1,x5) ,midpt_surface(x1,x2,x6,x5),cube_midpt,midpt_surface(x1,x5,x8,x4),x5,midpt_side(x6,x5),midpt_surface(x5,x6,x7,x8),midpt_side(x5,x8),x,y,z );

/*6*/		lookup_table_human(midpt_surface(x1,x2,x6,x5) ,midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,midpt_side(x5,x6),x6, midpt_side(x6,x7), midpt_surface(x5,x6,x7,x8) ,x,y,z);

/*7*/		lookup_table_human(cube_midpt, midpt_surface(x2,x6,x7,x3),midpt_side(x3,x7),midpt_surface(x3,x7,x8,x4), midpt_surface(x5,x6,x7,x8), midpt_side(x6,x7), x7,midpt_side(x7,x8),x,y,z );

/*8*/		lookup_table_human(midpt_surface(x1,x5,x8,x4), cube_midpt, midpt_surface(x3,x7,x8,x4) , midpt_side(x4,x8),midpt_side(x5,x8) ,midpt_surface(x5,x6,x7,x8),midpt_side(x7,x8),x8 ,x,y,z);

	}

}



/*Human Voxel End*/


point midpt_surface(point x1,point x2,point x3,point x4)
{
	float x_midpt= (x1.x+ x2.x+ x3.x + x4.x)/4;
	float y_midpt= (x1.y +x2.y +x3.y+ x4.y)/4;
	float z_midpt= (x1.z +x2.z +x3.z +x4.z)/4;
	point midpt;
	midpt.x=x_midpt;
	midpt.y=y_midpt;
	midpt.z=z_midpt;
	return midpt;
}

point midpt_side(point x1,point x4)
{
	point xx1;
	xx1.y=(x1.y+ x4.y)/2;
	xx1.x=(x1.x+ x4.x)/2;
	xx1.z=(x1.z+ x4.z)/2;
	return xx1;
}

