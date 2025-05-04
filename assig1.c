#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
int xa,ya,xb,yb;
int lineType=0;
int clickCount=0;
void BresLine(int xa, int ya,int xb,int yb,int axes)
{
    int dx,dy,d,c,r,f;
    int i=0;
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
            
            if(axes)
            {
              glVertex2d(c,r);
            }
            else
            {
            
    switch(lineType){ 
    case 1:{
   glVertex2d(c,r);
         }
          break;
    case 2:
    if(i%2==0){
   glVertex2d(c,r);
         }
          break;
    case 3:
    if(i%6<4){
   glVertex2d(c,r);
        }
         break;
    case 4:
    if(i%12<6){
   glVertex2d(c,r);
         }
    else if(i%12==9){
   glVertex2d(c,r);
      }
     break;
   }
   i++;
        }
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
            if(axes)
            {
                glVertex2d(c,r);
            }
            else
            {
    switch(lineType){ 
    case 1:{
   glVertex2d(c,r);
         }
          break;
    case 2:
    if(i%2==0){
   glVertex2d(c,r);
         }
          break;
    case 3:
    if(i%6<4){
   glVertex2d(c,r);
        }
         break;
    case 4:
    if(i%12<6){
   glVertex2d(c,r);
         }
    else if(i%12==9){
   glVertex2d(c,r);
      }
     break;
   }
   i++;
          }       
       }  
    }
    
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    BresLine(-320,0,320,0,1);
    BresLine(0,-240,0,240,1);
    BresLine(xa,ya,xb,yb,0);
    glEnd();
    glFlush();
}

void Mouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(clickCount==0)
        {
          xa=x-320;
          ya=240-y;
          clickCount++;
        }
        else if(clickCount==1)
        {
          xb=x-320;
          yb=240-y;
          clickCount=0;
          glutPostRedisplay();
        }
        
    }
}

int main(int argc ,char **argv)
{
    printf("\n1) Simple Line\n2) Dotted Line\n3) Dashed Line\n4) Dashed-Dotted Line\nChoose line: ");
    scanf("%d",&lineType);
    
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
    gluOrtho2D(-320,320,-240,240);
    glutDisplayFunc(Draw);
    glutMouseFunc(Mouse);
    glutMainLoop();
    
    return 0;
}
