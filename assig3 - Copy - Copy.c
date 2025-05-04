#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int xa,ya,xb,yb;
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

void BresLine(int xa, int ya,int xb,int yb)
{
    int dx,dy,d,c,r,f;
    dx=xb-xa;
    dy=yb-ya;
    if(abs(dx)>abs(dy))
    {
        d=2*abs(dy)-abs(dx);
        if(dx>0)
        {
            c=xa;
            r=ya;
            f=xb;
        }
        else
        {
            c=xb;
            r=yb;
            f=xa;
        }
        while(f>c)
        {
            if(d<0)
            {
                c=c+1;
                d=d+2*abs(dy);
            }
            else
            {
                c=c+1;
                if(dx>0 && dy>0 || dx<0 && dy<0)
                {
                    r=r+1;
                }
                else
                {
                    r=r-1;
                }
                d=d+2*abs(dy)-2*abs(dx);
            }
              glVertex2d(c,r);
        }
    }

    else
    {
         d=2*abs(dx)-abs(dy);
        if(dy>0)
        {
            c=xa;
            r=ya;
            f=yb;
        }
        else
        {
            c=xb;
            r=yb;
            f=ya;
        }
        while(f>r)
        {
            if(d<0)
            {
                r=r+1;
                d=d+2*abs(dx);
            }
            else
            {
                r=r+1;
                if(dx>0 && dy>0 || dx<0 && dy<0)
                {
                    c=c+1;
                }
                else
                {
                    c=c-1;
                }
                d=d+2*abs(dx)-2*abs(dy);
            }
              glVertex2d(c,r);
             
       }  
    }
    
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    r=100;
    BCircle(xc,yc,r);
    BCircle(xc,yc,r/2);
    int x1,x2,x3,y1,y2,y3;
    x1=xc;
    y1=yc+r;
    x2=xc-(sqrt(3)*r/2);
    y2=yc-(r/2);
    x3=xc+(sqrt(3)*r/2);
    y3=yc-(r/2);
    BresLine(x1,y1,x2,y2);
    BresLine(x2,y2,x3,y3);
    BresLine(x3,y3,x1,y1);
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
    
    /*printf("\nEnter xa,ya: ");
    scanf("%d%d",&xa,&ya);
    
    printf("\nEnter xb,yb: ");
    scanf("%d%d",&xb,&yb);*/

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
