//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

typedef struct stVirtualObject  // �������󵲺c��ƫ��A�W�١C
{
	int iID;       // ��������s���C
	int iX1;       // ��ܦ�m���W���y�� ( X1, Y1 )�C
	int iY1;
	int iX2;       // ��ܦ�m�k�U�I�y�� ( X2, Y2 )�C
	int iY2;
	int iHeight;     // �������󤧰��C
	int iWidth;     // �������󤧼e�C
	int iBlockX1;    // ��ܦ�m���W���϶��y�� ( BlockX1, BlockY1 )�C
	int iBlockY1;
	int iBlockX2;    // ��ܦ�m�k�U�I�϶��y�� ( BlockX2, BlockY2 )�C
	int iBlockY2;
	bool bVisible;
	unsigned char ucBackgroundRed;   // ��������I���� ( �� )�C
	unsigned char ucBackgroundGreen;  // ��������I���� ( �� )�C
	unsigned char ucBackgroundBlue;  // ��������I���� ( �� )�C
} stObject;     // �������󵲺c��ƫ��A�W�١C

bool flag;

int iCapWindowX1; 	// ���T�^���������W���y�� ( iCapWindowX1, iCapWindowY1 ) �C
int iCapWindowY1;
int iCapWindowWidth;
int iCapWindowHeight;
int iVideoWidth, iVideoHeight;
int iVideoFormatSize;
int iVideoMacroWidth;
int iRowBufferSize;           // iRowBufferSize: ���@�C�һݪ��O����j�p, �������Ӽƭ��H 4 �C
int iPartner;                       // �Ψ��x�s�n�洫��H�����ޭȡC
int iR, iG, iB;
int iY, iY1, iU, iY2, iV, iC1, iD, iE;
int i, j, k, t, m, n;
int iCircleID;
int iCircleID2;
int iCircleID3;
int iCircleID4;
int iCircleID5;
int iCircleID6;
int iFrameCounter;
int iTemp[480][640][3];
int iTempYUV[480][640][3];
int iVideoBlockWidth, iVideoBlockHeight;
int iBlockChangeCounter[180][240];
int iY1Difference,iUDifference,iY2Difference,iVDifference;
int iSquareDifferenceSum1, iSquareDifferenceSum2;
int iThreshold;
int iTime;
int iDifferenceRange;
int iGetCircle;
int iCircleIndex;
int iSecond;
int iEndTime;

double dSizePro;

long dwDriverIndex;	// �q�����X�ʵ{���N�X�C

wchar_t szDeviceName[80];
wchar_t szDeviceVersion[80];
wchar_t wstrCaptureWindowName[20] = L"My Capture Window";
wchar_t bgmusic[] = L"..\\..\\bgmusic.wav";

unsigned char ucTempY1, ucTempU, ucTempY2, ucTempV;    // �Ȧs�ݥ洫����m�ȡC
unsigned char ucCircleRGB[17][110][110][3];
unsigned char ucCircleYUV[17][110][110][3];
unsigned char ucBackground[480][640][3];
unsigned char ucBackgroundYUV[480][640][3];
unsigned char ucStartImgRGB[50][300][3];
unsigned char ucStartImgYUV[50][300][3];

HWND hwndVideo; 	// �x�s�ҫإߪ����T�^���������N�X�C
BITMAPINFO bmiBitmapInfo;

BYTE *ptrImage;
BYTE *ptrCapture;

stObject voCircle, voCircle2, voCircle3;
stObject voCircle4, voCircle5, voCircle6;
stObject voStartImg;

void InitialPicture();
void InitialData();
void InitialVideoFormat();
void InitialBackgroundPic();
void InitialCircle();
void InitialStartImg();

LRESULT CALLBACK FrameCallbackMirror(HWND hwndVideo, PVIDEOHDR lpvhdr);
LRESULT CALLBACK FrameCallbackBackgroundYUV(HWND hwndVideo, PVIDEOHDR lpvhdr);
LRESULT CALLBACK FrameCallbackTouch(HWND hwndVideo, PVIDEOHDR lpvhdr);
LRESULT CALLBACK FrameCallbackPlayWithGecko6B(HWND hwndCapture, PVIDEOHDR lpvhdr);
LRESULT CALLBACK FrameCallbackWaitToStart(HWND hwndCapture, PVIDEOHDR lpvhdr);
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	InitialPicture();
	InitialData();
	if (capGetDriverDescription(dwDriverIndex, szDeviceName, sizeof(szDeviceName),
		szDeviceVersion, sizeof(szDeviceVersion)))   // �����\���o������T�|�Ǧ^ true�C
	{
		InitialVideoFormat();
		InitialBackgroundPic();
		InitialCircle();
		InitialStartImg();

		capSetCallbackOnFrame(hwndVideo, &FrameCallbackBackgroundYUV);
	}
}
//---------------------------------------------------------------------------

void InitialPicture()
{
	Form1->imCircle1->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\1.bmp");
	Form1->imCircle2->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\2.bmp");
	Form1->imCircle3->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\3.bmp");
	Form1->imCircle4->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\4.bmp");
	Form1->imCircle5->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\5.bmp");
	Form1->imCircle6->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\6.bmp");
	Form1->imCircle7->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\7.bmp");
	Form1->imCircle8->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\8.bmp");
	Form1->imCircle9->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\9.bmp");
	Form1->imCircle10->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\10.bmp");
	Form1->imCircle11->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\11.bmp");
	Form1->imCircle12->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\12.bmp");
	Form1->imCircle13->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\13.bmp");
	Form1->imCircle14->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\14.bmp");
	Form1->imCircle15->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\15.bmp");
	Form1->imCircle16->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\16.bmp");
	Form1->imCircle17->Picture->Bitmap->LoadFromFile("..\\..\\img\\circle\\17.bmp");

	Form1->imStartImg->Picture->Bitmap->LoadFromFile("..\\..\\img\\UI\\start.bmp");
}
//---------------------------------------------------------------------------

void InitialData()
{
	flag = false;

	dSizePro = 0.75;
	// �@�~�t�ι��w�˪���v���X�ʵ{���|�q 0 �}�l�s���C
	dwDriverIndex = 0;
	iFrameCounter = 0;
	iThreshold = 1600;

	iTime = clock();
	srand( iTime );

	iDifferenceRange = 20;
	iGetCircle = 0;
	iCircleID = 0;

	iCircleIndex = 0;
	iCircleID2 = 0;
	iSecond = -1;

    iEndTime = 220;

	Form1->mpBoom1->Open();
}
//---------------------------------------------------------------------------

void InitialVideoFormat()
{
	iCapWindowWidth = 0;
	iCapWindowHeight = 0;
	iCapWindowX1 = 0;
	iCapWindowY1 = 0;

	// �إߵ��T�^�������C
	Form1->pnlCaptureWindow->Visible = true;
	// pnlCaptureWindow �� Panel ���� Name , �Ψө� capture window�C
	hwndVideo = capCreateCaptureWindow(wstrCaptureWindowName, WS_CHILD | WS_VISIBLE,
				iCapWindowX1, iCapWindowY1, iCapWindowWidth, iCapWindowHeight,
				Form1->pnlCaptureWindow->Handle, 1);
	capDriverConnect(hwndVideo, dwDriverIndex);
	capPreview(hwndVideo, true);
	capPreviewRate(hwndVideo, 15);
	capPreviewScale(hwndVideo, true);
	if (!capDlgVideoFormat(hwndVideo))
		ShowMessage(" Can't open video format dialog ! ! ") ;
}
//---------------------------------------------------------------------------

