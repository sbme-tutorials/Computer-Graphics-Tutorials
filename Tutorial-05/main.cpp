#include <math.h>
#include <GL/glut.h>
#include "glm.h"
#include "imageloader.h"

int windowWidth = 1024;
int windowHeight = 768;
float aspect = float(windowWidth) / float(windowHeight);

float DRot = 90;
float Zmax, Zmin;
GLMmodel* pmodel;
float VRot =0.0;

GLMmodel* pmodel1;
GLMmodel* pmodel2 = glmReadOBJ("data/flowers.obj");
GLMmodel* pmodel3 = glmReadOBJ("data/rose+vase.obj");
GLMmodel* pmodel4 = glmReadOBJ("data/al.obj");
double eye[] = { 0, 0, 0 };
double center[] = { 0, 0, -1 };
double up[] = { 0, 1, 0 };
// RGBA
GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5,1.0 };
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0 };
// x , y, z, w
GLfloat light_position[] = {0.5,5.0, 0.0, 1.0 };
GLfloat lightPos1[] = {-0.5,-5.0,-2.0, 1.0 };
// Material Properties
GLfloat mat_amb_diff[] = {0.643, 0.753, 0.934, 1.0 };
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess[] = {100.0 };  
//left teapot specular
GLfloat teapotl_diff[] = { 0.0,0.0, 1.0, 1.0 };
GLfloat teapotl_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat teapotl_shininess[] = {10.0 };  
//middle teapot diffuse
GLfloat teapotm_diff[] = { 1.0, 0, 0.0, 1.0 };
GLfloat teapotm_specular[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat teapotm_shininess[] = {1.0 };  
//right teapot glosy
GLfloat teapotr_diff[] = { 1.0, .0, 0.0, 1.0 };
GLfloat teapotr_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat teapotr_shininess[] = {1000.0 };  
//cube
GLfloat cube_diff[] = {1.0,0.0, 0.0, 1.0 };
GLfloat cube_specular[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat cube_shininess[] = {10.0 }; 
//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
      GLuint textureId;
      glGenTextures(1, &textureId); //Make room for our texture
      glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
      //Map the image to the texture
      glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                               0,                            //0 for now
                               GL_RGB,                       //Format OpenGL uses for image
                               image->width, image->height,  //Width and height
                               0,                            //The border of the image
                               GL_RGB, //GL_RGB, because pixels are stored in RGB format
                               GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                                 //as unsigned numbers
                               image->pixels);               //The actual pixel data
      return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
GLuint _textureId1; //The id of the texture


void drawmodel(void)
{
		glmUnitize(pmodel1);
		glmFacetNormals(pmodel1);
		glmVertexNormals(pmodel1, 90.0);
		glmScale(pmodel1, .15);
		glmDraw(pmodel1, GLM_SMOOTH | GLM_MATERIAL);
}

GLuint startList;

//Initializes 3D rendering
void initRendering() {
     	 Image* image = loadBMP("floor.bmp");
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
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	GLfloat lightColor1[] = {1.0f, 1.0f,  1.0f, 1.0f };
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
        glEnable(GL_NORMALIZE);
        //Enable smooth shading
        glShadeModel(GL_SMOOTH);
        // Enable Depth buffer
        glEnable(GL_DEPTH_TEST);

    //     	startList = glGenLists(4);
	// glNewList(startList, GL_COMPILE);
	// glRotatef(90, 0, 1, 0);
    // 	glScalef(1, 1.2, 1);
    // 	glTranslatef(1.7, -0.05, -.3);
	// pmodel1 = pmodel4;
	// drawmodel();
	// glEndList();
	
	// glNewList(startList + 1, GL_COMPILE);
	// 	glRotatef(270, 0, 1, 0);
    // 	glScalef(1, 1.2, 1);
    // 	glTranslatef(-1.7, -0.05, -.3);
	// pmodel1 = pmodel4;
	// drawmodel();
	// glEndList();

	// glNewList(startList + 2, GL_COMPILE);
	// glTranslatef(0.3, -.1, 0.075);
	// pmodel1 = pmodel2;
	// drawmodel();
	// glEndList();

	// glNewList(startList + 3, GL_COMPILE);
	// glTranslatef(-0.6, 0, 0.0);
	// pmodel1 = pmodel2;
	// drawmodel();	
	// glEndList();


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

	temp[0] += (1 - cos(theta))*(a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta))*(a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta))*(a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta)*p[0];
	temp[1] += cos(theta)*p[1];
	temp[2] += cos(theta)*p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];

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
	double speed = 3.1415 / 100;
	double direction[] = { 0, 1, 0 };
	rotatePoint(direction, speed, center);


}

void turnRight()
{
	double speed = -3.1415 / 100;
	double direction[] = { 0, 1, 0 };
	rotatePoint(direction, speed, center);



}

void moveUp()
{
	double speed = 0.01;
	center[1] += speed;
}

void moveDown()
{

	double speed = -0.01;
	center[1] += speed;

}

