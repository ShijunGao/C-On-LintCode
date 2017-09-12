

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

//	//从左到右，从下到上扫描
//BITMAPFILEHEADER:
//	14 Byte;
//BITMAPINFORMATION:
//	40 Byte;
//	//24位真彩色图BMP没有调色板
//	//位图数据



typedef struct tagBITMAPFILEHEADER{
	WORD bType;			//文件类型，必须是0x42 (B,低字节), 0x4D (M,高字节) 0x4D42
	DWORD bfSize;		//文件大小
	WORD bfReserved1;	//保留字，不考虑？
	WORD bfReserved2;	//保留字，+1；
	DWORD bfOffBits;	//偏移量，本次使用的是
};
