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

const int SCREEN_W = 256;
const int SCREEN_H = 256;
int inpLimit;
int escapetime(int n,complex<double> c);
bool inMandelBrot(int n,complex<double> c);
GLubyte* getColor(float val);
void shade(complex<double> c,float time);
void visualzieMandelbrot(int limit);

int escapetime(int n,complex<double> c)
{
    complex<double> z(0, 0);
    int count = 0;
    int maxcount = n;
    while ((sqrt(norm(z))<2) && (count < maxcount)){

        float zreal = ( pow(real(z),2)) - (pow(imag(z),2)) + real(c);
        float zimag = 2 * real(z) * imag(z) + imag(c);
        complex<double> temp(zreal,zimag);
        z = temp;
        count = count + 1;
    }

    if (count == maxcount)
    {

        return -1;
    }
    else
    {

        return count;
    }
}

bool inMandelBrot(int n,complex<double> c)
{

    if(escapetime(n,c)==-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void visualzieMandelbrot(int limit)
{



    float xa,xb,ya,yb;
    int imgx,imgy,i;
    xa = -2.0;
    xb = 2.0;
    ya = -2.0;
    yb = 2.0;
    imgx = SCREEN_W;
    imgy = SCREEN_H;
    i=0;
    for (int y=0;y<imgy;y++)
    {

       double cy = y * (yb-ya)/(imgy - 1) + ya;
       for(int x=0;x < imgx; x++)
       {

            double cx = x * (xb - xa) /(imgx - 1) + xa;
            complex<double> c(cx,cy);
            complex<double> z(0,0);
            for(i=0;i<limit;i++)
            {

                if (sqrt(norm(z)) > 2.0)
                {
                    break;
                }
                else
                {
                    z = z * z + c;
                }
            }
            if (sqrt(norm(z)) > 2.0)
            {

                shade(c,float(i)/float(limit));
            }
       }

    }


}

void shade(complex<double> z,float time)
{

    if ((time < 0) || (time > 1))
    {


    }
    else
    {

        int x = (real(z) +2) * pow(2,6);
        int y = (imag(z) +2) * pow(2,6);
        glBegin(GL_POINTS);

            GLubyte* temp = getColor(time);
            GLubyte color[3] = {*temp,*(temp+1),*(temp+2)};
            glColor3ubv(color);
            glVertex2i (x, y);
        glEnd();

    }


}

GLubyte* getColor(float val)
{


    if (val <= 0.15)
    {

        float lim  = val / 0.15;
        int green = int(lim*255);
        GLubyte ret[3] = {255^green, green, 0};
        return ret;
    }
    else
    {

        float lim = (val - 0.15) / 0.85;
        int blue = int(lim*255);
        GLubyte ret[3]= {0,255^blue, blue};
        return ret;
    }
}
void display() {


    // begin transformations.
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* Transformation magic. */

        visualzieMandelbrot(inpLimit);

    glutSwapBuffers();
}

void keyboardEvent(unsigned char key,int x,int y)
{
    if(key=='q' || key=='Q')
        exit(0);
}

int main(int argc, char** argv) {

    inpLimit = 50;
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_W, SCREEN_H);
    glutInitWindowPosition(0   , 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("MBset - Question 4");
    glOrtho(0,256,0,256,-1,1);
    glutDisplayFunc(display);



    glutKeyboardFunc(keyboardEvent);

    glutMainLoop();
    return 0;
}
