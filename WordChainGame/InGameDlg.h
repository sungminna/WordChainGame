#pragma once


// CInGameDlg 대화 상자입니다.

class CInGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInGameDlg)

public:
	CInGameDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInGameDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INGAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddBtn1();
	afx_msg void OnBnClickedAddBtn2();
	CListBox m_chat_list1;
	CListBox m_chat_list2;
};
