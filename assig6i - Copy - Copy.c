#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int clickCount = 0;
float ctrlPoints[2][4]; // P0, P1, P2, P3

int ROUND(float a){
  return (int) (a+0.5); 
}

void DDA(int xa,int ya, int xb, int yb){
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
void Bezier() {
    float x, y, t;
    glColor3f(1, 0, 0); // Red curve

    for (t = 0.0; t <= 1.0; t += 0.001) {
        if (clickCount == 2) {
            // Linear Bézier
            x = (1 - t) * ctrlPoints[0][0] + t * ctrlPoints[0][1];
            y = (1 - t) * ctrlPoints[1][0] + t * ctrlPoints[1][1];
        }
        else if(clickCount==3)
         {
        x = pow(1 - t, 2) * ctrlPoints[0][0] +
            2 * (1 - t) * t * ctrlPoints[0][1] +
            pow(t, 2) * ctrlPoints[0][2];

        y = pow(1 - t, 2) * ctrlPoints[1][0] +
            2 * (1 - t) * t * ctrlPoints[1][1] +
            pow(t, 2) * ctrlPoints[1][2];
        }
        else if(clickCount==4)
         {
            x = pow(1 - t, 3) * ctrlPoints[0][0] +
            3 * pow(1 - t, 2) * t * ctrlPoints[0][1] +
            3 * (1 - t) * pow(t, 2) * ctrlPoints[0][2] +
            pow(t, 3) * ctrlPoints[0][3];

            y = pow(1 - t, 3) * ctrlPoints[1][0] +
            3 * pow(1 - t, 2) * t * ctrlPoints[1][1] +
            3 * (1 - t) * pow(t, 2) * ctrlPoints[1][2] +
            pow(t, 3) * ctrlPoints[1][3];
         }
         glVertex2d(ROUND(x), ROUND(y));
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

  
        glColor3f(0, 0, 1); // Blue control polygon
        for(int i=0;i<clickCount-1;i++)
        {
        DDA(ctrlPoints[0][i], ctrlPoints[1][i], ctrlPoints[0][i+1], ctrlPoints[1][i+1]);
        }
        Bezier();


    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (clickCount < 4) {
            ctrlPoints[0][clickCount] = x;
            ctrlPoints[1][clickCount] = 480 - y; // Flip Y
            clickCount++;
                glutPostRedisplay();
            
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        clickCount = 0;
        glutPostRedisplay();
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Quadratic & Cubic Bezier Curve with DDA");

    glClearColor(1, 1, 1, 0);
    glColor3f(0, 0, 0);
    gluOrtho2D(0, 640, 0, 480);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

