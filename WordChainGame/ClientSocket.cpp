// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WordChainGame.h"
#include "ClientSocket.h"


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
