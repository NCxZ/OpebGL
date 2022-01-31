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

int x_1 = -1;
int y_1 = -1;
int x_2 = -1;
int y_2 = -1;
int nPoints = 0;
int first = 1;
float cos5 = 0.996194698;
float sin5 = 0.087155742;
float cenx = 225;
float ceny = 225;
float M_PI = 3.1415;


float rect_points[8] = {
	150.0, 150.0,
	300.0, 150.0,
	300.0, 300.0,
	150.0, 300.0

};

void move(float amount, char axis) {
	if (axis == 'x') {

		rect_points[0] += amount;
		rect_points[2] += amount;
		rect_points[4] += amount;
		rect_points[6] += amount;
	}
	else if (axis == 'y') {
		rect_points[1] += amount;
		rect_points[3] += amount;
		rect_points[5] += amount;
		rect_points[7] += amount;

	}
	glutPostRedisplay();
}
void rotate() {

	for (int i = 0; i <= 7; i = i + 2)
	{
		rect_points[i] = cos5 * (rect_points[i] - cenx) - sin5 * (rect_points[i + 1] - ceny) + cenx;
		rect_points[i + 1] = sin5 * (rect_points[i] - cenx) + cos5 * (rect_points[i + 1] - ceny) + ceny;
	}
	glutPostRedisplay();
}

void drawLines() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(x_1, y_1, 5);
	glVertex3f(x_2, y_2, 10);
	glEnd();
	glFlush();
}



void init(void) {
	//Set background color
	glClearColor(0, 0, 0, 0);
	// Viewport size
	glViewport(0, 0, screen_width, screen_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0, 1.0, 2.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void mouseCallback(GLint button, GLint state, GLint x, GLint y) {
	y = screen_height - y;
	switch (button) { // b indicates the button
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {// button pressed
			nPoints = nPoints + 1;
			if (nPoints == 2) {
				first = 0;
				x_2 = x;
				y_2 = y;
				nPoints = 0;
			}
			else if (nPoints == 1) {
				x_1 = x;
				y_1 = y;
			}
			printf("%d: %d %d\n", nPoints, x_1, y_1);
		}
		else if (state == GLUT_UP) { // button released
			glutPostRedisplay();
			printf("Button up \n");
		}
		break;
	}
}

void reshapeCallback(GLsizei w, GLsizei h) {
	// called when the window is resized
}

void drawSphere(double r, int lats, int longs) {
	int i, j;
	for (i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(r * x * zr0, r * y * zr0, r * z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(r * x * zr1, r * y * zr1, r * z1);
		}
		glEnd();
	}
}

void dispCallback() {

	// FIRST DRAWING ON THE SCREEN
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	//drawSphere(5, 50, 50);

	if (nPoints != 1) {
		drawLines();
	}
	glLoadIdentity();
	glTranslatef(0, 0, -8);
	glutWireSphere(5, 36, 36);
	glFlush();


}

void keyCallback(unsigned char key, int x, int y) {
	switch (key)
			case 'r':
				rotate();

}

void specCallback(int key, int x, int y) {

	float amount = 5.0;

	switch (key) {
	case GLUT_KEY_UP:
		move(amount, 'y');
		break;
	case GLUT_KEY_DOWN:
		move(-amount, 'y');
		break;
	case GLUT_KEY_LEFT:
		move(-amount, 'x');
		break;
	case GLUT_KEY_RIGHT:
		move(amount, 'x');
		break;
	}
}

void redispCallback() {

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(screen_height, screen_width);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow("Assignment-1");
	glutMouseFunc(mouseCallback);
	//glutPassiveMotionFunc(mouseMoveCallback);
	glutDisplayFunc(dispCallback);
	glutKeyboardFunc(keyCallback);
	glutSpecialFunc(specCallback);
	//glutReshapeFunc(reshapeCallback);
	init();

	glutMainLoop();




}