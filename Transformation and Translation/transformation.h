#include<iostream>
#include<cstdio>
#include<cmath>
#include "mat_mul.h"
using namespace std;

#define PI 3.14159265
#define n 1
void rotate(float angle,int type,float obj_matrix[][n])
{
	float rot_matrix[4][4];
	for(int i=0;i<4;i++)
	   for(int j=0;j<4;j++)
		rot_matrix[i][j] = 0;
	if(type==1){ // Rotation about X-axis
	rot_matrix[0][0] = rot_matrix[3][3]=1;
	rot_matrix[1][1]= rot_matrix[2][2]=cos(PI*angle/180);
	rot_matrix[1][2] = -sin(PI*angle/180);
	rot_matrix[2][1]= sin(PI*angle/180);
	 }
 else if(type==2){   // Rotation about Y-axis
 	rot_matrix[1][1] = rot_matrix[3][3]=1;
	rot_matrix[0][0]= rot_matrix[2][2]=cos(PI*angle/180);
 	rot_matrix[2][0] = -sin(PI*angle/180);
 	rot_matrix[0][2]= sin(PI*angle/180);
 	}
else if(type == 3){
	 rot_matrix[2][2] = rot_matrix[3][3]=1;
	 rot_matrix[0][0]= rot_matrix[1][1]=cos(PI*angle/180);
	 rot_matrix[0][1] = -sin(PI*angle/180);
	 rot_matrix[1][0]= sin(PI*angle/180);
 	}
 else{
 	printf("Error : Enter valid Axis(out of X,Y,Z)\n");
	}
	
 	mat_mul(rot_matrix,obj_matrix);

}
void scale(float sx,float sy, float sz, float obj_matrix[][n])
{
 float scal_matrix[4][4];int i,j;
 for(i=0;i<4;i++)
    for(j=0;j<4;j++)
    	scal_matrix[i][j] = 0;
 scal_matrix[0][0] = sx; scal_matrix[1][1]= sy; scal_matrix[2][2] = sz;scal_matrix[3][3] = 1;
 mat_mul(scal_matrix,obj_matrix);
}
void translate(float tx,float ty, float tz, float obj_matrix[n][n])
{
 float trans_matrix[4][4];
 for(int i =0;i<4;i++)
 	for(int j = 0;j<4;j++) 	
 	if(i==j)
 		trans_matrix[i][j] = 1;
 	else 
 		trans_matrix[i][j] = 0;
 	
 
 	trans_matrix[0][3] = tx;
  	trans_matrix[1][3] = ty;
 	trans_matrix[2][3] = tz;
 
 mat_mul(trans_matrix,obj_matrix);
}
void shear(float sxy,float syx,float syz,float szy, float sxz,float szx, float obj_matrix[][n])
{
 	float trans_matrix[4][4];
 	for(int i =0;i<4;i++)
 		for(int j = 0;j<4;j++) 	{
 			if(i==j)
 				trans_matrix[i][j] = 1;
 			else 
 				trans_matrix[i][j] = 0;
 			}	
 		
 	trans_matrix[0][1] = sxy;
 	trans_matrix[0][2] = sxz;
	trans_matrix[1][0] = syx; trans_matrix[1][2] = syz;
 	trans_matrix[2][0] = szx; trans_matrix[2][1] = szy;
 	mat_mul(trans_matrix,obj_matrix);
}

void rotate_axis(float x, float y, float z, float alpha, float beta, float theta,float obj_matrix[][n])
{
	translate(-x, -y, -z, obj_matrix);
	rotate(alpha,1,obj_matrix);
	rotate(beta,2,obj_matrix);
	rotate(theta,3,obj_matrix);
	rotate(-beta,2,obj_matrix);
	rotate(-alpha,1,obj_matrix);
	translate(x,y,z,obj_matrix);
	
}
