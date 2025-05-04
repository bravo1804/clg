#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

int xa,ya,xb,yb;
int lineType=0;
int clickCount=0;
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
   y=y+yinc;
   x=x+xinc;
   switch(lineType){ 
    case 1:{
    glVertex2d(ROUND(x),ROUND(y));
         }
          break;
    case 2:
    if(i%2==0){
   glVertex2d(ROUND(x),ROUND(y));
         }
          break;
    case 3:
    if(i%6<4){
    glVertex2d(ROUND(x),ROUND(y));
        }
         break;
    case 4:
    if(i%12<6){
    glVertex2d(ROUND(x),ROUND(y));
         }
    else if(i%12==9){
    glVertex2d(ROUND(x),ROUND(y));
      }
     break;
   }
  }
 } 

void Draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  
  DDALine(-320,0,320,0);
  DDALine(0,-240,0,240);

  DDALine(xa,ya,xb,yb);
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

int main(int argc,char **argv){

  //printf("\nEnter First Coordinate: ");
 // scanf("%d%d",&xa,&ya);
 // printf("\nEnter Second Coordinate: ");
 // scanf("%d%d",&xb,&yb);
  printf("\nSelect Line Type: \n");
  printf("1: Simple Line\n2: Dotted Line\n3: Dashed Line\n4: Dashed-Dotted Line\n");
  scanf("%d", &lineType);
  
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("Draw a Line");
  glClearColor(1,1,1,0);
  glColor3f(0,0,0);
  gluOrtho2D(-320,320,-240,240);
  glutDisplayFunc(Draw);
  glutMouseFunc(Mouse);
  glutMainLoop();
  
  return 0;
}
