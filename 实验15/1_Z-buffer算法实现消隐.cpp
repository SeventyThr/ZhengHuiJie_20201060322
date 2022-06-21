#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <graphics.h>
#include <math.h>
#define PI 3.1415926535
#define x0 200
#define y0 200  //画面的大小

void z_Buffer(int x1, int x2, int y1, int y2, int x11, int x22, int y11, int y22) { //定义z_Buffer算法

	int a = 3, b = 3, c = 4, d = 2;//Pk的平面方程的参数
	int depth;//深度
	double MinValue = -1000000000;//深度缓存变量的最小值
	int i, j, k;//后面FOR循环会用到的
	int zb;	//深度缓存变量
	int indexp;//多边形序号

	for (i = 0; i <= 640; i++)
	{
		for (j = 0; j <= 480; j++)  //逐个扫描像素点(i,j)
		{
			zb = MinValue;//把MinValue给了zb
			for (k = 0; k <= 1; k++)//每个多边形Pk
			{
				if ((i >= x1 && i <= x2 && j >= y1 && j <= y2) || (i >= x11 && i <= x22 && j >= y11 && j <= y22))//像素点在Pk的投影多边形之内
				{
					depth = -(a * i + b * j + d) / c;//Pk在(i,j)处的depth
					if (depth > zb)  //当深度值大于深度缓存变量的时候，前面
					{
						zb = depth;
						indexp = k; //记录序号
					}
				}
			}
			if (zb != MinValue) //验证测试
			{
				printf("%d,%d\n", i, j);
				//计算多边形P(indexp)在（i,j）处的光照颜色并显示
				if (indexp = 0 && (i >= x1 && i <= x2 && j >= y1 && j <= y2) || (i >= x11 && i <= x22 && j >= y11 && j <= y22)) {
					putpixel(i, j, RED);
				}
				else if (indexp = 1 && (i >= x1 && i <= x2 && j >= y1 && j <= y2) || (i >= x11 && i <= x22 && j >= y11 && j <= y22)) {
					putpixel(i, j, BLUE);
				}
			}
		}
	}
}
int main()
{
	initgraph(x0 * 2, y0 * 2);//初始化
	setbkcolor(WHITE);
	cleardevice();
	setcolor(BLACK);

	z_Buffer(50, 130, 80, 250, 70, 200, 100, 230);
	_getch();
	closegraph();
	return 0;
}
