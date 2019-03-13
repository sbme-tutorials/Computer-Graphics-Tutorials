#include <GL/glut.h>
#include <stdio.h>

float light_ambient[] = {1.0, 0.0, 0.0, 1.0};   
float light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  
float light_specular[] = {1.0, 1.0, 1.0, 1.0}; 
float light_position[] = {0.0, 0.0, 4.0, 1.0};
float eye[] = {0.0, 0.0, 5.0};
float center[] = {0.0, 0.0, 0.0};
float up[] = {0.0, 1.0, 0.0};

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glPushMatrix();
  glutSolidSphere(3, 32, 32);
  glPopMatrix();
  glutSwapBuffers();
}

void init()
{
  glLightfv(GL_LIGHT1, GL_POSITION, light_position);
  glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);

  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(100.0, 1.0, 1.0, 10.0);
  gluLookAt(eye[0], eye[1], eye[2],
            center[0], center[1], center[2],
            up[0], up[1], up[2]);
  glMatrixMode(GL_MODELVIEW);
}
void main_menu(int value)
{
        if (value == 1)
        {
		printf("White Background\n");
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glutPostRedisplay();
        }
        else if (value == 2)
        {
		printf("Black Background\n");
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glutPostRedisplay();
        }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("red 3D lighted sphere");
  glutDisplayFunc(display);
  glutCreateMenu(main_menu);
  glutAddMenuEntry("White Background", 1);
  glutAddMenuEntry("Black Background", 2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  init();
  glutMainLoop();
  return 0;
}

