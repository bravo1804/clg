#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int step=3;

int ROUND(float a){
  return (int) (a+0.5); 
}

void DDALine(int xa,int ya, int xb, int yb){
  int dx,dy,steps;
  dx=xb-xa;
  dy=yb-ya;
  if(abs(dx)>abs(dy)){
    steps=abs(dx);
  }
  else{
    steps=abs(dy);
  }
  float xinc,yinc;
  xinc=(float)dx/steps;
  yinc=(float)dy/steps;
  
  glVertex2d(xa,ya);
  float x=xa,y=ya;
  for(int i=0;i<steps;i++){
    x=x+xinc;
    y=y+yinc;
    glVertex2d(ROUND(x),ROUND(y));
  }
}
void koch_curve(float xa,float ya, float xb, float yb,int step)
{   
    if(step==0)
    {
      DDALine(xa,ya,xb,yb);
      return;
    }
    float x1,y1,x2,y2,dx,dy,r_dx,r_dy, x3,y3;
    x1=xa+(xb-xa)/3;
    y1=ya+(yb-ya)/3;
    x2=xa+2*(xb-xa)/3;
    y2=ya+2*(yb-ya)/3;
    dx=x2-x1;
    dy=y2-y1;
    float angle=-M_PI/3;
    r_dx=dx*cos(angle)-dy*sin(angle);
    r_dy=dx*sin(angle)+dy*cos(angle);
    x3=x1+r_dx;
    y3=y1+r_dy;
    
    koch_curve(xa,ya,x1,y1,step-1);
    koch_curve(x1,y1,x3,y3,step-1);
    koch_curve(x3,y3,x2,y2,step-1);
    koch_curve(x2,y2,xb,yb,step-1);
}

void Draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  //DDALine(100,100,400,100);
  koch_curve(100,100,400,100,step);
  koch_curve(400,100,250,400,step);
  koch_curve(250,400,100,100,step);
  glEnd();
  glFlush();
}
 int main(int argc,char**argv){
 
    glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
     glutInitWindowPosition(0,0);
     glutInitWindowSize(640,480);
     glutCreateWindow("Koch Curve");
     glClearColor(1,1,1,0);
     glColor3f(0,0,0);
     gluOrtho2D(0,640,0,480);
     glutDisplayFunc(Draw);
     glutMainLoop();
     return 0;
     }
