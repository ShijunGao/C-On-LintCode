#include <string.h>     
#include <math.h>       
#include <stdio.h>       
#include <stdlib.h>       
#include <malloc.h>    
#include<Windows.h>

#define   WIDTHBYTES(bits) (((bits)+31)/32*4)//����ʹͼ������ռ�ֽ���Ϊ4byte�ı���    

#pragma warning(disable:4996)

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef long LONG;

//ͷ�ļ�

typedef struct tagBITMAPFILEHEADER {			
	//��14Byte 2+4+2+2+4

	WORD bType;			//�ļ����ͣ�������0x42 (B,���ֽ�), 0x4D (M,���ֽ�) 0x4D42
	DWORD bfSize;		//�ļ���С
	WORD bfReserved1;	//�����֣������ǣ�
	WORD bfReserved2;	//�����֣�+1��
	DWORD bfOffBits;	//ƫ����������ʹ�õ���54
}BITMAPFILEHEADER;

//λͼ��Ϣͷ

typedef struct tagBITMAPINFOHEADER {
	//40Byte  4+4+4+2+2+4+4+4+4+4+4

	DWORD biSize;			//�ṹ��tagBITMAPINFOHEADER��ռ�ֽ���
	LONG biWidth;			//ͼ���� pixel
	LONG biHeight;			//�߶� pixel
	WORD biPlanes;			//Ŀ���豸����===1
	WORD biBitCount;		//����Ϊ24λ���ͼ
							//ÿ����������λ�� 
							// 1λ --�ڰ�
							// 4��8��256
	DWORD biCompression;	//ѹ������ 
							// 0 --��ѹ��
							// 1 --BI_RLE8
							// 2 --BI_RLE4
	DWORD biSizeImage;		//λͼ���ݴ�С biWidth * biHeight (biWidth����4�ı���)
	LONG biXPelsPerMeter;	//ˮƽ�ֱ���
	LONG biYPelsPermeter;	//��ֱ�ֱ���
	DWORD biClrUsed;		//ʵ��ʹ����ɫ��
	DWORD biClrImportant;	//��Ҫ��ɫ�� 0--all
}BITMAPINFOHEADER;
void main(){
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
	fread(&bitHead, 1, sizeof(tagBITMAPFILEHEADER), pfile);		//��ȡ�ļ�ͷ
	fread(&bitInfoHead, 1, sizeof(BITMAPINFOHEADER), pfile);	//��ȡλͼ��Ϣͷ��Ϣ

	int width = bitInfoHead.biWidth;							//�п� pixel
	int height = bitInfoHead.biHeight;							//ͼ�� pixel
	//�����ڴ�ռ��Դͼ�����ڴ�     
	int l_width = WIDTHBYTES(width* bitInfoHead.biBitCount);	//����λͼ��ʵ�ʿ�Ȳ�ȷ����Ϊ4byte�ı���   

	BYTE *pColorData = (BYTE *)malloc(height*l_width);			//�����ڴ�ռ�洢ͼ������  
	memset(pColorData, 0, height*l_width);						//��'0'��ʼ��pColorData

	long nData = height*l_width;

	fread(pColorData, 1, nData, pfile);							//��λͼ���ݶ���һά������

	fclose(pfile);												//�ر��ļ���
	printf("read .bmp succeed\n");

	system("pause");
}