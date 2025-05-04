#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int xmin,ymin,xmax,ymax;
int clickCount=0;
int result[4];
int change=0;
struct lclip{
    int outcode[4];
    int x,y;
}p1,p2;

int Calculate(struct lclip *p)
{
    int change=0;
    for(int i=0;i<4;i++)
    {
        p->outcode[i]=0;
    }
    if(p-> x<xmin)
    {
        p->outcode[3]=1;
        change=1;
    }
    if(p-> x>xmax)
    {
       p-> outcode[2]=1;
        change=1;
    }
    if(p-> y<ymin)
    {
        p->outcode[1]=1;
        change=1;
    }
    if(p-> y>ymax)
    {
        p->outcode[0]=1;
        change=1;
    }
    return change;
  
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

void find(struct lclip *p)
{
    float X,Y;
    float slope=(float) (p2.y-p1.y)/(p2.x-p1.x);
    if(p->outcode[0]==1)
    {
        X=p1.x + (ymax-p1.y)/slope;
        Y=ymax;
    }
    if(p->outcode[1]==1)
    {
        X=p1.x + (ymin-p1.y)/slope;
        Y=ymin;
    }
    if(p->outcode[2]==1)
    {
        X=xmax;
        Y=p1.y+slope*(xmax-p1.x);
    }
    if(p->outcode[3]==1)
    {
        X=xmin;
        Y=p1.y+slope*(xmin-p1.x);
    }
    
    p->x=X;
    p->y=Y;
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glColor3f(0,0,0);
    BresLine(xmin,ymin,xmax,ymin);
    BresLine(xmax,ymin,xmax,ymax);
    BresLine(xmax,ymax,xmin,ymax);
    BresLine(xmin,ymax,xmin,ymin);

    int fp1,fp2;
    fp1=Calculate(&p1);
    fp2=Calculate(&p2);
    int flag=0;
    int flag1=0;
    
    for(int i=0;i<4;i++)        //rejected
    {
        if(p1.outcode[i]==1 || p2.outcode[i]==1)
        {
            flag=1;
            break;
        }
    }
    
    glColor3f(0,1,0);
    BresLine(p1.x,p1.y,p2.x,p2.y);
    
    if(flag==0)
    {
        glColor3f(1,0,0);
        BresLine(p1.x,p1.y,p2.x,p2.y);
    }
    else
    {
        for(int i=0;i<4;i++)
        {
            result[i]=p1.outcode[i] && p2.outcode[i];
        }
    }
    
    for(int i=0;i<4;i++)
    {
        if(result[i]==1)
        {
          flag1=1;
          break;
        }
    }
    
    if(flag1==1)
    {
        glColor3f(0,1,0);
        BresLine(p1.x,p1.y,p2.x,p2.y);
    }
    else
    {
        if(fp1==1)
        {
            find(&p1);
        }
        if(fp2==1)
        {
            find(&p2);
        }
        glColor3f(1,0,0);
        BresLine(p1.x,p1.y,p2.x,p2.y);
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
              p1.x=x;
              p1.y=480-y;
              clickCount++;
          }
          else if(clickCount==1)
          {
              p2.x=x;
              p2.y=480-y;
              clickCount=0;
              glutPostRedisplay();
          }
    }
}

int main(int argc ,char **argv)
{
    
    printf("\nEnter xmin,ymin: ");
    scanf("%d%d",&xmin,&ymin);
    
    printf("\nEnter xmax,ymax: ");
    scanf("%d%d",&xmax,&ymax);

    glutInit(& argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Line Clipping");
    glClearColor(1,1,1,0);
    glColor3f(0,0,0);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(Draw);
    glutMouseFunc(Mouse);
    glutMainLoop();
    
    return 0;
}
