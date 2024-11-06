#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "BmpLoader.h"



//#define GL_SILENCE_DEPRECATION
//#ifdef __APPLE_CC__
//#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif
//#include <stdlib.h>
//#include <stdio.h>

unsigned int ID;
double windowHeight=800, windowWidth=600;
double eyeX=70, eyeY=40, eyeZ=200, refX = 0, refY=0,refZ=0;
double theta = 180.0, y = 1.36, z = 7.97888, a=2;

static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};


static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
 GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;
 Ux = x2-x1;
 Uy = y2-y1;
 Uz = z2-z1;
 Vx = x3-x1;
 Vy = y3-y1;
 Vz = z3-z1;
 Nx = Uy*Vz - Uz*Vy;
 Ny = Uz*Vx - Ux*Vz;
 Nz = Ux*Vy - Uy*Vx;
 glNormal3f(Nx,Ny,Nz);
}

void drawCube(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ,
GLfloat shine=50)
{
 GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
 GLfloat mat_ambient[] = { 0.05, 0.05, 0.05, 1.0 };
 GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
 GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
 GLfloat mat_shininess[] = {shine};
 glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
 glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
 glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
 glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
 glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
 glBegin(GL_QUADS);
 for (GLint i = 0; i <6; i++)
 {
 getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1],
 v_cube[quadIndices[i][0]][2],
 v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
 v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
 glVertex3fv(&v_cube[quadIndices[i][0]][0]);glTexCoord2f(1,1);
 glVertex3fv(&v_cube[quadIndices[i][1]][0]);glTexCoord2f(1,0);
 glVertex3fv(&v_cube[quadIndices[i][2]][0]);glTexCoord2f(0,0);
 glVertex3fv(&v_cube[quadIndices[i][3]][0]);glTexCoord2f(0,1);
 }
 glEnd();}


static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte PquadIndices[1][4] =
{
    {0, 3, 2, 1}
};

void drawpyramid()
{
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}


