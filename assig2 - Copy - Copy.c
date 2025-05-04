#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

int xa,ya,xb,yb;
int clickCount=0;
void BLine(int xa,int ya, int xb,int yb)
{
	int dx,dy,d;
	int c,r,f;
	
	dx=xb-xa;
	dy=yb-ya;
	
   if(abs(dx) > abs(dy)){
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
		    if(dx>0 && dy>0 || dx<0 && dy<0)
		    {
		    	r=r+1;
		    }
		    else
		    {
		        r=r-1;
		    }
			c=c+1;
		
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
		    if(dx>0 && dy>0 || dx<0 && dy<0)
		    {
		    	c=c+1;
		    }
		    else
		    {
		        c=c-1;
		    }
			r=r+1;
		
			d=d+2*abs(dx)-2*abs(dy);
		}
		glVertex2d(c,r);
	}
    }	
}
void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	BLine(xa,ya,xb,ya);
	BLine(xb,ya,xb,yb);
	BLine(xb,yb,xa,yb);
	BLine(xa,yb,xa,ya);
	BLine(xa,(ya+yb)/2,(xa+xb)/2,ya);
	BLine((xa+xb)/2,ya,xb,(ya+yb)/2);
	BLine(xb,(ya+yb)/2,(xa+xb)/2,yb);
	BLine((xa+xb)/2,yb,xa,(ya+yb)/2);
	BLine((3*xa+xb)/4,(3*ya+yb)/4,(xa+3*xb)/4,(3*ya+yb)/4);
	BLine((xa+3*xb)/4,(3*ya+yb)/4,(xa+3*xb)/4,(ya+3*yb)/4);
	BLine((xa+3*xb)/4,(ya+3*yb)/4,(3*xa+xb)/4,(ya+3*yb)/4);
	BLine((3*xa+xb)/4,(ya+3*yb)/4,(3*xa+xb)/4,(3*ya+yb)/4);
	
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
            clickCount =0;
            glutPostRedisplay();
        }
    }
}

int main(int argc,char **argv){
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("First");
	glClearColor(1,1,1,0);
	glColor3f(0,0,0);
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(Draw);
	glutMouseFunc(Mouse);
	glutMainLoop();
	
	return 0;
	
}
