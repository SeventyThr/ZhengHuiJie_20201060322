#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;

inline int roound(const float a) { return int(a + 0.5); }

void setPixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void lineDDA() {
	int x0,y0,xEnd,yEnd;
	cout << "Please input x0,y0,xEnd,yEnd:" << endl;
	cin >> x0>>y0>>xEnd>>yEnd;
	int dx = xEnd - x0, dy = yEnd - y0, steps, k;
	float xIncrement, yIncrement, x = x0, y=y0;
	
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	xIncrement = float(dx) / float(steps);
	yIncrement = float(dy) / float(steps);

	setPixel(round(x), round(y));
	for (k = 0; k < steps; k++) {
		x += xIncrement;
		y += yIncrement;
		setPixel(round(x), round(y));
	}
}

void display(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	lineDDA();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);                         // 初始 GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //设定显示模式
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("lineDDA"); // 用前面指定参数创建窗口，并定义窗口名称
	glutDisplayFunc(display);       // 指定绘制的回调函数
	glColor3f(0.0, 1.0, 0.0);//颜色
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutMainLoop();
	return 0;
}
