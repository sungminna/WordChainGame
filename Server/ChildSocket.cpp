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
	//map 에서 삭제
	CString name;
	name.Format(_T("%s"), pMain->m_usermap[uPort]);
	pMain->m_usermap.erase(uPort);
	pMain->m_ready.erase(name);
	pMain->m_mapScore.erase(name);
	pMain->m_numlogged--;	//로그인한 사람수 -1

	//타이머 종료 및 브로드캐스트
	pMain->KillTimer(1);



	this->ShutDown();
	this-> Close();
	delete this;
	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//메시지 받고 난 후
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

		CServerDlg* pDlg = (CServerDlg*)AfxGetMainWnd();
		pDlg->m_ctrlEdit.ReplaceSel(str);

		if (szBuffer[0] == '0') {
			//회원가입
			CString ID, PASSWORD;
			AfxExtractSubString(ID, szBuffer, 1, ' ');
			AfxExtractSubString(PASSWORD, szBuffer, 2, ' ');
			pDlg->SignUp(ID, PASSWORD, uPortNumber);
		}
		else if (szBuffer[0] == '1') {
			//로그인
			CString ID, PASSWORD;
			AfxExtractSubString(ID, szBuffer, 1, ' ');
			AfxExtractSubString(PASSWORD, szBuffer, 2, ' ');
			pDlg->Login(ID, PASSWORD, uPortNumber);
		}
		else if (szBuffer[0] == '2') {
			//준비 여부
			CString status;
			CString username;
			CString msg;
			AfxExtractSubString(status, szBuffer, 1, ' ');

			if (status == "ready") {
				//준비
				username = pDlg->m_usermap.at(uPortNumber);
				msg.Format(_T("2 %s y \r\n"), username);
				pDlg->Ready(1, username, msg);
			}
			else {
				//준비 취소
				username = pDlg->m_usermap.at(uPortNumber);
				msg.Format(_T("2 %s n \r\n"), username);
				pDlg->Ready(0, username, msg);
			}
		}
		else if (szBuffer[0] == '5') {
			//타임 아웃
			CString username;
			CString time, turn, query, temp;
			username = pDlg->m_usermap.at(uPortNumber);

			//점수 깍기
			if (pDlg->m_mapScore.at(username) < 5) {	//0이하 스코어 존재 x
				pDlg->m_mapScore.at(username) = 0;
			}
			else {
				pDlg->m_mapScore.at(username) -= 5;	//깎을 점수 정하기
			}
			
			//턴 넘기기
			
			for (auto it = pDlg->m_usermap.begin(); it != pDlg->m_usermap.end(); it++) {
				if (username != it->second) {
					turn = it->second;
					break;
				}
			}

			time.Format(_T("10000"));
			query.Format(_T("5 %s %s "), turn, time);
			for (auto it = pDlg->m_mapScore.begin(); it != pDlg->m_mapScore.end(); it++) {
				temp.Format(_T("%s %d "), it->first, it->second);
				query.Append(temp);
			}
			temp.Format(_T("1 0 0 "));	//타임아웃에 의한 턴 변경, 게임 시작 아니다, 총게임 시간 포함 x
			query.Append(temp);
			temp.Format(_T("\r\n"));
			query.Append(temp);
			m_pListenSocket->Broadcast(query);	//다음 턴 사람에게 메시지 보내기

			pDlg->m_ctrlEdit.ReplaceSel(query);
		}
		else if (szBuffer[0] == '6') {	//단어 받음
			
			CString word;
			CString query;
			CString prev_R;
			CString now_L;
			int length;
			int islink = 1;
			int wrong_char = 0;	//잘못된 글자가 있을 시 1
			int success;
			
			AfxExtractSubString(word, szBuffer, 1, ' ');

			//잘못된 글자 있는지 확인 추가 필요
			wrong_char = 0;
			length = word.GetLength();

			//단어 확인
			

			//한글 2byte 영어 1byte

			//링크 확인
			prev_R = pDlg->m_prevword.Right(2);
			now_L = word.Left(2);

			if ((prev_R == now_L) || pDlg->m_isfirst == 1) {
				islink = 1;
			}
			else {
				islink = 0;
			}

			//rest 확인추가

			
			if ((islink == 1) & (length != 0) & (wrong_char == 0)) {
				success = 1;
			}
			else {
				success = 0;
			}

			


			//성공시 1 실패시 0
			query.Format(_T("6 %s %d \r\n"), word, success);

			m_pListenSocket->Broadcast(query);
			pDlg->m_ctrlEdit.ReplaceSel(query);
			
			if (success == 1) {	//성공
				pDlg->m_isfirst = 0;
				pDlg->m_prevword = word;	//prev에 word 저장
				//턴 넘김
				CString username;
				CString time, turn, temp;
				username = pDlg->m_usermap.at(uPortNumber);

				//점수 주기
				pDlg->m_mapScore.at(username) += 10;	//추가할 점수 정하기

				//턴 넘기기

				for (auto it = pDlg->m_usermap.begin(); it != pDlg->m_usermap.end(); it++) {
					if (username != it->second) {
						turn = it->second;
						break;
					}
				}

				time.Format(_T("10000"));	//시간 정하기
				query.Format(_T("5 %s %s "), turn, time);
				for (auto it = pDlg->m_mapScore.begin(); it != pDlg->m_mapScore.end(); it++) {
					temp.Format(_T("%s %d "), it->first, it->second);
					query.Append(temp);
				}
				temp.Format(_T("0 0 "));	//타임아웃에 의한 턴 변경(주기)아니다, 게임시작 아니다, 총게임시간 포함 x
				query.Append(temp);
				temp.Format(_T("\r\n"));
				query.Append(temp);
				m_pListenSocket->Broadcast(query);	//다음 턴 사람에게 메시지 보내기

				pDlg->m_ctrlEdit.ReplaceSel(query);
			}
			else {	//실패

				
			}

		}

		break;
	}
	CSocket::OnReceive(nErrorCode);
}