void base()
{
    // right wall
   // glColor3f(0.8, 0.9, 0.9);
    glPushMatrix();
    glTranslatef(-1.5,-1,.5);
    glScalef(15, 15, 0.1);
    drawCube(0.6, 0.5, 0.6,0.6, 0.5, 0.6);
    glPopMatrix();


    // left wall
   // glColor3f(0.5, 0.5, 0.6);
    glPushMatrix();
    glTranslatef(-1.6,-1,0);
    glScalef(0.1, 15, 20);
    drawCube(0.6, 0.5, 0.6,0.6, 0.5, 0.6);
    glPopMatrix();
    //
    glPushMatrix();
    glTranslatef(42.6,-1,0);
    glScalef(0.1, 15, 20);
    drawCube(0.6, 0.5, 0.6,0.6, 0.5, 0.6);
    glPopMatrix();

   //ceiling
   // glColor3f(0.8, 0.8, 0.9);
   glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
    glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(-2,17,0);
    glScalef(15, 0.3, 20);
    drawCube(0.8, 0.8, 0.9,0.8, 0.8, 0.9);
    glPopMatrix();
      glDisable(GL_TEXTURE_2D);

    //top ceiling
     glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(-2,43,0);
    glScalef(15.5, 1.5, 20);
    drawCube(0.8, 0.8, 0.9,0.8, 0.8, 0.9);
    glPopMatrix();

    //enter topceiling
     glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(-2,43,60);
    glScalef(15.5, 1.5, 20);
    drawCube(0.8, 0.8, 0.9,0.8, 0.8, 0.9);
    glPopMatrix();

     // surface

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(-2,-1.5,0);
    glScalef(15, 0.5, 20);
    drawCube(0.8, 0.8, 0.9,0.8, 0.8, 0.9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //extender part
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(-2,17,60);
    glScalef(15, 0.3, 5);
    drawCube(0.8, 0.8, 0.9,0.8, 0.8, 0.9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //2ndfloor devider wall with door
      glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,32);
    glPushMatrix();
    glTranslatef(17.3,17.5,59);
    glScalef(8.5, 10, 0.1);
    drawCube(0.9, 0.9, 0.9,0.9, 0.9, 0.9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,17.5,59);
    glScalef(3, 10, 0.1);
    drawCube(0.9, 0.9, 0.9,0.9, 0.9, 0.9);
    glPopMatrix();

     glPushMatrix();
    glTranslatef(7,33,59);
    glScalef(4, 3.5, 0.1);
    drawCube(0.9, 0.9, 0.9,0.9, 0.9, 0.9);
    glPopMatrix();
      glDisable(GL_TEXTURE_2D);







}

void hallskin(){
    //leftwall
 glPushMatrix();
    glTranslatef(-11.2,-2.5,0);
    glScalef(0.01, 8.5, 20);
    drawCube(0.1,0.1,0.1,0.1,0.1,0.1);
    glPopMatrix();

    //rightwall
    glPushMatrix();
    glTranslatef(-11.5,-2.5,0.9);
    glScalef(30, 8.5, 0.01);
    drawCube(0.1,0.1,0.1,0.1,0.1,0.1);
    glPopMatrix();

    //opo left wall
    glPushMatrix();
    glTranslatef(32.5,-2.5,0);
    glScalef(0.01, 8.5, 20);
    drawCube(0.1,0.1,0.1,0.1,0.1,0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(34.5,-2.5,0);
    glScalef(0.01, 8.5, 20);
    drawCube(0.15,0.15,0.15,0.15,0.15,0.15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(78,-2.5,0);
    glScalef(0.01, 8.5, 20);
    drawCube(0.15,0.15,0.15,0.15,0.15,0.15);
    glPopMatrix();

}

void buildingpart(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
glPushMatrix();
    glTranslatef(22.7,1,19.5);
    glScalef(0.6, 16.5, 0.2);
    drawCube(1,1,1,1,1,1);
    glPopMatrix();
          glDisable(GL_TEXTURE_2D);
}

void enter(){
  // surface
   // glColor3f(0.8, 0.8, 0.9);
       glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(-22,-1.5,-9);
    glScalef(30, 0.5, 20);
    drawCube(0.8, 0.8, 0.9,0.8, 0.8, 0.9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //left wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glPushMatrix();
    glTranslatef(-21.8,-1.5,-10);
    glScalef(0.1, 6.4, 20);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //extended leftwall
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,24);
    glPushMatrix();
    glTranslatef(-21.8,17.8,-10);
    glScalef(0.1, 10, 20);
    drawCube(0.6, 0.6, 0.7,0.6, 0.6, 0.7);
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);

    //right wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glPushMatrix();
    glTranslatef(68,-1.5,-10);
    glScalef(0.1, 6.4, 20);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     //extended rightwall
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,24);
    glPushMatrix();
    glTranslatef(68,17.8,-10);
    glScalef(0.1, 10, 20);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //front wall with doors
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glPushMatrix();
    glTranslatef(-21.8,-1.5,50);
    glScalef(12, 6.4, 0.1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();


    //2nd wall
    glPushMatrix();
    glTranslatef(32,-1.5,50);
    glScalef(12, 6.4, 0.1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);

     //front 2nd main
      glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,25);
      glPushMatrix();
    glTranslatef(-25,42,50);
    glScalef(32, 7, 0.1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
       glDisable(GL_TEXTURE_2D);

       //main front
       glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,26);
       glPushMatrix();
    glTranslatef(-21.8,17.8,50);
    glScalef(30, 8, 0.1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glDisable(GL_TEXTURE_2D);



    //2nd floor walkwaycover




    //walkway
    //glPushMatrix();
    //glTranslatef(-21.8,20,-10);
    //glScalef(14,0.1, 14);
    //drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    //glPopMatrix();


}

void cover2nd(){
 glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,22);
    glPushMatrix();
    glTranslatef(-8,16.5,5.5);
    glScalef(21, 3, 0.1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);}

void stairout(){
//stairs
    //stair1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(-20,0,30);
    glScalef(4, 0.5, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,28);
    glScalef(4, 1, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

     glPushMatrix();
    glTranslatef(-20,0,26);
    glScalef(4, 1.5, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,24);
    glScalef(4, 2, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,22);
    glScalef(4, 2.5, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,20);
    glScalef(4, 3, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,18);
    glScalef(4, 3.5, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,16);
    glScalef(4, 4, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,14);
    glScalef(4, 4.5, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,12);
    glScalef(4, 5, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,10);
    glScalef(4, 5.5, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,8);
    glScalef(4, 6, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void table() {
  // Tabletop
 // glColor3f(0.2, 0.1, 0);
 glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,18);

  glPushMatrix();
  glTranslatef(-41.5,0, -130);
  glScalef(15, 2.5, 0.05);
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

 glDisable(GL_TEXTURE_2D);

}

void photo(){

glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
      glPushMatrix();
  glTranslatef(3.5, 5, 16);
  glScalef(0.1, 3.5, 2); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  //2nd pic
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
   glPushMatrix();
  glTranslatef(3.5, 5, 26);
  glScalef(0.1, 3.5, 2); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  //3rdd pic
 glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
   glPushMatrix();
  glTranslatef(3.5, 5, 36);
  glScalef(0.1, 3.5, 2); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  //mainenter
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
   glPushMatrix();
  glTranslatef(17.5, 0, 74);
  glScalef(0.5, 6, 5); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  //border
  glPushMatrix();
  glTranslatef(17.5, 0, 89.1);
  glScalef(0.5, 6, 0.01); // Adjust the scale for the tabletop
  drawCube(0.2,0.2,0.2,0.2,0.2,0.2);
  glPopMatrix();


  //4th pic
   glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
   glPushMatrix();
  glTranslatef(3.5, 5, 46);
  glScalef(0.1, 3.5, 2); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
   glDisable(GL_TEXTURE_2D);

  //oposite wall
   glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
   glPushMatrix();
  glTranslatef(47.5, 5, 16);
  glScalef(0.1, 3.5, 2); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  //mainenter
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
   glPushMatrix();
  glTranslatef(78, 0, 74);
  glScalef(0.5, 6, 5); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  //border
  glPushMatrix();
  glTranslatef(78, 0, 89.1);
  glScalef(0.5, 6, 0.01); // Adjust the scale for the tabletop
  drawCube(0.2,0.2,0.2,0.2,0.2,0.2);
  glPopMatrix();




  //2nd pic
   glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
   glPushMatrix();
  glTranslatef(47.5, 5, 26);
  glScalef(0.1, 3.5, 2); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  //3rdd pic
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
   glPushMatrix();
  glTranslatef(47.5, 5, 36);
  glScalef(0.1, 3.5, 2); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
glDisable(GL_TEXTURE_2D);
  //4th pic
  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
   glPushMatrix();
  glTranslatef(47.5, 5, 46);
  glScalef(0.1, 3.5, 2); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  //counterpic
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
  glPushMatrix();
  glTranslatef(3.5, 6.5, 5);
  glScalef(15, 3.7, 0.2); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

}

void sofa(){


     glPushMatrix();
  glTranslatef(3, 1.4, 7);
  glScalef(1.2, 0.2, 3); // Adjust the scale for the tabletop
  drawCube(0.4,0,0,0.4,0,0);
  glPopMatrix();

glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,18);
    // Tabletop
  glPushMatrix();
  glTranslatef(3, 1.01, 7);
  glScalef(1.2, 0.1, 3); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

  // Front panel
  glPushMatrix();
  glTranslatef(3, 0, 7);
  glScalef(0.1, 1.5, 3); // Adjust the scale for the front panel
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

  // Side panel 2
  glPushMatrix();
  glTranslatef(3, -0.5, 16);
  glScalef(1.2, 1.40, 0.05); // Adjust the scale for side panel 2
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

  // Side panel 3
  glPushMatrix();
  glTranslatef(3, -0.5, 7);
  glScalef(1.2, 1.40, 0.05); // Adjust the scale for side panel 3
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);


}

void sofaopo(){

    glPushMatrix();
  glTranslatef(3, 1.4, 7);
  glScalef(1.2, 0.2, 3); // Adjust the scale for the tabletop
  drawCube(0.4,0,0,0.4,0,0);
  glPopMatrix();
    // Tabletop
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,18);

  glPushMatrix();
  glTranslatef(3, 1.01, 7);
  glScalef(1.2, 0.1, 3); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

  // Front panel
  glPushMatrix();
  glTranslatef(6.5, 0, 7);
  glScalef(0.1, 1.5, 3); // Adjust the scale for the front panel
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();



  // Side panel 2
  glPushMatrix();
  glTranslatef(3, -0.5, 16);
  glScalef(1.2, 1.40, 0.05); // Adjust the scale for side panel 2
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

  // Side panel 3
  glPushMatrix();
  glTranslatef(3, -0.5, 7);
  glScalef(1.2, 1.40, 0.05); // Adjust the scale for side panel 3
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();
glDisable(GL_TEXTURE_2D);
}


