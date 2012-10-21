#include <iostream>
#include <stdlib.h> //Needed for "exit" function

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include "lib/octree.h"
using namespace std;
#define PI 3.14159265



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
    glTranslatef(0.0f, -1.0f, 0.0f); //Move to the center of the trapezoid


	 glPopMatrix();  
	glPushMatrix();

//	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); //Rotate the camera
	glTranslatef(1.0f, 1.5f, -2.0f);
	create_cylinder_voxel(.5,.2,1);

	glPopMatrix();
	create_sphere_voxel( 0.5);


	

/*
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
	glColor3f(2.0,2.0,2.0);
	glColor3f(1.0,1.5,1.5);
	glBegin(GL_LINES);
	glVertex3f(0.0,-0.5,0.0);
	glVertex3f(2.5,-0.5,0.0);
	glVertex3f(0.0,-0.5,0.0);
	glVertex3f(0.0,1.0,0.0);
	glVertex3f(0.0,-0.5,0.0);
	glVertex3f(0.0,-0.5,-2.5);
	glEnd();
//	glTranslatef(0.0f, 0.0f, 1.0f);
	create_hill_voxel(1,1,1);
*/	
	glutSwapBuffers(); //Send the 3D scene to the screen
}

int main(int argc, char** argv) {


	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600); //Set the window size
	
	//Create the window
	glutCreateWindow("Octree");
	initRendering(); //Initialize rendering
	
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}









