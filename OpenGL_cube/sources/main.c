#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/gl.h>


int WindW, WindH;
int i;
int alpha;

void Visibility(int state) // Visibility function
{
  if (state == GLUT_NOT_VISIBLE) printf("Window not visible!\n");
  if (state == GLUT_VISIBLE) printf("Window visible!\n");
}

void Reshape(int width, int height) // Reshape function
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // gluOrtho2D(-1, 1, -1, 1);
  glOrtho(-1, 1, -1, 1, 0, 10);
  glMatrixMode(GL_MODELVIEW);

  WindW = width;
  WindH = height;
}

void timf(int value) // Timer function
{
  glutPostRedisplay();  // Redraw windows
  glutTimerFunc(40, timf, 0); // Setup next timer
}


void Draw(void) // Window redraw function
{

  glClear(GL_COLOR_BUFFER_BIT);

  glLineWidth(3);
  glColor3f(0.0f, 0.6f, 0.9f);

  glPushMatrix();
  glRotatef(alpha, 0.0f, 0.0f, 1.0f);
  alpha += 2;
  if (alpha > 359) alpha = 0;
  glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    // glVertex2f(0.9f, 0.9f);
  glEnd();
  glPopMatrix();


  glFlush();
  glutSwapBuffers();
}


int main(int argc, char *argv[]){

  WindW = 400;
  WindH = 300;
  alpha = 4;

  glutInit(&argc, argv);
  glutInitWindowSize(WindW, WindH);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  (void)glutCreateWindow("OTUS OpenGL");

  glutReshapeFunc(Reshape); // Set up reshape function
  glutDisplayFunc(Draw);    // Set up redisplay function
  glutTimerFunc(40, timf, 0); // Set up timer for 40ms, about 25 fps
  glutVisibilityFunc(Visibility); // Set up visibility funtion
  glClearColor(1, 1, 1, 0);

  glutMainLoop();

	return 0;
}
