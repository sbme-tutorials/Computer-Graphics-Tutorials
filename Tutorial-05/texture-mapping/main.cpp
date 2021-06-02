#include <math.h>
#include <GL/glut.h>
#include "imageloader.h"

#define PI 3.14

double eye[] = {0, 0, 3};
double center[] = {0, 0, 2};
double up[] = {0, 1, 0};

// RGBA
GLfloat light_ambient[] = {0.0, 0.0, 0.0, 0.0};
GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
// x , y, z, w
GLfloat light_position[] = {0.5, 5.0, 0.0, 1.0};
GLfloat lightPos1[] = {-0.5, -5.0, -2.0, 1.0};

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image *image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);			 //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,				  //Always GL_TEXTURE_2D
				 0,							  //0 for now
				 GL_RGB,					  //Format OpenGL uses for image
				 image->width, image->height, //Width and height
				 0,							  //The border of the image
				 GL_RGB,					  //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE,			  //GL_UNSIGNED_BYTE, because pixels are stored
											  //as unsigned numbers
				 image->pixels);			  //The actual pixel data
	return textureId;						  //Returns the id of the texture
}

GLuint _textureId; //The id of the texture

//Initializes 3D rendering
void initRendering()
{
	Image *image = loadBMP("images/wood.bmp");
	_textureId = loadTexture(image);
	delete image;
	// Turn on the power
	glEnable(GL_LIGHTING);
	// Flip light switch
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	// assign light parameters
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	// Material Properties
	GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
	glEnable(GL_NORMALIZE);
	//Enable smooth shading
	glShadeModel(GL_SMOOTH);
	// Enable Depth buffer
	glEnable(GL_DEPTH_TEST);
}

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
void turnLeft()
{
	double theta = -PI/100;
    rotatePoint(up, theta, eye);
}

void turnRight()
{
	double theta = PI/100;
    rotatePoint(up, theta, eye);
}

void moveUp()
{
	double horizontal [3];
    double look [] = {center[0] -eye[0], center[1] -eye[1], center[2] -eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, PI/100, eye);
    rotatePoint(horizontal, PI/100, up);
}


void moveDown()
{

	double horizontal [3];
    double look [] = {center[0] -eye[0], center[1] -eye[1], center[2] -eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, -PI/100, eye);
    rotatePoint(horizontal, -PI/100, up);
}

void moveForward()
{

	double speed = 0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	normalize(direction);

	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;
}

void moveBack()
{

	double speed = -0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	normalize(direction);

	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;
}

void display(void)
{

	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Clear Depth and Color buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, -1,  1);
	glTexCoord2f(3.0f, 0.0f); glVertex3f( 1, -1,  1);
	glTexCoord2f(3.0f, 3.0f); glVertex3f( 1, -1, -1);
	glTexCoord2f(0.0f, 3.0f); glVertex3f(-1, -1, -1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		turnLeft();
		break;
	case GLUT_KEY_RIGHT:
		turnRight();
		break;
	case GLUT_KEY_UP:
		if (center[1] <= 1.5)
			moveUp();
		break;
	case GLUT_KEY_DOWN:
		if (center[1] >= -1.5)
			moveDown();
		break;
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'f':
		moveForward();
		break;
	case 'b':
		moveBack();
		break;

	case 27:
		exit(0);
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
	glutCreateWindow("Floor");
	initRendering();
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, 1.0, 0.1, 10);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
