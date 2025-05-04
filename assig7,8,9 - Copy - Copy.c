#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int count=0,v;
int input[3][10];
float output[3][10],tr[3][3],rotate[3][3],scale[3][3],ref[3][3],xshear[3][3],yshear[3][3];

void mul(int input[3][10],float tr[3][3],float output[3][10],int v)
{
      for(int i=0;i<3;i++)
      {
          for(int j=0;j<v;j++)
          {
              output[i][j]=0;
              for(int k=0;k<3;k++)
              {
                  output[i][j] += tr[i][k] * input[k][j];
              }
          }
      }
}

void Translation()
{
      for(int i=0;i<3;i++)
      {
          for(int j=0;j<v;j++)
          {
              printf("\t%d",input[i][j]);
          }
          printf("\n");
      }
      
      int tx,ty;
      printf("\nEnter Value of TX and TY: ");
      scanf("%d%d",&tx,&ty);
      for(int i=0;i<3;i++)
      {
          for(int j=0;j<3;j++)
          {
              if(i==j)
              {
                  tr[i][j]=1;
              }
              else
              {
                  tr[i][j]=0;
              }
          }
      }
      
      tr[0][2]=tx;
      tr[1][2]=ty;
      
      for(int i=0;i<3;i++)
      {
          for(int j=0;j<3;j++)
          {
              printf("\t%f",tr[i][j]);
          }
          printf("\n");
      }
      
      mul(input,tr,output,v);
        for(int i=0;i<3;i++)
      {
          for(int j=0;j<v;j++)
          {
              printf("\t%f",output[i][j]);
          }
          printf("\n");
      }
      
      
}
float angle(float thita)
{
    return  (thita*3.14/180);
}


void Rotation()
{
     for(int i=0;i<3;i++)
      {
          for(int j=0;j<v;j++)
          {
              printf("\t%d",input[i][j]);
          }
          printf("\n");
      }
      float xr,yr,thita;
      	printf("Enter Value of Fixed Point: ");
	scanf("%f%f",&xr,&yr);
	printf("Enter value of Angle: ");
	scanf("%f",&thita);
	
	float sinT=sin(angle(thita));
	float cosT=cos(angle(thita));
      
      
      	rotate[0][0]=cosT;
	rotate[1][0]=sinT;
	rotate[2][0]=0;
	
	rotate[0][1]=-sinT;
	rotate[1][1]=cosT;
	rotate[2][1]=0;
	
	rotate[0][2]=xr*(1-cosT)+yr*sinT;
	rotate[1][2]=yr*(1-cosT)-xr*sinT;
	rotate[2][2]=1;
	
	mul(input,rotate,output,v);
        for(int i=0;i<3;i++)
      {
          for(int j=0;j<v;j++)
          {
              printf("\t%f",output[i][j]);
          }
          printf("\n");
      }
}

void Scaling()
{
        for(int i=0;i<3;i++)
      {
          for(int j=0;j<v;j++)
          {
              printf("\t%d",input[i][j]);
          }
          printf("\n");
      }
      int xf,yf;
    float sx,sy;
    printf("\nEnter value of Sx & Sy: ");
    scanf("%f%f",&sx,&sy);
    
    printf("\nEnter Fixed Point Xf & Yf: ");
    scanf("%d%d",&xf,&yf);
    
    scale[0][0]=sx;
    scale[0][1]=0;
    scale[0][2]=xf * (1 - sx);
    
    scale[1][0]=0;
    scale[1][1]=sy;
    scale[1][2]=yf * (1 - sy);
    
    scale[2][0]=0;
    scale[2][1]=0;
    scale[2][2]=1;
    
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("\t%f",scale[i][j]);
        }
        printf("\n");
    }
    mul(input,scale,output,v);
        for(int i=0;i<3;i++)
      {
          for(int j=0;j<v;j++)
          {
              printf("\t%f",output[i][j]);
          }
          printf("\n");
      }
    
}
void Reflection()
{
      for(int i=0;i<3;i++)
      {
          for(int j=0;j<v;j++)
          {
              printf("\t%d",input[i][j]);
          }
          printf("\n");
      }
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i==j)
            {
              ref[i][j]=1;
            }
            else
            {
              ref[i][j]=0;
            }
        }
    }
    int ch=0;
     printf("\n1.Reflection about X-axis\n2.Reflection about Y-axis\n3.Reflection to an Axis Perpendicular to xy plane\n4.Reflection about Y=X\n5.Reflection about Y=-X\nEnter Choice: ");
     scanf("%d",&ch);
    switch(ch)
    {
        case 1:
        ref[1][1]=-1;
        break;
        
        case 2:
        ref[0][0]=-1;
        break;
        
        case 3:
         ref[1][1]=-1;
         ref[0][0]=-1;
        break;
        
        case 4:
        ref[0][0]=0;
        ref[1][1]=0;
        ref[0][1]=1;
        ref[1][0]=1;
        break;
        
        case 5:
        ref[0][0]=0;
        ref[1][1]=0;
        ref[0][1]=-1;
        ref[1][0]=-1;
        break;
    }
    
    printf("\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("\t%f",ref[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //output matrix
    mul(input,ref,output,v);
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<v;j++)
        {
            printf("\t%f",output[i][j]);
        }
        printf("\n");
    }
}

