#include <iostream>
#include <stdlib.h> //Needed for "exit" function

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

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
  
	
	glScalef(0.7,0.8,0.7);
	//House
	
	glColor3f(0.5,0.5,0.5);
	glTranslatef(0,0.2,0);
	glutSolidCube(1);

	glColor3f(0.2,0.2,0.2);
	glPushMatrix();
	glTranslatef(-0.25,0.25,1);
	glutSolidCube(0.15);

	glTranslatef(0.5,0,0);
	glutSolidCube(0.15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,-0.3,1);
	glScalef(1,2,1);
	glutSolidCube(0.2);
	glPopMatrix();

	

//Right Roof
	glPushMatrix();
	glColor3f(0.7,0.7,0.7);
	glTranslatef(0.5,0.5,-2.0);
	glScalef(0.4,0.6,1.0);
	glRotatef(45,0,0,1);

	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glScalef(1.5,1.8,1.0);
	glTranslatef(0.5,0.1,-1.0);
	glutSolidCube(0.5);	
	glPopMatrix();

//Left Roof

	glPushMatrix();
	glColor3f(0.7,0.7,0.7);
	glTranslatef(-0.5,0.5,-2.0);
	glScalef(0.4,0.6,1.0);
	glRotatef(45,0,0,1);

	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glScalef(1.5,1.8,1.0);
	glTranslatef(-0.5,0.1,-1.0);
	glutSolidCube(0.5);	
	glPopMatrix();

//Middle Roof

	glPushMatrix();
	glTranslatef(0,1.1,-2.0);
	glScalef(1.40,0.92,1.0);
	glColor3f(0.7,0.7,0.7);
	glutSolidCube(0.8);
	glPopMatrix();


	glPopMatrix();



//Tree

	glColor3f(0.5,0.2,0.2);
	glPushMatrix();
	glTranslatef(-1.3,0.2,0);
	glScalef(0.3,1.5,0.2);
	glutSolidCube(0.5);
	glPopMatrix();

//Tree Right
	
	glPushMatrix();
	glColor3f(0.2,2.4,0.5);
	glTranslatef(-2.2,0.2,-4.0);
	glScalef(1,4,0.2);
	glRotatef(45,0,0,1);

	glutSolidCube(0.7);
	glPopMatrix();
/*
	glPushMatrix();
	glColor3f(0,0,0);
	glScalef(1.5,1.8,1.0);
	glTranslatef(-0.5,0.1,-1.0);
	glutSolidCube(0.5);	
	glPopMatrix();
	
*/

//Tree Left
	
	glPushMatrix();
	glColor3f(0.2,2.4,0.5);
	glTranslatef(-2.5,0.2,-4.0);
	glScalef(1,4,0.2);
	glRotatef(45,0,0,1);

	glutSolidCube(0.7);
	glPopMatrix();

//Blacking

	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(-2.0,-0.4,-2.0);
	glScalef(1.5,2,1.0);
	glutSolidCube(1);	
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2,2.4,0.5);
	glTranslatef(-1.3,1.0,0);
	glScalef(0.6,1.3,0.2);
	glutSolidCube(0.3);
	
	glPopMatrix();
	
//Human
	glPushMatrix();
	glTranslatef(1.4,0.5,0);

	glScalef(0.5,1.0,0.2);
	glutSolidCube(0.5);
	
	glTranslatef(-0.15,-0.4,0);

	glScalef(0.8,2.0,0.2);
	glutSolidCube(0.2);

	glTranslatef(0.40,0,0);
	glutSolidCube(0.2);

	glScalef(1.4,0.8,0.2);
	glTranslatef(-0.15,0.4,0);
	glutSolidCube(0.1);

	glScalef(1.3,0.5,1);
	glTranslatef(0,0.2,0);
	glutSolidCube(0.2);

//Hand Left
	glPushMatrix();
	glScalef(1,2,1);
	glTranslatef(-0.18,-0.25,-2);
	glRotatef(45,0,0,1);
	glutSolidCube(0.2);

	glColor3f(0,0,0);
	glTranslatef(-0.0,-0.1,1);
	glutSolidCube(0.3);
	glPopMatrix();

//Hand Right
	glColor3f(0.2,2.4,0.5);
	glPushMatrix();
	glScalef(1,2.1,1);
	glTranslatef(0.3,-0.12,-2);
	glRotatef(-45,0,0,1);
	glutSolidCube(0.2);

	glColor3f(0,0,0);
	glTranslatef(-0.0,0.1,1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPopMatrix();

//Eyes
	glPushMatrix();
	glColor3f(0.5,0.5,0.5);
	glTranslatef(1.35,0.92,0);
	glScalef(0.35,0.35,0.35);
	glutSolidCube(0.08);
	glTranslatef(0.27,0,0);
	glutSolidCube(0.08);
	glTranslatef(-0.135,-0.2,0);
	glScalef(2,0.5,1);
	glutSolidCube(0.1);
	glTranslatef(0,0.2,0);
	glScalef(0.2,2,1);
	glutSolidCube(0.1);
	glPopMatrix();

//Road
	glPushMatrix();
	glColor3f(0.2,0.2,0.2);
	glScalef(1.6,0.2,0.1);
	glTranslatef(-0.65,-3.2,0);
	//glRotatef(45,0,0,1);
	glutSolidCube(1);

	glPopMatrix();

	
	glPushMatrix();
	glColor3f(0.2,0.2,0.2);
	glScalef(0.5,0.8,0.3);
	glTranslatef(-0,-0.8,-2);
	glRotatef(45,0,0,1);
	glutSolidCube(1);

	glScalef(1.2,1,1);
	glColor3f(0,0,0);
	glTranslatef(0.1,-0.3,1);
	glutSolidCube(1);
	glPopMatrix();

	glutSwapBuffers(); //Send the 3D scene to the screen
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800); //Set the window size
	
	//Create the window
	glutCreateWindow("Basic Shapes - videotutorialsrock.com");
	initRendering(); //Initialize rendering
	
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}









