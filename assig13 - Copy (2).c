#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
int x,y;
float bcol[3],fcol[3];
int xa,ya,xb,yb;
int xmin,ymin,xmax,ymax;
int input[2][10];
int output[2][10];
int m=0;

/*void topClip(int xa,int ya,int xb,int yb)
{	
	float slope=(float) (yb-ya)/(xb-xa);
	
	if(ya<=ymax && yb<=ymax)	//in-in
	{
		output[0][m]=xb;
		output[1][m]=yb;
		m=m+1;
	}
	if(ya<=ymax && yb>ymax)// in-out
	{
		output[0][m]=xa+(ymax-ya)/slope;
		output[1][m]=ymax;
		m=m+1;
	}
	if(ya>ymax && yb<=ymax) // out-in
	{
		output[0][m]=xa+(ymax-ya)/slope;
		output[1][m]=ymax;
		output[0][m+1]=xb;
		output[1][m+1]=yb;
		m=m+2;
	}
}
*/
/*void Bfill(int x,int y,float bcol[3],float fcol[3])
{
	float current[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,current);
	if((current[0] != bcol[0] || current[1] != bcol[1] || current[2] != bcol[2] ) && (current[0] != fcol[0] || current[1] != fcol[1] || current[2] != fcol[2]  ) )
	{
		glColor3f(fcol[0],fcol[1],fcol[2]);
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		glFlush();
		
		Bfill(x,y+1,bcol,fcol);
		Bfill(x,y-1,bcol,fcol);
		Bfill(x+1,y,bcol,fcol);
		Bfill(x-1,y,bcol,fcol);
	}
}*/
void Bcircle(int xc,int yc,int r)
{
	int x,y,d;
	x=0;
	y=r;
	d=3-2*r;
	do
	{
		glVertex2d(xc+x,yc+y);
		glVertex2d(xc+y,yc+x);
		glVertex2d(xc+x,yc-y);
		glVertex2d(xc+y,yc-x);
		glVertex2d(xc-x,yc-y);
		glVertex2d(xc-y,yc-x);
		glVertex2d(xc-x,yc+y);
		glVertex2d(xc-y,yc+x);
		
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
 
void Bline(int xa,int ya,int xb,int yb)
{
	int dx,dy,d;
	dx=xb-xa;
	dy=yb-ya;
	int c,r,f;
	
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
	//glColor3f(bcol[0],bcol[1],bcol[2]);
	glColor3f(0,0,0);
	glBegin(GL_POINTS);

	Bline(200,50,220,50);
	Bline(220,50,220,150);
	Bline(220,150,200,150);
	Bline(200,150,200,50);
	
	Bline(260,50,280,50);
	Bline(280,50,280,150);
	Bline(280,150,260,150);
	Bline(260,150,260,50);
	
	Bline(200,150,280,150);
	Bline(280,150,280,280);
	Bline(280,280,200,280);
	Bline(200,280,200,150);
	
	Bline(235,280,235,290);
	Bline(245,280,245,290);
	
	Bcircle(240,320,30);
	
	Bline(200,280,150,220);
	Bline(150,220,200,260);
	
	Bline(280,280,330,220);
	Bline(330,220,280,260);
	
	Bcircle(225,325,5);
	Bcircle(255,325,5);
	
	Bline(240,320,235,315);
	Bline(235,315,245,315);
	Bline(245,315,240,320);
	
	Bline(230,310,230,305);
	Bline(230,305,250,305);
	Bline(250,305,250,310);
	Bline(250,310,230,310);
	
	glEnd();
	
	/*glColor3f(0,1,1);
	glBegin(GL_POINTS);
	Bline(xmin,ymin,xmax,ymin);
	Bline(xmax,ymin,xmax,ymax);
	Bline(xmax,ymax,xmin,ymax);
	Bline(xmin,ymax,xmin,ymin);

	glEnd();
	
	glColor3f(1,0,0);
	glBegin(GL_POINTS);
		m=0;
	for (int i=0;i<5;i++)
	{
		topClip(input[0][i],input[1][i],input[0][(i+1)%4],input[1][(i+1)%4]);
	}
	for(int i=0;i<m;i++)
	{
		Bline(output[0][i],output[1][i],output[0][(i+1)%m],output[1][(i+1)%m]);
	}
	glEnd();*/
	
	glFlush();
	
	
}
/*void Mouse(int button,int state,int xm,int ym)
{
    if(button== GLUT_LEFT_BUTTON && state== GLUT_DOWN)
    {
            x=xm;
            y=480-ym;
            Bfill(x,y,bcol,fcol);
            //glutPostRedisplay();
    }
}
*/
int main(int argc,char **argv)
{	
	input[0][0]=260;
	input[1][0]=50;
	input[0][1]=280;
	input[1][1]=50;
	input[0][2]=280;
	input[1][2]=150;
	input[0][3]=260;
	input[1][3]=150;
	
	xmin=235,ymin=25,xmax=295,ymax=75;
	
	/*for(int i=0;i<3;i++)
	{
	printf("\nEnter Boundry Color [%d]: ",i+1);
	scanf("%f",&bcol[i]);
	}
	
	for(int i=0;i<3;i++)
	{
	printf("\nEnter Fill Color [%d]: ",i+1);
	scanf("%f",&fcol[i]);
	}*/
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Window");
	glClearColor(1,1,1,0);
	
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(Draw);
	//glutMouseFunc(Mouse);
	glutMainLoop();
	
	return 0;
}
