#include <string.h>     
#include <math.h>       
#include <stdio.h>       
#include <stdlib.h>       
#include <malloc.h>    
#include<Windows.h>
#include<GL/glut.h>
#include<iostream>

using namespace std;


#pragma warning(disable:4996)

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef long LONG;

static GLint ImageWidth;
static GLint ImageHeight;
static GLubyte * PixelData;
static GLubyte * PixelData_1;
static GLint PixelLength;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glDrawPixels(ImageWidth, ImageHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
	glDrawPixels(ImageHeight, ImageWidth, GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData_1);
	glutSwapBuffers();
}

void main(int argc, char *argv[]) {
	BITMAPFILEHEADER bitHead;
	BITMAPINFOHEADER bitInfoHead;
	FILE* pfile;

	char strFile[50] = "G:\\images\\test.bmp";	//打开图像路径，需修改为自己图像存储的路径  
	pfile = fopen(strFile, "rb");				//文件打开图像  

									  
	WORD fileType;
	fread(&fileType, 1, sizeof(WORD), pfile);
	if (fileType != 0x4d42)						//判断是否为bmp文件
	{
		printf("file is not .bmp file!");
		return;
	}

	fseek(pfile, 0x0012, SEEK_SET);
	fread(&ImageWidth, sizeof(ImageWidth), 1, pfile);			//四个字节
	fread(&ImageHeight, sizeof(ImageHeight), 1, pfile);

	PixelLength = ImageWidth * 3;								//调整为四的倍数
	while (PixelLength % 4 != 0)
		++PixelLength;
	GLint tempLength = PixelLength;
	PixelLength *= ImageHeight;

	// 读取像素数据
	PixelData = (GLubyte*)malloc(PixelLength);
	PixelData_1 = (GLubyte*)malloc(PixelLength);
	if (PixelData == 0)
		exit(0);

	fseek(pfile, 54, SEEK_SET);
	fread(PixelData, PixelLength, 1, pfile);

	//读取的数据放入二维数组
	GLubyte **marix = new GLubyte *[ImageHeight];
	for (int i = 0; i < ImageHeight; i++) {
		marix[i] = new GLubyte[tempLength];
	}
	for (int i = 0; i < ImageHeight; i++) {
		for (int j = 0; j < tempLength; j++) {
			marix[i][j] = PixelData[i*tempLength + j];
		}
	}
	//二维数组中数据按90°转动后读出
	for (int j = 0; j < tempLength; j++) {
		for (int i = ImageHeight - 1; i > -1; i--) {
			PixelData_1[j*ImageHeight + ImageHeight-i-1] = marix[i][j];
		}
	}
	////读出的数据放如临时数组中
	//GLubyte **marix_1 = new GLubyte *[tempLength];
	//for (int i = 0; i < tempLength; i++) {
	//	marix_1[i] = new GLubyte[ImageHeight];
	//}
	//for (int i = 0; i < tempLength; i++) {
	//	for (int j = 0; j < ImageHeight; j++) {
	//		marix_1[i][j] = marix[][];
	//	}
	//}


	fclose(pfile);												//关闭文件流

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	//glutInitWindowSize(ImageWidth, ImageHeight);
	glutInitWindowSize(ImageHeight, ImageWidth);
	glutCreateWindow("显示bmp");
	glutDisplayFunc(&display);
	glutMainLoop();

	printf("read .bmp succeed\n");

	system("pause");
}