// AccessDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EsperClient.h"
#include "AccessDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include "Communication.h"
#include <vector>


// CAccessDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAccessDlg, CDialogEx)

CAccessDlg::CAccessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ACCESS, pParent)
{

}

CAccessDlg::~CAccessDlg()
{
}

void CAccessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_authlistctrl);
}

BOOL CAccessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	std::ifstream fin;
	fin.open("C:\\Program Files (x86)\\Esper\\idsk.txt");
	fin >> m_userid >> m_sessionkey;

	SetDlgItemText(IDC_ACCESS_STATIC_USERNAME, m_userid.c_str());
	SetDlgItemText(IDC_ACCESS_STATIC_FILENAME, m_filename.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BEGIN_MESSAGE_MAP(CAccessDlg, CDialogEx)	
	ON_BN_CLICKED(IDC_ACCESS_BTT_ADD, &CAccessDlg::OnBnClickedAccessBttAdd)
	ON_BN_CLICKED(IDOK, &CAccessDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAccessDlg 메시지 처리기입니다.




void CAccessDlg::OnBnClickedAccessBttAdd()
{
	/*
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItem(IDC_ACCESS_EDIT_ADD)->GetWindowText(str);
	CT2CA temp(str);
	std::string tempstr(temp);
	item.AccessorID = tempstr;
	item.setId(m_userid);
	item.SessionKey = m_sessionkey;
	/*
	//통신 목표 설정
	SOCKET s = socketCreate();
	if (s == SOCKET_ERROR) AfxMessageBox(_T("socket error!"), MB_OK);
	/*
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4500);
	addr.sin_addr.s_addr = inet_addr("165.132.144.106");
	*/

	//if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1) {
	//	AfxMessageBox(_T("connection(dir) error!"), MB_OK);
	//}
	/*
	if (sockSetting(s) == -1)
		AfxMessageBox(_T("connection error!"), MB_OK);
	else {
		socket_send(s, "accessorCheck", item);
		//closesocket(s);
		ShowWindow(SW_HIDE);
	}
	string strtemp = NULL;
	socket_recv(s, &strtemp);

	if (resultpacketbuffer1 == "succ")
	{
		m_authlistctrl.AddString(str);
		UpdateData(TRUE);
		item.Accessor.push_back(tempstr);
	 }
	else if (resultpacketbuffer1 == "fail")
	{
		AfxMessageBox(_T("잘못된 아이디입니다."));
	}
	else
	{
		AfxMessageBox(_T("서버와 통신이 실패했습니다."));
	}

	closesocket(s);
	WSACleanup();*/

	CString str;
	GetDlgItem(IDC_ACCESS_EDIT_ADD)->GetWindowText(str);
	CT2CA temp(str);
	string tempstr(temp);
	ifstream fin;
	fin.open("C:\\Program Files (x86)\\Esper\\idsk.txt");
	fin >> m_userid >> m_sessionkey;
	item.AccessorID = tempstr;
	item.setId(m_userid);
	item.SessionKey = m_sessionkey;

	//통신 목표 설정
	SOCKET s = socketCreate();
	if (s == SOCKET_ERROR) AfxMessageBox(_T("socket error!"), MB_OK);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4500);
	addr.sin_addr.s_addr = inet_addr("165.132.144.106");
	//if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1) {
	//	AfxMessageBox(_T("connection(dir) error!"), MB_OK);
	//}

	if (sockSetting(s) == -1)
		AfxMessageBox(_T("connection error!"), MB_OK);
	else {
		socket_send(s, "accessorCheck", item);
		//closesocket(s);
		//ShowWindow(SW_HIDE);
	}
	std::string strtemp;
	socket_recv(s, &strtemp);
	AfxMessageBox(_T("1"));
	if (resultpacketbuffer1 == "succ")
	{
		AfxMessageBox(_T("2"));
		m_authlistctrl.AddString(str);
		UpdateData(TRUE);
		item.Accessor.push_back(tempstr);
		AfxMessageBox(_T("3"));
	}
	else if (resultpacketbuffer1 == "fail")
	{
		AfxMessageBox(_T("잘못된 아이디입니다."));
	}
	else
	{
		AfxMessageBox(_T("서버와 통신이 실패했습니다."));
		::SendMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
	}

	closesocket(s);
}


void CAccessDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//id, session
	ifstream fin;
	fin.open("C:\\Program Files (x86)\\Esper\\idsk.txt");
	fin >> m_userid >> m_sessionkey;
	item.UserId = m_userid;
	item.SessionKey = m_sessionkey;
	item.FileName = m_filename;
	
	//통신 목표 설정
	SOCKET s = socketCreate();
	if (s == SOCKET_ERROR) AfxMessageBox(_T("socket error!"), MB_OK);


	if (sockSetting(s) == -1)
		AfxMessageBox(_T("connection error!"), MB_OK);
	else {
		for (int i = 0; i < item.Accessor.size(); i++)
		{

			AfxMessageBox(item.Accessor[i].c_str());
		}
		socket_send(s, "authUpdate", item);
		//closesocket(s);
		//ShowWindow(SW_HIDE);
	}
	
	string strtemp;	 
	AfxMessageBox(_T("Here1"));
	socket_recv(s, &strtemp);
	if (resultpacketbuffer2 == "succ")
	{
		AfxMessageBox(_T("접근 권한이 변경되었습니다."));
	}
	else
	{
		AfxMessageBox(_T("서버와 통신이 실패했습니다."));
	}
	

	closesocket(s);

	CDialogEx::OnOK();
}