void moveForward()
{


	double speed = .01;
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

	double speed = -0.01;
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

void
screen_menu(int value)
{
	char* name = 0;

	switch (value) {
	case 'a':
		name = "data/al.obj";
		break;
	case 's':
		name = "data/soccerball.obj";
		break;
	case 'd':
		name = "data/dolphins.obj";
		break;
	case 'f':
		name = "data/flowers.obj";
		break;
	case 'j':
		name = "data/f-16.obj";
		break;
	case 'p':
		name = "data/porsche.obj";
		break;
	case 'r':
		name = "data/rose+vase.obj";
		break;
	case 'D':
		name = "data/dragon-fixed.obj";
		break;
	}

	if (name) {
		pmodel = glmReadOBJ(name);
		if (!pmodel) exit(0);
		glmUnitize(pmodel);
		glmFacetNormals(pmodel);
		glmVertexNormals(pmodel, 90.0);
		glmScale(pmodel, .15);
	}

	glutPostRedisplay();
}


void drawmodel1(void)
{
	if (!pmodel) {
		pmodel = glmReadOBJ("data/rose+vase.obj");

		if (!pmodel) exit(0);
		glmUnitize(pmodel);
		glmFacetNormals(pmodel);
		glmVertexNormals(pmodel, 90.0);
		glmScale(pmodel, .15);
	}
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
}


void display(void)
{


	glClearColor(0.0, 0.0, 0.0, 0.0);
        // Clear Depth and Color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

        glPushMatrix();
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glPopMatrix();
        //materials properties
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glPushMatrix();
	glTranslatef(0, 0, -1);

	//floor
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBegin(GL_QUADS);
       
	glNormal3f(0.0,-1.0,0.0);
	glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.5,-0.25,2);
        glTexCoord2f(5.0f,  0.0f);
        glVertex3f(0.5,-0.25,2);
        glTexCoord2f(5.0f,  20.0f);
        glVertex3f(0.5,-0.25,-2);
        glTexCoord2f(0.0f, 20.0f);
        glVertex3f(-0.5,-0.25,-2);
        glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

    glPushMatrix();
    	glTranslatef(0.0, 0.015, -1.6);
    	glRotatef(VRot,0,1,0);
    	// glScalef(.25, .25, .25);
    	drawmodel1();
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void Timer(int x){
	// Refresh and redraw
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 0);
}
void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: turnLeft(); break;
	case GLUT_KEY_RIGHT: turnRight(); break;
	case GLUT_KEY_UP:
		if (center[1] <= 1.5)
			moveUp();
		break;
	case GLUT_KEY_DOWN:
		if (center[1] >= -1.5)
			moveDown();
		break;
	}

}
void correct()
{
	double speed = 0.001;
	if (eye[0]>0)
	{
		eye[0] -= speed;
		center[0] -= speed;
	}
	else
	{
		eye[0] += speed;
		center[0] += speed;
	}

	if (DRot == 0)
	{
		if ((eye[2] >= -1.2 && eye[2] <= -1) || eye[2]>0)
		{
			eye[2] -= speed;
			center[2] -= speed;
		}
		else
		{
			eye[2] += speed;
			center[2] += speed;
		}
	}
	else
	{
		if (eye[2]>0)
		{
			eye[2] -= speed;
			center[2] -= speed;
		}
		else
		{
			eye[2] += speed;
			center[2] += speed;
		}
	}

}
void SetBound()
{
	if (DRot == 0 || eye[0]> 0.15 || eye[0]< -0.15)
	{
		if (eye[2] >= -1)
		{
			Zmax = 0.7;
			Zmin = -0.8;
		}
		else
		{
			Zmax = -1.2;
			Zmin = -2.4;
		}
	}
	else
	{
		Zmax = 0.7;
		Zmin = -2.4;
	}
}
void Timer1(int x){
    // Refresh and redraw
    VRot += 5;
    if (VRot == 360)
        VRot=0;
    glutPostRedisplay();
    glutTimerFunc(50, Timer1, 0);
}

void DTimer1(int x){

	DRot -= 1;
	if (DRot == 0)
		return;
	glutPostRedisplay();
	glutTimerFunc(30, DTimer1, 0);


}

void DTimer2(int x){
	DRot += 1;
	if (DRot == 90)
		return;
	glutPostRedisplay();
	glutTimerFunc(30, DTimer2, 0);
}

void Keyboard(unsigned char Key, int x, int y){
	switch (Key)
	{
	case 'f':
		SetBound();
		if (eye[0]<0.25 && eye[0]>-0.25 && eye[2]<Zmax && eye[2]>Zmin)
			moveForward();
		else
			correct();
		break;
	case 'b':
		SetBound();
		if (eye[0]<0.25 && eye[0]>-0.25 && eye[2]<Zmax && eye[2]>Zmin)
			moveBack();
		else
			correct();

		break;
	case 27:
		exit(0);

		break;
	case ' ':
		if (DRot == 0 || DRot == 90)
		{
			if (DRot)
				DTimer1(0);
			else
				DTimer2(0);
		}
		break;
	default:
		break;
	}
}

int main (int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("ROOM");
	initRendering();

	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, aspect, 0.1, 10);



	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(Keyboard);
	Timer(0);

	glutCreateMenu(screen_menu);
	glutAddMenuEntry("Models", 0);
	glutAddMenuEntry("", 0);
	glutAddMenuEntry("Soccerball", 's');
	glutAddMenuEntry("Al Capone", 'a');
	glutAddMenuEntry("F-16 Jet", 'j');
	glutAddMenuEntry("Dolphins", 'd');
	glutAddMenuEntry("Flowers", 'f');
	glutAddMenuEntry("Porsche", 'p');
	glutAddMenuEntry("Rose", 'r');
	glutAddMenuEntry("Dragon", 'D');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutTimerFunc(0,Timer1,0);
	glutMainLoop();
	return 0;

}
