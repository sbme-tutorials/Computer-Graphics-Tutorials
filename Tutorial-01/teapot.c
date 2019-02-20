#include <GL/glut.h>

void display(void)
{  
  //Clear color and depth buffers 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Assign a color to the teapot
  glColor3f(0.0, 1.0, 0.0);
  // Rotation
  glRotatef(10, 0.0, 0.0, 1.0);
  glRotatef(10, 0.0, 1.0, 0.0);
  
  //Draw 
  glutWireTeapot(1);
  //Must swap the buffer in double buffer mode
  glutSwapBuffers();
}

void init(void)
{
  //Model(Object coordinates), View (Camera coordinates), Projection (Screen coordinates)
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */
}

int
main(int argc, char **argv)
{
  glutInit(&argc, argv);
  //Use Double buffer, RGB, and depth test mode
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Green 3D Teapot");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;            
}
