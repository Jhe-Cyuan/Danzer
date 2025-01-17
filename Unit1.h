//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <vfw.h>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.MPlayer.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlCaptureWindow;
	TImage *imCircle2;
	TImage *imCircle3;
	TImage *imCircle4;
	TImage *imCircle5;
	TImage *imCircle6;
	TImage *imCircle7;
	TImage *imCircle8;
	TImage *imCircle9;
	TImage *imCircle10;
	TImage *imCircle11;
	TImage *imCircle12;
	TImage *imCircle13;
	TImage *imCircle14;
	TImage *imCircle15;
	TImage *imCircle16;
	TImage *imCircle17;
	TImage *imCircle1;
	TTimer *tiCircleID1;
	TCheckBox *cbBlockDisplay;
	TLabel *Label1;
	TMediaPlayer *mpBoom1;
	TTimer *tiCircleID2;
	TTimer *tiSecondCounter;
	TLabel *Label2;
	TTimer *tiCircleID3;
	TImage *imStartImg;
	TTimer *tiCircleID4;
	TTimer *tiCircleID6;
	TTimer *tiCircleID5;
	TButton *btnEasy;
	TButton *btnHard;
	void __fastcall tiCircleID1Timer(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall tiSecondCounterTimer(TObject *Sender);
	void __fastcall tiCircleID2Timer(TObject *Sender);
	void __fastcall tiCircleID3Timer(TObject *Sender);
	void __fastcall tiCircleID4Timer(TObject *Sender);
	void __fastcall tiCircleID5Timer(TObject *Sender);
	void __fastcall tiCircleID6Timer(TObject *Sender);
	void __fastcall btnEasyClick(TObject *Sender);
	void __fastcall btnHardClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
