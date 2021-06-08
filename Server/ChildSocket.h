#pragma once

#include "ListenSocket.h"

// CChildSocket 명령 대상입니다.

class CChildSocket : public CSocket
{
public:
	CChildSocket();
	virtual ~CChildSocket();
	CListenSocket* m_pListenSocket;
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
//	void SignUp(CString id, CString password);
//	void Login(CString id, CString password);
//	CString m_prevword;
//	int m_isfirst;
};


