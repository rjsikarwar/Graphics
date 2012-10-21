#include <iostream>
#include <stdlib.h> 

#include <GL/glut.h>
#include <cmath>
using namespace std;
#define PI 3.14159265


typedef struct _point{
	float x;
	float y;
	float z;
	}point;

typedef struct _color{
	float x;
	float y;
	float z;
	}color;

typedef struct _voxel{
	color col;
	point mid;
	float size;
	}voxel;
	


void create_voxel(point x1,point x2,point x3,point x4,point x5,point x6,point x7,point x8);
void color_voxel(color arr[]);
point fill_point(float x,float y,float z);
void create_hill_voxel( float x,float y, float z);
void create_cylinder_voxel( float r1,float r2, float l);
void create_sphere_voxel( float r);
point midpt_surface(point x1,point x2,point x3,point x4);
point midpt_side(point x1,point x4);

