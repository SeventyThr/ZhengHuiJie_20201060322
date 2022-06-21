#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;

void setPixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void lineBres() {
	int x0, y0, xEnd, yEnd;
	cout << "Please input x0,y0,xEnd,yEnd:" << endl;
	cin >> x0 >> y0 >> xEnd >> yEnd;
	int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
	int p = 2 * dy - dx;
	int twoy = 2 * dy, twox = 2 * (dy - dx);
	int x, y;
	if (x0 > xEnd) {
		x = xEnd; y = yEnd; xEnd = x0;
	}
	else {
		x = x0; y = y0;
	}
	setPixel(x, y);
	while (x< xEnd) {
		x++;
		if (p < 0)
			p += twoy;
		else {
			y++;
			p += twox;
		}
		setPixel(x, y);
	}
}

void display(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	lineBres();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);                         // 初始 GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //设定显示模式
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("lineBres"); // 用前面指定参数创建窗口，并定义窗口名称
	glutDisplayFunc(display);       // 指定绘制的回调函数
	glColor3f(0.0, 0.0, 1.0);//颜色
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutMainLoop();
	return 0;
}
