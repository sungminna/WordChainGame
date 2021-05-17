// ChildSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Server.h"
#include "ChildSocket.h"
#include "ServerDlg.h"

// CChildSocket

CChildSocket::CChildSocket()
{
}

CChildSocket::~CChildSocket()
{
}


// CChildSocket 멤버 함수


void CChildSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	POSITION pos = m_pListenSocket->m_pChildSocketList.Find(this);
	m_pListenSocket->m_pChildSocketList.RemoveAt(pos);
	CString strSocketName; UINT uPort;
	this->GetPeerName(strSocketName, uPort);
	CString str; str.Format(_T("[%s:%d] 연결 종료\r\n"), strSocketName, uPort);
	CServerDlg* pMain = (CServerDlg*)AfxGetMainWnd();
	pMain->m_ctrlEdit.ReplaceSel(str);
	this->ShutDown();
	this-> Close();
	delete this;
	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString strlPAddress; UINT uPortNumber;
	GetPeerName(strlPAddress, uPortNumber);

	TCHAR szBuffer[1024];
	int nRead = Receive(szBuffer, sizeof(szBuffer));
	switch (nRead) {
	case 0: this->Close(); break;
	case SOCKET_ERROR: if (GetLastError() != WSAEWOULDBLOCK) {
		AfxMessageBox(_T("Error occured"));
		this->Close();
	}break;
	default:
		szBuffer[nRead] = _T('\0');
		CString str; str.Format(_T("[%s:%u] %s"), strlPAddress, uPortNumber, szBuffer);
		CServerDlg* pMain = (CServerDlg*)AfxGetMainWnd();
		pMain->m_ctrlEdit.ReplaceSel(str);

		//m_pListenSocket->Broadcast(str);	브로드캐스트 필요 x
		break;
	}
	CSocket::OnReceive(nErrorCode);
}
