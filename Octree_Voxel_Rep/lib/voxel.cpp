#include <iostream>
#include <stdlib.h> 

#include <GL/glut.h>
#include <cmath>
#include "voxel.h"

using namespace std;
#define PI 3.14159265

voxel vox_content[10000000];	
int iter=0;

point fill_point(float x,float y,float z)
{
	point x1;
	x1.x=x;x1.y=y;x1.z=z;
	return x1;
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

	create_voxel(x1,x2,x3,x4,x5,x6,x7,x8);
	cout<<"No. of voxels = "<<iter<<endl;

	for(int i=0;i<iter;i++)
	{
		color col;
		float dis_x=vox_content[i].mid.x-(-x/2);
		float dis_z=vox_content[i].mid.z-(-z/2);
		double angle_x=dis_x*x*PI;
		double angle_z=dis_z*z*PI;
	//	cout<<angle<<xendl;
		point mid=vox_content[i].mid;

		double xy=pow ( (pow(mid.x,2)+pow(mid.y+y/2,2)),.5);
		double zy=pow ( (pow(mid.z,2)+pow(mid.y+y/2,2)),.5);

		double xy_c=pow ( (pow(mid.x,2)+pow(sin(angle_x)/2,2)),.5);
		double zy_c=pow ( (pow(mid.x,2)+pow(sin(angle_z)/2,2)),.5);
		//if( (mid.y>=sin(angle_x)/2-0.01 && mid.y<=sin(angle_x)/2+0.01 ) )
		if( xy<=xy_c && zy<=zy_c )
		{
		//	cout<<"here "<<vox_content[i].mid.y <<" actual = "<<sin(angle)/2 <<endl;
			col.x=1.2;
			col.y=2.1;
			col.z=0.2;
			vox_content[i].col=col;
		}
		else {
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[i].col=col;
		}
	}

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



void create_cylinder_voxel( float r1,float r2, float l)
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

	create_voxel(x1,x2,x3,x4,x5,x6,x7,x8);
	cout<<"No. of voxels = "<<iter<<endl;

	for(int i=0;i<iter;i++)
	{
		color col;
		float dis=pow ( (pow(vox_content[i].mid.x,2)+pow(vox_content[i].mid.z,2) ),.5);
		if(dis>=r2 && dis<=r1)
		{
			col.x=1.2;
			col.y=2.1;
			col.z=0.2;
			vox_content[i].col=col;
		}
		else {
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[i].col=col;
		}
	}

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

	create_voxel(x1,x2,x3,x4,x5,x6,x7,x8);

	cout<<"No. of voxels = "<<iter<<endl;

	for(int i=0;i<iter;i++)
	{
		color col;
		float dis=pow ( (pow(vox_content[i].mid.x,2)+pow(vox_content[i].mid.y,2)+pow(vox_content[i].mid.z,2) ),.5);
		if(dis<=r)
		{
			col.x=0.2;
			col.y=2.1;
			col.z=0.2;
			vox_content[i].col=col;
		}
		else {
			col.x=1.0;
			col.y=1.0;
			col.z=1.0;
			vox_content[i].col=col;
		}
	}
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


void color_voxel(color arr[])
{
	for(int i=0;i<iter;i++)
	{
		vox_content[i].col=arr[i];
		cout<<"color : "<<vox_content[i].col.x<<" ,"<<vox_content[i].col.y<<" ,"<< vox_content[i].col.z<<endl;
	}
}

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



void create_voxel(point x1,point x2,point x3,point x4,point x5,point x6,point x7,point x8)
{
	// First calculate area and check //

	float length=pow( ( pow(x1.x-x2.x,2)+ pow(x1.y-x2.y,2)+ pow(x1.z-x2.z,2)),.5);
	float breadth=pow( ( pow(x1.x-x4.x,2)+ pow(x1.y-x4.y,2)+ pow(x1.z-x4.z,2)),.5);
	float height=pow( ( pow(x1.x-x5.x,2)+ pow(x1.y-x5.y,2)+ pow(x1.z-x5.z,2)),.5);
	float vol= length*breadth*height;

	point cube_midpt;
	cube_midpt.x= (x1.x+ x2.x+ x3.x + x4.x + x5.x + x6.x + x7.x + x8.x)/8;
	cube_midpt.y= (x1.y +x2.y +x3.y+ x4.y+ x5.y + x6.y + x7.y + x8.y)/8;
	cube_midpt.z= (x1.z +x2.z +x3.z +x4.z+ x5.z + x6.z + x7.z + x8.z)/8;



	cout<<"volume = "<<vol<<endl;
	if(vol <0.00001)
	{
		vox_content[iter].mid=cube_midpt;
		vox_content[iter++].size=length;
	}
	else {

		

/*1*/		create_voxel(x1,midpt_side(x1,x2),midpt_surface(x1,x2,x3,x4),midpt_side(x1,x4),midpt_side(x1,x5),midpt_surface(x1,x5,x6,x2),cube_midpt,midpt_surface(x1,x5,x8,x4) );

/*2*/		create_voxel(midpt_side(x1,x2),x2,midpt_side(x2,x3),midpt_surface(x1,x2,x3,x4),midpt_surface(x1,x5,x6,x2),midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt);

/*3*/		create_voxel(midpt_surface(x1,x2,x3,x4),midpt_side(x2,x3),x3,midpt_side(x3,x4),cube_midpt,midpt_surface(x2,x6,x3,x7),midpt_side(x3,x7), midpt_surface(x3,x7,x8,x4) );

/*4*/		create_voxel(midpt_side(x1,x4),midpt_surface(x1,x2,x3,x4),midpt_side(x3,x4),x4,midpt_surface(x1,x5,x8,x4),cube_midpt,midpt_surface(x4,x8,x3,x7),midpt_side(x4,x8) );

/*5*/		create_voxel(midpt_side(x1,x5) ,midpt_surface(x1,x2,x6,x5),cube_midpt,midpt_surface(x1,x5,x8,x4),x5,midpt_side(x6,x5),midpt_surface(x5,x6,x7,x8),midpt_side(x5,x8) );

/*6*/		create_voxel(midpt_surface(x1,x2,x6,x5) ,midpt_side(x2,x6),midpt_surface(x2,x6,x7,x3),cube_midpt,midpt_side(x5,x6),x6, midpt_side(x6,x7), midpt_surface(x5,x6,x7,x8) );

/*7*/		create_voxel(cube_midpt, midpt_surface(x2,x6,x7,x3),midpt_side(x3,x7),midpt_surface(x3,x7,x8,x4), midpt_surface(x5,x6,x7,x8), midpt_side(x6,x7), x7,midpt_side(x7,x8) );

/*8*/		create_voxel(midpt_surface(x1,x5,x8,x4), cube_midpt, midpt_surface(x3,x7,x8,x4) , midpt_side(x4,x8),midpt_side(x5,x8) ,midpt_surface(x5,x6,x7,x8),midpt_side(x7,x8),x8 );

		}

}
