#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

int input[2][20];
int v;
float output[2][20];
int m=0;
int xmin,ymin,xmax,ymax;
int isClipped = 0;

void leftClip(int xa,int ya,int xb,int yb)
{
    float slope=(float)(yb-ya)/(xb-xa);
    if(xa>=xmin && xb>=xmin)
    {
        output[0][m]=xb;
        output[1][m]=yb;
        m=m+1;
    }
    if(xa>=xmin && xb<xmin)
    {
        output[0][m]=xmin;
        output[1][m]=ya+slope*(xmin-xa);
        m=m+1;
    }
    if(xa<xmin && xb>=xmin)
    {
        output[0][m]=xmin;
        output[1][m]=ya+slope*(xmin-xa);
        output[0][m+1]=xb;
        output[1][m+1]=yb;
        m=m+2;
    }
}
void rightClip(int xa,int ya,int xb,int yb)
{
    float slope=(float)(yb-ya)/(xb-xa);
    if(xa<=xmax && xb<=xmax)
    {
        output[0][m]=xb;
        output[1][m]=yb;
        m=m+1;
    }
    if(xa<=xmax && xb>xmax)
    {
        output[0][m]=xmax;
        output[1][m]=ya+slope*(xmax-xa);
        m=m+1;
    }
    if(xa>xmax && xb<=xmax)
    {
        output[0][m]=xmax;
        output[1][m]=ya+slope*(xmax-xa);
        output[0][m+1]=xb;
        output[1][m+1]=yb;
        m=m+2;
    }
}
void bottomClip(int xa,int ya,int xb,int yb)
{
    float slope=(float)(yb-ya)/(xb-xa);
    if(ya>=ymin && yb>=ymin)
    {
        output[0][m]=xb;
        output[1][m]=yb;
        m=m+1;
    }
    if(ya>=ymin && yb<ymin)
    {
        output[0][m]=xa+(ymin-ya)/slope;
        output[1][m]=ymin;
        m=m+1;
    }
    if(ya<ymin && yb>=ymin)
    {
        output[0][m]=xa+(ymin-ya)/slope;
        output[1][m]=ymin;
        output[0][m+1]=xb;
        output[1][m+1]=yb;
        m=m+2;
    }
}

void topClip(int xa,int ya,int xb,int yb)
{
    float slope=(float)(yb-ya)/(xb-xa);
    if(ya<=ymax && yb<=ymax)
    {
        output[0][m]=xb;
        output[1][m]=yb;
        m=m+1;
    }
    if(ya<=ymax && yb>ymax)
    {
        output[0][m]=xa+(ymax-ya)/slope;
        output[1][m]=ymax;
        m=m+1;
    }
    if(ya>ymax && yb<=ymax)
    {
        output[0][m]=xa+(ymax-ya)/slope;
        output[1][m]=ymax;
        output[0][m+1]=xb;
        output[1][m+1]=yb;
        m=m+2;
    }
}

int ROUND(float a)
{
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
void clipPolygon() {
    m = 0;
    for (int i = 0; i < v; i++)
        leftClip(input[0][i], input[1][i], input[0][(i + 1) % v], input[1][(i + 1) % v]);

    float temp1[2][20]; int temp_m1 = m;
    for (int i = 0; i < temp_m1; i++) {
        temp1[0][i] = output[0][i];
        temp1[1][i] = output[1][i];
    }

    m = 0;
    for (int i = 0; i < temp_m1; i++)
        rightClip(temp1[0][i], temp1[1][i], temp1[0][(i + 1) % temp_m1], temp1[1][(i + 1) % temp_m1]);

    float temp2[2][20]; int temp_m2 = m;
    for (int i = 0; i < temp_m2; i++) {
        temp2[0][i] = output[0][i];
        temp2[1][i] = output[1][i];
    }

    m = 0;
    for (int i = 0; i < temp_m2; i++)
        bottomClip(temp2[0][i], temp2[1][i], temp2[0][(i + 1) % temp_m2], temp2[1][(i + 1) % temp_m2]);

    float temp3[2][20]; int temp_m3 = m;
    for (int i = 0; i < temp_m3; i++) {
        temp3[0][i] = output[0][i];
        temp3[1][i] = output[1][i];
    }

    m = 0;
    for (int i = 0; i < temp_m3; i++)
        topClip(temp3[0][i], temp3[1][i], temp3[0][(i + 1) % temp_m3], temp3[1][(i + 1) % temp_m3]);
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    DDA(xmin, ymin, xmax, ymin);
    DDA(xmax, ymin, xmax, ymax);
    DDA(xmax, ymax, xmin, ymax);
    DDA(xmin, ymax, xmin, ymin);
    glEnd();

    // Draw original polygon
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < v; i++)
        DDA(input[0][i], input[1][i], input[0][(i + 1) % v], input[1][(i + 1) % v]);
    glEnd();

    // Draw clipped polygon
    if (isClipped) {
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_POINTS);
        for (int i = 0; i < m; i++)
            DDA(output[0][i], output[1][i], output[0][(i + 1) % m], output[1][(i + 1) % m]);
        glEnd();
    }

    glFlush();
}
void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && v < 20) {
        input[0][v] = x;
        input[1][v] = 480 - y; // flip y-axis for OpenGL
        v++;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'c':
        case 'C':
            isClipped = 1;
            clipPolygon();
            glutPostRedisplay();
            break;
        case 'r':
        case 'R':
            v = m = isClipped = 0;
            glutPostRedisplay();
            break;
        case 'q':
        case 27:
            exit(0);
            break;
    }
}
int main(int argc ,char **argv)
{
    /*printf("Enter no. of Vertices: ");
    scanf("%d",&v);
    
    for(int i=0;i<v;i++)
    {
        printf("\nVertex [%d]: ",i+1);
        printf("\nX : ");
        scanf("%d",&input[0][i]);
        printf("\nY : ");
        scanf("%d",&input[1][i]);
    }
    */
    printf("\nEnter clipping window coordinates:\n");
    printf("xmin ymin: ");
    scanf("%d%d", &xmin, &ymin);
    printf("xmax ymax: ");
    scanf("%d%d", &xmax, &ymax);
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Polygon Clipping");
    glClearColor(1,1,1,0);
    glColor3f(0,0,0);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return 0;
    
}
