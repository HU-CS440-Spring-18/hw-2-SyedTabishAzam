#include <stdlib.h>
#include <iostream>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define PI 3.14159265

const int SCREEN_W = 320;
const int SCREEN_H = 320;


using namespace std;

class Prototype
{
    /*Class to generate instance of prototype*/
private:
    float horizontalLength;
    float verticalLength;
    float startXglobal;
    float startYglobal;
    float rotation = 0;
public:
    Prototype(float hLength, float vLength,float startX,float startY,float angle)
    {
        horizontalLength = hLength;
        verticalLength = vLength;
        startXglobal = startX;
        startYglobal = startY;
        rotation = angle;
    }

    void transformFunction(float hLength, float vLength,float startX,float startY,float angle)
    {
        horizontalLength = hLength;
        verticalLength = vLength;
        startXglobal = startX;
        startYglobal = startY;
        rotation = angle;
    }

    void drawPrototype()
    {

        glPushMatrix();
        glRotated(rotation,0,0,1);
        glBegin(GL_LINES);
            glVertex2f(startXglobal,startYglobal);
            glVertex2f(startXglobal,startYglobal + verticalLength);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(startXglobal,startYglobal + verticalLength);
            glVertex2f(startXglobal+horizontalLength,startYglobal + verticalLength);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(startXglobal+horizontalLength,startYglobal + verticalLength);
            glVertex2f(startXglobal+horizontalLength,startYglobal);
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(startXglobal+horizontalLength,startYglobal);
            glVertex2f(startXglobal,startYglobal);
        glEnd();

        glPopMatrix();

    }
};

Prototype* pr;

void renderScene(void) {

	// Clear Color and Depth Buffers

    glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glColor3f(1.0f,0,0);

    pr->transformFunction(72,72,14,14,45);
    pr->drawPrototype();
    pr->transformFunction(8,8,45,45,45);
    pr->drawPrototype();
    pr->transformFunction(8,8,20,60,0);
    pr->drawPrototype();
    pr->transformFunction(8,8,70,60,0);
    pr->drawPrototype();
    pr->transformFunction(45,8,27,25,0);
    pr->drawPrototype();

	glutSwapBuffers();
}






void keyboardInput(unsigned char key, int x, int y) {

	if (key == 'q' || key=='Q')
		exit(0);


}


int main(int argc, char **argv) {

	// init GLUT and create window



	glutInit(&argc, argv);
    pr = new Prototype(0,0,0,0,0);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(SCREEN_W,SCREEN_H);
	glutCreateWindow("Instance - Question 1");

	// register callbacks
	glOrtho(0,100,0,100,0,1);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(keyboardInput);



	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
