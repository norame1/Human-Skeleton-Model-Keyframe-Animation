#include <GLUT/GLUT.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#define PI 3.14159265358979323846
#include <stdlib.h>

#include <chrono>
#include <thread>

float angle = 0;
float leftelbowangle=0;
float rightelbowangle=0;
float leftshoulderangle=0;
float angle1 = 0;
float anglelefthip = 0;
float anglerighthip = 0;
float rightshoulderangle = 0;
float angleleftknee = 0;
float anglerightknee = 0;
float move = 0;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
float anglerighthipz=0;
float anglelefthipz=0;
float tX = 0;
float tY = 0;
float tZ = 0;
float offset =1;
float offset1 =1;
float offset12 =6;
float offset123 =1;
double valZoom = 10.0;

float skeletonX = 0.0f;
float skeletonY = 0.0;
float skeletonZ = 0.0;
double camX = 0, camY = 0, camZ = 10;

/* Callback: The mouse click event is defined based on the number of view ports enabled
*/
void sphereMouseEvent(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;
    }
    else
        mouseDown = false;

    if (mouseDown)
    {
        xdiff = (yrot + x);
        ydiff = -y + xrot;
    }

//    if (mouseDown)
//    {
//        //mouseDown = true;
//        xdiff = (yrot + x);
//        ydiff = -y + xrot;
//    }
}

/* Callback: Mouse movement on the sphere on left mouse down enables sphere rotation
*/
void sphereMouseMotion(int x, int y)
{
    if (mouseDown)
    {
        yrot = -(x + xdiff);
        xrot = (y + ydiff);
        if (xrot > 89) xrot = 89.0f;
        if (xrot < -89) xrot = -89.0f;

        //printf("(xrot, ytor)=(%f, %f)\n", xrot, yrot);
        camX = valZoom * (cos(xrot * PI / 180) * sin(yrot * PI / 180));
        camY = valZoom * (sin(xrot * PI / 180));
        camZ = valZoom * (cos(xrot * PI / 180) * cos(yrot * PI / 180));
       // printf("%d\n", valZoom);
    }
    glutPostRedisplay();
}

/* Callback: Reshape function for the openGL window
*/


void setMaterial(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
    GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
    GLfloat specularR, GLfloat specularG, GLfloat specularB,
    GLfloat shininess) {

    GLfloat ambient[] = { ambientR, ambientG, ambientB };
    GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
    GLfloat specular[] = { specularR, specularG, specularB };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void display() {

    /* clear window */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* future matrix manipulations should affect the modelview matrix */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        camX, camY, camZ,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    );
//    glTranslatef(tX, tY, tZ);
    glColor3f(1, 1, 1);
    glPushMatrix();
//    glTranslatef(0, 0,move
//                 );
    glTranslatef(skeletonX, skeletonY, skeletonZ);
    
    
    glPushMatrix();
    
    glColor3f(1,0,0);
    glTranslatef(0, 0+0.75, 0);
    glScalef(1, 1, 1);
    glutSolidSphere(.1, 100, 20);
    glLoadIdentity();
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(.5,0,0);
    glTranslatef(0, -0.15+0.75, 0);
    glScalef(1, 2, 1);
    glutSolidSphere(.025, 100, 20);
    glLoadIdentity();
    glPopMatrix();
    
//right shoulder
    glPushMatrix();
    glTranslatef(0.1, -0.225+0.75, 0);
//    glRotatef(60, 0, 0, 1);
    glScalef(4, 1, 1);
    glutSolidSphere(.025, 100, 20);
    glLoadIdentity();
    glPopMatrix();
    
//    left shoulder
    glPushMatrix();
    glTranslatef(-0.1, -0.225+0.75, 0);
    glScalef(4, 1, 1);
    glutSolidSphere(.025, 100, 20);
    glLoadIdentity();
    glPopMatrix();
//
//
//    //right arm
    glColor3f(1, 1, 1);
    glPushMatrix();
//    right shoulder joint
    
        glTranslatef(0.2, -0.25+0.75, 0);
        glRotatef(10+angle, 0, 0, 1);
        glRotatef(rightshoulderangle, 1, 0, 0);
        glScalef(1, 1, 1);
        glutSolidSphere(.025, 100, 20);
            glPushMatrix();
    
//   right upper arm
    glColor3f(1,0,0);
            glTranslatef(0, -0.1, 0);
            glScalef(1.5, 4, 1.5);
            glutSolidSphere(.025, 100, 20);
    
//elbow
                glPushMatrix();
    glColor3f(1,1,1);
                glTranslatef(0, -0.025, 0);
                
                glScalef(1/1.5,0.25, 1/1.5);
                glRotatef(angle1, 0, 0, 1);
    glRotatef(rightelbowangle,1,0,0);
                glutSolidSphere(.025, 100, 20);
    
//    right lower arm
    
                        glPushMatrix();
    glColor3f(1,0,0);
                        glTranslatef(0, -0.125, 0);
                        glScalef(1, 5, 1);
                        glutSolidSphere(.025, 100, 20);
    
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0, -0.025, 0);
    glScalef(1, 1/2.5, 1);
    glutSolidSphere(.025, 100, 20);
    glPopMatrix();