void barTable() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,18);
  // Tabletop
  glPushMatrix();
  glTranslatef(3.5, 5, 16);
  glScalef(1.5, 0.1, -16); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

  //2nd tabletop
   glPushMatrix();
  glTranslatef(3, 5, -37);
  glScalef(13, 0.1, 1.5); // Adjust the scale for the tabletop
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

  // Side panel 1
  glPushMatrix();
  glTranslatef(-2, -0.5, 16);
  glScalef(4, 2, 0.05); // Adjust the scale for side panel 2
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

  // Side panel 2 back
  glPushMatrix();
  glTranslatef(-2, -0.5, -32);
  glScalef(14.6, 2, 0.05); // Adjust the scale for side panel 3
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();





  // back bar panel 1
  glPushMatrix();
  glTranslatef(-1.5, -0.5, 16);
  glScalef(0.03, 5, -16); // Adjust the scale for side panel 1
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

   // front bar panel 1
  glPushMatrix();
  glTranslatef(8, -0.5, 16);
  glScalef(0.03, 2, -16); // Adjust the scale for side panel 1
  drawCube(0.8, 0.9, 0.9,0.8, 0.9, 0.9);
  glPopMatrix();

  //shelf
  glPushMatrix();
  glTranslatef(-1.5, 10, -30);
  glScalef(0.6, 0.2, 15); // Adjust the scale for side panel 1
  drawCube(0.2, 0.1, 0, 0.2, 0.1, 0);
  glPopMatrix();

  //shelf2
  glPushMatrix();
  glTranslatef(-1.5, 6, -30);
  glScalef(0.6, 0.2, 15); // Adjust the scale for side panel 1
  drawCube(0.2, 0.1, 0, 0.2, 0.1, 0);
  glPopMatrix();
