object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form_Permyakova'
  ClientHeight = 390
  ClientWidth = 619
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 488
    Top = 24
    Width = 3
    Height = 13
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 8
    Width = 449
    Height = 374
    Header.AutoSizeIndex = 0
    Header.Font.Charset = DEFAULT_CHARSET
    Header.Font.Color = clWindowText
    Header.Font.Height = -11
    Header.Font.Name = 'Tahoma'
    Header.Font.Style = []
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    OnFreeNode = VirtualStringTree1FreeNode
    OnGetText = VirtualStringTree1GetText
    Columns = <
      item
        Position = 0
        Width = 46
        WideText = 'ID'
      end
      item
        Position = 1
        Width = 404
        WideText = 'url'
      end>
  end
  object Button1: TButton
    Left = 472
    Top = 64
    Width = 139
    Height = 41
    Caption = #1054#1090#1086#1073#1088#1072#1079#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 472
    Top = 128
    Width = 139
    Height = 41
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 472
    Top = 192
    Width = 139
    Height = 41
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
    TabOrder = 3
    OnClick = Button3Click
  end
end
