object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 961
  ClientWidth = 1248
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object pnlCaptureWindow: TPanel
    Left = 0
    Top = 0
    Width = 1248
    Height = 961
    Align = alClient
    UseDockManager = False
    TabOrder = 0
    object imCircle2: TImage
      Left = 111
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle3: TImage
      Left = 222
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle4: TImage
      Left = 333
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle5: TImage
      Left = 444
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle6: TImage
      Left = 555
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle7: TImage
      Left = 666
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle8: TImage
      Left = 777
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle9: TImage
      Left = 888
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle10: TImage
      Left = 0
      Top = 111
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle11: TImage
      Left = 111
      Top = 111
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle12: TImage
      Left = 222
      Top = 111
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle13: TImage
      Left = 333
      Top = 111
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle14: TImage
      Left = 444
      Top = 111
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle15: TImage
      Left = 555
      Top = 111
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle16: TImage
      Left = 666
      Top = 111
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle17: TImage
      Left = 777
      Top = 111
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object imCircle1: TImage
      Left = 0
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object Label1: TLabel
      Left = 16
      Top = 344
      Width = 26
      Height = 58
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -48
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 24
      Top = 560
      Width = 31
      Height = 13
      Caption = 'Label2'
      Visible = False
    end
    object imStartImg: TImage
      Left = 888
      Top = 111
      Width = 105
      Height = 105
      AutoSize = True
      Visible = False
    end
    object cbBlockDisplay: TCheckBox
      Left = 0
      Top = 944
      Width = 97
      Height = 17
      Caption = 'cbBlockDisplay'
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object mpBoom1: TMediaPlayer
      Left = 16
      Top = 446
      Width = 253
      Height = 30
      DoubleBuffered = True
      FileName = '..\\..\\sound\\boom.wav'
      Visible = False
      ParentDoubleBuffered = False
      TabOrder = 1
    end
    object btnEasy: TButton
      Left = 16
      Top = 496
      Width = 139
      Height = 98
      Caption = #31777#21934
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnEasyClick
    end
    object btnHard: TButton
      Left = 16
      Top = 619
      Width = 139
      Height = 98
      Caption = #22256#38627
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnHardClick
    end
  end
  object tiCircleID1: TTimer
    Enabled = False
    Interval = 30
    OnTimer = tiCircleID1Timer
    Left = 24
    Top = 16
  end
  object tiCircleID2: TTimer
    Enabled = False
    Interval = 30
    OnTimer = tiCircleID2Timer
    Left = 24
    Top = 72
  end
  object tiSecondCounter: TTimer
    Enabled = False
    Interval = 900
    OnTimer = tiSecondCounterTimer
    Left = 440
    Top = 304
  end
  object tiCircleID3: TTimer
    Enabled = False
    Interval = 30
    OnTimer = tiCircleID3Timer
    Left = 24
    Top = 128
  end
  object tiCircleID4: TTimer
    Enabled = False
    Interval = 30
    OnTimer = tiCircleID4Timer
    Left = 80
    Top = 16
  end
  object tiCircleID6: TTimer
    Enabled = False
    Interval = 30
    OnTimer = tiCircleID6Timer
    Left = 80
    Top = 128
  end
  object tiCircleID5: TTimer
    Enabled = False
    Interval = 30
    OnTimer = tiCircleID5Timer
    Left = 80
    Top = 72
  end
end
