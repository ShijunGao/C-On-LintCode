

typedef unsigned char BYTE;   
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

//	//�����ң����µ���ɨ��
//BITMAPFILEHEADER:
//	14 Byte;
//BITMAPINFORMATION:
//	40 Byte;
//	//24λ���ɫͼBMPû�е�ɫ��
//	//λͼ����
//	//���� BGR


typedef struct tagBITMAPFILEHEADER{
	//��14Byte 2+4+2+2+4

	WORD bType;			//�ļ����ͣ�������0x42 (B,���ֽ�), 0x4D (M,���ֽ�) 0x4D42
	DWORD bfSize;		//�ļ���С
	WORD bfReserved1;	//�����֣������ǣ�
	WORD bfReserved2;	//�����֣�+1��
	DWORD bfOffBits;	//ƫ����������ʹ�õ���54
}BITMAPFILEHEADER;

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


//ѧϰ
void *memset(void *s, int ch, size_t  n)
//��s�е�ǰn���ֽ���ch�滻���ҷ���s
//ͷ�ļ� #include<string.h> or <memory.h>
