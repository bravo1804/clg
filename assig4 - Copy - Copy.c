#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int clickCount = 0;
int xa, ya, xb, yb;

int ROUND(float a) {
    return (int)(a + 0.5);
}

void ddaline(int xa, int ya, int xb, int yb) {
    int dx = xb - xa;
    int dy = yb - ya;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    float xinc = (float)dx / steps;
    float yinc = (float)dy / steps;
    
    float x = xa;
    float y = ya;
    
    glBegin(GL_POINTS);
    glVertex2d(ROUND(x), ROUND(y));
    
    for (int i = 0; i < steps; i++) {
        x += xinc;
        y += yinc;
        glVertex2d(ROUND(x), ROUND(y));
    }
    glEnd();
}

void BresCircle(int cx, int cy, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    
    glBegin(GL_POINTS);
    while (y >= x) {
        // Plot all eight octants
        glVertex2i(cx + x, cy + y);
        glVertex2i(cx - x, cy + y);
        glVertex2i(cx + x, cy - y);
        glVertex2i(cx - x, cy - y);
        glVertex2i(cx + y, cy + x);
        glVertex2i(cx - y, cy + x);
        glVertex2i(cx + y, cy - x);
        glVertex2i(cx - y, cy - x);
        
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glEnd();
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Set drawing color to black
    
    // Only draw if we have both points
    if (clickCount == 0) {
        int dx = xb - xa;
        int dy = yb - ya;
        
        // Calculate radius for the inscribed circle
        float side = sqrt((dx/2.0)*(dx/2.0) + (dy/2.0)*(dy/2.0));
        float area = fabs((dx * dy) / 2.0);
        float radius = area / (2.0 * side);
        
        // Draw the octagon
        ddaline(xa, ya, xb, ya);
        ddaline(xa + dx/2, ya, xb, ya + dy/2);
        ddaline(xb, ya, xb, yb);
        ddaline(xa + dx/2, yb, xb, ya + dy/2);
        ddaline(xa, yb, xb, yb);
        ddaline(xa + dx/2, yb, xa, ya + dy/2);
        ddaline(xa, yb, xa, ya);
        ddaline(xa + dx/2, ya, xa, ya + dy/2);
        
        // Draw the inscribed circle
        BresCircle(xa + dx/2, ya + dy/2, ROUND(radius));
    }
    
    glFlush();
}

void Mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (clickCount == 0) {
            xa = x;
            ya = 480 - y;
            clickCount++;
            printf("First point set at (%d, %d)\n", xa, ya);
        } else {
            xb = x;
            yb = 480 - y;
            clickCount = 0;
            printf("Second point set at (%d, %d)\n", xb, yb);
            glutPostRedisplay();
        }
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 480, 0, 480);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Octagon with Inscribed Circle");
    
    init();
    glutDisplayFunc(draw);
    glutMouseFunc(Mouse);
    glutMainLoop();
    
    return 0;
}
