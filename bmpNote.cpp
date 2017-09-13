

typedef unsigned char BYTE;   
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

//	//从左到右，从下到上扫描
//BITMAPFILEHEADER:
//	14 Byte;
//BITMAPINFORMATION:
//	40 Byte;
//	//24位真彩色图BMP没有调色板
//	//位图数据
//	//像素 BGR


typedef struct tagBITMAPFILEHEADER{
	//共14Byte 2+4+2+2+4

	WORD bType;			//文件类型，必须是0x42 (B,低字节), 0x4D (M,高字节) 0x4D42
	DWORD bfSize;		//文件大小
	WORD bfReserved1;	//保留字，不考虑？
	WORD bfReserved2;	//保留字，+1；
	DWORD bfOffBits;	//偏移量，本次使用的是54
}BITMAPFILEHEADER;

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


//学习
void *memset(void *s, int ch, size_t  n)
//将s中的前n个字节用ch替换并且返回s
//头文件 #include<string.h> or <memory.h>
