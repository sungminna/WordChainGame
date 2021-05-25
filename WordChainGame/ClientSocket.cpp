// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WordChainGame.h"
#include "ClientSocket.h"
#include "WordChainGameDlg.h"
#include "InGameDlg.h"

// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	this->ShutDown();
	this->Close();
	AfxMessageBox(_T("서버가 연결을 종료하엿습니다"));
	::PostQuitMessage(0);
	CSocket::OnClose(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	TCHAR szBuff[1024];
	int nRead = Receive(szBuff, sizeof(szBuff));
	switch (nRead) {
	case 0: this->Close(); break;
	case SOCKET_ERROR: if (GetLastError() != WSAEWOULDBLOCK) {
		AfxMessageBox(_T("Error occured"));
		this->Close();
	}break;
	default: 
		szBuff[nRead] = _T('\0');
		CWordChainGameDlg* pMain = (CWordChainGameDlg*)AfxGetMainWnd();

		if (szBuff[0] == '0') {	//회원가입
			CString name;
			CString msg;
			AfxExtractSubString(name, szBuff, 1, ' ');
			msg.Format(_T("%s 님이 회원가입 하셨습니다\r\n"), name);
			pMain->m_ctrlEdit.ReplaceSel(msg);

			if (pMain->m_strID == name) {	//내가 회원가입
				pMain->m_strID = _T("");
				pMain->m_strPASSWORD = _T("");
				CString text;
				text.Format(_T("%s 님 안녕하세요!!"), name);
				pMain->SetDlgItemText(IDC_STATIC11, text);
				//비활성화 및 활성화
				pMain->GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
			}
		}
		else if (szBuff[0] == '1') {	//로그인
			CString name;
			CString msg;
			AfxExtractSubString(name, szBuff, 1, ' ');
			msg.Format(_T("%s 님이 로그인 하셨습니다\r\n"), name);
			pMain->m_ctrlEdit.ReplaceSel(msg);

			if (pMain->m_strID == name) {	//내가 로그인
				pMain->m_strID = _T("");
				pMain->m_strPASSWORD = _T("");
				CString text;
				text.Format(_T("%s 님 안녕하세요!!"), name);
				pMain->SetDlgItemText(IDC_STATIC11, text);
				//비활성화 및 활성화
				pMain->GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
				pMain->GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);

			}
		}
		else if(szBuff[0] == '2'){	//준비 관련 메시지
			CString name;
			CString ready;
			CString msg;
			AfxExtractSubString(name, szBuff, 1, ' ');
			AfxExtractSubString(ready, szBuff, 2, ' ');
			if (ready == 'y') {
				msg.Format(_T("%s 님이 준비 하였습니다 \r\n"), name);
			}
			else {
				msg.Format(_T("%s 님이 준비취소 하였습니다 \r\n"), name);
			}
			pMain->m_ctrlEdit.ReplaceSel(msg);
		}
		else if (szBuff[0] == '3') {	//서버 연결 결과
			CString str1;
			CString str2;
			CString str3;
			CString msg;
			AfxExtractSubString(str1, szBuff, 1, ' ');
			AfxExtractSubString(str2, szBuff, 2, ' ');
			AfxExtractSubString(str3, szBuff, 3, ' ');
			msg.Format(_T("%s %s %s \r\n"), str1, str2, str3);
			pMain->m_ctrlEdit.ReplaceSel(msg);
			//EditControl 비활성 및 활성화
			pMain->GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
			pMain->GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
			pMain->GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
			pMain->GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
			pMain->GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
			pMain->GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
			pMain->GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);

		}
		else if (szBuff[0] == '4') {	//LeaderBoard 결과
			CString name, point;
			CString msg;
			for (int i = 0; i < 10; i+=2) {
				AfxExtractSubString(name, szBuff, i+1, ' ');
				AfxExtractSubString(point, szBuff, i+2, ' ');
				msg.Format(_T("%s\t\t%s \r\n"), name, point);
				pMain->m_ctrlLeaderBoard.ReplaceSel(msg);
			}

		}
		else {	//게임 시작

			CInGameDlg game;
			game.DoModal();

			game.DestroyWindow();

		}
	}
	CSocket::OnReceive(nErrorCode);
}
