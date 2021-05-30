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
	DDX_Control(pDX, IDC_CHAT_LIST1, m_chat_list1);
	DDX_Control(pDX, IDC_CHAT_LIST2, m_chat_list2);
}


BEGIN_MESSAGE_MAP(CInGameDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_BTN1, &CInGameDlg::OnBnClickedAddBtn1)
	ON_BN_CLICKED(IDC_ADD_BTN2, &CInGameDlg::OnBnClickedAddBtn2)
END_MESSAGE_MAP()


// CInGameDlg 메시지 처리기입니다.


void CInGameDlg::OnBnClickedAddBtn1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemText(IDC_CHAT_EDIT1, str);
	CInGameDlg::OnBnClickedAddBtn2();

}


void CInGameDlg::OnBnClickedAddBtn2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItemText(IDC_CHAT_EDIT2, str);
	CInGameDlg::OnBnClickedAddBtn2();
}
