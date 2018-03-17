#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif // platform
#include "math.h"
#include <iostream>
#include <complex>

using namespace std;
 GLUquadric* qobj;
  GLUquadric* body;
char title[] = "3D Shapes";
string ACTION = "STOP";
bool revers = true;
bool reversTail = true;
bool kicking = false;
bool throwBall = false;
bool rotateNeck = false;
bool pickup = false;
bool boneInMouth = false;
bool atNeckRest = true;
bool atLegRest = true;
float walkExt1 = 0;
float walkExt2 = 0;
float wagAngle = 280;
float revolve = 0;
float neckRotateFactor = 0;
float forwardPos = 3;
float factor = 0;
float elivate = -0.5;
void drawDog();
void drawBone();
void drawBall();
void kickBall();
void walk(string);
void wagTail();
void pickBone();
void DoAction();
static int slices = 16;
static int stacks = 16;
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
    DoAction();
   glTranslatef(-3, 0.0f, -7.0f);  // Move right and into the

    glPushMatrix();
    drawBall();
    glPopMatrix();



    glTranslated(1,0,0);

    glPushMatrix();
        if(pickup && !rotateNeck && (neckRotateFactor>0) && (elivate<1.2))
        {
            elivate = elivate + 0.005;
            boneInMouth = true;
        }
        if(boneInMouth)
        {
            glTranslated(forwardPos-0.8,elivate,1);
        }
        else
        {

            glTranslated(0,elivate,0);
        }
        drawBone();

    glPopMatrix();

   glTranslatef(forwardPos, 0.0f, 0);  // Move left and into the screen

   drawDog();


   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}



void drawBall()
{
    /*Ball drawn using sphere  - further logic added for kicking*/
    glColor3d(1,0,0);
    glPushMatrix();
    if(throwBall)
    {
        glTranslated(0,factor-1.2,0);
        factor = factor + 0.007;

        if(factor>10)
        {

            throwBall = false;
        }
    }
    else
    {
        if(factor>0)
        {

            factor = factor - 0.007;
        }
       glTranslated(0,factor-1.2,0);
    }
        glutSolidSphere(0.5,16,16);
    glPopMatrix();
}
void drawBone()
{
    /*Bone drawn using sphere and cylinder of white color */
    qobj = gluNewQuadric();
    glColor3d(1,1,1);

    glPushMatrix();
        glutSolidSphere(0.25,16,16);
        glTranslated(0,-0.4,0);
        glutSolidSphere(0.25,16,16);
        glTranslated(0,0.2,0);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-0.2,0);
        glRotated(90,0,1,0);
        gluCylinder(qobj, 0.1, 0.1, 1, 16, 1);
    glPopMatrix();

    glPushMatrix();

        glTranslated(1.2,-0.35,0);
        glutSolidSphere(0.25,16,16);
        glTranslated(0,0.3,0);
        glutSolidSphere(0.25,16,16);
    glPopMatrix();


}
void drawDog()
{
    /*Routing to draw dog using cubes cylinder and cone. Logic added for animation*/
    GLUquadricObj* body = gluNewQuadric();
    GLUquadricObj* tail = gluNewQuadric();

    glColor3d( 0.647059,0.164706,0.164706);

    //Body
    glPushMatrix();
    glRotated(80,0,1,0);
    gluCylinder(body, 0.5, 0.5, 2, 16, 1);
    glPopMatrix();

    //Tail
    glPushMatrix();
    glTranslated(2,0.3,0);
    glRotated(80,0,1,0);
    glRotated(wagAngle,1,0,0);
    gluCylinder(body, 0.1, 0.05, 0.8, 16, 1);
    glPopMatrix();


    //Neck
    glPushMatrix();
    glTranslated(0.3,0.3,0);
    if(rotateNeck)
    {
        atNeckRest = false;
        glRotated(neckRotateFactor,0,0,1);
        neckRotateFactor +=0.05;

        if(neckRotateFactor>80)
        {

            rotateNeck = false;
        }

    }
    else
    {
        glRotated(neckRotateFactor,0,0,1);
        if(neckRotateFactor>0)
        {
            neckRotateFactor-=0.05;
        }
        else
        {
            atNeckRest = true;
        }

    }
    glRotated(80,0,1,0);
    glRotated(240,1,0,0);
    gluCylinder(tail, 0.3, 0.3, 0.8, 16, 1);
    glRotated(120,1,0,0);
    glRotated(280,0,1,0);
    glTranslated(-0.3,-0.3,0);
        //Head
        glPushMatrix();
        glTranslated(-0.2,1.2,0);

        glutSolidSphere(0.5,16,16);
        glPopMatrix();

        //eye 1
        glColor3d(1,1,1);
        glPushMatrix();
        glTranslated(-0.5,1.25,0.5);
        glutSolidSphere(0.1,16,16);
        glColor3d(0,0,0);
        glTranslated(0,-0.03,0.03);
        glutSolidSphere(0.08,16,16);
        glPopMatrix();

        //eye 2
        glColor3d(1,1,1);
        glPushMatrix();
        glTranslated(-0.2,1.35,0.5);
        glutSolidSphere(0.1,16,16);
        glColor3d(0,0,0);
        glTranslated(0,-0.03,0.03);
        glutSolidSphere(0.08,16,16);
        glPopMatrix();

        //nose
        glColor3d(0,0,0);
        glPushMatrix();
        glTranslated(-0.3,1.05,0.5);
        glutSolidSphere(0.1,16,16);
        glPopMatrix();

        //ear 1
        glColor3d(0,0,0);
        glPushMatrix();
        glTranslated(-0.5,1.35,0);
         glRotated(260,0,1,0);
         glRotated(340,1,0,0);
        glutSolidCone(0.2,0.5,16,16);
        glPopMatrix();

        //ear 2
        glColor3d(0,0,0);
        glPushMatrix();
        glTranslated(0,1.50,0);
         glRotated(90,0,1,0);
         glRotated(295,1,0,0);
        glutSolidCone(0.2,0.5,16,16);
        glPopMatrix();

    glPopMatrix();

    //legs
    glColor3d( 0.647059,0.164706,0.164706);


    for(int frontBack=0;frontBack<2;frontBack++)
    {

        glTranslated(frontBack*1.2,0,0);

        //Leg and joint
        glPushMatrix();
        if((kicking==true) && (frontBack==0))
        {
            atLegRest = false;
            glRotated(revolve,0,0,1);
            revolve=revolve-0.1;
            if(revolve<walkExt1- 50)
            {
                kicking = false;

                //revolve = walkExt1;
            }
        }else if((kicking==false) && (frontBack==0))
        {

            if(revolve<0)
            {

                revolve=revolve+0.1;
            }
            else
            {
                atLegRest = true;
            }



            glRotated(revolve,0,0,1);
        }

        glRotated(walkExt1,0,0,1);
        glTranslated(0.2,-0.75,0);
        glRotated(80,0,1,0);
        glRotated(290,1,0,0);
        gluCylinder(body, 0.1, 0.05, 0.3, 16, 1);
        glRotated(150,1,0,0);
        gluCylinder(body, 0.1, 0.05, 0.4, 16, 1);

            //Paw front leg
            glPushMatrix();
            glRotated(270,1,0,0);
            glTranslated(0,-0.4,-0.15);
            gluCylinder(body, 0.05, 0.1, 0.2, 16, 1);
            glPopMatrix();
        glPopMatrix();


        //pairedLeg
        glPushMatrix();
        int hingeRotate = 360-walkExt1;
        glRotated(hingeRotate,0,0,1);
        glTranslated(0.6,-0.75,0);

        glRotated(80,0,1,0);
        glRotated(290,1,0,0);
        gluCylinder(body, 0.1, 0.05, 0.3, 16, 1);
        glRotated(150,1,0,0);
        gluCylinder(body, 0.1, 0.05, 0.5, 16, 1);
        glPopMatrix();

        //pawPairdLeg
        glPushMatrix();
        glRotated(hingeRotate,0,0,1);
        glTranslated(0.5,-1.25,0);
        glRotated(80,0,1,0);
        glRotated(350,1,0,0);
        gluCylinder(body, 0.05, 0.1, 0.2, 16, 1);
        glPopMatrix();
        glPopMatrix();
    }

}

