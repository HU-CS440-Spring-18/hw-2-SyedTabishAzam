#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif // platform
#include "math.h"
#include <iostream>
#define PI 3.14159265
using namespace std;

const int SCREEN_W = 60;
const int SCREEN_H = 60;
const int MAX_POLY = 2;
int depth;
int startingY = 0;
int heightOfWindow;
void drawLine(GLfloat[],GLfloat[]);
void KochLine(GLfloat A[2], GLfloat B[2],int);
GLfloat* findNextVertexFromPosition(GLfloat a[2],float length,double);
double findAngleBetweenPoints(GLfloat[], GLfloat[],float);
GLfloat* midOftwo(GLfloat a[2],GLfloat b[2]);

void kochSnowflake(GLfloat P[2],
GLfloat Q[2],
GLfloat R[2],int);

float Eucledian(GLfloat a[2], GLfloat b[2]);

void KochLine(GLfloat A[2], GLfloat B[2],int depth) {
// segment endpoints.

        float fullLength = Eucledian(A,B);
        float lengthOfLine = fullLength/3;
        double initialAngle = findAngleBetweenPoints(A,B,fullLength);

        GLfloat* get1 = findNextVertexFromPosition(A,lengthOfLine,initialAngle);
        GLfloat v0[2] = {get1[0],get1[1]};


        GLfloat* get2 = findNextVertexFromPosition(get1,lengthOfLine,initialAngle+60);
        GLfloat midpoint[2] = {get2[0],get2[1]};

        GLfloat* get3 = findNextVertexFromPosition(midpoint,lengthOfLine,initialAngle-60);
        GLfloat v1[2] = {get3[0],get3[1]};


        // begin transformations.
        if(depth==0)
        {
            glPushMatrix();
            drawLine(A, B);
            glPopMatrix();
        }
        else if(depth==1)
        {


            glPushMatrix();
            /* Transformation magic. */

            /* Assign v0, v1; only once. */
            drawLine(A, v0);
            /* Transformation magic. */
            drawLine(v0, midpoint);
            /* Transformation magic. */
            drawLine(midpoint, v1);
            /* Transformation magic. */
            drawLine(v1, B);
            // end transformations.
            glPopMatrix();
        }
        else if(depth>1)
        {
            KochLine(A,v0,depth-1);
            KochLine(v0,midpoint,depth-1);
            KochLine(midpoint,v1,depth-1);
            KochLine(v1,B,depth-1);
        }

}
double findAngleBetweenPoints(GLfloat a[],GLfloat b[],float length)
{
    /*Function that calculate angles between two coordinate in form (x,y)*/
    float base = b[0] - a[0];

    float perp = b[1] - a[1];
    double rad = atan(fabs(perp)/fabs(base));

    double angle = (rad*180/PI);
    if(base>0 && perp > 0)
    {
        return angle;
    }
    else if(base>0 && perp <= 0)
    {

        return 360 - angle;
    }
    else if(base<=0 && perp > 0)
    {
        return 180-(rad*180/PI);
    }
    else if(base<=0 && perp <=0)
    {

        return 180+(rad*180/PI);
    }



}
GLfloat* findNextVertexFromPosition(GLfloat a[2],float length,double angleRad)
{
    /*Function that find the coordinates of next vertex based on length and angle*/
    double angle = angleRad * PI / 180.0;
    float initialX,initialY,finalX,finalY;
    initialX = a[0];
    initialY = a[1];
    float cosA = cos(angle);

    finalX = initialX + (cos(angle)*length);
    finalY = initialY + (sin(angle)*length);
    GLfloat ret[] = {finalX,finalY};
    return ret;
}

GLfloat* midOftwo(GLfloat a[2],GLfloat b[2])
{
    /*To calculate middle vertex of two coordinates */
    float x1,y1,x2,y2;
    x1 = a[0];
    y1 = a[1];
    x2 = b[0];
    y2 = b[1];

    GLfloat ret[] = {x1+x2/2,y1+y2/2};
    return ret;
}

float Eucledian(GLfloat a[2], GLfloat b[2])
{
    /*Simple Eucledian calculater*/
    float x1,x2,y1,y2;

    x1 = a[0];
    x2 = b[0];
    y1 = a[1];
    y2 = b[1];

    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

void kochSnowflake(GLfloat P[2],
GLfloat Q[2],
GLfloat R[2], int depth) {

KochLine(P, Q, depth);
KochLine(Q, R, depth);
KochLine(R, P, depth);
}


void drawLine(GLfloat A[2], GLfloat B[2]) {
glBegin(GL_LINES);
glVertex2fv(A);
glVertex2fv(B);
glEnd();
}

void display() {
// GL stuff.
// equilateral triangle
    GLfloat v[3][2] = {{5,14},
    {25, 48.64},
    {45, 14}};

    // begin transformations.

    glPushMatrix();
    /* Transformation magic. */

    for(int rec=0;rec<=depth;rec++)
    {
        int level2 = rec / MAX_POLY;
        int xPos = rec % MAX_POLY;
        cout<<level2<<" now"<<((level2)*280)<<endl;
        glViewport( (GLsizei) (SCREEN_W) + (300*xPos), (heightOfWindow*300)-((level2+1)*280), (GLsizei) 320, (GLsizei) 320 );
        kochSnowflake(v[0], v[1], v[2],rec);
    }

    /* Transformation magic. */

    // end transformations.
    glPopMatrix();
    glFlush();
}

void keyboardEvent(unsigned char key,int x,int y)
{
    if(key=='q' || key=='Q')
        exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    depth = 3;
    heightOfWindow = depth / MAX_POLY;
    heightOfWindow +=1;
    cout<<"height"<<heightOfWindow<<endl;
    glutInitWindowSize(350*MAX_POLY, heightOfWindow*300);
    glutInitWindowPosition(0   , 0);
    glutCreateWindow("Koch flakes - Question 3");
    glutDisplayFunc(display);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,SCREEN_W,0,SCREEN_H,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glutKeyboardFunc(keyboardEvent);

    glutMainLoop();
    return 0;
}
