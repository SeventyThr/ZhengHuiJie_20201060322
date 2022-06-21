#include <Windows.h>
#include <gl/glut.h>

GLfloat AngleX, AngleY;

void init()
{
	AngleX = 45.0f;
	AngleY = 315.0f;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	{
		glRotatef(AngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(AngleY, 0.0f, 1.0f, 0.0f);
		//绘制三维的正方体
		glBegin(GL_POLYGON);
		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
		glVertex3f(50.0f, -50.0f, 50.0f);

		glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
		glVertex3f(-50.0f, -50.0f, 50.0f);

		glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3d(0.0, 1.0, 1.0);
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3d(1.0, 1.0, 1.0);
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3d(1.0, 0.0, 1.0);
		glVertex3f(-50.0f, 50.0f, 50.0f);

		glColor3d(0.0, 0.0, 1.0);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3ub(0u, 255u, 0u);
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3ub(255u, 255u, 0u);
		glVertex3f(50.0f, -50.0f, 50.0f);

		glColor3ub(255u, 0u, 0u);
		glVertex3f(-50.0f, -50.0f, 50.0f);

		glColor3ub(255u, 255u, 255u);
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)255);
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
		glVertex3f(50.0f, -50.0f, 50.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-50.0f, 50.0f, 50.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);
		glEnd();
	}
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	GLfloat nRange = 100.0f;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	if (w <= h)
	{
		glOrtho(-nRange, nRange, -nRange * aspect, nRange * aspect, -nRange, nRange);
	}
	else
	{
		glOrtho(-nRange, nRange, -nRange / aspect, nRange / aspect, -nRange, nRange);
	}
}

void key_board(int key, int x, int y)
{
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);

	if (key == GLUT_KEY_UP)//按“上”，放大图形	
		glScalef(1.5, 1.5, 1.5);

	if (key == GLUT_KEY_DOWN)//按“下”，缩小图形
		glScalef(0.5, 0.5, 0.5);

	if (key == GLUT_KEY_LEFT)//按“左”，旋转图形
		glRotated(10, 0, 1, 0);

	if (key == GLUT_KEY_RIGHT)//按“右”，右移图形
		glTranslated(10, 0, 0);



	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(400, 400);
	glutCreateWindow("三维图形几何变换");
	glutReshapeFunc(reshape);
	//glutKeyboardFunc(key_board);
	glutSpecialFunc(key_board);
	glutDisplayFunc(display);

	init();
	glutMainLoop();
	return 0;
}
