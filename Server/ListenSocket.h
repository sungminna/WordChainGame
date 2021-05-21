#pragma once

// CListenSocket 명령 대상입니다.

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	CPtrList m_pChildSocketList;
	virtual void OnAccept(int nErrorCode);
	void Broadcast(CString strMessage);
//	MYSQL m_mysql;
};


