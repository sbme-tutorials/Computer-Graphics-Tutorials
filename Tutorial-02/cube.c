#include <GL/glut.h>

float light_diffuse[] = {1.0, 0.0, 0.0, 1.0};   /* Red diffuse light. */
float light_position[] = {-1.0, 1.0, 1.0, 0.0}; /* Infinite light location. */
float eye[] = {0.0, 0.0, 5.0};
float center[] = {0.0, 0.0, 0.0};
float up[] = {0.0, 1.0, 0.0};
float translationx = 0.0;
float scale = 1;
float rotation = 0.0;
int rotateFirst = 0;

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glRotatef(rotation, 0.0, 0.0, 1.0);
  glTranslatef(translationx, 0.0, 0.0);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(translationx, 0.0, 0.0);
  glRotatef(rotation, 0.0, 0.0, 1.0);
  if (rotateFirst == 0)
  {
    glPopMatrix();
    glutSolidCube(scale);
  }
  else
  {
    glutSolidCube(scale);
    glPopMatrix();
  }
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case '1':
    translationx += 0.01;
    glutPostRedisplay();
    break;
  case '2':
    scale *= 1.1;
    glutPostRedisplay();
    break;
  case '3':
    rotation += 5;
    glutPostRedisplay();
    break;
  case '4':
    if (rotateFirst == 0)
      rotateFirst = 1;
    else
      rotateFirst = 0;
  }
}
void init()
{
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(100.0, 1.0, 1.0, 10.0);
  gluLookAt(eye[0], eye[1], eye[2],
            center[0], center[1], center[2],
            up[0], up[1], up[2]);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("red 3D lighted cube");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
  return 0;
}
