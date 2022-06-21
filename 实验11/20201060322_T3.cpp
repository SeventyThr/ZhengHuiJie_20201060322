#include <GL/glut.h>  
#include <math.h>
#define DEG_TO_RAD 0.017453  //角度转为弧度的参数，即 2*PI/360

float theta = 30.0; //直线与X轴正方向的夹角
float length = 200.0;  //直线的长度
float x = 300.0, y = 200.0; //直线的第一个端点

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + length * cos(DEG_TO_RAD * theta),
        y + length * sin(DEG_TO_RAD * theta));
    glVertex2f(x + length * cos(DEG_TO_RAD * (theta + 30)),
        y + length * sin(DEG_TO_RAD * (theta + 30)));
    glEnd();
    glFlush();
}

void mySpecialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_F1 || key == GLUT_KEY_LEFT)
        theta += 5.0;
    x += 100;
    if (key == GLUT_KEY_F2 || key == GLUT_KEY_RIGHT)
        theta -= 5.0;
    if (theta > 360) theta -= 360;
    if (theta < 0) theta += 360;
    glutPostRedisplay(); //重新调用绘制函数
}


void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Draw Triangle with Single Buffer");

    init();
    glutDisplayFunc(display);
    glutSpecialFunc(mySpecialKeyboard);
    glutMainLoop();
}
