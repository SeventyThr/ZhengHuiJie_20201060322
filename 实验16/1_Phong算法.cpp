#include <gl\glut.h>    
#include <gl\GLU.h>
#include <gl\GL.h>
#include <math.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926     
#define WIDTH 500 
#define HEIGHT 500 

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓冲  

    // 定义太阳光源，它是一种白色的光源  
    {
        GLfloat sun_light_position[] = { 0.0f, 0.0f, 100.0f, 1.0f }; // 光源的位置
        GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //指定第0号光源的位置   
        glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient); //GL_AMBIENT表示各种光线照射到该材质上，  
        //经过很多次反射后最终遗留在环境中的光线强度（颜色）  
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse); //漫反射后~~  
        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//镜面反射后~~~  

        glEnable(GL_LIGHT0); //使用第0号光照  
        glEnable(GL_LIGHTING); //在后面的渲染中使用光照  
        glEnable(GL_DEPTH_TEST); //这句是启用深度测试，这样，在后面的物体会被挡着，例如房子后面有棵树，如果不启用深度测试，  
        //你先画了房子再画树，树会覆盖房子的；但启用深度测试后无论你怎么画，树一定在房子后面（被房子挡着）   
    }

    glPushMatrix();
    // 定义一个球体 
    {
        GLfloat earth_mat_ambient[] = { 0.0f, 0.5f, 0.0f, 1.0f };
        GLfloat earth_mat_diffuse[] = { 0.0f, 0.5f, 0.0f, 1.0f }; // 浅绿色的球
        GLfloat earth_mat_specular[] = { 0.0f, 1.0f, 0.0f, 1.0f };
        GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat earth_mat_shininess = 110.0f; // 球体比较粗糙

        // GL_AMBIENT 材质的环境颜色 
        glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
        // GL_DIFFUSE 材质的散射颜色
        glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
        // GL_SPECULAR 材质的镜面反射颜色
        glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
        // GL_EMISSION 材质的发射光颜色
        glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
        // GL_SHININESS 镜面反射指数
        glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

        glTranslatef(0.0f, 0.0f, 0.0f);   // 平移

        glutSolidSphere(2.3, 40, 32);
    }
    glPopMatrix();

    glutSwapBuffers(); //交换缓冲区  
}

void Reshape(int w, int h)
{
    // //改变显示区域，起始位置为客户端窗口左下角（非坐标原点）
    glViewport(0, 0, 500,500);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //宽高比改为当前值，视线区域与屏幕大小一致；
    gluPerspective(20, 1.0, 1, 1000);
    // 开启更新深度缓冲区的功能
    glEnable(GL_DEPTH_TEST);
    // 摄像机视图观看
    gluLookAt(0.0, 0.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1000.0);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("光照明模型");

    glutReshapeFunc(&Reshape);
    glutDisplayFunc(&myDisplay);

    glutMainLoop();
    return 0;
}