glDisable(GL_TEXTURE_2D);


//long back
 glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,31);
   glPushMatrix();
  glTranslatef(0, -3, -40);
  glScalef(13.5, 6.5, 0.05); // Adjust the scale for side panel 3
  drawCube(0.6, 0.5, 0.6,0.6, 0.5, 0.6);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);


}

void projector(){

      glPushMatrix();
  glTranslatef(-1.5, 6, -31);
  glScalef(1, 0.5, 1); // Adjust the scale for side panel 1
  drawCube(0,0,0,0,0,0);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.5, 6.5, -30);
  glScalef(0.5, 2, 0.5); // Adjust the scale for side panel 1
  drawCube(0,0,0,0,0,0);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-1.5, 12, -31);
  glScalef(0.8, 0.5, 1); // Adjust the scale for side panel 1
  drawCube(0,0,0,0,0,0);
  glPopMatrix();

}


void grass()
{
     //grass
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(-50,-2,-30);
    glScalef(100, 0.1, 120);
    drawCube(0.8, 0.8, 0.9,0.8, 0.8, 0.9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //sky
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,19);
    glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(-60,-5,-40);
    glScalef(105, 150, 0.1);
    drawCube(0.8, 0.8, 0.9,0.8, 0.8, 0.9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //leftsky
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,20);
    glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(-60,-5,-40);
    glScalef(0.1, 150, 100);
    drawCube(0.8, 0.8, 0.9,0.8, 0.8, 0.9);
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);

    //right sky
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(250,-5,-40);
    glScalef(0.1, 150, 100);
    drawCube(0.8, 0.8, 0.9,0.8, 0.8, 0.9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



}

void light0()
{
 //top right farthest corner
 GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
 GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
 GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
 GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
 GLfloat light_position[] = { 5.0, 4.0, -5.0, 3.0 }; //Change x,y,z to change position of light
 glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
 glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
 glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
 glLightfv( GL_LIGHT0, GL_POSITION, light_position);
 glEnable( GL_LIGHT0);
}
void light1()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 5.0, 4.0, 5.0, 1.0 }; //Change x,y,z to change position of light
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glEnable(GL_LIGHT1);  // <-- Corrected
}

void light2()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 5.0, 10.0, 60, 1.0 }; //Change x,y,z to change position of light
    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    glEnable(GL_LIGHT2);  // <-- Corrected
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// DEMO CODE FOR DRAW WARDROBE

