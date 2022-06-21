#include<Gl/glut.h>
#include <process.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;


class wcPt2D {
public:
    float x, y;
};

wcPt2D p1,p2;
double cd[8];

GLubyte encode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax);

void swapPts(wcPt2D* p1, wcPt2D* p2);

void swapCodes(GLubyte* c1, GLubyte* c2);

void lineClipCohSuth(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2);

void myKeyBoard(unsigned char key, int x, int y);

const GLint winLeftBitCode = 0x1;
const GLint winRightBitCode = 0x2;
const GLint winBottomBitCode = 0x4;
const GLint winTopBitCode = 0x8;

inline GLint inside(GLint code) {
    return GLint(!code);
}

inline GLint reject(GLint code1, GLint code2) {
    return GLint(code1 & code2);
}

inline GLint accept(GLint code1, GLint code2) {
    return GLint(!(code1 | code2));
}

GLubyte encode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax) {
    GLubyte code = 0x00;
    if (pt.x < winMin.x) code = code | winLeftBitCode;
    if (pt.x > winMax.x) code = code | winRightBitCode;
    if (pt.y < winMin.y) code = code | winBottomBitCode;
    if (pt.y > winMax.y) code = code | winTopBitCode;
    return (code);
}

void swapPts(wcPt2D* p1, wcPt2D* p2) {
    wcPt2D tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void swapCodes(GLubyte* c1, GLubyte* c2) {
    GLubyte tmp;
    tmp = *c1;
    *c1 = *c2;
    *c2 = tmp;
}

void lineClipCohSuth(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2) {
    GLubyte code1, code2;
    GLint done = false, plotLine = false;
    GLfloat m;
    while (!done) {
        code1 = encode(p1, winMin, winMax);
        code2 = encode(p2, winMin, winMax);
        if (accept(code1, code2)) {
            done = true;
            plotLine = true;
        }
        else if (reject(code1, code2)) {
            done = true;
        }
        else {
            if (inside(code1)) {
                swapPts(&p1, &p2);
                swapCodes(&code1, &code2);
            }
            if (p2.x != p1.x) m = (p2.y - p1.y) / (p2.x - p1.x);
            if (code1 & winLeftBitCode) {
                p1.y += (winMin.x - p1.x) * m;
                p1.x = winMin.x;
            }
            else if (code1 & winRightBitCode) {
                p1.y += (winMax.x - p1.x) * m;
                p1.x = winMax.x;
            }
            else if (code1 & winBottomBitCode) {
                if (p2.x != p1.x)
                    p1.x += (winMin.y - p1.y) / m;
                p1.y = winMin.y;
            }
            else if (code1 & winTopBitCode) {
                if (p2.x != p1.x)
                    p1.x = (winMax.y - p1.y) / m;
                p1.y = winMax.y;
            }
        }
    }
    if (plotLine)
        glBegin(GL_LINES);
    glLineWidth(10);
    glColor3f(1, 0, 0);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

void drawpolygon(double cd[]) {
    glBegin(GL_LINE_LOOP);
    glLineWidth(20);
    for (int i = 0; i < 8; i = i + 2) {
        glVertex2f(cd[i], cd[i + 1]);
    }
    glEnd();
}

void drawline(double cd[]) {
    glBegin(GL_LINES);
    glLineWidth(10);
    for (int i = 0; i < 8; i = i + 2) {
        glVertex2f(cd[i], cd[i + 1]);
    }
    glEnd();
}

void myKeyBoard(unsigned char key, int x, int y) {
    wcPt2D winMin = { 100, 100 };
    wcPt2D winMax = { 400, 400 };

    if (key == 13) {
        lineClipCohSuth(winMin, winMax, p1, p2);
    }
    glFlush();
    if (key == 27)
        exit(0);
}

void display(void) {
    cout << "Please input p1.x,p1.y,p2.x,p2.y:" << endl;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;

    double cd[8] = { 100, 100, 100, 400, 400, 400, 400, 100 };
    double line[4] = { p1.x ,p1.y, p2.x, p2.y };
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 500, 500);
    glColor3f(1, 0, 1);
    drawpolygon(cd);
    glColor3f(0, 1, 1);
    drawline(line);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland裁剪算法");
    glClearColor(1, 1, 1, 0.0);
    glMatrixMode(GL_PROJECTION);//投影模型
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glutKeyboardFunc(myKeyBoard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;

}
