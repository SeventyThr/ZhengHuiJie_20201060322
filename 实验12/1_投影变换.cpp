#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>
//摄像机离物体的距离
float G_fDistance = 3.6f;

void myinit(void);
void myReshape(GLsizei w, GLsizei h);
void display(void);

//主函数
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//初始化OPENGL显示方式
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//设定OPENGL窗口位置和大小
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	//打开窗口
	glutCreateWindow("利用OpenGL的多视区分别在4个视区内显示空间四面体的透视投影图、主视图、俯视图、侧视图");
	//调用初始化函数
	myinit();
	//设定窗口大小变化的回调函数
	glutReshapeFunc(myReshape);
	//开始OPENGL的循环
	glutDisplayFunc(display);
	//	glutIdleFunc(timer);
	glutMainLoop();
	return 0;
}


//用户初始化函数
void myinit(void)
{
}
//窗口大小变化时的回调函数
void myReshape(GLsizei w, GLsizei h)
{
	//设定透视方式
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(-5.0,-5.0,5.0,5.0);
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 30.0);
}
void LookAt(int direction)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -G_fDistance);
	if (direction == 1) {//主视图观察方向
	}
	else if (direction == 2) {//侧视图观察方向
		gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
	}
	else if (direction == 3) {//俯视图观察方向
		gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		glRotatef(180.0, 0.0, 1.0, 0.0);
	}
	else if (direction == 4) {//透视投影观察方向
	}
	glutWireTeapot(1.0);
}
//每桢OpenGL都会调用这个函数，用户应该把显示代码放在这个函数中
void display(void)
{
	//设置清除屏幕的颜色，并清除屏幕和深度缓冲
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//设定主视图视区1
	glViewport(0, 0, 200, 200);
	LookAt(1);
	//设定侧视图视区2
	glViewport(200, 0, 200, 200);
	LookAt(2);
	//设定俯视图视区3
	glViewport(0, 200, 200, 200);
	LookAt(3);
	//设定透视投影图视区4
	glViewport(200, 200, 200, 200);
	LookAt(4);
	//交换前后缓冲区
	glutSwapBuffers();
}
