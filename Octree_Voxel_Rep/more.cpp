
#include <iostream>
#include <stdlib.h> //Needed for "exit" function
#include <cmath>
//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

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
    glTranslatef(-1.5f, 0.0f, 0.0f); //Move to the center of the trapezoid

	

	glBegin(GL_QUADS); //Begin quadrilateral coordinates
	
	glColor3f(1.0f, 1.0f, 0.0f);
	//Trapezoid
	glVertex3f(-0.7f, -1.5f, -5.0f);
	glVertex3f(0.7f, -1.5f, -5.0f);
	glVertex3f(0.4f, -0.5f, -5.0f);
	glVertex3f(-0.4f, -0.5f, -5.0f);
	

	
	glEnd(); //End quadrilateral coordinates
	 glPopMatrix();   

	glBegin(GL_TRIANGLES); //Begin triangle coordinates
	
	//Pentagon
	glVertex3f(0.5f, 0.5f, -5.0f);
	glVertex3f(1.5f, 0.5f, -5.0f);
	glVertex3f(0.5f, 1.0f, -5.0f);
	
	glVertex3f(0.5f, 1.0f, -5.0f);
	glVertex3f(1.5f, 0.5f, -5.0f);
	glVertex3f(1.5f, 1.0f, -5.0f);
	
	glVertex3f(0.5f, 1.0f, -5.0f);
	glVertex3f(1.5f, 1.0f, -5.0f);
	glVertex3f(1.0f, 1.5f, -5.0f);
	
	//Triangle
	glVertex3f(-0.5f, 0.5f, -5.0f);
	glVertex3f(-1.0f, 1.5f, -5.0f);
	glVertex3f(-1.5f, 0.5f, -5.0f);
	
	glEnd(); //End triangle coordinates
        glBegin(GL_QUADS); //Begin quadrilateral coordinates
	
	glColor3f(1.0f, 0.0f, 0.0f);
	//Trapezoid
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-2.0f, -1.0f, -1.0f);
	glVertex3f(-2.0f, -2.0f, -1.0f);
	glVertex3f(-1.0f, -2.0f, -1.0f);
	
	glColor3f(2.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -2.0f);
	glVertex3f(-2.0f, -1.0f, -2.0f);
	glVertex3f(-2.0f, -2.0f, -2.0f);
	glVertex3f(-1.0f, -2.0f, -2.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-2.0f, -1.0f, -1.0f);
	glVertex3f(-2.0f, -1.0f, -2.0f);
	glVertex3f(-1.0f, -1.0f, -2.0f);

	glColor3f(1.0f, 2.0f, 2.0f);
	glVertex3f(-2.0f, -2.0f, -2.0f);
	glVertex3f(-1.0f, -2.0f, -2.0f);
	glVertex3f(-1.0f, -2.0f, -1.0f);
	glVertex3f(-2.0f, -2.0f, -1.0f);
	
	glEnd(); //End quadrilateral coordinates


		
		
	for(int i=0;i<90;i++){
//	
	glTranslatef(-1.0f,1.0f,0.0f);
	glBegin(GL_LINES);
	
	glVertex3f(+0.0f, 0.0f, 0.0f);
	glVertex3f(+0.5f, 0.5f, 0.0f);

	glVertex3f(+0.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);


	glEnd();
	glRotatef(4.0f,0.0f,1.0f,0.0f);

	glTranslatef(1.0f,-1.0f,0.0f);
//	glTranslatef(0.5f,1.0f,0.0f);

//	

	}

	glColor3f(1.0f, 0.0f, 1.0f);
//	glutWireSphere(0.5f,   //Radius
 //                   50, 8); //Indicate the # of polygons used to draw the sphere
    //...
	glPushMatrix();
	glTranslatef(2.0f,-1.0f,-3.0f);
	glutWireTeapot( 1);
//	glTranslatef(-2.0f,+1.0f,+3.0f);
	glPopMatrix();

	//glutWireTorus(1.0f,2.0f,50,5);
	glPushMatrix();
//	glTranslatef(1.0f,2.0f,-3.0f);
	glColor3f(2.2f, 0.0f, 0.0f);
	glutSolidCube(0.5f);
	glPopMatrix();
//	glTranslatef(-1.0f,-2.0f,+3.0f);

	glPushMatrix();
	glTranslatef(0.0f,0.25f,0.0f);
	glColor3f(0.5f, 0.0f, 0.0f);
//	glutSolidCube(0.5f);
	glutSolidSphere(0.25,30,30);


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
	glutCreateWindow("PART 2");
	initRendering(); //Initialize rendering
	
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}









