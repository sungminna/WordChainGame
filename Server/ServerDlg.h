
// ServerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "ListenSocket.h"
#include "mysql.h"
#include<map>
using namespace std;

// CServerDlg 대화 상자
class CServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlEdit;
	CListenSocket* m_pListenSocket;
	virtual BOOL DestroyWindow();
	MYSQL m_mysql;
	void SignUp(CString id, CString password, UINT port);
	void Login(CString id, CString password, UINT port);
	map<UINT, CString> m_usermap;
	void Ready(int isready, CString username, CString msg);
	map<CString, int> m_ready;
	map<CString, int> m_mapScore;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_numlogged;
	CString m_prevword;
//	CString m_isfirst;
	int m_isfirst;
};
