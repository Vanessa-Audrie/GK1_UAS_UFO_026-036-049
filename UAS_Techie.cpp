// Pertemuan7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glut.h>
#include <math.h>

float
fx = 2.5, fy = 2, fz = 1.5,
tx = 0, ty = 0, tz = 0,
yp = 0;

void cameraLook()
{
	gluLookAt(fx, fy, fz,
		tx, ty, tz,
		0, 1, 0
	);

	GLfloat light_position[] = { 0, 50, 100, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

void draw()
{
	glPushMatrix();
	glColor3f(0.3f, 0.7f, 0.9f);
	glScalef(1.0f, 0.3f, 1.0f);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9f, 0.9f, 0.1f);
	glTranslatef(0.0f, 0.5f, 0.0f);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	for (int i = 0; i < 360; i += 45) {
		glPushMatrix();
		float rad = i * 3.14 / 180.0f;
		float distance = 0.8f;
		glColor3f(1.0f, 0.1f, 0.1f);
		glTranslatef(distance * cos(rad), 0.2f, distance * sin(rad));
		glutSolidSphere(0.1, 20, 20);
		glPopMatrix();
	}

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 1.0f, 0.3f, 0.5f);
	glTranslatef(0.0f, -1.5f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glutSolidCone(1.0, 2.0, 50, 50);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	cameraLook();
	draw();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, (GLsizei)w / (GLsizei)h, 1, 300);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int value)
{
	yp += 10;
	if (yp >= 360)
	{
		yp = 0;
	}
	glutPostRedisplay();
	glutTimerFunc(100, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w':
		fy += 2;
		break;
	case 'S':
	case 's':
		fy -= 2;
		break;
	case 'A':
	case 'a':
		fx -= 2;
		break;
	case 'D':
	case 'd':
		fx += 2;
		break;
	case 'O':
	case 'o':
		fz -= 2;
		break;
	case 'L':
	case 'l':
		fz += 2;
		break;
	}
}

void specialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		ty += 2;
		break;
	case GLUT_KEY_DOWN:
		ty -= 2;
		break;
	case GLUT_KEY_LEFT:
		tx -= 2;
		break;
	case GLUT_KEY_RIGHT:
		tx += 2;
		break;
	case GLUT_KEY_PAGE_UP:
		tz -= 2;
		break;
	case GLUT_KEY_PAGE_DOWN:
		tz += 2;
		break;
	}
}

int main()
{
	glutInit(&__argc, __argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("UAS Techie");
	glOrtho(-2, 2, -2, 2, -2, 2);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKey);
	glutTimerFunc(1, timer, 0);
	glutMainLoop();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
