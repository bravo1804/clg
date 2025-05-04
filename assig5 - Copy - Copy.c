#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int xa,ya,xb,yb;
int xc,yc,r;
int clickCount=0;

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
    
    int xinc=(abs(xb)-abs(xa))/4;
    int yinc=(abs(yb)-abs(ya))/4;
    int x=xa,y=ya;
    for(int i=0;i<=4;i++)
    {
        BresLine(x,ya,x,yb);
        BresLine(xa,y,xb,y);
        x=x+xinc;
        y=y+yinc;
    }
   
    glEnd();
    glFlush();
}

void Mouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {     
          if(clickCount==0)
          {
              xa=x;
              ya=480-y;
              clickCount++;
          }
          else if(clickCount==1)
          {
              xb=x;
              yb=480-y;
              clickCount=0;
              glutPostRedisplay();
          }
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
