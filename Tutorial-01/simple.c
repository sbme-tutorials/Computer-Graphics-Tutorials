#include <GL/glut.h>

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);  /* blue */
    glVertex2i(0, 0);
    glColor3f(0.0, 1.0, 0.0);  /* green */
    glVertex2i(150, 250);
    glColor3f(1.0, 0.0, 0.0);  /* red */
    glVertex2i(300, 0);
  glEnd();
  glFlush();  /* Single buffered, so needs a flush. */
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutCreateWindow("single triangle");
  glOrtho(0, 300, 0, 300, -1, 1);   /* Map abstract coords directly to window coords. */
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;      
}
