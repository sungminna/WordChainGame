#pragma once

// CClientSocket 명령 대상입니다.

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	CString m_turn;
	CString m_ID;
	CString m_MyScore;
	CString m_OtherScore;
	int m_itime;
	CString m_MyLastInput;
};