void cellight(){
    glPushMatrix();
    glTranslatef(2.5, 1.5, 4.8);
    glScalef(0.8, 0.05, 0.05);
    drawCube(0.75, 0.75, 0.75,0.75, 0.75, 0.75);
    glPopMatrix();
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// DEMO CODE FOR DRAW WINDOW
void window() //Screen
{

    //tv
    //glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-0.9,3,4);
    glScalef(0.09, 7, 12);
    drawCube(0.0, 0.0, 0.0,0.0, 0.0, 0.0);
    glPopMatrix();

    //soundbox
glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
     glPushMatrix();
    glTranslatef(-1,1,-2);
    glScalef(1, 7, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    //soundbox left

     glPushMatrix();
    glTranslatef(-1,1,44);
    glScalef(1, 7, 1);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void cinemachair() {

    // Chair seat
    glPushMatrix();
    glTranslatef(3, 1, 44);
    glScalef(0.8, 0.8, 0.8); // Adjust the scale for the chair seat
    drawCube(0.3, 0, 0,0.3, 0, 0);
    glPopMatrix();

    // Handle1
    glPushMatrix();
    glTranslatef(3.5, 1, 46.5);
    glScalef(0.7, 1.1, 0.15); // Adjust the scale for handle1
    drawCube(0.3, 0, 0,0.3, 0, 0);
    glPopMatrix();

    // Handle2
    glPushMatrix();
    glTranslatef(3.5, 1, 43.5);
    glScalef(0.7, 1.1, 0.15); // Adjust the scale for handle2
    drawCube(0.3, 0, 0,0.3, 0, 0);
    glPopMatrix();

    // Backrest

    glPushMatrix();
    glTranslatef(5.6, 1, 44);
    glScalef(0.1, 1.7, 1); // Adjust the scale for the backrest
    drawCube(0.7, 0, 0,0.7, 0, 0);
    glPopMatrix();
}

void signboard(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glPushMatrix();
    glTranslatef(5.55,1,70);
    glScalef(0.3, 5, 0.7);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,1,70);
    glScalef(0.3, 5, 0.7);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
      glDisable(GL_TEXTURE_2D);

    //signboard
      glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,27);
     glPushMatrix();
    glTranslatef(-1,16,70);
    glScalef(2.5, 0.5, 0.7);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);
}