//                glLoadIdentity();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    
    //left arm
        glColor3f(1, 0, 0);
      glPushMatrix();
  //    left shoulder joint
    glColor3f(1,1,1);
    
          glTranslatef(-0.2, -0.25+0.75, 0);
            glRotatef(-(10+angle), 0, 0, 1);
    glRotatef(leftshoulderangle, 1, 0, 0);
//        glRotatef(angle, 1, 0, 0);
          glScalef(1, 1, 1);
          glutSolidSphere(.025, 100, 20);
              glPushMatrix();
      
  //   left upper arm
    glColor3f(1,0,0);
              glTranslatef(0, -0.1, 0);
              glScalef(1.5, 4, 1.5);
              glutSolidSphere(.025, 100, 20);
      
  //leftelbow
    glColor3f(1,1,1);
                  glPushMatrix();
                  glTranslatef(0, -0.025, 0);
                   
                  glScalef(1/1.5,0.25, 1/1.5);
            glRotatef(-angle1, 0, 0, 1);
    glRotatef(leftelbowangle,1,0,0);
                  glutSolidSphere(.025, 100, 20);
      
  //    left lower arm
      
                          glPushMatrix();
    glColor3f(1,0,0);
                          glTranslatef(0, -0.125, 0);
                          glScalef(1, 5, 1);
                          glutSolidSphere(.025, 100, 20);
    
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0, -0.025, 0);
    glScalef(1, 1/2.5, 1);
    glutSolidSphere(.025, 100, 20);
    glPopMatrix();
    
  //                glLoadIdentity();
      glPopMatrix();
      glPopMatrix();
      glPopMatrix();
      glPopMatrix();
//    glPushMatrix();
//    glTranslatef(-0.2, -0.35+0.75, 0);
//    glScalef(1, 4, 1);
//    glutSolidSphere(.025, 100, 20);
//    glLoadIdentity();
//
    glPushMatrix();
    glColor3f(0.5,0,0);
    glTranslatef(0, -0.35+0.75, 0);
    glScalef(2, 4, 2);
    glutSolidSphere(.025, 100, 20);
    glPushMatrix();
    glTranslatef(0, -0.05, 0);
    glScalef(1, 1, 1);
    glutSolidSphere(.025, 100, 20);
    glPopMatrix();
    glPopMatrix();
    
    
