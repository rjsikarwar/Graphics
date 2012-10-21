
#include <iostream>
#include <stdlib.h> //Needed for "exit" function
#include <cmath>
//Include OpenGL header files, so that we can use OpenGL

#include <GL/glut.h>
#include "transformation.h"
using namespace std;


typedef struct _point{
	float arr[4][1];
	}point;

point cube_mid(point,point,point,point,point,point,point,point);
void fill_point(float [][1],float ,float ,float );
void fill_cube(float ,point []);

void fill_cube(float r,point block[])
{
	r/=2;
	fill_point(block[0].arr,-r,r,r);
	fill_point(block[1].arr,r,r,r);
	fill_point(block[2].arr,r,-r,r);
	fill_point(block[3].arr,-r,-r,r);
	fill_point(block[4].arr,-r,r,-r);
	fill_point(block[5].arr,r,r,-r);
	fill_point(block[6].arr,r,-r,-r);
	fill_point(block[7].arr,-r,-r,-r);
}

void draw_cube(point block[])
{
	glBegin(GL_QUADS);	
//1
	glVertex3f(block[0].arr[0][0],block[0].arr[1][0],block[0].arr[2][0]);
	glVertex3f(block[1].arr[0][0],block[1].arr[1][0],block[1].arr[2][0]);
	glVertex3f(block[2].arr[0][0],block[2].arr[1][0],block[2].arr[2][0]);
	glVertex3f(block[3].arr[0][0],block[3].arr[1][0],block[3].arr[2][0]);

//2	
	glVertex3f(block[0].arr[0][0],block[0].arr[1][0],block[0].arr[2][0]);
	glVertex3f(block[1].arr[0][0],block[1].arr[1][0],block[1].arr[2][0]);
	glVertex3f(block[5].arr[0][0],block[5].arr[1][0],block[5].arr[2][0]);
	glVertex3f(block[4].arr[0][0],block[4].arr[1][0],block[4].arr[2][0]);
//3

	glVertex3f(block[1].arr[0][0],block[1].arr[1][0],block[1].arr[2][0]);
	glVertex3f(block[5].arr[0][0],block[5].arr[1][0],block[5].arr[2][0]);
	glVertex3f(block[6].arr[0][0],block[6].arr[1][0],block[6].arr[2][0]);
	glVertex3f(block[2].arr[0][0],block[2].arr[1][0],block[2].arr[2][0]);
//4

	glVertex3f(block[4].arr[0][0],block[4].arr[1][0],block[4].arr[2][0]);
	glVertex3f(block[5].arr[0][0],block[5].arr[1][0],block[5].arr[2][0]);
	glVertex3f(block[6].arr[0][0],block[6].arr[1][0],block[6].arr[2][0]);
	glVertex3f(block[7].arr[0][0],block[7].arr[1][0],block[7].arr[2][0]);

//5
	glVertex3f(block[0].arr[0][0],block[0].arr[1][0],block[0].arr[2][0]);
	glVertex3f(block[4].arr[0][0],block[4].arr[1][0],block[4].arr[2][0]);
	glVertex3f(block[7].arr[0][0],block[7].arr[1][0],block[7].arr[2][0]);
	glVertex3f(block[3].arr[0][0],block[3].arr[1][0],block[3].arr[2][0]);

//6

	glVertex3f(block[3].arr[0][0],block[3].arr[1][0],block[3].arr[2][0]);
	glVertex3f(block[2].arr[0][0],block[2].arr[1][0],block[2].arr[2][0]);
	glVertex3f(block[6].arr[0][0],block[6].arr[1][0],block[6].arr[2][0]);
	glVertex3f(block[7].arr[0][0],block[7].arr[1][0],block[7].arr[2][0]);

	glEnd();


}



/*
point cube_mid(point x1,point x2,point x3,point x4,point x5,point x6,point x7,point x8)
{
	point cube_midpt;
	cube_midpt.x= (x1.x+ x2.x+ x3.x + x4.x + x5.x + x6.x + x7.x + x8.x)/8;
	cube_midpt.y= (x1.y +x2.y +x3.y+ x4.y+ x5.y + x6.y + x7.y + x8.y)/8;
	cube_midpt.z= (x1.z +x2.z +x3.z +x4.z+ x5.z + x6.z + x7.z + x8.z)/8;
	
	return cube_midpt;
}
*/
void fill_point(float arr[][1],float x,float y,float z)
{
	arr[0][0]=x;arr[1][0]=y;arr[2][0]=z,arr[3][0]=1;

}

//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
					int x, int y) {    //The current mouse coordinates
	switch (key) {
		case 27: //Escape key
			exit(0); //Exit the program
	}
}

//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate*/
}

//Draws the 3D scene
void drawScene() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	

    glTranslatef(0.0f, 0.0f, -5.0f); //Move forward 5 units
    
    glPushMatrix(); //Save the transformations performed thus far

	float r=0.8;	//side of cube

//House
	point block[8],house_left[8],house_right[8],window_left[8],window_right[8],door[8];

	fill_cube(r,block);
	fill_cube(2*r/3,house_left);
	fill_cube(2*r/3,house_right);
	fill_cube(r/5,window_left);
	fill_cube(r/5,window_right);
	fill_cube(r/4,door);

	for(int i=0;i<8;i++)
	{
		translate(1,0,-0.2,block[i].arr);
		translate(1-5*r/11,4*r/5,-0.2,house_left[i].arr);
		shear(r/3,0,0,0,0,0,house_left[i].arr);
		translate(1+5*r/11,4*r/5,-0.2,house_right[i].arr);
		shear(-r/3,0,0,0,0,0,house_right[i].arr);
		translate(1-r/3,r/4,0.2,window_left[i].arr);
		translate(1+r/3,r/4,0.2,window_right[i].arr);
		translate(1,-r/8,0.2,door[i].arr);
		scale(1,2,1,door[i].arr);
		
	}
	
	glColor3f(0.5,0.2,0.2);

	draw_cube(block);
	draw_cube(house_left);
	draw_cube(house_right);

	glColor3f(0.2,0.2,0.2);
	
	draw_cube(window_left);
	draw_cube(window_right);
	draw_cube(door);


