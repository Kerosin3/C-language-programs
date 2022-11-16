#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define SPINNING_FACTOR 1.0 // for more speed -> increase
#define PERSPECTIVE_DISTANCE 30 // set how far the cube is seen
#define ANGLE_OF_VIEW 30
#define CLOCKWISE 1  // 1 is clockwise, -1 if anticlockwise

// draw cube with gradients on its sides
void DisplayFunc(void)
{
    static float alpha = 0; 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0, 0, -10);
    glRotatef(ANGLE_OF_VIEW, 1, 0, 0);
#if(CLOCKWISE == 1 )
    glRotatef(alpha, 0, -1, 0);
#else
    glRotatef(alpha, 0, 1, 0);
#endif

    glBegin(GL_QUADS); // begin draw
    
    glColor3f(0, 0, 0); //gradients
    glVertex3f(-1, -1, -1);
    glColor3f(0, 0, 1); // gradients
    glVertex3f(-1, -1, 1);
    glColor3f(0, 1, 1); // gradients
    glVertex3f(-1, 1, 1);
    glColor3f(0, 1, 0); //gradients
    glVertex3f(-1, 1, -1);

    glColor3f(1, 0, 0);
    glVertex3f(1, -1, -1);
    glColor3f(1, 0, 1);
    glVertex3f(1, -1, 1);
    glColor3f(1, 1, 1);
    glVertex3f(1, 1, 1);
    glColor3f(1, 1, 0);
    glVertex3f(1, 1, -1);

    glColor3f(0, 0, 0);
    glVertex3f(-1, -1, -1);
    glColor3f(0, 0, 1);
    glVertex3f(-1, -1, 1);
    glColor3f(1, 0, 1);
    glVertex3f(1, -1, 1);
    glColor3f(1, 0, 0);
    glVertex3f(1, -1, -1);

    glColor3f(0, 1, 0);
    glVertex3f(-1, 1, -1);
    glColor3f(0, 1, 1);
    glVertex3f(-1, 1, 1);
    glColor3f(1, 1, 1);
    glVertex3f(1, 1, 1);
    glColor3f(1, 1, 0);
    glVertex3f(1, 1, -1);

    glColor3f(0, 0, 0);
    glVertex3f(-1, -1, -1);
    glColor3f(0, 1, 0);
    glVertex3f(-1, 1, -1);
    glColor3f(1, 1, 0);
    glVertex3f(1, 1, -1);
    glColor3f(1, 0, 0);
    glVertex3f(1, -1, -1);

    glColor3f(0, 0, 1);
    glVertex3f(-1, -1, 1);
    glColor3f(0, 1, 1);
    glVertex3f(-1, 1, 1);
    glColor3f(1, 1, 1);
    glVertex3f(1, 1, 1);
    glColor3f(1, 0, 1);
    glVertex3f(1, -1, 1);

    glEnd();
	
    //set spinning factor
    alpha = alpha + SPINNING_FACTOR;

    glFlush();
    glutSwapBuffers();
    //update
    glutPostRedisplay();
}

void ReshapeFunc(int width, int height)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(PERSPECTIVE_DISTANCE, width / (float)height, 5, 15);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

// press Esc to exit
void KeyboardFunc(unsigned char key, int x, int y)
{
    int dummy;

    dummy = x + y; //its ok
    if (27 == key) {
	printf("exiting application spinning cube\n");
        exit(0);
	}
}

int main(int argc, char **argv)
{
    printf("starting application spinning cube\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL spinning cube");

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    // callbacks
    glutDisplayFunc(&DisplayFunc);
    glutReshapeFunc(&ReshapeFunc);
    glutKeyboardFunc(&KeyboardFunc);
    //main loop
    glutMainLoop();

    return 0;
}