//
//
//    glTranslatef(-0.2, -0.55+0.75, 0);
//    glScalef(1, 4, 1);
//    glutSolidSphere(.025, 100, 20);
//    glLoadIdentity();
//    glTranslatef(0, -0.75+0.75, 0);
//    glScalef(1, 4, 1);
//    glutSolidSphere(.025, 100, 20);
//    glLoadIdentity();
//
    glPushMatrix();
    glColor3f(0.5,0,0);
    glTranslatef(0.075, 0.05, 0);
    glScalef(3, 1, 1);
    glutSolidSphere(.025, 100, 20);
    glPushMatrix();
    glTranslatef(-0.05, 0, 0);
    glScalef(1, 1, 1);
    glutSolidSphere(.025, 100, 20);
    glPopMatrix();
    glPopMatrix();
//
    
    //left leg joint
    glColor3f(1, 1, 1);
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0.15, 0.025, 0);
    glRotatef(anglelefthip, 1, 0, 0);
    glRotatef(anglelefthipz, 0, 0, 1);
    glScalef(1, 1, 1);
    glutSolidSphere(.025, 100, 20);
    //upper leg
    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(0, -0.175, 0);
    glScalef(1.5, 6, 1.5);
    glutSolidSphere(.025, 100, 20);
    //knee
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0,-0.025, 0);
    glScalef(1/1.5, .1666, 1/1.5);
    glRotatef(angleleftknee, 1, 0, 0);
    glutSolidSphere(.025, 100, 20);
    //lower leg
    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(0,-0.175, 0);
    glScalef(1,6, 1);
    glutSolidSphere(.025, 100, 20);
    
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    //right leg joint
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-0.15, 0.025, 0);
    glRotatef(anglerighthip, 1, 0, 0);
    glRotatef(anglerighthipz, 0, 0, 1);
    glScalef(1, 1, 1);
    glutSolidSphere(.025, 100, 20);
    //upper leg
    glPushMatrix();
    glColor3f(1,0,0);
    
    glTranslatef(0, -0.175, 0);
    glScalef(1.5, 6, 1.5);
    glutSolidSphere(.025, 100, 20);
    //knee
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0,-0.025, 0);
    glScalef(1/1.5, .166666, 1/1.5);
    glRotatef(anglerightknee, 1, 0, 0);
    glutSolidSphere(.025, 100, 20);
    //lower leg
    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(0,-0.175, 0);
    glScalef(1,6, 1);
    glutSolidSphere(.025, 100, 20);
    
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    glPopMatrix();
    
    
   
    
    //floor
    
    glPushMatrix();
    glColor3f(.5,.5,.5);
    
    
    
//    glutSolidSphere(1, 4, 20);
    glBegin(GL_POLYGON);
        glVertex3f(-50,-0.625,50);
        glVertex3f(-50,-0.625,-50);
        glVertex3f(50,-0.625,-50);
        glVertex3f(50,-0.625,50);
        
        
    glEnd();
    
    glPopMatrix();
    
//    glTranslatef(-0.2, -0.275, 0);
//    glScalef(1, 6, 1);
//    glutSolidSphere(.025, 100, 20);
//    glLoadIdentity();
//
    
//    glTranslatef(-0.2, -0.575, 0);
//    glScalef(1, 6, 1);
//    glutSolidSphere(.025, 100, 20);
//    glLoadIdentity();
//
//
//
//
//    glPopMatrix();

    /* flush drawing routines to the window */
    glFlush();
}

void reshape(int width, int height) {

    /* define the viewport transformation */
    glViewport(0, 0, width, height);
}

