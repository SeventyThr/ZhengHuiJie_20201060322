#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;


class screenPt
{
private:
	GLint x, y;
public:
	screenPt(){
		x = y = 0;
	}
	void setCoords(GLint xCoordValue, GLint yCoordValue) {
		x = xCoordValue;
		y = yCoordValue;
	}
	GLint getx() const {
		return x;
	}
	GLint gety() const {
		return y;
	}
	void incrementx() {
		x++;
	}
	void decrementy() {
		y--;
	}
};


void setPixel(GLint xCoord, GLint yCoord) {
	glBegin(GL_POINTS);
	glVertex2i(xCoord, yCoord);
	glEnd();
}

void circleMidpoint() {
	GLint xc,yc,radius;
	cout<< "Please input xc,yc,radius:" << endl;
	cin >> xc >> yc >> radius;
	screenPt circPt;
	GLint p = 1 - radius;
	circPt.setCoords(0, radius);
	void circlePlotPoints(GLint, GLint, screenPt);
	circlePlotPoints(xc, yc, circPt);
	while (circPt.getx() < circPt.gety()) {
		circPt.incrementx();
		if (p < 0)
			p += 2 * circPt.getx() + 1;
		else {
			circPt.decrementy();
			p += 2 * (circPt.getx() - circPt.gety()) + 1;
		}
		circlePlotPoints(xc, yc, circPt);
	}
}

void circlePlotPoints(GLint xc, GLint yc, screenPt circPt) {
	setPixel(xc + circPt.getx(), yc + circPt.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety());
	setPixel(xc + circPt.gety(), yc + circPt.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx());
}

void display(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	circleMidpoint();
	glFlush();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);                         // 初始 GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //设定显示模式
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("circleMidpoint"); // 用前面指定参数创建窗口，并定义窗口名称
	glutDisplayFunc(display);       // 指定绘制的回调函数
	glColor3f(0.0, 1.0, 0.0);//颜色
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutMainLoop();
	return 0;
}
