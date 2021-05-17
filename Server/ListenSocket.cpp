// ListenSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Server.h"
#include "ListenSocket.h"
#include "ChildSocket.h"
#include "ServerDlg.h"

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CChildSocket* pChild = new CChildSocket;
	BOOL check = Accept(*pChild);
	if (check == FALSE) {
		delete pChild;
		return;
	}
	m_pChildSocketList.AddTail(pChild);

	CString strSocketName; UINT uPort;
	pChild->GetPeerName(strSocketName, uPort);
	CString str; str.Format(_T("[%s:%d] 서버 접속을 승인합니다.\r\n"), strSocketName, uPort);
	CServerDlg* pMain = (CServerDlg*)AfxGetMainWnd();
	pMain->m_ctrlEdit.ReplaceSel(str);

	pChild->Send(str.GetBuffer(), str.GetLength());

	pChild->m_pListenSocket = this;

	CAsyncSocket::OnAccept(nErrorCode);
}
