#include <string.h>     
#include <math.h>       
#include <stdio.h>       
#include <stdlib.h>       
#include <malloc.h>    
#include<Windows.h>

#define   WIDTHBYTES(bits) (((bits)+31)/32*4)//用于使图像宽度所占字节数为4byte的倍数    

#pragma warning(disable:4996)

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef long LONG;

//头文件

typedef struct tagBITMAPFILEHEADER {			
	//共14Byte 2+4+2+2+4

	WORD bType;			//文件类型，必须是0x42 (B,低字节), 0x4D (M,高字节) 0x4D42
	DWORD bfSize;		//文件大小
	WORD bfReserved1;	//保留字，不考虑？
	WORD bfReserved2;	//保留字，+1；
	DWORD bfOffBits;	//偏移量，本次使用的是54
}BITMAPFILEHEADER;

//位图信息头

typedef struct tagBITMAPINFOHEADER {
	//40Byte  4+4+4+2+2+4+4+4+4+4+4

	DWORD biSize;			//结构体tagBITMAPINFOHEADER所占字节数
	LONG biWidth;			//图像宽度 pixel
	LONG biHeight;			//高度 pixel
	WORD biPlanes;			//目标设备级别？===1
	WORD biBitCount;		//本次为24位真彩图
							//每个像素所需位数 
							// 1位 --黑白
							// 4、8、256
	DWORD biCompression;	//压缩类型 
							// 0 --不压缩
							// 1 --BI_RLE8
							// 2 --BI_RLE4
	DWORD biSizeImage;		//位图数据大小 biWidth * biHeight (biWidth补齐4的倍数)
	LONG biXPelsPerMeter;	//水平分辨率
	LONG biYPelsPermeter;	//垂直分辨率
	DWORD biClrUsed;		//实际使用颜色数
	DWORD biClrImportant;	//重要颜色数 0--all
}BITMAPINFOHEADER;
void main(){
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
	fread(&bitHead, 1, sizeof(tagBITMAPFILEHEADER), pfile);		//读取文件头
	fread(&bitInfoHead, 1, sizeof(BITMAPINFOHEADER), pfile);	//读取位图信息头信息

	int width = bitInfoHead.biWidth;							//行宽 pixel
	int height = bitInfoHead.biHeight;							//图高 pixel
	//分配内存空间把源图存入内存     
	int l_width = WIDTHBYTES(width* bitInfoHead.biBitCount);	//计算位图的实际宽度并确保它为4byte的倍数   

	BYTE *pColorData = (BYTE *)malloc(height*l_width);			//开辟内存空间存储图像数据  
	memset(pColorData, 0, height*l_width);						//用'0'初始化pColorData

	long nData = height*l_width;

	fread(pColorData, 1, nData, pfile);							//把位图数据读到一维数组中

	fclose(pfile);												//关闭文件流
	printf("read .bmp succeed\n");

	system("pause");
}