void pickBone()
{

    if(atNeckRest)
    {

        if(!boneInMouth)
        {

        rotateNeck = true;

            if(forwardPos>0.6 && forwardPos < 1.5)
            {

                pickup = true;
            }
        }
    }
}

void kickBall()
{

    if(atLegRest)
    {

        kicking = true;
        if(forwardPos<0.5f && forwardPos > -2.5f)
        {
            throwBall = true;
        }
    }
}

void wagTail()
{
    if((wagAngle>320) && (reversTail==true))
    {

        reversTail = false;

    }
    if(wagAngle<300 && (!reversTail))
    {


        reversTail = true;

    }

    if(!reversTail)
    {

        wagAngle = wagAngle-0.05;

    }
    else
    {


        wagAngle = wagAngle + 0.05;
    }
}

void walk(string direction)
{

    if((walkExt1>8) && (revers==true))
    {

        revers = false;

    }
    if(walkExt1<0 && (!revers))
    {


        revers = true;

    }

    if(!revers)
    {

        walkExt1 = walkExt1-0.03;
        walkExt2 = walkExt2 - 0.03;
    }
    else
    {

        walkExt1 = walkExt1+0.03;
        walkExt2 = walkExt2 + 0.03;
    }

    if(direction=="FORWARD")
    {

    forwardPos-=0.001;
    }
    else if(direction=="BACKWARD")
    {
        forwardPos+=0.001;
    }


}
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void DoAction()
{
    if(ACTION=="WAGTAIL")
    {
        wagTail();
    }
    else if(ACTION=="WALKFORWARD")
    {
        walk("FORWARD");
    }
    else if(ACTION=="WALKBACKWARD")
    {
        walk("BACKWARD");
    }
    else if(ACTION=="KICKBALL")
    {
        kickBall();
    }
    else if(ACTION=="PICKBONE")
    {
        pickBone();
    }
    else if(ACTION=="STOP")
    {

    }

}

void keyboardEvent(unsigned char key,int x,int y)
{
    if(key=='q' || key=='Q')
        exit(0);

    if(key=='A' || key=='a')
        ACTION="WALKFORWARD";

    if(key=='D' || key=='d')
        ACTION="WALKBACKWARD";

    if(key=='t' || key=='T')
        ACTION="WAGTAIL";

    if(key=='K' || key=='k')
        ACTION="KICKBALL";

    if(key=='P' || key=='p')
        ACTION="PICKBONE";

    if(key=='S' || key=='s')
        ACTION="STOP";
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutIdleFunc(display);
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutKeyboardFunc(keyboardEvent);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