void stair(){
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
       glPushMatrix();
    glTranslatef(16,1,-2);
    glScalef(1.5, 0.5, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    //2nd layer
      glPushMatrix();
    glTranslatef(20,1,-2);
    glScalef(1.5, 1, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    //3nd layer
      glPushMatrix();
    glTranslatef(24,1,-2);
    glScalef(1.5, 1.5, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    //4th layer
    glPushMatrix();
    glTranslatef(28,1,-2);
    glScalef(1.5, 2, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

//5th layer
glPushMatrix();
    glTranslatef(32,1,-2);
    glScalef(1.5, 2.5, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    //6th layer
glPushMatrix();
    glTranslatef(36,1,-2);
    glScalef(1.5, 3, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void stair2(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);
 glPushMatrix();
    glTranslatef(16,1,-2);
    glScalef(1.5, 0.5, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    //2nd layer
      glPushMatrix();
    glTranslatef(20,1,-2);
    glScalef(1.5, 1, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    //3nd layer
      glPushMatrix();
    glTranslatef(24,1,-2);
    glScalef(1.5, 1.5, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    //4th layer
    glPushMatrix();
    glTranslatef(28,1,-2);
    glScalef(1.5, 2, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

//5th layer
glPushMatrix();
    glTranslatef(32,1,-2);
    glScalef(1.5, 2.5, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();

    //6th layer
glPushMatrix();
    glTranslatef(36,1,-2);
    glScalef(1.5, 3, 17);
    drawCube(0.5, 0.5, 0.6,0.5, 0.5, 0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void popcorn(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 30);
    glPushMatrix();
    glTranslatef(2, 2.5, 10);
    glScalef(0.4, 1, 1);  // Adjust the scale for the bottle (increased scale)
    drawCube(0.6, 0.5, 0.6,0.6, 0.5, 0.6);  // Bottle dimensions and appearance
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(2, 2.5, 13);
    glScalef(0.4, 1, 0.01);  // Adjust the scale for the bottle (increased scale)
    drawCube(0,0,0,0,0,0);  // Bottle dimensions and appearance
    glPopMatrix();


}

void drawBottle() {
    // Draw the main body of the bottle
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 29);
    glPushMatrix();
    glTranslatef(2, 2.5, 10);
    glScalef(0.4, 0.6, 0.4);  // Adjust the scale for the bottle (increased scale)
    drawCube(0.6, 0.6, 0, 0.6, 0.6, 0);  // Bottle dimensions and appearance
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Draw the bottle cap
    glPushMatrix();
    glTranslatef(2, 4.5, 10);
    glScalef(0.4, 0.2, 0.4);  // Adjust the scale for the cap (increased scale)
    drawCube(0.2, 0.2, 0.2, 0.2, 0.2, 0.2);  // Cap dimensions and appearance
    glPopMatrix();

    // Draw the bottle top
    glPushMatrix();
    glTranslatef(2.5, 5, 10.4);
    glScalef(0.1, 0.52, 0.16);  // Adjust the scale for the top (increased scale)
    drawCube(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  // Top dimensions and appearance
    glPopMatrix();


}




void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
      glEnable(GL_LIGHTING);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(90,1,1,900);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  0,1,0); //7,2,15, 0,0,0, 0,1,0

    //glViewport(0, 0, 800, 600);

    base();  // DRAW THE BASE OF THE HOUSE


       glPushMatrix();
       glTranslatef(-17.0,1.0,-12.0);
       cellight();
       glPopMatrix();

    //2nd buildong
       glPushMatrix();
       glTranslatef(45.5,0,0);
       base();
       glPopMatrix();

       //hallskin
         glPushMatrix();
       glTranslatef(10,20,0);
       hallskin();
       glPopMatrix();


       //grass
       glPushMatrix();
       glTranslatef(-95,-0.4,-50);
       grass();
       glPopMatrix();

       //Screen
        glPushMatrix();
       glTranslatef(0,17,10);
       window();
       glPopMatrix();

       //stair
       glPushMatrix();
       glTranslatef(1.7,17,10);
       stair();
       glPopMatrix();



         //cinemachair starts

       //cinemachair
       glPushMatrix();
       glTranslatef(15.5,18.5,10);
       cinemachair();
       glPopMatrix();

       //cinemachair starts
       glPushMatrix();
       glTranslatef(15.5,18.5,6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(15.5,18.5,2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(15.5,18.5,-2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(15.5,18.5,-6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(15.5,18.5,-20);
       cinemachair();
       glPopMatrix();

         glPushMatrix();
       glTranslatef(15.5,18.5,-24);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(15.5,18.5,-28);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(15.5,18.5,-32);
       cinemachair();
       glPopMatrix();

       //2nd row

       glPushMatrix();
       glTranslatef(19.6,20,10);
       cinemachair();
       glPopMatrix();
       //cinemachair starts
       glPushMatrix();
       glTranslatef(19.6,20,6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(19.6,20,2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(19.6,20,-2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(19.6,20,-6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(19.6,20,-20);
       cinemachair();
       glPopMatrix();

         glPushMatrix();
       glTranslatef(19.6,20,-24);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(19.6,20,-28);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(19.6,20,-32);
       cinemachair();
       glPopMatrix();

        //3rd row

       glPushMatrix();
       glTranslatef(23.6,21.5,10);
       cinemachair();
       glPopMatrix();

       //cinemachair starts
       glPushMatrix();
       glTranslatef(23.6,21.5,6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(23.6,21.5,2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(23.6,21.5,-2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(23.6,21.5,-6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(23.6,21.5,-20);
       cinemachair();
       glPopMatrix();

         glPushMatrix();
       glTranslatef(23.6,21.5,-24);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(23.6,21.5,-28);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(23.6,21.5,-32);
       cinemachair();
       glPopMatrix();


        //4th row
       glPushMatrix();
       glTranslatef(27.6,23,10);
       cinemachair();
       glPopMatrix();

       //cinemachair starts
       glPushMatrix();
       glTranslatef(27.6,23,6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(27.6,23,2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(27.6,23,-2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(27.6,23,-6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(27.6,23,-20);
       cinemachair();
       glPopMatrix();

         glPushMatrix();
       glTranslatef(27.6,23,-24);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(27.6,23,-28);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(27.6,23,-32);
       cinemachair();
       glPopMatrix();

       //5th row
       glPushMatrix();
       glTranslatef(31.6,24.7,10);
       cinemachair();
       glPopMatrix();
       //cinemachair starts
       glPushMatrix();
       glTranslatef(31.6,24.7,6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(31.6,24.7,2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(31.6,24.7,-2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(31.6,24.7,-6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(31.6,24.7,-20);
       cinemachair();
       glPopMatrix();

         glPushMatrix();
       glTranslatef(31.6,24.7,-24);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(31.6,24.7,-28);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(31.6,24.7,-32);
       cinemachair();
       glPopMatrix();

       //projector 1st building
       glPushMatrix();
       glTranslatef(40.5,21.3,63);
       projector();
       glPopMatrix();







       //2nd building stuffs
        glPushMatrix();
       glTranslatef(46,17,10);
       window();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(47,17,10);
       stair2();
       glPopMatrix();

       //cinemachair starts
       //cinemachair

       glPushMatrix();
       glTranslatef(61,18.5,10);
       cinemachair();
       glPopMatrix();

       //cinemachair starts
       glPushMatrix();
       glTranslatef(61,18.5,6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(61,18.5,2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(61,18.5,-2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(61,18.5,-6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(61,18.5,-20);
       cinemachair();
       glPopMatrix();

         glPushMatrix();
       glTranslatef(61,18.5,-24);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(61,18.5,-28);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(61,18.5,-32);
       cinemachair();
       glPopMatrix();

       //2nd row

       glPushMatrix();
       glTranslatef(65.1,20,10);
       cinemachair();
       glPopMatrix();
       //cinemachair starts
       glPushMatrix();
       glTranslatef(65.1,20,6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(65.1,20,2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(65.1,20,-2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(65.1,20,-6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(65.1,20,-20);
       cinemachair();
       glPopMatrix();

         glPushMatrix();
       glTranslatef(65.1,20,-24);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(65.1,20,-28);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(65.1,20,-32);
       cinemachair();
       glPopMatrix();

        //3rd row

       glPushMatrix();
       glTranslatef(69,21.5,10);
       cinemachair();
       glPopMatrix();

       //cinemachair starts
       glPushMatrix();
       glTranslatef(69,21.5,6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(69,21.5,2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(69,21.5,-2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(69,21.5,-6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(69,21.5,-20);
       cinemachair();
       glPopMatrix();

         glPushMatrix();
       glTranslatef(69,21.5,-24);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(69,21.5,-28);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(69,21.5,-32);
       cinemachair();
       glPopMatrix();


        //4th row
       glPushMatrix();
       glTranslatef(73.1,23,10);
       cinemachair();
       glPopMatrix();

       //cinemachair starts
       glPushMatrix();
       glTranslatef(73.1,23,6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(73.1,23,2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(73.1,23,-2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(73.1,23,-6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(73.1,23,-20);
       cinemachair();
       glPopMatrix();

         glPushMatrix();
       glTranslatef(73.1,23,-24);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(73.1,23,-28);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(73.1,23,-32);
       cinemachair();
       glPopMatrix();

       //5th row
       glPushMatrix();
       glTranslatef(77.1,24.7,10);
       cinemachair();
       glPopMatrix();
       //cinemachair starts
       glPushMatrix();
       glTranslatef(77.1,24.7,6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(77.1,24.7,2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(77.1,24.7,-2);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(77.1,24.7,-6);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(77.1,24.7,-20);
       cinemachair();
       glPopMatrix();

         glPushMatrix();
       glTranslatef(77.1,24.7,-24);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(77.1,24.7,-28);
       cinemachair();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(77.1,24.7,-32);
       cinemachair();
       glPopMatrix();








       //stair outside
       glPushMatrix();
       glTranslatef(20,0,67);
       stairout();
       glPopMatrix();

       //stair outside
       glPushMatrix();
       glTranslatef(95,0,67);
       stairout();
       glPopMatrix();



       //signboard
       glPushMatrix();
       glTranslatef(35,-3,36.8);
       signboard();
       glPopMatrix();

        glPushMatrix();
       glTranslatef(43,-3,36.8);
       signboard();
       glPopMatrix();

        //buildong part
       glPushMatrix();
       glTranslatef(20,-3,40);
       buildingpart();
       glPopMatrix();

       //enter
        //buildong part
       glPushMatrix();
       glTranslatef(20,0,70);
       enter();
       glPopMatrix();

       //table
       glPushMatrix();
       glTranslatef(20,0,70);
       table();
       glPopMatrix();

       //photo
       glPushMatrix();
       glTranslatef(-5,0,2);
       photo();
       glPopMatrix();

       //sofa
       glPushMatrix();
       glTranslatef(-3,0,25);
       sofa();
       glPopMatrix();
       //2nd sofa
       glPushMatrix();
       glTranslatef(-3,0,40);
       sofa();
       glPopMatrix();

       //sofa opo
       glPushMatrix();
       glTranslatef(35.5,0,25);
       sofaopo();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(35.5,0,40);
       sofaopo();
       glPopMatrix();


       //foodcourte table
       glPushMatrix();
       glTranslatef(46,1,41);
       barTable();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(43,9.1,42);
       drawBottle();
       glPopMatrix();

       //popcorn
        glPushMatrix();
       glTranslatef(43,5,42);
       popcorn();
       glPopMatrix();

        glPushMatrix();
       glTranslatef(43,5,38);
       popcorn();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(43,5,34);
       popcorn();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(43,5,30);
       popcorn();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(43,5,20);
       popcorn();
       glPopMatrix();

        glPushMatrix();
       glTranslatef(43,5,12);
       popcorn();
       glPopMatrix();

        glPushMatrix();
       glTranslatef(43,5,8);
       popcorn();
       glPopMatrix();

       //bottle
        glPushMatrix();
       glTranslatef(43,9.1,38);
       drawBottle();
       glPopMatrix();
         //bottle
       glPushMatrix();
       glTranslatef(43,9.1,34);
       drawBottle();
       glPopMatrix();

         glPushMatrix();
       glTranslatef(43,9.1,20);
       drawBottle();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(43,9.1,16);
       drawBottle();
       glPopMatrix();

       glPushMatrix();
       glTranslatef(43,9.1,12);
       drawBottle();
       glPopMatrix();



       glPushMatrix();
       glTranslatef(20,0,70);
       cover2nd();
       glPopMatrix();



    glFlush();
    glutSwapBuffers();
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//DO NOT TOUCH!!!!

// CODE FOR KEYBOARD CONTROL
void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case 'w': // move eye point upwards along Y axis
            eyeY+=1.0;
            refY+=1.0;
            break;
        case 's': // move eye point downwards along Y axis
            eyeY-=1.0;
            refY-=1.0;
            break;
        case 'a': // move eye point left along X axis
            eyeX-=1.0;
            refX-=1.0;
            break;
        case 'd': // move eye point right along X axis
            eyeX+=1.0;
            refX+=1.0;
            break;
        case 'o':  //zoom out
            eyeZ+=1;
            refZ+=1;
            break;
        case 'i': //zoom in
            eyeZ-=1;
            refZ-=1;
            break;
        case 'q': //back to default eye point and ref point
                eyeX=0.0; eyeY=2.0; eyeZ=40.0;
                refX=0.0; refY=0.0; refZ=0.0;
            break;
        case 'j': // move ref point upwards along Y axis
            refY+=1.0;
            break;
        case 'n': // move ref point downwards along Y axis
            refY-=1.0;
            break;
        case 'b': // move ref point left along X axis
            refX-=1.0;
            break;
        case 'm': // move eye point right along X axis
            refX+=1.0;
            break;
        case 'k':  //move ref point away from screen/ along z axis
            refZ+=1;
            break;
        case 'l': //move ref point towards screen/ along z axis
            refZ-=1;
            break;

        case 27:    // Escape key
            exit(1);
    }

    glutPostRedisplay();
}

void fullScreen(int w, int h)
{
    //Prevent a divide by zero, when window is too short;you cant make a window of zero width.
    if (h == 0)
        h = 1;
    float ratio = (GLfloat)w / (GLfloat)h;         //Calculate aspect ratio of the window

    //Set the perspective coordinate system
    glMatrixMode(GL_PROJECTION);                   //Use the Projection Matrix
    glLoadIdentity();                              //Reset Matrix

    glViewport(0, 0, w, h);                        //Set the viewport to be the entire window
    gluPerspective(120, ratio, 1, 3000);             //Set the correct perspective.
    //glFrustum(-2.5,2.5,-2.5,2.5, ratio, 200);
    glMatrixMode(GL_MODELVIEW);                    //Get Back to the Modelview
}


void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}





int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    std::cout<<"To move Eye point:"<< std::endl;
    std::cout<<"w: up"<<std::endl;
    std::cout<<"s: down"<<std::endl;
    std::cout<<"a: left"<<std::endl;
    std::cout<<"d: right"<<std::endl;
    std::cout<<"i: zoom in"<<std::endl;
    std::cout<<"o: zoom out"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"To move Camera point:"<< std::endl;
    std::cout<<"j: up"<<std::endl;
    std::cout<<"n: down"<<std::endl;
    std::cout<<"b: left"<<std::endl;
    std::cout<<"m: right"<<std::endl;
    std::cout<<"l: move nearer"<<std::endl;
    std::cout<<"k: move far"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"Press q to move to default position"<<std::endl;
    std::cout<<"      "<<std::endl;




    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("CGIPL Final");

    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\barcar.bmp");//1
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\p1.bmp");//2
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\p2.bmp");//3
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\p4.bmp");//4
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\p5.bmp");//5
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\p6.bmp");//6
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\p7.bmp");//7
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\p8.bmp");//8
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\p9.bmp");//9
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\counter.bmp");//10
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\grass.bmp");//11
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\leftwall.bmp");//12
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\glass.bmp");//13
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\cinemachair.bmp");//14
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\enterfloor.bmp");//15
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\sound.bmp");//16
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\cinemacarpet.bmp");//17
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\table.bmp");//18
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\sky.bmp");//19
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\skyleft.bmp");//20
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\skyright.bmp");//21
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\secondfloor.bmp");//22
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\glassmain.bmp");//23
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\glasswall.bmp");//24
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\cinema.bmp");//25
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\cinema2.bmp");//26
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\signboard.bmp");//27
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\steel.bmp");//28
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\tvwall.bmp");//29
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\popcorn.bmp");//30
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\wallpic2.bmp");//31
    LoadTexture("D:\\Class Works\\CGIPL\\Final\\Assignment\\BMP\\wallinside.bmp");//32





    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );


    glutReshapeFunc(fullScreen);
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);

    glShadeModel( GL_SMOOTH );

    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);
    light0();
    light1();
    light2();


    glutMainLoop();

    return 0;
}
