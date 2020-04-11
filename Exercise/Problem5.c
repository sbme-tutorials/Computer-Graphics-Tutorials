#include <GL/glut.h>

//Setting Camera
float eye[] = {0.0, 0.0, 5.0};
float center[] = {0.0, 0.0, 0.0};
float up[] = {0.0, 1.0, 0.0};
float alpha = 60;
float theta = 60;
void DB()
{
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    glPopMatrix();
}
void draw_block(float xs, float ys)
{
    glPushMatrix();
    glScalef(xs, ys, 1.0);
    glTranslatef(0.0, -0.5, 0.0);
    DB();
    glPopMatrix(); 
}

void draw_scene()
{
    glPushMatrix();
    glTranslatef(1.0, 3.5, 0.0);
    draw_block(2, 5);
    glTranslatef(1.0, 1.5, 0.0);
    glRotatef(alpha-90, 0.0, 0.0, 1.0); 
    draw_block(3, 1);
    glTranslatef(3.0, 0.0, 0.0);
    glRotatef(theta, 0.0, 0.0, 1.0); 
    draw_block(3, 1);
    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    draw_scene();
    glutSwapBuffers();
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 10, 0, 10, 1, 10);
    // gluPerspective(120.0, 1.0, 1.0, 10.0);
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              up[0], up[1], up[2]);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("red 3D lighted sphere");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
