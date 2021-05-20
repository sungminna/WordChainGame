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
		switch (szBuff[0]) {
		case '0':	//회원가입
			break;
		case '1':	//로그인
			break;
		case '2':	//준비
			break;
		case '3':	//서버 연결
			break;
		case '4':	//게임 시작
			break;
		default:
			break;
		}


		if (szBuff[0] == '0') {	//회원가입
			CString name;
			CString msg;
			AfxExtractSubString(name, szBuff, 1, ' ');
			msg.Format(_T("%s 님이 회원가입 하셨습니다\r\n"), name);
			pMain->m_ctrlEdit.ReplaceSel(msg);
		}
		else if (szBuff[0] == '1') {	//로그인
			CString name;
			CString msg;
			AfxExtractSubString(name, szBuff, 1, ' ');
			msg.Format(_T("%s 님이 로그인 하셨습니다\r\n"), name);
			pMain->m_ctrlEdit.ReplaceSel(msg);
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
			CString str4;
			CString msg;
			AfxExtractSubString(str1, szBuff, 1, ' ');
			AfxExtractSubString(str2, szBuff, 2, ' ');
			AfxExtractSubString(str3, szBuff, 3, ' ');
			AfxExtractSubString(str4, szBuff, 4, ' ');
			msg.Format(_T("%s %s %s %s"), str1, str2, str3, str4);
			pMain->m_ctrlEdit.ReplaceSel(msg);
		}
		else {	//게임 시작

			CInGameDlg game;
			game.DoModal();

			game.DestroyWindow();

		}
	}
	CSocket::OnReceive(nErrorCode);
}