void ShearMatrix()
{   
      for(int i=0;i<3;i++)
      {
          for(int j=0;j<v;j++)
          {
              printf("\t%d",input[i][j]);
          }
          printf("\n");
      }
    int ch;
    printf("\n1.X shear\n2.Y shear\nEnter Choice: ");
    scanf("%d",&ch);
    float xref,yref,shx,shy;
    switch(ch)
    {
        case 1:
        printf("\nEnter Value of X Shear: ");
        scanf("%f",&shx);
         printf("\nEnter Value of Y Ref: ");
        scanf("%f",&yref);
        
        xshear[0][0]=1;
        xshear[0][1]=shx;
        xshear[0][2]=-shx*yref;
        
        xshear[1][0]=0;
        xshear[1][1]=1;
        xshear[1][2]=0;
        
        xshear[2][0]=0;
        xshear[2][1]=0;
        xshear[2][2]=1;
        
        mul(input,xshear,output,v);
        break;
        
        case 2:
        printf("\nEnter Value of Y Shear: ");
        scanf("%f",&shy);
        printf("\nEnter Value of X Ref: ");
        scanf("%f",&xref);
        
        yshear[0][0]=1;
        yshear[0][1]=0;
        yshear[0][2]=0;
        
        yshear[1][0]=shy;
        yshear[1][1]=1;
        yshear[1][2]=-shy*xref;
        
        yshear[2][0]=0;
        yshear[2][1]=0;
        yshear[2][2]=1;
         mul(input,yshear,output,v);
    }
    

}

void BresLine(int xa,int ya,int xb,int yb)
{
      int dx,dy,d;
      dx=xb-xa;
      dy=yb-ya;
      int c,r,f;
      int i=0;
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


void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    BresLine(-320,0,320,0);
    BresLine(0,-240,0,240);
    glEnd();
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    for(int i=0;i<v;i++)
    {    
        BresLine(input[0][i],input[1][i],input[0][(1+i)%v],input[1][(1+i)%v]);
    }
    glEnd();
   

    glBegin(GL_POINTS);     
    glColor3f(0,1,0);
    for(int i=0;i<v;i++)
    {
       BresLine(output[0][i],output[1][i],output[0][(1+i)%v],output[1][(1+i)%v]);
    }
    
    glEnd();
    glFlush();
}


int main(int argc,char **argv)
{

    printf("\nEnter no. of Vertices: ");
    scanf("%d",&v);
    
    
    for(int i=0; i<v;i++)
    {
        printf("\nX[%d]:",i+1);
        scanf("%d",&input[0][i]);
        printf("\nY[%d]:",i+1);
        scanf("%d",&input[1][i]);
        input[2][i]=1;
    }
        
     //Translation();   
     //Rotation();
     //Scaling();
     //Reflection();
     ShearMatrix();
        
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Window");
    glClearColor(1,1,1,0);
    glColor3f(0,0,0);
    gluOrtho2D(-320,320,-240,240);
    glutDisplayFunc(Draw);
    
    glutMainLoop();
    
    return 0;
}

