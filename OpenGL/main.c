#include <stdio.h>
#include <string.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

int screen_width = 500;
int screen_height = 500;


// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, ly = 0.0f, lz = 0.0f;
// XZ position of the camera
float x = 0.0f, y = 5.0f, z = 0.0f;

float up = 0.0f, front = 0.0f;

float speed = 0.5;
float VCspeed = 1.0;
float HCspeed = 1.0;

float aLx ,aLy,aLz;
GLfloat lightPosition[] = { 0.0 , 5.0 , 0.0 , 1.0 };
GLfloat lightPosition1[] = { 14.0 , 9.0 , 9.0 , 1.0 };
float sx = 5.0;
float delta = 0.1;



void init(void) {
	//Set background color
	glClearColor(0, 0, 0, 0);
	// Viewport size
	glViewport(0, 0, screen_width, screen_height);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(80.0, 1.0, 0.5, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	//Light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	GLfloat qaAmbientLight[] = { 0.2 , 0.2 ,0.2 ,1.0 };
	GLfloat qaDiffuseLight[] = { 1.8 , 1.8 ,1.8 ,1.0 };
	GLfloat qaSpecularLight[] = { 0.2 , 0.2 ,0.2 ,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);

	glMaterialf(GL_FRONT, GL_SHININESS, 64);
	//Position
	
	glLightfv(GL_LIGHT0, GL_POSITION , lightPosition);
	glLightfv(GL_LIGHT1, GL_POSITION , lightPosition1);
	glTranslatef(-x, -y, -z);

}
void drawWalls() {
	int wallHeight = 10;
	glColor3f(1.0, 0, 0);
	glBegin(GL_QUADS);
	//redwall
	glNormal3i(0, 0, 1);
	glVertex3i(-15, wallHeight, -10);
	glVertex3i(-15, 0, -10);
	glVertex3i(15, 0, -10);
	glVertex3i(15, wallHeight, -10);
	//yellowwall
	glNormal3i(0, 0, -1);
	glColor3f(1.0,1.0,0);
	glVertex3i(-15, wallHeight, 10);
	glVertex3i(-15, 0, 10);
	glVertex3i(15, 0, 10);
	glVertex3i(15, wallHeight, 10);
	//greenwall
	glNormal3i(1, 0, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3i(-15,wallHeight,10);
	glVertex3i(-15,0,10);
	glVertex3i(-15,0,-10);
	glVertex3i(-15,wallHeight,-10);
	//bluewall
	glNormal3i(-1, 0, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3i(15,wallHeight,10);
	glVertex3i(15,0,10);
	glVertex3i(15,0,-10);
	glVertex3i(15,wallHeight,-10);
	//top
	
	glNormal3i(0, -1, 0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3i(15,wallHeight,10);
	glVertex3i(15,wallHeight,-10);
	glVertex3i(-15,wallHeight,-10);
	glVertex3i(-15,wallHeight,10);

	//bottom
	glNormal3i(0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3i(15,0,10);
	glVertex3i(15,0,-10);
	glVertex3i(-15,0,-10);
	glVertex3i(-15,0,10);

	glEnd();

	glPushMatrix();

	glTranslatef(5, 2, sx);
	glColor3f(0.3, 0.5, 0.7);
	glutSolidSphere(2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6, 2, -2);
	glColor3f(0.2, 0.4, 0.1);
	glutSolidTeapot(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1.0, -9.0);
	glColor3f(0.5, 0.0, 0.5);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14.0, 9.0, 9.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(.5);
	glPopMatrix();
	glFlush();
	

}

void setCameraPosition() {
	float radian = front / 180 * 3.141592654;

	glLoadIdentity();

	glRotatef(front, 0, 1, 0);
	glRotatef(up, cos(radian), 0, sin(radian));
	glTranslatef(-x, -y, -z);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);

	printf("X: %f	Z: %f	Up: %f	Front: %f\n", x, z, up, front);



	glutPostRedisplay();

}

void rotateVertical(char dir) {
	if (dir == 'l') {
		front -= VCspeed;
	}
	else if (dir == 'r') {
		front += VCspeed;
		glLoadIdentity();
	}
	setCameraPosition();
}

void rotateHorizontal(char dir) {
	if (dir == 'd') {
		up -= HCspeed;
	}
	else if (dir == 'u') {
		up += HCspeed;
	}
	setCameraPosition();
}

void move(char dir) {
	float mx, mz;
	float radian = front / 180 * 3.141592654;

	if (dir == 'a') {
		mz = -sin(radian) * speed;
		mx = -cos(radian) * speed;
	}
	else if (dir == 's') {
		mz = cos(radian) * speed;
		mx = -sin(radian) * speed;
	}
	else if (dir == 'd') {
		mz = sin(radian) * speed;
		mx = cos(radian) * speed;
	}
	else if (dir == 'w') {
		mz = -cos(radian) * speed;
		mx = sin(radian) * speed;
	}
	x += mx;
	z += mz;

	glTranslated(-mx, 0, -mz);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	printf("X: %f	Z: %f	Up: %f	Front: %f\n", x, z, up, front);

	glutPostRedisplay();
}

void mouseMoveCallback(GLint x,GLint y) {
	if (x > screen_width/2)
		rotateVertical('r');
	else if (x < screen_width/2)
		rotateVertical('l');

	if (y < 250) 
		rotateHorizontal('d');
	else if (y > 250) 
		rotateHorizontal('u');
	

	glutWarpPointer(screen_height / 2, screen_width / 2);
}

void mouseCallback(GLint button, GLint state, GLint x, GLint y) {

}

void reshapeCallback(GLsizei w, GLsizei h) {
	// called when the window is resized
}

void dispCallback() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawWalls();


}

void keyCallback(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		move('a');
		break;
	case 's':
		move('s');
		break;
	case 'd':
		move('d');
		break;
	case 'w':
		move('w');
		break;
	case 'l':
		if (glIsEnabled(GL_LIGHT0)) 
			glDisable(GL_LIGHT0);
		else 
			glEnable(GL_LIGHT0);
		glutPostRedisplay();
		break;
	case 'm':
		if (glIsEnabled(GL_LIGHT1)) 
			glDisable(GL_LIGHT1);
		else 
			glEnable(GL_LIGHT1);
		glutPostRedisplay();
		break;
	case 'k':
		if (glIsEnabled(GL_LIGHTING)) 
			glDisable(GL_LIGHTING);
		else 
			glEnable(GL_LIGHTING);
		glutPostRedisplay();
		break;
	}
}

void timer() {
	if (sx > 8) 
		delta = -0.1;
	else if (sx < -8)
		delta = 0.1;
	sx += delta;
	glutPostRedisplay();
	glutTimerFunc(20, timer, 1);
}

void specCallback(int key, int x, int y) {

}

void redispCallback() {
		
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(screen_height, screen_width);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );

	glutCreateWindow("Project");
	glutMouseFunc(mouseCallback);
	glutPassiveMotionFunc(mouseMoveCallback);
	glutDisplayFunc(dispCallback);
	glutKeyboardFunc(keyCallback);
	glutSpecialFunc(specCallback);
	glutTimerFunc(50,timer,1);
	//glutReshapeFunc(reshapeCallback);
	
	init();

	glutMainLoop();




}