void initLight()
{
    /* set up lights */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat lightpos[] = { 0.0, 0.0, 15.0 };
    GLfloat lightcolor[] = { 1, 0.5, 0.5 };
    GLfloat ambcolor[] = { 0.2, 0.2, 0.2 };
    GLfloat specular[] = { 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambcolor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcolor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glEnable(GL_COLOR_MATERIAL); // tells opengl to maintain the original color of the object
}

void animatesquat()
{


    if (anglerighthip<30){
        anglerighthip+=3;
        anglelefthip+=3;
    }
    if (anglerightknee>-60){
        angleleftknee-=6;
        anglerightknee-=6;

    }
    if (rightelbowangle<60){
        rightelbowangle+=6;
        leftelbowangle+=6;
    }
    if (skeletonY>-0.0904){
        skeletonY-=0.00904;
    }


    glutPostRedisplay();




}
void animatejump()
{
    if (skeletonY<0.3){
        skeletonY+=0.03;
    }
    if (anglerightknee<0){
        angleleftknee+=12;
        anglerightknee+=12;

    }
    if (rightelbowangle>0){
        rightelbowangle-=6;
        leftelbowangle-=6;
    }
    if (anglerighthip>0){
        anglerighthip-=6;
        anglelefthip-=6;
    }
    
}
void animatelandjump()
{
    if (skeletonY>-0.0904){
        skeletonY-=0.01808;
    }
    if (anglerighthip<30&&skeletonY<0){
        anglerighthip+=3;
        anglelefthip+=3;
    }
    if (rightelbowangle<60){
        rightelbowangle+=6;
        leftelbowangle+=6;
    }
    if (anglerightknee>-60&&skeletonY<0){
        angleleftknee-=6;
        anglerightknee-=6;

    }
    
}
void animatestand()
{
    if (skeletonY<0){
        skeletonY+=0.00904;
    }
    if (anglerightknee<0){
        angleleftknee+=6;
        anglerightknee+=6;

    }
    if (rightelbowangle>0){
        rightelbowangle-=6;
        leftelbowangle-=6;
    }
    if (anglerighthip>0){
        anglerighthip-=3;
        anglelefthip-=3;
    }
    
}
void sidewalk()
{
    if (anglelefthipz<30){
        anglelefthipz+=3;
        anglerighthipz-=3;
    }
    if (angle<60){
        angle+=6;
    }
    if(skeletonY>-0.0904){
        skeletonY-=0.00904;
        skeletonX+=0.03375;
    }
}
void sidewalk1()
{
    if (anglelefthipz>0){
        anglelefthipz-=3;
        anglerighthipz+=3;
    }
    if (angle>0){
        angle-=6;
    }
    if(skeletonY<0){
        skeletonY+=0.00904;
        skeletonX+=0.03375;
    }
}
void sidewalk2()
{
    if (anglelefthipz<30){
        anglelefthipz+=3;
        anglerighthipz-=3;
    }
    if (angle<60){
        angle+=6;
    }
    if(skeletonY>-0.0904){
        skeletonY-=0.00904;
        skeletonX-=0.03375;
    }
}
void sidewalk3()
{
    if (anglelefthipz>0){
        anglelefthipz-=3;
        anglerighthipz+=3;
    }
    if (angle>0){
        angle-=6;
    }
    if(skeletonY<0){
        skeletonY+=0.00904;
        skeletonX-=0.03375;
    }
}

void animate1()
{
//    static  float z_stopper = 0.0;
//
//    if(z_stopper==-0.230){
//        z_stopper = 0.0;
//        std::cout<<z_stopper<<" 11"<<skeletonZ<<std::endl;
//    }
//    while(anglelefthip<20){
//        anglelefthip+=2;
//        anglerighthip-=2;
//    }
    if(anglelefthip<20){
        anglelefthip+=2;
        anglerighthip-=2;
    }
    if(anglerightknee>-10){
        anglerightknee-=1;
    }
    if(rightshoulderangle<20){
        rightshoulderangle+=2;
        leftshoulderangle-=2;
    }
    if(rightelbowangle<10){
        rightelbowangle+=1;
        leftelbowangle+=1;
        skeletonZ-=0.0230;
    }
    
//            anglerightknee-=10;
//    if(z_stopper>-.230){
//        z_stopper = z_stopper - 0.0230;
//        skeletonZ-=0.0230;
////        if(z_stopper<-0.22){
////            z_stopper = 0.0;
////            std::cout<<z_stopper<<" 11"<<skeletonZ<<std::endl;
////        }
//        //z_stopper;
//        std::cout<<z_stopper<<" "<<skeletonZ<<std::endl;
//    }
//    if(skeletonZ>-0.2300){
//        skeletonZ-=0.0230;
//    }
//    std::cout<<" "<<skeletonZ<<std::endl;
    
//            skeletonZ+=0.230;
    if(skeletonY>-0.0407){
        skeletonY-=0.00407;
    }
    
    glutPostRedisplay();

}


void animate2()
{


    if(anglelefthip>0){
        anglelefthip-=2;
        anglerighthip+=2;
    }
    
    if(anglerightknee<0){
        anglerightknee+=1;
    }
    if(rightshoulderangle>0){
        rightshoulderangle-=2;
        leftshoulderangle+=2;
    }
    if(rightelbowangle>0){
        rightelbowangle-=1;
        leftelbowangle-=1;
        skeletonZ-=0.0230;
    }
//            anglerightknee-=10;
    
//            skeletonZ+=0.230;
    if(skeletonY<0){
        skeletonY+=0.00407;
    }


    glutPostRedisplay();



}

void animate3()
{


    if(anglelefthip>-20){
        anglelefthip-=2;
        anglerighthip+=2;
//        std::cout<<anglelefthip<<std::endl;
    }
    if(angleleftknee>-10){
        angleleftknee-=1;
    }
    if(rightshoulderangle<20){
        rightshoulderangle+=2;
        leftshoulderangle-=2;
    }
    if(rightelbowangle<10){
        rightelbowangle+=1;
        leftelbowangle+=1;
        skeletonZ-=0.0230;
    }
//            anglerightknee-=10;
//    if(skeletonZ>-0.680){
//        skeletonZ-=0.0230;
//        std::cout<<skeletonZ<<std::endl;
//    }
//            skeletonZ+=0.230;
    if(skeletonY>-0.0407){
        skeletonY-=0.00407;
    }


    glutPostRedisplay();



}

void animate4()
{


    if(anglelefthip<0){
        anglelefthip+=2;
        anglerighthip-=2;
    }
    if(angleleftknee<0){
        angleleftknee+=1;
    }
    if(rightshoulderangle>0){
        rightshoulderangle-=2;
        leftshoulderangle+=2;
    }
    if(rightelbowangle>0){
        rightelbowangle-=1;
        leftelbowangle-=1;
        skeletonZ-=0.0230;
    }
//            anglerightknee-=10;
//    if(skeletonZ>-0.920){
//        skeletonZ-=0.0230;
//    }
//            skeletonZ+=0.230;
    if(skeletonY<0){
        skeletonY+=0.00407;
    }


    glutPostRedisplay();



}

void keyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
//        case 'A':
//        case 'a': tX = tX - 0.1; break;
//
//        case 'D':
//        case 'd': tX = tX + 0.1; break;
//
//        case 'W':
//        case 'w': tY = tY + 0.1; break;
//
//        case 'S':
//        case 's': tY = tY - 0.1; break;
//
        
//        case 'i': if (angle<=170 ){
//            angle+=2;}break;
//
//
//        case 'I': if (angle>=5 ){
//            angle-=2;}break;
//
//
//        case 't': if (angle1<=170 ){
//            angle1+=2;}break;
//        case 'T': if (angle1>=5 ){
//            angle1-=2;}break;
//
//
//        case 'r': if (rightshoulderangle<=170 ){
//            rightshoulderangle+=3;}break;
//
//
//        case 'R': if (rightshoulderangle>=5 ){
//            rightshoulderangle-=3;}break;
            
        //leg
        case 'j':
            animate1();
            
            
//            while(anglelefthip<20){
//                anglelefthip+=.2;
//                anglerighthip-=.2;
//            }
//            while(anglerightknee>-10){
//                anglerightknee-=.1;
//            }
////            anglerightknee-=10;
//            while(skeletonZ>-0.230){
//                skeletonZ-=0.00230;
//            }
////            skeletonZ+=0.230;
//            while(skeletonY>-0.0407){
//                skeletonY-=0.000407;
//            }
//            skeletonY-=0.0407;
            
        break;
            
        case 'k':
//            anglelefthip-=20;
//            anglerighthip+=20;
//            anglerightknee+=10;
//            skeletonZ-=0.230;
//            skeletonY+=0.0407;
           animate2();
        break;
            
        case 'l':
//            anglelefthip-=20;
//            anglerighthip+=20;
//            angleleftknee-=10;
//            skeletonZ-=0.230;
//            skeletonY-=0.0407;
           animate3();
        break;
            
        case 'm':
            animate4();
//            anglelefthip+=20;
//            anglerighthip-=20;
//            angleleftknee+=10;
//            skeletonZ-=0.230;
//            skeletonY+=0.0407;
        break;
            
      
            
        case 'w':
            skeletonX=0;
            skeletonY=0;
            skeletonZ=0;
            break;
//        case 'J': if (anglelefthip>=-45 ){
//            anglelefthip-=2;}break;
//        //leg
//        case 'k': if (anglerighthip<=45 ){
//            anglerighthip+=2;
////            std::cout<<anglerighthip<<std::endl;
//        }break;
//        case 'K': if (anglerighthip>=-45 ){
//            anglerighthip-=2;}break;
//            //knee left
//        case 'v': if (angleleftknee<=0 ){
//            angleleftknee+=2;}break;
//        case 'V': if (angleleftknee>=-45 ){
//            angleleftknee-=2;}break;
//
//            //right knee
//        case 'b': if (anglerightknee<=0 ){
//            anglerightknee+=2;}break;
//        case 'B': if (anglerightknee>=-45 ){
//            anglerightknee-=2;}break;
//
//        case 'x':
//            skeletonX+=0.005f;break;
//        case 'X':
//            skeletonX-=0.005f;break;
//        case 'q':
//            skeletonX+=0.005f;break;
//        case 'Q':
//            skeletonX-=0.005f;break;
//        case 'y':
//            skeletonY+=0.005f;break;
//        case 'Y':
//            skeletonY-=0.005f;break;
//
//        case 'z':
//            skeletonZ+=0.005;break;
//        case 'Z':
//            skeletonZ-=0.005;break;
        
        case 'e':animatesquat();break;
        case 'r':animatejump();break;
        case 't':animatelandjump();break;
        case 'y':animatestand();break;
        case 'z':sidewalk();break;
        case 'x':sidewalk1();break;
        case 'c':sidewalk2();break;
        case 'v':sidewalk3();break;
            
        default:
            break;
    }
    glutPostRedisplay();
}

