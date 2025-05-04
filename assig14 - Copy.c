#include<GL/glut.h>
#include<stdio.h>
int xc,yc,r;
void BCircle(int xc,int yc,int r)
{
    int d,x,y;
    x=0;
    y=r;
    d=3-2*r;
    do
    {
        glVertex2d(xc+x,yc+y);
        glVertex2d(xc+y,yc+x);
        glVertex2d(xc+y,yc-x);
        glVertex2d(xc+x,yc-y);
        glVertex2d(xc-x,yc-y);
        glVertex2d(xc-y,yc-x);
        glVertex2d(xc-y,yc+x);
        glVertex2d(xc-x,yc+y);
        
        if(d<0)
        {
            x=x+1;
            d=d+4*x+6;
        }
        else
        {
            x=x+1;
            y=y-1;
            d=d+4*x-4*y+10;
        }
    }while(y>=x);
}
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    r=100;
    BCircle(xc,yc,r); 
    BCircle(xc+2*r,yc,r);
    BCircle(xc+r,yc+r,r);
    BCircle(xc+r,yc-r,r);
    glEnd();
    glFlush();
}
void Mouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        xc=x;
        yc=480-y;
        glutPostRedisplay();
    }
}

int main(int argc ,char **argv)
{

    glutInit(& argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Bresenham's Line");
    glClearColor(1,1,1,0);
    glColor3f(0,0,0);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(Draw);
    glutMouseFunc(Mouse);
    glutMainLoop();
    
    return 0;
}
