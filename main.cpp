#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<cmath>

int windowWidth = 600, windowHeight = 600;
static int tx=-57,ty=0;

void line(double x1,double y1,double x2,double y2,double r,double g, double b)
{
    glColor3f(r,g,b);
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}

void rectangle(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
    glEnd();
}

void circle(int radius)
{
    int i;
    glBegin(GL_LINE_LOOP);
    //glColor3f(1, 1, 1);
    //glVertex2f(0,0);

    for(i = 0; i <= 360; i++)
    {
        glColor3f(1, 1, 1);
        glVertex2f((radius * cos(i *  3.1416 / 180)),
                   (radius * sin(i * 3.1416 / 180)));
    }
    glEnd();
}

void football(double x, double y,double radius)
{
    int i;
    glBegin(GL_TRIANGLE_FAN);
    //glColor3f(249, 6, 6);
    glVertex2f(x,y);

    for(i = 0; i <= 360; i++)
    {
        glColor3f(1, 1, 1);
        glVertex2f((radius * cos(i *  3.1416 / 180)),
                   (radius * sin(i * 3.1416 / 180)));
    }
    glEnd();
}

bool isTerminated()
{
 if((abs(abs(tx)-30)<=1&&((ty>=16 && ty<=46)||(ty>=-36 && ty<=6)))
            || (abs(abs(tx)-15)==1 && (ty>=-16 && ty<=36))|| (abs(abs(tx)-10)==1 && (ty>=-46 && ty<=-16)) )
        return true;
    else
        return false;
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(-70, 70, -70, 70);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glViewport(0, 0 ,windowWidth ,windowHeight);
    glPushMatrix();

    //glTranslatef(-70,-70,0);

    rectangle(60,45,-60,45,-60,-45,60,-45);

    rectangle(60,22,42,22,42,-22,60,-22);
    rectangle(-60,22,-42,22,-42,-22,-60,-22);

    rectangle(60,10,53,10,53,-10,60,-10);
    rectangle(-60,10,-53,10,-53,-10,-60,-10);

    rectangle(60,5,64,5,64,-5,60,-5);
    rectangle(-60,5,-64,5,-64,-5,-60,-5);

    line(0,45,0,-45,1,1,1);

    line(-30,45,-30,15,1,0,0);
    line(-30,5,-30,-35,1,0,0);
    line(-15,35,-15,-15,1,0,0);
    line(-10,-15,-10,-45,1,0,0);

    line(30,45,30,15,1,0,0);
    line(30,5,30,-35,1,0,0);
    line(15,35,15,-15,1,0,0);
    line(10,-15,10,-45,1,0,0);

    circle(10);

    football(0,0,1);

    glTranslatef(48,0,0);
    football(0,0,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-48,0,0);
    football(0,0,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx,ty,0);
    football(0,0,2);

    if(isTerminated())
        //exit(0);
        {
            tx=-57;
            ty=0;
           printf("\a");
        }
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void arrowKey(int c,int x, int y)
{
    switch(c)
    {
    case GLUT_KEY_LEFT:
        if(tx>-68)
            tx--;
        break;
    case GLUT_KEY_RIGHT:
        if(tx<68)
            tx++;
        break;
    case GLUT_KEY_DOWN:
        if(ty>-45)
            ty--;
        break;
    case GLUT_KEY_UP:
        if(ty<45)
            ty++;
        break;
    }
}

void keyboardOperation(unsigned char c,int x,int y)
{
    switch(c)
    {
    case 'q':
        exit(0);
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("Football Field");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardOperation);
    glutSpecialFunc(arrowKey);
    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    glutMainLoop();
    return 0;
}

