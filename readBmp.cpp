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
static GLint PixelLength;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(ImageWidth, ImageHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
	glutSwapBuffers();
}

void main(int argc, char *argv[]) {
	BITMAPFILEHEADER bitHead;
	BITMAPINFOHEADER bitInfoHead;
	FILE* pfile;

	char strFile[50] = "G:\\images\\test.bmp";	//��ͼ��·�������޸�Ϊ�Լ�ͼ��洢��·��  
	pfile = fopen(strFile, "rb");				//�ļ���ͼ��  

									  
	WORD fileType;
	fread(&fileType, 1, sizeof(WORD), pfile);
	if (fileType != 0x4d42)						//�ж��Ƿ�Ϊbmp�ļ�
	{
		printf("file is not .bmp file!");
		return;
	}

	fseek(pfile, 0x0012, SEEK_SET);
	fread(&ImageWidth, sizeof(ImageWidth), 1, pfile);
	fread(&ImageHeight, sizeof(ImageHeight), 1, pfile);

	// �����������ݳ���
	PixelLength = ImageWidth * 3;
	while (PixelLength % 4 != 0)
		++PixelLength;
	PixelLength *= ImageHeight;

	// ��ȡ��������
	PixelData = (GLubyte*)malloc(PixelLength);
	if (PixelData == 0)
		exit(0);

	fseek(pfile, 54, SEEK_SET);
	fread(PixelData, PixelLength, 1, pfile);


	fclose(pfile);												//�ر��ļ���

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ImageWidth, ImageHeight);
	glutCreateWindow("��ʾbmp");
	glutDisplayFunc(&display);
	glutMainLoop();

	printf("read .bmp succeed\n");

	system("pause");
}