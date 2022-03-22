#include <GL/glut.h>
static int year = 0, day = 0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    GLfloat light_ambient[] =
        {0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[] =
        {1.0, 1.0, 0.0, 1.0};
    GLfloat light_specular[] =
        {1.0, 1.0, 1.0, 1.0};
    /* light_position is NOT default value */
    GLfloat light_position[] =
        {0.0, 0.0, 4.0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glutWireSphere(1, 20, 16); /* draw sun */
    glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 0.0, 0.0);

    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glutWireSphere(0.2, 20, 8); /* draw smaller planet */

    glPopMatrix();
    glutSwapBuffers();
}

void timer(int value)
{
    if (value == 0)
    {
        day = (day + 1) % 360;
        glutPostRedisplay();
        glutTimerFunc(10, timer, 0);

    }
    else if (value == 1)
    {
        year = (year + 1) % 360;
        glutPostRedisplay();
        glutTimerFunc(10, timer, 1);
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(0, timer, 1);
    glutCreateWindow(argv[0]);
  
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}