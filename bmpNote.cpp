

typedef unsigned char BYTE;   
typedef unsigned short WORD;
typedef unsigned long DWORD;

//	//�����ң����µ���ɨ��
//BITMAPFILEHEADER:
//	14 Byte;
//BITMAPINFORMATION:
//	40 Byte;
//	//24λ���ɫͼBMPû�е�ɫ��
//	//λͼ����



typedef struct tagBITMAPFILEHEADER{
	//��14Byte 2+4+2+2+4

	WORD bType;			//�ļ����ͣ�������0x42 (B,���ֽ�), 0x4D (M,���ֽ�) 0x4D42
	DWORD bfSize;		//�ļ���С
	WORD bfReserved1;	//�����֣������ǣ�
	WORD bfReserved2;	//�����֣�+1��
	DWORD bfOffBits;	//ƫ����������ʹ�õ���54
};

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;			//�ṹ��tagBITMAPINFOHEADER��ռ�ֽ���
	long biWidth;			//ͼ���� pixel
	long biHeight;			//�߶� pixel
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

};