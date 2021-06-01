
// WordChainGameDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "ClientSocket.h"

// CWordChainGameDlg 대화 상자
class CWordChainGameDlg : public CDialogEx
{
// 생성입니다.
public:
	CWordChainGameDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORDCHAINGAME_DIALOG };
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
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnStnClickedStatic2();
	CString m_strAddress;
	int m_nPort;
	CEdit m_ctrlEdit;
	CClientSocket* m_pClientSocket;
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButton2();
	CString m_strID;
	CString m_strPASSWORD;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
//	CString m_strLeaderBoard;
//	CEdit m_editLeaderBoard;
	CEdit m_ctrlLeaderBoard;
	CEdit m_ctrlWho;
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_cnt;
};
