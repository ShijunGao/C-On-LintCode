

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
	WORD bType;			//�ļ����ͣ�������0x42 (B,���ֽ�), 0x4D (M,���ֽ�) 0x4D42
	DWORD bfSize;		//�ļ���С
	WORD bfReserved1;	//�����֣������ǣ�
	WORD bfReserved2;	//�����֣�+1��
	DWORD bfOffBits;	//ƫ����������ʹ�õ���
};