void arrowKey(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            valZoom = valZoom + 0.1; break;
        case GLUT_KEY_DOWN:
            valZoom = valZoom - 0.1; break;
        default:
            break;
    }
    camX = valZoom * (cos(xrot * PI / 180) * sin(yrot * PI / 180));
    camY = valZoom * (sin(xrot * PI / 180));
    camZ = valZoom * (cos(xrot * PI / 180) * cos(yrot * PI / 180));
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {

    /* initialize GLUT, using any commandline parameters passed to the
       program */
    glutInit(&argc, argv);

    /* setup the size, position, and display mode for new windows */
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    /* create and set up a window */
    glutCreateWindow("my first openGL");
    glutDisplayFunc(display);

    /* set up depth-buffering */
    glEnable(GL_DEPTH_TEST);

    initLight();

    /* define the projection transformation */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 0.0001, 100);

    //register the IdleFunction
//    glutIdleFunc(animate);
//    glutIdleFunc(animate1);

    //Register keyboard and mouse movements function
    glutMouseFunc(sphereMouseEvent);
    glutMotionFunc(sphereMouseMotion);
    glutKeyboardFunc(keyBoard); // void keyBoard(unsigned char key, int x, int y);
    glutSpecialFunc(arrowKey); // void arrowKey(int key, intx, int y)
    
   
    /* tell GLUT to wait for events */
    glutMainLoop();
}
