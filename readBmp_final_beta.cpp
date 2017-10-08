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
static GLint PixelLength_1;
static GLint PixelHeight;

void display() {				
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(ImageWidth, ImageHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);				//画图像
	//glDrawPixels(ImageHeight, ImageWidth, GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData_1);			//画旋转图像
	glutSwapBuffers();
}

void main(int argc, char *argv[]) {
	BITMAPFILEHEADER bitHead;
	BITMAPINFOHEADER bitInfoHead;
	FILE* pfile;
	FILE* wfile;			

	char strFile[50] = "G:\\images\\test.bmp";					//打开图像路径 
	char strFilesave[50] = "G:\\images\\test_save.bmp";			//存储路径
	pfile = fopen(strFile, "rb");								//文件打开图像  
	wfile = fopen(strFilesave, "wb");

									  
	WORD fileType;
	fread(&fileType, 1, sizeof(WORD), pfile);
	fwrite(&fileType, 1, sizeof(WORD), wfile);
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
	PixelHeight = ImageHeight * 3;
	while (PixelHeight % 4 != 0)
		++PixelHeight;
	GLint tempLength = PixelLength;
	PixelLength *= ImageHeight;

	
	PixelLength_1 = PixelHeight*ImageWidth;
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
	int m = 0;
	//二维数组中数据按90°转动后读出
	for (int j = 0; j <ImageWidth; j++) {
		for (int i = 0; i < ImageHeight; i++) {
			for (int n = 0, k = 0; n < 3; n++) {
				PixelData_1[m++] = marix[i][j*3+k];
				k++;
			}
		}
	}

	//临时矩阵
	GLubyte **marix_1 = new GLubyte *[ImageWidth];
	for (int i = 0; i < ImageWidth; i++) {
		marix_1[i] = new GLubyte[PixelHeight];
	}
	for (int i = 0; i < ImageWidth; i++) {
		for (int j = 0; j < PixelHeight; j++) {
			marix_1[i][j] = PixelData_1[i*PixelHeight + j];
		}
	}
	for (int i = 0; i < ImageWidth; i++) {
		for (int j = 0; j < PixelHeight; j++) {
			PixelData_1[i*PixelHeight + j] = marix_1[i][j];
		}
	}
		
	//四分之一矩阵
	GLubyte **marix_3 = new GLubyte *[ImageHeight/2];
	for (int i = 0; i < ImageHeight/2; i++) {
		marix_3[i] = new GLubyte[tempLength/2];
	}

	for (int i = 0; i < ImageHeight/2; i++) {
		for (int j = 0; j < tempLength/2; j++) {
			marix_3[i][j] = marix[i][j];
		}
	}
	for (int i = 0; i < ImageHeight / 2; i++) {
		for (int j = 0; j < tempLength / 2; j++) {
			marix[i][j] = marix[i+ ImageHeight / 2][j+ tempLength / 2];
		}
	}
	for (int i = ImageHeight / 2, m = 0; i < ImageHeight-1; i++, m++) {
		for (int j = tempLength / 2, n = 0; j < tempLength-1; j++, n++) {
			marix[i][j] = marix_3[m][n];
		}
	}
	for (int i = 0; i < ImageHeight; i++) {
		for (int j = 0; j < tempLength; j++) {
			PixelData[i*tempLength + j] = marix[i][j];
		}
	}
	//写入文件
	/*bitInfoHead.biWidth = ImageHeight;
	bitInfoHead.biHeight = ImageWidth;*/
	
	fwrite(&bitHead, 1, sizeof(tagBITMAPFILEHEADER), wfile);
	fwrite(&bitInfoHead, 1, sizeof(BITMAPINFOHEADER), wfile);
	fwrite(PixelData, 1, PixelLength, wfile);

	fclose(pfile);												//关闭文件流
	fclose(wfile);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(ImageWidth, ImageHeight);				//建立Windows框
	//glutInitWindowSize(ImageHeight, ImageWidth);				//建立旋转后的Windows框
	glutCreateWindow("显示.bmp");
	glutDisplayFunc(&display);									//调展示函数
	glutMainLoop();

	system("pause");
}