#include <GL/glut.h>
#include <math.h>

#define PI 3.14

double eye[] = {0.0, 0.0, 5.0};
double center[] = {0.0, 0.0, 0.0};
double up[] = {0.0, 1.0, 0.0};

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta) * p[0];
	temp[1] += cos(theta) * p[1];
	temp[2] += cos(theta) * p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}

// Rotation about vertical direction
void lookRight()
{
}

void lookLeft()
{
}

// Rotation about horizontal direction

void lookUp()
{
}

void lookDown()
{
	// Write your code here
}

// Forward and Backward
void moveForward()
{
}

void moveBackword()
{
	// Write your code here
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2],
			  center[0], center[1], center[2],
			  up[0], up[1], up[2]);
	glColor3f(0.0, 1.0, 0.0);
	glutWireTeapot(1);
	glutSwapBuffers();
}

void init(void)
{
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0,
				   1.0,
				   1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		lookLeft();
		break;
	case GLUT_KEY_RIGHT:
		lookRight();
		break;
	case GLUT_KEY_UP:
		lookUp();
		break;
	case GLUT_KEY_DOWN:
		lookDown();
		break;
	}
	glutPostRedisplay();
}

void keyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'f':
		moveForward();
		break;
	case 'b':
		moveBackword();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Green 3D Teapot");
	glutKeyboardFunc(keyBoard);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
