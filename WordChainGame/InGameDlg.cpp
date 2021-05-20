// InGameDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WordChainGame.h"
#include "InGameDlg.h"
#include "afxdialogex.h"


// CInGameDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInGameDlg, CDialogEx)

CInGameDlg::CInGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INGAME, pParent)
{

}

CInGameDlg::~CInGameDlg()
{
}

void CInGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInGameDlg, CDialogEx)
END_MESSAGE_MAP()


// CInGameDlg 메시지 처리기입니다.