//Tree

	point trunk[8],tree_left[8],tree_right[8];
	fill_cube(r/4,trunk);
	fill_cube(r/4,tree_left);
	fill_cube(r/4,tree_right);
	

	for(int i=0;i<8;i++)
	{

		scale(1.5,4.5,1,tree_left[i].arr);
		scale(1.5,4.5,1,tree_right[i].arr);
		scale(1,4,1,trunk[i].arr);
		shear(r/3,0,0,0,0,0,tree_left[i].arr);
		shear(-r/3,0,0,0,0,0,tree_right[i].arr);

		translate(-1.5-r/6,-.5+r/3.5,-0.2,tree_left[i].arr);
		translate(-1.5+r/6,-.5+r/3.5,-0.2,tree_right[i].arr);
		translate(-1.5,-.5-r/3,-0.2,trunk[i].arr);
		
	}	

	glColor3f(0.5,0.2,0.2);
	draw_cube(trunk);
	
	glColor3f(0.2,2.4,0.5);
	draw_cube(tree_left);
	draw_cube(tree_right);

//Road

	point road_left[8],road_centre[8],road_right[8];

	fill_cube(r/4,road_left);
	fill_cube(r/4,road_centre);
	fill_cube(r/4,road_right);

	
	for(int i=0;i<8;i++)
	{

		scale(12,1,1,road_left[i].arr);
		scale(1.5,3,1,road_centre[i].arr);
		scale(1.5,2,1,road_right[i].arr);
		shear(r,0,0,0,0,0,road_centre[i].arr);

		translate(-0.5,-1.2,0,road_left[i].arr);
		translate(0.8,-1,0,road_centre[i].arr);
		translate(1.05,-0.7+r/4,0,road_right[i].arr);
		
	}	
	
	glColor3f(0.3,0.3,0.3);
	draw_cube(road_left);
	draw_cube(road_centre);
	draw_cube(road_right);

//Human

	point face[8],neck[8],eye_right[8],eye_left[8],nose[8],mouth[8],hand_left[8],hand_right[8],torso[8],leg_left[8],leg_right[8];
	fill_cube(r/4,face);
	fill_cube(r/4,neck);
	fill_cube(r/4,eye_right);
	fill_cube(r/4,eye_left);
	fill_cube(r/4,nose);
	fill_cube(r/4,mouth);
	fill_cube(r/4,hand_left);
	fill_cube(r/4,hand_right);
	fill_cube(r/4,torso);
	fill_cube(r/4,leg_left);
	fill_cube(r/4,leg_right);
	for(int i=0;i<8;i++)
	{
		scale(1.4,1.2,1,face[i].arr);
		scale(.2,.2,.2,eye_left[i].arr);
		scale(.2,.2,.2,eye_right[i].arr);
		scale(.5,.15,.2,mouth[i].arr);
		scale(.2,.4,.2,nose[i].arr);
		scale(.8,.8,1,neck[i].arr);
		scale(3,4,1,torso[i].arr);
		scale(0.7,4.2,1,hand_right[i].arr);
		scale(0.7,4.2,1,hand_left[i].arr);
		translate(2*r/3,1.18-0.8*r,-5,hand_right[i].arr);
		shear(-r/3,0,0,0,0,0,hand_right[i].arr);
		translate(-2*r/3,1.18-0.8*r,-5,hand_left[i].arr);
		shear(r/3,0,0,0,0,0,hand_left[i].arr);
		scale(0.9,4.5,1,leg_right[i].arr);
		scale(0.9,4.5,1,leg_left[i].arr);
		translate(0,1.2,-5,face[i].arr);
		translate(-0.1,1.18,-4.8,eye_left[i].arr);
		translate(0.1,1.18,-4.8,eye_right[i].arr);
		translate(0,1.13,-4.8,nose[i].arr);
		translate(0.0,1.05,-4.8,mouth[i].arr);

		translate(0,1.2-r/4,-5,neck[i].arr);
		translate(0,1.2-0.8*r,-5,torso[i].arr);
		translate(-r/4.5,-r/3,-5,leg_left[i].arr);
		translate(r/4.5,-r/3,-5,leg_right[i].arr);
		/*shear(r,0,0,0,0,0,road_centre[i].arr);

		translate(-0.5,-1.2,0,road_left[i].arr);
		translate(0.8,-1,0,road_centre[i].arr);
		translate(1.05,-0.7+r/4,0,road_right[i].arr);*/
		
	}
	glColor3f(0.3,0.3,0.3);
	draw_cube(face);
	draw_cube(neck);
	draw_cube(torso);
	draw_cube(leg_left);
	draw_cube(leg_right);
	draw_cube(hand_left);
	draw_cube(hand_right);
	glColor3f(0.2,1.3,0.1);
	draw_cube(nose);
	draw_cube(eye_left);
	draw_cube(eye_right);
	draw_cube(mouth);
	glPopMatrix();
	//glTranslatef(-1.0f,-2.0f,-3.0f);

	glutSwapBuffers(); //Send the 3D scene to the screen
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800); //Set the window size
	
	//Create the window
	glutCreateWindow("PART 1");
	initRendering(); //Initialize rendering
	
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}









