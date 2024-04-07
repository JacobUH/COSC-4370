/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "./freeglut-3.4.0/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = { 0,1,4,1 };
int windowWidth = 640, windowHeight = 480;
double xRot = 0;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

// teapots in different orientations
void problem1() {

  // Produce Outside Teapots
  glPushMatrix();
  glTranslatef(0, -1, 0); // centers, weird enough
  
  for (int i = 0; i < 4; i++){
    glTranslatef(1, 1, 0); // move location
    glRotatef(90, 0, 0, 1); // rotate teapot
    glutSolidTeapot(0.1); // place teapot
  }
  glPopMatrix();
  
  // Produce Inside Teapots
  glPushMatrix(); 
  glTranslatef(0.25, -0.25, 0);
  glRotatef(45, 0, 0, 1);

  for (int i = 0; i < 4; ++i) {
    glTranslatef(0.35, 0.35, 0);
    glRotatef(90, 0, 0, 1);
    glutSolidTeapot(0.1);
  }
  glPopMatrix();
}

void problem2() {
  const int numRows = 7;

  for (int i = 0; i < numRows; ++i) {
    int numPots = (i < numRows / 2) ? i + 1 : numRows - i;

    for (int j = 0; j < numPots; ++j) {
      glPushMatrix();
      glTranslatef((j - numPots / 2.0f + 0.5f) * 0.3, (i - numRows / 2.0f + 0.5f) * 0.3, 1);
      glutSolidTeapot(0.1);
      glPopMatrix();
    }

    glPopMatrix();
  }
}

void problem3() {
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
  
    // Top to Mid
    for (int i = 1; i <= 11; i++){
      glPushMatrix();
      
      glTranslatef(x, i * 0.1, z);
      glScalef((11 - i) * 2, 1, (11 - i) * 2);
      glutSolidCube(0.1);

      glPopMatrix();
    }
  
    // Mid to Bottom
    for (int j = 1; j <= 10; j++){
      glPushMatrix();
      
      glTranslatef(x, (j * -0.1) + 0.2, z);
      glScalef((11 - j) * 2, 1, (11 - j) * 2);
      glutSolidCube(0.1);
      
      glPopMatrix();
    }
    
}

// texas flag
void problem4() {
  
  glDisable(GL_LIGHTING);

  // blue part
  glPushMatrix();
  glColor3f(0, 0, 1);
  glTranslatef(-0.75, 0.25, 0);
  glScalef(1,2,1);
  glutSolidCube(0.5);
  glPopMatrix();
  
  // white part
  glPushMatrix();
  glColor3f(1, 1, 1);
  glTranslatef(0.0, 0.5, 0.0);
  glScalef(2, 1, 1);
  glutSolidCube(0.5);
  glPopMatrix();

  // red part
  glPushMatrix();
  glColor3f(1, 0, 0);
  glTranslatef(0.0, 0.0, 0.0);
  glScalef(2, 1, 1);
  glutSolidCube(0.5);
  glPopMatrix();

  // star
  glPushMatrix();
  glColor3f(1, 1, 1);
  glTranslatef(-0.8, 0.35, 0.275);
  
  for (int i = 0; i < 5; i++) {
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    float angle1 = i * 72.0 * 3.14159265 / 180.0;
    float angle2 = (i + 2) * 72.0 * 3.14159265 / 180.0;

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.1 * cos(angle1), 0.1 * sin(angle1), 0.0);
    glVertex3f(0.1 * cos(angle2), 0.1 * sin(angle2), 0.0);

    glEnd();
    glPopMatrix();
  }

  glEnable(GL_LIGHTING);
  glPopMatrix();
}

void display()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x axis
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y axis
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z axis
    glEnd(/*GL_LINES*/);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, windowWidth, windowHeight);

    float ratio = (float)windowWidth / (float)windowHeight;
    gluPerspective(50, ratio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    if (curProblem == 1) problem1();
    if (curProblem == 2) problem2();
    if (curProblem == 3) problem3();
    if (curProblem == 4) problem4();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
    else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

    lastPos[0] = x;
    lastPos[1] = y;
}

void mouseMoved(int x, int y)
{
    if (leftDown) {
        xRot += (y - lastPos[1]) * .1;
        yRot += (x - lastPos[0]) * .1;
    }
    if (rightDown) {
        for (int i = 0; i < 3; i++)
            cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
    }


    lastPos[0] = x;
    lastPos[1] = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    curProblem = key - '0';
    if (key == 'q' || key == 'Q' || key == 27) {
        exit(0);
    }
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("HW2");

    glutDisplayFunc(display);
    glutMotionFunc(mouseMoved);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}