void InitialBackgroundPic()
{
	iVideoFormatSize = capGetVideoFormatSize(hwndVideo);
	capGetVideoFormat ( hwndVideo, &bmiBitmapInfo, iVideoFormatSize );
	iVideoWidth = bmiBitmapInfo.bmiHeader.biWidth;
	iVideoHeight = bmiBitmapInfo.bmiHeader.biHeight;
	for (j = 0; j < iVideoHeight; j++)
	{
		for (i = 0; i < iVideoWidth; i++)
		{
			// RGB ��m�Ҧ��I���v���C
			ucBackground[j][i][0] = 0;
			ucBackground[j][i][1] = 0;
			ucBackground[j][i][2] = 0;
			iTemp[j][i][0] = 0;
			iTemp[j][i][1] = 0;
			iTemp[j][i][2] = 0;
			// YUV ��m�Ҧ��I���v���C
			ucBackgroundYUV[j][i][0] = 0;
			ucBackgroundYUV[j][i][1] = 0;
			ucBackgroundYUV[j][i][2] = 0;
			iTempYUV[j][i][0] = 0;
			iTempYUV[j][i][1] = 0;
			iTempYUV[j][i][2] = 0;
		}
	}
}
//---------------------------------------------------------------------------

void InitialCircle()
{
	voCircle.iX1 = 0;
	voCircle.iY1 = 0;
	voCircle.iWidth = 110;
	voCircle.iHeight = 110;
	voCircle.iX2 = voCircle.iX1 + voCircle.iWidth - 1;
	voCircle.iY2 = voCircle.iY1 + voCircle.iHeight - 1;
	voCircle.iBlockX1 = voCircle.iX1 / 8;
	voCircle.iBlockY1 = voCircle.iY1 / 8;
	voCircle.iBlockX2 = voCircle.iX2 / 8;
	voCircle.iBlockY2 = voCircle.iY2 / 8;
	voCircle.bVisible = false;
	voCircle.ucBackgroundRed = 255;
	voCircle.ucBackgroundGreen = 255;
	voCircle.ucBackgroundBlue = 255;

	voCircle2.iX1 = 0;
	voCircle2.iY1 = 0;
	voCircle2.iWidth = 110;
	voCircle2.iHeight = 110;
	voCircle2.iX2 = voCircle2.iX1 + voCircle2.iWidth - 1;
	voCircle2.iY2 = voCircle2.iY1 + voCircle2.iHeight - 1;
	voCircle2.iBlockX1 = voCircle2.iX1 / 8;
	voCircle2.iBlockY1 = voCircle2.iY1 / 8;
	voCircle2.iBlockX2 = voCircle2.iX2 / 8;
	voCircle2.iBlockY2 = voCircle2.iY2 / 8;
	voCircle2.bVisible = false;
	voCircle2.ucBackgroundRed = 255;
	voCircle2.ucBackgroundGreen = 255;
	voCircle2.ucBackgroundBlue = 255;

	voCircle3.iX1 = 0;
	voCircle3.iY1 = 0;
	voCircle3.iWidth = 110;
	voCircle3.iHeight = 110;
	voCircle3.iX2 = voCircle3.iX1 + voCircle3.iWidth - 1;
	voCircle3.iY2 = voCircle3.iY1 + voCircle3.iHeight - 1;
	voCircle3.iBlockX1 = voCircle3.iX1 / 8;
	voCircle3.iBlockY1 = voCircle3.iY1 / 8;
	voCircle3.iBlockX2 = voCircle3.iX2 / 8;
	voCircle3.iBlockY2 = voCircle3.iY2 / 8;
	voCircle3.bVisible = false;
	voCircle3.ucBackgroundRed = 255;
	voCircle3.ucBackgroundGreen = 255;
	voCircle3.ucBackgroundBlue = 255;

	voCircle4.iX1 = 0;
	voCircle4.iY1 = 0;
	voCircle4.iWidth = 110;
	voCircle4.iHeight = 110;
	voCircle4.iX2 = voCircle2.iX1 + voCircle2.iWidth - 1;
	voCircle4.iY2 = voCircle2.iY1 + voCircle2.iHeight - 1;
	voCircle4.iBlockX1 = voCircle2.iX1 / 8;
	voCircle4.iBlockY1 = voCircle2.iY1 / 8;
	voCircle4.iBlockX2 = voCircle2.iX2 / 8;
	voCircle4.iBlockY2 = voCircle2.iY2 / 8;
	voCircle4.bVisible = false;
	voCircle4.ucBackgroundRed = 255;
	voCircle4.ucBackgroundGreen = 255;
	voCircle4.ucBackgroundBlue = 255;

	voCircle5.iX1 = 0;
	voCircle5.iY1 = 0;
	voCircle5.iWidth = 110;
	voCircle5.iHeight = 110;
	voCircle5.iX2 = voCircle2.iX1 + voCircle2.iWidth - 1;
	voCircle5.iY2 = voCircle2.iY1 + voCircle2.iHeight - 1;
	voCircle5.iBlockX1 = voCircle2.iX1 / 8;
	voCircle5.iBlockY1 = voCircle2.iY1 / 8;
	voCircle5.iBlockX2 = voCircle2.iX2 / 8;
	voCircle5.iBlockY2 = voCircle2.iY2 / 8;
	voCircle5.bVisible = false;
	voCircle5.ucBackgroundRed = 255;
	voCircle5.ucBackgroundGreen = 255;
	voCircle5.ucBackgroundBlue = 255;

	voCircle6.iX1 = 0;
	voCircle6.iY1 = 0;
	voCircle6.iWidth = 110;
	voCircle6.iHeight = 110;
	voCircle6.iX2 = voCircle2.iX1 + voCircle2.iWidth - 1;
	voCircle6.iY2 = voCircle2.iY1 + voCircle2.iHeight - 1;
	voCircle6.iBlockX1 = voCircle2.iX1 / 8;
	voCircle6.iBlockY1 = voCircle2.iY1 / 8;
	voCircle6.iBlockX2 = voCircle2.iX2 / 8;
	voCircle6.iBlockY2 = voCircle2.iY2 / 8;
	voCircle6.bVisible = false;
	voCircle6.ucBackgroundRed = 255;
	voCircle6.ucBackgroundGreen = 255;
	voCircle6.ucBackgroundBlue = 255;

    // �N�v�����󤤪���m��Ʃ��}�C��
	for (j=0; j<voCircle.iHeight; j++)
	{
		ptrImage = (BYTE*)Form1->imCircle1->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++)
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[0][j][i][0] = (unsigned char) iB;
			ucCircleRGB[0][j][i][1] = (unsigned char) iG;
			ucCircleRGB[0][j][i][2] = (unsigned char) iR;
			ucCircleYUV[0][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[0][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[0][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle2->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[1][j][i][0] = (unsigned char) iB;
			ucCircleRGB[1][j][i][1] = (unsigned char) iG;
			ucCircleRGB[1][j][i][2] = (unsigned char) iR;
			ucCircleYUV[1][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[1][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[1][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle3->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[2][j][i][0] = (unsigned char) iB;
			ucCircleRGB[2][j][i][1] = (unsigned char) iG;
			ucCircleRGB[2][j][i][2] = (unsigned char) iR;
			ucCircleYUV[2][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[2][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[2][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle4->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[3][j][i][0] = (unsigned char) iB;
			ucCircleRGB[3][j][i][1] = (unsigned char) iG;
			ucCircleRGB[3][j][i][2] = (unsigned char) iR;
			ucCircleYUV[3][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[3][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[3][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle5->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[4][j][i][0] = (unsigned char) iB;
			ucCircleRGB[4][j][i][1] = (unsigned char) iG;
			ucCircleRGB[4][j][i][2] = (unsigned char) iR;
			ucCircleYUV[4][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[4][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[4][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle6->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[5][j][i][0] = (unsigned char) iB;
			ucCircleRGB[5][j][i][1] = (unsigned char) iG;
			ucCircleRGB[5][j][i][2] = (unsigned char) iR;
			ucCircleYUV[5][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[5][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[5][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle7->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[6][j][i][0] = (unsigned char) iB;
			ucCircleRGB[6][j][i][1] = (unsigned char) iG;
			ucCircleRGB[6][j][i][2] = (unsigned char) iR;
			ucCircleYUV[6][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[6][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[6][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle8->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[7][j][i][0] = (unsigned char) iB;
			ucCircleRGB[7][j][i][1] = (unsigned char) iG;
			ucCircleRGB[7][j][i][2] = (unsigned char) iR;
			ucCircleYUV[7][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[7][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[7][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle9->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[8][j][i][0] = (unsigned char) iB;
			ucCircleRGB[8][j][i][1] = (unsigned char) iG;
			ucCircleRGB[8][j][i][2] = (unsigned char) iR;
			ucCircleYUV[8][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[8][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[8][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle10->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[9][j][i][0] = (unsigned char) iB;
			ucCircleRGB[9][j][i][1] = (unsigned char) iG;
			ucCircleRGB[9][j][i][2] = (unsigned char) iR;
			ucCircleYUV[9][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[9][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[9][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle11->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[10][j][i][0] = (unsigned char) iB;
			ucCircleRGB[10][j][i][1] = (unsigned char) iG;
			ucCircleRGB[10][j][i][2] = (unsigned char) iR;
			ucCircleYUV[10][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[10][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[10][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle12->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[11][j][i][0] = (unsigned char) iB;
			ucCircleRGB[11][j][i][1] = (unsigned char) iG;
			ucCircleRGB[11][j][i][2] = (unsigned char) iR;
			ucCircleYUV[11][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[11][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[11][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle13->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[12][j][i][0] = (unsigned char) iB;
			ucCircleRGB[12][j][i][1] = (unsigned char) iG;
			ucCircleRGB[12][j][i][2] = (unsigned char) iR;
			ucCircleYUV[12][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[12][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[12][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle14->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[13][j][i][0] = (unsigned char) iB;
			ucCircleRGB[13][j][i][1] = (unsigned char) iG;
			ucCircleRGB[13][j][i][2] = (unsigned char) iR;
			ucCircleYUV[13][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[13][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[13][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle15->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[14][j][i][0] = (unsigned char) iB;
			ucCircleRGB[14][j][i][1] = (unsigned char) iG;
			ucCircleRGB[14][j][i][2] = (unsigned char) iR;
			ucCircleYUV[14][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[14][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[14][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle16->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[15][j][i][0] = (unsigned char) iB;
			ucCircleRGB[15][j][i][1] = (unsigned char) iG;
			ucCircleRGB[15][j][i][2] = (unsigned char) iR;
			ucCircleYUV[15][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[15][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[15][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
		ptrImage = (BYTE*)Form1->imCircle17->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voCircle.iWidth; i++ )
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucCircleRGB[16][j][i][0] = (unsigned char) iB;
			ucCircleRGB[16][j][i][1] = (unsigned char) iG;
			ucCircleRGB[16][j][i][2] = (unsigned char) iR;
			ucCircleYUV[16][j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucCircleYUV[16][j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucCircleYUV[16][j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
	}
}
//---------------------------------------------------------------------------

void InitialStartImg()
{
	voStartImg.iX1 = 20;
	voStartImg.iY1 = 20;
	voStartImg.iWidth = Form1->imStartImg->Width;
	voStartImg.iHeight = Form1->imStartImg->Height;
	voStartImg.iX2 = voStartImg.iX1 + voStartImg.iWidth - 1;
	voStartImg.iY2 = voStartImg.iY1 + voStartImg.iHeight - 1;
	voStartImg.iBlockX1 = voStartImg.iX1 / 8;
	voStartImg.iBlockY1 = voStartImg.iY1 / 8;
	voStartImg.iBlockX2 = voStartImg.iX2 / 8;
	voStartImg.iBlockY2 = voStartImg.iY2 / 8;
	voStartImg.bVisible = true;
	voStartImg.ucBackgroundRed = 0;
	voStartImg.ucBackgroundGreen = 255;
	voStartImg.ucBackgroundBlue = 0;

	for (j=0; j<voStartImg.iHeight; j++)
	{
		ptrImage = (BYTE*)Form1->imStartImg->Picture->Bitmap->ScanLine[j];
		for (i=0; i<voStartImg.iWidth; i++)
		{
			iB = ptrImage[i*3];
			iG = ptrImage[i*3+1];
			iR = ptrImage[i*3+2];
			ucStartImgRGB[j][i][0] = (unsigned char) iB;
			ucStartImgRGB[j][i][1] = (unsigned char) iG;
			ucStartImgRGB[j][i][2] = (unsigned char) iR;
			ucStartImgYUV[j][i][0] = (unsigned char) (((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16);
			ucStartImgYUV[j][i][1] = (unsigned char) (((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128);
			ucStartImgYUV[j][i][2] = (unsigned char) (((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
	iCapWindowHeight = Form1->pnlCaptureWindow->Height;
	iCapWindowWidth = int((double)iCapWindowHeight / dSizePro);
	iCapWindowX1 = (Form1->pnlCaptureWindow->Width - iCapWindowWidth) / 2;
	iCapWindowY1 = 0;
	MoveWindow(hwndVideo, iCapWindowX1, iCapWindowY1, iCapWindowWidth, iCapWindowHeight, true);

	iVideoFormatSize = capGetVideoFormatSize(hwndVideo);
	capGetVideoFormat(hwndVideo , &bmiBitmapInfo , iVideoFormatSize);
	iVideoWidth = bmiBitmapInfo.bmiHeader.biWidth;
	iVideoHeight = bmiBitmapInfo.bmiHeader.biHeight;
	iVideoMacroWidth = iVideoWidth / 2;
	iRowBufferSize = iVideoMacroWidth * 4;
	iVideoBlockWidth = iVideoWidth / 8;
	iVideoBlockHeight = iVideoHeight / 8;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tiSecondCounterTimer(TObject *Sender)
{
	iSecond += 1;
	if(iSecond > 2 && iSecond < iEndTime)
	{
		if((iSecond-12) % 3 == 0)
		{
			voCircle.bVisible = true;
			voCircle.iX1 = rand() % (640-110);
			voCircle.iY1 = rand() % (480-110);
			voCircle.iX2 = voCircle.iX1 + voCircle.iWidth - 1;
			voCircle.iY2 = voCircle.iY1 + voCircle.iHeight - 1;
			voCircle.iBlockX1 = voCircle.iX1 / 8;
			voCircle.iBlockY1 = voCircle.iY1 / 8;
			voCircle.iBlockX2 = voCircle.iX2 / 8;
			voCircle.iBlockY2 = voCircle.iY2 / 8;
			tiCircleID1->Enabled = true;

			voCircle4.bVisible = true;
			voCircle4.iX1 = rand() % (640-110);
			voCircle4.iY1 = rand() % (480-110);
			voCircle4.iX2 = voCircle4.iX1 + voCircle4.iWidth - 1;
			voCircle4.iY2 = voCircle4.iY1 + voCircle4.iHeight - 1;
			voCircle4.iBlockX1 = voCircle4.iX1 / 8;
			voCircle4.iBlockY1 = voCircle4.iY1 / 8;
			voCircle4.iBlockX2 = voCircle4.iX2 / 8;
			voCircle4.iBlockY2 = voCircle4.iY2 / 8;
			tiCircleID4->Enabled = true;
			if(rand()%100 < 30)
			{
				voCircle4.iX1 = 640;
				voCircle4.iY1 = 480;
			}
		}
		else if((iSecond-12) % 3 == 1)
		{
			voCircle2.bVisible = true;
			voCircle2.iX1 = rand() % (640-110);
			voCircle2.iY1 = rand() % (480-110);
			voCircle2.iX2 = voCircle2.iX1 + voCircle2.iWidth - 1;
			voCircle2.iY2 = voCircle2.iY1 + voCircle2.iHeight - 1;
			voCircle2.iBlockX1 = voCircle2.iX1 / 8;
			voCircle2.iBlockY1 = voCircle2.iY1 / 8;
			voCircle2.iBlockX2 = voCircle2.iX2 / 8;
			voCircle2.iBlockY2 = voCircle2.iY2 / 8;
			tiCircleID2->Enabled = true;

			voCircle5.bVisible = true;
			voCircle5.iX1 = rand() % (640-110);
			voCircle5.iY1 = rand() % (480-110);
			voCircle5.iX2 = voCircle5.iX1 + voCircle5.iWidth - 1;
			voCircle5.iY2 = voCircle5.iY1 + voCircle5.iHeight - 1;
			voCircle5.iBlockX1 = voCircle5.iX1 / 8;
			voCircle5.iBlockY1 = voCircle5.iY1 / 8;
			voCircle5.iBlockX2 = voCircle5.iX2 / 8;
			voCircle5.iBlockY2 = voCircle5.iY2 / 8;
			tiCircleID5->Enabled = true;
			if(rand()%100 < 30)
			{
				voCircle5.iX1 = 640;
				voCircle5.iY1 = 480;
			}
		}
		else if((iSecond-12) % 3 == 2)
		{
			voCircle3.bVisible = true;
			voCircle3.iX1 = rand() % (640-110);
			voCircle3.iY1 = rand() % (480-110);
			voCircle3.iX2 = voCircle3.iX1 + voCircle3.iWidth - 1;
			voCircle3.iY2 = voCircle3.iY1 + voCircle3.iHeight - 1;
			voCircle3.iBlockX1 = voCircle3.iX1 / 8;
			voCircle3.iBlockY1 = voCircle3.iY1 / 8;
			voCircle3.iBlockX2 = voCircle3.iX2 / 8;
			voCircle3.iBlockY2 = voCircle3.iY2 / 8;
			tiCircleID3->Enabled = true;

			voCircle6.bVisible = true;
			voCircle6.iX1 = rand() % (640-110);
			voCircle6.iY1 = rand() % (480-110);
			voCircle6.iX2 = voCircle6.iX1 + voCircle6.iWidth - 1;
			voCircle6.iY2 = voCircle6.iY1 + voCircle6.iHeight - 1;
			voCircle6.iBlockX1 = voCircle6.iX1 / 8;
			voCircle6.iBlockY1 = voCircle6.iY1 / 8;
			voCircle6.iBlockX2 = voCircle6.iX2 / 8;
			voCircle6.iBlockY2 = voCircle6.iY2 / 8;
			tiCircleID6->Enabled = true;
			if(rand()%100 < 30)
			{
				voCircle6.iX1 = 640;
				voCircle6.iY1 = 480;
			}
		}
	}
	else if(iSecond > iEndTime+10)
	{
		Form1->tiSecondCounter->Enabled = false;
		flag = false;
		iSecond = 0;
		btnEasy->Enabled = true;
		btnHard->Enabled = true;
		capSetCallbackOnFrame ( hwndVideo, &FrameCallbackWaitToStart );
    }
	Label2->Caption = IntToStr(iSecond);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tiCircleID1Timer(TObject *Sender)
{

	iCircleID++;
	if(iCircleID > 16) {
		iCircleID = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tiCircleID2Timer(TObject *Sender)
{
	iCircleID2++;
	if(iCircleID2 > 16) {
		iCircleID2 = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tiCircleID3Timer(TObject *Sender)
{
	iCircleID3++;
	if(iCircleID3 > 16) {
		iCircleID3 = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tiCircleID4Timer(TObject *Sender)
{
	iCircleID4++;
	if(iCircleID4 > 16) {
		iCircleID4 = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tiCircleID5Timer(TObject *Sender)
{
	iCircleID5++;
	if(iCircleID5 > 16) {
		iCircleID5 = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tiCircleID6Timer(TObject *Sender)
{
	iCircleID6++;
	if(iCircleID6 > 16) {
		iCircleID6 = 0;
	}
}
//---------------------------------------------------------------------------

LRESULT CALLBACK FrameCallbackMirror(HWND hwndVideo, PVIDEOHDR lpvhdr)
{
	ptrCapture = lpvhdr->lpData;

	for ( j=0; j<iVideoHeight; j++  )
	{
		for ( i=0; i<iVideoMacroWidth/2; i++  )
		{
			// �� i �� macropixel ���洫��H�O�� ( iVideoWidth / 2 ) - i �C
			iPartner = iVideoMacroWidth - i - 1;
			// ���N�� i �� marcopixel ���|�Ӧ줸�ժ���m�ȼȦs�_�ӡC
			ucTempY1 = ptrCapture[j*iRowBufferSize+i*4];
			ucTempU = ptrCapture[j*iRowBufferSize+i*4+1];
			ucTempY2 = ptrCapture[j*iRowBufferSize+i*4+2];
			ucTempV = ptrCapture[j*iRowBufferSize+i*4+3];
			// �� Partner ���|�Ӧ줸�ժ���m�Ƚƻs�L��, �� Y1 �P Y2 �n������m�C
			ptrCapture[j*iRowBufferSize+i*4] = ptrCapture[j*iRowBufferSize+iPartner*4+2];
			ptrCapture[j*iRowBufferSize+i*4+1] = ptrCapture[j*iRowBufferSize+iPartner*4+1];
			ptrCapture[j*iRowBufferSize+i*4+2] = ptrCapture[j*iRowBufferSize+iPartner*4];
			ptrCapture[j*iRowBufferSize+i*4+ 3] = ptrCapture[j*iRowBufferSize+iPartner*4+3];
			// �N�Ȧs����m�ȩ�� Partner ���w�İϰO���餧��, �� Y1 �P Y2 �n������m�C
			ptrCapture[j*iRowBufferSize+iPartner*4] = ucTempY2;
			ptrCapture[j*iRowBufferSize+iPartner*4+1] = ucTempU;
			ptrCapture[j*iRowBufferSize+iPartner*4+2] = ucTempY1;
			ptrCapture[j*iRowBufferSize+iPartner*4+3] = ucTempV;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

LRESULT CALLBACK FrameCallbackBackgroundYUV ( HWND hwndVideo, PVIDEOHDR lpvhdr )
{
	ptrCapture = lpvhdr->lpData;

	FrameCallbackMirror(hwndVideo, lpvhdr);

	iFrameCounter++;
	if ( iFrameCounter > 15 )
	{
		// �����֥[ 30 �i�v��, �p�⥭���v���C
		for ( j=0; j < iVideoHeight; j++ )
		{
			t = 0;
			for ( i=0; i < iVideoWidth; i++ )
			{
				ucBackgroundYUV[j][i][0] = ( unsigned char ) ( iTempYUV[j][i][0] / 15 );
				ucBackgroundYUV[j][i][1] = ( unsigned char ) ( iTempYUV[j][i][1] / 15 );
				ucBackgroundYUV[j][i][2] = ( unsigned char ) ( iTempYUV[j][i][2] / 15 );
				// �N YUV ��m�ഫ�� RGB ��m��, �s�� imBackgroung ����ܥX�ӡC
				iY = ucBackgroundYUV[j][i][0];
				iU = ucBackgroundYUV[j][i][1];
				iV = ucBackgroundYUV[j][i][2];
				iC1 = iY - 16;
				iD = iU - 128;
				iE = iV - 128;
				// �B�z���⤧��m�ഫ�C
				iR = ( 298 * iC1 + 409 * iE + 128 ) >> 8;
				// �ˬd iR �O�_�o�ͷ��� ? �p�G�W�L 255 ���ܵo�ͷ���, �N��ȳ]�w�� 255�C
				if ( iR > 255 )
					iR = 255;
				else if ( iR < 0 )
					iR = 0;
				// �B�z��⤧��m�ഫ
				iG = ( 298 * iC1 - 100 * iD - 208 * iE + 128 ) >> 8;
				// �ˬd iG �O�_�o�ͷ��� ? �p�G�W�L 255 ���ܵo�ͷ���, �N��ȳ]�w�� 255�C
				if ( iG > 255 )
					iG = 255;
				else if ( iG < 0 )
					iG = 0;
				iB = ( 298 * iC1 + 516 * iD     + 128 ) >> 8;
				// �ˬd iB �O�_�o�ͷ��� ? �p�G�W�L 255 ���ܵo�ͷ���, �N��ȳ]�w�� 255�C
				if ( iB > 255 )
					iB = 255;
				else if ( iB < 0 )
					iB = 0;
				t = t + 3;
			}
		}
		// �I���v���إߧ���, �����w���^�I�禡�C
		iFrameCounter = 0;
		if(flag) {
			capSetCallbackOnFrame ( hwndVideo, &FrameCallbackTouch );
			Form1->btnEasy->Enabled = false;
			Form1->btnHard->Enabled = false;
		}
		else
			capSetCallbackOnFrame ( hwndVideo, &FrameCallbackWaitToStart );
	}
	else if(iFrameCounter >= 0)
	{
		k = 0;
		for ( j=0; j < iVideoHeight; j++ )
		{
			for ( i=0; i < iVideoWidth; i=i+2 )
			{
				iY1 = ptrCapture[k];
				iU = ptrCapture[k+1];
				iY2 = ptrCapture[k+2];
				iV = ptrCapture[k+3];
				// �֥[�����������Ĥ@�ӹ��� ( Pixel 1 )
				iTempYUV[j][i][0] = iTempYUV[j][i][0] + iY1;
				iTempYUV[j][i][1] = iTempYUV[j][i][1] + iU;
				iTempYUV[j][i][2] = iTempYUV[j][i][2] + iV;
				// �֥[�����������ĤG�ӹ��� ( Pixel 2 )
				iTempYUV[j][i+1][0] = iTempYUV[j][i+1][0] + iY2;
				iTempYUV[j][i+1][1] = iTempYUV[j][i+1][1] + iU;
				iTempYUV[j][i+1][2] = iTempYUV[j][i+1][2] + iV;
				k = k + 4;
			}
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

LRESULT CALLBACK FrameCallbackWaitToStart( HWND hwndCapture, PVIDEOHDR lpvhdr )
{
	iFrameCounter++;
	ptrCapture = lpvhdr->lpData;
	FrameCallbackMirror(hwndVideo, lpvhdr);

	// ���]�϶��֥[�}�C
	for ( m = 0; m < iVideoBlockHeight; m++ )
		for ( n = 0; n < iVideoBlockWidth; n++ )
			iBlockChangeCounter[m][n] = 0;

	// �j�餤, �P�ɳB�z��Ҫ��󰻴� ( �t������ ) �P�m�J�����������T�^������
	// ���i���Ҫ��󰻴�, �A�i��m�J�����������T�^������
	k = 0;
	for ( j=0; j < iVideoHeight; j++ )
	{
		for ( i=0; i < iVideoWidth; i=i+2 )
		{
			m = j / 8;
			n = i / 8;
			iY1 = ptrCapture[k];
			iU = ptrCapture[k+1];
			iY2 = ptrCapture[k+2];
			iV = ptrCapture[k+3];
			iY1Difference = abs( ptrCapture[k] - ucBackgroundYUV[j][i][0] );
			iUDifference = abs( ptrCapture[k+1] - ucBackgroundYUV[j][i][1] );
			iY2Difference = abs( ptrCapture[k+2] - ucBackgroundYUV[j][i+1][0] );
			iVDifference = abs( ptrCapture[k+3] - ucBackgroundYUV[j][i+1][2] );

			iSquareDifferenceSum1 = iY1Difference * iY1Difference + iUDifference * iUDifference + iVDifference * iVDifference;
			iSquareDifferenceSum2 = iY2Difference * iY2Difference + iUDifference * iUDifference + iVDifference * iVDifference;
			// �֥[�C�Ӱ϶������t������
			if ( iSquareDifferenceSum1 > iThreshold )
				iBlockChangeCounter[m][n]++;
			if ( iSquareDifferenceSum2 > iThreshold )
				iBlockChangeCounter[m][n]++;

			k = k + 4;
		}
	}

	// ��Ҫ��󰻴�����, ���U��, �}�l�m�J�����������T�^������
	// ���ϥΪ̤Ŀ� 8 * 8 �¥հ϶���ܮ�, �h�N���T�^���������e�̷Ӯt���������G���
	// �զ� YUV ��m�Ȫ� YUV = ( 255, 128, 128 )
	// �¦� YUV ��m�Ȫ� YUV = ( 16, 128, 128 )

	k = 0;
	for ( j = 0; j < iVideoHeight; j++ )
	{
		for ( i=0; i < iVideoWidth; i = i + 2 )
		{
			m = j / 8;
			n = i / 8;
			if ( Form1->cbBlockDisplay->Checked )
			{
				ptrCapture[k+1] = 128;
				ptrCapture[k+3] = 128;
				if ( iBlockChangeCounter[m][n] > iDifferenceRange )
				{
					ptrCapture[k] = 255;
					ptrCapture[k+2] = 255;
				}
				else
				{
					ptrCapture[k] = 16;
					ptrCapture[k+2] = 16;
				}
			}

			// �p�G bVisible �Ȭ� true,
			// �b�y�� ( iX1, iY1 ) �P ( iX2, iY2 ) �������ϰ�n�m�J��������
			if ( ( voStartImg.bVisible ) &&
			( i >= voStartImg.iX1 ) && ( i < voStartImg.iX2 ) &&
			( j >= voStartImg.iY1 ) && ( j < voStartImg.iY2 ) )
			{
				// �������󪺭I���ϰ쥲������, �L���m�J
				if (  ( ucStartImgRGB[j - voStartImg.iY1][i - voStartImg.iX1][0] != voStartImg.ucBackgroundBlue )
				|| ( ucStartImgRGB[j - voStartImg.iY1][i - voStartImg.iX1][1] != voStartImg.ucBackgroundGreen )
				|| ( ucStartImgRGB[j - voStartImg.iY1][i - voStartImg.iX1][2] != voStartImg.ucBackgroundRed ) )
				{
					ptrCapture[k] = ucStartImgYUV[j-voStartImg.iY1][i-voStartImg.iX1][0];
					ptrCapture[k+1] = ucStartImgYUV[j-voStartImg.iY1][i-voStartImg.iX1][1];
					ptrCapture[k+2] = ucStartImgYUV[j-voStartImg.iY1][i-voStartImg.iX1+1][0];
					ptrCapture[k+3] = ucStartImgYUV[j-voStartImg.iY1][i-voStartImg.iX1][2];
				}
			}
			k = k + 4;
		}
	}

	// ��Ҫ��󪺦�m�� iBlockChangeCounter[m][n] > 31 ���϶�,
	// �������󪺦�m��( iObjectBlockX1, iObjectBlockY1 ) �P ( iObjectBlockX2, iObjectBlockY2 ) ����,
	// �ˬd��Ҫ���P�������󪺦�m�O�_���| ?

	k = 0;
	for ( m=0; m < iVideoBlockHeight; m++ )
	{
		for ( n=0; n < iVideoBlockWidth; n++ )
		{
			// �� 1 �ӧP�_�� ( iBlockChangeCounter[m][n]>31 ) �P�_��Ҫ��󪺦�m,
			// ��l 4 �ӧP�_���O�P�_�������󪺦�m,
			// �P�ɦ��ߪ��ܨ�Ӫ���b�o�� [m, n] �϶����涰 !
			if ( ( voStartImg.bVisible )&&
			( m > voStartImg.iBlockY1 ) && ( n > voStartImg.iBlockX1 ) &&
			( m < voStartImg.iBlockY2 ) && ( n < voStartImg.iBlockX2 ) &&
				iBlockChangeCounter[m][n]>iDifferenceRange )
			{
				Form1->tiSecondCounter->Enabled = true;
				PlaySound(bgmusic, NULL, SND_FILENAME|SND_ASYNC);
				flag = true;
				iFrameCounter = -50;
				//InitialBackgroundPic();
				capSetCallbackOnFrame ( hwndVideo, &FrameCallbackTouch );
			}
		}
	}

	// ���}�w���^�I�禡
	return 0;
}
//---------------------------------------------------------------------------

LRESULT CALLBACK FrameCallbackTouch( HWND hwndCapture, PVIDEOHDR lpvhdr )
{
	iFrameCounter++;
	ptrCapture = lpvhdr->lpData;
	FrameCallbackMirror(hwndVideo, lpvhdr);

	// ���]�϶��֥[�}�C
	for ( m = 0; m < iVideoBlockHeight; m++ )
		for ( n = 0; n < iVideoBlockWidth; n++ )
			iBlockChangeCounter[m][n] = 0;

	// �j�餤, �P�ɳB�z��Ҫ��󰻴� ( �t������ ) �P�m�J�����������T�^������
	// ���i���Ҫ��󰻴�, �A�i��m�J�����������T�^������
	k = 0;
	for ( j=0; j < iVideoHeight; j++ )
	{
		for ( i=0; i < iVideoWidth; i=i+2 )
		{
			m = j / 8;
			n = i / 8;
			iY1 = ptrCapture[k];
			iU = ptrCapture[k+1];
			iY2 = ptrCapture[k+2];
			iV = ptrCapture[k+3];
			iY1Difference = abs( ptrCapture[k] - ucBackgroundYUV[j][i][0] );
			iUDifference = abs( ptrCapture[k+1] - ucBackgroundYUV[j][i][1] );
			iY2Difference = abs( ptrCapture[k+2] - ucBackgroundYUV[j][i+1][0] );
			iVDifference = abs( ptrCapture[k+3] - ucBackgroundYUV[j][i+1][2] );

			iSquareDifferenceSum1 = iY1Difference * iY1Difference + iUDifference * iUDifference + iVDifference * iVDifference;
			iSquareDifferenceSum2 = iY2Difference * iY2Difference + iUDifference * iUDifference + iVDifference * iVDifference;
			// �֥[�C�Ӱ϶������t������
			if ( iSquareDifferenceSum1 > iThreshold )
				iBlockChangeCounter[m][n]++;
			if ( iSquareDifferenceSum2 > iThreshold )
				iBlockChangeCounter[m][n]++;

			k = k + 4;
			}
	}

	// ��Ҫ��󰻴�����, ���U��, �}�l�m�J�����������T�^������
	// ���ϥΪ̤Ŀ� 8 * 8 �¥հ϶���ܮ�, �h�N���T�^���������e�̷Ӯt���������G���
	// �զ� YUV ��m�Ȫ� YUV = ( 255, 128, 128 )
	// �¦� YUV ��m�Ȫ� YUV = ( 16, 128, 128 )

	k = 0;
	for ( j = 0; j < iVideoHeight; j++ )
	{
		for ( i=0; i < iVideoWidth; i = i + 2 )
		{
			m = j / 8;
			n = i / 8;
			if ( Form1->cbBlockDisplay->Checked )
			{
				ptrCapture[k+1] = 128;
				ptrCapture[k+3] = 128;
				if ( iBlockChangeCounter[m][n] > iDifferenceRange )
				{
					ptrCapture[k] = 255;
					ptrCapture[k+2] = 255;
				}
				else
				{
					ptrCapture[k] = 16;
					ptrCapture[k+2] = 16;
				}
			}

			// �p�G bVisible �Ȭ� true,
			// �b�y�� ( iX1, iY1 ) �P ( iX2, iY2 ) �������ϰ�n�m�J��������
			if ( ( voCircle.bVisible ) &&
			( i >= voCircle.iX1 ) && ( i < voCircle.iX2 ) &&
			( j >= voCircle.iY1 ) && ( j < voCircle.iY2 ) )
			{
				// �������󪺭I���ϰ쥲������, �L���m�J
				if (  ( ucCircleRGB[iCircleID][j - voCircle.iY1][i - voCircle.iX1][0] != voCircle.ucBackgroundBlue )
				|| ( ucCircleRGB[iCircleID][j - voCircle.iY1][i - voCircle.iX1][1] != voCircle.ucBackgroundGreen )
				|| ( ucCircleRGB[iCircleID][j - voCircle.iY1][i - voCircle.iX1][2] != voCircle.ucBackgroundRed ) )
				{
					ptrCapture[k ] = ucCircleYUV[iCircleID][j-voCircle.iY1][i-voCircle.iX1][0];
					ptrCapture[k+1] = ucCircleYUV[iCircleID][j-voCircle.iY1][i-voCircle.iX1][1];
					ptrCapture[k+2] = ucCircleYUV[iCircleID][j-voCircle.iY1][i-voCircle.iX1+1][0];
					ptrCapture[k+3] = ucCircleYUV[iCircleID][j-voCircle.iY1][i-voCircle.iX1][2];
				}
			}
			if ( ( voCircle2.bVisible ) &&
			( i >= voCircle2.iX1 ) && ( i < voCircle2.iX2 ) &&
			( j >= voCircle2.iY1 ) && ( j < voCircle2.iY2 ) )
			{
				// �������󪺭I���ϰ쥲������, �L���m�J
				if (  ( ucCircleRGB[iCircleID2][j - voCircle2.iY1][i - voCircle2.iX1][0] != voCircle2.ucBackgroundBlue )
				|| ( ucCircleRGB[iCircleID2][j - voCircle2.iY1][i - voCircle2.iX1][1] != voCircle2.ucBackgroundGreen )
				|| ( ucCircleRGB[iCircleID2][j - voCircle2.iY1][i - voCircle2.iX1][2] != voCircle2.ucBackgroundRed ) )
				{
					ptrCapture[k ] = ucCircleYUV[iCircleID2][j-voCircle2.iY1][i-voCircle2.iX1][0];
					ptrCapture[k+1] = ucCircleYUV[iCircleID2][j-voCircle2.iY1][i-voCircle2.iX1][1];
					ptrCapture[k+2] = ucCircleYUV[iCircleID2][j-voCircle2.iY1][i-voCircle2.iX1+1][0];
					ptrCapture[k+3] = ucCircleYUV[iCircleID2][j-voCircle2.iY1][i-voCircle2.iX1][2];
				}
			}
			if ( ( voCircle3.bVisible ) &&
			( i >= voCircle3.iX1 ) && ( i < voCircle3.iX2 ) &&
			( j >= voCircle3.iY1 ) && ( j < voCircle3.iY2 ) )
			{
				// �������󪺭I���ϰ쥲������, �L���m�J
				if (  ( ucCircleRGB[iCircleID3][j - voCircle3.iY1][i - voCircle3.iX1][0] != voCircle3.ucBackgroundBlue )
				|| ( ucCircleRGB[iCircleID3][j - voCircle3.iY1][i - voCircle3.iX1][1] != voCircle3.ucBackgroundGreen )
				|| ( ucCircleRGB[iCircleID3][j - voCircle3.iY1][i - voCircle3.iX1][2] != voCircle3.ucBackgroundRed ) )
				{
					ptrCapture[k ] = ucCircleYUV[iCircleID3][j-voCircle3.iY1][i-voCircle3.iX1][0];
					ptrCapture[k+1] = ucCircleYUV[iCircleID3][j-voCircle3.iY1][i-voCircle3.iX1][1];
					ptrCapture[k+2] = ucCircleYUV[iCircleID3][j-voCircle3.iY1][i-voCircle3.iX1+1][0];
					ptrCapture[k+3] = ucCircleYUV[iCircleID3][j-voCircle3.iY1][i-voCircle3.iX1][2];
				}
			}
			if ( ( voCircle4.bVisible ) &&
			( i >= voCircle4.iX1 ) && ( i < voCircle4.iX2 ) &&
			( j >= voCircle4.iY1 ) && ( j < voCircle4.iY2 ) )
			{
				// �������󪺭I���ϰ쥲������, �L���m�J
				if (  ( ucCircleRGB[iCircleID4][j - voCircle4.iY1][i - voCircle4.iX1][0] != voCircle4.ucBackgroundBlue )
				|| ( ucCircleRGB[iCircleID4][j - voCircle4.iY1][i - voCircle4.iX1][1] != voCircle4.ucBackgroundGreen )
				|| ( ucCircleRGB[iCircleID4][j - voCircle4.iY1][i - voCircle4.iX1][2] != voCircle4.ucBackgroundRed ) )
				{
					ptrCapture[k ] = ucCircleYUV[iCircleID4][j-voCircle4.iY1][i-voCircle4.iX1][0];
					ptrCapture[k+1] = ucCircleYUV[iCircleID4][j-voCircle4.iY1][i-voCircle4.iX1][1];
					ptrCapture[k+2] = ucCircleYUV[iCircleID4][j-voCircle4.iY1][i-voCircle4.iX1+1][0];
					ptrCapture[k+3] = ucCircleYUV[iCircleID4][j-voCircle4.iY1][i-voCircle4.iX1][2];
				}
			}
			if ( ( voCircle5.bVisible ) &&
			( i >= voCircle5.iX1 ) && ( i < voCircle5.iX2 ) &&
			( j >= voCircle5.iY1 ) && ( j < voCircle5.iY2 ) )
			{
				// �������󪺭I���ϰ쥲������, �L���m�J
				if (  ( ucCircleRGB[iCircleID5][j - voCircle5.iY1][i - voCircle5.iX1][0] != voCircle5.ucBackgroundBlue )
				|| ( ucCircleRGB[iCircleID5][j - voCircle5.iY1][i - voCircle5.iX1][1] != voCircle5.ucBackgroundGreen )
				|| ( ucCircleRGB[iCircleID5][j - voCircle5.iY1][i - voCircle5.iX1][2] != voCircle5.ucBackgroundRed ) )
				{
					ptrCapture[k ] = ucCircleYUV[iCircleID5][j-voCircle5.iY1][i-voCircle5.iX1][0];
					ptrCapture[k+1] = ucCircleYUV[iCircleID5][j-voCircle5.iY1][i-voCircle5.iX1][1];
					ptrCapture[k+2] = ucCircleYUV[iCircleID5][j-voCircle5.iY1][i-voCircle5.iX1+1][0];
					ptrCapture[k+3] = ucCircleYUV[iCircleID5][j-voCircle5.iY1][i-voCircle5.iX1][2];
				}
			}
			if ( ( voCircle6.bVisible ) &&
			( i >= voCircle6.iX1 ) && ( i < voCircle6.iX2 ) &&
			( j >= voCircle6.iY1 ) && ( j < voCircle6.iY2 ) )
			{
				// �������󪺭I���ϰ쥲������, �L���m�J
				if (  ( ucCircleRGB[iCircleID6][j - voCircle6.iY1][i - voCircle6.iX1][0] != voCircle6.ucBackgroundBlue )
				|| ( ucCircleRGB[iCircleID6][j - voCircle6.iY1][i - voCircle6.iX1][1] != voCircle6.ucBackgroundGreen )
				|| ( ucCircleRGB[iCircleID6][j - voCircle6.iY1][i - voCircle6.iX1][2] != voCircle6.ucBackgroundRed ) )
				{
					ptrCapture[k ] = ucCircleYUV[iCircleID6][j-voCircle6.iY1][i-voCircle6.iX1][0];
					ptrCapture[k+1] = ucCircleYUV[iCircleID6][j-voCircle6.iY1][i-voCircle6.iX1][1];
					ptrCapture[k+2] = ucCircleYUV[iCircleID6][j-voCircle6.iY1][i-voCircle6.iX1+1][0];
					ptrCapture[k+3] = ucCircleYUV[iCircleID6][j-voCircle6.iY1][i-voCircle6.iX1][2];
				}
			}
			k = k + 4;
		}
	}

	// ��Ҫ��󪺦�m�� iBlockChangeCounter[m][n] > 31 ���϶�,
	// �������󪺦�m��( iObjectBlockX1, iObjectBlockY1 ) �P ( iObjectBlockX2, iObjectBlockY2 ) ����,
	// �ˬd��Ҫ���P�������󪺦�m�O�_���| ?

	k = 0;
	for ( m=0; m < iVideoBlockHeight; m++ )
	{
		for ( n=0; n < iVideoBlockWidth; n++ )
		{
			// �� 1 �ӧP�_�� ( iBlockChangeCounter[m][n]>31 ) �P�_��Ҫ��󪺦�m,
			// ��l 4 �ӧP�_���O�P�_�������󪺦�m,
			// �P�ɦ��ߪ��ܨ�Ӫ���b�o�� [m, n] �϶����涰 !
			if ( ( voCircle.bVisible )&&
			( m > voCircle.iBlockY1 ) && ( n > voCircle.iBlockX1 ) &&
			( m < voCircle.iBlockY2 ) && ( n < voCircle.iBlockX2 ) && iCircleID == 16)
			{
				if(( iBlockChangeCounter[m][n]>iDifferenceRange ))
				{
					// �Ұʤ��ʳB�z�{�ǡC
					iGetCircle++;
					Form1->mpBoom1->Play();
				}
			}
			if ( ( voCircle2.bVisible )&&
			( m > voCircle2.iBlockY1 ) && ( n > voCircle2.iBlockX1 ) &&
			( m < voCircle2.iBlockY2 ) && ( n < voCircle2.iBlockX2 ) && iCircleID2 == 16)
			{
				if(( iBlockChangeCounter[m][n]>iDifferenceRange ))
				{
					// �Ұʤ��ʳB�z�{�ǡC
					iGetCircle++;
					Form1->mpBoom1->Play();
				}
			}
			if ( ( voCircle3.bVisible )&&
			( m > voCircle3.iBlockY1 ) && ( n > voCircle3.iBlockX1 ) &&
			( m < voCircle3.iBlockY2 ) && ( n < voCircle3.iBlockX2 ) && iCircleID3 == 16)
			{
				if(( iBlockChangeCounter[m][n]>iDifferenceRange ))
				{
					// �Ұʤ��ʳB�z�{�ǡC
					iGetCircle++;
					Form1->mpBoom1->Play();
				}
			}
			if ( ( voCircle4.bVisible )&&
			( m > voCircle4.iBlockY1 ) && ( n > voCircle4.iBlockX1 ) &&
			( m < voCircle4.iBlockY2 ) && ( n < voCircle4.iBlockX2 ) && iCircleID4 == 16)
			{
				if(( iBlockChangeCounter[m][n]>iDifferenceRange ))
				{
					// �Ұʤ��ʳB�z�{�ǡC
					iGetCircle++;
					Form1->mpBoom1->Play();
				}
			}
			if ( ( voCircle5.bVisible )&&
			( m > voCircle5.iBlockY1 ) && ( n > voCircle5.iBlockX1 ) &&
			( m < voCircle5.iBlockY2 ) && ( n < voCircle5.iBlockX2 ) && iCircleID5 == 16)
			{
				if(( iBlockChangeCounter[m][n]>iDifferenceRange ))
				{
					// �Ұʤ��ʳB�z�{�ǡC
					iGetCircle++;
					Form1->mpBoom1->Play();
				}
			}
			if ( ( voCircle6.bVisible )&&
			( m > voCircle6.iBlockY1 ) && ( n > voCircle6.iBlockX1 ) &&
			( m < voCircle6.iBlockY2 ) && ( n < voCircle6.iBlockX2 ) && iCircleID6 == 16)
			{
				if(( iBlockChangeCounter[m][n]>iDifferenceRange ))
				{
					// �Ұʤ��ʳB�z�{�ǡC
					iGetCircle++;
					Form1->mpBoom1->Play();
				}
			}
		}
	}

	if(iCircleID == 16)
	{
        voCircle.bVisible = false;
		Form1->tiCircleID1->Enabled = false;
		iCircleID = 0;
	}
	if(iCircleID2 == 16)
	{
		voCircle2.bVisible = false;
		Form1->tiCircleID2->Enabled = false;
		iCircleID2 = 0;
	}
	if(iCircleID3 == 16)
	{
		voCircle3.bVisible = false;
		Form1->tiCircleID3->Enabled = false;
		iCircleID3 = 0;
	}
	if(iCircleID4 == 16)
	{
		voCircle4.bVisible = false;
		Form1->tiCircleID4->Enabled = false;
		iCircleID4 = 0;
	}
	if(iCircleID5 == 16)
	{
		voCircle5.bVisible = false;
		Form1->tiCircleID5->Enabled = false;
		iCircleID5 = 0;
	}
	if(iCircleID6 == 16)
	{
		voCircle6.bVisible = false;
		Form1->tiCircleID6->Enabled = false;
		iCircleID6 = 0;
	}

	Form1->Label1->Caption = IntToStr(iGetCircle);
	// ���}�w���^�I�禡
	return 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnEasyClick(TObject *Sender)
{
	tiSecondCounter->Interval = 1800;
	iEndTime = 110;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnHardClick(TObject *Sender)
{
	tiSecondCounter->Interval = 900;
    iEndTime = 220;
}
//---------------------------------------------------------------------------
